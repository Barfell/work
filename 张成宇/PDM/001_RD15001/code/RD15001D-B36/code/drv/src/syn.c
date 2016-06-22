/**********************************************************************   
* Module: 		同步  
* Function: 	CONTROL  SYN 
* Description: 	NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/03/16            SYAN                        	CREATE
**********************************************************************/ 
 
#include "mileage.h"
#include "adc.h"
#include "usart.h"
#include "key.h"
#include "GUI.h"
#include "syn.h"
STATIC U32 g_u32SynCount = 0;
STATIC U32 g_u32SynCnt = 0;
STATIC U8 *g_pData;
STATIC BOOL g_bMileAccess = FALSE;
STATIC BOOL g_bGaugeAccess = FALSE;
BOOL g_bMileGaugeAccess = FALSE;
U32 GetSynCount(VOID)
{
    return g_u32SynCount;
}
VOID SynInit(VOID)
{    	 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
    
    NVIC_InitTypeDef NVIC_InitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;
    
/*50ms进行发送一次*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);

	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
}



VOID TIM3_IRQHandler(VOID)
{ 
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)==SET)
	{        
        g_u32SynCount ++;
        if(g_u32SynCount%50 == 0)
		{
            g_bMileGaugeAccess = TRUE;
//            g_u32SynCnt = g_u32SynCount;
//			SendMileGaugeDataProc();
		}

	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);  //清除中断标志位
}

//发送里程轨距等数据
VOID HandleSynDataProc(VOID)
{
    if(g_bMileGaugeAccess == TRUE)
    {
        SendMileGaugeDataProc();
        
        g_bMileGaugeAccess = FALSE;
    }
    else if(g_bMileAccess == TRUE)
    {
        SendMileDataProc();
        
        g_bMileAccess = FALSE;
    }
    else if(g_bGaugeAccess == TRUE)
    {
        SendGaugeDataProc();
        
        g_bGaugeAccess = FALSE;
    }
}
VOID SendMileGaugeDataProc(VOID)
{
	unsigned long miles;
	unsigned int gauges;
	double mileage_a;    
	U8 szData[30] = {0};
	U16 u16Count;
	U32 u32Tick;
//    u32Tick = g_u32SynCnt;
	u32Tick = GetSynCount();
	g_pData = &szData[0];
	Adc_Read();
	calculate_mileage();
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

	u16Count = 30;
//	USART3_Send(g_pData, &u16Count);
	Usart3_DMA_Send(g_pData, u16Count);  
//	u16Count = 30;
////	USART1_Send(g_pData, &u16Count);
//	Usart1_DMA_Send(g_pData, u16Count);  
}
VOID SendMileDataProc(VOID)
{
	unsigned long miles;
	double mileage_a;    
	U8 szData[24] = {0};
	U16 u16Count;
	U32 u32Tick;
	u32Tick = GetSynCount();
	g_pData = &szData[0];
	calculate_mileage();
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
    *(g_pData + 22) = '\r' ;
    *(g_pData + 23) = '\n' ;

    
    u16Count = 24;
//    Usart3_DMA_Send(g_pData, u16Count);
	USART3_Send(g_pData, &u16Count); 
//	u16Count = 24;
//	USART1_Send(g_pData, &u16Count);
}

VOID SendGaugeDataProc(VOID)
{
	unsigned int gauges;
	U8 szData[19] = {0};
	U16 u16Count;
	U32 u32Tick;
	u32Tick = GetSynCount();
	Adc_Read();
	g_pData = &szData[0];
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
    //下面的是轨距电压值    
    gauges = systemvalue.gauge_DC;
    gauges=systemvalue.gauge_DC*1000;
    systemvalue.gauge_DC=0;
    *(g_pData + 12) = (gauges/1000)+'0' ;
    *(g_pData + 13) ='.';
    *(g_pData + 14) =(gauges%1000)/100+'0' ;
    *(g_pData + 15) =(gauges%100)/10+'0' ;
    *(g_pData + 16) =(gauges%10)/1+'0' ;;
  
    *(g_pData + 17) = '\r' ;
    *(g_pData + 18) = '\n' ;
    u16Count = 19;
//    Usart3_DMA_Send(g_pData, u16Count);
	USART3_Send(g_pData, &u16Count);
//	u16Count = 19;
//	USART1_Send(g_pData, &u16Count);
}


VOID DisplayMileDataProc(VOID)
{
	U8 u8KeyNumber;
	unsigned long miles;
	unsigned int gauges;
	double mileage_a;    
	U8 szData[30] = {0};
	U8 szDisData[18] = {0};
	U32 u32Tick;
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	pOldFont = GUI_SetFont(&GUI_Font6x8);//GUI_Font6x8
	
	u32Tick = GetSynCount();//获取时间
	g_pData = &szData[0];
	calculate_mileage();//计算里程值
	Adc_Read();//计算轨距电压
    if(mileage_record.mileage_sign=='-')
        mileage_a=0-mileage_record.mileage;
    else mileage_a=mileage_record.mileage;
        miles=((unsigned long)(mileage_a *1000));
    
    
        //系统节律时间点
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

		//里程值
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

  		 //轨距值
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
	
	memcpy(szDisData, g_pData + 11, 17);
	GUI_ClearRect(0, 0,  128, 0 + 12);//这里加12是因为避免影响下一行的数据
	GUI_DispStringAt((char *)szDisData, 0, 0);

	while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);	
			if(u8KeyNumber == KEY_EXIT)
			{
				GUI_Clear();
				break;
			}
					
						
		}
		
	}
	GUI_SetFont(pOldFont);
}
