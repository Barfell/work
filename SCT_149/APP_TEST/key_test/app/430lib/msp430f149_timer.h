/**
 * @file  msp430f149_timer.h
 * @author  wf
 * @version V1.0
 * @date  2015-11-20
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-20
 * +  file create
 */
#ifndef MSP430F149_TIMER_H
#define MSP430F149_TIMER_H
#include "i430type.h"


typedef enum
{
	TimerNumber_A = 1,
	TimerNumber_B
}TimerNumber_TypeDef;

typedef enum
{
	TimerSource_TACLK = TASSEL_0,
	TimerSource_ACLK = TASSEL_1,
	TimerSource_MCLK = TASSEL_2,
	TimerSource_INCLK = TASSEL_3
}TimerSource_TypeDef;

typedef enum
{
	TimerDivde_0 = ID_0,
	TimerDivde_2 = ID_1,
	TimerDivde_4 = ID_2,
	TimerDivde_8 = ID_3
}TimerDivde_TypeDef;

typedef enum
{
	TimerPWM_0 = OUTMOD_0,
	TimerPWM_1 = OUTMOD_1,
	TimerPWM_2 = OUTMOD_2,
	TimerPWM_3 = OUTMOD_3,
	TimerPWM_4 = OUTMOD_4,
	TimerPWM_5 = OUTMOD_5,
	TimerPWM_6 = OUTMOD_6,
	TimerPWM_7 = OUTMOD_7
}TimerPWM_TypeDef;

typedef enum
{
	TimerOutputPin_P11 = 1,
	TimerOutputPin_P12,
	TimerOutputPin_P13,
	TimerOutputPin_P15,
	TimerOutputPin_P16,
	TimerOutputPin_P17
}TimerOutputPin_TypeDef;
//typedef enum
//{
//	
//}TimerCount_TypeDef;


void TimerA_SetTimerMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,u16 u16Count);


#endif
