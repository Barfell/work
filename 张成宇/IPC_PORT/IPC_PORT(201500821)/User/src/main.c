/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* 文件名称: main.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 主函数.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "command.h"
#include "power.h"
#include <stdio.h>
#include <string.h>


/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None						       
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	System_Init();                                          //系统时钟等参数配置,信息初始化

	while(1)
	{
//		Process_Usart1Command();

//		Process_Usart2Command();

		Process_PowerKey();

		Process_IPCPWRON();
	}
}

