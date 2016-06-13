
#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT



#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>



/*------stlib------------------------------*/
#include  "stm32f4xx.h"

/*------bsp--------------------------------*/
#include  "bsp_init.h"
#include  "bsp_usart.h"
#include  "bsp_sst25vf064.h"
#include  "bsp_rtc.h"
#include  "bsp_io_control.h"
#include  "bsp_adc.h"
#include  "bsp_flash.h"

/*------app--------------------------------*/
#include  "Tools.h"

#include  "Dtu.h"
#include  "kernal.h"
#include  "Protocol.h"
#include  "flash.h"
#include  "Test.h"
#include  "serial.h"
#include  "UartBoot.h"
#include  "DtuBoot.h"
#include  "iap.h"

//宏定义用于配置用哪个串口作为通讯口。
//#define _UART3_ 1
#define _UART1_ 1

#endif

