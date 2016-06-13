#include "key.h"

#define READ_KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)	
#define READ_KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8) 
#define READ_KEY3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)	
#define READ_KEY4 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10) 

STATIC U8 g_u8KeyNumbuer = KEY_INVALID;//按键编号

VOID KeyInit(VOID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

// 中断线以及中断初始化配置   上升沿触发
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7);
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);
    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);
    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);
    EXTI_InitStructure.EXTI_Line = EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;               
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;                 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure); 
	
	
}

VOID EXTI9_5_IRQHandler(VOID)
{
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE上的中断标志位  
		KeyScan();		
	}
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{				 
		EXTI_ClearITPendingBit(EXTI_Line8); //清除LINE上的中断标志位
		KeyScan();		
	}
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{				 
		EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE上的中断标志位
		KeyScan();		
	}
}
EXTERN BOOL g_bSart;
VOID KeyScan(VOID)
{
	U8 u8Count = 0;
	U8 u8KeyValue[5] = {KEY_INVALID};
    if(g_bSart == FALSE)
    {
        DelayMs_Sft(5);
    
        for(u8Count = 0; u8Count < 5; u8Count++)
        {
            if(Bit_SET == READ_KEY1)
            {
                SetKeyNumber(KEY_1);
            }
            else if(Bit_SET == READ_KEY2)
            {
                SetKeyNumber(KEY_2);
            }
            else if(Bit_SET == READ_KEY3)
            {
                SetKeyNumber(KEY_3);
            }
            else if(Bit_SET == READ_KEY4)
            {
                SetKeyNumber(KEY_4);
            }
            u8KeyValue[u8Count] = GetKeyNumber();
            DelayMs_Sft(2);
        }	
        if((u8KeyValue[0] == u8KeyValue[1]) && (u8KeyValue[2] == u8KeyValue[1]))
        {
            SetKeyNumber(u8KeyValue[0]);
        }
        else
        {
            SetKeyNumber(KEY_INVALID);
        }
    }
}

U8 GetKeyNumber(VOID)
{
	return g_u8KeyNumbuer;
}
VOID SetKeyNumber(U8 u8Type)
{
	g_u8KeyNumbuer = u8Type;
	
}
