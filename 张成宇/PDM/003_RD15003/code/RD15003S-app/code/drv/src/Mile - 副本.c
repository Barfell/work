#include "Mile.h"

//#define MILE_UNIT               5.236 //接近开关每变化一次 里程的变化值5.236mm
#define MILE_UNIT               100 //接近开关每变化一次 里程的变化值5.236mm


STATIC CMileSwitchInfo  cMileSwitchInfo;
CMileRecordInfo  cMileRecordInfo;
U32 g_u32Value;
 
/************************************************************************
*Precedure  :       MileGpioInit
*Funtion  :	     里程计IO口创建
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************

************************************************************************/

STATIC VOID MileGpioInit(VOID)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	TIM_DeInit(TIM2);
//	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
//	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  // Time base configuration
//	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
//	TIM_SetCounter(TIM2, 0); 
//	TIM_Cmd(TIM2, ENABLE); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
//	TIM_TimeBaseStructure.TIM_Period = 0xffff;
//	TIM_TimeBaseStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 8;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 8;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 8;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 8;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	/* TIM enable counter */
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);

	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
	
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
	
	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	
	

}

/************************************************************************
*Precedure  :       CalculateMile
*Funtion  :	     计算行驶里程 
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/
VOID CalculateMile(VOID)
{ 
	if(cMileSwitchInfo.LastMileUnitNumber < 0)
	{
        cMileRecordInfo.MileSign = '-';
	}
    else 
	{
        cMileRecordInfo.MileSign = '+';
	}
	cMileRecordInfo.mmileage = cMileSwitchInfo.MileUnitNumber*MILE_UNIT;
	
	cMileRecordInfo.mileage = (cMileRecordInfo.mmileage/(float)1000.0);	

	g_u32Value = cMileSwitchInfo.MileUnitNumber;
}

/************************************************************************
*Precedure  :      MileDataInit
*Funtion  :	    初始里程初始化
*Parameter  :      无
*Result       :      无
*Description:       无
*************************************************************************
*LOG DATA     AUTHOR 	     ACTION
*************************************************************************
************************************************************************/																	
VOID MileDataInit(VOID)
{
    cMileSwitchInfo.LastSwitchState = 0x00;
    cMileSwitchInfo.CurrentSwitchState = 0x00;
	cMileSwitchInfo.MileUnitNumber = 0;
	cMileSwitchInfo.LastMileUnitNumber = 0;
	
    cMileRecordInfo.mmileage = 0.0;
    cMileRecordInfo.mileage = 0.0;
    cMileRecordInfo.MileSign = '+';
	
}

EXTERN BOOL g_bMileTrigger;

VOID TIM2_IRQHandler(VOID)
{
	cMileSwitchInfo.LastMileUnitNumber = cMileSwitchInfo.MileUnitNumber;
	
	cMileSwitchInfo.CurrentSwitchState = (GPIO_ReadInputData(GPIOA) & 0x000C);
	
	if(cMileSwitchInfo.CurrentSwitchState == 0x00c0)
	{
		cMileSwitchInfo.bMileState = TRUE;
	}
	else
	{
		if(cMileSwitchInfo.bMileState == TRUE)
		{
			switch(cMileSwitchInfo.CurrentSwitchState)
			{
				case 0x0000:
					if(cMileSwitchInfo.LastSwitchState == 0X0080)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}
					else if(cMileSwitchInfo.LastSwitchState == 0X0040)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;
					
				case 0x0080:
					if(cMileSwitchInfo.LastSwitchState == 0X0040)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}

					else if(cMileSwitchInfo.LastSwitchState == 0X0000)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;
					
				case 0x0040:
					if(cMileSwitchInfo.LastSwitchState == 0X0000)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}
					else if(cMileSwitchInfo.LastSwitchState == 0X0080)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;	
				default:
					break;
			}
			cMileSwitchInfo.LastSwitchState = cMileSwitchInfo.CurrentSwitchState;
			cMileSwitchInfo.bMileState = FALSE;
		}
		else if(cMileSwitchInfo.CurrentSwitchState == 0x0000)
		{
			if(cMileSwitchInfo.LastSwitchState == 0X0080)
			{
				cMileSwitchInfo.MileUnitNumber--;
			}
			else if(cMileSwitchInfo.LastSwitchState == 0X0040)
			{
				cMileSwitchInfo.MileUnitNumber++;
			}
			
		}
		
		
	}
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC3 | TIM_IT_CC4);
	
	
}

VOID MileThreadProc(VOID)
{
	cMileSwitchInfo.CurrentSwitchState = (GPIO_ReadInputData(GPIOA) & 0x00c0);
	
	if(cMileSwitchInfo.CurrentSwitchState == 0x00c0)
	{
		cMileSwitchInfo.bMileState = TRUE;
	}
	
	if(cMileSwitchInfo.bMileErrorState == TRUE)
	{
		if(cMileSwitchInfo.CurrentSwitchState == 0x0000)
		{
			cMileSwitchInfo.LastSwitchState = cMileSwitchInfo.LastSwitchStateEx;
						
			cMileSwitchInfo.MileUnitNumber = cMileSwitchInfo.MileUnitNumber + cMileSwitchInfo.Offset;
			
			if(cMileSwitchInfo.LastSwitchState == 0X0080)
			{
				cMileSwitchInfo.MileUnitNumber--;
			}
			else if(cMileSwitchInfo.LastSwitchState == 0X0040)
			{
				cMileSwitchInfo.MileUnitNumber++;
			}
		}
		cMileSwitchInfo.bMileErrorState = FALSE;
	}
	
}

VOID TIM3_IRQHandler(VOID)
{	
	cMileSwitchInfo.LastMileUnitNumber = cMileSwitchInfo.MileUnitNumber;
	
	cMileSwitchInfo.CurrentSwitchState = (GPIO_ReadInputData(GPIOA) & 0x00c0);
	
	if(cMileSwitchInfo.bMileState == TRUE)
	{
		switch(cMileSwitchInfo.CurrentSwitchState)
		{
			case 0x0000:
				if(cMileSwitchInfo.LastSwitchState == 0X0080)
				{
					cMileSwitchInfo.MileUnitNumber--;
					cMileSwitchInfo.Offset = 1;
				}
				else if(cMileSwitchInfo.LastSwitchState == 0X0040)
				{
					cMileSwitchInfo.MileUnitNumber++;
					cMileSwitchInfo.Offset = -1;
				}
				else
				{
					cMileSwitchInfo.bMileErrorState = TRUE;
					goto MILE_EXIT;
				}
				break;
				
			case 0x0080:
				if(cMileSwitchInfo.LastSwitchState == 0X0040)
				{
					cMileSwitchInfo.MileUnitNumber--;
					cMileSwitchInfo.Offset = 1;
				}

				else if(cMileSwitchInfo.LastSwitchState == 0X0000)
				{
					cMileSwitchInfo.MileUnitNumber++;
					cMileSwitchInfo.Offset = -1;
				}
				else
				{
					cMileSwitchInfo.bMileErrorState = TRUE;
					goto MILE_EXIT;
				}
				break;
				
			case 0x0040:
				if(cMileSwitchInfo.LastSwitchState == 0X0000)
				{
					cMileSwitchInfo.MileUnitNumber--;
					cMileSwitchInfo.Offset = 1;
				}
				else if(cMileSwitchInfo.LastSwitchState == 0X0080)
				{
					cMileSwitchInfo.MileUnitNumber++;
					cMileSwitchInfo.Offset = -1;
				}
				else
				{
					cMileSwitchInfo.bMileErrorState = TRUE;
					goto MILE_EXIT;
				}
				break;	
			default:
				break;
		}
		cMileSwitchInfo.LastSwitchStateEx = cMileSwitchInfo.LastSwitchState;
		cMileSwitchInfo.LastSwitchState = cMileSwitchInfo.CurrentSwitchState;

		cMileSwitchInfo.bMileState = FALSE;
MILE_EXIT:
		
		
	}
	else if(cMileSwitchInfo.CurrentSwitchState == 0x0000)
	{
		cMileSwitchInfo.LastSwitchState = cMileSwitchInfo.LastSwitchStateEx;
					
		cMileSwitchInfo.MileUnitNumber = cMileSwitchInfo.MileUnitNumber + cMileSwitchInfo.Offset;
		
		if(cMileSwitchInfo.LastSwitchState == 0X0080)
		{
			cMileSwitchInfo.MileUnitNumber--;
		}
		else if(cMileSwitchInfo.LastSwitchState == 0X0040)
		{
			cMileSwitchInfo.MileUnitNumber++;
		}
		
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_CC2);
}

VOID TIM4_IRQHandler(VOID)
{
	cMileSwitchInfo.LastMileUnitNumber = cMileSwitchInfo.MileUnitNumber;
	
	cMileSwitchInfo.CurrentSwitchState = (GPIO_ReadInputData(GPIOB) & 0x00c0);
	
	if(cMileSwitchInfo.CurrentSwitchState == 0x00c0)
	{
		cMileSwitchInfo.bMileState = TRUE;
	}
	else
	{
		if(cMileSwitchInfo.bMileState == TRUE)
		{
			switch(cMileSwitchInfo.CurrentSwitchState)
			{
				case 0x0000:
					if(cMileSwitchInfo.LastSwitchState == 0X0080)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}
					else if(cMileSwitchInfo.LastSwitchState == 0X0040)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;
					
				case 0x0080:
					if(cMileSwitchInfo.LastSwitchState == 0X0040)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}

					else if(cMileSwitchInfo.LastSwitchState == 0X0000)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;
					
				case 0x0040:
					if(cMileSwitchInfo.LastSwitchState == 0X0000)
					{
						cMileSwitchInfo.MileUnitNumber--;
					}
					else if(cMileSwitchInfo.LastSwitchState == 0X0080)
					{
						cMileSwitchInfo.MileUnitNumber++;
					}
					break;	
				default:
					break;
			}
			cMileSwitchInfo.LastSwitchState = cMileSwitchInfo.CurrentSwitchState;
			cMileSwitchInfo.bMileState = FALSE;
		}
		else if(cMileSwitchInfo.CurrentSwitchState == 0x0000)
		{
			if(cMileSwitchInfo.LastSwitchState == 0X0080)
			{
				cMileSwitchInfo.MileUnitNumber--;
			}
			else if(cMileSwitchInfo.LastSwitchState == 0X0040)
			{
				cMileSwitchInfo.MileUnitNumber++;
			}
			
		}
		
		
	}
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1 | TIM_IT_CC2);
}

VOID MileageInit(VOID)
{
    MileDataInit();
    MileGpioInit();
}
  

