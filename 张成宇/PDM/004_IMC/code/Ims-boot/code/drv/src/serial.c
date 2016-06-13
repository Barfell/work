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
* Description    : ���ô˺���������ɶ�ָ�������豸�����в������á��漰����������
*                  �����¼�����
*                  1.�����豸���ų�ʼ��
*                  2.�����豸����ʱ�ӳ�ʼ��
*                  3.�����豸ʱ�ӳ�ʼ��
*                  4.�����豸������ӳ��ʱ�ӳ�ʼ��
*                  5.�����豸�ж���������
*                  6.�����豸������ӳ������
*                  7.���������豸�շ���������
*                  8.ʹ�ܴ����豸��������ӳ��ʱ��
*                  9.�����豸Tx��������
*                 10.�����豸Rx��������
*                 11.�����豸�ж�����
*                 12.������Ҫʹ�ܴ����豸�ж�
* Input          : USARTx -> �����豸��
*                  USART_InitStruct -> �����豸��ʼ������(�����ʡ�У��λ������)
*                  EnableTxInt -> �����豸�����жϿ���
*                  EnableRxInt -> �����豸�����жϿ���
* Output         : �����豸������Ϣ�ṹ��
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
	XSERIAL *p ; //��̬���䴮�ڳ�ʼ�������洢��
	p = &xSerial;

  	p->USARTx = USARTx; //����Ҫ��ʼ���Ĵ����豸��
  	p->USART_InitStruct = USART_InitStruct; //�洢���ڳ�ʼ������
  	p->USART_EnableTxInt = EnableTxInt; //�洢���ڷ����жϿ��Ʋ���
  	p->USART_EnableRxInt = EnableRxInt; //�洢���ڽ����жϿ��Ʋ���
  
  	if(USARTx == USART1)
  	{
    	/* ����1��ʼ������ */
    	p->USART_PinTx = SERIAL1_USART_PIN_TX; //Tx����
    	p->USART_PinRx = SERIAL1_USART_PIN_RX; //Rx����
    	p->USART_PinTxGpioClk = SERIAL1_USART_TX_GPIO_CLK; //Tx����ʱ��
    	p->USART_PinRxGpioClk = SERIAL1_USART_RX_GPIO_CLK; //Rx����ʱ��
    	p->USART_Clk = SERIAL1_USART_CLK; //����1�豸ʱ��
    	p->USART_APB2PeriphAfioClk = SERIAL1_USART_AFIO_CLK; //����1������ӳ��ʱ��
    	p->USART_IRQChannel = SERIAL1_USART_IRQn; //����1�ж�����
    	p->USART_PinRxGpio = SERIAL1_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL1_USART_GPIO_TX;
          
    	/* ʹ�ܴ���1�ʹ���1������ӳ��ʱ�� */
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
    	/* ����2��ʼ������ */
    	p->USART_PinTx = SERIAL2_USART_PIN_TX; //Tx����
    	p->USART_PinRx = SERIAL2_USART_PIN_RX; //Rx����
    	p->USART_PinTxGpioClk = SERIAL2_USART_TX_GPIO_CLK; //Tx����ʱ��
    	p->USART_PinRxGpioClk = SERIAL2_USART_RX_GPIO_CLK; //Rx����ʱ��
    	p->USART_Clk = SERIAL2_USART_CLK; //����2�豸ʱ��
    	p->USART_IRQChannel = SERIAL2_USART_IRQn; //����2�ж�����
    	p->USART_PinRxGpio = SERIAL2_USART_GPIO_RX; 
    	p->USART_PinTxGpio = SERIAL2_USART_GPIO_TX;
    
    	/* ʹ�ܴ���2ʱ�� */
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
  	/* ����Tx�������� */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinTx;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(p->USART_PinTxGpio, &GPIO_InitStructure);
  
  	/* ����Rx�������� */
  	GPIO_InitStructure.GPIO_Pin = p->USART_PinRx;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(p->USART_PinRxGpio, &GPIO_InitStructure);
  
  	if (USARTx == USART1)
	{
		/* ����1�ж����� */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(USARTx == USART2)
	{
		/* ����2�ж����� */
		NVIC_InitStructure.NVIC_IRQChannel = p->USART_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
  	/* �����豸�������� */
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
{  	/* ��������TX�ж� */

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
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 
