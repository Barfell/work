#include "msp430.h"
#include "key.h"
#define KEY_START_VALUE         0x00
#define KEY                     (P1IN & BIT2)
unsigned char KeyTrg = 0;//���¶���������Ϣ
unsigned char KeyCont = 0;//����ֵ
void KeyInit(void)
{
  P1DIR &= ~BIT2;//����Ϊ����ģʽ
}

/*һ�㰴���ṹ�Ĳ�ѯʱ����20ms��ѯһ��*/
void KeyTask(void)
{
  unsigned char KeyRead = KEY ^ KEY_START_VALUE;//��ǰ����ֵ���ް���ʱ��Ϊ0x00
  KeyTrg = KeyRead & (KeyRead ^ KeyCont);//����������ʱ�Ĵ����źţ�ֻ����һ�Σ�
  KeyCont = KeyRead;//����ֵ��������û�зſ�ʱ��һֱ�ǰ���ֵ�������ж��Ƿ��ǳ���
}