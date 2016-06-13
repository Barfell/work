#include "syn.h"
#include "CPLD.h" 
#include "GUI.h"

VOID TestSynProc(VOID)
{
	U8 szData[20] = {0};
	
//	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
    SynInit();
	
	CpldOn();
	
//	pOldFont = GUI_SetFont(&GUI_FontD24x32);
    GUI_SetFont(&GUI_FontD24x32);

    while(1)
    {
		sprintf((char *)szData, "%d", GetSynCount());

		GUI_DispStringAt((char *)szData, 0, 0); 

        
    }
       
}


