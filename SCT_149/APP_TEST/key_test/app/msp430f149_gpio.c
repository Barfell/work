/**
 * @file  msp430f149_gpio.c
 * @author  wf
 * @version V1.0
 * @date  2015-11-19
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-19
 * +  file create
 */
#include "msp430f149_gpio.h"
/****************************
 	| SEL 	| DIR 	| OUT 	|
 0	| IO	| IN 	| 0 	|
 1	| AL 	| OUT 	| 1 	|
 ***************************/
/**
 * @brief 设置 GPIO 为普通模式并输出高电平
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinOutputHigh(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		/* SEL 置0, DIR 置1, OUT 置1 */
		case GPIO_1:
			P1SEL &= ~GPIO_Pin;
			P1DIR |= GPIO_Pin;
			P1OUT |= GPIO_Pin;
			break;
		case GPIO_2:
			P2SEL &= ~GPIO_Pin;
			P2DIR |= GPIO_Pin;
			P2OUT |= GPIO_Pin;
			break;
		case GPIO_3:
			P3SEL &= ~GPIO_Pin;
			P3DIR |= GPIO_Pin;
			P3OUT |= GPIO_Pin;
			break;
		case GPIO_4:
			P4SEL &= ~GPIO_Pin;
			P4DIR |= GPIO_Pin;
			P4OUT |= GPIO_Pin;
			break;
		case GPIO_5:
			P5SEL &= ~GPIO_Pin;
			P5DIR |= GPIO_Pin;
			P5OUT |= GPIO_Pin;
			break;
		case GPIO_6:
			P6SEL &= ~GPIO_Pin;
			P6DIR |= GPIO_Pin;
			P6OUT |= GPIO_Pin;
			break;
		default :
			break;
	}
}

/**
 * @brief 设置 GPIO 为普通模式并输出低电平
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinOutputLow(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		/* SEL 置0, DIR 置1, OUT 置0 */
		case GPIO_1:
			P1SEL &= ~GPIO_Pin;
			P1DIR |= GPIO_Pin;
			P1OUT &= ~GPIO_Pin;
			break;
		case GPIO_2:
			P2SEL &= ~GPIO_Pin;
			P2DIR |= GPIO_Pin;
			P2OUT &= ~GPIO_Pin;
			break;
		case GPIO_3:
			P3SEL &= ~GPIO_Pin;
			P3DIR |= GPIO_Pin;
			P3OUT &= ~GPIO_Pin;
			break;
		case GPIO_4:
			P4SEL &= ~GPIO_Pin;
			P4DIR |= GPIO_Pin;
			P4OUT &= ~GPIO_Pin;
			break;
		case GPIO_5:
			P5SEL &= ~GPIO_Pin;
			P5DIR |= GPIO_Pin;
			P5OUT &= ~GPIO_Pin;
			break;
		case GPIO_6:
			P6SEL &= ~GPIO_Pin;
			P6DIR |= GPIO_Pin;
			P6OUT &= ~GPIO_Pin;
			break;
		default :
			break;
	}
}

/**
 * @brief GPIO 初始化函数
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin, GPIO_ModeTypeDef GPIO_Mode)
{
	if(GPIO_Mode == GPIO_Mode_IN)
	{
		switch(GPIOx)
		{
			case GPIO_1:
				P1SEL &= ~GPIO_Pin;
				P1DIR &= ~GPIO_Pin;
				break;
			case GPIO_2:
				P2SEL &= ~GPIO_Pin;
				P2DIR &= ~GPIO_Pin;
				break;
			case GPIO_3:
				P3SEL &= ~GPIO_Pin;
				P3DIR &= ~GPIO_Pin;
				break;
			case GPIO_4:
				P4SEL &= ~GPIO_Pin;
				P4DIR &= ~GPIO_Pin;
				break;
			case GPIO_5:
				P5SEL &= ~GPIO_Pin;
				P5DIR &= ~GPIO_Pin;
				break;
			case GPIO_6:
				P6SEL &= ~GPIO_Pin;
				P6DIR &= ~GPIO_Pin;
				break;
			default :
				break;
		}
	}
	if(GPIO_Mode == GPIO_Mode_Out)
	{
		switch(GPIOx)
		{
			case GPIO_1:
				P1SEL &= ~GPIO_Pin;
				P1DIR |= GPIO_Pin;
				break;
			case GPIO_2:
				P2SEL &= ~GPIO_Pin;
				P2DIR |= GPIO_Pin;
				break;
			case GPIO_3:
				P3SEL &= ~GPIO_Pin;
				P3DIR |= GPIO_Pin;
				break;
			case GPIO_4:
				P4SEL &= ~GPIO_Pin;
				P4DIR |= GPIO_Pin;
				break;
			case GPIO_5:
				P5SEL &= ~GPIO_Pin;
				P5DIR |= GPIO_Pin;
				break;
			case GPIO_6:
				P6SEL &= ~GPIO_Pin;
				P6DIR |= GPIO_Pin;
				break;
			default :
				break;
		}
	}
	if(GPIO_Mode == GPIO_Mode_AFIN)
	{
		switch(GPIOx)
		{
			case GPIO_1:
				P1SEL |= GPIO_Pin;
				P1DIR &= ~GPIO_Pin;
				break;
			case GPIO_2:
				P2SEL |= GPIO_Pin;
				P2DIR &= ~GPIO_Pin;
				break;
			case GPIO_3:
				P3SEL |= GPIO_Pin;
				P3DIR &= ~GPIO_Pin;
				break;
			case GPIO_4:
				P4SEL |= GPIO_Pin;
				P4DIR &= ~GPIO_Pin;
				break;
			case GPIO_5:
				P5SEL |= GPIO_Pin;
				P5DIR &= ~GPIO_Pin;
				break;
			case GPIO_6:
				P6SEL |= GPIO_Pin;
				P6DIR &= ~GPIO_Pin;
				break;
			default :
				break;
		}
	}
	if(GPIO_Mode == GPIO_Mode_AFOUT)
	{
		switch(GPIOx)
		{
			case GPIO_1:
				P1SEL |= GPIO_Pin;
				P1DIR |= GPIO_Pin;
				break;
			case GPIO_2:
				P2SEL |= GPIO_Pin;
				P2DIR |= GPIO_Pin;
				break;
			case GPIO_3:
				P3SEL |= GPIO_Pin;
				P3DIR |= GPIO_Pin;
				break;
			case GPIO_4:
				P4SEL |= GPIO_Pin;
				P4DIR |= GPIO_Pin;
				break;
			case GPIO_5:
				P5SEL |= GPIO_Pin;
				P5DIR |= GPIO_Pin;
				break;
			case GPIO_6:
				P6SEL |= GPIO_Pin;
				P6DIR |= GPIO_Pin;
				break;
			default :
				break;
		}
	}
	if(GPIO_Mode == GPIO_Mode_AF)
	{
		switch(GPIOx)
		{
			case GPIO_1:
				P1SEL |= GPIO_Pin;
				break;
			case GPIO_2:
				P2SEL |= GPIO_Pin;
				break;
			case GPIO_3:
				P3SEL |= GPIO_Pin;
				break;
			case GPIO_4:
				P4SEL |= GPIO_Pin;
				break;
			case GPIO_5:
				P5SEL |= GPIO_Pin;
				break;
			case GPIO_6:
				P6SEL |= GPIO_Pin;
				break;
			default :
				break;
		}
	}
}

/**
 * @brief 设置 GPIO 作为输入,仅改变 IO 方向,不改变 IO 工作模式
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinInput(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		case GPIO_1:
			P1DIR &= ~GPIO_Pin;
			break;
		case GPIO_2:
			P2DIR &= ~GPIO_Pin;
			break;
		case GPIO_3:
			P3DIR &= ~GPIO_Pin;
			break;
		case GPIO_4:
			P4DIR &= ~GPIO_Pin;
			break;
		case GPIO_5:
			P5DIR &= ~GPIO_Pin;
			break;
		case GPIO_6:
			P6DIR &= ~GPIO_Pin;
			break;
		default :
			break;
	}
}

/**
 * @brief 设置 GPIO 作为输出,仅改变 IO 口方向,不改变 IO 口工作模式
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinOutput(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		case GPIO_1:
			P1DIR |= GPIO_Pin;
			break;
		case GPIO_2:
			P2DIR |= GPIO_Pin;
			break;
		case GPIO_3:
			P3DIR |= GPIO_Pin;
			break;
		case GPIO_4:
			P4DIR |= GPIO_Pin;
			break;
		case GPIO_5:
			P5DIR |= GPIO_Pin;
			break;
		case GPIO_6:
			P6DIR |= GPIO_Pin;
			break;
		default :
			break;
	}
}

void GPIO_SetPinHigh(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	
	switch(GPIOx)
	{
		case GPIO_1:
			P1OUT &= ~GPIO_Pin;
			break;
		case GPIO_2:
			P2OUT &= ~GPIO_Pin;
			break;
		case GPIO_3:
			P3OUT &= ~GPIO_Pin;
			break;
		case GPIO_4:
			P4OUT &= ~GPIO_Pin;
			break;
		case GPIO_5:
			P5OUT &= ~GPIO_Pin;
			break;
		case GPIO_6:
			P6OUT &= ~GPIO_Pin;
			break;
		default :
			break;
	}
}
void GPIO_SetPinLow(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		case GPIO_1:
			P1OUT |= GPIO_Pin;
			break;
		case GPIO_2:
			P2OUT |= GPIO_Pin;
			break;
		case GPIO_3:
			P3OUT |= GPIO_Pin;
			break;
		case GPIO_4:
			P4OUT |= GPIO_Pin;
			break;
		case GPIO_5:
			P5OUT |= GPIO_Pin;
			break;
		case GPIO_6:
			P6OUT |= GPIO_Pin;
			break;
		default :
			break;
	}
}
/**
 * @brief 设置 GPIO 作为普通模式,仅改变 IO 工作模式, 不改变 IO 方向
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinDefault(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		case GPIO_1:
			P1SEL &= ~GPIO_Pin;
			break;
		case GPIO_2:
			P2SEL &= ~GPIO_Pin;
			break;
		case GPIO_3:
			P3SEL &= ~GPIO_Pin;
			break;
		case GPIO_4:
			P4SEL &= ~GPIO_Pin;
			break;
		case GPIO_5:
			P5SEL &= ~GPIO_Pin;
			break;
		case GPIO_6:
			P6SEL &= ~GPIO_Pin;
			break;
		default :
			break;
	}
}

/**
 * @brief 设置 GPIO 作为复用模式,仅改变 IO 工作模式, 不改变 IO 方向
 * @param GPIOx    GPIO PORT 端口 
 * @param GPIO_Pin GPIO_PIN 引脚
 */
void GPIO_SetPinAlternate(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	switch(GPIOx)
	{
		case GPIO_1:
			P1SEL |= GPIO_Pin;
			break;
		case GPIO_2:
			P2SEL |= GPIO_Pin;
			break;
		case GPIO_3:
			P3SEL |= GPIO_Pin;
			break;
		case GPIO_4:
			P4SEL |= GPIO_Pin;
			break;
		case GPIO_5:
			P5SEL |= GPIO_Pin;
			break;
		case GPIO_6:
			P6SEL |= GPIO_Pin;
			break;
		default :
			break;
	}
}

void GPIO_SetPortOutputVaule(GPIO_PortTypeDef GPIOx, u8 u8value)
{
	switch(GPIOx)
		{
			case GPIO_1:
				P1OUT = u8value;
				break;
			case GPIO_2:
				P2OUT = u8value;
				break;
			case GPIO_3:
				P3OUT = u8value;
				break;
			case GPIO_4:
				P4OUT = u8value;
				break;
			case GPIO_5:
				P5OUT = u8value;
				break;
			case GPIO_6:
				P6OUT = u8value;
				break;
			default :
				break;
		}
}

/**
 * @brief 设置 IO 端口为普通模式 
 * @param GPIOx GPIO 端口
 */
void GPIO_SetPortDefault(GPIO_PortTypeDef GPIOx)
{
	switch(GPIOx)
		{
			case GPIO_1:
				P1SEL = 0;
				break;
			case GPIO_2:
				P2SEL = 0;
				break;
			case GPIO_3:
				P3SEL = 0;
				break;
			case GPIO_4:
				P4SEL = 0;
				break;
			case GPIO_5:
				P5SEL = 0;
				break;
			case GPIO_6:
				P6SEL = 0;
				break;
			default :
				break;
		}
}

/**
 * @brief 设置 IO 端口方向为输入 
 * @param GPIOx GPIO 端口
 */
void GPIO_SetPortIntput(GPIO_PortTypeDef GPIOx)
{
	switch(GPIOx)
		{
			case GPIO_1:
				P1DIR = 0;
				break;
			case GPIO_2:
				P2DIR = 0;
				break;
			case GPIO_3:
				P3DIR = 0;
				break;
			case GPIO_4:
				P4DIR = 0;
				break;
			case GPIO_5:
				P5DIR = 0;
				break;
			case GPIO_6:
				P6DIR = 0;
				break;
			default :
				break;
		}
}
/**
 * @brief 设置 IO 端口方向为输出 
 * @param GPIOx GPIO 端口
 */
void GPIO_SetPortOutput(GPIO_PortTypeDef GPIOx)
{
	switch(GPIOx)
		{
			case GPIO_1:
				P1DIR = 0xFF;
				break;
			case GPIO_2:
				P2DIR = 0xFF;
				break;
			case GPIO_3:
				P3DIR = 0xFF;
				break;
			case GPIO_4:
				P4DIR = 0xFF;
				break;
			case GPIO_5:
				P5DIR = 0xFF;
				break;
			case GPIO_6:
				P6DIR = 0xFF;
				break;
			default :
				break;
		}
}

/**
 * @brief 获取引脚输入电平
 * @param  GPIOx    GPIO 端口
 * @param  GPIO_Pin GPIO 引脚
 * @return 高低电平, 1 为高 0 为低
 */
u8 GPIO_GetPinInputValue(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	u8 u8Ret = 0;
	switch(GPIOx)
		{
			case GPIO_1:
				u8Ret = P1IN & GPIO_Pin;
				break;
			case GPIO_2:
				u8Ret = P2IN & GPIO_Pin;
				break;
			case GPIO_3:
				u8Ret = P3IN & GPIO_Pin;
				break;
			case GPIO_4:
				u8Ret = P4IN & GPIO_Pin;
				break;
			case GPIO_5:
				u8Ret = P5IN & GPIO_Pin;
				break;
			case GPIO_6:
				u8Ret = P6IN & GPIO_Pin;
				break;
			default :
				break;
		}
	if(u8Ret == GPIO_Pin)
	{
		return 1;
	}
	return 0;
}
/**
 * @brief 获取端口输入电平
 * @param  GPIOx    GPIO 端口
 * @return 各位高低电平, 1 为高 0 为低
 */
u8 GPIO_GetPortInputValue(GPIO_PortTypeDef GPIOx)
{
	u8 u8Ret = 0;
	switch(GPIOx)
		{
			case GPIO_1:
				u8Ret = P1IN;
				break;
			case GPIO_2:
				u8Ret = P2IN;
				break;
			case GPIO_3:
				u8Ret = P3IN;
				break;
			case GPIO_4:
				u8Ret = P4IN;
				break;
			case GPIO_5:
				u8Ret = P5IN;
				break;
			case GPIO_6:
				u8Ret = P6IN;
				break;
			default :
				break;
		}
	return u8Ret;
}
/**
 * @brief 获取引脚输出电平
 * @param  GPIOx    GPIO 端口
 * @param  GPIO_Pin GPIO 引脚
 * @return 高低电平, 1 为高 0 为低
 */
u8 GPIO_GetPinOutputValue(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin)
{
	u8 u8Ret = 0;
	switch(GPIOx)
		{
			case GPIO_1:
				u8Ret = P1OUT & GPIO_Pin;
				break;
			case GPIO_2:
				u8Ret = P2OUT & GPIO_Pin;
				break;
			case GPIO_3:
				u8Ret = P3OUT & GPIO_Pin;
				break;
			case GPIO_4:
				u8Ret = P4OUT & GPIO_Pin;
				break;
			case GPIO_5:
				u8Ret = P5OUT & GPIO_Pin;
				break;
			case GPIO_6:
				u8Ret = P6OUT & GPIO_Pin;
				break;
			default :
				break;
		}
	if(u8Ret == GPIO_Pin)
	{
		return 1;
	}
	return 0;
}
/**
 * @brief 获取端口输出电平
 * @param  GPIOx    GPIO 端口
 * @return 各位高低电平, 1 为高 0 为低
 */
u8 GPIO_GetPortOutputValue(GPIO_PortTypeDef GPIOx)
{
	u8 u8Ret = 0;
	switch(GPIOx)
		{
			case GPIO_1:
				u8Ret = P1OUT;
				break;
			case GPIO_2:
				u8Ret = P2OUT;
				break;
			case GPIO_3:
				u8Ret = P3OUT;
				break;
			case GPIO_4:
				u8Ret = P4OUT;
				break;
			case GPIO_5:
				u8Ret = P5OUT;
				break;
			case GPIO_6:
				u8Ret = P6OUT;
				break;
			default :
				break;
		}
	return u8Ret;
}

void GPIO_SetEXTIPin(GPIO_PortTypeDef GPIOx,  GPIO_PinTypeDef GPIO_Pin, GPIO_TriggerTypeDef GPIO_Trigger)//
{
	if(GPIOx == GPIO_1)
	{
		P1SEL &= ~GPIO_Pin;/*普通IO功能*/
		P1DIR &= ~GPIO_Pin;/*输入模式*/
		P1IE |= GPIO_Pin;/*允许外部中断*/
		P1IES |= (GPIO_Pin & GPIO_Trigger);/*触发沿设置*/
		P1IFG |= (GPIO_Pin & 0x00);/*软件清零中断标志寄存器*/	
	}
	if(GPIOx == GPIO_2)
	{
		P2SEL &= ~GPIO_Pin;/*普通IO功能*/
		P2DIR &= ~GPIO_Pin;/*输入模式*/
		P2IE |= GPIO_Pin;/*允许外部中断*/
		P2IES |= (GPIO_Pin & GPIO_Trigger);/*触发沿设置*/
		P2IFG |= (GPIO_Pin & 0x00);/*软件清零中断标志寄存器*/
	}
}


/**
 * P1口中断服务程序
 */
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
	switch(P1IFG&0x0F)
	{
		case 0x01: 
		break;
		case 0x02:;
		break;
		case 0x04: 
		break;
		case 0x08: 
		break;
		case 0x10:
		break;
		case 0x20:
		break;
		case 0x40:
		break;
	}
}
/**
 * P2口中断服务程序
 */
#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  switch(P1IFG&0x0F)
	{
		case 0x01: 
		break;
		case 0x02:;
		break;
		case 0x04: 
		break;
		case 0x08: 
		break;
		case 0x10:
		break;
		case 0x20:
		break;
		case 0x40:
		break;
	}
}