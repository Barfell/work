#ifndef _CFG_H
#define _CFG_H

/*
  内部存储结构：
    11000-- (APP ) ---18000            28K
    FFC0--- (VECTOR)--FFFF      
    B000--- (CFG) ----FF00                      
    3100---（BOOT）---B000             32K
*/

/*116k
(interrrupt )    0x0ffff - 0xffc0
(code memery)    0x01ffff - 0x003100
*/

/*--------FLASH memory organization-------------------------
*MAIN FLASH  INTERRUPT VECTOR   :  0XFFFF       -       0XFFC0  
*MAIN FLASH  CODE MEMORT        :  0X01FFFF     -       0X3100-0XFFC0     0XFFFF-0X01FFFF  
*RAM                            :  0X30FF       -       0X1100
*/




/*cfg:   8000 ---- 9fff*/
#define _LOWPOWER_MODE_
//#define _ONLINE_MODE_


#define MACHINE_ID                              "SCT16012"//本机机号
#define INTERVAL_TIME                           2  //默认时间间隔 单位是min至少需要5分钟
#define CMD_TIME                                60 //默认的cmd等待时间


/*--------------------------------------------------------------------------------------------------------*/
#define DEVICE_FIRST_TIME_POWERON_ADDR          0xB000//存放仪器是否是第一次上电信息
#define INTERVAL_TIME_ADDR                      0xB200//存放采集间隔时间
#define CMD_TIME_ADDR                           0XB400//存放CMD等待时间
#define CONNECT_TYPE_ADDR                       0xB600//存放仪器的连接方式（0：RF连接 1:DTU连接）
#define PROTOCOL_TYPE_ADDR                      0xB800//存放仪器的传输是否添加协议标志(0:不带协议，1:带协议)


/*--------------------------------------------------------------------------------------------------------*/
#define CHANNEL_TYPE_ADDR                       0xBA00//存放本机通道类型（0：VW  1：485）
#define SENSOR_ID_ADDR                          0xBC00//存放本机通道所接的485传感器编号ID (八个  每个传感器的编号范围0 - 255)

/*--------------------------------------------------------------------------------------------------------*/
#define SUB_DEVICE_ID                           0xBE00//存放主设备连接的子设备的设备编号ID（八个  每个子设备编号范围为：0-255）
#define SUB_DEVICE_TYPE_ADDR                    0xC200//存放主设备连接的子设备的通道类型（0：VW  1：485）
#define SUB_DEVICE_SENSOR_ID_ADDR               0xC400//存放主设备连接的子设备所接的485传感器编号ID (八个  每个传感器的编号范围0 - 255)

/*--------------------------------------------------------------------------------------------------------*/
#define SET_INTERVAL_TIME_FLAG_ADDR             0xC600//存放下一次是否需要设置的时间间隔的标志
#define NEXT_INTERVAL_TIME_ADDR                 0xC800//存放下一次需要设置的时间间隔

/*--------------------------------------------------------------------------------------------------------*/
#define RECORD_DATA_ADDR                        114401 //前100K给雨量存储
#define RECORD_DATA_LEN_ADDR                    102401 //存储保存的数据长度
#define RECORD_READ_POS_ADDR                    107401 //存储当前读到哪里

#endif