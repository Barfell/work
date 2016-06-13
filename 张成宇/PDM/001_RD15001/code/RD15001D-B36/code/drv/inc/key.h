#ifndef __KEY_H
#define __KEY_H

#include "kernal.h" 

enum
{
	KEY_INVALID = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
};

#define KEY_ENTER	KEY_1
#define KEY_RIGHT	KEY_2
#define KEY_LEFT	KEY_3
#define KEY_EXIT	KEY_4

VOID KeyInit(VOID);
U8 GetKeyNumber(VOID);
VOID SetKeyNumber(U8 u8Type);
VOID KeyScan(VOID);




#endif

