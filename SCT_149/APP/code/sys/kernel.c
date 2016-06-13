/**
 * @file  kernel.c
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
#include "kernel.h"
#include "msp430f149_uart.h"

/**
 * @brief 外部高速晶振作为系统的主时钟初始化函数
 * @note  初始化后时钟为 ACLK = LFXT1, MCLK = XT2, SMCLK = XT2
 * @note  LFXT1 常使用 32.768Khz, XT2 常使用 8Mhz
 */
void RCC_HSECLKInit(void)
{
    u8 i;
	/* 打开 XT2 振荡器, ACLK 默认不分频*/
	BCSCTL1 &= ~XT2OFF;
	/* MCLK 时钟源为 XT2,SMCLK时钟源为 XT2*/
	BCSCTL2|= SELM1 + SELS;
	do
	{
		/* OFIFG 位置0, 清除振荡器错误标志*/
		IFG1 &= ~OFIFG;
		/* 至少延时 50us */
		for(i=0; i<100; i++)
		{
			i = i;
		}
	}while((IFG1 & OFIFG)!=0);//如果标志位为1，则继续循环等待
	IFG1 &= ~OFIFG; 
}

/**
 * @brief 外部低速时钟作为系统的主时钟初始化函数
 * @note  初始化后时钟为 ACLK = LFXT1, MCLK = LFXT1, SMCLK = XT2
 * @note  LFXT1 常使用 32.768Khz, XT2 常使用 8Mhz
 */
void RCC_LSECLKInit(void)
{
	u8 i;
	/* MCLK 时钟源为 LFXT1, SMCLK 时钟源为 XT2 */
	//BCSCTL2|= SELM1 + SELM0 + SELS;
        BCSCTL2|= SELM1 + SELM0;
	do
	{
		/* OFIFG 位置0, 清除振荡器错误标志*/
		IFG1 &= ~OFIFG;
		/* 至少延时 50us */
		for(i=0; i<100; i++)
		{
			i = i;
		}
		
	}while((IFG1 & OFIFG)!=0);//如果标志位1，则继续循环等待
	IFG1 &= ~OFIFG; 
}

/*
		 |u8RSEL|u8DCO 	|  MOD 	| DCOR  |  Mhz 		|
	DCO03|  0	|	3	|	0	|	0	|	0.13	|
	DCO13|  1	|	3	|	0	|	0	|	0.18	|
	DCO23|  2	|	3	|	0	|	0	|	0.28	|
	DCO33|  3	|	3	|	0	|	0	|	0.47	|
	DCO43|  4	|	3	|	0	|	0	|	0.75	|
	DCO53|  5	|	3	|	0	|	0	|	1.3		|
	DCO63|  6	|	3	|	0	|	0	|	2.0		|
	DCO73|  7	|	3	|	0	|	0	|	3.2		|
	DCO47|  4	|	7	|	0	|	0	|	x		|
	DCO77|  7	|	7	|	0	|	0	|	4.9		|
 */
/**
 * @biref 内部 DCO 时钟作为系统主时钟的初始化函数
 * @param u8RSEL DCO内部电阻选择(0~7)
 * @param u8DCO  DCO频段选择(0~7)
 * @note  算出的频率只是大概值,会有误差,多使用 DCO73项
 * @note  初始化后时钟为 ACLK = LFXT1, MCLK = DCO, SMCLK = DCO
 */
void RCC_DCOCLKInit(u8 u8RSEL, u8 u8DCO)
{
	u8 u8MOD = 0;
	u8 u8DCOx = u8DCO << 5;
	/* DCO 频段*/
	DCOCTL = u8DCOx + u8MOD;
	/* ACLK 不分频,选择内部 DCO 电阻*/
	BCSCTL1 = DIVA_0 + u8RSEL;
	/* SELM 选择1,即 MCLK 时钟源为 DCO ,DIVM 选择0 不分频,DIVS 选择0,不分频*/
	BCSCTL2 = SELM_1 + DIVM_0 + DIVS_0;
}

/**
 * @brief 软件延时,8MHZ下
 * @param nms 延时时间
 */
void delay_ms_soft(u16 nms)
{
    u16 i,j;
    for( i=0; i<nms; i++ )
    {
        for(j=0;j<1141;j++);
    }
}

/**
 * @brief 软件延时,8MHZ下
 * @param nms 延时时间
 */
void delay_us_soft(u16 nus)
{
    u16 i,j;
    for( i=0; i<nus; i++ )
    {
        for(j=0;j<120;j++);
    }
}


////使用printf标准函数需要以下函数支持
//int putchar( int c )//注意不要改参数的类型和返回值的类型，否则printf调用是就有问题了。
//{        
//  if (c == '\n') 
//  { 
//    UART_SendByte(UART_0,'\r');
//  }
//  UART_SendByte(UART_0,c);
//  return c;
//}


#ifdef SERIAL_USE_PORT0
int putchar( int c )//注意不要改参数的类型和返回值的类型，否则printf调用是就有问题了。
{        
  UART_SendByte(UART_0,c);
  while((IFG1&UTXIFG0)==0);
  return c;
}
#endif

#ifdef SERIAL_USE_PORT1
int putchar( int c )//注意不要改参数的类型和返回值的类型，否则printf调用是就有问题了。
{        
  UART_SendByte(UART_1,c);
  while((IFG2&UTXIFG1)==0);
  return c;
}
#endif

