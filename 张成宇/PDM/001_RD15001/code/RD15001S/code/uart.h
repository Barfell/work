#ifndef _UART_H
#define _UART_H
#include "protocol.h"

#define uchar unsigned char	
#define uint unsigned int


extern PQueueInfo pQueueUsart1Info;
extern PQueueInfo pQueueUsart2Info;

extern U32 g_u32Uart1TimeCount; 
extern U32 g_u32Uart2TimeCount;

void UartInit(void);

void Uart1_Tx(uchar *string0,uchar snum0);

void Uart2_Tx(uchar *string1,uchar snum1);

void Uart1_Tx_End(uchar *string);

void Uart2_Tx_End(uchar *string);

uchar GetUart1Length(void);
uchar GetUart2Length(void);
void ClearUart1Length(void);
void ClearUart2Length(void);

void ReceiveUsart1Data(uchar *pBuf, U16 *pLength);
void ReceiveUsart2Data(uchar *pBuf, U16 *pLength);

#endif