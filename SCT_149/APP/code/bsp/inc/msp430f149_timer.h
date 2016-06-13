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
	TimerSourceA_TACLK = TASSEL_0,
	TimerSourceA_ACLK = TASSEL_1,
	TimerSourceA_MCLK = TASSEL_2,
	TimerSourceA_INCLK = TASSEL_3,
        
        TimerSourceB_TBCLK = TBSSEL_0,
	TimerSourceB_ACLK = TBSSEL_1,
	TimerSourceB_MCLK = TBSSEL_2,
	TimerSourceB_INCLK = TBSSEL_3
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
	TimerPWMMode_0 = OUTMOD_0,
	TimerPWMMode_1 = OUTMOD_1,
	TimerPWMMode_2 = OUTMOD_2,
	TimerPWMMode_3 = OUTMOD_3,
	TimerPWMMode_4 = OUTMOD_4,
	TimerPWMMode_5 = OUTMOD_5,
	TimerPWMMode_6 = OUTMOD_6,
	TimerPWMMode_7 = OUTMOD_7
}TimerPWMMode_TypeDef;

typedef enum
{
	TimerOutputPin_P11 = 1,
	TimerOutputPin_P12,
	TimerOutputPin_P13,
	TimerOutputPin_P15,
	TimerOutputPin_P16,
	TimerOutputPin_P17,
        
        
        TimerOutputPin_P41,
        TimerOutputPin_P43,
        TimerOutputPin_P44,
        TimerOutputPin_P45,
        TimerOutputPin_P46,
}TimerOutputPin_TypeDef;

typedef enum
{
	TimerEdge_NONE = CM_0,
	TimerEdge_RISE = CM_1,
	TimerEdge_DOWN = CM_2,
	TimerEdge_BOTH = CM_3,
}TimerEdge_TypeDef;

//typedef enum
//{
//	
//}TimerCount_TypeDef;


void TimerA_SetTimerMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,u16 u16Count);
void TimerA_SetPWMMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,TimerPWMMode_TypeDef TimerPWMMode, TimerOutputPin_TypeDef TimerOutputPin, u16 u16Period, u16 u16Duty);
void TimerB_SetPWMMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,TimerPWMMode_TypeDef TimerPWMMode, TimerOutputPin_TypeDef TimerOutputPin, u16 u16Period, u16 u16Duty);
void TimerA_CaptureMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde, TimerOutputPin_TypeDef TimerOutputPin, TimerEdge_TypeDef TimerEdge);
void TimerA_TACLK(void);
#endif
