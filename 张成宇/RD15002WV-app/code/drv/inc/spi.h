#ifndef __SPI_H                           /* avoid multiple inclusion */
#define __SPI_H

#include "kernal.h"

VOID SPI1_Init(VOID);			 //��ʼ��SPI1��
VOID SPI1_SetSpeed(U8 SpeedSet); //����SPI1�ٶ�   
U8 SPI1_ReadWriteByte(U8 TxData);//SPI1���߶�дһ���ֽ�

#endif
