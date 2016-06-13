#include "beep.h"

VOID TestBeepProc(VOID)
{
    BeepInit();

    while(1)
    {
        //printf("us tick = %d \r\n", GetTickCount());
        BeepOn();
        DelayMs_Sft(1000);
        //printf("us tick = %d \r\n", GetTickCount());
        BeepOff();
        DelayMs_Sft(1000);
        
    }
       
}


