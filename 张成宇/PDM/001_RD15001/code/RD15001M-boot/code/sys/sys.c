#include "sys.h"  

#define     TICKMSUNIT    1000   
#define     TICKUSUNIT    10

STATIC volatile U32 g_u32TickCount = 0;
STATIC volatile U32 g_u32MicroSecondOfWeek = 0;//1ms����
STATIC volatile U32 g_u32TenMicroSecondOfWeek = 0;//10ms����
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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
       
    my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
    my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
    
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



