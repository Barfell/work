#include "kernal.h"
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
    FSMC_NAND_Init();
    NAND_Reset();
    StartUSB();
    CommInit();//与显示板的通信串口(双CPU)
	SynInit();//定时器发生一个固定频率的信号
	BeepInit();//蜂鸣器初始化
    uart1_init(115200, 128, 256);//imu
    uart2_init(115200, 128, 2048);//gps
//    uart3_init(115200, 256, 256);//双cpu
	uart4_init(115200, 128, 128);//里程规矩

	
}

INT main(VOID)
{

    OsInit();//时钟，systick等等初始化
    BoardInit();//外设的初始化。nand、usb、串口。		
//	TestImu();
//	TestGps();
//	TestUsart();
//	TestUsartSend();
//	TestSynProc();
//	TestCommProc();
//	TestCommGuiProc();
//	TestCommKeyProc();
//	TestUsbhost();
//	TestSdProc();
//	TestNandflash();
//	TestBeepProc();
	TestInsGpsOtherNandStorage();
//	TestCanProc();
    return 0;
}
