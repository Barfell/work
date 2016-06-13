#ifndef __BSP_H
#define __BSP_H	

//bsp调用
#include "stm32f4xx.h" 
#include "stm32f4xx_conf.h"
//工具调用
#include "tool.h"
//私有调用
#include "malloc.h"	 
//ERROR CODE
enum
{
    ERR_RFID_STEP_1 = 1,
    ERR_RFID_STEP_2,
    ERR_RFID_STEP_3,
    ERR_RFID_STEP_4,
    ERR_RFID_STEP_5,
    ERR_RFID_STEP_6,
    ERR_RFID_STEP_7,
    ERR_RFID_STEP_8,
    ERR_RFID_STOP,
    ERR_NAND_BADBLOCK_FULL,
    ERR_NAND_FULL,
    ERR_NAND_MALLOC_FAIL,
    ERR_GPS_NAND_FULL,
    ERR_INS_NAND_FULL,
    ERR_OTHER_NAND_FULL,
    ERR_RFID_NAND_FULL,
    ERR_UPAN_OPEN_FAIL,
    ERR_UPAN_WRITE_FAIL,
    ERR_UPAN_READ_FAIL,
    ERR_UPAN_CLOSE_FAIL,
    ERR_USATT1_MALLOC_FAIL,
    ERR_USATT2_MALLOC_FAIL,
    ERR_USATT3_MALLOC_FAIL,
	ERR_USATT4_MALLOC_FAIL,
    ERR_OTHER_MALLOC_FAIL,
    ERR_OTHER_SPACE_FULL,
    ERR_INS_SPACE_FULL,
    ERR_GPS_SPACE_FULL,
    ERR_COMM_MALLOC_FAIL,
    ERR_TEST_MALLOC_FAIL,
    ERR_SD_WRITE_FAIL,
    ERR_SD_READ_FAIL,    
    ERR_ADD_FAIL,
};
																	    
	 
//位带操作
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

//以下为汇编函数
VOID WFI_SET(VOID);		//执行WFI指令
VOID INTX_DISABLE(VOID);//关闭所有中断
VOID INTX_ENABLE(VOID);	//开启所有中断
VOID MSR_MSP(u32 addr);	//设置堆栈地址 

VOID OsInit(VOID);
VOID DelayMs(U32 nTime);
VOID DelayMs_Sft(U32 nTime);
VOID DelayUs_Sft(U32 nTime);
U32 GetTickCount(VOID);
U32 GetSecondOfWeek(VOID);
VOID SetSecondOfWeek(U32 u32Cnt);
VOID EnterException(U32 u32ErrCode);
#endif











