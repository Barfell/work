#ifndef __SPI_H                           /* avoid multiple inclusion */
#define __SPI_H

#include "kernal.h"

VOID SPI1_Init(VOID);			 //初始化SPI1口
VOID SPI1_SetSpeed(U8 SpeedSet); //设置SPI1速度   
U8 SPI1_ReadWriteByte(U8 TxData);//SPI1总线读写一个字节

#endif
