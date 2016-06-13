/*****************************************************************
*Modules: kernel.h
*Dedcription: 存放一些系统的杂项函数，比如：delay、printf、、、等等
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
#ifndef KERNEL_H
#define KERNEL_H

#include "i430type.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "msp430.h"

/* XT2 外部晶振(8Mhz)作为主时钟 */
#define XT2CLK ((double)8000000)
/**
 * @brief 使用 IAR 内置函数 __delay_cycles 进行精确延时
 * @note  XT2CLK 为系统主时钟 MCLK
 */
#define delay_us(x) __delay_cycles((long)(XT2CLK*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(XT2CLK*(double)x/1000.0)) 

void DelayMs(void);
void DelayUs(void);
void DelayS(void);

#endif
