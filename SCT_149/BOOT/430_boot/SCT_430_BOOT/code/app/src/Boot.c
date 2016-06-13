/********************************************************************************
APP端处理方法：
//先需要将IAR 开发环境的.XCL文件进行修改，对FLASH进行分配，具体参考《关于MSP430单片机的二次升级》
1.用户APP发送升级命令。
2.硬件接受到命令后把FLASH里面的BOOT的中断向量保存区域拷贝至物理中断向量地址。
3.利用看门狗将硬件复位。（msp430每次复位都是先把PC指向物理中断向量表的RESET位置，具体位置可以看器件的数据手册）


BOOT端的处理方法：
1.进入到BOOT的第一件事情就是备份物理中断向量表到BOOT的中断向量保存区域。
	（能进入到BOOT说明是第一次硬件运行，或者是APP端接收到升级命令而跳转到BOOT，正常情况下，不是第一次硬件运行的话，复位都是在APP中）
2.擦除APP的flash区域，等待升级数据包。
3.待升级数据包接收完毕（写入到APP Flash完成）。
4.接收完毕后，将APP 的中断向量保存区域的数据拷贝到物理中断向量地址。准备APP运行环境。
5.利用看门狗将硬件复位。
********************************************************************************
*/
#include "kernel.h"             //里面包含了板子的各种配置,以及一些系统的小函数，比如延时CRC校验等....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_flash.h"
/*_----------------器件驱动---------------------*/
#include "Power.h"
/*_----------------功能函数---------------------*/
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include "Boot.h"
#include "msp430f149_wdt.h"

void BootProc(void)
{
  printf("bootloader init done.\r\n");
  printf("begin to save Vector in BOOT area.\r\n");
  FeedWatchDog();
  Vector_HARD2BOOT();//备份BOOT的向量表
  printf("begin to wipe APP area.\r\n");
  FeedWatchDog();
  EarseAppFlash();//擦除App的FLASH，准备写入新的app固件
  printf("wipe Flash done.\r\nready to download the fireware.(请按发送按键)\r\n");
  while(1)
  {
    delay_ms(10);
    FeedWatchDog();
  }
}

//ascii转HEX
unsigned char AsciiToHex(unsigned char cNum)
{
	if(cNum>='0'&&cNum<='9')
	{
		cNum -= '0';
	}
	else if(cNum>='A'&&cNum<='F')
	{
		cNum -= 'A';
		cNum += 10;
	}
	return cNum;
}

/***********************以下对中断向量表操作************************************/
//将APP的向量表拷贝到物理向量表中
void Vector_APP2HARD(void)
{
  unsigned int i;
  FlashEreaseSector(HARDWARE_VECTOR_BUTTOM);
  delay_ms(20);
  FCTL1 = FWKEY + WRT;
  for(i=0;i<32;i++)
  {
    *(char *)(HARDWARE_VECTOR_BUTTOM + i) = *(char*)(APP_VECTOR_BUTTOM + i);
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK; 
}

//备份BOOT向量表
void Vector_HARD2BOOT(void)
{
  unsigned int i;
  FlashEreaseSector(BOOT_VECTOR_BUTTOM);
  FeedWatchDog();
  delay_ms(20);
  FCTL1 = FWKEY + WRT;
  for(i=0;i<32;i++)
  {
    *(char*)(BOOT_VECTOR_BUTTOM + i) = *(char *)(HARDWARE_VECTOR_BUTTOM + i);
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK; 
}
  
  
  
//跳转之前先把APP的中断向量表拷贝到物理的中断向量表中
void GoToApp(void)
{
  printf("Copy App vector to VECTOR area.\r\n");
  Vector_APP2HARD();            //将app的向量表放到物理中断向量表中
  printf("Copy Done, jump to app ....\r\n");
  WDTCTL = 0x0000;
}

//擦除App存储区域的数据
void EarseAppFlash(void)
{
  unsigned int j;
  for(j=0; j<(APP_ADDR_TOP - APP_ADDR_BUTTOM); j+=0xff )
  {
    FlashEreaseSector(APP_ADDR_BUTTOM + j+1);
    delay_ms(20);
    FeedWatchDog();
  }
}





unsigned int  AddrToWrite_HEX = 0;//@后面的地址（HEX类型的）
unsigned char UpdateData_HEX = 0;//升级数据（HEX类型的）

unsigned char AddrToWrite[4];//@后面的地址（数组缓冲类型的）
unsigned char UpdateData[2];//升级数据（数组缓冲类型的）
unsigned char Addr_i = 0;//用于解析地址时候
unsigned char Data_i = 0;//用于解析升级数据时候
unsigned char Flag_AT = 0;//是否出现 ‘@’
unsigned int WritePosition = 0;//写flash时候的偏移变量



//接收以及解析
/************************TXT固件格式***********************
@5000
44 54 00 52 44 31 35 30 30 31 00 55 61 72 74 20
72 65 63 69 76 65 64 20 64 61 74 61 3A 25 73 00
25 73 0D 0A 00 25 73 20 69 73 20 6E 6F 74 20 61
@51AA
01 
@51AC
31 40 00 0A 3C 40 02 02 3D 40 B8 00 B0 12 A2 70
3C 40 00 02 3D 40 AA 51 3E 40 01 00 B0 12 BE 71
B0 12 16 6D B0 12 C2 71 0A 12 0B 12 08 12 09 12
06 12 07 12 0C 12 30 40 C6 71 30 40 CA 71 FF 3F
@DFE2
DA 6E 
@DFE6
74 71 F8 6E 9C 67 A0 6F E6 6B 
@DFF2
A4 6D 
@DFFE
AC 51 
q

***********************************************************
*/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  u8 u8data = 0;
  FeedWatchDog();
  u8data = U0RXBUF;
  
  //出现了@后，后面四位都是地址位
  if(Flag_AT == 1)
  {
    AddrToWrite[Addr_i] = u8data;
    Addr_i++;
    if(Addr_i == 4)//已经接受完四个字符
    {
      Addr_i = 0;
      Flag_AT = 0;
      AddrToWrite_HEX =  4096*AsciiToHex(AddrToWrite[0]);
      AddrToWrite_HEX =  256 *AsciiToHex(AddrToWrite[1]) + AddrToWrite_HEX;
      AddrToWrite_HEX =  16  *AsciiToHex(AddrToWrite[2]) + AddrToWrite_HEX;
      AddrToWrite_HEX =       AsciiToHex(AddrToWrite[3]) + AddrToWrite_HEX;
      WritePosition = 0;
      goto OutFunc;
    }
  }
  
  //'@' 没有出现
  else
  {
    //假如不是回车换行或者空格的时候
    if(u8data != ' ' && u8data != '\r' && u8data != '\n' && u8data != 0X0A && u8data != 0X0D)
    {
        //地址位
        if(u8data == '@')
        {
          Flag_AT = 1;
          FCTL1 = FWKEY + WRT;
          goto OutFunc;
        }
        //‘q’ 结束位置 
        if(u8data == 'q')
        {
          FCTL1 = FWKEY;                            // Clear WRT bit
          GoToApp();
        }
        //data数据
        else
        {
          UpdateData[Data_i] = u8data;
          Data_i++;
          if(Data_i == 2)
            {
              Data_i = 0; 
              UpdateData_HEX = 16 * AsciiToHex(UpdateData[0]);
              UpdateData_HEX = UpdateData_HEX + AsciiToHex(UpdateData[1]);
              //写入到APP FLASH中
              *(char *)(AddrToWrite_HEX + WritePosition) = UpdateData_HEX;
              WritePosition++;
            }
        }
    }
  }
  
OutFunc:
}



