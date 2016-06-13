#include "other.h"

VOID EnterException(U32 u32ErrCode)
{
    while(1)
    {
        printf("error code = %x \r\n", u32ErrCode);
        DelayMs(1000);
    }  
    
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
