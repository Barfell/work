/**********************************************************************
* Module:	   DRIVER\lcd
* Function:
* Description:	液晶
* Log:	
**********************************************************************/

#include "LcdDrvHd.h"

//写一个数据
//STATIC VOID Lcd_Write_DAT(U8 dat)
//{
//	LCD_RS_H
//	LCD_RD_H
//	LCD_DATA_PORT->ODR &= 0xff00;
//	LCD_DATA_PORT->ODR |= dat;
//	LCD_WR_L
//	LCD_WR_H
//}

//STATIC VOID Lcd_Write_CMD(U8 cmd)
//{
//	LCD_RS_L
//	LCD_RD_H
//	LCD_DATA_PORT->ODR &= 0xff00;
//	LCD_DATA_PORT->ODR |= cmd;
//	LCD_WR_L
//	LCD_WR_H
//}
////8080
STATIC VOID Lcd_Write_DAT(U8 dat)
{
	LCD_RS_H
	LCD_RD_H
	LCD_WR_L
	LCD_DATA_PORT->ODR &= 0xff00;
	LCD_DATA_PORT->ODR |= dat;
	LCD_WR_H
}

STATIC VOID Lcd_Write_CMD(U8 cmd)
{
	LCD_RS_L
	LCD_RD_H
	LCD_WR_L
	LCD_DATA_PORT->ODR &= 0xff00;
	LCD_DATA_PORT->ODR |= cmd;
	LCD_WR_H
}
////6800
//STATIC VOID Lcd_Write_DAT(U8 dat)
//{
//	LCD_RS_H
//	LCD_RD_H
//	LCD_WR_L
//	LCD_DATA_PORT->ODR &= 0xff00;
//	LCD_DATA_PORT->ODR |= dat;
//	LCD_RD_L
//}

//STATIC VOID Lcd_Write_CMD(U8 cmd)
//{
//	LCD_RS_L
//	LCD_RD_H
//	LCD_WR_L
//	LCD_DATA_PORT->ODR &= 0xff00;
//	LCD_DATA_PORT->ODR |= cmd;
//	LCD_RD_L
//}

//U8 Lcd_READ_DAT(VOID)
//{
//	U16 u16Value;
//	LCD_RS_H
//	LCD_WR_H
//	
//	
//	LCD_RD_H
//	LCD_RD_L
//	LCD_WR_L
//	u16Value = (LCD_DATA_PORT->ODR & 0xffff);
////	u16Value = u16Value | LCD_DATA_PORT->ODR;
//	return u16Value;
//	
//}

U8 Lcd_READ_DAT(VOID)
{
	U16 u16Value;
	LCD_CS_L
	LCD_RS_H
	LCD_WR_H
	LCD_RD_L
	u16Value = (LCD_DATA_PORT->ODR & 0xffff);
	u16Value = u16Value | LCD_DATA_PORT->ODR;
	LCD_CS_H
	return u16Value;
	
}
VOID STDCALL LcdReset(VOID)
{
	LCD_RST_L
    LcdDelayUs(10);	
    LCD_RST_H
	//延时等待复位操作完成
	LcdDelayUs(20);	
}

VOID STDCALL LcdInitHd(VOID)
{
	
	GPIO_InitTypeDef Lcd_GPIO;
	    //设置IO口时钟        
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	 
  
    //管脚模式:输出口  
    Lcd_GPIO.GPIO_Mode = GPIO_Mode_OUT;      
    //类型:推挽模式  
    Lcd_GPIO.GPIO_OType = GPIO_OType_PP;    
    //上拉下拉设置  
    Lcd_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    //IO口速度  
    Lcd_GPIO.GPIO_Speed = GPIO_Speed_100MHz;  
    //管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_DATA_PIN;  
    //初始化  
    GPIO_Init(LCD_DATA_GPIO, &Lcd_GPIO); 
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_CS_PIN; 
	//初始化  CS
    GPIO_Init(LCD_CS_GPIO, &Lcd_GPIO); 
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_RST_PIN; 
	//初始化 RST
    GPIO_Init(LCD_RST_GPIO, &Lcd_GPIO); 
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_BL_PIN; 
	//初始化  BKL
    GPIO_Init(LCD_BL_GPIO, &Lcd_GPIO); 
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_RS_PIN; 
	//初始化  RS
    GPIO_Init(LCD_RS_GPIO, &Lcd_GPIO);
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_WR_PIN; 
	//初始化  WR
    GPIO_Init(LCD_WR_GPIO, &Lcd_GPIO);
	
	//管脚指定  
    Lcd_GPIO.GPIO_Pin = LCD_RD_PIN; 
	//初始化  RD
    GPIO_Init(LCD_RD_GPIO, &Lcd_GPIO);
	
    
    LCD_CS_H
}


VOID STDCALL LcdBackLightOn(VOID)
{
#ifdef LCD_BL_ON_HIGH
    LCD_BL_H
#elif defined LCD_BL_ON_LOW
    LCD_BL_L
#else
	#error "please define LCD_BL_ON_HIGH or LCD_BL_ON_LOW"
#endif
}

VOID STDCALL LcdBackLightOff(VOID)
{
#ifdef LCD_BL_ON_HIGH
    LCD_BL_L
#elif defined LCD_BL_ON_LOW
    LCD_BL_H
#else
	#error "please define LCD_BL_ON_HIGH or LCD_BL_ON_LOW"
#endif
}


VOID STDCALL WriteToLcd(LCD_DataType type, U8 data)
{
	LCD_CS_L
    
    if(LCD_CMD == type)
    {
        Lcd_Write_CMD(data);
    }
    else
    {
       Lcd_Write_DAT(data);
    }
    
    LCD_CS_H
}
