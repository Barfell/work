/*****************************************************************
*Modules: uart.c
*Dedcription: ��uart�Ĳ���
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       ����ļ�
******************************************************************/
/*****************************includes****************************/
#include "msp430.h"
#include "uart.h"
#include "stdio.h"
/******************************veraible**************************/




/*****************************************************************
*Function: UARTInit
*Para:  ��UARTNumber�˿ں�,  UARTClkSource������ʱ��Դ , BaudRate��������
*Return:��
*Dedcription: ��ʼ��һ������
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      ��Ӻ���
*       zhangq          2016-3-24       uart0��115200 56000 9600��Ч
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
    
    P2SEL |= BIT4+BIT5;//GPIO����Ϊ����ģʽ
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
      UCA0CTL1 &= ~UCSWRST;                     //�����λ����״̬����ֹ����
      IE2 |= UCA0RXIE;// + UCA0TXIE;                 //ʹ�� TX/RX �ж�
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
          UCA0MCTL= 0x0E;
          break;
        case Baud_115200:
          UCA0BR0 = 0x45;                           // 8m/115200
          UCA0BR1 = 0x00;                           //
          UCA0MCTL= 0x08;
          break;
        default:break;
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
      UCA0CTL1 &= ~UCSWRST;                     //�����λ����״̬����ֹ����
      IE2 |= UCA0RXIE;// + UCA0TXIE;                 //ʹ�� TX/RX �ж�
    }
  }
 if(UARTNumber == UART_1)
 {
    P1REN &= BIT6;
    P1REN &= BIT7;
    
    P1DIR |=  BIT6;                             
    P1DIR &=  ~BIT7;
    P1OUT |=  BIT6;                              
    
    P1SEL |= BIT6+BIT7;//GPIO����Ϊ����ģʽ
    
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
      UCA1CTL1 &= ~UCSWRST;                     //�����λ����״̬����ֹ����
      IE2 |= UCA1RXIE;// + UCA1TXIE;                 //ʹ�� TX/RX �ж�
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
      UCA1CTL1 &= ~UCSWRST;                     //�����λ����״̬����ֹ����
      IE2 |= UCA1RXIE;                 //ʹ�� TX/RX �ж�
    }
 }
}
/*****************************************************************
*Function: GPIOOutPut
*Para:  port���˿ں�,  pin�����ź� , value�������ƽ��1-�ߵ�ƽ��0-�͵�ƽ��
*Return:��
*Dedcription: ����GPIO�������ƽ
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      ��Ӻ���
******************************************************************/
void UART_SendByte(UART_NumberTypeDef UART_Number, unsigned char u8data)
{
	if(UART_Number == UART_0)
	{
		/*�ȴ����ͼĴ����յ�ʱ��������*/
		while((IFG2 & UCA0TXIFG)==0);
                UCA0TXBUF = u8data;
	}
	else if (UART_Number == UART_1)
	{
		/*�ȴ����ͼĴ����յ�ʱ��������*/
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
*       zhangq          2016-2-22       ��Ӻ���
******************************************************************/
int putchar(int c)
{
  while((IFG2 & UCA0TXIFG)==0);
  UCA0TXBUF = c;
  while((IFG2 & UCA0TXIFG)==0);
  return c;
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
  LPM3_EXIT;
  while(!(IFG2&UCA0RXIFG));
  IFG2 &= ~UCA0RXIFG;
  printf("uart rxd lpm3 exit\r\n");
}

//__interrupt void USCIA0TX_ISR (void)
//{
//  //while(!(IFG2&UCA0TXIFG));
//  //LPM3_EXIT;
//  printf("lpm3 exit\r\n");
//}