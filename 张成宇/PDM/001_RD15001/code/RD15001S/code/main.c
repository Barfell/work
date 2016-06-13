#include <c8051f340.h>
#include <intrins.h>   
#include "stdio.h"
#include "Init.h"	 

void TestUart1(void);
void TestUart2(void);
void TestUartRfid(void);
void TestTemperature(void);
VOID TestCalcuate(VOID);
VOID TestRFID(VOID);

void main(void)
{
	Init_Device();		// Initializes hardware peripherals
	TestRFID();
}




 