#ifndef __BSP_SST25VF064_H
#define __BSP_SST25VF064_H

//初始化ADC的引脚
void SST25VF064Init(void);
unsigned char SST25VF064WriteReadByte(unsigned char cmd);
void SST25VF064Unselect(void);
void SST25VF064Select(void);
void SST25VF064Reset(void);
void SST25VF064SectorErase(unsigned int Addr);
void SST25VF064BlockErase(unsigned int Addr);
void SST25VF064BlockOPErase(unsigned int Addr);
void SST25VF064ChipErase(unsigned int Addr);
//1:unbusy
//0:busy
unsigned char SST25VF064BusySatue(void);
//向某一个地址写入一个数据
void SST25VF064ProgramByte(unsigned int Addr,unsigned char dat);
//从某一个地址开始，写入一定长度的连续数据
void SST25VF064ProgramLength(unsigned int Addr,unsigned char *dat,unsigned int length);
//读取某一地址的一个字节
unsigned char SST25VF064FlashReadByte(unsigned int Addr);
//读取一定长度到buff
void SST25VF064FlashRead(unsigned int Addr,unsigned char *pbuff,unsigned int length);


#endif



