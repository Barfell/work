#ifndef __SERIAL_H                           
#define __SERIAL_H

/* 头文件处理 */
#include "kernal.h"
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

EXTERN PQueueInfo pUart1QueueInfo;
EXTERN PQueueInfo pUart2QueueInfo;
EXTERN PQueueInfo pUart3QueueInfo;

/* 对外函数声明 */
VOID UartInit(USART_InitTypeDef* pUSART_InitStructure, U32 uBaudRate);	//初始化串口公用配置
VOID UartCreate(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct, BOOL EnableTxInt, BOOL EnableRxInt);	//串口私有配置
VOID UartOpen(USART_TypeDef* USARTx );							//打开串口
VOID UartClose(USART_TypeDef* USARTx );						//关闭串口
VOID UsartSend(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length);
VOID ReadUsartData(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength);
U32 GetUartReceiveTime(USART_TypeDef* USARTx);
VOID UartDeinit(USART_TypeDef* USARTx);
VOID DmaConfig(DMA_Channel_TypeDef*DMA_CHx, U32 cpar, U32 cmar, U16 cndtr);//配置DMA1_CHx
VOID DmaEnable(DMA_Channel_TypeDef*DMA_CHx);//使能DMA1_CHx
VOID Usart1_DMA_Send(U8 *pBuf, U16 u16Length);
#endif
