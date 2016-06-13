#include  <includes.h>

PQueueInfo pUart3QueueInfo;

int main(void)
{
    char DEVICE_ID[50];
	SetClock();//���ø���CPUʱ��
	bsp_io_init();//IO��
	UsartConfig();//������������
	
	pUart3QueueInfo = malloc(sizeof(CQueueInfo));//�����ڴ�.���ڻ���
	memset(pUart3QueueInfo, 0, sizeof(CQueueInfo));
	
	printf("-----SCT15001-Version 0.0------\r\n          @Copyright SZDT Technology.\r\n");
	
	bsp_io_init();//IO��
	printf("Uart Init                 Ok.\r\n");
	printf("Control IO Init           Ok.\r\n");
	SW_12V(1);//��Դ
	SW_5V(1);//������Դ�����ڼ��ز�
	printf("Power Control IO Init     Ok.\r\n");
/*********************************************************/
	read_dev_id(DEVICE_ID);
	printf("CHIP ID: %s\r\n",DEVICE_ID);
	voltage_adc_init();//�ڲ���ѹ
	printf("Inner ADC Init            Ok.\r\n");
	printf("Inner ADC Value:          %f v\r\n",get_dev_voltage(get_adc_value()));
	rain_gpio();//����GPIO��ʼ��
	printf("RainCounter Init          Ok.\r\n");
	FreqModuleInit();//��Ƶ��ģ���ʼ��
	printf("FreqModule Init           Ok.\r\n");
	LTC2402Init();//�¶Ȳɼ���ʼ��
	printf("LTC2402 Init              Ok.\r\n");
	printf("RTC Configration......\r\n");
	RTC_Config(inner);
	printf("RTC Configed In Inner Clock Mode.\r\n");
	printf("Current Time:<-%s->\r\n",get_time2());
	printf("Board All Moudles Init Done.\r\n");
/********************************************************/
	GetFreq(1);//��ȡƵ��
	
	
	
	while(1)
	{
		AppMain();//�����д�������
	}
	
}


