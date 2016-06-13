/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* 文件名称: power.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 系统电源管理.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "power.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
* Function Name  : Process_PowerKey
* Description    : 处理电源按键状态
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_PowerKey(void)
{	
	if(SystemPowerManage.PowerKeyTime>100*10)		//100ms检测一次
	{
		SystemPowerManage.PowerKeyTime = 0;
		if(GET_KEY())
		{
			SystemPowerManage.PowerKeyCount++;
		}
		else
			SystemPowerManage.PowerKeyCount=0;
					
		if(SystemPowerManage.PowerKeyCount>3*10)	//连续按键3s后启动关机进程
		{
			CLOSE_PWR();
			CLOSE_IPCPWR();
			LED_OFF();
			printf("KEY DOWN\r\n");
		}
	}
}

/*******************************************************************************
* Function Name  : Process_IPCPWRON
* Description    : 工控主板电源使能电压引脚POWER_ON状态
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_IPCPWRON(void)
{	
	if(SystemPowerManage.IPC_POWERONTime>100*10)	//100ms检测一次
	{
		SystemPowerManage.IPC_POWERONTime = 0;
		if(Get_IPC_POWERON())
		{
			SystemPowerManage.IPC_POWERONCount++;
		}
		else
			SystemPowerManage.IPC_POWERONCount=0;
					
		if(SystemPowerManage.IPC_POWERONCount>5*10)	//连续5s检测引脚电压为高电平时启动关机进程
		{
			CLOSE_PWR();
			CLOSE_IPCPWR();
			LED_OFF();
			printf("POWERON DOWN\r\n");
		}
	}
}

