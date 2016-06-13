#include "serial.h"

PQueueInfo pUart1QueueInfo, pUart2QueueInfo, pUart3QueueInfo;
U8 *pUart1Queue, *pUart2Queue, *pUart3Queue;
STATIC U32 g_u32Uart1RevCount = 0;
STATIC U32 g_u32Uart2RevCount = 0;
STATIC U32 g_u32Uart3RevCount = 0;

VOID UartInit(USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,DISABLE);
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
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		
		pUart1Queue = malloc(MAXSIZE_A);
		
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,DISABLE);
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
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		pUart2Queue = malloc(MAXSIZE_A);
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,DISABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);  
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
		USART_InitStructure.USART_BaudRate = 115200;
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
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure); 
		pUart3Queue = malloc(MAXSIZE_A);
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

VOID UartDeinit(USART_TypeDef* USARTx)
{  	/* 开启串口TX中断 */

	if (USARTx == USART1)
	{
		free(pUart1QueueInfo);
		free(pUart1Queue);
	}
	if(USARTx == USART2)
	{	
		free(pUart2QueueInfo);
		free(pUart2Queue);
	}
	if(USARTx == USART3)
	{	
		free(pUart3QueueInfo);
		free(pUart3Queue);
	}
  	USART_Cmd(USARTx, DISABLE);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	
	USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
	
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
VOID USART1_IRQHandler(VOID)
{ 
	U8 u8Value;
	/* 串口1接收中断处理 */
  	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  	{ 
		u8Value = USART_ReceiveData(USART1);
		
		if(AddQueue(pUart1QueueInfo, u8Value, pUart1Queue) == TRUE)
		{
			g_u32Uart1RevCount = GetTickCount();
		}
          
  	}
}
VOID USART2_IRQHandler(VOID)
{
	U8 u8Value;
	/* 串口1接收中断处理 */
  	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  	{  
		u8Value = USART_ReceiveData(USART2);
		
        if(AddQueue(pUart2QueueInfo, u8Value, pUart2Queue) == TRUE)
		{
			g_u32Uart2RevCount = GetTickCount();
		}
          
  	}
}
VOID USART3_IRQHandler(VOID)
{
	U8 u8Value;
	/* 串口1接收中断处理 */
  	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  	{  
		u8Value = USART_ReceiveData(USART2);
		
        if(AddQueue(pUart2QueueInfo, u8Value, pUart2Queue) == TRUE)
		{
			g_u32Uart2RevCount = GetTickCount();
		}
          
  	}
}
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

VOID ReadUsartData(USART_TypeDef* USARTx, U8 *pBuf, U16 *pLength)
{
	U16 u16Count = 0;
	QueueDataType Value;
	U8 *pData;
	PQueueInfo pQueueInfo;
	
	if(USARTx == USART1)
	{
		pQueueInfo = pUart1QueueInfo;
		pData = pUart1Queue;
	}
	else if(USARTx == USART2)
	{
		pQueueInfo = pUart2QueueInfo;
		pData = pUart2Queue;
	}
	while(DeleteQueue(pQueueInfo, &Value, pData) == TRUE)
	{
		*(pBuf + u16Count) = Value;
		u16Count++;	
		
	}
	*pLength = u16Count;
}
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)
void _ttywrch(int ch)
{
	ch  = ch;
}
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 
