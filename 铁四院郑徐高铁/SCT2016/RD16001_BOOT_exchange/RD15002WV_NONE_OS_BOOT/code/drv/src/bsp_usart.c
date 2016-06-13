#include "stm32f4xx.h"
#include <stdio.h>
#include <stm32f4xx.h>
#include "includes.h"

unsigned char UartPreData=0;
unsigned char UartFinishFlag = 0;//�����·����������־


void UsartConfig(void)
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
}





//void USART3_IRQHandler(void)
//{ 
//	unsigned char u8Value = 0;
//	/* ����1�����жϴ��� */
//  	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//  	{ 
//		USART_ClearFlag(USART3, USART_FLAG_RXNE);
//		u8Value = USART_ReceiveData(USART3);
//		//LoopRAMWriteByte(u8Value);
//		if(UartPreData == '\r' && u8Value == '\n')
//			{UartFinishFlag = 1;}
//  	}
//	UartPreData = u8Value;//��¼��һ�ε�����
//}

//void USART1_IRQHandler(void)
//{ 
//	unsigned char u8Value = 0;
//	/* ����1�����жϴ��� */
//  	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  	{ 
//		USART_ClearFlag(USART1, USART_FLAG_RXNE);
//		u8Value = USART_ReceiveData(USART1);
//		USART_SendData(USART1,u8Value );
//		if(UartPreData == '\r' && u8Value == '\n')
//			{UartFinishFlag = 1;}
//  	}
//	UartPreData = u8Value;//��¼��һ�ε�����
//}


//int fputc(int ch, FILE *f)
//{
//#ifdef _UART1_
//	USART_GetFlagStatus(USART1, USART_FLAG_TC);
//	USART_ClearFlag( USART1, USART_FLAG_TC );
//  	USART_SendData(USART1, (u8) ch);
//  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//  	return ch;
//#endif
//	
//#ifdef _UART3_
//	USART_GetFlagStatus(USART3, USART_FLAG_TC);
//	USART_ClearFlag( USART3, USART_FLAG_TC );
//  	USART_SendData(USART3, (u8) ch);
//  	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
//  	return ch;
//#endif
//}




