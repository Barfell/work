/**********************************************************************   
* Module: 		CPLD  
* Function: 	CONTROL  CPLD 
* Description: 	NONE
* LOG_DATE      		AUTHOR             				ACTION  
***********************************************************************  
* 2015/03/16            SYAN                        	CREATE
**********************************************************************/ 
#include "CPLD.h" 

#define RCC_CPLD_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)
#define CPLD_GPIO			GPIOC
#define CPLD_PIN			GPIO_Pin_7


VOID CpldInit(VOID)
{    	 
	RCC_CPLD_CONFIG();
	
	GPIO_Set(CPLD_GPIO, CPLD_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);

	CpldOff();
}



VOID CpldOn(VOID)
{
    GPIO_ResetBits(CPLD_GPIO, CPLD_PIN);
}

VOID CpldOff(VOID)
{
    GPIO_SetBits(CPLD_GPIO, CPLD_PIN);
}


