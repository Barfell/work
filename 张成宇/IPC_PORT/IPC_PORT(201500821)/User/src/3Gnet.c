/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* 文件名称: 3Gnet.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 3G模块功能函数.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "command.h"
#include "power.h"
#include "3Gnet.h"
#include <stdio.h>
#include <string.h>


/*******************************************************************************
* Function Name  : Delayms
* Description    : Delayms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Delayms(u16 i)
{
	u16 n,m;
	for(n=0;n<i;n++)
	{
		for(m=0;m<5000;m++);
	}
}

/*******************************************************************************
* Function Name  : UC864_POWERON
* Description    : 3G模块UC864启动
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UC864_POWERON(void)
{
	MCU_UC864PWRON_UP();
	Delayms(1000);
	MCU_UC864PWRON_DOWN();
	printf("UC864 POWERON\r\n");
}

/*******************************************************************************
* Function Name  : UC864_RESET
* Description    : 3G模块UC864复位
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UC864_RESET(void)
{
	MCU_UC864RST_UP();
	Delayms(200);
	MCU_UC864RST_DOWN();
	printf("UC864 RESET\r\n");
}




