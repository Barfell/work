#ifndef _BOOT_H_
#define _BOOT_H_


/***********************************************************
------------------msp43f149---------------------------------
size                    :60kbyte
main interrupt vector   :0ffffh-0ffe0h
main code               :0ffffh-01100h
information             :010ffh-01000h
boot                    :0fffh-0c00h
ram                     :09ffh-0200h    (2kbyte)
peripherals             :01ffh-00h
***********************************************************
*/
//存放APP的数据域：           0x5000----0xe000
//VECTOR放置于：              0xDFE0----0xDFFF
#define APP_ADDR_TOP                    0xe000
#define APP_VECTOR_TOP                  0xDFFF
#define APP_VECTOR_BUTTOM               0xDFE0
#define APP_ADDR_BUTTOM                 0x5000
//存放BOOT的数据域：          0x1100----0x4000
//VECTOR放置于：              0x3FE0----0x3FFF
#define BOOT_ADDR_TOP                   0x4000
#define BOOT_VECTOR_TOP                 0x3FFF
#define BOOT_VECTOR_BUTTOM              0x3FE0
#define BOOT_ADDR_BUTTOM                0x1100
//物理中断向量表的地址所在：  0XFFE0----0XFFFF
#define HARDWARE_VECTOR_TOP                 0XFFFF
#define HARDWARE_VECTOR_BUTTOM              0XFFE0

void BootProc(void);
void EarseAppFlash(void);
unsigned char AsciiToHex(unsigned char cNum);
void Vector_APP2HARD(void);
void Vector_HARD2BOOT(void);

void GoToApp(void);


#endif