#ifndef __BOARD_H
#define __BOARD_H

//system
#include "sys.h"
#include "protocol.h"

//driver
#include "usart.h"
#include "other.h"
#include "stmflash.h"
#include "iap.h" 

//���Գ���
//����
VOID TestUsart1(VOID);
VOID TestUsart2(VOID);
VOID TestUsart3(VOID);
VOID Test3Usart(VOID);
VOID TestGps(VOID); //ģ��GPS���ݲ���
//�ڴ�
VOID TestMem(VOID);
//LED
VOID TestLedProc(VOID);

VOID TestBoot(VOID);


#endif 

