#include "device.h"
#include "test.h"
//component
#include "exfuns.h"
#include "usbh_usr.h" 
#include "fontupd.h"
#include "ff.h"
#include "fattester.h"
//app
#include "app_usb.h"


STATIC VOID BoardInit(VOID)
{
	PwcInit();
	KeyInit();
	BeepInit();
	LedInit();
    FSMC_NAND_Init();
    NAND_Reset();
    StartUSB();
    CommInit();
	EtrSynInit();
	SST25VF0_Init();
	

	
//    uart1_init(115200, 128, 256);//imu
//    uart2_init(115200, 128, 2048);//mile
//	uart4_init(115200, 128, 128);

	
}

INT main(VOID)
{

    OsInit();
    BoardInit();
//	TestUsart();
//	TestUsartSend();
//	TestUsbhost();
//	TestBeepProc();
//	TestEtrSynProc();
//	TestNandflash();
//	TestSST25VF0();
//	TestSST25VF0_Storage();	
//	TestLedProc();
//	TestPwcProc();
	
//	TestStim300Proc(); 
	TestStim300StorageProc();

	
	

	
//	TestCommProc();
//	TestCanProc();
    return 0;
}
