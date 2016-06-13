
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
#include  "Temperature.h"
/*------app--------------------------------*/
#include  "FreqMeasurement.h"
#include  "Tools.h"
#include  "Temperature.h"
#include  "485.h"

#include  "Dtu.h"
#include  "kernal.h"
#include  "Protocol.h"
#include  "flash.h"
#include  "Test.h"
#include  "serial.h"






/*
*************************************************************
SCT001(4-485-4-VW):《左线8通道振弦数据采集仪1 》3个485 3个振弦
				--------------位移传感器--------
				(DT-SENSOR1)2-5：轨道板板端翘曲位移（485）
				(DT-SENSOR2)2-6：轨道板板中翘曲位移（485）
				(DT-SENSOR3)2-7：轨道板板端翘曲位移（485）
				(DT-SENSOR4)
				----------------应力传感器------
				(VW1)3-1：轨道板板顶应力（振弦）
				(VW2)3-2：轨道板板中应力（振弦）
				(VW3)3-3：自密实混凝土应力（振弦）
				(VW4)
*************************************************************			
				
*************************************************************
SCT002(4-485-4-VW):《左线8通道振弦数据采集仪2》2个485 2个振弦
				---------------位移传感器-------
				(DT-SENSOR1)2-1：|钢轨轨道板相对位移（485）
				(DT-SENSOR2)2-2：|钢轨轨道板相对位移（485）
				(DT-SENSOR3)
				(DT-SENSOR4)
				--------------------------------
				(VW1)2-3：|轨道板-底座板相对位移
				(VW2)2-4：|轨道板-底座板相对位移
				(VW3)
				(VW4)
*************************************************************

*************************************************************
SCT003(6-NTC):《右线8通道温度数据采集仪3》6个ntc
				------温度传感器---------------
				(Temperature1)1-1：轨道板板顶温度
				(Temperature2)1-2：轨道板板中温度
				(Temperature3)1-3：轨道板板底温度
				(Temperature4)1-4：自密实混凝土温度
				(Temperature5)1-5：底座板温度
				(Temperature6)1-6：大气温度
				(Temperature7)
				(Temperature8)
*************************************************************

*************************************************************
SCT004(4-485-4-VW):《8通道振弦数据采集仪1》3个485 3个振弦
				---------------位移传感器----
				(DT-SENSOR1)2-12：轨道板板端翘曲位移
				(DT-SENSOR2)2-13：轨道板板中翘曲位移
				(DT-SENSOR3)2-14：轨道板板端翘曲位移
				(DT-SENSOR4)
				------------应力传感器-------
				(VW1)3-1：轨道板板顶应力
				(VW2)3-2：轨道板板中应力
				(VW3)3-5：自密实混凝土应力
				(VW4)
*************************************************************

*************************************************************
SCT005(6-NTC):《8通道温度数据采集仪2》6个ntc
				(Temperature1)1-1：轨道板板顶温度
				(Temperature2)1-2：轨道板板中温度
				(Temperature3)1-3：轨道板班底温度
				(Temperature4)1-4：自密实混凝土温度
				(Temperature5)1-5：底座板温度
				(Temperature6)1-6：大气温度
				(Temperature7)
				(Temperature8)
*************************************************************

*************************************************************
SCT006(2-485-6-VW):《8通道数据采集仪2》2个485 6个振弦
				----------------------------
				(DT-SENSOR1)2-1：|钢轨轨道板相对位移
				(DT-SENSOR1)2-2：|钢轨轨道板相对位移
				(VW4)2-5：|轨道板-底板座相对位移
				(VW5)2-6：|轨道板-底板座相对位移
				(VW6)2-15：桥梁缝位移
				----------------------------
				(VW1)3-3：轨道板板顶应力
				(VW2)3-4：轨道板板中应力
				(VW3)3-6：自密实混凝土应力
*************************************************************

*************************************************************
SCT007(6-485-2-VW):《8通道数据采集仪1》6个485 2个振弦
				----------------------------
				(DT-SENSOR1)2-3：|钢轨-轨道板相对位移
				(DT-SENSOR2)2-4：|钢轨-轨道板相对位移
				----------------------------
				(VW1)2-7：|轨道板底座板相对位移
				(VW2)2-8：|轨道板底座板相对位移
				----------------------------
				(DT-SENSOR3)2-9：轨道板板顶端翘曲位移
				(DT-SENSOR4)2-10：轨道板板中翘曲位移
				(DT-SENSOR5)2-11：轨道板板端翘曲位移
				(DT-SENSOR6)
*************************************************************
*/

/*默认唤醒时间和默认命令等待时间*/
#define DEFAULT_WKP_TIME 1800
#define DEFAULT_CMD_TIME 150


/*以下宏定义确定机器的编号，对于相应的代码*/
//#define _SCT001_
//#define _SCT002_
//#define _SCT003_
#define _SCT004_
//#define _SCT005_
//#define _SCT006_
//#define _SCT007_


/* 访问方式 */
#define IP_INTERVIEW
//#define	DOMAIN_INTERVIEW
/*ip网址*/



#ifdef IP_INTERVIEW
	#define TEST_IP 	  "AT+SETPARAM=CHPDSCIP,59.172.252.243\r\n"
	#define TEST_PORT 	"AT+SETPARAM=CHPDSCP,7005\r\n"
//	#define TEST_IP 	  "AT+SETPARAM=CHPDSCIP,183.233.190.96\r\n"
//	#define TEST_PORT 	"AT+SETPARAM=CHPDSCP,6254\r\n"
#endif

#ifdef DOMAIN_INTERVIEW
	#define DOMAIN 	  		"AT+SETPARAM=CHPDSCD,14g542w137.iok.la"
	#define DOMAIN_PORT 	"AT+SETPARAM=CHPDSCP,12658"
#endif











/****************485 的型号*************************/
#define SENSOR_HEAD 	"$DTLOG,"
#define SENSOR_TYPE 	"01"

#ifdef _SCT001_
	#define S485_4_VW_4
	#define DT_SENSOR_ADDR1 "0001\r\n"
	#define DT_SENSOR_ADDR2 "0002\r\n"
	#define DT_SENSOR_ADDR3 "0003\r\n"
	#define DT_SENSOR_ADDR4 "XXXXXXXXXX\r\n"
#endif

#ifdef _SCT002_
	#define S485_4_VW_4
	#define DT_SENSOR_ADDR1 "0004\r\n"
	#define DT_SENSOR_ADDR2 "0005\r\n"
	#define DT_SENSOR_ADDR3 "XXXXXXXXXX\r\n"
	#define DT_SENSOR_ADDR4 "XXXXXXXXXX\r\n"
#endif

#ifdef _SCT003_
	#define NTC_6
#endif

#ifdef _SCT004_
	#define S485_4_VW_4
	#define DT_SENSOR_ADDR1 "0006\r\n"
	#define DT_SENSOR_ADDR2 "0007\r\n"
	#define DT_SENSOR_ADDR3 "0008\r\n"
	#define DT_SENSOR_ADDR4 "XXXXXXXXXX\r\n"
#endif

#ifdef _SCT005_
	#define NTC_6
#endif

#ifdef _SCT006_
	#define S485_2_VW_6
	#define DT_SENSOR_ADDR1 "0009\r\n"
	#define DT_SENSOR_ADDR2 "0010\r\n"
#endif

#ifdef _SCT007_
	#define S485_6_VW_2
	#define DT_SENSOR_ADDR1 "0011\r\n"
	#define DT_SENSOR_ADDR2 "0012\r\n"
	#define DT_SENSOR_ADDR3 "0013\r\n"
	#define DT_SENSOR_ADDR4 "0014\r\n"
	#define DT_SENSOR_ADDR5 "0016\r\n"
	#define DT_SENSOR_ADDR6 "XXXXXXXXXX\r\n"
#endif








#endif

