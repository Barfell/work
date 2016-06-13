/**********************************************************************   
* Module: 				SYNCHRONIZATION  
* Function: 			CONTROL  SYN 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "syn.h" 

#define CPLD_GPIO			GPIOE
#define CPLD_PIN			GPIO_Pin_2

STATIC volatile U32 g_u32EtrSynCount = 0, g_u32TotalEtrCount = 0;

VOID EtrSynRunThreadProc(VOID)
{
    if(TIM_GetCounter(TIM4) >= 0xEA60)
    {
        TIM_SetCounter(TIM4, TIM_GetCounter(TIM4) - 0xEA60);
        g_u32EtrSynCount = g_u32EtrSynCount + 0xEA60;	
    }  
}

U32 GetEtrSynCount(VOID)
{
     g_u32TotalEtrCount = g_u32EtrSynCount + TIM_GetCounter(TIM4);
     return g_u32TotalEtrCount;
}

VOID SetEtrSynCount(U32 u32Value)
{
     g_u32TotalEtrCount = u32Value;
}

VOID EtrSynInit(VOID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_TIM4);
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  // Time base configuration
	TIM_ETRClockMode2Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
	TIM_SetCounter(TIM4, 0); 
	TIM_Cmd(TIM4, ENABLE); 
    g_u32EtrSynCount = 0;
    g_u32TotalEtrCount = 0;
	
	GPIO_Set(CPLD_GPIO, CPLD_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	CpldOff();
}

VOID CpldOn(VOID)
{
    GPIO_ResetBits(CPLD_GPIO, CPLD_PIN);
}

VOID CpldOff(VOID)
{
    GPIO_SetBits(CPLD_GPIO, CPLD_PIN);
}


