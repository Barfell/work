#include "board.h"
#include "iap.h"
extern iapfun jump2app; 
STATIC VOID BoardInit(VOID)
{
	uart2_init(115200, 256, 2060);

}


VOID RCC_Configuration(VOID)
{
	RCC_DeInit();//将外设 RCC寄存器重设为缺省值

	RCC_HSICmd(ENABLE);//使能HSI  
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)//等待HSI使能成功
	{
	}

	if(1)
	{
		//FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//FLASH_SetLatency(FLASH_Latency_2);

		RCC_HCLKConfig(RCC_SYSCLK_Div1);   
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);

		//设置 PLL 时钟源及倍频系数
		RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 2, 7);                
		//使能或者失能 PLL,这个参数可以取：ENABLE或者DISABLE
		RCC_PLLCmd(ENABLE);//如果PLL被用于系统时钟,那么它不能被失能
		//等待指定的 RCC 标志位设置成功 等待PLL初始化成功
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		//设置系统时钟（SYSCLK） 设置PLL为系统时钟源
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
		//等待PLL成功用作于系统时钟的时钟源
		//  0x00：HSI 作为系统时钟 
		//  0x04：HSE作为系统时钟 
		//  0x08：PLL作为系统时钟  
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}

INT main(VOID)
{
//	RCC_Configuration();
    OsInit();
    BoardInit();

    TestBoot();
 
    return 0;
}

