#ifndef __SERIAL_H                           
#define __SERIAL_H

/* ͷ�ļ����� */
#include "includes.h"

/* ȫ�ֱ������� */
typedef struct 
{
    USART_TypeDef* USARTx;
    USART_InitTypeDef* USART_InitStruct;
    BOOL USART_EnableTxInt;
    BOOL USART_EnableRxInt;
    
    U16 USART_PinRx;
    U16 USART_PinTx;
    
    GPIO_TypeDef* USART_PinRxGpio;
    GPIO_TypeDef* USART_PinTxGpio;
    
    U32 USART_Clk;
    U32 USART_PinRxGpioClk;
    U32 USART_PinTxGpioClk;
    U8 USART_IRQChannel;
}XSERIAL;

#define DTUUARTSIZE	4096

EXTERN PQueueInfo pUart1QueueInfo;
EXTERN PQueueInfo pUart2QueueInfo;
EXTERN PQueueInfo pUart3QueueInfo;

/* ���⺯������ */
VOID UartInit(USART_TypeDef* USARTx);	//��ʼ�����ڹ�������
VOID UartOpen(USART_TypeDef* USARTx );							//�򿪴���
VOID UartClose(USART_TypeDef* USARTx );						//�رմ���
VOID UsartSend(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length);
VOID ReadUsartData(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength);
VOID ReadUsartDataEx(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength);
VOID ReadUsartDataSolod(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length);
U32 GetUartReceiveTime(USART_TypeDef* USARTx);
VOID UartDeinit(USART_TypeDef* USARTx);
#endif
