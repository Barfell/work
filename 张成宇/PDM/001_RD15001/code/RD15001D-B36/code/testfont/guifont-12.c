#include "GUI.h"
/*
****************************************
*
*˵��:GUI_FontHZ12.C�ļ�
*
*By:ailson jack
*
*Date:2013.09.21
*****************************************
*/
extern int GUIPROP_X_GetCharDistX(U16P c);//��������
extern void GUIPROP_X_DispChar(U16P c) ; 
 
GUI_CONST_STORAGE GUI_CHARINFO GUI_FontHZ12_CharInfo[2] = 
{    
    { 6, 6, 1, (void *)0},//&ASC_ROM_6X12 �ֿ��·��
    { 12,12,2, (void*)0x600}, //&HZ_ROM_12X12�ֿ��·��
};
GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontHZ12_PropHZ= {
      0xA1A1, //��һ���ַ�
      0xFEFE, //���һ���ַ�
      &GUI_FontHZ12_CharInfo[1], //�ַ���Ϣ
      (void *)0, 
};
GUI_CONST_STORAGE  GUI_FONT_PROP GUI_FontHZ12_PropASC= {
      0x0000, //��һ���ַ�
      0x007F, //���һ���ַ�
      &GUI_FontHZ12_CharInfo[0], //�ַ���Ϣ
      (void GUI_CONST_STORAGE *)&GUI_FontHZ12_PropHZ, 
};
GUI_CONST_STORAGE  GUI_FONT GUI_FontHZ12 = 
{
      GUI_FONTTYPE_PROP_USER,
      12, //xsize
      12, //yszie
      1,  //x����Ŵ���
      1,  //y����Ŵ���
      (void GUI_CONST_STORAGE *)&GUI_FontHZ12_PropASC
};