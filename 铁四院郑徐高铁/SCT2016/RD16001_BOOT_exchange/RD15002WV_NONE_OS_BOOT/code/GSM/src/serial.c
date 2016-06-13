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
	//-------------------------------- �����ж�-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//���ڽ����ж����ȼ�
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
	//-------------------------------- �����ж�-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//���ڽ����ж����ȼ�
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
	//-------------------------------- �����ж�-------------------------------------//	
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//���ڽ����ж����ȼ�
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
* Description    : ������Ӧ�����豸���˺�����UartClose����Ϊ��Ժ�����
* Input          : pserial -> �����豸������Ϣ�ṹ��
* Output         : ����ִ�гɹ����
*******************************************************************************/
VOID UartOpen(USART_TypeDef* USARTx)
{
  	/* ��������TX�ж� */
  	USART_Cmd(USARTx, ENABLE);
}

/*******************************************************************************
* Function Name  : UartClose
* Description    : �رն�Ӧ�����豸���˺���UartOpen����Ϊ��Ժ�����
* Input          : pserial -> �����豸������Ϣ�ṹ��
* Output         : ����ִ�гɹ����
*******************************************************************************/
VOID UartClose(USART_TypeDef* USARTx)
{
  	/* �رմ���TX�ж� */
  	USART_Cmd(USARTx, DISABLE);
	
}

VOID UartDeinit(USART_TypeDef* USARTx)
{  	/* ��������TX�ж� */

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
* Description    : �����жϴ���������ɴ������е��ж��жϺʹ����������������
*                  �ϴ������У����˷��ͺͽ����жϴ���ģ���⣬��������״̬��⴦
*                  ����Щ״̬��⴦�������ֲ�ͬ���ж�������һ������ʹ������Ӧ��
*                  �ж�֮��ͨ���ж��жϱ�־�����м�⣻��һ������û��ʹ����Ӧ��
*                  �жϵ�����£�ͨ���жϸ���״̬λ�����м�⡣
* Input          : ��
* Output         : ��
*******************************************************************************/
VOID USART1_IRQHandler(VOID)
{ 
	U8 u8Value;
	/* ����1�����жϴ��� */
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
	/* ����1�����жϴ��� */
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
	/* ����1�����жϴ��� */
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
		/* ��Ҫ���͵�����д�봮��1���ݷ��ͼĴ��� */
		USART_SendData(USARTx, *(pBuf + u16Count)); 
		
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);//����Ƿ�����
			
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
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)
void _ttywrch(int ch)
{
	ch  = ch;
}
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 
