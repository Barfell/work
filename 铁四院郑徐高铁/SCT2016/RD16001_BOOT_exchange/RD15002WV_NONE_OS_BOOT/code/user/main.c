#include  <includes.h>


void AppProc(void)
{
	U8 szData[4] = {0}; 
		
	FlashReadSTM32(UPDATE_FLAG_ADDRESS, 4, szData);//����UPDATE_FLAG_ADDRESS��������־
	
	if((szData[0] == 0xAA) && (szData[1] == 0x55) && (szData[2] == 0xAA) && (szData[3] == 0x55))//�������� 
	{
		DtuBoot();
	}
	UartBoot();
}





int main(void)
{
	SetClock();//���ø���CPUʱ��
	OsInit();
	bsp_io_init();//IO��
	SW_12V(1);//��Դ
	SW_5V(1);//������Դ�����ڼ��ز�
	
	UartInit(USART1);
	UartInit(USART2);
	

	while(1)
	{
		AppProc();
	}
}


