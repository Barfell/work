#include "Led.h" 

#define RCC_LED_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)
#define LED_GPIO			GPIOC
#define LED_PIN				GPIO_Pin_13


VOID LedInit(VOID)
{    	 
	RCC_LED_CONFIG();
	
	GPIO_Set(LED_GPIO, LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

	GPIO_ResetBits(LED_GPIO, LED_PIN);
}



VOID LedOff(VOID)
{
    GPIO_ResetBits(LED_GPIO, LED_PIN);
}

VOID LedOn(VOID)
{
    GPIO_SetBits(LED_GPIO, LED_PIN);
}


