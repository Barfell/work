#include "drv_glcd.h"
#include "debug_frmwrk.h"
#include "draw.h"
#include "sdram_k4s561632j.h"
#include "logo.h"

uint8_t 			g_LcdType;
extern uint32_t		C_GLCD_PIX_CLK ;           
extern uint32_t		C_GLCD_H_SIZE ;         
extern uint32_t		C_GLCD_H_PULSE ;        
extern uint32_t		C_GLCD_H_FRONT_PORCH ;  
extern uint32_t		C_GLCD_H_BACK_PORCH ; 
extern uint32_t		C_GLCD_V_SIZE ;         
extern uint32_t		C_GLCD_V_PULSE ;       
extern uint32_t		C_GLCD_V_FRONT_PORCH ;  
extern uint32_t		C_GLCD_V_BACK_PORCH ;   	   	   
extern uint32_t		C_GLCD_BytesPP;



const unsigned char LCD_msg[] =
"**************************************************************************\n\r"
"Chose LCD Size \n\r"
"1 -> 320*240 \n\r"
"2 -> 480*272 \n\r"
"3 -> 800*480 \n\r"
"4 -> 800*600 \n\r"
"***************************************************************************\n\r";


 /*********************************************************************
 * @brief		choose the LCD Size
 * @param[in]	None
 * @return 		g_LcdType
 **********************************************************************/

uint32_t ChooseLcd(void)
{
	uint8_t InChar = 0;

	put_str_("Please Choose LCD:\r\n");
	put_str_("[1] 320*240\r\n");
	put_str_("[2] 480*272\r\n");
	put_str_("[3] 800*480\r\n");
	put_str_("[4] 800*600\r\n");

    while(!((InChar == 0x0d) || (InChar == 0x0a)))
    {
        InChar = getkey();
            if ((InChar >= '0' && InChar <= '4'))
            {
            	switch(InChar){
					case '1':
						g_LcdType = LCD_320_240;
						put_str_("-->320*240\r\n");
						break;
					case '2':
						g_LcdType = LCD_480_272;
						put_str_("-->480*272\r\n");
						break;
					case '3':
						g_LcdType = LCD_800_480;
						put_str_("-->800*480\r\n");
						break;
					case '4':
						g_LcdType = LCD_800_600;
						put_str_("-->800*600\r\n");
						break;
					default:
						break;
            	}
				
				break;
        }
    }
	
	return g_LcdType;
}

/******************************************************************
TFT LCD单个象素的显示数据输出
*******************************************************************/
void PutPixel(uint32_t x,uint32_t y,uint16_t c) 
{ 
    if(x < 320 && y < 240) 
      *(volatile uint16_t *)(LCD_VRAM_BASE_ADDR + 2*(x+320*y)) = c; 
} 

/************************************************************** 
// LCD display is flipped vertically 
// But, think the algorithm by mathematics point. 
//   3 I 2 
//   4 I 1 
//  --+--   <-8 octants  mathematical cordinate 
//   5 I 8 
//   6 I 7 
******************************************************************/
 void Glib_Line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint16_t color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}
/*****************************************************************
      LCD清屏
******************************************************************/
void Lcd_ClearScr(uint32_t x,uint32_t y,uint16_t c) 
{ 

        uint32_t i = 0; 
        while (i < y*x) 
        { 
            *(volatile uint16_t *)(LCD_VRAM_BASE_ADDR + i * 2) = c; 
            i += 1; 
        } 
}

/************************************************************** 
在LCD屏幕上画一个矩形 
**************************************************************/
void Glib_Rectangle(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t color) 
{ 
    Glib_Line(x1,y1,x2,y1,color); 
    Glib_Line(x2,y1,x2,y2,color); 
    Glib_Line(x1,y2,x2,y2,color); 
    Glib_Line(x1,y1,x1,y2,color); 
} 

/************************************************************** 
在LCD屏幕上用颜色填充一个矩形 
**************************************************************/ 
void Glib_FilledRectangle(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t color) 
{ 
    uint32_t i; 

    for(i=y1;i<=y2;i++) 
        Glib_Line(x1,i,x2,i,color); 
}

/**************************************************************
用红绿蓝分别清屏 ，最后显示三原色
 * ***************************************************************/
void LCD_Testclean()
{	 uint32_t i;
  	uint16_t *pDst = (uint16_t *)LCD_VRAM_BASE_ADDR ;
//	GLCD_Dis_Logo(LogoPic.pPicStream, NULL); // display picture

	Lcd_ClearScr(C_GLCD_H_SIZE,C_GLCD_V_SIZE ,0xf800);  //red
	GLCD_Ctrl (TRUE);
	Delay(1000);

	Lcd_ClearScr(C_GLCD_H_SIZE,C_GLCD_V_SIZE,0x07e0);  //green
	Delay(1000);

	Lcd_ClearScr(C_GLCD_H_SIZE,C_GLCD_V_SIZE,0x001f);  //bule*/
	Delay(1000);

	  for (i=0; i<C_GLCD_H_SIZE*C_GLCD_V_SIZE; i++)
        {
			if(i<C_GLCD_H_SIZE*C_GLCD_V_SIZE/3)
				*pDst++ = 0xf800;        // Blue -- 0x001F,green -- 0x07e0,red -- 0xf800
        	else if(i<2*C_GLCD_H_SIZE*C_GLCD_V_SIZE/3)
        		*pDst++ = 0x07e0;
        	else
        		*pDst++ = 0x001F;
        }	
	
}
/*********************************************************************
 * @brief		Test the LCD 
 * @param[in]	None
 * @return 		NOne
 **********************************************************************/
void LCD_Test_menu(void)
{
	GLCD_Ctrl (FALSE);
	ChooseLcd();
	GLCD_Init(g_LcdType);
	//
	LCD_Testclean();	
}


void LCD_menu(void)
{		uint8_t	 rechar,LCDSTYPE;
		put_str_(LCD_msg);
		put_str_("please input 1，2，3，4 choose to the LCD type or input ESC exit this menu\n\r");
		while(1)
		{
			rechar=getkey();
			if(rechar!=0)
			{
			putchar(rechar);
	   		while(getkey()!= 0x0d);  //等待回车键输入执行
		
				switch(rechar){
				case '1':
					LCDSTYPE=35;
					put_str_("Test 320*240 LCD\n\r");
					GLCD_Ctrl (FALSE);
					GLCD_Init(LCDSTYPE);
					LCD_Testclean()	;				
				break;
				case '2':
					LCDSTYPE=43;
					put_str_("Test 480*272 LCD\n\r");
					GLCD_Ctrl (FALSE);
					GLCD_Init(LCDSTYPE);
					LCD_Testclean()	;											
				break;
				case '3':
					LCDSTYPE=70;
					put_str_("Test 800*480 LCD\n\r");
					GLCD_Ctrl (FALSE);
					GLCD_Init(LCDSTYPE);		
					LCD_Testclean();				
				break;
					case '4':
					LCDSTYPE=80;
					put_str_("Test 800*600 LCD\n\r");
					GLCD_Ctrl (FALSE);
					GLCD_Init(LCDSTYPE);		
					LCD_Testclean();				
				break;
				default:
				putchar(rechar);
				break;	
			}
			while(getkey()!=0x1b);
			break;
			}			
		//break;
	}

}