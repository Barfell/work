#include "kernal.h" 
#include "includes.h"

STATIC volatile U32 g_u32TickCount = 0;
STATIC volatile U32 g_u32Second = 0;

CSysInfo cSysInfo = {0};

VOID SysTick_Handler(VOID)
{
    g_u32TickCount ++; 

    if(g_u32TickCount%1000 == 0)
    {
		g_u32Second++;
    }
}


U32 GetSecondOfWeek(VOID)
{
    return g_u32Second;
}

VOID SetSecondOfWeek(U32 u32Cnt)
{
    g_u32Second = u32Cnt;
}

STATIC VOID RCC_Configuration(VOID)
{
 
}

VOID OsInit(VOID)
{
	if (SysTick_Config(SystemCoreClock / 1000))	   //����ʹ��û��TimeDelay��ֵ��ʱ1us,���Ҫ��ʱ1ms����Ӧ�ĳ���1000�Ϳ�����
	{ 
		/* Capture error */ 
		while (1);
	} 
	
	cSysInfo.RTC_FLAG = TRUE;
}



U32 GetTickCount(VOID)
{
    return g_u32TickCount;
}


VOID DelayMs(U32 nTime)
{ 
	volatile U32 u32Tick;	
	u32Tick = nTime + g_u32TickCount;
	do
    {
		__nop();
		
    }while(g_u32TickCount < u32Tick);

}

//SOFT
VOID DelayMs_Sft(U32 nTime)
{ 
   
    DelayUs_Sft(nTime*1000);
}
//SOFT
VOID DelayUs_Sft(U32 nTime)
{ 
    U32 u32Cnt, u32Count;
    
	for(u32Count = 0; u32Count < nTime; u32Count++)
	{
		for(u32Cnt = 0; u32Cnt < 5; u32Cnt++);
	}

}

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm VOID WFI_SET(VOID)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm VOID INTX_DISABLE(VOID)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm VOID INTX_ENABLE(VOID)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm VOID MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}


VOID NMI_Handler(VOID)
{
}


VOID HardFault_Handler(VOID)
{
    /* Go to infinite loop when Hard Fault exception occurs */
	
	NVIC_SystemReset();
	
    while (1)
    {
    }
}


VOID MemManage_Handler(VOID)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

VOID BusFault_Handler(VOID)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}


VOID UsageFault_Handler(VOID)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

VOID SVC_Handler(VOID)
{
}

VOID DebugMon_Handler(VOID)
{
}

VOID PendSV_Handler(VOID)
{
}

VOID EnterException(U32 u32ErrCode)
{
	U8 u8Count = 0;
    while(u8Count < 100)
    {
        printf("error code = %x \r\n", u32ErrCode);
        DelayMs_Sft(1000);
		u8Count++;
    }  
    NVIC_SystemReset();
}
