

#include "stm32f4xx_it.h"
#include <stdio.h>
#include  <includes.h>
#define ERR_INFO "\r\nEnter HardFault_Handler, System Halt.\r\n"

unsigned int 	CountTimes    = 0;//��ʱ
double 			OnFreq        = 0 ;//Ƶ��
unsigned char 	measureflag   = 0;//������ϵı�־
unsigned char 	PulseNumFlag  = 0;//���ڼ�¼�Ѿ����伸������--���Ƹ���
extern unsigned char PulseNUM ;//��������ĸ���

unsigned char 	PreRecvieData = 0;
unsigned char 	Reciv[20];
unsigned char 	RecivNum      = 0;
unsigned char 	IsCMDflag     = 0;
unsigned char 	UploadFlag    = 0;







/*------------------------------------------����Ƶ��-----------------------------------------------*/
void TIM4_IRQHandler(void)
{
	// �ⲿ����ﵽ50��
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		CountTimes = TIM2->CNT;//�õ�ʱ��,������ʱ
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		OnFreq = (double)15000000/(double)(CountTimes);//���Ƶ��
		TIM_Cmd(TIM4,DISABLE);
		TIM4->CNT = 0;
		//printf("FINISHED MEASURE tim2 :%d\r\n",CountTimes);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT = 0;//�رռ�ʱ,����һ�β���
		measureflag = 1;
	}
	//��15�����忪ʼ��ʱ
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
		TIM2->CNT = 0;
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		TIM_Cmd(TIM2,ENABLE);//��ʼ��ʱ��
	}
}


/*------------------------------------------��������-----------------------------------------------*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		PulseNumFlag++;
		if(PulseNumFlag == PulseNUM)
		{
			PulseNumFlag = 0;
			PulseNUM = 0;
			TIM_Cmd(TIM3,DISABLE);//�ﵽ�������֮��͹رն�ʱ����ֹͣ����
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}




