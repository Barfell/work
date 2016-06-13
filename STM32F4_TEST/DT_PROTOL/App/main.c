#include <stm32f4xx.h>
#include "PeriphInit.h"
#include <stdio.h>
#include <stdlib.h>
#include "DTprotocol.h"
int main(void)
{
	DTprotocolStructType *DTprotocoltest;
	char str123[]={"DT RD15001 CONF TIME 2016-01-14-13:46:12\r\n"};

	DTprotocoltest = malloc(sizeof(DTprotocolStructType));
    setckock();
	LedGPIOConfig();
	Usart1_Config();
	Nvic_Config();
	printf("okokokokokok\r\n");
	DTcmdExtract(str123,*DTprotocoltest);
	while(1)
	{
		//printf("okokokokokok\r\n");
	}
}
