#include "ads1248.h" 
#include "spi.h" 
#include "tsa5017.h"
#include "ds18b20.h"


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

VOID TestAds1248andDs18b20(VOID)
{
	float PT100Res;
	short temperature;   
	U8 u8ADS_MUX0;
	double PT100TempValue;
	SPI_InitTypeDef Spi_InitStruct;		
	SpiCreate(ADS1248_SPI, &Spi_InitStruct, FALSE, FALSE);	
	SpiOpen(ADS1248_SPI);	
	Tsa5017Init();	
	ADS1248_Init();
	while(DS18B20_Init())	//DS18B20初始化	
	{
		printf("DS18B20 Init error\r\n");
	}
	DS18B20_Get_Temp();
	DS18B20_Get_Temp();
	DS18B20_Get_Temp();
	while(1)
	{
		PT100TempProcess(4, &PT100Res, &u8ADS_MUX0, &PT100TempValue);
		printf("Channel:%2d-PT100:%.2f##",4, PT100TempValue);
		PT100TempProcess(3, &PT100Res, &u8ADS_MUX0, &PT100TempValue);
		printf("Channel:%2d-PT100:%.2f##",3, PT100TempValue);
		printf("Ds18b20:");
		temperature = DS18B20_Get_Temp();	
		if(temperature<0)
			{		
				printf("-");								//显示负号
				temperature=-temperature;					//转为正数
			}
			else 
			{
				printf("+");
			}
			printf("%d.", temperature/10);
			printf("%d", temperature%10);

		DelayMs(1000);
	}
	
}
