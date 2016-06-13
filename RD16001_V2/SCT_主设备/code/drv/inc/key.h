#ifndef _KEY_H_
#define _KEY_H_

#define KEY_TIME  200
extern unsigned char KeyTrg;//按下动作触发信息
extern unsigned char KeyCont;//按键值

void KeyInit(void);
void KeyTask(void);

#endif