/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* 文件名称: usart.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 串口配置.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

  return ch;
}

/*******************************************************************************
* Function Name  : USARTx_Putc
* Description    : send char to USARTx.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USARTx_Putc(USART_TypeDef* USARTx,char c)
{
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//导致一向串口1发送数据就进入了死循环
	USART_SendData(USARTx, c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

/*******************************************************************************
* Function Name  : USART_PutString
* Description    : send string to USARTx.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_PutString(USART_TypeDef* USARTx, char *Buffer)
{
	while (*Buffer != '\0')
	{
		USARTx_Putc(USARTx,*Buffer);
		Buffer++;
	}
}

/*******************************************************************************
* Function Name  : USART_SendString
* Description    : Send length chars to USARTX.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - Buffer: the address of String .
*				   - length: the length of String.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SendString(USART_TypeDef* USARTx, char *Buffer,u16 length)
{
	u16 i;
	for(i=0;i<length;i++)
	{
		USARTx_Putc(USARTx,Buffer[i]);
	}
}

/*******************************************************************************
* Function Name  : USART_SendWord
* Description    : Send Word to USARTX.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - DataWord: the Data to transmit. .
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SendWord(USART_TypeDef* USARTx, u32 DataWord)
{
	u8 i;
	u16 temp=0;
	for(i=0;i<4;i++)
	{
		temp=(u8)DataWord;
		USARTx_Putc(USARTx,temp);
		DataWord=DataWord>>8;
	}
}

