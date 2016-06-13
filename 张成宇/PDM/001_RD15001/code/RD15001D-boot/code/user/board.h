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

//测试程序
//串口
VOID TestUsart1(VOID);
VOID TestUsart2(VOID);
VOID TestUsart3(VOID);
VOID Test3Usart(VOID);
VOID TestGps(VOID); //模拟GPS数据测试
//内存
VOID TestMem(VOID);
//LED
VOID TestLedProc(VOID);

VOID TestBoot(VOID);


#endif 

