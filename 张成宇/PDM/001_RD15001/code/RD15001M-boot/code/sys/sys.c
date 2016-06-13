#include "sys.h"  

#define     TICKMSUNIT    1000   
#define     TICKUSUNIT    10

STATIC volatile U32 g_u32TickCount = 0;
STATIC volatile U32 g_u32MicroSecondOfWeek = 0;//1ms计数
STATIC volatile U32 g_u32TenMicroSecondOfWeek = 0;//10ms计数
STATIC volatile U32 g_u32SecondOfWeek = 0;
STATIC RCC_ClocksTypeDef RCC_Clocks;

EXTERN VOID HandleOtherDataProc(VOID);

VOID SysTick_Handler(VOID)
{
    g_u32TickCount ++; 
    if(g_u32TickCount%10 == 0)
    {
        g_u32MicroSecondOfWeek++;
    }
    if(g_u32TickCount%100 == 0)
    {
        g_u32TenMicroSecondOfWeek++;
        
        if(g_u32TenMicroSecondOfWeek%100 == 0)
        {
            g_u32SecondOfWeek++;
        }
    }
}

U32 GetTenMicroSecondOfWeek(VOID)
{
    return g_u32TenMicroSecondOfWeek;
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
    SysTick_Config(RCC_Clocks.HCLK_Frequency / (TICKMSUNIT*TICKUSUNIT));/* SysTick end of count event each 1/TICKMSUNIT*TICKUSUNIT = 0.1ms */
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
    
    while(((GetTickCount() - u32Tick)/TICKUSUNIT) < nTime);

}

VOID DelayUs(U32 nTime)
{ 
    volatile U32 u32Tick;
    
    u32Tick = GetTickCount();
    
    while((GetTickCount() - u32Tick) < nTime);

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



