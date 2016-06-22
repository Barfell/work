/*Software Driver
Device Communication Protocol(pinout related) functions:
Functions                    		Function
------------------------------------------------------------------
init					Initializes clock to set up mode 0.
Send_Byte				Sends one byte using SI pin to send and 
					shift out 1-bit per clock rising edge
Get_Byte				Receives one byte using SO pin to receive and shift 
					in 1-bit per clock falling edge
Poll_SO					Used in the polling for RY/BY# of SO during AAI programming
CE_High					Sets Chip Enable pin of the serial flash to high
CE_Low					Clears Chip Enable of the serial flash to low
Hold_Low				Clears Hold pin to make serial flash hold
Unhold					Unholds the serial flash
WP_Low					Clears WP pin to make serial flash write protected
UnWP					Disables write protection pin

Note:  The pin names of the SST25VF032B are used in this application note. The associated test code
will not compile unless these pinouts (SCK, SI, SO, SO, CE, WP, Hold) are pre-defined on your
software which should reflect your hardware interfaced. 	 


Device Operation Instruction functions:

Functions                    		Function
------------------------------------------------------------------
Read_Status_Register			Reads the status register of the serial flash
EWSR					Enables the Write Status Register
WRSR					Performs a write to the status register
WREN					Write enables the serial flash
WRDI					Write disables the serial flash
EBSY					Enable SO to output RY/BY# status during AAI programming
DBSY					Disable SO to output RY/BY# status during AAI programming
Read_ID					Reads the manufacturer ID and device ID
Jedec_ID_Read				Reads the Jedec ID
Read					Reads one byte from the serial flash and returns byte(max of 25 MHz CLK frequency)
Read_Cont				Reads multiple bytes(max of 25 MHz CLK frequency)
HighSpeed_Read				Reads one byte from the serial flash and returns byte(max of 66 MHz CLK frequency)
HighSpeed_Read_Cont			Reads multiple bytes(max of 66 MHz CLK frequency)
SST_Byte_Program				Program one byte to the serial flash
Auto_Add_IncA				Initial Auto Address Increment process
Auto_Add_IncB				Successive Auto_Address_Increment process after AAI initiation
Auto_Add_IncA_EBSY			Initial Auto Address Increment process with EBSY
Auto_Add_IncB_EBSY			Successive Auto_Address_Increment process after AAI initiation with EBSY
Chip_Erase				Erases entire serial flash
Sector_Erase				Erases one sector (4 KB) of the serial flash
Block_Erase_32K				Erases 32 KByte block memory of the serial flash
Block_Erase_64K				Erases 64 KByte block memory of the serial flash
Wait_Busy				Polls status register until busy bit is low
Wait_Busy_AAI				Polls status register until busy bit is low for AAI programming
WREN_Check				Checks to see if WEL is set
WREN_AAI_Check				Checks to see if WEL and AAI mode is set
                                                      
"C" LANGUAGE DRIVERS 
*/


#include "msp430.h"
#include "sst.h"
#include "spi.h"
#include "cfg.h"


#define SPI_MISO        P2IN & BIT1
#define SO              SPI_MISO?1:0;

#define SPI_MOSI_H      P2OUT |=  BIT2
#define SPI_MOSI_L      P2OUT &= ~BIT2

#define SPI_SCK_H       P2OUT |=  BIT3
#define SPI_SCK_L       P2OUT &= ~BIT3

#define CE_Low() 			P2OUT &= ~BIT0;_NOP();_NOP()
#define CE_High()		 	P2OUT |= BIT0//P20

#define Hold_Low() 			P1OUT &= ~BIT4
#define Unhold()		 	P1OUT |= BIT4//P14



void Send_Byte(unsigned char out)
{	
  unsigned char i = 0;
  for (i = 0; i < 8; i++)
  {    
    if ((out & 0x80) == 0x80)	/* check if MSB is high */
            SPI_MOSI_H;
    else
            SPI_MOSI_L;			/* if not, set to low */
    SPI_SCK_H;			/* toggle clock high */
    out = (out << 1);		/* shift 1 place for next bit */
    SPI_SCK_L;			/* toggle clock low */
  }
}

unsigned char Get_Byte()
{
  unsigned char i = 0, in = 0, temp = 0;
  for (i = 0; i < 8; i++)
  {
    in = (in << 1);		/* shift 1 place to the left or shift in 0 */
    temp = SO;		/* save input */
    SPI_SCK_H;		/* toggle clock high */
    if (temp == 1)			/* check to see if bit is high */
    {in = in | 0x01;}		/* if high, make bit high */
    SPI_SCK_L;		/* toggle clock low */
  }
  return in;
}

void Poll_SO()
{
  unsigned char temp = 0;
  CE_Low();
  while (temp == 0x00)	/* waste time until not busy */
          temp = SO;
  CE_High();
}

void WP_Low()
{
	//WP = 0;				/* clear WP pin */
}


void UnWP()
{
	//WP = 1;				/* set WP pin */
}
















unsigned char Read_Status_Register()
{
  unsigned char byte = 0;
  CE_Low();			/* enable device */
  Send_Byte(0x05);		/* send RDSR command */
  byte = Get_Byte();		/* receive byte */
  CE_High();			/* disable device */
  return byte;
}


void EWSR()
{
  CE_Low();			/* enable device */
  Send_Byte(0x50);		/* enable writing to the status register */
  CE_High();			/* disable device */
}
void WRSR(unsigned char byte)
{
  CE_Low();			/* enable device */
  Send_Byte(0x01);		/* select write to status register */
  Send_Byte(byte);		/* data that will change the status of BPx 
                                     or BPL (only bits 2,3,4,5,7 can be written) */
  CE_High();			/* disable the device */
}
void EHLD(void)
{
  CE_Low();			/* enable device */
  Send_Byte(0xAA);		/* send WREN command */
  CE_High();			/* disable device */
}
void WREN()
{
  CE_Low();			/* enable device */
  Send_Byte(0x06);		/* send WREN command */
  CE_High();			/* disable device */
}
void WRDI()
{
  CE_Low();			/* enable device */
  Send_Byte(0x04);		/* send WRDI command */
  CE_High();			/* disable device */
}
void EBSY()
{
  CE_Low();			/* enable device */
  Send_Byte(0x70);		/* send EBSY command */
  CE_High();			/* disable device */
}
void DBSY()
{
  CE_Low();			/* enable device */
  Send_Byte(0x80);		/* send DBSY command */
  CE_High();			/* disable device */
}
void Wait_Busy()
{
  while ((Read_Status_Register() & 0x01) == 0x01)	/* waste time until not busy */
    {Read_Status_Register();}
}











void SST_init()
{
  P2REN &= ~BIT0;
  P2REN &= ~BIT1;
  P2REN &= ~BIT2;
  P2REN &= ~BIT3;
  
  P2DIR |= BIT2;        //MOSI
  P2DIR |= BIT3;        //SCK
  P2DIR &= ~BIT1;       //MISO
  //CS
  P2DIR |= BIT0;
  P2OUT |= BIT0;
  //HOLD
  P1REN &= ~BIT4;
  P1DIR |= BIT4;
  P1OUT |= BIT4;
  
  SPI_SCK_L;	/* set clock to low initial state */
  
  EWSR();       //使能写寄存器
  WRSR(0x00);   //BPL=0,BP0~3=0000,NO Protect
}
void SST_Chip_Erase()
{
  CE_High();
  WREN();
  CE_Low();	
  /* enable device */
  Send_Byte(0x60);			/* send Chip Erase command (60h or C7h) */
  CE_High();				/* disable device */
  Wait_Busy();
}
void SST_Sector_Erase(unsigned long Dst)
{
  CE_High();
  WREN();
  CE_Low();	
  /* enable device */
  Send_Byte(0x20);			/* send Sector Erase command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  CE_High();				/* disable device */
  Wait_Busy();
}
void SST_Block_Erase_32K(unsigned long Dst)
{
  CE_High();
  WREN();
  CE_Low();				/* enable device */
  Send_Byte(0x52);			/* send 32 KByte Block Erase command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  CE_High();				/* disable device */
  Wait_Busy();
}
void SST_Block_Erase_64K(unsigned long Dst)
{
  CE_High();
  WREN();
  CE_Low();				/* enable device */
  Send_Byte(0xD8);			/* send 64KByte Block Erase command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  CE_High();				/* disable device */
  Wait_Busy();//Wait_Busy必须在CE_High之后 ！！！！！！
}

unsigned char SST_Read_ID(unsigned char ID_addr)
{
  unsigned char byte;
  CE_Low();			/* enable device */
  Send_Byte(0x90);		/* send read ID command (90h or ABh) */
  Send_Byte(0x00);		/* send address */
  Send_Byte(0x00);		/* send address */
  Send_Byte(ID_addr);		/* send address - either 00H or 01H */
  byte = Get_Byte();		/* receive byte */
  CE_High();			/* disable device */
  return byte;
}
unsigned long SST_Jedec_ID_Read() 
{
  unsigned long temp;
  temp = 0;
  CE_Low();			 /* enable device */
  Send_Byte(0x9F);		 /* send JEDEC ID command (9Fh) */
  temp = (temp | Get_Byte()) << 8; /* receive byte */
  temp = (temp | Get_Byte()) << 8;	
  temp = (temp | Get_Byte()); 	 /* temp value = 0xBF254A */
  CE_High();			 /* disable device */
  return temp;
}








void SST_Byte_Program(unsigned long Dst, unsigned char byte)
{
  WREN();
  CE_Low();	
  Send_Byte(0x02); 			/* send Byte Program command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  Send_Byte(byte);			/* send byte to be programmed */
  CE_High();				/* disable device */
  Wait_Busy();
}
unsigned char SST_Byte_Read(unsigned long Dst) 
{
  unsigned char byte = 0;	
  CE_Low();			/* enable device */
  Send_Byte(0x03); 		/* read command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  byte = Get_Byte();
  CE_High();			/* disable device */
  return byte;			/* return one byte read */
}




void SST_Length_Program(unsigned long Dst,unsigned char *buf, unsigned long len)
{
  unsigned long i = 0;
  for(i=0;i<len;i++)
  {
    SST_Byte_Program(Dst+i, *(buf+i));
  }
}
void SST_Length_Read(unsigned long Dst,unsigned char *buf, unsigned long len) 
{
  unsigned long i = 0;
  for(i=0;i<len;i++)
  {
    *(buf+i) = SST_Byte_Read(Dst+i);
  }
}



void SST_Word_Program(unsigned long Dst,unsigned long dat)
{
  SST_Byte_Program(Dst+0, (unsigned char)(dat>>24) );
  SST_Byte_Program(Dst+1, (unsigned char)(dat>>16));
  SST_Byte_Program(Dst+2, (unsigned char)(dat>>8));
  SST_Byte_Program(Dst+3, (unsigned char)dat);
}
unsigned long SST_Word_Read(unsigned long Dst) 
{
  unsigned long ret = 0;
  unsigned long word1 = 0;
  unsigned long word2 = 0;
  unsigned long word3 = 0;
  unsigned long word4 = 0;
  word1 = SST_Byte_Read(Dst+0);
  word2 = SST_Byte_Read(Dst+1);
  word3 = SST_Byte_Read(Dst+2);
  word4 = SST_Byte_Read(Dst+3);
  ret = word1<<24|word2<<16|word3<<8|word4;
  
  return ret;
}



unsigned char SST_HighSpeed_Read(unsigned long Dst) 
{
  unsigned char byte = 0;	
  CE_Low();			/* enable device */
  Send_Byte(0x0B); 		/* read command */
  Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
  Send_Byte(((Dst & 0xFFFF) >> 8));
  Send_Byte(Dst & 0xFF);
  Send_Byte(0xFF);		/*dummy byte*/
  byte = Get_Byte();
  CE_High();			/* disable device */
  return byte;			/* return one byte read */
}












//设置暂存的数据长度
void SetDataLen(unsigned long num)
{
  SST_Sector_Erase(RECORD_DATA_LEN_ADDR);
  SST_Word_Program(RECORD_DATA_LEN_ADDR,num);
}
//获取暂存的数据长度
unsigned long GetDataLen(void)
{
 return SST_Word_Read(RECORD_DATA_LEN_ADDR);
}

//设置读取到的位置
void SetReadPos(unsigned long num)
{
  SST_Sector_Erase(RECORD_READ_POS_ADDR);
  SST_Word_Program(RECORD_READ_POS_ADDR,num);
}
//获取读取到的位置，返回读取到的当前位置
unsigned long GetReadPos(void)
{
  //记得先初始化，不然会导致初始值很大 
  return SST_Word_Read(RECORD_READ_POS_ADDR);
}


//存储数据dat到FALASH，长度为len
void StoreRecordData(char *dat,unsigned int len)
{
  unsigned long WriteAddr = 0;
  unsigned long data_num = 0;
  
  data_num = GetDataLen();
  
  WriteAddr = data_num + RECORD_DATA_ADDR;
  
  SST_Length_Program(WriteAddr,(unsigned char*)dat,len);
  
  SetDataLen(data_num + len);
}

//读取一定长度num的数据,存放到buf，
void ReadRecordData( unsigned char *buf, unsigned char num)
{
  unsigned long Addr = 0;
  Addr = GetReadPos();
  SST_Length_Read(Addr,buf,num);
  SetReadPos(Addr+num);
}