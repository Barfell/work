#ifndef _SST25VF064_H
#define _SST25VF064_H

//初始化ADC的引脚
void SST25VF064Init(void);
unsigned char SST25VF064WriteReadByte(unsigned char cmd);
void SST25VF064Unselect(void);
void SST25VF064Select(void);
void SST25VF064Reset(void);
void SST25VF064SectorErase(unsigned long Addr);
void SST25VF064BlockErase(unsigned long Addr);
void SST25VF064BlockOPErase(unsigned long Addr);
void SST25VF064ChipErase(unsigned long Addr);
//1:unbusy
//0:busy
unsigned char SST25VF064BusySatue(void);
//向某一个地址写入一个数据
void SST25VF064ProgramByte(unsigned long Addr,unsigned char dat);
//从某一个地址开始，写入一定长度的连续数据
void SST25VF064ProgramLength(unsigned long Addr,unsigned char *dat,unsigned long length);
//读取某一地址的一个字节
unsigned char SST25VF064FlashReadByte(unsigned long Addr);
//读取一定长度到buff
void SST25VF064FlashRead(unsigned long Addr,unsigned char *pbuff,unsigned long length);


#endif



