/**********************************************************************   
* Module: 				KEY CONTROL  
* Function: 			CONTROL  KEY 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "key.h"
#include "beep.h"

#define RCC_KEY_CONFIG()				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)
#define KEY_FUNCTION_GPIO				GPIOB
#define KEY_FUNCTION_PIN				GPIO_Pin_2

#define READ_KEY_FUNCTION_STATE 		GPIO_ReadInputDataBit(KEY_FUNCTION_GPIO, KEY_FUNCTION_PIN)

STATIC BOOL g_bFunctionKeyPress = FALSE;

STATIC U16 g_u16KeyTimeCount;

STATIC BOOL g_bPressFunction = FALSE;

EXTERN BOOL g_bFunction;
EXTERN BOOL g_bBeepWork;
EXTERN U32 g_u32BeepCount;
VOID KeyThreadProc(VOID)
{
	if(g_bFunctionKeyPress == TRUE)
	{
		if(READ_KEY_FUNCTION_STATE == Bit_RESET) 
		{
			if(g_bPressFunction == FALSE)
			{
				BeepOn();
				g_bBeepWork = TRUE;
				g_u32BeepCount = GetTickCount();
				g_bPressFunction = TRUE;
			}
			
			g_u16KeyTimeCount++;
			
			if(g_u16KeyTimeCount > 2000)
			{
				if(g_bFunction == FALSE)
				{
					g_bFunction = TRUE;
					g_bFunctionKeyPress = FALSE;
					g_u16KeyTimeCount = 0; 
				}
				else
				{
					g_bFunction = FALSE;
				}
			}
			
		}
		else
		{
			g_u16KeyTimeCount = 0;
			g_bFunctionKeyPress = FALSE;
			g_bPressFunction = FALSE;
		}
		
	}
}


VOID KeyInit(VOID)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_KEY_CONFIG();
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_Set(KEY_FUNCTION_GPIO, KEY_FUNCTION_PIN, GPIO_Mode_IN, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);

// 中断线以及中断初始化配置   上升沿触发
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure); 

}


VOID EXTI2_IRQHandler(VOID)//功能键
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		if(READ_KEY_FUNCTION_STATE == Bit_RESET)
		{
			g_bFunctionKeyPress = TRUE;
		}
		EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE上的中断标志位  
		
	}
	
}


