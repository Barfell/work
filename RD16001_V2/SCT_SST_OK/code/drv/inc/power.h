#ifndef _POWER_H_
#define _POWER_H_

//PWR_
#define PWR_ON               P1OUT |=  BIT0//
#define PWR_OFF              P1OUT &= ~BIT0

//COLL_PWR_
#define COLL_PWR_ON          P9OUT |=  BIT5
#define COLL_PWR_OFF         P9OUT &= ~BIT5

//TRAN_PWR_
#define TRAN_PWR_ON          P4OUT |=  BIT4
#define TRAN_PWR_OFF         P4OUT &= ~BIT4


void PowerInit(void);

void LowPowerEntry(void);

void LowperMeneagement(void);

void LED(unsigned char x);

void CH_Select(unsigned char ch);
#endif