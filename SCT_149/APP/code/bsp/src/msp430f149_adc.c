/**************************************************
 内部adc的使用函数等等
***************************************************
*/
#include "msp430f149_adc.h"
#include "kernel.h"

ADCValuetype ADCStatus = NOT_DONE;
int value[9]={0};


void ADC12Init(ADC12_CH_Type channel)
{
    ADC12CTL0 |= ADC12ON + SHT0_2 ;//adc on ,   sample time 
    switch(channel)
    {
    case ADC12_CH0:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_0;
      ADC12MCTL0 |= INCH_0 + EOS;
      ADC12IE    |= ADC12_CH0;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH1:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_1;
      ADC12MCTL1 |= INCH_1 + EOS;
      ADC12IE    |= ADC12_CH1;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH2:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_2;
      ADC12MCTL2 |= INCH_2 + EOS;
      ADC12IE    |= ADC12_CH2;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH3:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_3;
      ADC12MCTL3 |= INCH_3 + EOS;
      ADC12IE    |= ADC12_CH3;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH4:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_4;
      ADC12MCTL4 |= INCH_4 + EOS;
      ADC12IE    |= ADC12_CH4;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH5:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_5;
      ADC12MCTL5 |= INCH_5 + EOS;
      ADC12IE    |= ADC12_CH5;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH6:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_6;
      ADC12MCTL6 |= INCH_6 + EOS;
      ADC12IE    |= ADC12_CH6;
      break;//clk_SMCLK  ,  SHP
    case ADC12_CH7:
      ADC12CTL1 |= ADC12SSEL_3 + SHP + CSTARTADD_7;
      ADC12MCTL7 |= INCH_7 + EOS;
      ADC12IE    |= ADC12_CH7;
      break;//clk_SMCLK  ,  SHP
    }
    
    ADC12CTL0  |= ENC;             // Conversion enabled
    P6SEL |= 0x02;                 // 选择引脚   p61
}





int GetADC12Value(ADC12_CH_Type channel)
{
  int AdcData;
  ADCStatus  = NOT_DONE;                         // adc采集状态为等待完成状态
  ADC12CTL0 |= ADC12SC;                          // Sampling open开始转换，等待转换完成
  
  
  while(ADCStatus != DONE);
  ADCStatus  = NOT_DONE; 
  switch(channel)
  {
    case ADC12_CH0: AdcData = value[1];break;
    case ADC12_CH1: AdcData = value[2];break;
    case ADC12_CH2: AdcData = value[3];break;
    case ADC12_CH3: AdcData = value[4];break;
    case ADC12_CH4: AdcData = value[5];break;
    case ADC12_CH5: AdcData = value[6];break;
    case ADC12_CH6: AdcData = value[7];break;
    case ADC12_CH7: AdcData = value[8];break;
    default:break;
  }
  return AdcData;
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR (void)
{
   // printf("adc done. ADC12MEMx:%d\r\n",ADC12MEM1);

  value[1] = ADC12MEM0;
  value[2] = ADC12MEM1;
  value[3] = ADC12MEM2;
  value[4] = ADC12MEM3;
  value[5] = ADC12MEM4;
  value[6] = ADC12MEM5;
  value[7] = ADC12MEM6;
  value[8] = ADC12MEM7;
  ADCStatus = DONE;
   // ADC12IFG = 0x0000;
}

