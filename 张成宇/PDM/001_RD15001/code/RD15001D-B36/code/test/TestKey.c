#include "key.h"
#include "display.h" 
#include "GUI.h"
#include "comm.h"

VOID TestKeyProc(VOID)
{
	U8 u8KeyNumber;
//	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
//	pOldFont = GUI_SetFont(&GUI_Font16_ASCII);
	GUI_SetFont(&GUI_Font16_ASCII);
	
    while(1)
    {
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SendCommData(COMM_KEY);

			GUI_Clear();
			switch(u8KeyNumber)
			{
				case KEY_1:
					
					GUI_DispStringAt("key 1:Start", 0, LINE_1);
					break;
				case KEY_2:
					GUI_DispStringAt("key 2:Save", 0, LINE_2);
					break;
				case KEY_3:
					GUI_DispStringAt("key 3:Clear", 0, LINE_3);
					break;
				case KEY_4:
					GUI_DispStringAt("key 4:Stop", 0, LINE_4);
					break;
				default:
					break;
				
			}
			SetKeyNumber(KEY_INVALID);
						
		}
	
    }
//	GUI_SetFont(pOldFont);
       
}
