#include "kernal.h" 

#define     TICKMSUNIT    1000   

STATIC volatile U32 g_u32TickCount = 0;
STATIC volatile U32 g_u32SecondOfWeek = 0;
STATIC RCC_ClocksTypeDef RCC_Clocks;

EXTERN VOID HandleOtherDataProc(VOID);
EXTERN VOID IndicationStopThreadProc(VOID);
EXTERN VOID EtrSynRunThreadProc(VOID);
EXTERN VOID PwcThreadProc(VOID);
EXTERN VOID KeyThreadProc(VOID);
VOID SysTick_Handler(VOID)
{
    g_u32TickCount ++; 
    if(g_u32TickCount%1000 == 0)
    {
        g_u32SecondOfWeek++;
    }
	IndicationStopThreadProc();
    EtrSynRunThreadProc();
	PwcThreadProc();
	KeyThreadProc();
}


U32 GetSecondOfWeek(VOID)
{
    return g_u32SecondOfWeek;
}

VOID SetSecondOfWeek(U32 u32Cnt)
{
    g_u32SecondOfWeek = u32Cnt;
}


VOID OsInit(VOID)
{
    
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / (TICKMSUNIT));/* SysTick end of count event each 1/TICKMSUNIT*TICKUSUNIT = 0.1ms */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
       
    my_mem_init(SRAMIN);		//初始化内部内存池
    my_mem_init(SRAMEX);		//初始化外部内存池
    my_mem_init(SRAMCCM);		//初始化CCM内存池
    
}

U32 GetTickCount(VOID)
{
    return g_u32TickCount;
}


VOID DelayMs(U32 nTime)
{ 
    volatile U32 u32Tick;
    
    u32Tick = GetTickCount();
    
    while(((GetTickCount() - u32Tick)) < nTime);

}

//SOFT
VOID DelayMs_Sft(U32 nTime)
{ 
    DelayUs_Sft(nTime*1000);
}
//SOFT
VOID DelayUs_Sft(U32 nTime)
{ 
    U32 u32Tick;
    
    for(u32Tick = 0; u32Tick < nTime*42; u32Tick++);

}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm VOID WFI_SET(VOID)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm VOID INTX_DISABLE(VOID)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm VOID INTX_ENABLE(VOID)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
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
    while(1)
    {
        printf("error code = %x \r\n", u32ErrCode);
        DelayMs(1000);
    }  
    
}
