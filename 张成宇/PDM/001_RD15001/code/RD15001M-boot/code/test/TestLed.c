#include "board.h"

VOID TestLedProc(VOID)
{
    Led_Init();

    while(1)
    {
        //printf("us tick = %d \r\n", GetTickCount());
        Led_On();
        DelayMs_Sft(1000);
        //printf("us tick = %d \r\n", GetTickCount());
        Led_Off();
        DelayMs_Sft(1000);
        
    }
       
}


