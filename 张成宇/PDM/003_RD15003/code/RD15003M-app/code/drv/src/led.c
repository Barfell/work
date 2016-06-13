/**********************************************************************   
* Module: 				KEY  
* Function: 			CONTROL  KEY 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "led.h" 

#define RCC_LED_CONFIG()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)
#define LED_SYS_GPIO			GPIOC
#define LED_SYS_PIN				GPIO_Pin_8
#define LED_DAT_GPIO			GPIOC
#define LED_DAT_PIN				GPIO_Pin_9
#define LED_PWR_GPIO			GPIOC
#define LED_PWR_PIN				GPIO_Pin_10

VOID LedInit(VOID)
{    	 
	RCC_LED_CONFIG();
	
	GPIO_Set(LED_SYS_GPIO, LED_SYS_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	GPIO_Set(LED_DAT_GPIO, LED_DAT_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	GPIO_Set(LED_PWR_GPIO, LED_PWR_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	SysLedOff();//yellow
	DatLedOff();//green
	PwrLedOn();//red
}



VOID SysLedOn(VOID)
{
    GPIO_SetBits(LED_SYS_GPIO, LED_SYS_PIN);
}

VOID SysLedOff(VOID)
{
    GPIO_ResetBits(LED_SYS_GPIO, LED_SYS_PIN);
}

VOID DatLedOn(VOID)
{
    GPIO_SetBits(LED_DAT_GPIO, LED_DAT_PIN);
}

VOID DatLedOff(VOID)
{
    GPIO_ResetBits(LED_DAT_GPIO, LED_DAT_PIN);
}

VOID PwrLedOn(VOID)
{
    GPIO_SetBits(LED_PWR_GPIO, LED_PWR_PIN);
}

VOID PwrLedOff(VOID)
{
    GPIO_ResetBits(LED_PWR_GPIO, LED_PWR_PIN);
}


