#ifndef _BOOT_H_
#define _BOOT_H_

/********************************************************************************
//msp重启或者复位后第一件事情就是会把PC指向“物理中断向量表地址“的RESET位置，跳转到对应的代码运行
//每个固件都对应相应的中断向量表，将固件对应的中断向量表拷贝到“物理中断向量表地址“，复位后就会直接执行固件
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

#define APP_ADDR_TOP                    0xe000
#define APP_VECTOR_TOP                  0xDFFF
#define APP_VECTOR_BUTTOM               0xDFE0
#define APP_ADDR_BUTTOM                 0x5000



#define BOOT_ADDR_TOP                   0x4000
#define BOOT_VECTOR_TOP                 0x3FFF
#define BOOT_VECTOR_BUTTOM              0x3FE0
#define BOOT_ADDR_BUTTOM                0x1100


#define HARDWARE_VECTOR_TOP                 0XFFFF
#define HARDWARE_VECTOR_BUTTOM              0XFFE0



void Vector_BOOT2HRAD(void);
void FirmwareUpdate(void);


#endif