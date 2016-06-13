/******************** (C) COPYRIGHT 2010 SystemII ********************
* 文件名称: stm32f10x_it.c
* 程序作者: Dyj
* 程序版本: V0.0.1
* 编制日期: 06/14/2012
* 功能描述: 中断入口函数
*******************************************************************************/

/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

//#define DEBUG_IT

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys_init.h"
#include "usart.h"
#include "command.h"
#include "power.h"
#include "3Gnet.h"
#include <stdio.h>
#include <string.h>

SystemPowerManageS  SystemPowerManage;

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    #ifdef DEBUG_IT

    #endif
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
    #ifdef DEBUG_IT

    #endif
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
    #ifdef DEBUG_IT

    #endif
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
    #ifdef DEBUG_IT

    #endif
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
    #ifdef DEBUG_IT

    #endif
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*void SysTick_Handler(void)
{
}*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
/**
  * @}
  */ 


/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External lines 0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void) //检测是否产生下降沿中断请求
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		printf("RESET\r\n");
		UC864_RESET();
    	EXTI_ClearITPendingBit(EXTI_Line1);		
	}
}


void EXTI15_10_IRQHandler(void) //检测是否产生下降沿中断请求
{
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
		printf("rain sensor toggle\r\n");
    	EXTI_ClearITPendingBit(EXTI_Line12);
	}
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    :系统时钟，一般调教到0.1MS中断一次
*******************************************************************************/
void SysTick_Handler(void)
{   
	SystemPowerManage.PowerKeyTime++;
	SystemPowerManage.IPC_POWERONTime++;
}


/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.  10ms 定时	
                 用于检测是否有按键按下,响蜂响器,和注册码过期时状态
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)		
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//向上计数中断溢出	
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清标志
        
        
    }
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.    20ms 定时
                  用于控制各种工作模式正常工作时指示灯的闪烁	
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)		
{
/*
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//向上计数中断溢出	
	{
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		//清标志
       
	}
*/
}


/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	
		Usart1Command.Buf1[Usart1Command.In1++] = USART_ReceiveData(USART1);
//		Usart1Command.Count1 ++;
		if(Usart1Command.In1 >= Usart1Command_Buf_Size)Usart1Command.In1 = 0;
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  	{
        Usart2Command.Buf2[Usart2Command.In2++] = USART_ReceiveData(USART2);
//		Usart2Command.Count2 ++;
		if(Usart2Command.In2 >= Usart2Command_Buf_Size)Usart2Command.In2 = 0;
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
  	}

}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  	{
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
  	}
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{

}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
