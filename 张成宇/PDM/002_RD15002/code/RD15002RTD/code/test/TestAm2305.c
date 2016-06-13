#include "am2305.h"
#include "Serial.h"

VOID TestAm2305(VOID)
{
	float Temperature,Humidity;
//	U8 szData[50] = {0};
//	U16 u16Length;
	U8 szAM2305_Data[5] = {0};
	U8 u8AM2305_Check;

	AM2305_Init();
	
	USART_InitTypeDef Usart_InitStruct;
	UartInit(&Usart_InitStruct, 57600);
	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	UartOpen(USART2);
	
    while(1)
    {
        DelayMs(2000);
        if(AM2305_Run() == 0)
        {
    		GetAm2305Data(szAM2305_Data);
            u8AM2305_Check = szAM2305_Data[0] + szAM2305_Data[1] + szAM2305_Data[2] + szAM2305_Data[3];
            if(u8AM2305_Check == szAM2305_Data[4])
            {					
    //          printf("%c%c%c%c%c",szAM2305_Data[0],szAM2305_Data[1],szAM2305_Data[2],szAM2305_Data[3],szAM2305_Data[4]);//显示五个字节数据
                Humidity = (szAM2305_Data[0]*256 + szAM2305_Data[1])/10.0;
                Temperature = (szAM2305_Data[2]*256 + szAM2305_Data[3])/10.0;
    			printf("\r\nHumidity = %.1f\r\nTemperature = %.1f\r\n",Humidity,Temperature);
    //			sprintf((char *)szData, "\r\nHumidity = %.1f\r\nTemperature = %.1f\r\n",Humidity,Temperature);
    //			u16Length = 50;
    //			UsartSend(USART1, szData, u16Length);
    			
               
            }
            else 
            {
                printf("AM2305 Data Error\r\n");
            }
        }
        else
        {
            printf("AM2305 Data Error2\r\n");
        }
    }		
}


