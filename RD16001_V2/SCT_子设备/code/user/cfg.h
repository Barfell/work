#ifndef _CFG_H
#define _CFG_H

/*116k
(interrrupt )    0x0ffff - 0xffc0
(code memery)    0x01ffff - 0x003100
*/

/*--------FLASH memory organization-------------------------
*MAIN FLASH  INTERRUPT VECTOR   :  0XFFFF       -       0XFFC0  
*MAIN FLASH  CODE MEMORT        :  0X01FFFF     -       0X3100  
*RAM                            :  0X30FF       -       0X1100
*/

/*cfg:   8000 ---- 9fff*/
#define MACHINE_ID                              "SCT16002"//本机机号
#define SUB_NUM                                 2      //本机是作为第几个子设备
#define INTERVAL_TIME                           8  //默认时间间隔 单位是min
#define CMD_TIME                                60 //默认的cmd等待时间



/*--------------------------------------------------------------------------------------------------------*/
#define DEVICE_FIRST_TIME_POWERON_ADDR          0x9000//存放仪器是否是第一次上电信息

#define INTERVAL_TIME_ADDR                      0x9200//存放采集间隔时间

#define CMD_TIME_ADDR                           0X9400//存放CMD等待时间

#define CONNECT_TYPE_ADDR                       0x9600//存放仪器的连接方式（0：RF连接 1:DTU连接）

#define PROTOCOL_TYPE_ADDR                      0x9800//存放仪器的传输是否添加协议标志(0:不带协议，1:带协议)


/*--------------------------------------------------------------------------------------------------------*/
#define CHANNEL_TYPE_ADDR                       0x9A00//存放本机通道类型（0：VW  1：485）

#define SENSOR_ID_ADDR                          0x9C00//存放本机通道所接的485传感器编号ID (八个  每个传感器的编号范围0 - 255)


/*--------------------------------------------------------------------------------------------------------*/
#define SUB_DEVICE_ID                           0x9E00//存放主设备连接的子设备的设备编号ID（八个  每个子设备编号范围为：0-255）

#define SUB_DEVICE_TYPE_ADDR                    0xA200//存放主设备连接的子设备的通道类型（0：VW  1：485）

#define SUB_DEVICE_SENSOR_ID_ADDR               0xA400//存放主设备连接的子设备所接的485传感器编号ID (八个  每个传感器的编号范围0 - 255)




/*rain:  12000 ---- 1A000*/
//32K
/*rain temp:   1B000*/
//
#define RAIN_ADDR                               0x12000//雨量保存的位置
#define RAIN_TEMP_ADDR                          0x1A000//雨量数据交换的缓冲位置
#define RAIN_NUM_ADDR                           0x1B000//雨量数目的位置

#endif