/*************************************************************************
 *
*    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : drv_glcd.h
 *    Description : Graphical LCD driver include file
 *
 *    History :
 *    1. Date        : 6, March 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *
 *    $Revision: 24636 $
 *
 *    @Modify: NXP MCU Application Team - NguyenCao
 *    @Date: 04. March. 2011
 **************************************************************************/
#include "lpc_types.h"

#define LCD_320_240	(1)
#define LCD_480_272	(2)
#define LCD_800_480	(3)
#define LCD_800_600	(4)

#ifndef __GLCD_DRV_H
#define __GLCD_DRV_H

typedef struct _Bmp_t {
  uint32_t  H_Size;
  uint32_t  V_Size;

  uint32_t *pPalette;
  uint8_t *pPicStream;
  uint8_t *pPicDesc;
} Bmp_t, *pBmp_t;

typedef struct _FontType_t {
  uint32_t H_Size;
  uint32_t V_Size;
  uint32_t CharacterOffset;
  uint32_t CharactersNuber;
  uint8_t *pFontStream;
  uint8_t *pFontDesc;
} FontType_t, *pFontType_t;

typedef uint32_t LdcPixel_t, *pLdcPixel_t;
 
#define C_GLCD_REFRESH_FREQ     (50HZ)
#define	C_GLCD_BitsPP		     16						
	 //东华3.5寸屏
#define C_GLCD_320_240_PIX_CLK          (6.4*1000000l)
#define C_GLCD_320_240_H_SIZE           320
#define C_GLCD_320_240_H_PULSE          30
#define C_GLCD_320_240_H_FRONT_PORCH    20
#define C_GLCD_320_240_H_BACK_PORCH     38
#define C_GLCD_320_240_V_SIZE           240
#define C_GLCD_320_240_V_PULSE          3
#define C_GLCD_320_240_V_FRONT_PORCH    5
#define C_GLCD_320_240_V_BACK_PORCH     15
#define C_GLCD_320_240_BytesPP			2

	 //东华 4.3寸屏
#define C_GLCD_480_272_PIX_CLK          (9.0*1000000l)
#define C_GLCD_480_272_H_SIZE           480
#define C_GLCD_480_272_H_PULSE          42
#define C_GLCD_480_272_H_FRONT_PORCH    3
#define C_GLCD_480_272_H_BACK_PORCH     3
#define C_GLCD_480_272_V_SIZE           272
#define C_GLCD_480_272_V_PULSE          11
#define C_GLCD_480_272_V_FRONT_PORCH    3
#define C_GLCD_480_272_V_BACK_PORCH     3
#define C_GLCD_480_272_BytesPP			2

	 //群创7.0寸屏
#define C_GLCD_800_480_PIX_CLK          (30*1000000l)
#define C_GLCD_800_480_H_SIZE           800
#define C_GLCD_800_480_H_PULSE          48
#define C_GLCD_800_480_H_FRONT_PORCH    40
#define C_GLCD_800_480_H_BACK_PORCH     40
#define C_GLCD_800_480_V_SIZE           480
#define C_GLCD_800_480_V_PULSE          3
#define C_GLCD_800_480_V_FRONT_PORCH    13
#define C_GLCD_800_480_V_BACK_PORCH     29
#define C_GLCD_800_480_BytesPP			2

	 //群创8.0寸屏
#define C_GLCD_800_600_PIX_CLK          (20*1000000l)
#define C_GLCD_800_600_H_SIZE           800
#define C_GLCD_800_600_H_PULSE          30
#define C_GLCD_800_600_H_FRONT_PORCH    210
#define C_GLCD_800_600_H_BACK_PORCH     46
#define C_GLCD_800_600_V_SIZE           600
#define C_GLCD_800_600_V_PULSE          10
#define C_GLCD_800_600_V_FRONT_PORCH    13
#define C_GLCD_800_600_V_BACK_PORCH     23
#define C_GLCD_800_600_BytesPP			2
	
#define C_GLCD_PWR_ENA_DIS_DLY  10000
#define C_GLCD_ENA_DIS_DLY      10000

#define CRSR_PIX_32     0
#define CRSR_PIX_64     1
#define CRSR_ASYNC      0
#define CRSR_FRAME_SYNC 2

#define TEXT_DEF_TAB_SIZE 5

#define TEXT_BEL1_FUNC()

int  GLCD_Init (uint8_t LCDtype);
void GLCD_Dis_Logo (const uint8_t *pPain, const uint8_t * pPallete);
void LCD_menu(void);
void GLCD_SetPallet (const uint32_t * pPallete);
void GLCD_Ctrl (Bool bEna);
void GLCD_Cursor_Cfg(int Cfg);
void GLCD_Cursor_En(int cursor);
void GLCD_Cursor_Dis(int cursor);
void GLCD_Move_Cursor(int x, int y);
void GLCD_Copy_Cursor (const uint32_t *pCursor, int cursor, int size);
void GLCD_SetFont(pFontType_t pFont, LdcPixel_t Color, LdcPixel_t BackgndColor);
void GLCD_SetWindow(uint32_t X_Left, uint32_t Y_Up,
                    uint32_t X_Right, uint32_t Y_Down);
void GLCD_TextSetPos(uint32_t X, uint32_t Y);
void GLCD_TextSetTabSize(uint32_t Size);
static void LCD_SET_WINDOW (uint32_t X_Left, uint32_t X_Right,
                            uint32_t Y_Up, uint32_t Y_Down);
static void LCD_WRITE_PIXEL (uint32_t Pixel);
static Bool GLCD_TextCalcWindow (uint32_t * pXL, uint32_t * pXR,
                                    uint32_t * pYU, uint32_t * pYD,
                                    uint32_t * pH_Size, uint32_t * pV_Size);
int _putchar (int c);


#endif // __GLCD_DRV_H
