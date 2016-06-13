/*****************************************************************
*Modules: gpio.c
*Dedcription: 对gpio的操作
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
#ifndef _GPIO_H
#define _GPIO_H

typedef enum
{
  P1 =  0,
  P2,
  P3,
  P4,
  P5,
  P7,
  P8,
  P9,
  P10
} PortType;

typedef enum
{
  Pin0 = 0x01,
  Pin1 = 0x02,
  Pin2 = 0x04,
  Pin3 = 0x08,
  Pin4 = 0x10,
  Pin5 = 0x20,
  Pin6 = 0x40,
  Pin7 = 0x80
} PinType;

typedef enum
{
  In  = 0x01,
  Out = 0x02,
  Af  = 0x04,
} PinModeType;


void GPIOInit(PortType port, PinType pin ,PinModeType mode);
void GPIOOutPut(PortType port, PinType pin ,unsigned char value);
void LowPowerGPIO(void);
#endif
