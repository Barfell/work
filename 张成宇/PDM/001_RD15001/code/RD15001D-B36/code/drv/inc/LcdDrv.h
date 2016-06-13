/**********************************************************************
* Module:	   DRIVER\lcd
* Function:
* Description:	液晶
* Log:	
**********************************************************************/
#ifndef	__LCDDRV_H
#define	__LCDDRV_H

#include "LcdDrvHd.h"
#include "LcdIcon.h"
#include "display.h"



//屏参
#include "LcdConfig.cfg"
#define LCD_COL_OFFSET          0
#define ClearWdg()

//LCD指令
#define LCDCMD_SET_PAGE_ADDRESS		    (0xB0)
#define LCDCMD_SET_COLUMN_ADDRESS_H	    (0x10)
#define LCDCMD_SET_COLUMN_ADDRESS_L	    (0x00)

//LCD

#define LCDCMD_SET_ICON_ENABLE						(0XA3)	//有光标
#define LCDCMD_SET_ICON_DISABLE						(0XA2)	//无光标
#define LCDCMD_SET_PAGE_ADDRESS		    			(0xB0)//设置页地址
#define LCDCMD_SET_COLUMN_ADDRESS_H	    			(0x10)
#define LCDCMD_SET_COLUMN_ADDRESS_L	    			(0x00)

#define LCDCMD_DISPLAY_ON							(0xAF)//开机
#define LCDCMD_DISPLAY_OFF              			(0xAE)//关机
#define LCDCMD_START_LINE			    			(0x40)//设置起始行

		
//该指令只在3-SPI上使用		
#define SET_DATA_DIRECTION_DDL						(0xE8)	

/**********************************************************
*以下定义了液晶的属性和可能的属性值
*例如：
*#define LCDCMD_SEG_DIRECTION			(0xA0)
*    #define LCDCFG_SEG_DIRECTION_NORMAL     (0x0)
*    #define LCDCFG_SEG_DIRECTION_REVERSE    (0x1)
*LCDCMD_SEG_DIRECTION表示液晶SEG的方向属性
*LCDCFG_SEG_DIRECTION_NORMAL
*LCDCFG_SEG_DIRECTION_REVERSE 分别表示方向正常和方向反向
*每种液晶需要配置每个属性的属性值，例如
*#define LCDCFG_SEG_DIRECTION    LCDCFG_SEG_DIRECTION_NORMAL
*
************************************************************/

#define LCDCMD_SEG_DIRECTION			(0xA0)
    #define LCDCFG_SEG_DIRECTION_NORMAL     (0x0)
    #define LCDCFG_SEG_DIRECTION_REVERSE    (0x1)
//反转显示
#define LCDCMD_DISPLAY_MODE			    (0xA6)
    #define LCDCFG_DISPLAY_MODE_NORMAL      (0x0)
    #define LCDCFG_DISPLAY_MODE_INVERSE     (0x1)
//Entire display
#define LCDCMD_ALL_PIXEL		        (0xA4)
    #define LCDCFG_ALL_PIXEL_ON             (0x1)
    #define LCDCFG_ALL_PIXEL_NORMAL         (0x0)
//图标ICON control
#define LCDCMD_ICON_CONTROL    		    (0xA2)
    #define  LCDCFG_ICON_DISABLE           (0x0)
    #define  LCDCFG_ICON_ENABLE            (0x1)

#define LCDCMD_READ_MODIFY_WRITE		(0xE0)
#define LCDCMD_END_READ_MODIFY_WRITE	(0xEE)
#define LCDCMD_LCD_RESET				(0xE2)

#define LCDCMD_POWER_CONTROL	        (0x28)
    #define LCDCFG_POWER_CONTROL_BOOSTER_OFF   (0x0)
    #define LCDCFG_POWER_CONTROL_BOOSTER_ON    (0x1)
    #define LCDCFG_POWER_CONTROL_REGULATOR_OFF (0x0)
    #define LCDCFG_POWER_CONTROL_REGULATOR_ON  (0x2)
    #define LCDCFG_POWER_CONTROL_FOLLOWER_OFF  (0x0)
    #define LCDCFG_POWER_CONTROL_FOLLOWER_ON   (0x4)

#define LCDCMD_REGULATION_RATIO         (0x20)
    #define LCDCFG_REGULATION_RATIO_1       (0x0)
    #define LCDCFG_REGULATION_RATIO_2     (0x1)
    #define LCDCFG_REGULATION_RATIO_3       (0x2)
    #define LCDCFG_REGULATION_RATIO_4     (0x3)
    #define LCDCFG_REGULATION_RATIO_5       (0x4)
    #define LCDCFG_REGULATION_RATIO_6     (0x5)
    #define LCDCFG_REGULATION_RATIO_7       (0x6)
    #define LCDCFG_REGULATION_RATIO_8     (0x7)

#define LCDCMD_COM_DIRECTION    		(0xC0)
    #define LCDCFG_COM_DIRECTION_NORMAL     (0x0)	//从0~127
    #define LCDCFG_COM_DIRECTION_REVERSE    (0x8)	//从127~0

//对比度 范围是0~63
#define LCDCMDDB_SET_EV                 (0x81)
#define LCDCMDDB_SET_CONTRAST           LCDCMDDB_SET_EV


#define LCDCMD_NOP					    (0xE3)

enum
{
	LCD_PAGE0 = 0,
	LCD_PAGE1,
	LCD_PAGE2,
	LCD_PAGE3,
	LCD_PAGE4,
	LCD_PAGE5,
	LCD_PAGE6,
	LCD_PAGE7,
	LCD_PAGE8,
	LCD_PAGE9,
	LCD_PAGE10,
	LCD_PAGE11,
};

#ifndef  ICON_CONNECT_PC
    #define ICON_CONNECT_PC	        0x80
#endif
#ifndef  ICON_LOCK
    #define ICON_LOCK		        0x40
#endif
#ifndef   ICON_PINYIN  
    #define ICON_PINYIN		        0x20
#endif
#ifndef  ICON_BH   
    #define ICON_BH     	        0x4
#endif
#ifndef  ICON_ZIMU   
    #define ICON_ZIMU		        0x8
#endif
#ifndef  ICON_RESERVE2   
    #define ICON_RESERVE2	        0x10
#endif
#ifndef  ICON_FUHAO   
    #define ICON_FUHAO		        0x2
#endif    
#ifndef  ICON_SHUZI  
    #define ICON_SHUZI		        0x1
#endif

#define LCD_MAX_X               SCREEN_WIDTH
#define LCD_MAX_Y               SCREEN_HEIGHT
#define LCD_SEG_SIZE		    SCREEN_WIDTH

VOID STDCALL LcdDevClear(VOID);
//lcd初始化
VOID STDCALL  LCDDrvInit(VOID);

//设置对比度 允许设置区间为0 ~ 63,实际使用区间为15~45
VOID STDCALL LcdDevSetContrast(UCHAR ucValue);
UCHAR STDCALL LcdDevGetContrast(VOID);
VOID STDCALL LcdEnterSavePowerMode(VOID);
//刷新屏幕，显示显存数据
VOID STDCALL RefreshFrameBuf(UINT uX, UINT uY, UINT uDx, UINT uDy, U8 * pFrameBuf);
VOID STDCALL LcdSetPage(U8 page);
VOID STDCALL LcdSetColumn(U8 col);


//lcd左右图标和滚动条（特定液晶才有）
//设置左边图标风格
    //覆盖之前所有设置
    //在之前基础上关闭
    //在之前基础上点亮

#define LCDDrvClr()  			LcdDevClear() 
#define GetLCDDrvContrast()     LcdDevGetContrast()
#define SetLCDDrvContrast(v)    LcdDevSetContrast(v)


#endif  //__LCDDRV_H
