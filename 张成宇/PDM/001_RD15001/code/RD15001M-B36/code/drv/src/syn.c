/**********************************************************************   
* Module: 		同步  
* Function: 	CONTROL  SYN 
* Description: 	NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/03/16            SYAN                        	CREATE
**********************************************************************/ 
#include "syn.h" 

STATIC U32 g_u32SynCount = 0;

VOID SynInit(VOID)
{    	 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
    
    NVIC_InitTypeDef NVIC_InitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;
    

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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
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

U32 GetSynCount(VOID)
{
    return g_u32SynCount;
}
  

STATIC U8 tx_buf[43] = {0x55,0xAA,0x00,0x00,0x00,0x00,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16
									,0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,0x25,0x26
									,0x27,0x28,0x29,0x30,0x31,0x32,0x33,0x34,0x35,0x36
									,0x37,0x38,0x39,0x40,0x41,0x42,0x43};

STATIC U32 g_u32TimerCount = 0;

STATIC U8 g_u8Count = 0;//产生各种频率事件的计数

STATIC U8  *g_pBuf1, *g_pBuf2;//GPS&INS模拟数据缓冲

U32 g_TestdataCount = 0, g_TestdataCount2 = 0;
U8 *g_pTestdataCount =  (U8 *)&g_TestdataCount;       
U8 *g_pTestdataCount2 =  (U8 *)&g_TestdataCount2;                                        

                                    
VOID TIMER_Init(U16 u16Cnt, U16 u16Predivision)
{        
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    
    NVIC_InitTypeDef NVIC_InitStructure;
    
    U8 u8Cnt;
    
    U8 *pBuf1 = mymalloc(SRAMIN, 43);
    
    U8 *pBuf2 = mymalloc(SRAMIN, 200);
    
    if((pBuf1 == NULL) || (pBuf2 == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
    
    else
    {
        g_pBuf1 = pBuf1;
        memcpy(pBuf1, tx_buf, 43);        
        pBuf1[0] = 0x55;
        pBuf1[1] = 0xAA;
       
        
        g_pBuf2 = pBuf2;
        pBuf2[0] = 0x55;
        pBuf2[1] = 0xAA;
        for(u8Cnt = 2; u8Cnt < 200; u8Cnt++)//产生GPS数据
        {
            pBuf2[u8Cnt] = u8Cnt;
        }

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟

        TIM_TimeBaseInitStructure.TIM_Period = u16Cnt; 	//自动重装载值
        TIM_TimeBaseInitStructure.TIM_Prescaler= u16Predivision;  //定时器分频
        TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
        TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

        TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3

        TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
        TIM_Cmd(TIM3,ENABLE); //使能定时器3

        NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    }
}
                         
VOID TIM3_IRQHandler(VOID)
{ 
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)==SET)
	{        
        g_u32SynCount ++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);  //清除中断标志位
	}

	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		if((bUsbPlugin == FALSE) && (g_bSave == FALSE)) //溢出中断     
		{			
			memcpy(g_pUsart1_rx_buf, g_pBuf1, 43);
			SetUsartCurrentLength(USART1_TYPE, 43);
			g_pUsart1_rx_buf[2] = *g_pTestdataCount ;
			g_pUsart1_rx_buf[3] = *(g_pTestdataCount + 1) ;
			g_pUsart1_rx_buf[4] = *(g_pTestdataCount + 2) ;
			g_pUsart1_rx_buf[5] = *(g_pTestdataCount + 3) ;
			
			AddQueue(pUsart1Data, g_pUsart1_rx_buf, pQueueUsart1Info, 43);
			
			if(g_u8Count == 20)//每100ms
			{
				g_u8Count = 0;
				memcpy(g_pUsart2_rx_buf, g_pBuf2, 200);
				SetUsartCurrentLength(USART2_TYPE, 200);
				g_pUsart2_rx_buf[2] = *g_pTestdataCount2 ;
				g_pUsart2_rx_buf[3] = *(g_pTestdataCount2 + 1) ;
				g_pUsart2_rx_buf[4] = *(g_pTestdataCount2 + 2) ;
				g_pUsart2_rx_buf[5] = *(g_pTestdataCount2 + 3) ;

				
				AddQueue(pUsart2Data, g_pUsart2_rx_buf, pQueueUsart2Info, 200);
				
				
				g_TestdataCount2++;
	//			HandleOtherDataProc();
				g_u32TimerCount ++;
			}
			
			g_u8Count++;
			g_TestdataCount++;
		}
        
      	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位  
	}

}

