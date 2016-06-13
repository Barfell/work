/**********************************************************************
* Module:	   DRIVER\lcd
* Function:
* Description:	Һ��
* Log:	
**********************************************************************/
#include "LcdDrv.h"


//�Աȶ�
STATIC UCHAR gContrast = LCD_CONTRAST_DEF;	

/**********************************************************************************
* Procedure:	LcdDevClear
* Function:		lcd����
* Parameter:	NULL
* Result:		NULL
* Description:	lcd������ʵ�������0x00����
* Attribute:    Hidden
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
***********************************************************************************/
VOID STDCALL LcdDevClear(VOID)
{
    UINT uLoop;
    UINT uPage;
    
    for(uPage = 0; uPage < LCD_PAGE_NUM; ++uPage)
    {
    	LcdSetPage(uPage);
        LcdSetColumn(0 + LCD_COL_OFFSET);
        for(uLoop = (0 + LCD_COL_OFFSET); uLoop < LCD_COL_NUM; ++uLoop)
    	{ 
    	    LcdTransData(0x00);
            LcdTransData(0x00);//LM9033AҺ������д���Σ�дһ�λ�ܵ�
        }
    }
    LcdClearIcon();
}

/**********************************************************************************
* Procedure:	LCDDrvInit
* Function:		lcd��ʼ��
* Parameter:	NULL
* Result:		SUCCESS
* Description:	��ʼ�����̰���ST7567�ֲ��д
* Attribute:    Hidden
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
***********************************************************************************/
VOID STDCALL LCDDrvInit(VOID)
{
    LcdInitHd();
    DelayMs_Sft(1);    //wait power stable
    LcdReset();
	LcdTransCmd(0x48);LcdTransCmd(0x60);
	LcdTransCmd(0xA1);
	LcdTransCmd(0xC8);
	LcdTransCmd(0x44);LcdTransCmd(0x10);//������ʼcom��2�ֽڣ�����Ϊ16�п�ʼ
	LcdTransCmd(0x40);LcdTransCmd(0x00);//������ʼ�У�2�ֽ�
	LcdTransCmd(0xAB);
	LcdTransCmd(0x66);
	LcdTransCmd(0x27);
	LcdTransCmd(0x81);LcdTransCmd(0x20);
	LcdTransCmd(0x54);
	LcdTransCmd(0x94);
	LcdTransCmd(0x88);LcdTransCmd(0x00);
	LcdTransCmd(0x89);LcdTransCmd(0x00);
	LcdTransCmd(0x8A);LcdTransCmd(0x09);
	LcdTransCmd(0x8B);LcdTransCmd(0x00);
	LcdTransCmd(0x8C);LcdTransCmd(0x99);
	LcdTransCmd(0x8D);LcdTransCmd(0x00);
	LcdTransCmd(0x8E);LcdTransCmd(0x99);
	LcdTransCmd(0x8F);LcdTransCmd(0x09);
	LcdTransCmd(0x2C);LcdDelayUs(50);
	LcdTransCmd(0x2E);LcdDelayUs(50);
	LcdTransCmd(0x2F);LcdDelayUs(50);
	LcdTransCmd(0xAF);
	
	//����ͼ��
	LcdTransCmd(LCDCMD_ICON_CONTROL | LCDCFG_ICON_ENABLE);
	
	LcdBackLightOn();
	//����
	LCDDrvClr();

}


/**********************************************************************************
* Procedure:	LcdDevSetContrast
* Function:		lcd���öԱȶ�
* Parameter:	
* Result:		
* Description:	���öԱȶ� .������������Ϊ0 ~ 63,ʵ��ʹ������Ϊ15~45����������޸Ĵ�����֧�ִ�0��63��΢��
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
***********************************************************************************/
VOID STDCALL LcdDevSetContrast(UCHAR ucValue)
{
	gContrast = ucValue & 0x003F;
	if(gContrast < LCD_CONTRAST_MIN)
    {
		gContrast = LCD_CONTRAST_MIN;
    }
	else if(gContrast > LCD_CONTRAST_MAX)
	{
    	gContrast = LCD_CONTRAST_MAX;
	}
    
    LcdTransCmd(LCDCMDDB_SET_CONTRAST);
    
    LcdTransCmd(gContrast);
}

/**********************************************************************************
* Procedure:	LcdDevGetContrast
* Function:		��ȡ�Աȶ�
* Parameter:	
* Result:		
* Description:	
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
***********************************************************************************/
UCHAR STDCALL LcdDevGetContrast(VOID)
{
    return gContrast;
}

VOID STDCALL LcdEnterSavePowerMode(VOID)
{
    LcdTransCmd(LCDCMD_DISPLAY_OFF);
    LcdTransCmd(LCDCMD_ALL_PIXEL | LCDCFG_ALL_PIXEL_ON);
}

VOID STDCALL LcdSetPage(U8 page)
{
    U8  pageTemp;
    pageTemp = page | LCDCMD_SET_PAGE_ADDRESS;
    WriteToLcd(LCD_CMD, pageTemp);
}

VOID STDCALL LcdSetColumn(U8 col)
{
	U8  columnTemp;
	columnTemp = (col & 0x0F) | LCDCMD_SET_COLUMN_ADDRESS_L;		
	WriteToLcd(LCD_CMD, columnTemp);
	columnTemp = (col & 0xF0)>>4;		
	columnTemp = columnTemp | LCDCMD_SET_COLUMN_ADDRESS_H;
	WriteToLcd(LCD_CMD, columnTemp);
}

/**********************************************************************************
* Procedure:	RefreshFrameBuf
* Function:		ˢ���Դ棬��ָ��������Դ������͵�lcd����
* Parameter:	ucX ucY ���������������꣬ucWidth,ucHeightΪ���򳤺Ϳ�
*               �����������(0, 0) (2,3)��ucX=0,ucY=0,uWidth=2,uHeight=3
* Result:		
* Description:	���ڲ�ͬ�����˺������ܲ�ͬ
*               �Դ湲��1K���ֽڣ��ֲ�����
                 (0, 0)
                  ________________________________________________________> x   
                 |0 | |                                                |
        ÿ��8 λ |1 | |                                                |
                 |3 | |                                                |
                 |3_|_|                                                |
                 |4 | |                                                |
                 |5 | |                                                |
                 |6 | |                                                |
               y |7_|_|________________________________________________|
                 |
                 V
* Attribute:    Hidden
***********************************************************************************
* LOG	DATE	AUTHOR		ACTION
***********************************************************************************
***********************************************************************************/
VOID STDCALL RefreshFrameBuf(UINT uX, UINT uY, UINT uWidth, UINT uHeight, U8 * pFrameBuf)
{
    UINT uPageStart, uColStart, uColEnd, uPageEnd;
    UINT uPage, uCol;
	UINT uCount = 0;
    UCHAR uData;
	
	uPageStart = (uY>>3UL);
    uPageEnd =  ((uY + uHeight)>>3UL);
    uColStart = uX;
    uColEnd = (uX + uWidth);

    for(uPage = uPageStart; uPage < uPageEnd; uPage++)
    {
        LcdSetPage(uPage);
        
		for(uCol = uColStart; uCol <= uColEnd; uCol++)
        {
			LcdSetColumn(uCol);
            uData = *(pFrameBuf + uCount); 			
			LcdTransData(uData);  			
			LcdTransData(uData);			
			uCount++;
        }
    }
    

}

U8 g_szlcddata[128][12]={0};
//void My_SetPixelIndex(int uX, int uY, U8 uData)
//{
//	UINT uPage, uCol;
//	U8 u8a,u8b;
//	u8a = uY%8;
////	if(uData)
////		u8b = (0x01<<u8a);
//	u8b = (0x01<<u8a) & uData;
//	uPage = (uY>>3UL);
//    uCol = uX;
//	g_szlcddata[uX][uPage] = u8b | g_szlcddata[uX][uPage];
////	g_szlcddata[uX][uPage] = u8b & g_szlcddata[uX][uPage];
//	LcdSetPage(uPage);
//	LcdSetColumn(uCol);
//	u8b = u8b | g_szlcddata[uX][uPage];	
//	LcdTransData(u8b);  	//���������ǰ��ֺڵף����������Ǻ��Ӱ׵�
//	LcdTransData(u8b);

//}

void My_SetPixelIndex(int uX, int uY, U8 uData)
{
	UINT uPage, uCol;
	U8 u8a,u8b;
	u8a = uY%8;
	u8b = (0x01<<u8a) & uData;
	uPage = (uY>>3UL);
    uCol = uX;
	if(u8b)
	{
		g_szlcddata[uX][uPage] = u8b | g_szlcddata[uX][uPage];
	}
	else
	{
		g_szlcddata[uX][uPage] = (~(0x01<<u8a)) & g_szlcddata[uX][uPage];
	}
	
	LcdSetPage(uPage);
	LcdSetColumn(uCol);
	u8b = u8b | g_szlcddata[uX][uPage];	
//	LcdTransData(u8b);  	//���������ǰ��ֺڵף����������Ǻ��Ӱ׵�
//	LcdTransData(u8b);
	LcdTransData(~u8b);  	//���������ǰ��ֺڵף����������Ǻ��Ӱ׵�
	LcdTransData(~u8b);

}

unsigned My_GetPixelIndex(int uX, int uY)
{

	U8 u8a,u8b;
	u8a = uY%8;
	u8b = (0x01<<u8a);

	u8b = u8b & g_szlcddata[uX][uY];

	if(u8b)
		return 1;
	else
		return 0;
	
//	return u8b;
		
}

