/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* 文件名称: command.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 串口收发数据处理.
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
* Description    : 处理串口1接收缓冲区数据
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

		for(i=0;i<recdatalength;i++,Usart1Command.Out1++)//一个字节一个字节地查询
		{
			if(Usart1Command.Out1 >= Usart1Command_Buf_Size)Usart1Command.Out1 = 0;//指针是否溢出

			USARTx_Putc(USART2,Usart1Command.Buf1[Usart1Command.Out1] );//转发给串口2
		}
	}
}

/*******************************************************************************
* Function Name  : Process_Usart2Command
* Description    : 处理串口2接收缓冲区数据
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

		for(i=0;i<recdatalength;i++,Usart2Command.Out2++)//一个字节一个字节地查询
		{
			if(Usart2Command.Out2 >= Usart2Command_Buf_Size)Usart2Command.Out2 = 0;//指针是否溢出

			USARTx_Putc(USART1,Usart2Command.Buf2[Usart2Command.Out2] );//转发给串口1
		}
	}
}

