#include "key.h"
#include "display.h" 
#include "GUI.h"
#include "comm.h"
#include "syn.h"
#include "test.h"
#include "usart.h"
#include "kernal.h"    
#include "test.h"
#include "SST25VF0.h" 
#include "usart.h"
extern const GUI_FONT GUI_FontHZ12;

/************/
u16 RXCount = 0;
u8 RXBuf[512];
u8 Write[256];
u8 RXfinish = 0;
u8 RXfinish2 = 0;
u32 WRADDR = 0;
/************/
VOID TestFont(VOID)
{   
    SST25VF0_Init();
	ExternFlash_Init();
//    ExternFlashChipErase();
    while(1)
	{
        printf("werty \r\n");
        DelayMs(1000);
        GUI_SetFont(&GUI_FontHZ12);       
        GUI_DispStringAt("啊阿埃挨哎唉哀",0,0);
        GUI_DispStringAt("自定义",0,15);        
        GUI_DispStringAt("2015.07.28",0,30);
        GUI_DispStringAt("深圳大铁",0,45); 
        GUI_DispStringAt("惯导小车",0,60);           
    }
}

    

