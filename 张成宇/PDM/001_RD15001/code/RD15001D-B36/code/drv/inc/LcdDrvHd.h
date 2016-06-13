/**********************************************************************
* Module:	   DRIVER\lcdhd
* Function:
* Description:	液晶
* Log:	
**********************************************************************/
#ifndef	__LCDDRVHD_H
#define	__LCDDRVHD_H

#include "kernal.h"
/**************************** LCD IO 配置 ******************************/
#define LCD_CS_GPIO			GPIOA	
#define LCD_CS_PIN			GPIO_Pin_12	
#define LCD_RST_GPIO		GPIOA	
#define LCD_RST_PIN			GPIO_Pin_15	
#define LCD_WR_GPIO			GPIOC	
#define LCD_WR_PIN			GPIO_Pin_11	
#define LCD_RD_GPIO			GPIOC	
#define LCD_RD_PIN			GPIO_Pin_12
#define LCD_RS_GPIO			GPIOC	
#define LCD_RS_PIN			GPIO_Pin_10	
#define LCD_BL_GPIO         GPIOB
#define LCD_BL_PIN          GPIO_Pin_3
#define LCD_DATA_GPIO       GPIOD
#define LCD_DATA_PIN        GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7


#define LCD_CS_H  GPIO_SetBits(LCD_CS_GPIO, LCD_CS_PIN);
#define LCD_RST_H GPIO_SetBits(LCD_RST_GPIO,LCD_RST_PIN);
#define LCD_WR_H  GPIO_SetBits(LCD_WR_GPIO, LCD_WR_PIN);
#define LCD_RD_H  GPIO_SetBits(LCD_RD_GPIO, LCD_RD_PIN);
#define LCD_RS_H  GPIO_SetBits(LCD_RS_GPIO, LCD_RS_PIN);
#define LCD_BL_H  GPIO_SetBits(LCD_BL_GPIO, LCD_BL_PIN);

#define LCD_CS_L  GPIO_ResetBits(LCD_CS_GPIO, LCD_CS_PIN);
#define LCD_RST_L GPIO_ResetBits(LCD_RST_GPIO, LCD_RST_PIN);
#define LCD_WR_L  GPIO_ResetBits(LCD_WR_GPIO, LCD_WR_PIN);
#define LCD_RD_L  GPIO_ResetBits(LCD_RD_GPIO, LCD_RD_PIN);
#define LCD_RS_L  GPIO_ResetBits(LCD_RS_GPIO, LCD_RS_PIN);
#define LCD_BL_L  GPIO_ResetBits(LCD_BL_GPIO, LCD_BL_PIN);

#define LCD_DATA_PORT	GPIOD
								
#define LCD_BL_ON_HIGH

typedef enum
{
    LCD_CMD,
    LCD_DATA
}LCD_DataType;

// -----------------------接口定义-------------------------------------------
//开关背光
VOID STDCALL LcdBackLightOn(VOID);
VOID STDCALL LcdBackLightOff(VOID);
VOID STDCALL LcdReset(VOID);
//lcd初始化硬件部分
VOID STDCALL LcdInitHd(VOID);
VOID STDCALL WriteToLcd(LCD_DataType type, U8 data);

#define LcdTransCmd(cmd)        WriteToLcd(LCD_CMD, cmd);  
#define LcdTransData(data)      WriteToLcd(LCD_DATA, data);
#define LcdDelayUs(n)   		DelayUs_Sft(n)

#endif //__LCDDRVHD_H
