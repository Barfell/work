#include "test.h"
#include "kernel.h"
#include "msp430f149_spi.h"


void testspi(void)
{
	u8 testspia = 0;
	u8 testspib = 0;
	u8 testspic = 0;
	SpiInit();
	while(1)
	{
		testspia = SpiWriteReadByte(0xab);
		delay_ms(200);
		testspib = SpiWriteReadByte(0xfe);
		delay_ms(200);
		testspic = SpiWriteReadByte(0xaa);
		delay_ms(200);
	}
}