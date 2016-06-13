/**********************************************************************   
* Module: 				SYNCHRONIZATION  
* Function: 			CONTROL  SYN 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "syn.h" 

STATIC volatile U32 g_u32EtrSynCount = 0, g_u32TotalEtrCount = 0;

VOID EtrSynThreadProc(VOID)
{
    if(TIM_GetCounter(TIM2) >= 0xEA60)
    {
        TIM_SetCounter(TIM2, TIM_GetCounter(TIM2) - 0xEA60);
        g_u32EtrSynCount = g_u32EtrSynCount + 0xEA60;	
    }  
}

U32 GetEtrSynCount(VOID)
{
     g_u32TotalEtrCount = g_u32EtrSynCount + TIM_GetCounter(TIM2);
     return g_u32TotalEtrCount;
}

VOID EtrSynInit(VOID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  // Time base configuration
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
	TIM_SetCounter(TIM2, 0); 
	TIM_Cmd(TIM2, ENABLE); 
    g_u32EtrSynCount = 0;
    g_u32TotalEtrCount = 0;
}




