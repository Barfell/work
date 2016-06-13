#include "serial.h"

PQueueInfo pUart1QueueInfo, pUart2QueueInfo, pUart3QueueInfo;

STATIC U32 g_u32Uart1RevCount = 0;
STATIC U32 g_u32Uart2RevCount = 0;
U32 g_u32Uart3RevCount = 0;




VOID UartInit(USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);  
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART1, &USART_InitStructure);
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART1, ENABLE);
		USART_ClearFlag(USART1, USART_FLAG_TC);
	//-------------------------------- 串口中断-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口接收中断优先级
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		
		pUart1QueueInfo = malloc(sizeof(CQueueInfo));
		if(pUart1QueueInfo == NULL)
		{
					EnterException(ERR_MALLOC_FAIL);
		}
	}
	
	
	if(USARTx == USART2)
	{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);  
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		USART_InitStructure.USART_BaudRate = 57600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART2, &USART_InitStructure);
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART2, ENABLE);
		USART_ClearFlag(USART2, USART_FLAG_TC);
	//-------------------------------- 串口中断-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口接收中断优先级
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		pUart2QueueInfo = malloc(sizeof(CQueueInfo));
		if(pUart2QueueInfo == NULL)
		{
					EnterException(ERR_MALLOC_FAIL);
		}
	}
	
	
	if(USARTx == USART3)
	{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
		GPIO_Init(GPIOD, &GPIO_InitStructure);  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  
		GPIO_Init(GPIOD, &GPIO_InitStructure);     
		
		
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);  
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART3, &USART_InitStructure);
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART3, ENABLE);
		USART_ClearFlag(USART3, USART_FLAG_TC);
	//-------------------------------- 串口中断-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口接收中断优先级
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		pUart3QueueInfo = malloc(sizeof(CQueueInfo));
		if(pUart3QueueInfo == NULL)
		{
					EnterException(ERR_MALLOC_FAIL);
		}
	}
}

/*******************************************************************************
* Function Name  : UartOpen
* Description    : 开启对应串口设备。此函数和UartClose函数为配对函数。
* Input          : pserial -> 串口设备配置信息结构体
* Output         : 函数执行成功结果
*******************************************************************************/
VOID UartOpen(USART_TypeDef* USARTx)
{
  	/* 开启串口TX中断 */
  	USART_Cmd(USARTx, ENABLE);
}

/*******************************************************************************
* Function Name  : UartClose
* Description    : 关闭对应串口设备。此函数UartOpen函数为配对函数。
* Input          : pserial -> 串口设备配置信息结构体
* Output         : 函数执行成功结果
*******************************************************************************/
VOID UartClose(USART_TypeDef* USARTx)
{
  	/* 关闭串口TX中断 */
  	USART_Cmd(USARTx, DISABLE);
	
}
/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : 串口中断处理函数。完成串口所有的中断判断和处理操作！在整个中
*                  断处理函数中，除了发送和接收中断处理模块外，还有其他状态检测处
*                  理。这些状态检测处理有两种不同的判断条件，一种是在使能了相应的
*                  中断之后，通过判断中断标志来进行检测；另一种是在没有使能相应的
*                  中断的情况下，通过判断各个状态位来进行检测。
* Input          : 无
* Output         : 无
*******************************************************************************/

U32 GetUartReceiveTime(USART_TypeDef* USARTx)
{
	U32 u32Value;
	
	if(USARTx == USART1)
	{
		u32Value = g_u32Uart1RevCount;
	}
	else if(USARTx == USART2)
	{
		u32Value = g_u32Uart2RevCount;
	}
	else if(USARTx == USART3)
	{
		u32Value = g_u32Uart3RevCount;
	}
	return u32Value;
}
VOID UsartSend(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length)
{
	U16 u16Count;
	
	for(u16Count = 0; u16Count < u16Length; u16Count++)
	{
		/* 将要发送的数据写入串口1数据发送寄存器 */
		USART_SendData(USARTx, *(pBuf + u16Count)); 
		
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);//检查是否发送完
			
	}
}

VOID UartDeinit(USART_TypeDef* USARTx)
{  	/* 开启串口TX中断 */

	if (USARTx == USART1)
	{
		free(pUart1QueueInfo);

	}
	if(USARTx == USART2)
	{	
		free(pUart2QueueInfo);
	}
	if(USARTx == USART3)
	{	
		free(pUart3QueueInfo);
	}
  	USART_Cmd(USARTx, DISABLE);
	
	USART_ClearFlag(USARTx, USART_FLAG_TC);
	USART_ClearFlag(USARTx, USART_IT_RXNE);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	
	USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
	
}

VOID ReadUsartData(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength)
{
	U16 u16Count = 0;
	QueueDataType Value;
	PQueueInfo pQueueInfo;
	
	if(USARTx == USART1)
	{
		pQueueInfo = pUart1QueueInfo;
	}
	else if(USARTx == USART2)
	{
		pQueueInfo = pUart2QueueInfo;
	}
	else if(USARTx == USART3)
	{
		pQueueInfo = pUart3QueueInfo;
	}
	while(DeleteQueue(pQueueInfo, &Value) == TRUE)
	{
		*(pBuf + u16Count) = Value;
		u16Count++;	
		if(u16Count > DTUUARTSIZE)
		{
			break;
		}
	}
	*pLength = u16Count;
}
STATIC U8 g_u8LastValue;
VOID ReadUsartDataEx(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength)
{
	U16 u16Count = 0;
	QueueDataType Value;
	PQueueInfo pQueueInfo;
	
	if(USARTx == USART1)
	{
		pQueueInfo = pUart1QueueInfo;
	}
	else if(USARTx == USART2)
	{
		pQueueInfo = pUart2QueueInfo;
	}
	else if(USARTx == USART3)
	{
		pQueueInfo = pUart3QueueInfo;
	}
	while(DeleteQueue(pQueueInfo, &Value) == TRUE)
	{
		*(pBuf + u16Count) = Value;
		
		u16Count++;	
		if((Value == 0x0A) && (g_u8LastValue == 0x0D))
		{
			break;
		}
		g_u8LastValue = Value;
	}
	*pLength = u16Count;
}



VOID ReadUsartDataSolod(USART_TypeDef* USARTx, U8 *pBuf, U16 u16Length)
{
	U16 u16Count = 0;
	QueueDataType Value;
	PQueueInfo pQueueInfo;
	
	if(USARTx == USART1)
	{
		pQueueInfo = pUart1QueueInfo;
	}
	else if(USARTx == USART2)
	{
		pQueueInfo = pUart2QueueInfo;
	}
	else if(USARTx == USART3)
	{
		pQueueInfo = pUart3QueueInfo;
	}
	while(u16Length != u16Count)
	{
		while(DeleteQueue(pQueueInfo, &Value) == TRUE)
		{
			*(pBuf + u16Count) = Value;
			
			u16Count++;	
		}
		
	}
	
}



//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}





VOID USART1_IRQHandler(VOID)
{ 
	U8 u8Value;
	/* 串口1接收中断处理 */
  	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  	{ 
		u8Value = USART_ReceiveData(USART1);
		
		if(AddQueue(pUart1QueueInfo, u8Value) == TRUE)
		{
			g_u32Uart1RevCount = GetTickCount();
		}
  	}
}
VOID USART2_IRQHandler(VOID)
{
	U8 u8Value;
  	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  	{  
		u8Value = USART_ReceiveData(USART2);
		
        if(AddQueue(pUart2QueueInfo, u8Value) == TRUE)
		{
			g_u32Uart2RevCount = GetTickCount();
		}
  	}
}
VOID USART3_IRQHandler(VOID)
{
	U8 u8Value;
  	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  	{  
		u8Value = USART_ReceiveData(USART3);	
    if(AddQueue(pUart3QueueInfo, u8Value) == TRUE)
		{
			g_u32Uart3RevCount = GetTickCount();
		}
  	}
}
