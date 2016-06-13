#include <includes.h>

//初始化ADC的引脚
void LTC2402Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	/*-----------------------LTC2402--------------------------*/
	//MISO ---->LTC2402--SDO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//SCK ---->LTC2402--SCK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//CS ---->LTC2402--CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 0x00;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
	SPI_InitStructure.SPI_FirstBit =  SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
	
}
//读出数据
unsigned int LTC2402Read(void)
{
	unsigned short DATL,DATH;
	DATH = SPI_I2S_ReceiveData(SPI1);//高16位
	DATL = SPI_I2S_ReceiveData(SPI1);//低16位
	return ( (unsigned int)DATH << 16 | (unsigned int)DATL );
}
//转换的状态
//1:done
//0:not yet
unsigned char ConversionSatue(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
		{return 1;}
	else
		{return 0;}
}
//进行一次ADC值的获取，得出的值是转换的最终结果
unsigned int GetLTC2402Value(void)
{
	OS_ERR		err;
	unsigned int Adcvalue = 0;
	unsigned char TimeOver = 0;
	LTC2402_CS_LOW;
	while(ConversionSatue() == 0)
		{
			OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_DLY,&err);
			TimeOver++;
			if(TimeOver ==150)
				{TimeOver = 0;return 0;}
		}
	Adcvalue = LTC2402Read();
	LTC2402_CS_HIGH;
	return Adcvalue;
}



