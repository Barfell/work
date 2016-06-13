#include  <includes.h>


void AppProc(void)
{
	U8 szData[4] = {0}; 
		
	FlashReadSTM32(UPDATE_FLAG_ADDRESS, 4, szData);//读出UPDATE_FLAG_ADDRESS的升级标志
	
	if((szData[0] == 0xAA) && (szData[1] == 0x55) && (szData[2] == 0xAA) && (szData[3] == 0x55))//网络升级 
	{
		DtuBoot();
	}
	UartBoot();
}





int main(void)
{
	SetClock();//配置各级CPU时钟
	OsInit();
	bsp_io_init();//IO口
	SW_12V(1);//电源
	SW_5V(1);//正负电源，用于检测回波
	
	UartInit(USART1);
	UartInit(USART2);
	

	while(1)
	{
		AppProc();
	}
}


