/**********************************************************************   
* Module: 		ADC  
* Function: 	CONTROL  ADC
* Description: 	NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/03/16            SYAN                        	CREATE
**********************************************************************/ 
#include "adc.h"

#define RCC_ADC_CONFIG()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE)
#define RCC_ADC_CONFIG_EX()		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE)
#define ADC_GPIO				GPIOC
#define ADC_PIN					GPIO_Pin_0
#define ADC_SOURCE				ADC3

#define ADC_VREF	3.290
#define standard_gauge 1430.00//标准轨距长度为1430.00mm
#define RIN 510
#define ROUT 4990
#define RSENSE 10
#define ADCHECKAUM 50  ///AD采样次数

#define ADSAMPLETIME    ADC_SampleTime_84Cycles

typedef struct
{
    U16 gauge_ADbuf[ADCHECKAUM];///AD转换缓冲包
    U16 gauge_AD;///轨距电压值
    U16 voltage_AD;
    U16 current_AD;
    U16 interior_temper_AD;
    U16 external_temper_AD;
    
}SYSTEMPARAMETER_TypeDef;


///AD采集点数
STATIC unsigned char GuaSum=40;

///AD剔除点数
STATIC unsigned char AdCallnum=5;

STATIC SYSTEMPARAMETER_TypeDef SYSTEMPARAMETER;

systemvalue_TypeDef systemvalue;

VOID Adc_Init(VOID)
{    
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
    
    U8 index;
    for (index = 0; index < ADCHECKAUM; index++)
    {
        SYSTEMPARAMETER.gauge_ADbuf[index] = 0;
    }
    SYSTEMPARAMETER.gauge_AD = 0;
    SYSTEMPARAMETER.current_AD = 0;
    SYSTEMPARAMETER.external_temper_AD = 0;
    SYSTEMPARAMETER.interior_temper_AD = 0;
    SYSTEMPARAMETER.voltage_AD = 0;
    systemvalue.gauge_DC = 0;
    systemvalue.gauge_m = 0.00000;
    systemvalue.gauge_mm = 0000.00;
    systemvalue.systemexternal_T = 00.000;
    systemvalue.systeminterior_T = 0.000;
    systemvalue.system_c = 000.00;
    systemvalue.system_v = 00.00;

	RCC_ADC_CONFIG();
    
	//先初始化IO口
	GPIO_Set(ADC_GPIO, ADC_PIN, GPIO_Mode_AN, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
   

    RCC_ADC_CONFIG_EX();

	ADC_SOURCE->CR1=0;   			//CR1设置清零
	ADC_SOURCE->CR2=0;   			//CR2设置清零 

	ADC_TempSensorVrefintCmd(ENABLE);//使能内部温度传感器

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; //ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC_SOURCE, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC_SOURCE, ADC_CHANNEL, 1, ADSAMPLETIME );	//ADC1-10,ADC通道,480个周期,提高采样时间可以提高精确度			
    ADC_RegularChannelConfig(ADC_SOURCE, ADC_TEMP_CHANNEL, 1, ADSAMPLETIME );
    
    ADC_Cmd(ADC_SOURCE, ENABLE);//开启AD转换器	
    

}

//获得ADC值
//ch:通道值 0~16：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
VOID Get_Adc(U8 ch, P_U16 pParam)   
{
	 //设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC_SOURCE, ch, 1, ADSAMPLETIME );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC_SOURCE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC_SOURCE, ADC_FLAG_EOC ));//等待转换结束

	*pParam = ADC_GetConversionValue(ADC_SOURCE);	//返回最近一次ADC1规则组的转换结果

 
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值

VOID Get_Adc_Average(U8 ch, U8 times, P_U16 pParam)
{
	u32 temp_val=0;
    U16 tempvalue = 0;
	UINT uCurrentTick;
	U8 t;
	for(t=0;t<times;t++)
	{
        Get_Adc(ch, &tempvalue);//获取通道转换值
		temp_val+=tempvalue;
		uCurrentTick = GetTickCount();
		while(GetTickCount() - uCurrentTick < 2);
	}
	*pParam = temp_val/times;
} 


//得到温度值
//返回值:温度值(扩大了100倍,单位:℃.)

VOID Get_Temprate(P_U16 pParam)
{
    u16 adcx;
    u16 result;
    double temperate;
	Get_Adc_Average(ADC_TEMP_CHANNEL,10,&adcx);	//读取通道16内部温度传感器通道,10次取平均
	temperate=(float)adcx*(3.3/4096);		//电压值
	temperate=(temperate-0.76)/0.0025 + 25; //转换为温度值 
	result=temperate*=100;					//扩大100倍.
	*pParam = result;
}

/**********************************************************************
* Procedure:	BubSort冒泡法法排序求平均值
* Function:	冒泡法法排序求平均值
*                 
* Parameter:	None		
* Result:	fsum  平均值结果		
* Description:	无
* Attribute:    
***********************************************************************
* LOG	DATE			AUTHOR					ACTION
***********************************************************************
**********************************************************************/
STATIC U16 BubSort(U16 *istr, U8 sum)
{
	U16 index1;
	U16 index2;
	U16 index3;
	float fsum=0;
	float fmin=0;
	float fmax=0;
	U16 Data=0;
	for(index1 = 0; index1 < sum ; index1 ++)
    {
        for(index2 = 0; index2 < sum-index1 ; index2 ++)
            {
                 if(istr[index2]>istr[index2+1])
                    {
                        Data=istr[index2];
                    istr[index2]=istr[index2+1];
                    istr[index2+1]=Data;
                    }
            }
    }
	for(index3=0;index3 < sum ; index3 ++)
	fsum += (float)istr[index3];
	for(index3=0;index3 < AdCallnum ; index3 ++)
	fmin += (float)istr[index3];
	for(index3=sum-AdCallnum;index3 < sum ; index3 ++)
	fmax += (float)istr[index3];
	fsum = (fsum - fmax - fmin) / (sum - AdCallnum*2);
	return (unsigned int)fsum;	
}

/***************************************
                  轨距计算
  ***************************************/
STATIC VOID Gauge_Gompute(U16 string)
{
    systemvalue.gauge_DC=(string*ADC_VREF/4096.00);
    SYSTEMPARAMETER.gauge_AD=0;
    systemvalue.gauge_mm=standard_gauge+(systemvalue.gauge_DC*(100.00/3.30));//轨距的实际长度=轨距的规定长度+传感器的测量值+偏差值
}

/****************************************
      系统参数计算
  **************************************/
VOID SystemParameter_Compute(VOID)
{
    systemvalue.system_v = (SYSTEMPARAMETER.voltage_AD*ADC_VREF/4096.00)*6.0725;
    systemvalue.system_c = (SYSTEMPARAMETER.current_AD*ADC_VREF/4096.00*100)*RIN/(ROUT*RSENSE);//系统电流=v/r
    systemvalue.systemexternal_T_MMDC = SYSTEMPARAMETER.interior_temper_AD*(ADC_VREF/4096.00);
    systemvalue.systeminterior_T = 25.0000 + (((double)1.43 - systemvalue.systemexternal_T_MMDC)/0.0043);//芯片内部温度传感器
    SYSTEMPARAMETER.voltage_AD = 0;
    SYSTEMPARAMETER.current_AD = 0;
    SYSTEMPARAMETER.interior_temper_AD = 0;
}


//转换40次得出电压值
VOID Adc_Read(VOID)
{
    U8 index;
    for (index = 0; index < GuaSum; index++)
    {
        Get_Adc(ADC_CHANNEL, &(SYSTEMPARAMETER.gauge_ADbuf[index]));
    } 
    
    SYSTEMPARAMETER.gauge_AD = BubSort(SYSTEMPARAMETER.gauge_ADbuf,GuaSum);
    
    for (index = 0;index < GuaSum; index++)
    {
        SYSTEMPARAMETER.gauge_ADbuf[index] = 0;	
    }
        ///将AD转换值转换成轨距电压值
    Gauge_Gompute(SYSTEMPARAMETER.gauge_AD);
}




