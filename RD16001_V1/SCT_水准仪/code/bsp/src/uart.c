/*****************************************************************
*Modules: uart.c
*Dedcription: 对uart的操作
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
/*****************************includes****************************/
#include "msp430.h"
#include "uart.h"
#include "stdio.h"
#include "ramloop.h"
#include "kernel.h"
/******************************veraible**************************/


LoopRAMType Uart0loop;//串口0环形缓冲
long Uart0time;

LoopRAMType Uart1loop;//串口1环形缓冲
long Uart1time;


/*****************************************************************
*Function: UARTInit
*Para:  ：UARTNumber端口号,  UARTClkSource：串口时钟源 , BaudRate：波特率
*Return:无
*Dedcription: 初始化一个串口
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      添加函数
*       zhangq          2016-3-24       uart0的115200 56000 9600有效
******************************************************************/
void UARTInit(UART_NumberTypeDef UARTNumber, UART_SouceClkTypeDef UARTClkSource, UART_BaudTypeDef BaudRate)
{
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
/*****************************************************************
*Function: GPIOOutPut
*Para:  port：端口号,  pin：引脚号 , value：输出电平（1-高电平、0-低电平）
*Return:无
*Dedcription: 设置GPIO的输出电平
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      添加函数
******************************************************************/
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




/*****************************************************************
*Function: 
*Para: 
*Return:
*Dedcription: 
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加函数
******************************************************************/
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











/*
********************USCIAB0***************************************
*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
  while(!(IFG2 & UCA0TXIFG));
// UCA0TXBUF = UCA0RXBUF;
//  while(!(UC1IFG&UCA1TXIFG));
//  UCA1TXBUF = UCA0RXBUF;
  LoopRAMWriteByte(&Uart0loop,UCA0RXBUF);//加入到环形缓冲中
  Uart0time = GetTick();//接收的时间点
}




/*
*********************USCIAB1**************************************
*/
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCIA1RX_ISR (void)
{
  while(!(UC1IFG&UCA1TXIFG));
  //UCA1TXBUF = UCA1RXBUF;
  LoopRAMWriteByte(&Uart1loop,UCA1RXBUF);//加入到环形缓冲中
  Uart1time = GetTick();//接收的时间点
}
