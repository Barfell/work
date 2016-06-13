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
void UARTInit(UART_NumberTypeDef UARTNumber, UART_SouceClkTypeDef UARTClkSource, UART_BaudTypeDef BaudRate)
{
  
  /*串口设置*/
  if(UARTNumber == UART_0)
  { 
    P2REN &= ~BIT4;
    P2REN &= ~BIT5;
    
    P2DIR |=  BIT4;                             
    P2DIR &= ~BIT5;                            
    P2OUT |=  BIT4;                              
    
    P2SEL |= BIT4+BIT5;//GPIO设置为串口模式
    if(UARTClkSource == UART_Clk_ACLK)
    {
      UCA0CTL1 |= UCSSEL_1;                         // CLK = ACLK
      switch(BaudRate)
      {
        case Baud_2400:
          UCA0BR0 = 0x0D;                           // 32k/2400 
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x0D;
          break;
        case Baud_4800:
          UCA0BR0 = 0x06;                           // 32k/4800 
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x0E;
          break;
        case Baud_9600:
          UCA0BR0 = 0x03;                           // 32k/9600 
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x06;
          break;
        default:break;
      }
      UCA0CTL1 &= ~UCSWRST;                     //软件复位串口状态，防止乱码
      IE2 |= UCA0RXIE;// + UCA0TXIE;                 //使能 TX/RX 中断
    }
    if(UARTClkSource == UART_Clk_SMCLK)
    {
      UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
      switch(BaudRate)
      {
        case Baud_2400:
          UCA0BR0 = 0x03;                           // 8m/2400 
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x06;
          break;
        case Baud_4800:
          UCA0BR0 = 0x03;                           // 8m/4800 
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x06;
          break;
        case Baud_9600:
          UCA0BR0 = 0x41;                           // 8m/9600 
          UCA0BR1 = 0x03;                           //
          UCA0MCTL= 0x04;
          break;
        case Baud_19200:
          UCA0BR0 = 0xA0;                           // 8m/19200 
          UCA0BR1 = 0x01;                           //
          UCA0MCTL= 0x0D;
          break;
        case Baud_38400:
          UCA0BR0 = 0xD0;                           // 8m/38400
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x06;
          break;
        case Baud_57600:
          UCA0BR0 = 0x8A;                           // 8m/57600
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x08;
          break;
        case Baud_115200:
          UCA0BR0 = 0x45;                           // 8m/115200
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x08;
          break;
        default:break;
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
      UCA0CTL1 &= ~UCSWRST;                     //软件复位串口状态，防止乱码
      IE2 |= UCA0RXIE;// + UCA0TXIE;                 //使能 TX/RX 中断
    }
  }
 if(UARTNumber == UART_1)
 {
    P1REN &= BIT6;
    P1REN &= BIT7;
    
    P1DIR |=  BIT6;                             
    P1DIR &=  ~BIT7;
    P1OUT |=  BIT6;                              
    
    P1SEL |= BIT6+BIT7;//GPIO设置为串口模式
    
    if(UARTClkSource == UART_Clk_ACLK)
    {
      UCA1CTL1 |= UCSSEL_1;                         // CLK = ACLK
      switch(BaudRate)
      {
        case Baud_2400:
          UCA1BR0 = 0x0D;                           // 32k/2400 
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x0D;
          break;
        case Baud_4800:
          UCA1BR0 = 0x06;                           // 32k/4800 
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x0E;
          break;
        case Baud_9600:
          UCA1BR0 = 0x03;                           // 32k/9600 
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x06;
          break;
        default:break;
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
      UCA1CTL1 &= ~UCSWRST;                     //软件复位串口状态，防止乱码
      UC1IE |= UCA1RXIE;// + UCA1TXIE;                 //使能 TX/RX 中断
    }
    if(UARTClkSource == UART_Clk_SMCLK)
    {
      UCA1CTL1 |= UCSSEL_2;                     // CLK = SMCLK
      switch(BaudRate)
      {
        case Baud_2400:
          UCA1BR0 = 0x03;                           // 8m/2400 
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x06;
          break;
        case Baud_4800:
          UCA1BR0 = 0x03;                           // 8m/4800 
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x06;
          break;
        case Baud_9600:
          UCA1BR0 = 0x41;                           // 8m/9600 
          UCA1BR1 = 0x03;                           //
          UCA1MCTL= 0x04;
          break;
        case Baud_19200:
          UCA1BR0 = 0xA0;                           // 8m/19200 
          UCA1BR1 = 0x01;                           //
          UCA1MCTL= 0x0D;
          break;
        case Baud_38400:
          UCA1BR0 = 0xD0;                           // 8m/38400
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x06;
          break;
        case Baud_57600:
          UCA1BR0 = 0x8A;                           // 8m/57600
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x0E;
          break;
        case Baud_115200:
          UCA1BR0 = 0x45;                           // 8m/115200
          UCA1BR1 = 0x00;                           //
          UCA1MCTL= 0x08;
          break;
        default:break;
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      UCA1CTL1 &= ~UCSWRST;                     //软件复位串口状态，防止乱码
      UC1IE |= UCA1RXIE;                 //使能 TX/RX 中断
    }
 }
}

/**
 * @brief 串口发送函数 
 * @param NumberTypeDef 串口号 @ref UART_NumberTypeDef
 * @param u8data        待发送数据
 */
void UART_SendByte(UART_NumberTypeDef UART_Number, unsigned char u8data)
{
	if(UART_Number == UART_0)
	{
		/*等待发送寄存器空的时候发送数据*/
		while((IFG2 & UCA0TXIFG)==0);
                UCA0TXBUF = u8data;
	}
	else if (UART_Number == UART_1)
	{
		/*等待发送寄存器空的时候发送数据*/
		while((UC1IFG & UCA1TXIFG)==0);
                UCA1TXBUF = u8data;
	}
}

/**
 * @brief 串口发送字符串函数
 * @param NumberTypeDef 串口号 @ref UART_NumberTypeDef
 * @param str           字符串指针
 * @param u16length     发送长度
 */
void UartString(UART_NumberTypeDef UARTNumber,char *s)
{
  if(UARTNumber == UART_0)
  {
    while(*s != '\0')
    {
      while((IFG2 & UCA0TXIFG)==0);
      UCA0TXBUF = *s;
      while((IFG2 & UCA0TXIFG)==0);
      s++;
    }
  }
  if(UARTNumber == UART_1)
  {
    while(*s != '\0')
    {
      while((UC1IFG & UCA1TXIFG)==0);
      UCA1TXBUF = *s;
      while((UC1IFG & UCA1TXIFG)==0);
      s++;
    }
  }
}




