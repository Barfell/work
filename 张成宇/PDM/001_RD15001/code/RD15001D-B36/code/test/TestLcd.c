#include "LcdDrv.h"
#include "GUI.h"

VOID TestLcdProc(VOID)
{
	
	GUI_Init();

	GUI_Clear();
	
	GUI_FillCircle(5,5,5);
	
	GUI_DispStringAt("what are you doing",12,2);
	
//	GUI_FillCircle(64,48,10);
	
	GUI_FillCircle(5,48,5);
	
	GUI_DispStringAt("to be or not to be",12,45); 

	while(1);
//	int i, j;
//		
//	LCDDrvClr();
//	
//	DisplayLogo();
	
//	for(i = 0; i< 128;i++)
//	{
//		for(j=0;j<96;j++)
//		{
//			My_SetPixelIndex(i, j, 1);
//		}
//	}
       
}
