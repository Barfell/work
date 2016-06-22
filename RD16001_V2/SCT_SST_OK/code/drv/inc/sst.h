#ifndef _SST_H
#define _SST_H

void SST_init();


void SST_Chip_Erase();
void SST_Sector_Erase(unsigned long Dst);
void SST_Block_Erase_32K(unsigned long Dst);
void SST_Block_Erase_64K(unsigned long Dst);

unsigned char SST_Read_ID(unsigned char ID_addr);
unsigned long SST_Jedec_ID_Read() ;

void SST_Byte_Program(unsigned long Dst, unsigned char byte);
unsigned char SST_Byte_Read(unsigned long Dst);
void SST_Word_Program(unsigned long Dst,unsigned long dat);
unsigned long SST_Word_Read(unsigned long Dst);
void SST_Length_Program(unsigned long Dst,unsigned char *buf, unsigned long len);
void SST_Length_Read(unsigned long Dst,unsigned char *buf, unsigned long len); 


unsigned char SST_HighSpeed_Read(unsigned long Dst);

#endif