#include "msp430.h"
#include "key.h"
#define KEY_START_VALUE         0x00
#define KEY                     (P1IN & BIT2)
unsigned char KeyTrg = 0;//按下动作触发信息
unsigned char KeyCont = 0;//按键值
void KeyInit(void)
{
  P1DIR &= ~BIT2;//设置为输入模式
}

/*一般按键结构的查询时间是20ms查询一次*/
void KeyTask(void)
{
  unsigned char KeyRead = KEY ^ KEY_START_VALUE;//当前按键值，无按键时候为0x00
  KeyTrg = KeyRead & (KeyRead ^ KeyCont);//当按键按下时的触发信号（只出现一次）
  KeyCont = KeyRead;//按键值，当按键没有放开时候，一直是按键值，用于判断是否是长按
}