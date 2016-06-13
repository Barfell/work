/**
 * @versionnote
 * version    V1.0
 * +  2015-11-20
 * +  file create
 */
#include "msp430f149_uart.h"
#include "kernel.h" 

/*
ACLK:	32768HZ		
BAUD	2400	4800	9600	19200	38400	76800	115200
UBR1	0x00	0x00	0x00
UBR0	0x0D	0x06	0x03
UMCTL	0x6D	0xFB	0x4A

SMCLK:	8HMZ
BAUD	2400	4800	9600	19200	38400	76800	115200
UBR1	0x0D	0x06	0x03	0x01	0x00	0x00	0x00
UBR0	0x05	0x82	0x41	0xA0	0xD0 	0x68	0x45
UMCTL	0x00	0x00	0x00	0xC0	0x40	0x40	0x4A
*/
/**
 * @brief 串口初始化函数,默认接收发送使能,开启接收中断
 * @param SouceClkTypeDef 波特率产生时钟源 @ref UART_SouceClkTypeDef
 * @param NumberTypeDef   串口号 @ref UART_NumberTypeDef
 * @param BaudTypeDef     波特率 @ref UART_BaudTypeDef
 */
void UART_Init(UART_NumberTypeDef NumberTypeDef, UART_SouceClkTypeDef SouceClkTypeDef, UART_BaudTypeDef BaudTypeDef)
{
	if(NumberTypeDef == UART_0)
	{
		U0CTL |= SWRST;
		U0CTL |= CHAR;/* 8 位长度*/
		if (SouceClkTypeDef == UART_SouceClk_SMCLK)
		{
			U0TCTL |= SSEL1;/*选择 SMCLK */
			switch(BaudTypeDef)
			{
				case UART_SMCLKBaud_2400:
					U0BR1 = 0x0D;
					U0BR0 = 0x05;
					U0MCTL = 0x00;
					break;
				case UART_SMCLKBaud_4800:
					U0BR1 = 0x06;
					U0BR0 = 0x82;
					U0MCTL = 0x00;
					break;
				case UART_SMCLKBaud_9600:
					U0BR1 = 0x03;
					U0BR0 = 0x41;
					U0MCTL = 0x00;
					break;
				case UART_SMCLKBaud_19200:
					U0BR1 = 0x01;
					U0BR0 = 0xA0;
					U0MCTL = 0xC0;
					break;
				case UART_SMCLKBaud_38400:
					U0BR1 = 0x00;
					U0BR0 = 0xD0;
					U0MCTL = 0x40;
					break;
				case UART_SMCLKBaud_76800:
					U0BR1 = 0x00;
					U0BR0 = 0x68;
					U0MCTL = 0x40;
					break;
				case UART_SMCLKBaud_115200:
					U0BR1 = 0x00;
					U0BR0 = 0x45;
					U0MCTL = 0x4A;
					break;
			}
		}else if (SouceClkTypeDef == UART_SouceClk_ACLK)
		{
			U0TCTL |= SSEL0;/*选择 ACLK */
			switch(BaudTypeDef)
			{
				case UART_ACLKBaud_2400:
					U0BR1 = 0x00;
					U0BR0 = 0x0D;
					U0MCTL = 0x6D;
					break;
				case UART_ACLKBaud_4800:
					U0BR1 = 0x00;
					U0BR0 = 0x06;
					U0MCTL = 0xFB;
					break;
				case UART_ACLKBaud_9600:
					U0BR1 = 0x00;
					U0BR0 = 0x03;
					U0MCTL = 0x4A;
					break;
			}
		}
		ME1 |= UTXE0;/*UART0发送使能*/
		ME1 |= URXE0;/*UART0接收使能*/
		U0CTL &= ~SWRST;
		IE1 |= URXIE0;/*接收中断使能位*/
		
		P3SEL|= BIT4 + BIT5;/*设置IO口为第二功能模式，启用UART功能*/
  		P3DIR|= BIT4;/*设置IO口方向为输出*/
	}
	if(NumberTypeDef == UART_1)
	{
		U1CTL |= SWRST;
		U1CTL |= CHAR;
		if (SouceClkTypeDef == UART_SouceClk_SMCLK)
		{
			U1TCTL |= SSEL1;/*选择 SMCLK */
			switch(BaudTypeDef)
			{
				case UART_SMCLKBaud_2400:
					U1BR1 = 0x0D;
					U1BR0 = 0x05;
					U1MCTL = 0x00;
					break;
				case UART_SMCLKBaud_4800:
					U1BR1 = 0x06;
					U1BR0 = 0x82;
					U1MCTL = 0x00;
					break;
				case UART_SMCLKBaud_9600:
					U1BR1 = 0x03;
					U1BR0 = 0x41;
					U1MCTL = 0x00;
					break;
				case UART_SMCLKBaud_19200:
					U1BR1 = 0x01;
					U1BR0 = 0xA0;
					U1MCTL = 0xC0;
					break;
				case UART_SMCLKBaud_38400:
					U1BR1 = 0x00;
					U1BR0 = 0xD0;
					U1MCTL = 0x40;
					break;
				case UART_SMCLKBaud_76800:
					U1BR1 = 0x00;
					U1BR0 = 0x68;
					U1MCTL = 0x40;
					break;
				case UART_SMCLKBaud_115200:
					U1BR1 = 0x00;
					U1BR0 = 0x45;
					U1MCTL = 0x4A;
					break;
				default :
					break;
			}
		}else if (SouceClkTypeDef == UART_SouceClk_ACLK)
			{
				U1TCTL |= SSEL0;/*选择 ACLK */
				switch(BaudTypeDef)
				{
					case UART_ACLKBaud_2400:
						U1BR1 = 0x00;
						U1BR0 = 0x0D;
						U1MCTL = 0x6D;
						break;
					case UART_ACLKBaud_4800:
						U1BR1 = 0x00;
						U1BR0 = 0x06;
						U1MCTL = 0xFB;
						break;
					case UART_ACLKBaud_9600:
						U1BR1 = 0x00;
						U1BR0 = 0x03;
						U1MCTL = 0x4A;
						break;
				}
			}
			ME2 |= UTXE1;/*UART1发送使能*/
			ME2 |= URXE1;/*UART1接收使能*/
			U1CTL &= ~SWRST;
			IE2 |= URXIE1;/*接收中断使能位*/

			P3SEL|= BIT6 + BIT7;/*设置IO口为第二功能模式，启用UART功能*/
  			P3DIR|= BIT6;/*设置IO口方向为输出*/
			__enable_interrupt();
		}
	/*开启接收中断*/
	__enable_interrupt();
	
}

/**
 * @brief 串口发送函数 
 * @param NumberTypeDef 串口号 @ref UART_NumberTypeDef
 * @param u8data        待发送数据
 */
void UART_SendByte(UART_NumberTypeDef NumberTypeDef, u8 u8data)
{
	if(NumberTypeDef == UART_0)
	{
		/*等待发送寄存器空的时候发送数据*/
		while((IFG1&UTXIFG0)==0);
    	U0TXBUF = u8data;
	}
	else if (NumberTypeDef == UART_1)
	{
		/*等待发送寄存器空的时候发送数据*/
		while((IFG2&UTXIFG1)==0);
    	U1TXBUF = u8data;
	}
}

/**
 * @brief 串口发送字符串函数
 * @param NumberTypeDef 串口号 @ref UART_NumberTypeDef
 * @param str           字符串指针
 * @param u16length     发送长度
 */
void UART_SendStr(UART_NumberTypeDef NumberTypeDef, u8 *str, u16 u16length)
{
	u16 i = 0;
	for(i=0; i<u16length; i++)
	{
		UART_SendByte(NumberTypeDef, *(str+i));
	}
}

/**
 * @brief 串口 printf 函数, 使用时必须以'\n'结尾,默认使用串口0发送
 * @param s 待发送字符串
 */
void PrintStr(u8 *s)
{
	while(*s != '\0')
    {
#ifdef SERIAL_USE_PORT0
        UART_SendByte(UART_0,*s++);
#endif
        
#ifdef SERIAL_USE_PORT1
        UART_SendByte(UART_1,*s++);
#endif
    }
}


