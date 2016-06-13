#include "stm32f4xx.h"
#include <stdio.h>
void setckock(void);

void Usart1_Config(void);

void LedGPIOConfig(void);

void OutPutGPIOConfig(void);

void Time1_Config(void);

void Time2_Config(void);	   

//freq最大为84000000，最小为1300
void OutPutFreqSet(unsigned int freq);

void Nvic_Config(void);


