#include "serial.h"

/***USART1 GPIO Defined***/
#define SERIAL1_USART              USART1
#define SERIAL1_USART_GPIO_TX      GPIOA
#define SERIAL1_USART_GPIO_RX      GPIOA

#define SERIAL1_USART_PIN_TX       GPIO_Pin_9
#define SERIAL1_USART_PIN_RX       GPIO_Pin_10

#define SERIAL1_USART_TX_GPIO_CLK  RCC_APB2Periph_GPIOA
#define SERIAL1_USART_RX_GPIO_CLK  RCC_APB2Periph_GPIOA

#define SERIAL1_USART_CLK          RCC_APB2Periph_USART1
#define SERIAL1_USART_AFIO_CLK     RCC_APB2Periph_AFIO     
#define SERIAL1_USART_IRQn         USART1_IRQn                 
/***USART2 GPIO Defined***/
#define SERIAL2_USART              USART2
#define SERIAL2_USART_GPIO_TX      GPIOA
#define SERIAL2_USART_GPIO_RX      GPIOA

#define SERIAL2_USART_PIN_TX       GPIO_Pin_2
#define SERIAL2_USART_PIN_RX       GPIO_Pin_3

#define SERIAL2_USART_TX_GPIO_CLK  RCC_APB2Periph_GPIOA
#define SERIAL2_USART_RX_GPIO_CLK  RCC_APB2Periph_GPIOA

#define SERIAL2_USART_CLK          RCC_APB1Periph_USART2   
#define SERIAL2_USART_IRQn         USART2_IRQn

/***USART3 GPIO Defined***/
#define SERIAL3_USART              USART3
#define SERIAL3_USART_GPIO_TX      GPIOB
#define SERIAL3_USART_GPIO_RX      GPIOB

#define SERIAL3_USART_PIN_TX       GPIO_Pin_10
#define SERIAL3_USART_PIN_RX       GPIO_Pin_11

#define SERIAL3_USART_TX_GPIO_CLK  RCC_APB2Periph_GPIOB
#define SERIAL3_USART_RX_GPIO_CLK  RCC_APB2Periph_GPIOB

#define SERIAL3_USART_CLK          RCC_APB1Periph_USART3   
#define SERIAL3_USART_IRQn         USART3_IRQn

#define UART1SENDSIZE	50

STATIC U32 g_u32Uart1RevCount = 0;
STATIC U32 g_u32Uart2RevCount = 0;
STATIC U32 g_u32Uart3RevCount = 0;

STATIC U8 g_SendBuff[50];

PQueueInfo pUart1QueueInfo = NULL, pUart2QueueInfo = NULL, pUart3QueueInfo = NULL;
/*******************************************************************************
* Function Name  : UartCreate
* Description    : 调用此函数可以完成对指定串口设备的所有参数配置。涉及到的配置项
*                  有以下几个：
*                  1.串口设备引脚初始化
*                  2.串口设备引脚时钟初始化
*                  3.串口设备时钟初始化
*                  4.串口设备引脚重映射时钟初始化
*                  5.串口设备中断向量设置
*                  6.串口设备引脚重映射设置
*                  7.创建串口设备收发数据邮箱
*                  8.使能串口设备和引脚重映射时钟
*                  9.串口设备Tx引脚配置
*                 10.串口设备Rx引脚配置
*                 11.串口设备中断配置
*                 12.根据需要使能串口设备中断
* Input          : USARTx -> 串口设备号
*                  USART_InitStruct -> 串口设备初始化参数(波特率、校验位。。。)
*                  EnableTxInt -> 串口设备发送中断控制
*                  EnableRxInt -> 串口设备接收中断控制
* Output         : 串口设备配置信息结构体
*******************************************************************************/

VOID UartInit(USART_InitTypeDef* pUSART_InitStructure, U32 uBaudRate)
{
	pUSART_InitStructure->USART_BaudRate = uBaudRate;
  	pUSART_InitStructure->USART_WordLength = USART_WordLength_8b;
  	pUSART_InitStructure->USART_StopBits = USART_StopBits_1;
  	pUSART_InitStructure->USART_Parity = USART_Parity_No;
  	pUSART_InitStructure->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	pUSART_InitStructure->USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
}

VOID UartCreate(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct,
                       BOOL EnableTxInt, BOOL EnableRxInt)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	NVIC_InitTypeDef NVIC_InitStructure;
  
	XSERIAL xSerial = {0};
	XSERIAL *p ; //动态分配串口初始化参数存储区
	p = &xSerial;

  	p->USARTx = USARTx; //保存要初始化的串口设备号
  	p->USART_InitStruct = USART_InitStruct; //存储串口初始化参数
  	p->USART_EnableTxInt = EnableTxInt; //存储串口发送中断控制参数
  	p->USART_EnableRxInt = EnableRxInt; //存储串口接收中断控制参数
  
  	if(USARTx == USART1)
  	{
    	/* 串口1初始化参数 */
    	p->USART_PinTx = SERIAL1_USART_PIN_TX; //Tx引脚
    	p->USART_PinRx = SERIAL1_USART_PIN_RX; //Rx引脚
    	p->USART_PinTxGpioClk = SERIAL1_USART_TX_GPIO_CLK; //Tx引脚时钟
    	p->USART_PinRxGpioClk = SERIAL1_USART_RX_GPIO_CLK; //Rx引脚时钟
    	p->USART_Clk = SERIAL1_USART_CLK; //串口1设备时钟
    	p->USART_APB2PeriphAfioClk = SERIAL1_USART_AFIO_CLK; //串口1引脚重映射时钟
    	p->USART_IRQChannel = SERIAL1_USART_IRQn; //串口1中断向量
    	p->USART_PinRxGpio = SERIAL1_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL1_USART_GPIO_TX;
          
    	/* 使能串口1和串口1引脚重映射时钟 */
    	RCC_APB2PeriphClockCmd((p->USART_APB2PeriphAfioClk | p->USART_Clk), ENABLE);
		
		if(pUart1QueueInfo == NULL)
		{
			pUart1QueueInfo = malloc(sizeof(CQueueInfo));
			if(pUart1QueueInfo == NULL)
			{
				EnterException(ERR_MALLOC_FAIL);
			}
			
			DmaConfig(DMA1_Channel4, (U32)&USART1->DR, (U32)g_SendBuff, UART1SENDSIZE);//DMA1通道4,外设为串口1,存储器为g_SendBuff,长度UART1SENDSIZE.
		}
  	}
  
  	else if	(USARTx == USART2)
  	{
    	/* 串口2初始化参数 */
    	p->USART_PinTx = SERIAL2_USART_PIN_TX; //Tx引脚
    	p->USART_PinRx = SERIAL2_USART_PIN_RX; //Rx引脚
    	p->USART_PinTxGpioClk = SERIAL2_USART_TX_GPIO_CLK; //Tx引脚时钟
    	p->USART_PinRxGpioClk = SERIAL2_USART_RX_GPIO_CLK; //Rx引脚时钟
    	p->USART_Clk = SERIAL2_USART_CLK; //串口2设备时钟
    	p->USART_IRQChannel = SERIAL2_USART_IRQn; //串口2中断向量
    	p->USART_PinRxGpio = SERIAL2_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL2_USART_GPIO_TX;
    
    	/* 使能串口2时钟 */
    	RCC_APB1PeriphClockCmd(p->USART_Clk, ENABLE);
		
		if(pUart2QueueInfo == NULL)
		{
			pUart2QueueInfo = malloc(sizeof(CQueueInfo));
			if(pUart2QueueInfo == NULL)
			{
				EnterException(ERR_MALLOC_FAIL);
			}
		}
  	}
	
	else if	(USARTx == USART3)
  	{
    	/* 串口2初始化参数 */
    	p->USART_PinTx = SERIAL3_USART_PIN_TX; //Tx引脚
    	p->USART_PinRx = SERIAL3_USART_PIN_RX; //Rx引脚
    	p->USART_PinTxGpioClk = SERIAL3_USART_TX_GPIO_CLK; //Tx引脚时钟
    	p->USART_PinRxGpioClk = SERIAL3_USART_RX_GPIO_CLK; //Rx引脚时钟
    	p->USART_Clk = SERIAL3_USART_CLK; //串口3设备时钟
    	p->USART_IRQChannel = SERIAL3_USART_IRQn; //串口3中断向量
    	p->USART_PinRxGpio = SERIAL3_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL3_USART_GPIO_TX;
    
    	/* 使能串口3时钟 */
    	RCC_APB1PeriphClockCmd(p->USART_Clk, ENABLE);

		if(pUart3QueueInfo == NULL)
		{
			pUart3QueueInfo = malloc(sizeof(CQueueInfo));
			
			if(pUart3QueueInfo == NULL)
			{
				EnterException(ERR_MALLOC_FAIL);
			}
		}
  	}
	RCC_APB2PeriphClockCmd((p->USART_PinTxGpioClk), ENABLE);
	RCC_APB2PeriphClockCmd((p->USART_PinRxGpioClk), ENABLE);
  	/* 串口Tx引脚配置 */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinTx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(p->USART_PinTxGpio, &GPIO_InitStructure);
  
  	/* 串口Rx引脚配置 */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinRx;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(p->USART_PinRxGpio, &GPIO_InitStructure);
  
  	if (USARTx == USART1)
	{
		/* 串口1中断配置 */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(USARTx == USART2)
	{
		/* 串口2中断配置 */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(USARTx == USART3)
	{
		/* 串口2中断配置 */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
  
  	/* 串口设备参数设置 */
  	USART_Init(USARTx, USART_InitStruct);

  	/* Enable the USART Transmoit interrupt: this interrupt is generated when the 
   	   USART transmit data register is empty */  
  	if(EnableTxInt)
  	{
    	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
  	}
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	   USART receive data register is not empty */
	if(EnableRxInt)
	{
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	}

  
}


STATIC U16 g_u16DmaMemLength;//保存DMA每次数据传送的长度 	    
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量 
VOID DmaConfig(DMA_Channel_TypeDef* DMA_CHx,U32 cpar,U32 cmar,U16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
    DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
	g_u16DmaMemLength=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	  	
} 
//开启一次DMA传输
VOID DmaEnable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA1_Channel4, g_u16DmaMemLength);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
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
	/* 串口1接收中断处理 */
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
	/* 串口1接收中断处理 */
  	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  	{  
		u8Value = USART_ReceiveData(USART3);
		
        if(AddQueue(pUart3QueueInfo, u8Value) == TRUE)
		{
			g_u32Uart3RevCount = GetTickCount();
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
VOID Usart1_DMA_Send(U8 *pBuf, U16 u16Length)
{
	memcpy(g_SendBuff, pBuf, u16Length);
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送  
	DmaEnable(DMA1_Channel4);//开始一次DMA传输！
}

VOID UartDeinit(USART_TypeDef* USARTx)
{  	/* 开启串口TX中断 */

	if (USARTx == USART1)
	{
		free(pUart1QueueInfo);

	}
	else if(USARTx == USART2)
	{	
		free(pUart2QueueInfo);
	}
	else if(USARTx == USART3)
	{	
		free(pUart3QueueInfo);
	}
  	USART_Cmd(USARTx, DISABLE);
	
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
