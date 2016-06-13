#ifndef _POWER_H_
#define _POWER_H_

//
#define PWR_ON               GPIOOutPut(P4,Pin3,1)
#define PWR_OFF              GPIOOutPut(P4,Pin3,0)
#define CORE_PWR_ON          GPIOOutPut(P4,Pin2,1)
#define CORE_PWR_OFF         GPIOOutPut(P4,Pin2,0)

//
#define COLL_PWR_ON          GPIOOutPut(P9,Pin5,1)
#define COLL_PWR_OFF         GPIOOutPut(P9,Pin5,0)

void PowerInit(void);

void LowPowerEntry(void);

void LowperMeneagement(void);
#endif