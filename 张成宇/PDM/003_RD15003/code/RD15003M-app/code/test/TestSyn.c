#include "syn.h"


VOID TestEtrSynProc(VOID)
{
	U8 szData[20] = {0};
	U32 u32CurrentCount = 0, u32LastCount = 0;
	
    EtrSynInit();
	
	CpldOn();
	
    while(1)
    {
		u32CurrentCount = GetEtrSynCount();
		if(u32CurrentCount - u32LastCount > 1000)
		{
			sprintf((char *)szData, "%d", u32CurrentCount);

			printf((char *)szData); 
			
			u32LastCount = u32CurrentCount; 
		}

        
    }
       
}

