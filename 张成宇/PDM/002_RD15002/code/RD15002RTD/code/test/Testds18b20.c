#include "ds18b20.h"
#include "Serial.h"

VOID TestDs18b20(VOID)
{
	U32 u32Tick;
	    
	short temperature;   
	
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		printf("DS18B20 Init error\r\n");
	}
	DS18B20_Get_Temp();
	DS18B20_Get_Temp();
	DS18B20_Get_Temp();
	u32Tick = GetTickCount();
	
	while(1)
	{	    	    
 		if((GetTickCount() - u32Tick) > 1000)
		{									  
			temperature = DS18B20_Get_Temp();	
			if(temperature<0)
			{		
				printf("-");								//��ʾ����
				temperature=-temperature;					//תΪ����
			}
			else 
			{
				printf("+");
			}
			printf("%d.", temperature/10);
			printf("%d", temperature%10);
			
			u32Tick = GetTickCount();
	   
		}				   
	 	
	}
}


