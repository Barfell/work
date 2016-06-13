/**********************************************************************   
* Module: 				POWER CONTROL  
* Function: 			CONTROL  POWER 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "pwc.h" 
#include "led.h"
#include "beep.h"


STATIC BOOL g_bPressPwc = FALSE;
STATIC U16 g_u16PwcTimeCount = 0;

BOOL g_bKeyPress = FALSE;

EXTERN BOOL g_bBeepWork;
EXTERN U32 g_u32BeepCount;

VOID PwcThreadProc(VOID)
{
	U8 u8Cnt;
	if(g_bKeyPress == TRUE)
	{
		if(READ_PWC_STATE == Bit_SET) 
		{
			if(g_bPressPwc == FALSE)
			{
				BeepOn();
				g_bBeepWork = TRUE;
				g_u32BeepCount = GetTickCount();
				g_bPressPwc = TRUE;
			}
				
			g_u16PwcTimeCount++;
			
			if(g_u16PwcTimeCount > 3000)
			{
				for(u8Cnt = 0; u8Cnt < 3; u8Cnt++)
				{
					BeepOn();
					DelayMs_Sft(50);
					BeepOff();
					DelayMs_Sft(50);
					
				}
				DatLedOff();
				SysLedOff();
				PwrLedOff();
				PwrOff();
				
				g_bKeyPress = FALSE;
			}
			
		}
		else
		{
			g_u16PwcTimeCount = 0;
			g_bKeyPress = FALSE;
			
			g_bPressPwc = FALSE;
		}
		
	}
}


VOID PwcInit(VOID)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_PWC_CONFIG();
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_Set(PWR_GPIO, PWR_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	GPIO_Set(KEY_GPIO, KEY_PIN, GPIO_Mode_IN, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);

// 中断线以及中断初始化配置   上升沿触发
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure); 
	
	
	PwrOn();

}


VOID PwrOn(VOID)
{
    GPIO_SetBits(PWR_GPIO, PWR_PIN);
}

VOID PwrOff(VOID)
{
    GPIO_ResetBits(PWR_GPIO, PWR_PIN);
}


VOID EXTI4_IRQHandler(VOID)//右键保存
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		if(READ_PWC_STATE == Bit_SET)
		{
			g_bKeyPress = TRUE;
		}
		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE上的中断标志位  
		
	}
	
}


