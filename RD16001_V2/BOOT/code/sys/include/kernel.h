/**
 * @file  kernel.h
 * @author  wf
 * @version V1.0
 * @date  2015-11-18
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-18
 * +  file create
 */
#ifndef KERNEL_H
#define KERNEL_H
#include "i430type.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


/**************************************************************
板子的系统配置：
1.传感器类型
2.COMUNICATION
3.
4.
***************************************************************/

/*----------------传感器类型----------------*/
//#define SENSOR_VOLTAGE
//#define SENSOR_VW
//#define SENSOR_CURENT
#define SENSOR_RESISTENCE

/*-----------------COMUNICATION-------------*/
#define SERIAL_USE_PORT0
//#define SERIAL_USE_PORT1  //485 232_uart1
//#define COMUNICATION_ZIGBEE



/**************************************************************/


/* XT2 外部晶振(8Mhz)作为主时钟 */
#define XT2CLK ((double)8000000)
/* XT1 外部低速晶振作为主时钟 */
#define XT1CLK ((double)32768)
/* DCO 外部低速晶振作为主时钟 */
#define DCOCLK ((double)3200000)

/**
 * @brief 使用 IAR 内置函数 __delay_cycles 进行精确延时
 * @note  XT2CLK 为系统主时钟 MCLK
 */
#define delay_us(x) __delay_cycles((long)(XT2CLK*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(XT2CLK*(double)x/1000.0)) 

/**
 * @brief 使用 IAR 内置函数 __delay_cycles 进行精确延时
 * @note  XT1CLK 为系统主时钟 MCLK
 */
#define XT1_delay_us(x) __delay_cycles((long)(XT1CLK*(double)x/1000000.0)) 
#define XT1_delay_ms(x) __delay_cycles((long)(XT1CLK*(double)x/1000.0)) 

/**
 * @brief 使用 IAR 内置函数 __delay_cycles 进行精确延时
 * @note  DCOCLK 为系统主时钟 MCLK
 */
#define DCO_delay_us(x) __delay_cycles((long)(DCOCLK*(double)x/1000000.0)) 
#define DCO_delay_ms(x) __delay_cycles((long)(DCOCLK*(double)x/1000.0)) 

void RCC_HSECLKInit(void);
void RCC_LSECLKInit(void);
void RCC_DCOCLKInit(u8 u8RSEL, u8 u8DCO);

void delay_ms_soft(u16 nms);
void delay_us_soft(u16 nus);


#endif
