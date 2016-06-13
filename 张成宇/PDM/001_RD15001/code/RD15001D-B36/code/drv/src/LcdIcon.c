#include "LcdIcon.h"


STATIC U16  IconsState = 0;

   
STATIC STDCALL VOID LcdSetDot(VOID)
{
   UINT uPage = 0;
   for(; uPage < ICON_PAGE_NUM; uPage++)
   {
       LcdSetPage(ICON_PAGE1 + uPage);
       LcdSetColumn(ICON_COL);
       LcdTransData((IconsState>>(uPage*8)) & 0xFF);
	   LcdTransData((IconsState>>(uPage*8)) & 0xFF);
   }
}
/**********************************************************************************
* Procedure:	LcdSetIcon
* Function:     ����Һ��ͼ��
* Parameter:    wItem
*                   ICON_CONNECT_PC	
                    ICON_LOCK		
                    ICON_PINYIN		
                    ICON_RESERVE1
                    ICON_ZIMU	
                    ICON_RESERVE2	
                    ICON_FUHAO	
                    ICON_SHUZI	
                    ICON_BH     

                    ICON_SIGNAL_INTENSITY5	
                    ICON_SIGNAL_INTENSITY4
                    ICON_SIGNAL_INTENSITY3
                    #CON_SIGNAL_INTENSITY2	
                    ICON_SIGNAL_INTENSITY1	
                    ICON_SIGNAL_STATION	
                    ICON_DOWNLOAD	
                    ICON_UPLOAD	
                    ���Ϻ������ϣ�
                    //����ͼ����Ϻ�
                    #define ICON_ALL        0xFFFF
                    #define ICON_SIGNAL0	ICON_SIGNAL_STATION
                    #define ICON_SIGNAL1	(ICON_SIGNAL_STATION | ICON_SIGNAL_INTENSITY1)
                    #define ICON_SIGNAL2	(ICON_SIGNAL_STATION | ICON_SIGNAL_INTENSITY1 | ICON_SIGNAL_INTENSITY2)
                    #define ICON_SIGNAL3	(ICON_SIGNAL_STATION | ICON_SIGNAL_INTENSITY1 | ICON_SIGNAL_INTENSITY2 | ICON_SIGNAL_INTENSITY3)
                    #define ICON_SIGNAL4	(ICON_SIGNAL_STATION | ICON_SIGNAL_INTENSITY1 | ICON_SIGNAL_INTENSITY2 | ICON_SIGNAL_INTENSITY3 | ICON_SIGNAL_INTENSITY4)
                    #define ICON_SIGNAL5	(ICON_SIGNAL_STATION | ICON_SIGNAL_INTENSITY1 | ICON_SIGNAL_INTENSITY2 | ICON_SIGNAL_INTENSITY3 | ICON_SIGNAL_INTENSITY4 | ICON_SIGNAL_INTENSITY5)

                    #define ICON_PC_UP		(ICON_CONNECT_PC | ICON_UPLOAD)
                    #define ICON_PC_DOWN	(ICON_CONNECT_PC | ICON_DOWNLOAD)
*               wStyle
                    
                    LSI_SET = 0x00, ����֮ǰ��������
                    LSI_OFF,        ��֮ǰ�����Ϲر�
                    LSI_ON,         ��֮ǰ�����ϵ���
* Result:		
* Description:	
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
*
***********************************************************************************/
VOID STDCALL LcdSetIcon(U16 wItems, U16 wStyle)
{
    if(wStyle == LSI_SET)
    {
        IconsState = wItems;
    }
    else
    {
        if(wStyle == LSI_ON)
       {
            IconsState |= wItems;
       }
        else
       {
            IconsState &= ~wItems;
       }
    }
    LcdSetDot();
}

/************************************************************************
* Procedure:	LcdSetArrow
* Function:	    ��ʾ��Ļ�ұ�ͼ��,��������
* Parameters:	usVal--Ҫ��ʾ��ͼ��.ȡֵ��Χ��0~0x1fff��
				��3λ:����,���¼�ͷ���м���
				��10λ:�Ӹ����Ͷ�Ӧ�ڴ������µĺ��
* Result:		��
* Description:	
* Attribute:    Hidden
*************************************************************************
* LOG	DATE	AUTHOR		ACTION
*************************************************************************
* 2011-10-9		tao.lan		Create this procedure
*************************************************************************/    
VOID STDCALL LcdSetArrow(UINT wVal)
{
   wVal &= 0x1FFF;
   U16 uArrow = 0;
   UINT uPage = 0;
   if(wVal & LCD_ARROW_UP)
   {
       uArrow |= ARROW_UP;
   }
   if(wVal & LCD_ARROW_DOWN)
   {
       uArrow |= ARROW_DOWN;
   }
   if(wVal & LCD_ARROW_MID_LINE)
   {
       uArrow |= ARROW_MIDLINE;
   }
   wVal = (wVal & 0x3FF)<<5UL;
   uArrow |= wVal;    
   for(; uPage < ARROW_PAGE_NUM; uPage++)
   {
       LcdSetPage(ARROW_PAGE1 + uPage);
       LcdSetColumn(ARROW_COL);
       LcdTransData((uArrow>>(uPage*8)) & 0xFF);
	   LcdTransData((uArrow>>(uPage*8)) & 0xFF);
   }
}

void LcdClearIcon(void)
{
    
}
