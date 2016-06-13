#include "spi.h"
/***SPI1 GPIO Defined***/
#define SPI1_SPI                   SPI1
#define SPI1_GPIO_NSS              GPIOA
#define SPI1_GPIO_CLK              GPIOA
#define SPI1_GPIO_MISO             GPIOA
#define SPI1_GPIO_MOSI             GPIOA

#define SPI1_PIN_NSS               GPIO_Pin_4
#define SPI1_PIN_CLK               GPIO_Pin_5
#define SPI1_PIN_MISO              GPIO_Pin_6
#define SPI1_PIN_MOSI              GPIO_Pin_7

#define SPI1_NSS_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SPI1_CLK_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SPI1_MISO_GPIO_CLK         RCC_APB2Periph_GPIOA
#define SPI1_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOA

#define SPI1_CLK                   RCC_APB2Periph_SPI1
#define SPI1_AFIO_CLK              RCC_APB2Periph_AFIO
#define SPI1_IRQn                  SPI1_IRQn

/***SPI2 GPIO Defined***/
#define SPI2_SPI                   SPI2
#define SPI2_GPIO_NSS              GPIOB
#define SPI2_GPIO_CLK              GPIOB
#define SPI2_GPIO_MISO             GPIOB
#define SPI2_GPIO_MOSI             GPIOB

#define SPI2_PIN_NSS               GPIO_Pin_12
#define SPI2_PIN_CLK               GPIO_Pin_13
#define SPI2_PIN_MOSI              GPIO_Pin_15
#define SPI2_PIN_MISO              GPIO_Pin_14

#define SPI2_NSS_GPIO_CLK          RCC_APB2Periph_GPIOB
#define SPI2_CLK_GPIO_CLK          RCC_APB2Periph_GPIOB
#define SPI2_MISO_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SPI2_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOB

#define SPI2_CLK                   RCC_APB1Periph_SPI2
#define SPI2_AFIO_CLK              RCC_APB2Periph_AFIO
#define SPI2_IRQn                  SPI2_IRQn

VOID SpiCreate(SPI_TypeDef *pSPIx, SPI_InitTypeDef *pSPI_InitStruct,
                 BOOL EnableTxInt, BOOL EnableRxInt)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CSpiInfo xSpi = {0};
	CSpiInfo *p;
	p = &xSpi;

	p->pSPIx = pSPIx;
	p->pSPI_InitStruct = pSPI_InitStruct;
	p->SPI_EnableTxInt = EnableTxInt;
	p->SPI_EnableRxInt = EnableRxInt;

	if(pSPIx == SPI1)
	{ 
		//配置spi参数
		p->pSPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		p->pSPI_InitStruct->SPI_Mode = SPI_Mode_Master;
		p->pSPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
		p->pSPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
		p->pSPI_InitStruct->SPI_CPHA = SPI_CPHA_2Edge;
		p->pSPI_InitStruct->SPI_NSS = SPI_NSS_Soft;
		p->pSPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//SPI_BaudRatePrescaler_2;//36MHZ4分频就是6MHZ
		p->pSPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
		p->pSPI_InitStruct->SPI_CRCPolynomial = 7;		
		 //pin
		 p->SPI_PinTx = SPI1_PIN_MOSI;
		 p->SPI_PinRx = SPI1_PIN_MISO;
		 p->SPI_PinClk = SPI1_PIN_CLK;    
		 p->SPI_PinNss = SPI1_PIN_NSS;  
		 //clk gpio
		 p->SPI_ClkGpioClk = SPI1_CLK_GPIO_CLK;
		 p->SPI_TxGpioClk = SPI1_MOSI_GPIO_CLK;
		 p->SPI_RxGpioClk = SPI1_MISO_GPIO_CLK;
		 p->SPI_NssGpioClk = SPI1_NSS_GPIO_CLK;     
		 //device clock
		 p->SPI_Clk = SPI1_CLK;
		 p->SPI_APB2PeriphAfioClk = SPI1_AFIO_CLK;     
		 //中断
		 p->SPI_IRQChannel = SPI1_IRQn;
		 //gpio
		 p->SPI_PinRxGpio = SPI1_GPIO_MISO;
		 p->SPI_PinTxGpio = SPI1_GPIO_MOSI;
		 p->SPI_PinClkGpio = SPI1_GPIO_CLK;
		 p->SPI_PinNssGpio = SPI1_GPIO_NSS;  
		  
		 if((p->SPI_PinTx == GPIO_Pin_4) && (p->SPI_PinRx == GPIO_Pin_5) && 
			(p->SPI_PinClk == GPIO_Pin_3) && (p->SPI_PinNss == GPIO_Pin_15))
		{
			GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);
		}
		

	}
	else if(pSPIx == SPI2)
	{
		//配置spi参数
		p->pSPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		p->pSPI_InitStruct->SPI_Mode = SPI_Mode_Master;
		p->pSPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
		p->pSPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
		p->pSPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
		p->pSPI_InitStruct->SPI_NSS = SPI_NSS_Soft;
		p->pSPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//36MHZ4分频就是6MHZ
		p->pSPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
		p->pSPI_InitStruct->SPI_CRCPolynomial = 7;
		//pin
		p->SPI_PinTx = SPI2_PIN_MOSI;
		p->SPI_PinRx = SPI2_PIN_MISO;
		p->SPI_PinClk = SPI2_PIN_CLK;    
		p->SPI_PinNss = SPI2_PIN_NSS;  
		//clk gpio
		p->SPI_ClkGpioClk = SPI2_CLK_GPIO_CLK;
		p->SPI_TxGpioClk = SPI2_MOSI_GPIO_CLK;
		p->SPI_RxGpioClk = SPI2_MISO_GPIO_CLK;
		p->SPI_NssGpioClk = SPI2_NSS_GPIO_CLK;     
		//device clock
		p->SPI_Clk = SPI2_CLK;
		//中断
		p->SPI_IRQChannel = SPI2_IRQn;
		//gpio
		p->SPI_PinRxGpio = SPI2_GPIO_MISO;
		p->SPI_PinTxGpio = SPI2_GPIO_MOSI;
		p->SPI_PinClkGpio = SPI2_GPIO_CLK;
		p->SPI_PinNssGpio = SPI2_GPIO_NSS; 

	}

	RCC_APB2PeriphClockCmd(p->SPI_ClkGpioClk | p->SPI_TxGpioClk | p->SPI_RxGpioClk | p->SPI_NssGpioClk, ENABLE);
	if(pSPIx == SPI1)
	{
		RCC_APB2PeriphClockCmd(p->SPI_Clk, ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(p->SPI_Clk, ENABLE);
	}
	//rcc must be set first,before operate corresponding peripheral (usart register etc).
	/***Configure spi Clk as alternate function push-pull***/
	GPIO_InitStructure.GPIO_Pin = p->SPI_PinClk;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(p->SPI_PinClkGpio, &GPIO_InitStructure);
	/***Configure spi Tx as alternate function push-pull***/
	GPIO_InitStructure.GPIO_Pin = p->SPI_PinTx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(p->SPI_PinTxGpio, &GPIO_InitStructure);
	/***Configure spi Rx as alternate function push-pull***/
	GPIO_InitStructure.GPIO_Pin = p->SPI_PinRx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(p->SPI_PinRxGpio, &GPIO_InitStructure);
	/***Configure spi NSS as output push-pull***/
	GPIO_InitStructure.GPIO_Pin =  p->SPI_PinNss;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(p->SPI_PinNssGpio, &GPIO_InitStructure);

	/***Configure the spix***/
	SPI_Init(p->pSPIx, p->pSPI_InitStruct);

	/***Enable the spi Interrupt***/
	NVIC_InitStructure.NVIC_IRQChannel = p->SPI_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	if(EnableTxInt)
	{
		SPI_I2S_ITConfig(p->pSPIx, SPI_I2S_IT_TXE, ENABLE);
	}
	else
	{
		SPI_I2S_ITConfig(p->pSPIx, SPI_I2S_IT_TXE, DISABLE);
	}

	if(EnableRxInt)
	{
		SPI_I2S_ITConfig(p->pSPIx, SPI_I2S_IT_RXNE, ENABLE);
	}
	else
	{
		SPI_I2S_ITConfig(p->pSPIx, SPI_I2S_IT_RXNE, DISABLE);
	}

}

VOID SpiOpen(SPI_TypeDef *pSPIx)
{  
	SPI_CalculateCRC(pSPIx, DISABLE);//forbit crc
	/* Enable SPIx */
	SPI_Cmd(pSPIx, ENABLE);
}

VOID SpiClose(SPI_TypeDef *pSPIx)
{ 
	SPI_Cmd(pSPIx, DISABLE);
}

VOID SpiSetSpeed(SPI_TypeDef *pSPIx, U8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	pSPIx->CR1&=0XFFC7;
	pSPIx->CR1|=SPI_BaudRatePrescaler;	//设置SPI速度 
	SPI_Cmd(pSPIx, ENABLE); 

} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
U8 SpiReadWriteByte(SPI_TypeDef *pSPIx, U8 TxData)
{		
	U8 u8retry=0;	
	U8	u8Ret;
	while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
			
	}			  
	SPI_I2S_SendData(pSPIx, TxData); //通过外设SPIx发送一个数据
	u8retry=0;
	while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
	}
	
	u8Ret = SPI_I2S_ReceiveData(pSPIx);//返回通过SPIx最近接收的数据
SPI_ReadWriteByte_exit:	
	return  u8Ret;				    
}
