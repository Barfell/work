/**********************************************************************   
* Module: 				BEEP  
* Function: 			CONTROL  BEEP 
* Description: 			NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/09/11            SYAN                        	CREATE
**********************************************************************/ 
#include "beep.h" 

#define RCC_BEEP_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
#define BEEP_GPIO			GPIOE
#define BEEP_PIN			GPIO_Pin_12


VOID BeepInit(VOID)
{    	 
	RCC_BEEP_CONFIG();
	
	GPIO_Set(BEEP_GPIO, BEEP_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    BeepOn();
    
    DelayMs(500);
    
    BeepOff();
}


VOID BeepOn(VOID)
{
    GPIO_SetBits(BEEP_GPIO, BEEP_PIN);
}

VOID BeepOff(VOID)
{
    GPIO_ResetBits(BEEP_GPIO, BEEP_PIN);
}

