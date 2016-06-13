/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* �ļ�����: main.c
* ��������: Dyj
* ����汾: V0.0.1
* ��������: 06/14/2012
* ��������: ������.
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
	System_Init();                                          //ϵͳʱ�ӵȲ�������,��Ϣ��ʼ��

	while(1)
	{
//		Process_Usart1Command();

//		Process_Usart2Command();

		Process_PowerKey();

		Process_IPCPWRON();
	}
}

