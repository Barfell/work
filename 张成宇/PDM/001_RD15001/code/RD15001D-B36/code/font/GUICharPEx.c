#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
//#include "ff.h"
#include "malloc.h"
#include "fm25v10.h"
#include "SST25VF0.h" 

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
//字模数据的暂存数组,以单个字模的最大字节数为设定值
#define BYTES_PER_FONT      128
static U8 GUI_FontDataBuf[BYTES_PER_FONT];
extern void GUI_X_GetFontData(char *font, U32 oft, U8 *ptr, U8 bytes);
//从外部存储器取得字模数据 
static void GUI_GetDataFromMemory(const GUI_FONT_PROP GUI_UNI_PTR *pProp, U16P c)
{
    U8 BytesPerFont;
    U32 oft;
    char *font = (char *)pProp->paCharInfo->pData;
    BytesPerFont = GUI_Context.pAFont->YSize * pProp->paCharInfo->BytesPerLine; //每个字模的数据字节数
    if (BytesPerFont > BYTES_PER_FONT){BytesPerFont = BYTES_PER_FONT;}
    if (c < 0x80)                                                               //英文字符地址偏移算法
    {
    oft = c * BytesPerFont;
    GUI_X_GetFontData(font, oft, GUI_FontDataBuf, BytesPerFont);
    }
    else                                                                          
    {
         oft = ((((c >> 8)-0xA1)) + ((c & 0xFF)-0xA1) * 94)* BytesPerFont;  //中文字符地址偏移算法包括符号
        oft = oft + 0x600;
        GUI_X_GetFontData(font, oft, GUI_FontDataBuf, BytesPerFont);
    }
    
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_DispChar
*
* Purpose:
*   This is the routine that displays a character. It is used by all
*   other routines which display characters as a subroutine.
*/
void GUIPROP_X_DispChar(U16P c) 
{
    int BytesPerLine;
    GUI_DRAWMODE DrawMode = GUI_Context.TextMode;
    const GUI_FONT_PROP GUI_UNI_PTR *pProp = GUI_Context.pAFont->p.pProp;
    //搜索定位字库数据信息 
    for (; pProp; pProp = pProp->pNext)                                         
    {
        if ((c >= pProp->First) && (c <= pProp->Last))break;
    }
    if (pProp)
    {
        GUI_DRAWMODE OldDrawMode;
        const GUI_CHARINFO GUI_UNI_PTR * pCharInfo = pProp->paCharInfo;
        GUI_GetDataFromMemory(pProp, c);//取出字模数据
        BytesPerLine = pCharInfo->BytesPerLine;
        OldDrawMode  = LCD_SetDrawMode(DrawMode);
        LCD_DrawBitmap(GUI_Context.DispPosX, GUI_Context.DispPosY,
                       pCharInfo->XSize, GUI_Context.pAFont->YSize,
                       GUI_Context.pAFont->XMag, GUI_Context.pAFont->YMag,
                       1,     /* Bits per Pixel */
                       BytesPerLine,
                       &GUI_FontDataBuf[0],
                       &LCD_BKCOLORINDEX
                       );
        /* Fill empty pixel lines */
        if (GUI_Context.pAFont->YDist > GUI_Context.pAFont->YSize) 
        {
            int YMag = GUI_Context.pAFont->YMag;
            int YDist = GUI_Context.pAFont->YDist * YMag;
            int YSize = GUI_Context.pAFont->YSize * YMag;
            if (DrawMode != LCD_DRAWMODE_TRANS) 
            {
                LCD_COLOR OldColor = GUI_GetColor();
                GUI_SetColor(GUI_GetBkColor());
                LCD_FillRect(GUI_Context.DispPosX, GUI_Context.DispPosY + YSize, 
                             GUI_Context.DispPosX + pCharInfo->XSize, 
                             GUI_Context.DispPosY + YDist);
                GUI_SetColor(OldColor);
            }
        }
        LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
        GUI_Context.DispPosX += pCharInfo->XDist * GUI_Context.pAFont->XMag;
    }
}
/*********************************************************************
*
*       GUIPROP_GetCharDistX
*/
int GUIPROP_X_GetCharDistX(U16P c) 
{
    const GUI_FONT_PROP GUI_UNI_PTR * pProp = GUI_Context.pAFont->p.pProp;  
    for (; pProp; pProp = pProp->pNext)                                         
    {
        if ((c >= pProp->First) && (c <= pProp->Last))break;
    }
    return (pProp) ? (pProp->paCharInfo)->XSize * GUI_Context.pAFont->XMag : 0;
}
/*---------------------------------------------------------------------------*/
/*字库外部函数部分-----------------------------------------------------------*/

void GUI_X_GetFontData(char* font, U32 oft, U8 *ptr, U8 bytes)
{    
    ExternFlashHighSpeedRead(oft,ptr,bytes);
}
