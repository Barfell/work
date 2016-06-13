

#include "stm32f4xx_it.h"
#include <stdio.h>
#include  <includes.h>
#define ERR_INFO "\r\nEnter HardFault_Handler, System Halt.\r\n"

unsigned int 	CountTimes    = 0;//计时
double 			OnFreq        = 0 ;//频率
unsigned char 	measureflag   = 0;//测量完毕的标志
unsigned char 	PulseNumFlag  = 0;//用于记录已经发射几个脉冲--控制个数
extern unsigned char PulseNUM ;//发射脉冲的个数

unsigned char 	PreRecvieData = 0;
unsigned char 	Reciv[20];
unsigned char 	RecivNum      = 0;
unsigned char 	IsCMDflag     = 0;
unsigned char 	UploadFlag    = 0;







/*------------------------------------------测量频率-----------------------------------------------*/
void TIM4_IRQHandler(void)
{
	// 外部脉冲达到50个
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		CountTimes = TIM2->CNT;//得到时间,结束计时
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		OnFreq = (double)15000000/(double)(CountTimes);//算出频率
		TIM_Cmd(TIM4,DISABLE);
		TIM4->CNT = 0;
		//printf("FINISHED MEASURE tim2 :%d\r\n",CountTimes);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT = 0;//关闭计时,等下一次测量
		measureflag = 1;
	}
	//第15个脉冲开始计时
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
		TIM2->CNT = 0;
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		TIM_Cmd(TIM2,ENABLE);//开始计时了
	}
}


/*------------------------------------------激励脉冲-----------------------------------------------*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		PulseNumFlag++;
		if(PulseNumFlag == PulseNUM)
		{
			PulseNumFlag = 0;
			PulseNUM = 0;
			TIM_Cmd(TIM3,DISABLE);//达到脉冲个数之后就关闭定时器，停止发射
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}




