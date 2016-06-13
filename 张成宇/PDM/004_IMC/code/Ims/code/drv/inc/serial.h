#ifndef __SERIAL_H                           
#define __SERIAL_H

/* 头文件处理 */
#include "kernel.h"
#include "Protocol.h"

/* 全局变量声明 */
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
    U32 USART_APB2PeriphAfioClk;
      
    U8 USART_IRQChannel;
}XSERIAL;

#define DTUUARTSIZE	1100

EXTERN PQueueInfo pUart1QueueInfo;
EXTERN PQueueInfo pUart2QueueInfo;
EXTERN U8 *pUart1Queue;
EXTERN U8 *pUart2Queue;

/* 对外函数声明 */
VOID UartInit(USART_InitTypeDef* pUSART_InitStructure, U32 uBaudRate);	//初始化串口公用配置
VOID UartCreate(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct, BOOL EnableTxInt, BOOL EnableRxInt);	//串口私有配置
VOID UartOpen(USART_TypeDef* USARTx );							//打开串口
VOID UartClose(USART_TypeDef* USARTx );						//关闭串口
VOID UsartSend(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length);
VOID ReadUsartData(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength);
U32 GetUartReceiveTime(USART_TypeDef* USARTx);
VOID UartDeinit(USART_TypeDef* USARTx);
#endif
