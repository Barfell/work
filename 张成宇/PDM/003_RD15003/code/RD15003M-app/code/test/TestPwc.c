#include "pwc.h"
#include "led.h"

EXTERN BOOL g_bKeyPress;

VOID TestPwcProc(VOID)
{
	S32 s32Count;
	U32 u32Count;

	while(1)
	{
		u32Count = GetTickCount();
		if(g_bKeyPress == TRUE)
		{
			while(READ_PWC_STATE == Bit_SET) 
			{
				s32Count = GetTickCount() - u32Count;
				
				if(s32Count > 2000)
				{
					PwrOff();
					PwrLedOff();
				}
				
			}
			g_bKeyPress = FALSE;
		}
	}
}

