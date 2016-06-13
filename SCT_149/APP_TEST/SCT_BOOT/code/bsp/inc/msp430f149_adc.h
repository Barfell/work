#ifndef __MSP430F149_ADC_H_
#define __MSP430F149_ADC_H_

typedef  enum{
  DONE = 0,
  NOT_DONE
} ADCValuetype;


typedef  enum{
  ADC12_CH0 = 0X01,
  ADC12_CH1 = 0X02,
  ADC12_CH2 = 0X04,
  ADC12_CH3 = 0X08,
  ADC12_CH4 = 0X10,
  ADC12_CH5 = 0X20,
  ADC12_CH6 = 0X40,
  ADC12_CH7 = 0X80
} ADC12_CH_Type;

void ADC12Init(ADC12_CH_Type channel);

int GetADC12Value(ADC12_CH_Type channel);

#endif
