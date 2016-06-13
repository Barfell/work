#include "device.h"
#include "test.h"
#include "GUI.h"

STATIC VOID BoardInit(VOID)
{
	KeyInit();
	CommInit();//通信口初始化，用于跟存储板通信
	Adc_Init();
	MileageInit();
	LCDDrvInit();
	SynInit();
	CpldInit();
	SST25VF0_Init();
	ExternFlash_Init();
	uart1_init(115200, 256, 256);
//	uart2_init(115200, 256, 256);//双CPU通信的串口，对应M板的uart3
	uart3_init(115200, 256, 256);
}

INT main(VOID)
{

    OsInit();
	
    BoardInit();
	
	GUI_Init();

	GUI_Clear();
		
//	TestSST25VF0();
//	TestLcdProc();
//	TestMileageProc();
//	TestKeyProc();
//	TestKeyGuiProc();
//	TestBeepProc();
//	TestCommProc();
//	TestCommGuiProc();
//	TestFramProc();
//	TestUsart();
//	TestSynProc();
//	TestFrequency();
//	TestFont();
	TestGuiProc();


    return 0;
}

