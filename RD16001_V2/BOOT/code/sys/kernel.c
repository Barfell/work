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

long SysTick = 0;
void SysTickInit(void)
{
  SysTick = 0;
  /*定时器中断初始化*/
  /*------------------------------*/
  TACTL   |= TASSEL_2 + ID_0 + MC_3;//smclk - div0 - up/down mode
  TACCR0   = 40000;//10ms
  TACCTL0  = OUTMOD_4 + CCIE;
  /*------------------------------*/
}
/**
 * @brief 外部高速晶振作为系统的主时钟初始化函数
 * @note  初始化后时钟为 ACLK = LFXT1, MCLK = XT2, SMCLK = XT2
 * @note  LFXT1 常使用 32.768Khz, XT2 常使用 8Mhz
 */
void RCC_HSECLKInit(void)
{
  volatile unsigned int i;
  FLL_CTL0 |= XCAP11PF;                       //LXT CAP 
  FLL_CTL1 &= ~XT2OFF;                        // Activate XT2 high freq xtal
  /* Wait for xtal to stabilize*/
  do
  {
    IFG1 &= ~OFIFG;                           
    for (i = 550; i > 0; i--);
  }
  while (IFG1 & OFIFG);                       // OSCFault flag still set
  
  FLL_CTL1 |= SELS;                           // SMCLK = XT2CLK
  FLL_CTL2 |= XT2S_2;                         // 2-16mhz
  FLL_CTL1 |= SELM1;                          // MCLK = XT2
  FLL_CTL1 &= ~SMCLKOFF;                      // SMCLK ON
  
  
  SysTickInit();
  
    /*用于控制串口0选择哪个通道   DTU  或者 RF */
  P1REN &= ~BIT1;
  P1REN &= ~BIT2;
  P1DIR |=  BIT1;
  P1DIR |=  BIT2;
  P1OUT &=  ~BIT1;
  P1OUT &=  ~BIT2;//默认初始化是N2
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




int putchar(int c)
{
  while((IFG2 & UCA0TXIFG)==0);
  UCA0TXBUF = c;
  while((IFG2 & UCA0TXIFG)==0);
  return c;
}

