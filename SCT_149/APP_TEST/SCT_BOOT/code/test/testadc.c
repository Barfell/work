/*_---------------------------------------*/
#include "kernel.h"             //里面包含了板子的各种配置以及一些系统的小函数，比如延时CRC校验等....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"
#include "msp430f149_adc.h"
#include "msp430f149_spi.h"
#include "msp430f149_flash.h"
/*_---------------------------------------*/
#include "Vibration.h"
#include "Power.h"
#include "JN5139.h"
#include "LTC2402.h"
#include "Beep.h"
/*_---------------------------------------*/
#include "Freq.h"
#include "Voltage.h"
#include "Temperature.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include "test.h"

void testadc(void)
{
  printf("**************************************\r\n");
  VoltageInit();
  printf("MCU Voltage sensor init ok.\r\n");
  printf("MCU Voltage is %f\r\n", GetVoltage() );
}
