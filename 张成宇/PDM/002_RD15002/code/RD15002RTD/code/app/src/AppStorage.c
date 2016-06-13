#include "AppStorage.h" 
#include "SST25VF064C.h" 
#include "ads1248.h" 
#include "spi.h" 
#include "tsa5017.h"
#include "am2305.h"
#include "Serial.h"
#include "Adc.h" 
#include "Dtu.h" 
STATIC VOID GetHumidityTemperature(U8 *pBuf, U16 *pLength)
{
	float Temperature,Humidity;
	U8 szAM2305_Data[5];
	U8 u8AM2305_Check;
	AM2305_Run();
	GetAm2305Data(szAM2305_Data);
	u8AM2305_Check = szAM2305_Data[0] + szAM2305_Data[1] + szAM2305_Data[2] + szAM2305_Data[3];
	if(u8AM2305_Check == szAM2305_Data[4])
	{					
		Humidity = (szAM2305_Data[0]*256 + szAM2305_Data[1])/10.0;
		Temperature = (szAM2305_Data[2]*256 + szAM2305_Data[3])/10.0;
		sprintf((char *)pBuf,"#%3.2f#%3.2f",Humidity,Temperature);
		UsartSend(USART1, pBuf, 14);		 
	}
	else
	{
		Humidity = 0;
		Temperature = 0;
		sprintf((char *)pBuf,"#%3.2f#%3.2f",Humidity,Temperature);
		UsartSend(USART1, pBuf, 14);
	}
	memcpy(pBuf, pBuf, 14);
	*pLength = 14;
	
}
STATIC VOID GetPowerVoltage(U8 *pBuf, U16 *pLength)
{
	U16 u16Value;
	double dValue;
	u16Value = GetAdc(ADC_CHANNEL);
	dValue = (u16Value/4096.0)*3.298;
	sprintf((char *)pBuf,"#%1.6f",dValue);
	UsartSend(USART1, pBuf, 8);
	*pLength = 8;
}
STATIC VOID GetTemperature(U8 *pBuf, U16 *pLength)
{
	double PT100TempValue;
	float PT100Res;
	U8 u8ADS_MUX0;
	u8 u8Channel = 1;
	for(u8Channel = 1; u8Channel < 5; u8Channel++)
	{
		PT100TempProcess(u8Channel, &PT100Res, &u8ADS_MUX0, &PT100TempValue);
		sprintf((char *)pBuf,"#%d_%f_%f",u8Channel, PT100Res, PT100TempValue);
	}
}

VOID DataStorage(VOID)
{

	U32 u32Tick;
	U16 u16Offset = 0;
	U16 u16Length;
	U8 szData[50];

//////////////////////	
	USART_InitTypeDef Usart_InitStruct;
	UartInit(&Usart_InitStruct, 57600);
	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	UartOpen(USART2);

//////////////////////
	SPI_InitTypeDef Spi_InitStruct;	
	SpiCreate(ADS1248_SPI, &Spi_InitStruct, FALSE, FALSE);	
	SpiOpen(ADS1248_SPI);	
	Tsa5017Init();	
	ADS1248_Init();
//////////////////////
	AM2305_Init();
//////////////////////
	AdcInit();
//////////////////////	
	SST25VF0_Init();
	ExternFlash_Init();
//////////////////////
	DtuInit();
	
//////////////////////
	u32Tick = GetTickCount();
	while(1)
	{
		if((GetTickCount() - u32Tick) > 3000)
		{
			u32Tick = GetTickCount();
			u16Offset = 0;
			GetHumidityTemperature(szData + u16Offset, &u16Length);
			u16Offset = u16Length + u16Offset;
			GetPowerVoltage(szData + u16Offset, &u16Length);
			u16Offset = u16Length + u16Offset;
			GetTemperature(szData + u16Offset, &u16Length);
			u16Offset = u16Offset + u16Length;
			UsartSend(USART1, szData, u16Offset);
		}
	}
	

	
	
	
}
