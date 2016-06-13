#include "spi.h"
#include "msp430.h"
#include "sst25vf064c.h"
#include "kernel.h"

#define SST25VF064_CS_LOW 			P2OUT |= BIT0//P20
#define SST25VF064_CS_HIGH		 	P2OUT &= ~BIT0

#define SST25VF064_HOLD_LOW 			P1OUT |= BIT4//P14
#define SST25VF064_HOLD_HIGH		 	P1OUT &= ~BIT4

//read

#define READ          		0x03		// normal read 

#define READ_DOUBLE_IO		0xBB		//read in double IO

#define READ_DOUBLE_OUT 	0x3B		//read in double OUT

#define READ_HS       		0x0B		// read with 8 extra clocks between address and data. for high speed bus 

//Erase

#define SECTOR_ERASE  		0x20		// Sector Erase 4k

#define BLOCK_ERASE   		0x52		// Block Erase 32k

#define BLOCK_ERASE_OP 		0xD8		// Block Erase 64k

#define CHIP_ERASE    		0x60		// Chip Erase

#define CHIP_ERASE_OP 		0xC7		// Chip Erase optional cmd

//program

#define BYTE_PROGRAM  		0x02		// Byte Program

#define AAI_PROGRAM   		0xAD		// auto increment mode Word program




#define RDSR          		0x05		// Read Status Register

#define EWSR          		0x50		// Enable Write Status Register

#define WRSR          		0x01		// Write Status register

#define WREN          		0x06		// Write Enable

#define WRDI          		0x04		// Write Disable

#define RDID         		0x90		// Read ID

#define RDID_OP       		0xAB		// Read ID, optional cmd

#define JEDEC_ID      		0x9F		// JEDEC ID read cmd



#define EHLD			0xAA		//SWITCH  RST#/HOLD# to HOLD func 

#define SID			0x88		//read safe ID

#define SID_PROGRAM		0xA5		//program in user's safe ID area

#define SID_LOCK		0x85		//LOCK the ID area




//因为FLASH里面是没有时钟的，所以读取数据的时候需要spi口本身提供给FLASH
void SST25VF064Init(void)
{
  SpiInit();
  
  //CS
  P2REN &= ~BIT0;
  P2DIR |= BIT0;
  P2OUT |= BIT0;
  //HOLD
  P1REN &= ~BIT4;
  P1DIR |= BIT4;
  P1OUT |= BIT4;
}

unsigned char SST25VF064WriteReadByte(unsigned char cmd)
{
  return SpiWriteReadByte(cmd);
}

void SST25VF064Unselect(void)
{
	SST25VF064_CS_HIGH;
}
void SST25VF064Select(void)
{
	SST25VF064_CS_LOW;
}

void SST25VF064Reset(void)
{
	SST25VF064_HOLD_HIGH;
	delay_ms(5);
	SST25VF064_HOLD_LOW;
	delay_ms(1);
	SST25VF064_HOLD_HIGH;
	delay_ms(5);
}




void SST25VF064SectorErase(unsigned long Addr)
{
	unsigned long timeover=0; 
	SST25VF064Select();
	SST25VF064WriteReadByte(WREN);
	SST25VF064WriteReadByte(SECTOR_ERASE);
	SST25VF064WriteReadByte((unsigned char)(Addr>>16));
	SST25VF064WriteReadByte((unsigned char)(Addr>>8));
	SST25VF064WriteReadByte((unsigned char)Addr);
	while(SST25VF064BusySatue() == 0 )
		{
			timeover++;
			if(timeover == 200)
				{timeover = 0;break;}
			delay_ms(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064BlockErase(unsigned long Addr)
{
	unsigned long timeover=0; 
	SST25VF064Select();
	SST25VF064WriteReadByte(WREN);
	SST25VF064WriteReadByte(BLOCK_ERASE);
	SST25VF064WriteReadByte((unsigned char)(Addr>>16));
	SST25VF064WriteReadByte((unsigned char)(Addr>>8));
	SST25VF064WriteReadByte((unsigned char)Addr);
	while(SST25VF064BusySatue() == 0 )
		{
			timeover++;
			if(timeover == 200)
				{timeover = 0;break;}
			delay_ms(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064BlockOPErase(unsigned long Addr)
{
	unsigned long timeover=0; 
	SST25VF064Select();
	SST25VF064WriteReadByte(WREN);
	SST25VF064WriteReadByte(BLOCK_ERASE_OP);
	SST25VF064WriteReadByte((unsigned char)(Addr>>16));
	SST25VF064WriteReadByte((unsigned char)(Addr>>8));
	SST25VF064WriteReadByte((unsigned char)Addr);
	while(SST25VF064BusySatue() == 0 )
		{
			timeover++;
			if(timeover == 200)
				{timeover = 0;break;}
			delay_ms(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064ChipErase(unsigned long Addr)
{
	unsigned long timeover=0; 
	SST25VF064Select();
	SST25VF064WriteReadByte(WREN);
	SST25VF064WriteReadByte(CHIP_ERASE);
	SST25VF064WriteReadByte((unsigned char)(Addr>>16));
	SST25VF064WriteReadByte((unsigned char)(Addr>>8));
	SST25VF064WriteReadByte((unsigned char)Addr);
	while(SST25VF064BusySatue() == 0 )
		{
			timeover++;
			if(timeover == 200)
				{timeover = 0;break;}
			delay_ms(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}



//1:unbusy
//0:busy
unsigned char SST25VF064BusySatue(void)
{
	SST25VF064WriteReadByte(RDSR);
	if( SST25VF064WriteReadByte(0xff) & 0x01 )
		{return 0;}
	else
		{return 1;}
}



//向某一个地址写入一个数据
void SST25VF064ProgramByte(unsigned long Addr,unsigned char dat)
{
	unsigned long timeover=0;
	SST25VF064Select();
	SST25VF064WriteReadByte(WREN);
	SST25VF064WriteReadByte(BYTE_PROGRAM);
	SST25VF064WriteReadByte((unsigned char)(Addr>>16));
	SST25VF064WriteReadByte((unsigned char)(Addr>>8));
	SST25VF064WriteReadByte((unsigned char)Addr);
	SST25VF064WriteReadByte(dat);
	while(SST25VF064BusySatue() == 0 )
		{
			timeover++;
			if(timeover == 200)
				{timeover = 0;break;}
			//delay
		}	
	
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
//从某一个地址开始，写入一定长度的连续数据
void SST25VF064ProgramLength(unsigned long Addr,unsigned char *dat,unsigned long length)
{
	unsigned int i;
	for(i = 0;i<length;i++)
		{
			SST25VF064ProgramByte(Addr+i,*(dat+i));
		}
}




//读取某一地址的一个字节
unsigned char SST25VF064FlashReadByte(unsigned long Addr)
{
		unsigned long dat;
		SST25VF064Select();
		SST25VF064WriteReadByte(READ);
		SST25VF064WriteReadByte((unsigned char)(Addr>>16));
		SST25VF064WriteReadByte((unsigned char)(Addr>>8));
		SST25VF064WriteReadByte((unsigned char)Addr);
		dat = SST25VF064WriteReadByte(0xff);
		SST25VF064Unselect();
		return dat;
}
//读取一定长度到buff
void SST25VF064FlashRead(unsigned long Addr,unsigned char *pbuff,unsigned long length)
{
		unsigned long i;
		SST25VF064Select();
		SST25VF064WriteReadByte(READ);
		SST25VF064WriteReadByte((unsigned char)(Addr>>16));
		SST25VF064WriteReadByte((unsigned char)(Addr>>8));
		SST25VF064WriteReadByte((unsigned char)Addr);
		for(i=0;i<length;i++)
			{
				*(pbuff+i) = SST25VF064WriteReadByte(0xff);
			}
		SST25VF064Unselect();
}

