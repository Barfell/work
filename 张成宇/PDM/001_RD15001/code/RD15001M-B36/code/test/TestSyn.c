#include "syn.h"


VOID TestSynProc(VOID)
{
	U8 szData[20] = {0};
	
    SynInit();
	
    while(1)
    {
		sprintf((char *)szData, "%d", GetSynCount());

		printf((char *)szData); 

        
    }
       
}


