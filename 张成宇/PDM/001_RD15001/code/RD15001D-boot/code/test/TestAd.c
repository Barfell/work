#include "board.h"

VOID TestAdcProc(VOID)
{
	U16 adcx;
    Adc_Init();
	printf("ADC TEST\r\n");
	
	while(1)
	{	

        Get_Adc_Average(ADC_CHANNEL, 20, &adcx);
        printf("adcx = %d\r\n", adcx);
        Get_Temprate(&adcx);
        printf("temp = %d\r\n", adcx);	
        Get_Adc(ADC_CHANNEL, &adcx);
        printf("adcx_once = %d\r\n", adcx); 
        
        DelayMs(300);

	}
}
