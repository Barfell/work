#ifndef __ADC_H
#define __ADC_H	
#include "kernal.h"

 

typedef struct
{
    float gauge_mm;
    float gauge_m;
    float system_v;//单位V
    float system_c;//单位mA
    float systemexternal_T;
    U32 systeminterior_T;
    float gauge_DC;
    float  systemexternal_T_MMDC;
}systemvalue_TypeDef;

#define ADC_CHANNEL				ADC_Channel_10
#define ADC_TEMP_CHANNEL		ADC_Channel_16

VOID Adc_Init(VOID);
VOID Adc_Read(VOID);

VOID Get_Adc(U8 ch, P_U16 pParam);
VOID Get_Adc_Average(U8 ch, U8 times, P_U16 pParam);
VOID Get_Temprate(P_U16 pParam);

EXTERN systemvalue_TypeDef systemvalue;///计算后的最终值

#endif 















