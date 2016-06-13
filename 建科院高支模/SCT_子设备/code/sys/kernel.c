/*****************************************************************
*Modules: kernel.c
*Dedcription: 存放一些系统的杂项函数，比如：delay、printf、、、等等
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
#include "kernel.h"


extern long SysTick;


/*****************************************************************
*Function: 
*Para: 
*Return:
*Dedcription: 
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加函数
******************************************************************/
void DelayMs(void)
{
  
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
void DelayUs(void)
{
  
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
void DelayS(void)
{
  
}

void hextostr(char *str ,unsigned char hex)
{
	if( (hex / 16) > 9)
		{*str = (hex / 16)+'0'+ 7;}
	else
		{*str = (hex / 16)+'0';}

	if((hex%16) > 9)
		{*(str+1) = (hex%16)+'0' + 7;}
	else
		{*(str+1) = (hex%16)+'0';}
}

void HextoAscii(char *str ,char hex)
{
        if( (hex / 16) > 9)
		{*str = (hex / 16)+'0'+ 7;}
	else
		{*str = (hex / 16)+'0';}

	if((hex%16) > 9)
		{*(str+1) = (hex%16)+'0' + 7;}
	else
		{*(str+1) = (hex%16)+'0';}
}

void HexBufToAsciiBuf(char *ascii, char *hex, unsigned char length)
{
  unsigned char i;
  for( i=0; i < length; i++)
  {
    HextoAscii( (ascii+(2*i)),*(hex+i));
  }
}


float Hex_To_Decimal( char *Byte)//十六进制到浮点数
{
  float *f = (float *)Byte;
//  *( (char*)f+0 ) = *(Byte+0);
//  *( (char*)f+1 ) = *(Byte+1);
//  *( (char*)f+2 ) = *(Byte+2);
//  *( (char*)f+3 ) = *(Byte+3);
  return *f;
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
#define UART0_PRINTF
//#define UART1_PRINTF

int putchar(int c)
{
#ifdef UART0_PRINTF
  while((IFG2 & UCA0TXIFG)==0);
  UCA0TXBUF = c;
  while((IFG2 & UCA0TXIFG)==0);
  return c;
#endif

#ifdef UART1_PRINTF
  while((UC1IFG & UCA1TXIFG)==0);
  UCA1TXBUF = c;
  while((UC1IFG & UCA1TXIFG)==0);
  return c;
#endif
}


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

void SysTickOff(void)
{
  TACTL   &= ~TASSEL_2;
  TACTL   &= ~ID_0;
  TACTL   &= ~MC_3;
  TACCR0   = 0;//10ms
  TACCTL0  &= ~OUTMOD_4;
  TACCTL0  &= ~CCIE;
}

//10ms的时间片
long GetTick(void)
{
  return SysTick;
}


