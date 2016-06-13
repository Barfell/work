/**********************************************************************   
* Module: 		LED  
* Function: 	CONTROL  LED 
* Description: 	NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/03/16            SYAN                        	CREATE
**********************************************************************/ 
#include "led.h" 

#define RCC_LED_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)
#define LED_GPIO			GPIOC
#define LED_PIN				GPIO_Pin_5


VOID Led_Init(VOID)
{    	 
	RCC_LED_CONFIG();
	
	GPIO_Set(LED_GPIO, LED_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);

	GPIO_ResetBits(LED_GPIO, LED_PIN);
}



VOID Led_On(VOID)
{
    GPIO_SetBits(LED_GPIO, LED_PIN);
}

VOID Led_Off(VOID)
{
    GPIO_ResetBits(LED_GPIO, LED_PIN);
}


