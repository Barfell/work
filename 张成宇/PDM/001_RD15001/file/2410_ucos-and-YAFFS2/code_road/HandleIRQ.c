#include "Uart.h"
#include "cs8900.h"
#include <stdio.h>
#include "Shell.h"
#include "lwip_bsp.h"

void HandleUartInt()
{
	unsigned long sub_src_pnd = *(volatile unsigned *)0x4a000018;
	*(volatile unsigned *)0x4a000018 = 0x000007ff; /*clear all the sub src pnd*/	
	
	if (1 == (sub_src_pnd & 0x01 )) /*sub src pnd*/
	{
		char rx_data = ReadChar();
		SendToShell(&rx_data, 1);
	}
}

void HandleEInt9()
{
	unsigned short isq = ReadCS8900Reg(0x0120);

	/*printf("eth irq is 0x%x\n", isq);*/

	if (0x04 == (isq & 0x0f))
	{
		RecvEthPkt();
	}
	
	*(volatile unsigned *)0x560000a8 = 0xffffffff; /*clear external int pnd*/
}

void HandleTimer4()
{
	OSTimeTick();
}

void HandleIRQ(void)
{
	unsigned char offset = *(volatile unsigned char *)0x4a000014; /*int Offset*/

	switch (offset)
	{
	case 28:
		HandleUartInt();
		break;
	case 14:
		HandleTimer4();
		break;
	case 5:
		HandleEInt9();
		break;
	default:
		break;
	}

	*(volatile unsigned *)0x4a000000 = (1 << offset); /*clear src pnd*/
	*(volatile unsigned *)0x4a000010 = (1 << offset); /*clear int pnd*/
}


