#include "timer.h"

STATIC U16 g_u16gTIM2Delay = 0;
STATIC U16 g_u16gTIM2Over = 0;

VOID TIM2_IRQHandler(VOID)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM2->SR &= 0xFFFE; //���UIF��־
		g_u16gTIM2Over ++;
		if(g_u16gTIM2Over >= g_u16gTIM2Delay)		//��ʱ����
		{
			g_u16gTIM2Over = 0;
			g_u16gTIM2Delay = 0;
			TIM_Cmd(TIM2, DISABLE);
		}
			
	}
}

/**********************************************************************
* Procedure:	TIM_Create
* Function:		���ô˺�����Ҫ��ɶԶ�ʱ��2�ĳ�ʼ�����������а�����ʱ��2�Ļ���
*           	�������á���ʱ��2�ж����á���ʱ��2ʱ�����á���ʱ��2�жϿ��ơ�
*           	T2��δ��Ƶ����ʱ��Ϊ36M��
*           	T2�ĵ�ǰ����Ϊ -> ����ʱ�ӣ�36M
*                             ��ʱ���ȣ�1ms
* Parameter:	None		
* Result:		None		
* Description:	T2��ʱ��ʹ�ܲ����ᵽT2���ò�������֮ǰ���С���һ�����Ҫ��
*             	���T2ʱ��ʹ����T2���ò�������֮����У��ͻ����T2���ò���
*             	ʧ�ܵ�������֡�			
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

	TIM_TimeBaseStructure.TIM_Period = 18000;//		18000/18M=1MS,ÿһ�����ж�һ��
	TIM_TimeBaseStructure.TIM_Prescaler = 1;//		36M/(1+1)=18M
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//��ֵ��0
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
* Description    : ִ�ж�ʱ��2�豸�����������˲���ֻ���ڶ�ʱ��2�������֮��ִ�У�
*                  ִ����˺����󣬶�ʱ����ʼ���м���������
* Input          : ��
* Output         : ���غ���ִ�гɹ�״̬��Ϣ��
*******************************************************************************/
VOID TIM_Open(VOID)
{  
	/* ʹ�ܶ�ʱ��2�������� */
	TIM_Cmd(TIM2, ENABLE); 	
}

/*******************************************************************************
* Function Name  : TIM_Close
* Description    : ִ�ж�ʱ��2�豸�رղ�����ִ����˺����󣬶�ʱ��ֹͣ����������
* Input          : ��
* Output         : ���غ���ִ�гɹ�״̬��Ϣ��
*******************************************************************************/
VOID TIM_Close(VOID)
{ 
	/* ֹͣ��ʱ��2�������� */
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
