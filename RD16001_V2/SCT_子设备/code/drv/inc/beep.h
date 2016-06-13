#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP_OFF  (P4OUT &= ~BIT0)
#define BEEP_ON   (P4OUT |= BIT0 )

void BeepInit(void);
void Beep(unsigned char i);


#endif