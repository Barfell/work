#include "comm.h"
#include "display.h"
#include "GUI.h"
#include "syn.h" 
#include "CPLD.h" 

BOOL g_bPlugin = FALSE;
BOOL g_bSart = FALSE;
VOID TestCommProc(VOID)
{
	U16 u16Length;
	U8 u8High, u8Low;
	
	LCDDrvClr();	
	
	Lcd_Show_Menu_16(16,2,2);//
	Lcd_Show_Menu_16(48,2,3);//
	Lcd_Show_Menu_16(80,2,31);//中
	
	while(1)
	{
		u16Length = GetUsartCurrentLength(USART2_TYPE);
		ClearUsartCurrentLength(USART2_TYPE);
		if(u16Length == 12)
		{
			if((g_pUsart2_rx_buf[0] == COMM_HEADER) && (g_pUsart2_rx_buf[10] == COMM_END1) && (g_pUsart2_rx_buf[11] == COMM_END2))
			{
				if(g_pUsart2_rx_buf[3] == COMM_SUBCMD_DISPLAY_PERCENTAGE)
				{
					u8High = g_pUsart2_rx_buf[7] + 16;
					u8Low = g_pUsart2_rx_buf[8] + 16;
					Lcd_Show_Menu_16(16,6,10);//保
					Lcd_Show_Menu_16(32,6,11);//存
					Lcd_Show_Menu_16(48,6,31);//中

					Lcd_Show_num_16(72,6,u8High);//16-->0
					Lcd_Show_num_16(80,6,u8Low);//18-->2
					Lcd_Show_num_16(88,6,5);//%
				}
				if(g_pUsart2_rx_buf[3] == COMM_SUBCMD_DISPLAY_INSTRUCTION)
				{
					u8High = g_pUsart2_rx_buf[7] + 16;
					u8Low = g_pUsart2_rx_buf[8] + 16;
					Lcd_Show_Menu_16(16,10,14);
					Lcd_Show_Menu_16(32,10,32);
					Lcd_Show_Menu_16(48,10,31);//中

					Lcd_Show_num_16(72,10,u8High);//16-->0
					Lcd_Show_num_16(80,10,u8Low);//18-->2

				}
			}
							
		}
		
		if(GetKeyNumber() != KEY_INVALID)
		{
			SendCommData(COMM_KEY);
			SetKeyNumber(KEY_INVALID);
		}
		
	}
}

//测试主板控制GUI显示
VOID TestCommGuiProc(VOID)
{
	U16 u16Length;
	U8 szBuf[20];
	U8 u8Value;
	
	while(1)
	{
		u16Length = GetUsartCurrentLength(USART2_TYPE);
		if(u16Length != 0)
		{
			ClearUsartCurrentLength(USART2_TYPE);
			u16Length = MAKEWORD(g_pUsart2_rx_buf[5], g_pUsart2_rx_buf[4]);
			if((g_pUsart2_rx_buf[0] == COMM_HEADER) && (g_pUsart2_rx_buf[u16Length + 10] == COMM_END1) && (g_pUsart2_rx_buf[u16Length + 11] == COMM_END2))
			{
				u8Value = CalcCheckSum(g_pUsart2_rx_buf + 1, 12 + u16Length - 4);
				if((g_pUsart2_rx_buf[3] == COMM_SUBCMD_DISPLAY_STRING) && (u8Value == g_pUsart2_rx_buf[9 + u16Length]))
				{
					memcpy(szBuf, g_pUsart2_rx_buf + 9, u16Length);
					*(szBuf + u16Length) = '\0';
					GUI_Clear();
					GUI_DispStringAt((char *)szBuf, g_pUsart2_rx_buf[7], g_pUsart2_rx_buf[8]); 
				}
			}
		}
		
	}
}

EXTERN BOOL g_bMileGaugeAccess;

    
VOID TestKeyGuiProc(VOID)
{
    U32 u32Tick, u32KeyCount;
    U16 u16Count = 600;
	U8 u8KeyNumber;
	U8 szData[20] = {0};
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
	GUI_Clear();
    
    GUI_DispStringAt("Esc Exit test", 0, LINE_1);
    
    
    GUI_DispStringAt("Please wait...", 0, LINE_3);
    
    pOldFont = GUI_SetFont(&GUI_FontD24x32);
    
    u32Tick = GetTickCount();
    
    while(1)
    {
			
        if(GetKeyNumber() == KEY_EXIT)
        {
            SetKeyNumber(KEY_INVALID);
            break;
        }
        
        if((GetTickCount() - u32Tick) > 1000)
        {
            u32Tick = GetTickCount();
            
            u16Count--;
            
            sprintf((char *)szData, "%d", u16Count);

            GUI_DispStringAt((char *)szData, 0, 48); 
            
            if(u16Count < 1)
            {
                break;
            }
        }

    }
    
    GUI_SetFont(pOldFont);
    
    pOldFont = GUI_SetFont(&GUI_Font8x9);//GUI_Font6x8
    
    GUI_Clear();
    
	GUI_DispStringAt("Enter start test", 0, LINE_1);
	
	GUI_DispStringAt("Right Save test", 0, LINE_3);
	
	GUI_DispStringAt("Left Stop test", 0, LINE_5);
	
	GUI_DispStringAt("Esc Exit test", 0, LINE_7);
	
    while(1)
    {
        if(g_bSart == TRUE)
        {
            u32KeyCount = 0;
            while((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8) != RESET) && (u32KeyCount < 0xffff))
            {
                u32KeyCount++;
            }
            if(u32KeyCount > 0xfffe)
            {
                SetKeyNumber(KEY_2);
            }
        }
		u8KeyNumber = GetKeyNumber();
			
		if(u8KeyNumber != KEY_INVALID)
		{
			
			
			if(u8KeyNumber == KEY_EXIT)
			{
				SetKeyNumber(KEY_INVALID);
				break;
			}
			else 
			{
                if(g_bPlugin == FALSE)
                {
                    SendCommData(COMM_KEY);
                   
                    if(u8KeyNumber == KEY_RIGHT)
                    {
                        g_bPlugin = TRUE;
                        GUI_Clear();
                        GUI_DispStringAt("Save processing", 0, LINE_5);
                        g_bMileGaugeAccess = FALSE;//保存的时候强制不再输出
                        CpldOff();
                    }
                    else if(u8KeyNumber == KEY_LEFT)
                    {
                        
                        GUI_Clear();
                        GUI_DispStringAt("Stop processing", 0, LINE_5);
                    }
                    else if(u8KeyNumber == KEY_ENTER)
                    {
                        GUI_Clear();
                        GUI_DispStringAt("Test processing", 0, LINE_5);
                        g_bSart = TRUE;
                    }	
                }				
				SetKeyNumber(KEY_INVALID); 
			}
			
				
		}
		
		ReceiveCommData();
        
        HandleSynDataProc();
		
		
    }
	GUI_SetFont(pOldFont);
        
}

