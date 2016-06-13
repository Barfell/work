#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "kernal.h"

#include "LcdDrv.h"

VOID DisplayLogo(VOID);
VOID DisplayProc(U8 num);
VOID DisplayFirstMenuStart(VOID);
VOID DisplayFirstMenuEnd(VOID);
VOID DisplayFirstMenuClear(VOID);
VOID DisplayFirstMenuSave(VOID);
VOID DisplayFirstMenuSysError(VOID);
VOID DisplayFirstMenuUError(VOID);
VOID DisplaySecondMenuMeasure(VOID);
VOID DisplaySecondMenuEnd(VOID);
VOID DisplaySecondMenuSave(VOID);
VOID DisplaySecondMenuClear(VOID);


VOID DisplayTestcomm1(VOID);
VOID DisplayTestcomm2(VOID);
VOID DisplayTestcomm3(VOID);

VOID Lcd_Show_Menu_16(U8 x,U8 y,U8 n);
VOID Lcd_Show_num_16(U8 x,U8 y,U8 n);


#endif
