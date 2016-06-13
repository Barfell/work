#include "timer.h"

STATIC U16 g_u16gTIM2Delay = 0;
STATIC U16 g_u16gTIM2Over = 0;

VOID TIM2_IRQHandler(VOID)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM2->SR &= 0xFFFE; //清除UIF标志
		g_u16gTIM2Over ++;
		if(g_u16gTIM2Over >= g_u16gTIM2Delay)		//定时结束
		{
			g_u16gTIM2Over = 0;
			g_u16gTIM2Delay = 0;
			TIM_Cmd(TIM2, DISABLE);
		}
			
	}
}

/**********************************************************************
* Procedure:	TIM_Create
* Function:		调用此函数主要完成对定时器2的初始化操作。其中包括定时器2的基本
*           	参数设置、定时器2中断设置、定时器2时钟设置、定时器2中断控制。
*           	T2的未分频工作时钟为36M。
*           	T2的当前配置为 -> 工作时钟：36M
*                             定时长度：1ms
* Parameter:	None		
* Result:		None		
* Description:	T2的时钟使能操作提到T2配置参数操作之前进行。这一点很重要，
*             	如果T2时钟使能在T2配置参数操作之后进行，就会出现T2配置参数
*             	失败的情况出现。			
* Attribute:    Hidden
***********************************************************************
* LOG	DATE			AUTHOR						ACTION
***********************************************************************
**********************************************************************/
VOID TIM_Create(VOID)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 18000;//		18000/18M=1MS,每一毫秒中断一次
	TIM_TimeBaseStructure.TIM_Prescaler = 1;//		36M/(1+1)=18M
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//初值是0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Enable the TIM2 Interrupt */ 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 Update Interrupt enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

}

/*******************************************************************************
* Function Name  : TIM_Open
* Description    : 执行定时器2设备开启操作。此操作只能在定时器2配置完成之后执行！
*                  执行完此函数后，定时器开始进行计数操作。
* Input          : 无
* Output         : 返回函数执行成功状态信息。
*******************************************************************************/
VOID TIM_Open(VOID)
{  
	/* 使能定时器2计数操作 */
	TIM_Cmd(TIM2, ENABLE); 	
}

/*******************************************************************************
* Function Name  : TIM_Close
* Description    : 执行定时器2设备关闭操作。执行完此函数后，定时器停止计数操作。
* Input          : 无
* Output         : 返回函数执行成功状态信息。
*******************************************************************************/
VOID TIM_Close(VOID)
{ 
	/* 停止定时器2计数操作 */
	TIM_Cmd(TIM2, DISABLE); 
	
}

VOID SetTimer(u16 wTimeOut)
{
	g_u16gTIM2Delay = wTimeOut;
	g_u16gTIM2Over = 0;
}

U16 GetTimer(VOID)
{
	return g_u16gTIM2Delay;
}
