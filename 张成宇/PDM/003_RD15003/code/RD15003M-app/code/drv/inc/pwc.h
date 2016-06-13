#ifndef __PWC_H
#define __PWC_H	 
#include "kernal.h"


#define RCC_PWC_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
#define PWR_GPIO			GPIOA
#define PWR_PIN				GPIO_Pin_5

#define KEY_GPIO			GPIOA
#define KEY_PIN				GPIO_Pin_4

#define READ_PWC_STATE 		GPIO_ReadInputDataBit(KEY_GPIO, KEY_PIN)

VOID PwcInit(VOID);
VOID PwrOn(VOID);
VOID PwrOff(VOID);

#endif

















