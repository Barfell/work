
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
SCT001(4-485-4-VW):������8ͨ���������ݲɼ���1 ��3��485 3������
				--------------λ�ƴ�����--------
				(DT-SENSOR1)2-5�������������λ�ƣ�485��
				(DT-SENSOR2)2-6��������������λ�ƣ�485��
				(DT-SENSOR3)2-7�������������λ�ƣ�485��
				(DT-SENSOR4)
				----------------Ӧ��������------
				(VW1)3-1�������嶥Ӧ�������ң�
				(VW2)3-2����������Ӧ�������ң�
				(VW3)3-3������ʵ������Ӧ�������ң�
				(VW4)
*************************************************************			
				
*************************************************************
SCT002(4-485-4-VW):������8ͨ���������ݲɼ���2��2��485 2������
				---------------λ�ƴ�����-------
				(DT-SENSOR1)2-1��|�ֹ��������λ�ƣ�485��
				(DT-SENSOR2)2-2��|�ֹ��������λ�ƣ�485��
				(DT-SENSOR3)
				(DT-SENSOR4)
				--------------------------------
				(VW1)2-3��|�����-���������λ��
				(VW2)2-4��|�����-���������λ��
				(VW3)
				(VW4)
*************************************************************

*************************************************************
SCT003(6-NTC):������8ͨ���¶����ݲɼ���3��6��ntc
				------�¶ȴ�����---------------
				(Temperature1)1-1�������嶥�¶�
				(Temperature2)1-2�����������¶�
				(Temperature3)1-3����������¶�
				(Temperature4)1-4������ʵ�������¶�
				(Temperature5)1-5���������¶�
				(Temperature6)1-6�������¶�
				(Temperature7)
				(Temperature8)
*************************************************************

*************************************************************
SCT004(4-485-4-VW):��8ͨ���������ݲɼ���1��3��485 3������
				---------------λ�ƴ�����----
				(DT-SENSOR1)2-12�������������λ��
				(DT-SENSOR2)2-13��������������λ��
				(DT-SENSOR3)2-14�������������λ��
				(DT-SENSOR4)
				------------Ӧ��������-------
				(VW1)3-1�������嶥Ӧ��
				(VW2)3-2����������Ӧ��
				(VW3)3-5������ʵ������Ӧ��
				(VW4)
*************************************************************

*************************************************************
SCT005(6-NTC):��8ͨ���¶����ݲɼ���2��6��ntc
				(Temperature1)1-1�������嶥�¶�
				(Temperature2)1-2�����������¶�
				(Temperature3)1-3����������¶�
				(Temperature4)1-4������ʵ�������¶�
				(Temperature5)1-5���������¶�
				(Temperature6)1-6�������¶�
				(Temperature7)
				(Temperature8)
*************************************************************

*************************************************************
SCT006(2-485-6-VW):��8ͨ�����ݲɼ���2��2��485 6������
				----------------------------
				(DT-SENSOR1)2-1��|�ֹ��������λ��
				(DT-SENSOR1)2-2��|�ֹ��������λ��
				(VW4)2-5��|�����-�װ������λ��
				(VW5)2-6��|�����-�װ������λ��
				(VW6)2-15��������λ��
				----------------------------
				(VW1)3-3�������嶥Ӧ��
				(VW2)3-4����������Ӧ��
				(VW3)3-6������ʵ������Ӧ��
*************************************************************

*************************************************************
SCT007(6-485-2-VW):��8ͨ�����ݲɼ���1��6��485 2������
				----------------------------
				(DT-SENSOR1)2-3��|�ֹ�-��������λ��
				(DT-SENSOR2)2-4��|�ֹ�-��������λ��
				----------------------------
				(VW1)2-7��|�������������λ��
				(VW2)2-8��|�������������λ��
				----------------------------
				(DT-SENSOR3)2-9�������嶥������λ��
				(DT-SENSOR4)2-10��������������λ��
				(DT-SENSOR5)2-11�������������λ��
				(DT-SENSOR6)
*************************************************************
*/

/*Ĭ�ϻ���ʱ���Ĭ������ȴ�ʱ��*/
#define DEFAULT_WKP_TIME 1800
#define DEFAULT_CMD_TIME 150


/*���º궨��ȷ�������ı�ţ�������Ӧ�Ĵ���*/
//#define _SCT001_
//#define _SCT002_
//#define _SCT003_
#define _SCT004_
//#define _SCT005_
//#define _SCT006_
//#define _SCT007_


/* ���ʷ�ʽ */
#define IP_INTERVIEW
//#define	DOMAIN_INTERVIEW
/*ip��ַ*/



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











/****************485 ���ͺ�*************************/
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

