/**
 * @file  msp430f149_uart.h
 * @author  wf
 * @version V1.0
 * @date  2015-11-20
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-20
 * +  file create
 */
#ifndef MSP430F149_UART_H
#define MSP430F149_UART_H
#include "i430type.h"

/*	UART0	UART1
Tx	P3.4	P3.6
Rx	P3.5	P3.7
 */

typedef enum
{
	UART_SouceClk_ACLK = 1,
	UART_SouceClk_SMCLK
}UART_SouceClkTypeDef;

typedef enum
{
	UART_0 = 1,
	UART_1
}UART_NumberTypeDef;

typedef enum
{
	UART_ACLKBaud_2400 = 1,
	UART_ACLKBaud_4800,
	UART_ACLKBaud_9600,
	UART_SMCLKBaud_2400,
	UART_SMCLKBaud_4800,
	UART_SMCLKBaud_9600,
	UART_SMCLKBaud_19200,
	UART_SMCLKBaud_38400,
	UART_SMCLKBaud_76800,
	UART_SMCLKBaud_115200
}UART_BaudTypeDef;

void UART_Init(UART_NumberTypeDef NumberTypeDef, UART_SouceClkTypeDef SouceClkTypeDef, UART_BaudTypeDef BaudTypeDef);
void UART_SendByte(UART_NumberTypeDef NumberTypeDef, u8 u8data);
void UART_SendStr(UART_NumberTypeDef NumberTypeDef, u8 *str, u16 u16length);
void PrintStr(u8 *s);

#endif
