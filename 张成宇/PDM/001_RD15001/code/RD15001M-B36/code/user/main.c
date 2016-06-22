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
    CommInit();//����ʾ���ͨ�Ŵ���(˫CPU)
	SynInit();//��ʱ������һ���̶�Ƶ�ʵ��ź�
	BeepInit();//��������ʼ��
    uart1_init(115200, 128, 256);//imu
    uart2_init(115200, 128, 2048);//gps
//    uart3_init(115200, 256, 256);//˫cpu
	uart4_init(115200, 128, 128);//��̹��

	
}

INT main(VOID)
{

    OsInit();//ʱ�ӣ�systick�ȵȳ�ʼ��
    BoardInit();//����ĳ�ʼ����nand��usb�����ڡ�		
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
