#include "key.h"
#include "display.h" 
#include "GUI.h"
#include "comm.h"
#include "syn.h"
#include "test.h"

extern const GUI_FONT GUI_FontHZ12;

#define	DISPALY_ITEM_NUMBER	5
enum
{
    DISPLAY_BOARDINFO = 0,
    DISPLAY_MILEDATA,
    KEY_GUI,
    ADJUST_GAIN,
    SET_SUPERSOUND,
};
STATIC U8 g_u8SelectCount = 0;
STATIC U8 g_szStart[] = " 深圳大铁 ";
STATIC U8 g_szWindow[DISPALY_ITEM_NUMBER][20] = 
{
//	{"Dislpay board infor"},
//	{"Dislpay mile infor"},
//	{"Enter measure"},
//	{"Enter Rfid Adjust"},
	
	{"显示设备信息"},
	{"显示里程信息"},
	{"进入测试"},
	{"RFID增益设置"},
    {"轨枕参数设置"},
	
};

STATIC VOID ReadLockId(U32 *pData)
{
//	U32 u32CpuID[3];
	//获取CPU唯一ID
	pData[0]=*(vu32*)(0x1FFF7A10);
	pData[1]=*(vu32*)(0x1FFF7A14);
	pData[2]=*(vu32*)(0x1FFF7A18);

}
STATIC VOID DisplayBoardInfo(VOID)
{
	U32 szId[3];
	U8 u8KeyNumber;
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
	pOldFont = GUI_SetFont(&GUI_Font8x9);//GUI_Font6x8
	GUI_Clear();
	ReadLockId(szId);
	GUI_DispStringAt("Board Id:", 0, LINE_1);
	
	GUI_DispHexAt(szId[0], 0, LINE_3, 8);
	GUI_DispHexAt(szId[1], 0, LINE_5, 8);
	GUI_DispHexAt(szId[2], 0, LINE_7, 8);
	
	while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);	
			if(u8KeyNumber == KEY_EXIT)
			{
				GUI_Clear();
				break;
			}
					
						
		}
		
	}
	GUI_SetFont(pOldFont);
}

STATIC VOID SetRailPillow(VOID)
{
    
    U8 u8KeyNumber;
    U8 szData[30] = {0};
	U16 u16Count;
	U32 u32Tick;
    
    const GUI_FONT GUI_UNI_PTR *pOldFont;
	
	pOldFont = GUI_SetFont(&GUI_Font8x9);//GUI_Font6x8
SetRailPillow_begain: 
    
	GUI_Clear();
	GUI_DispStringAt("Set rail pillow", 0, LINE_1);
    
    
    
    while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);	
			if(u8KeyNumber == KEY_EXIT)
			{
				GUI_Clear();
				goto SetRailPillow_exit;
			}
            
            else if(u8KeyNumber == KEY_LEFT)
            {
                GUI_Clear();
                goto SetRailPillow_begain;
            }
            
            else if(u8KeyNumber == KEY_RIGHT)
            {
                GUI_Clear();
                break;
            }
           
            else if(u8KeyNumber == KEY_ENTER)
            {
                memset(szData, 0, sizeof(szData));
                sprintf((char *)szData, "$SET,1\r\n");
                u16Count = strlen((char *)szData);
            	USART1_Send(szData, &u16Count);
                
                u32Tick = GetTickCount();
                while(1)
                {
                    u16Count = GetUsartCurrentLength(USART1_TYPE);
                    if(u16Count != 0)
                    {
                        memset(szData, 0, sizeof(szData));
                        memcpy(szData, g_pUsart1_rx_buf, u16Count);
                        ClearUsartCurrentLength(USART1_TYPE);
                        GUI_DispStringAt((char *)szData, 0, LINE_7);
                        break;
                    }
                    
                    if((GetTickCount() - u32Tick) > 2000)
					{
						sprintf((char *)szData, "Set   fail");
						GUI_DispStringAt((char *)szData, 0, LINE_7);
						break;
					}
                }
           
            }
		}
	}
    
    GUI_Clear();
	GUI_DispStringAt("Set rail", 0, LINE_1);
    
    while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);	
			if(u8KeyNumber == KEY_EXIT)
			{
				GUI_Clear();
				goto SetRailPillow_exit;
			}
            
            else if(u8KeyNumber == KEY_LEFT)
            {
                GUI_Clear();
                goto SetRailPillow_begain;
            }
            
            else if(u8KeyNumber == KEY_RIGHT)
            {
                GUI_Clear();
                break;
            }
           
            else if(u8KeyNumber == KEY_ENTER)
            {
                memset(szData, 0, sizeof(szData));
                sprintf((char *)szData, "$SET,2\r\n");
                u16Count = strlen((char *)szData);
            	USART1_Send(szData, &u16Count);
                
                u32Tick = GetTickCount();
                while(1)
                {
                    u16Count = GetUsartCurrentLength(USART1_TYPE);
                    if(u16Count != 0)
                    {
                        memset(szData, 0, sizeof(szData));
                        memcpy(szData, g_pUsart1_rx_buf, u16Count);
                        ClearUsartCurrentLength(USART1_TYPE);
                        GUI_DispStringAt((char *)szData, 0, LINE_7);
                        break;
                    }
                    
                    if((GetTickCount() - u32Tick) > 2000)
					{
						sprintf((char *)szData, "Set   fail");
						GUI_DispStringAt((char *)szData, 0, LINE_7);
						break;
					}
                }
           
            }
		}
	}
        
    
SetRailPillow_exit:   
    
	GUI_SetFont(pOldFont);
    
}
STATIC VOID AdjustRfidGain(VOID)
{
	U8 u8KeyNumber;
    U8 u8AdjustGain = 0;
    U8 szData[10] = {0};
	U16 u16Count;
	U32 u32Tick;
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
	pOldFont = GUI_SetFont(&GUI_Font8x9);//GUI_Font6x8
	GUI_Clear();
	GUI_DispStringAt("Adjust rfid gain", 0, LINE_1);
		
	while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);	
			if(u8KeyNumber == KEY_EXIT)
			{
				GUI_Clear();
				break;
			}
            else if(u8KeyNumber == KEY_RIGHT)
            {
                if(u8AdjustGain < 30)
                {
                    u8AdjustGain = u8AdjustGain + 5;
                    sprintf((char *)szData, "gain = %3d", u8AdjustGain);
                    GUI_ClearRect(0, LINE_5,  128, LINE_5 + 7);//这里加7是因为避免影响下一行的数据
//                    GUI_DispHexAt((char *)szData, 0, LINE_5, 8);
                    GUI_DispStringAt((char *)szData, 0, LINE_5);
                }
                
                
            }
            else if(u8KeyNumber == KEY_LEFT)
            {
                if(u8AdjustGain > 5)
                {
                    u8AdjustGain = u8AdjustGain - 5;
                    sprintf((char *)szData, "gain = %3d", u8AdjustGain);
                    GUI_ClearRect(0, LINE_5,  128, LINE_5 + 7);//这里加7是因为避免影响下一行的数据
//                    GUI_DispHexAt((char *)szData, 0, LINE_5, 8);
                    GUI_DispStringAt((char *)szData, 0, LINE_5);
                }
            }
            else
            {
                u16Count = 3;
                szData[0] = 0xfe;
                szData[1] = 0xfe;
                szData[2] = u8AdjustGain;
            	USART1_Send(szData, &u16Count);
				u32Tick = GetTickCount();
                while(1)
                {
                    u16Count = GetUsartCurrentLength(USART1_TYPE);
                    if(u16Count != 0)
                    {
                        ClearUsartCurrentLength(USART1_TYPE);
                        if(u16Count == 3)
                        {
                            if((g_pUsart1_rx_buf[0] == 0xef) && (g_pUsart1_rx_buf[1] == 0xfe) && (g_pUsart1_rx_buf[2] == u8AdjustGain))
                            {
                                sprintf((char *)szData, "Set   over");
//                                GUI_DispHexAt((char *)szData, 0, LINE_7, 8);
                                GUI_DispStringAt((char *)szData, 0, LINE_7);
								break;
                            }
                        }
                    }
					
					if((GetTickCount() - u32Tick) > 2000)
					{
						sprintf((char *)szData, "Set   fail");
						GUI_DispStringAt((char *)szData, 0, LINE_7);
						break;
					}
                 
                }
                
            }
		}
		
	}
	GUI_SetFont(pOldFont);
}

STATIC VOID IdleWindow(VOID)
{
	GUI_Clear();
	
	GUI_DispStringAt((char *)g_szStart, 40, LINE_6);	
}


//主要的任务
VOID TestGuiProc(VOID)
{
		
	U8 u8KeyNumber;
	
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	
//	pOldFont = GUI_SetFont(&GUI_Font8x9);//GUI_Font6x8
	pOldFont = GUI_SetFont(&GUI_FontHZ12);  
	
	IdleWindow(); 
	
	
	while(1)
	{
		u8KeyNumber = GetKeyNumber();
		
		if(u8KeyNumber != KEY_INVALID)
		{
			SetKeyNumber(KEY_INVALID);
			
			if(u8KeyNumber == KEY_EXIT)
			{
				break;
			}
			else if(u8KeyNumber == KEY_LEFT)
			{
				if(g_u8SelectCount == 0)
				{
					g_u8SelectCount = DISPALY_ITEM_NUMBER;
				}
				g_u8SelectCount--;
				
			}
			else if(u8KeyNumber == KEY_RIGHT)
			{
				g_u8SelectCount++;
				if(g_u8SelectCount == DISPALY_ITEM_NUMBER)
				{
					g_u8SelectCount = 0;
				}
			}
			else if(u8KeyNumber == KEY_ENTER)
			{
				if(g_u8SelectCount == DISPLAY_BOARDINFO)
				{
					DisplayBoardInfo();
				}
				else if(g_u8SelectCount == DISPLAY_MILEDATA)
				{
					DisplayMileDataProc();
				}
				else if(g_u8SelectCount == KEY_GUI)
				{
					TestKeyGuiProc();
				}
                else if(g_u8SelectCount == ADJUST_GAIN)
                {
                    AdjustRfidGain();//rfid
                }
                else if(g_u8SelectCount == SET_SUPERSOUND)
                {
                    SetRailPillow();//里程
                }
			}
			GUI_Clear();
			GUI_DispStringAt((char *)g_szWindow[g_u8SelectCount], 0, LINE_1);				
							
		}
		
	}
	
	GUI_SetFont(pOldFont);
	
	  
}
