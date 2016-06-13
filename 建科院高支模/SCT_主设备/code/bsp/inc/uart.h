#ifndef MSP430F149_UART_H
#define MSP430F149_UART_H

#include "msp430.h"

#define UART0_CH_DTU       P1OUT &=  ~BIT1;P1OUT &=  ~BIT2
#define UART0_CH_RF        P1OUT |=   BIT1;P1OUT |=   BIT2

typedef enum
{
	UART_Clk_ACLK = 1,
	UART_Clk_SMCLK
}UART_SouceClkTypeDef;

typedef enum
{
	UART_0 = 1,
	UART_1
}UART_NumberTypeDef;

typedef enum
{
  Baud_2400 = 1,
  Baud_4800,
  Baud_9600,
  Baud_19200,
  Baud_38400,
  Baud_57600,
  Baud_76800,
  Baud_115200
}UART_BaudTypeDef;

void UARTInit(UART_NumberTypeDef UARTNumber, UART_SouceClkTypeDef UARTClkSource, UART_BaudTypeDef BaudRate);
void UART_SendByte(UART_NumberTypeDef UART_Number, unsigned char u8data);
void UartString(UART_NumberTypeDef UARTNumber,char *s);
void UartStringLength(UART_NumberTypeDef UARTNumber,char *s,unsigned int length);

#endif
