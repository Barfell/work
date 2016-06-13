/**********************************************************************
* Module:	   DRIVER\lcd
* Function:
* Description:	Һ��
* Log:	
**********************************************************************/
#ifndef	__LCDDRV_H
#define	__LCDDRV_H

#include "LcdDrvHd.h"
#include "LcdIcon.h"
#include "display.h"



//����
#include "LcdConfig.cfg"
#define LCD_COL_OFFSET          0
#define ClearWdg()

//LCDָ��
#define LCDCMD_SET_PAGE_ADDRESS		    (0xB0)
#define LCDCMD_SET_COLUMN_ADDRESS_H	    (0x10)
#define LCDCMD_SET_COLUMN_ADDRESS_L	    (0x00)

//LCD

#define LCDCMD_SET_ICON_ENABLE						(0XA3)	//�й��
#define LCDCMD_SET_ICON_DISABLE						(0XA2)	//�޹��
#define LCDCMD_SET_PAGE_ADDRESS		    			(0xB0)//����ҳ��ַ
#define LCDCMD_SET_COLUMN_ADDRESS_H	    			(0x10)
#define LCDCMD_SET_COLUMN_ADDRESS_L	    			(0x00)

#define LCDCMD_DISPLAY_ON							(0xAF)//����
#define LCDCMD_DISPLAY_OFF              			(0xAE)//�ػ�
#define LCDCMD_START_LINE			    			(0x40)//������ʼ��

		
//��ָ��ֻ��3-SPI��ʹ��		
#define SET_DATA_DIRECTION_DDL						(0xE8)	

/**********************************************************
*���¶�����Һ�������ԺͿ��ܵ�����ֵ
*���磺
*#define LCDCMD_SEG_DIRECTION			(0xA0)
*    #define LCDCFG_SEG_DIRECTION_NORMAL     (0x0)
*    #define LCDCFG_SEG_DIRECTION_REVERSE    (0x1)
*LCDCMD_SEG_DIRECTION��ʾҺ��SEG�ķ�������
*LCDCFG_SEG_DIRECTION_NORMAL
*LCDCFG_SEG_DIRECTION_REVERSE �ֱ��ʾ���������ͷ�����
*ÿ��Һ����Ҫ����ÿ�����Ե�����ֵ������
*#define LCDCFG_SEG_DIRECTION    LCDCFG_SEG_DIRECTION_NORMAL
*
************************************************************/

#define LCDCMD_SEG_DIRECTION			(0xA0)
    #define LCDCFG_SEG_DIRECTION_NORMAL     (0x0)
    #define LCDCFG_SEG_DIRECTION_REVERSE    (0x1)
//��ת��ʾ
#define LCDCMD_DISPLAY_MODE			    (0xA6)
    #define LCDCFG_DISPLAY_MODE_NORMAL      (0x0)
    #define LCDCFG_DISPLAY_MODE_INVERSE     (0x1)
//Entire display
#define LCDCMD_ALL_PIXEL		        (0xA4)
    #define LCDCFG_ALL_PIXEL_ON             (0x1)
    #define LCDCFG_ALL_PIXEL_NORMAL         (0x0)
//ͼ��ICON control
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
    #define LCDCFG_COM_DIRECTION_NORMAL     (0x0)	//��0~127
    #define LCDCFG_COM_DIRECTION_REVERSE    (0x8)	//��127~0

//�Աȶ� ��Χ��0~63
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
//lcd��ʼ��
VOID STDCALL  LCDDrvInit(VOID);

//���öԱȶ� ������������Ϊ0 ~ 63,ʵ��ʹ������Ϊ15~45
VOID STDCALL LcdDevSetContrast(UCHAR ucValue);
UCHAR STDCALL LcdDevGetContrast(VOID);
VOID STDCALL LcdEnterSavePowerMode(VOID);
//ˢ����Ļ����ʾ�Դ�����
VOID STDCALL RefreshFrameBuf(UINT uX, UINT uY, UINT uDx, UINT uDy, U8 * pFrameBuf);
VOID STDCALL LcdSetPage(U8 page);
VOID STDCALL LcdSetColumn(U8 col);


//lcd����ͼ��͹��������ض�Һ�����У�
//�������ͼ����
    //����֮ǰ��������
    //��֮ǰ�����Ϲر�
    //��֮ǰ�����ϵ���

#define LCDDrvClr()  			LcdDevClear() 
#define GetLCDDrvContrast()     LcdDevGetContrast()
#define SetLCDDrvContrast(v)    LcdDevSetContrast(v)


#endif  //__LCDDRV_H
