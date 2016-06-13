#include "mileage.h"
#include "adc.h"
#include "usart.h"
#include "comm.h"

STATIC U8 *g_pData;

STATIC VOID DebugMeasure(VOID)
{
  
    unsigned long miles;
    unsigned int gauges;
    double mileage_a;    

    U32 u32Tick;
    u32Tick = GetTickCount();
    calculate_mileage();
    Adc_Read();
    if(mileage_record.mileage_sign=='-')
        mileage_a=0-mileage_record.mileage;
    else mileage_a=mileage_record.mileage;
        miles=((unsigned long)(mileage_a *1000));
    
    
        
    *(g_pData) = '#';
    *(g_pData + 1) = (u32Tick/1000000000)+'0' ;
    *(g_pData + 2) = ((u32Tick/100000000)%10)+'0' ;
    *(g_pData + 3) = ((u32Tick/10000000)%10)+'0' ;
    *(g_pData + 4) = ((u32Tick/1000000)%10)+'0' ;
    *(g_pData + 5) = ((u32Tick/100000)%10)+'0' ;
    *(g_pData + 6) = ((u32Tick/10000)%10)+'0' ;
    *(g_pData + 7) = ((u32Tick/1000)%10)+'0' ;
    *(g_pData + 8) = ((u32Tick/100)%10)+'0' ;
    *(g_pData + 9) = ((u32Tick/10)%10)+'0' ;
    *(g_pData + 10) = (u32Tick%10)+'0' ;

    *(g_pData + 11) = '\\';        
    *(g_pData + 12) = mileage_record.mileage_sign;
    *(g_pData + 13) = (miles/10000000)+'0' ;
    *(g_pData + 14) = (miles%10000000)/1000000+'0' ;
    *(g_pData + 15) = (miles%1000000)/100000+'0' ;
    *(g_pData + 16) = (miles%100000)/10000+'0' ;
    *(g_pData + 17) = (miles%10000)/1000+'0' ;
    *(g_pData + 18) = '.';
    *(g_pData + 19) = (miles%1000)/100+'0' ;
    *(g_pData + 20) = (miles%100)/10+'0' ;
    *(g_pData + 21) = (miles%10)/1+'0' ;
   
    *(g_pData + 22) = '\\';
    //下面的是轨距电压值    
    gauges = systemvalue.gauge_DC;
    gauges=systemvalue.gauge_DC*1000;
    systemvalue.gauge_DC=0;
    *(g_pData + 23) = (gauges/1000)+'0' ;
    *(g_pData + 24) ='.';
    *(g_pData + 25) =(gauges%1000)/100+'0' ;
    *(g_pData + 26) =(gauges%100)/10+'0' ;
    *(g_pData + 27) =(gauges%10)/1+'0' ;;
  
    *(g_pData + 28) = '\r' ;
    *(g_pData + 29) = '\n' ;

    Usart1_DMA_Send(g_pData, 30);
	
    //下面的是换算成轨距
//    gauges = systemvalue.gauge_mm;   
//    g_pData[23]=(gauges/1000)+'0' ;
//    g_pData[24]=(gauges%1000)/100+'0' ;
//    g_pData[25]=(gauges%100)/10+'0' ;
//    g_pData[26]=(gauges%10)/1+'0' ;
//    g_pData[27]='.';
//    gauges = systemvalue.gauge_mm*100; 
//    g_pData[28]=(gauges%100)/10+'0' ;
//    g_pData[29]=(gauges%10)/1+'0' ;
//    g_pData[30]='\r';
//    g_pData[31]='\n';

//    Usart1_DMA_Send(g_pData, 32); 
    

}
VOID TestMileageProc(VOID)
{
    
    g_pData = mymalloc(SRAMIN, 35);//5个间隔符，10个时间，17个里程轨距信息
    
    if(g_pData == NULL)
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
	printf("Mileage TEST\r\n");
	
	while(1)
	{	
        DebugMeasure();
        DelayMs(300);
	}

}
TIM_ICInitTypeDef  TIM_ICInitStructure;
U16 IC2Value = 0;
U16 DutyCycle = 0;
U32 Frequency = 0;

STATIC U32 g_u32Capture1 = 0;
STATIC U32 g_u32Capture2 = 0;
STATIC U32 g_u32Tick = 0;
VOID TIM1_CC_IRQHandler(VOID)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_CC3) == SET) 
	{
		/* Clear TIM1 Capture compare interrupt pending bit */
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
		g_u32Capture1++;
		
	}
	if(TIM_GetITStatus(TIM1, TIM_IT_CC4) == SET) 
	{
		/* Clear TIM1 Capture compare interrupt pending bit */
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
		g_u32Capture2++;
		
	}
	g_u32Tick = GetTickCount();
}

STATIC VOID TIM_Config(VOID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* GPIOE clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/* TIM1 chenne3 configuration : PE.13 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* TIM1 chenne4 configuration : PE.14 */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect TIM pin to AF2 */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);

	/* Connect TIM pin to AF2 */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

	/* Enable the TIM4 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM1, &TIM_ICInitStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM1, ENABLE);

	/* Enable the CC3 Interrupt Request */
	TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE);
	/* Enable the CC4 Interrupt Request */
	TIM_ITConfig(TIM1, TIM_IT_CC4, ENABLE);

}

VOID TestFrequency(VOID)
{
	TIM_Config();
	
	while(1)
	{
		if((GetTickCount() - g_u32Tick) >3000)
		{
			printf("The current Capture1 = 0x%04d \r\n", g_u32Capture1);
			printf("The current Capture2 = 0x%04d \r\n", g_u32Capture2);
			g_u32Tick = GetTickCount();
		}
	}

}






            
   
