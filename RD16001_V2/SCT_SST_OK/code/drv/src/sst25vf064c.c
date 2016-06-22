//#include "spi.h"
//#include "msp430.h"
//#include "sst25vf064c.h"
//#include "kernel.h"
//
//#define SST25VF064_CS_LOW 			P2OUT &= ~BIT0;_NOP();_NOP()
//#define SST25VF064_CS_HIGH		 	P2OUT |= BIT0//P20
//
//#define SST25VF0_CS_Low();                      P2OUT &= ~BIT0;_NOP();_NOP();
//#define SST25VF0_CS_High();                     P2OUT |= BIT0;//P20
//
//
//#define SST25VF064_HOLD_LOW 			P1OUT &= ~BIT4
//#define SST25VF064_HOLD_HIGH		 	P1OUT |= BIT4//P14
//
////read
//#define SST_DATA_UNIT_SIZE			                0x100
//
//#define SST25VF0_ReadReg					0x03
//#define SST25VF0_HighSpeedReadReg			        0x0B
//#define SST25VF0_SectorErase4KReg			        0x20
//#define SST25VF0_SectorErase32KReg			        0x52
//#define SST25VF0_SectorErase64KReg			        0xD8
//#define SST25VF0_ChipeEraseFullReg			        0x60		//C7
//#define SST25VF0_PageProgramReg				        0x02		
//#define SST25VF0_ReadStatusReg				        0x05		//RDSR
//#define SST25VF0_EnableWriteStatusReg		                0x50		//EWSR
//#define SST25VF0_WriteStatusReg				        0x01		//WRSR
//#define SST25VF0_WriteEnableReg				        0x06		//WREN
//#define SST25VF0_WriteDisableReg			        0x04		//WRDI
//#define SST25VF0_ReadDidReg					0x90		//read id   //AB
//#define SST25VF0_JedecIdReg					0x9f		  
//#define SST25VF0_EHLDReg					0xAA		//EHLD
//#define SST25VF0_ReadSidReg					0x88		//read security id
//#define SST25VF0_ProSidReg					0xA5		//program user security id
//#define SST25VF0_LockSidReg					0x85		//Lockout security id programming
//
//
//#define SST25VF064C_JEDEC_ID   				        0xBF254B
//
//
//unsigned char SST25VF064WriteReadByte(unsigned char cmd)
//{
//  return SpiWriteReadByte(cmd);
//}
//
//
//
//void EWSR(void)
//{
//	SST25VF064_CS_LOW;
//	SST25VF064WriteReadByte(SST25VF0_EnableWriteStatusReg);// enable writing to the status register 
//	SST25VF064_CS_HIGH; 	
//}
//
//void WRSR(unsigned char byte)
//{
//	SST25VF064_CS_LOW;			  // enable device 
//	SST25VF064WriteReadByte( SST25VF0_WriteStatusReg); // select write to status register 
//	SST25VF064WriteReadByte( byte); 	// data that will change the status of BPx or BPL (only bits 2,3,4,5,7 can be written) 
//	SST25VF064_CS_HIGH; 			// disable the device 
//}
//
//void EHLD(void)
//{
//	SST25VF064_CS_LOW;			        // enable device 
//	SST25VF064WriteReadByte( SST25VF0_EHLDReg);		
//	SST25VF064_CS_HIGH; 				// disable device 
//}
//
//void WREN(void)
//{
//	SST25VF064_CS_LOW;  
//	SST25VF064WriteReadByte( SST25VF0_WriteEnableReg);// enable writing to the status register 
//	SST25VF064_CS_HIGH; 
//}
//
//void WaitBusy(void)
//{
//	unsigned char temp = 1;
//	SST25VF064_CS_LOW;  
//	SST25VF064WriteReadByte( SST25VF0_ReadStatusReg);// send RDSR command 
//	while (temp==1)
//	{
//		temp = SST25VF064WriteReadByte(SST25VF0_ReadStatusReg);
//                delay_ms(5);
//		//temp=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);//Get the Value of Busy bit in the status register
//	}
//	SST25VF064_CS_HIGH; 
//}
//
//unsigned char ReadStatusRegister(void)
//{
//	unsigned char byte = 0;
//	SST25VF064_CS_LOW;  			 // enable device 
//	SST25VF064WriteReadByte( SST25VF0_ReadStatusReg);	 //send RDSR command 
//	byte = SST25VF064WriteReadByte( 0xFF);//receive byte 
//	SST25VF064_CS_HIGH; 			 //disable device 
//	return byte;
//}
//
//
//
//
//
//
//
//
//
//
//
//
////因为FLASH里面是没有时钟的，所以读取数据的时候需要spi口本身提供给FLASH
//void SST25VF064Init(void)
//{
//  SpiInit();
//  
//  //CS
//  P2REN &= ~BIT0;
//  P2DIR |= BIT0;
//  P2OUT |= BIT0;
//  //HOLD
//  P1REN &= ~BIT4;
//  P1DIR |= BIT4;
//  P1OUT |= BIT4;
//  
//  SST25VF0_CS_Low();
//  SST25VF064_HOLD_HIGH;
//  SST25VF0_CS_High();
//}
//
//
//
//long JedecIDRead(void) 
//{
//	long temp=0;
//	SST25VF0_CS_Low();			 	                // enable device 
//	SST25VF064WriteReadByte( SST25VF0_JedecIdReg);		 	            // send JEDEC ID command (9Fh) 
//	temp = (temp | SST25VF064WriteReadByte( 0XFF)) << 8;	// receive byte 
//	temp = (temp | SST25VF064WriteReadByte( 0XFF)) << 8;	
//	temp = (temp | SST25VF064WriteReadByte( 0XFF)); 	 	  // temp value = 0xBF254B 
//	SST25VF0_CS_High();			 	              // disable device 
//	return temp;
//}
//
//
//
//unsigned char Read(long Dst) 
//{
//	unsigned char byte = 0;	
//	SST25VF0_CS_Low();				                     // enable device 
//	SST25VF064WriteReadByte( SST25VF0_ReadReg);			               // read command 
//	SST25VF064WriteReadByte((((Dst & 0xFFFFFF) >> 16))); // send 3 address bytes 
//	SST25VF064WriteReadByte((((Dst & 0xFFFF) >> 8)));
//	SST25VF064WriteReadByte((Dst & 0xFF));
//        
//	byte = SST25VF064WriteReadByte( 0XFF);
//	SST25VF0_CS_High();				                   // disable device 
//	return byte;				                 // return one byte read 
//}
//
//void ExternFlashSectorErase_4K(long Dst)
//{
//	WREN();
//	SST25VF0_CS_Low();					// enable device 
//	SST25VF064WriteReadByte( SST25VF0_SectorErase4KReg);		// send Sector Erase command 
//	SST25VF064WriteReadByte((((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
//	SST25VF064WriteReadByte( (((Dst & 0xFFFF) >> 8)));
//	SST25VF064WriteReadByte( (Dst & 0xFF));
//	SST25VF0_CS_High();				// disable device 
//	//Wait Busy
//	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy 
//}
//
//
//void FlashChipErase(void)
//{	
//	WREN();				
//	SST25VF0_CS_Low();					// enable device
//	SST25VF064WriteReadByte( SST25VF0_ChipeEraseFullReg);		// send Chip Erase command (60h or C7h)
//	SST25VF0_CS_High();				// disable device
//	//Wait Busy
//	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy
//}
//
//
//void FlashPageProgramByte(long Dst,  unsigned char x)
//{
//	WREN(); 
//	SST25VF0_CS_Low();				// enable device 
//	SST25VF064WriteReadByte( SST25VF0_PageProgramReg);   // send Byte Program command 
//	SST25VF064WriteReadByte( (((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
//	SST25VF064WriteReadByte( (((Dst & 0xFFFF) >> 8)   ));
//	SST25VF064WriteReadByte( (  Dst & 0xFF  )          );
//	SST25VF064WriteReadByte( (x));
//	//Wait Busy
//	while ((ReadStatusRegister()& 0x01) == 0x01);// waste time until not busy 
//}
