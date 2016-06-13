#include "Voltage.h"
#include "msp430f149_adc.h"

void VoltageInit(void)
{
  ADC12Init(ADC12_CH1);//p61----mcu_voltage
}


double GetVoltage(void)
{
  double MCUvoltage = 0;
  MCUvoltage =  (   (double)GetADC12Value(ADC12_CH1)   *   3.3 ) / 4096    ;
  return MCUvoltage;
}
