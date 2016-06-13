/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* �ļ�����: power.c
* ��������: Dyj
* ����汾: V0.0.1
* ��������: 06/14/2012
* ��������: ϵͳ��Դ����.
*******************************************************************************/


#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "power.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
* Function Name  : Process_PowerKey
* Description    : �����Դ����״̬
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_PowerKey(void)
{	
	if(SystemPowerManage.PowerKeyTime>100*10)		//100ms���һ��
	{
		SystemPowerManage.PowerKeyTime = 0;
		if(GET_KEY())
		{
			SystemPowerManage.PowerKeyCount++;
		}
		else
			SystemPowerManage.PowerKeyCount=0;
					
		if(SystemPowerManage.PowerKeyCount>3*10)	//��������3s�������ػ�����
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
* Description    : ���������Դʹ�ܵ�ѹ����POWER_ON״̬
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Process_IPCPWRON(void)
{	
	if(SystemPowerManage.IPC_POWERONTime>100*10)	//100ms���һ��
	{
		SystemPowerManage.IPC_POWERONTime = 0;
		if(Get_IPC_POWERON())
		{
			SystemPowerManage.IPC_POWERONCount++;
		}
		else
			SystemPowerManage.IPC_POWERONCount=0;
					
		if(SystemPowerManage.IPC_POWERONCount>5*10)	//����5s������ŵ�ѹΪ�ߵ�ƽʱ�����ػ�����
		{
			CLOSE_PWR();
			CLOSE_IPCPWR();
			LED_OFF();
			printf("POWERON DOWN\r\n");
		}
	}
}

