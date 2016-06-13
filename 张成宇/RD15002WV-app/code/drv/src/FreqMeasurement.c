#include "FreqMeasurement.h"
#include "bsp_io_control.h"
unsigned char PulseNUM = 0;//�����������

//����λ����
double CalDisplacement(double Freq,double T)
{
	double G = 0.016457;
	double TM = 0.000330;
	double TB = 0.415;//Model:4450-3mm
	
	
	double DigitsPRE = 0,DigitsNEXT = 0;
	double Displacement = 0;
	DigitsPRE  = (1175.800000*1175.800000)/1000;
	DigitsNEXT = (Freq*Freq)/1000;
	Displacement = (DigitsNEXT-DigitsPRE)*G + (T - 26.300000)*((DigitsNEXT * TM) +TB)*G;
	return Displacement;
}


//ʹ��ǰ��ʼ��
void FreqModuleInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|
						RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	/*-----------------------VW_TX PB0---------------------------*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);//TIM3_CH3--PWM--pb0(����Դ)  tim3
	/*-----------------------VW_TRCN-------------------------*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	/*-----------------------POWER_SW------------------------*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_2;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/*-----------------------VW_SW--------------------------*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	/*-----------------------VW_RX PE0--------------------------*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_TIM4);//����
	//tran
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//CH3
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,DISABLE);//�رգ�׼���÷�������
	//count
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 279;		 //   35
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2,DISABLE);//һֱ����
	//measure
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
	TIM_TimeBaseStructure.TIM_Period = 114;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_SelectInputTrigger(TIM4,TIM_TS_ETRF);
	TIM_ETRClockMode2Config(TIM4,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x2);//�ⲿʱ������,ģʽ2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_Pulse = 15;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_CC1|TIM_IT_Update,ENABLE);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update); 
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM4->CNT = 0;
	TIM_Cmd(TIM4,DISABLE);//��ʼ��֮���ǹرյ�
	//nvic
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//����Ƶ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//����̶�������pwm
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��������һ��Ƶ��һ������������
//freq:Ƶ��
//num:����
void TranPulse(unsigned int freq,unsigned char num)
{
	OutPutFreqSet(freq);
	PulseNUM = num;//�������
	TIM3->CNT = 0;// ��������
	if(num == 0)
	{TIM_Cmd(TIM3,DISABLE);}
	else
	{TIM_Cmd(TIM3,ENABLE);}//����һ�����巢��
}

double Measure(void)
{
//	OS_ERR err;
	U32 u32Tick;
	S32 s32Tick;
	OnFreq = 0;
	TIM_Cmd(TIM4,ENABLE);
	/*
	while(measureflag == 0)//�ȴ��������
		{
			OSTimeDlyHMSM(0,0,0,1,OS_OPT_TIME_DLY,&err);
			OverTime++;
			if(OverTime > 300)//300ms��ʱ
			{OverTime = 0;break;}
		}
		*/
	
	u32Tick = GetTickCount();
	while(measureflag == 0)
	{
		s32Tick = GetTickCount() - u32Tick;
		
		if(s32Tick > 100)
		{
			break;
		}
	}
	
	measureflag = 0;//������Ϻ����״̬
	TIM_Cmd(TIM4,DISABLE);
	TIM4->CNT = 0;
	return OnFreq;
}
//��ȡĳ��ͨ����Ƶ��
double GetFreq(unsigned char ch)
{
//	OS_ERR		err;
	SW_VW(ch);//ѡ��ͨ��
	
	
	SW_VW_TRCN(0);
	TranPulse(4000,10);
	DelayMs(2);
//	OSTimeDlyHMSM(0,0,0,2,OS_OPT_TIME_DLY,&err);
	TranPulse(35000,10);
	DelayMs(4);
//	OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_DLY,&err);
	TranPulse(3000,10);
	DelayMs(4);
//	OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_DLY,&err);
	TranPulse(2500,10);
	DelayMs(4);
//	OSTimeDlyHMSM(0,0,0,4,OS_OPT_TIME_DLY,&err);
	TranPulse(2000,10);
	DelayMs(8);
//	OSTimeDlyHMSM(0,0,0,8,OS_OPT_TIME_DLY,&err);
	TranPulse(1500,10);
	DelayMs(8);
//	OSTimeDlyHMSM(0,0,0,8,OS_OPT_TIME_DLY,&err);
	TranPulse(1000,10);
	DelayMs(12);
//	OSTimeDlyHMSM(0,0,0,12,OS_OPT_TIME_DLY,&err);
	TranPulse(500,10);
	DelayMs(20);
//	OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_DLY,&err);
	SW_VW_TRCN(1);
	DelayMs(20);
//	OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_DLY,&err);//ͣ�٣��ȴ�������������
	return Measure();
}



//freq:�����Ƶ�ʣ���λ��hz
void OutPutFreqSet(unsigned int freq)
{
	unsigned int N = 0;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//1282hz----84Mhz
	if( (freq>1282) && (freq<84000000))
		{
			N = 42000000/freq;
			TIM_TimeBaseStructure.TIM_Prescaler = N-1;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
			TIM_TimeBaseStructure.TIM_Period = 1;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_Pulse = 1;
		}
//128hz----1282hz
	else if( (freq <= 1282) && (freq > 128) )
		{
			N = 4200000/freq;
			TIM_TimeBaseStructure.TIM_Prescaler = N-1;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
			TIM_TimeBaseStructure.TIM_Period = 19;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_Pulse = 10;
		}
//С��128hz
		else if(freq <= 128)
		{
			N = 42000/freq;
			TIM_TimeBaseStructure.TIM_Prescaler = N-1;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
			TIM_TimeBaseStructure.TIM_Period = 1999;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_Pulse = 1000;
		}
//���ֻ����84Mhz
		else if(freq > 84000000)
		{
			TIM_TimeBaseStructure.TIM_Prescaler = 0;
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
			TIM_TimeBaseStructure.TIM_Period = 1;
			TIM_TimeBaseStructure.TIM_ClockDivision = 0;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
			TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
			TIM_OCInitStructure.TIM_Pulse = 1;
		}
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
}


unsigned int CountTimes = 0;//��ʱ
double OnFreq ;//Ƶ��
unsigned char measureflag = 0;//������ϵı�־
unsigned char PulseNumFlag = 0;//���ڼ�¼�Ѿ����伸������--���Ƹ���
extern unsigned char PulseNUM;//��������ĸ���


/*------------------------------------------����Ƶ��-----------------------------------------------*/
void TIM4_IRQHandler(void)
{
	// �ⲿ����ﵽ100��
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		CountTimes = TIM2->CNT;//�õ�ʱ��,������ʱ
		OnFreq = (double)30000000/(double)(CountTimes);//���Ƶ��
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT = 0;//�رռ�ʱ,����һ�β���
		measureflag = 1;
		
	}
	//��һ�����忪ʼ��ʱ
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		TIM2->CNT = 0;
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
