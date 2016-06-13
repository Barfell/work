/*****************************************************************
*Modules: includes.h
*Dedcription: 总的头文件包含，以及对整个系统的配置等等
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
#ifndef _INCLUDES_H_
#define _INCLUDES_H_

//device
#include "msp430.h"
#include "i430type.h"
#include "kernel.h"

//c99
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//bsp
#include "clk.h"
#include "flash.h"
#include "gpio.h"
#include "rtc.h"
#include "sd.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "wdt.h"

//drv
#include "beep.h"
#include "jn5139.h"
#include "ltc2402.h"
#include "power.h"
#include "vibration.h"

//app
#include "dtprotocol.h"
#include "firmwareupdate.h"
#include "freq.h"
#include "ramloop.h"
#include "sensor.h"
#include "voltage.h"


//configratuion

#endif