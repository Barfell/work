/**
 * @file  msp430f149_uart.h
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
#ifndef MSP430F149_TIM_H
#define MSP430F149_TIM_H
#include "i430type.h"



typedef enum
{
	TIM_SouceClk_ACLK = 1,
	TIM_SouceClk_SMCLK,
          
        TIM_SouceClk_TACLK,
        TIM_SouceClk_INCLK
}TIM_SouceClkTypeDef;

typedef enum
{
	TIM_A = 1,
	TIM_B
}TIM_NumberTypeDef;

typedef enum
{
	TIM_Div_1 = 0x00<<6,
        TIM_Div_2 = 0x01<<6,
        TIM_Div_4 = 0x02<<6,
        TIM_Div_8 = 0x03<<6
}TIM_DivTypeDef;


#endif
