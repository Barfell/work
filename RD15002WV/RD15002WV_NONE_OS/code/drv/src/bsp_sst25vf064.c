#include  "includes.h"


#define SST25VF064_CS_LOW 			GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SST25VF064_CS_HIGH		 	GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define SST25VF064_HOLD_LOW 			GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define SST25VF064_HOLD_HIGH		 	GPIO_SetBits(GPIOB,GPIO_Pin_11)



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
#define RDID         		 	0x90		// Read ID
#define RDID_OP       		0xAB		// Read ID, optional cmd
#define JEDEC_ID      		0x9F		// JEDEC ID read cmd

#define EHLD							0xAA		//SWITCH  RST#/HOLD# to HOLD func 
#define SID								0x88		//read safe ID
#define SID_PROGRAM				0xA5		//program in user's safe ID area
#define SID_LOCK					0x85		//LOCK the ID area


//��ΪFLASH������û��ʱ�ӵģ����Զ�ȡ���ݵ�ʱ����Ҫspi�ڱ����ṩ��FLASH
void SST25VF064Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	//MISO ---->SST25VF064--SDO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//MOSI ---->SST25VF064--SDI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//SCK ---->SST25VF064--SCK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//CS ---->SST25VF064--CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//HOLD ---->SST25VF064--HOLD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 0x00;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit =  SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2,&SPI_InitStructure);
	SPI_Cmd(SPI2,ENABLE);
	
}

unsigned char SST25VF064WriteReadByte(unsigned char cmd)
{
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET );
	SPI_I2S_SendData(SPI2,cmd);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET );
	SPI_I2S_SendData(SPI2,0xff);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET );
	return SPI_I2S_ReceiveData(SPI2);
	//while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET );
	//SPI_I2S_SendData(SPI2,0xff);
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
	DlyMs(5);
	SST25VF064_HOLD_LOW;
	DlyMs(1);
	SST25VF064_HOLD_HIGH;
	DlyMs(5);
}




void SST25VF064SectorErase(unsigned int Addr)
{
	unsigned int timeover=0; 
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
			DlyMs(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064BlockErase(unsigned int Addr)
{
	unsigned int timeover=0; 
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
			DlyMs(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064BlockOPErase(unsigned int Addr)
{
	unsigned int timeover=0; 
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
			DlyMs(5);
		}
	SST25VF064WriteReadByte(WRDI);
	SST25VF064Unselect();
}
void SST25VF064ChipErase(unsigned int Addr)
{
	unsigned int timeover=0; 
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
			DlyMs(5);
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



//��ĳһ����ַд��һ������
void SST25VF064ProgramByte(unsigned int Addr,unsigned char dat)
{
	unsigned int timeover=0;
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
//��ĳһ����ַ��ʼ��д��һ�����ȵ���������
void SST25VF064ProgramLength(unsigned int Addr,unsigned char *dat,unsigned int length)
{
	unsigned int i;
	for(i = 0;i<length;i++)
		{
			SST25VF064ProgramByte(Addr+i,*(dat+i));
		}
}




//��ȡĳһ��ַ��һ���ֽ�
unsigned char SST25VF064FlashReadByte(unsigned int Addr)
{
		unsigned int dat;
		SST25VF064Select();
		SST25VF064WriteReadByte(READ);
		SST25VF064WriteReadByte((unsigned char)(Addr>>16));
		SST25VF064WriteReadByte((unsigned char)(Addr>>8));
		SST25VF064WriteReadByte((unsigned char)Addr);
		dat = SST25VF064WriteReadByte(0xff);
		SST25VF064Unselect();
		return dat;
}
//��ȡһ�����ȵ�buff
void SST25VF064FlashRead(unsigned int Addr,unsigned char *pbuff,unsigned int length)
{
		unsigned int i;
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

