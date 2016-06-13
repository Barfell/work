/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* �ļ�����: command.c
* ��������: Dyj
* ����汾: V0.0.1
* ��������: 06/14/2012
* ��������: �����շ����ݴ���.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "command.h"
#include <stdio.h>
#include <string.h>

Usart1CommandTypeDef		Usart1Command;
Usart2CommandTypeDef		Usart2Command;

/*******************************************************************************
* Function Name  : Process_Usart1Command
* Description    : ������1���ջ���������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_Usart1Command(void)
{
	u32 i;
	u32 recdatalength;
	if(Usart1Command.Out1 != Usart1Command.In1)
    {
        if(Usart1Command.In1>Usart1Command.Out1)recdatalength = Usart1Command.In1 - Usart1Command.Out1;
        else recdatalength = Usart1Command.In1 + Usart1Command_Buf_Size - Usart1Command.Out1;

		for(i=0;i<recdatalength;i++,Usart1Command.Out1++)//һ���ֽ�һ���ֽڵز�ѯ
		{
			if(Usart1Command.Out1 >= Usart1Command_Buf_Size)Usart1Command.Out1 = 0;//ָ���Ƿ����

			USARTx_Putc(USART2,Usart1Command.Buf1[Usart1Command.Out1] );//ת��������2
		}
	}
}

/*******************************************************************************
* Function Name  : Process_Usart2Command
* Description    : ������2���ջ���������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_Usart2Command(void)
{
	u32 i;
	u32 recdatalength;
	if(Usart2Command.Out2 != Usart2Command.In2)
    {
        if(Usart2Command.In2>Usart2Command.Out2)recdatalength = Usart2Command.In2 - Usart2Command.Out2;
        else recdatalength = Usart2Command.In2 + Usart2Command_Buf_Size - Usart2Command.Out2;

		for(i=0;i<recdatalength;i++,Usart2Command.Out2++)//һ���ֽ�һ���ֽڵز�ѯ
		{
			if(Usart2Command.Out2 >= Usart2Command_Buf_Size)Usart2Command.Out2 = 0;//ָ���Ƿ����

			USARTx_Putc(USART1,Usart2Command.Buf2[Usart2Command.Out2] );//ת��������1
		}
	}
}

