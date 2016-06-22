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
#define standard_gauge 1430.00//��׼��೤��Ϊ1430.00mm
#define RIN 510
#define ROUT 4990
#define RSENSE 10
#define ADCHECKAUM 50  ///AD��������

#define ADSAMPLETIME    ADC_SampleTime_84Cycles

typedef struct
{
    U16 gauge_ADbuf[ADCHECKAUM];///ADת�������
    U16 gauge_AD;///����ѹֵ
    U16 voltage_AD;
    U16 current_AD;
    U16 interior_temper_AD;
    U16 external_temper_AD;
    
}SYSTEMPARAMETER_TypeDef;


///AD�ɼ�����
STATIC unsigned char GuaSum=40;

///AD�޳�����
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
    
	//�ȳ�ʼ��IO��
	GPIO_Set(ADC_GPIO, ADC_PIN, GPIO_Mode_AN, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
   

    RCC_ADC_CONFIG_EX();

	ADC_SOURCE->CR1=0;   			//CR1��������
	ADC_SOURCE->CR2=0;   			//CR2�������� 

	ADC_TempSensorVrefintCmd(ENABLE);//ʹ���ڲ��¶ȴ�����

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; //ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC_SOURCE, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC_SOURCE, ADC_CHANNEL, 1, ADSAMPLETIME );	//ADC1-10,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			
    ADC_RegularChannelConfig(ADC_SOURCE, ADC_TEMP_CHANNEL, 1, ADSAMPLETIME );
    
    ADC_Cmd(ADC_SOURCE, ENABLE);//����ADת����	
    

}

//���ADCֵ
//ch:ͨ��ֵ 0~16��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
VOID Get_Adc(U8 ch, P_U16 pParam)   
{
	 //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC_SOURCE, ch, 1, ADSAMPLETIME );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC_SOURCE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC_SOURCE, ADC_FLAG_EOC ));//�ȴ�ת������

	*pParam = ADC_GetConversionValue(ADC_SOURCE);	//�������һ��ADC1�������ת�����

 
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ

VOID Get_Adc_Average(U8 ch, U8 times, P_U16 pParam)
{
	u32 temp_val=0;
    U16 tempvalue = 0;
	UINT uCurrentTick;
	U8 t;
	for(t=0;t<times;t++)
	{
        Get_Adc(ch, &tempvalue);//��ȡͨ��ת��ֵ
		temp_val+=tempvalue;
		uCurrentTick = GetTickCount();
		while(GetTickCount() - uCurrentTick < 2);
	}
	*pParam = temp_val/times;
} 


//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��,��λ:��.)

VOID Get_Temprate(P_U16 pParam)
{
    u16 adcx;
    u16 result;
    double temperate;
	Get_Adc_Average(ADC_TEMP_CHANNEL,10,&adcx);	//��ȡͨ��16�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
	temperate=(float)adcx*(3.3/4096);		//��ѹֵ
	temperate=(temperate-0.76)/0.0025 + 25; //ת��Ϊ�¶�ֵ 
	result=temperate*=100;					//����100��.
	*pParam = result;
}

/**********************************************************************
* Procedure:	BubSortð�ݷ���������ƽ��ֵ
* Function:	ð�ݷ���������ƽ��ֵ
*                 
* Parameter:	None		
* Result:	fsum  ƽ��ֵ���		
* Description:	��
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
                  ������
  ***************************************/
STATIC VOID Gauge_Gompute(U16 string)
{
    systemvalue.gauge_DC=(string*ADC_VREF/4096.00);
    SYSTEMPARAMETER.gauge_AD=0;
    systemvalue.gauge_mm=standard_gauge+(systemvalue.gauge_DC*(100.00/3.30));//����ʵ�ʳ���=���Ĺ涨����+�������Ĳ���ֵ+ƫ��ֵ
}

/****************************************
      ϵͳ��������
  **************************************/
VOID SystemParameter_Compute(VOID)
{
    systemvalue.system_v = (SYSTEMPARAMETER.voltage_AD*ADC_VREF/4096.00)*6.0725;
    systemvalue.system_c = (SYSTEMPARAMETER.current_AD*ADC_VREF/4096.00*100)*RIN/(ROUT*RSENSE);//ϵͳ����=v/r
    systemvalue.systemexternal_T_MMDC = SYSTEMPARAMETER.interior_temper_AD*(ADC_VREF/4096.00);
    systemvalue.systeminterior_T = 25.0000 + (((double)1.43 - systemvalue.systemexternal_T_MMDC)/0.0043);//оƬ�ڲ��¶ȴ�����
    SYSTEMPARAMETER.voltage_AD = 0;
    SYSTEMPARAMETER.current_AD = 0;
    SYSTEMPARAMETER.interior_temper_AD = 0;
}


//ת��40�εó���ѹֵ
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
        ///��ADת��ֵת���ɹ���ѹֵ
    Gauge_Gompute(SYSTEMPARAMETER.gauge_AD);
}




