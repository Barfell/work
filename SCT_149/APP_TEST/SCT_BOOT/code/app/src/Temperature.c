#include "Temperature.h"
#include "kernel.h"

void TemperatureInit(void)
{
  LTC2402Init();
}

double GetTemperature(void)
{
 return GetNTCTemperature(LTC2402_GetResistance());
}

