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
STATIC volatile U32 g_u32Uart1RevCount = 0;
STATIC volatile U32 g_u32Uart2RevCount = 0;


PQueueInfo pUart1QueueInfo, pUart2QueueInfo;
U8 *pUart1Queue, *pUart2Queue;
/*******************************************************************************
* Function Name  : UartCreate
* Description    : µ÷ÓÃ´Ëº¯Êı¿ÉÒÔÍê³É¶ÔÖ¸¶¨´®¿ÚÉè±¸µÄËùÓĞ²ÎÊıÅäÖÃ¡£Éæ¼°µ½µÄÅäÖÃÏî
*                  ÓĞÒÔÏÂ¼¸¸ö£º
*                  1.´®¿ÚÉè±¸Òı½Å³õÊ¼»¯
*                  2.´®¿ÚÉè±¸Òı½ÅÊ±ÖÓ³õÊ¼»¯
*                  3.´®¿ÚÉè±¸Ê±ÖÓ³õÊ¼»¯
*                  4.´®¿ÚÉè±¸Òı½ÅÖØÓ³ÉäÊ±ÖÓ³õÊ¼»¯
*                  5.´®¿ÚÉè±¸ÖĞ¶ÏÏòÁ¿ÉèÖÃ
*                  6.´®¿ÚÉè±¸Òı½ÅÖØÓ³ÉäÉèÖÃ
*                  7.´´½¨´®¿ÚÉè±¸ÊÕ·¢Êı¾

*                  8.Ê¹ÄÜ´®¿ÚÉè±¸ºÍÒı½ÅÖØÓ³ÉäÊ±ÖÓ
*                  9.´®¿ÚÉè±¸TxÒı½ÅÅäÖÃ
*                 10.´®¿ÚÉè±¸RxÒı½ÅÅäÖÃ
*                 11.´®¿ÚÉè±¸ÖĞ¶ÏÅäÖÃ
*                 12.¸ù¾İĞèÒªÊ¹ÄÜ´®¿ÚÉè±¸ÖĞ¶Ï
* Input          : USARTx -> ´®¿ÚÉè±¸ºÅ
*                  USART_InitStruct -> ´®¿ÚÉè±¸³õÊ¼»¯²ÎÊı(²¨ÌØÂÊ¡¢Ğ£ÑéÎ»¡£¡£¡£)
*                  EnableTxInt -> ´®¿ÚÉè±¸·¢ËÍÖĞ¶Ï¿ØÖÆ
*                  EnableRxInt -> ´®¿ÚÉè±¸½ÓÊÕÖĞ¶Ï¿ØÖÆ
* Output         : ´®¿ÚÉè±¸ÅäÖÃĞÅÏ¢½á¹¹Ìå
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
	XSERIAL *p ; //¶¯Ì¬·ÖÅä´®¿Ú³õÊ¼»¯²ÎÊı´æ´¢Çø
	p = &xSerial;

  	p->USARTx = USARTx; //±£´æÒª³õÊ¼»¯µÄ´®¿ÚÉè±¸ºÅ
  	p->USART_InitStruct = USART_InitStruct; //´æ´¢´®¿Ú³õÊ¼»¯²ÎÊı
  	p->USART_EnableTxInt = EnableTxInt; //´æ´¢´®¿Ú·¢ËÍÖĞ¶Ï¿ØÖÆ²ÎÊı
  	p->USART_EnableRxInt = EnableRxInt; //´æ´¢´®¿Ú½ÓÊÕÖĞ¶Ï¿ØÖÆ²ÎÊı
  
  	if(USARTx == USART1)
  	{
    	/* ´®¿Ú1³õÊ¼»¯²ÎÊı */
    	p->USART_PinTx = SERIAL1_USART_PIN_TX; //TxÒı½Å
    	p->USART_PinRx = SERIAL1_USART_PIN_RX; //RxÒı½Å
    	p->USART_PinTxGpioClk = SERIAL1_USART_TX_GPIO_CLK; //TxÒı½ÅÊ±ÖÓ
    	p->USART_PinRxGpioClk = SERIAL1_USART_RX_GPIO_CLK; //RxÒı½ÅÊ±ÖÓ
    	p->USART_Clk = SERIAL1_USART_CLK; //´®¿Ú1Éè±¸Ê±ÖÓ
    	p->USART_APB2PeriphAfioClk = SERIAL1_USART_AFIO_CLK; //´®¿Ú1Òı½ÅÖØÓ³ÉäÊ±ÖÓ
    	p->USART_IRQChannel = SERIAL1_USART_IRQn; //´®¿Ú1ÖĞ¶ÏÏòÁ¿
    	p->USART_PinRxGpio = SERIAL1_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL1_USART_GPIO_TX;
          
    	/* Ê¹ÄÜ´®¿Ú1ºÍ´®¿Ú1Òı½ÅÖØÓ³ÉäÊ±ÖÓ */
    	RCC_APB2PeriphClockCmd((p->USART_APB2PeriphAfioClk | p->USART_Clk), ENABLE);
						

		pUart1Queue = malloc(MAXSIZE_A);
		
		pUart1QueueInfo = malloc(sizeof(CQueueInfo));
		
		if((pUart1QueueInfo == NULL) || (pUart1QueueInfo == NULL))
		{
			EnterException(ERR_UART1_MALLOC_FAIL);
		}
		pUart1QueueInfo->SizeType = QUEUETYPE_A;
		
  	}
  
	else if	(USARTx == USART2)
  	{
    	/* ´®¿Ú2³õÊ¼»¯²ÎÊı */
    	p->USART_PinTx = SERIAL2_USART_PIN_TX; //TxÒı½Å
    	p->USART_PinRx = SERIAL2_USART_PIN_RX; //RxÒı½Å
    	p->USART_PinTxGpioClk = SERIAL2_USART_TX_GPIO_CLK; //TxÒı½ÅÊ±ÖÓ
    	p->USART_PinRxGpioClk = SERIAL2_USART_RX_GPIO_CLK; //RxÒı½ÅÊ±ÖÓ
    	p->USART_Clk = SERIAL2_USART_CLK; //´®¿Ú2Éè±¸Ê±ÖÓ
    	p->USART_IRQChannel = SERIAL2_USART_IRQn; //´®¿Ú2ÖĞ¶ÏÏòÁ¿
    	p->USART_PinRxGpio = SERIAL2_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL2_USART_GPIO_TX;
    
    	/* Ê¹ÄÜ´®¿Ú2Ê±ÖÓ */
    	RCC_APB1PeriphClockCmd(p->USART_Clk, ENABLE);
		
		
		pUart2Queue = malloc(MAXSIZE_B);
		
		pUart2QueueInfo = malloc(sizeof(CQueueInfo));
		
		if((pUart2QueueInfo == NULL) && (pUart2QueueInfo == NULL))
		{
			EnterException(ERR_UART2_MALLOC_FAIL);
		}
		pUart2QueueInfo->SizeType = QUEUETYPE_B;
  	}
	
	RCC_APB2PeriphClockCmd((p->USART_PinTxGpioClk), ENABLE);
	RCC_APB2PeriphClockCmd((p->USART_PinRxGpioClk), ENABLE);
  	/* ´®¿ÚTxÒı½ÅÅäÖÃ */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinTx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(p->USART_PinTxGpio, &GPIO_InitStructure);
  
  	/* ´®¿ÚRxÒı½ÅÅäÖÃ */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinRx;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(p->USART_PinRxGpio, &GPIO_InitStructure);
  
  	if (USARTx == USART1)
	{
		/* ´®¿Ú1ÖĞ¶ÏÅäÖÃ */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(USARTx == USART2)
	{
		/* ´®¿Ú2ÖĞ¶ÏÅäÖÃ */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
  	/* ´®¿ÚÉè±¸²ÎÊıÉèÖÃ */
  	USART_Init(USARTx, USART_InitStruct);

  	/* Enable the USART Transmoit interrupt: this interrupt is generated when the 
   	   USART1 transmit data register is empty */  
  	if(EnableTxInt)
  	{
    	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
  	}
	/* Enable the USART Receive interrupt: this interrupt is generated when the 
	   USART1 receive data register is not empty */
	if(EnableRxInt)
	{
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	}

  
}
VOID UartDeinit(USART_TypeDef* USARTx)
{  	/* ¿ªÆô´®¿ÚTXÖĞ¶Ï */

	if (USARTx == USART1)
	{
		free(pUart1QueueInfo);
		free(pUart1Queue);
	}
	else if(USARTx == USART2)
	{
		free(pUart2QueueInfo);
		free(pUart2Queue);
	}
  	USART_Cmd(USARTx, DISABLE);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	
	USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
	
}
/*******************************************************************************
* Function Name  : UartOpen
* Description    : ¿ªÆô¶ÔÓ¦´®¿ÚÉè±¸¡£´Ëº¯ÊıºÍUartCloseº¯ÊıÎªÅä¶Ôº¯Êı¡£
* Input          : pserial -> ´®¿ÚÉè±¸ÅäÖÃĞÅÏ¢½á¹¹Ìå
* Output         : º¯ÊıÖ´ĞĞ³É¹¦½á¹û
*******************************************************************************/
VOID UartOpen(USART_TypeDef* USARTx)
{
  	/* ¿ªÆô´®¿ÚTXÖĞ¶Ï */
  	USART_Cmd(USARTx, ENABLE);
	
}

/*******************************************************************************
* Function Name  : UartClose
* Description    : ¹Ø±Õ¶ÔÓ¦´®¿ÚÉè±¸¡£´Ëº¯ÊıUartOpenº¯ÊıÎªÅä¶Ôº¯Êı¡£
* Input          : pserial -> ´®¿ÚÉè±¸ÅäÖÃĞÅÏ¢½á¹¹Ìå
* Output         : º¯ÊıÖ´ĞĞ³É¹¦½á¹û
*******************************************************************************/
VOID UartClose(USART_TypeDef* USARTx)
{
  	/* ¹Ø±Õ´®¿ÚTXÖĞ¶Ï */
  	USART_Cmd(USARTx, DISABLE);
	
}
/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : ´®¿ÚÖĞ¶Ï´¦Àíº¯Êı¡£Íê³É´®¿ÚËùÓĞµÄÖĞ¶ÏÅĞ¶ÏºÍ´¦Àí²Ù×÷£¡ÔÚÕû¸öÖĞ
*                  ¶Ï´¦Àíº¯ÊıÖĞ£¬³ıÁË·¢ËÍºÍ½ÓÊÕÖĞ¶Ï´¦ÀíÄ£¿éÍâ£¬»¹ÓĞÆäËû×´Ì¬¼ì²â´¦
*                  Àí¡£ÕâĞ©×´Ì¬¼ì²â´¦ÀíÓĞÁ½ÖÖ²»Í¬µÄÅĞ¶ÏÌõ¼ş£¬Ò»ÖÖÊÇÔÚÊ¹ÄÜÁËÏàÓ¦µÄ
*                  ÖĞ¶ÏÖ®ºó£¬Í¨¹ıÅĞ¶ÏÖĞ¶Ï±êÖ¾À´½øĞĞ¼ì²â£»ÁíÒ»ÖÖÊÇÔÚÃ»ÓĞÊ¹ÄÜÏàÓ¦µÄ
*                  ÖĞ¶ÏµÄÇé¿öÏÂ£¬Í¨¹ıÅĞ¶Ï¸÷¸ö×´Ì¬Î»À´½øĞĞ¼ì²â¡£
* Input          : ÎŞ
* Output         : ÎŞ
*******************************************************************************/
VOID USART1_IRQHandler(VOID)
{ 
	U8 u8Value;
	/* ´®¿Ú1½ÓÊÕÖĞ¶Ï´¦Àí */
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
	/* ´®¿Ú1½ÓÊÕÖĞ¶Ï´¦Àí */
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
		/* ½«Òª·¢ËÍµÄÊı¾İĞ´Èë´®¿Ú1Êı¾İ·¢ËÍ¼Ä´æÆ÷ */
		USART_SendData(USARTx, *(pBuf + u16Count)); 
		
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);//¼ì²éÊÇ·ñ·¢ËÍÍê
			
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
//¼ÓÈëÒÔÏÂ´úÂë,Ö§³Öprintfº¯Êı,¶ø²»ĞèÒªÑ¡Ôñuse MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)
void _ttywrch(int ch)
{
	ch  = ch;
}
//±ê×¼¿âĞèÒªµÄÖ§³Öº¯Êı                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef¡¯ d in stdio.h. */ 
FILE __stdout;       
//¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//ÖØ¶¨Òåfputcº¯Êı 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//Ñ­»··¢ËÍ,Ö±µ½·¢ËÍÍê±Ï   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 
