#include "device.h"

#include "test.h"


STATIC VOID BoardInit(VOID)
{
    uart1_init(115200, 128, 256);
//    uart2_init(115200, 128, 2048);
	
}

INT main(VOID)
{

    OsInit();
    BoardInit();
//	TestRtc();
//	TestUsart();
//	TestUsartSend();
//	TestSST25VF0();
//	TestSST25VF0_Storage();	
	TestLtc2402();
//	TestDtu();
	//TestFreqMeasure();
    return 0;
}


