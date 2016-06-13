#include "comm.h"

VOID TestCommProc(VOID)
{
	U8 u8First = 0, u8Second = 0;
	while(1)
	{
		DisplayPercentage(u8First, u8Second);
		u8Second++;
		if(u8Second == 10)
		{
			u8Second = 0;
			u8First++;
			if(u8First == 10)
			{
				u8First = 0;
			}
		}
		ReceiveCommData();
		DelayMs(100);
		
		if(GetKeyNumber() != KEY_INVALID)
		{
			DisplayInstruction(0, GetKeyNumber());
			SetKeyNumber(KEY_INVALID);
		}
		DelayMs(100);
	}
}


VOID TestCommGuiProc(VOID)
{
	U8 szData[3] = {0};
	U8 u8X = 0, u8Y = 0;
	while(1)
	{
		
		DisplayClear(0, 0, 10, 10, FALSE);
		sprintf((char *)szData, "what are you doing");
		DisplayString(u8X, u8Y, szData);

		u8X = u8X + 2;
		if(u8X == 128)
		{
			u8X = 0;
			u8Y = u8Y + 2;
			if(u8Y == 96)
			{
				u8Y = 0;
			}
		}
		
		DelayMs(300);
	}
}


VOID TestCommKeyProc(VOID)
{

	while(1)
	{
		ReceiveCommData();
		
		if(GetKeyNumber() != KEY_INVALID)
		{
			printf("key is %d", GetKeyNumber());
			SetKeyNumber(KEY_INVALID);
		}
	}
}

