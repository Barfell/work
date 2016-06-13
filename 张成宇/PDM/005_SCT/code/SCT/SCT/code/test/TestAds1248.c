#include "ads1248.h" 
#include "spi.h" 
#include "tsa5017.h"



VOID TestAds1248(VOID)
{
	float PT100Res;
//	U16 u16Length;
//	U8 szData[50];
	U8 u8ADS_MUX0;
	double PT100TempValue;
	u8 u8Channel = 1;
	SPI_InitTypeDef Spi_InitStruct;		
	SpiCreate(ADS1248_SPI, &Spi_InitStruct, FALSE, FALSE);	
	SpiOpen(ADS1248_SPI);	
	Tsa5017Init();	
	ADS1248_Init();

	while(1)
	{
		for(u8Channel = 1; u8Channel < 5; u8Channel++)
		{
			PT100TempProcess(u8Channel, &PT100Res, &u8ADS_MUX0, &PT100TempValue);
			printf("ADS_MUX0:%d    ",u8ADS_MUX0);
			printf("Channel:%2d  PT100Temp :%.2f  PT100Res:%f\r\n",u8Channel, PT100TempValue, PT100Res);
		}

		DelayMs(1000);
	}
	
}

