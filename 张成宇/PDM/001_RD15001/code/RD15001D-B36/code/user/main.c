#include "device.h"
#include "test.h"
#include "GUI.h"

STATIC VOID BoardInit(VOID)
{
	KeyInit();
	CommInit();//Í¨ÐÅ¿Ú³õÊ¼»¯£¬ÓÃÓÚ¸ú´æ´¢°åÍ¨ÐÅ
	Adc_Init();
	MileageInit();
	LCDDrvInit();
	SynInit();
	CpldInit();
	SST25VF0_Init();
	ExternFlash_Init();
	uart1_init(115200, 256, 256);//RFIDå£¿
//	uart2_init(115200, 256, 256);//Ë«CPUÍ¨ÐÅµÄ´®¿Ú£¬¶ÔÓ¦M°åµÄuart3
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

