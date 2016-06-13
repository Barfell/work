#include  <includes.h>

PQueueInfo pUart3QueueInfo;

int main(void)
{
    char DEVICE_ID[50];
	SetClock();//配置各级CPU时钟
	bsp_io_init();//IO口
	UsartConfig();//串口设置配置
	
	pUart3QueueInfo = malloc(sizeof(CQueueInfo));//申请内存.串口缓冲
	memset(pUart3QueueInfo, 0, sizeof(CQueueInfo));
	
	printf("-----SCT15001-Version 0.0------\r\n          @Copyright SZDT Technology.\r\n");
	
	bsp_io_init();//IO口
	printf("Uart Init                 Ok.\r\n");
	printf("Control IO Init           Ok.\r\n");
	SW_12V(1);//电源
	SW_5V(1);//正负电源，用于检测回波
	printf("Power Control IO Init     Ok.\r\n");
/*********************************************************/
	read_dev_id(DEVICE_ID);
	printf("CHIP ID: %s\r\n",DEVICE_ID);
	voltage_adc_init();//内部电压
	printf("Inner ADC Init            Ok.\r\n");
	printf("Inner ADC Value:          %f v\r\n",get_dev_voltage(get_adc_value()));
	rain_gpio();//雨量GPIO初始化
	printf("RainCounter Init          Ok.\r\n");
	FreqModuleInit();//测频率模块初始化
	printf("FreqModule Init           Ok.\r\n");
	LTC2402Init();//温度采集初始化
	printf("LTC2402 Init              Ok.\r\n");
	printf("RTC Configration......\r\n");
	RTC_Config(inner);
	printf("RTC Configed In Inner Clock Mode.\r\n");
	printf("Current Time:<-%s->\r\n",get_time2());
	printf("Board All Moudles Init Done.\r\n");
/********************************************************/
	GetFreq(1);//获取频率
	
	
	
	while(1)
	{
		AppMain();//假如有串口数据
	}
	
}


