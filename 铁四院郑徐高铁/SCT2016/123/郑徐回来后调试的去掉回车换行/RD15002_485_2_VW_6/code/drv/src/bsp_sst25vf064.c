#include "bsp_sst25vf064.h"

#define SST25VF0_SPI			SPI2

#define RCC_SST25VF0_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

#define SST25VF0_HOLD_GPIO	    GPIOB	
#define SST25VF0_HOLD_PIN		GPIO_Pin_11	

#define SST25VF0_CS_GPIO		GPIOB
#define SST25VF0_CS_PIN			GPIO_Pin_12


#define SST25VF0_CS_Low()   GPIO_ResetBits(SST25VF0_CS_GPIO, SST25VF0_CS_PIN)
#define SST25VF0_CS_High()  GPIO_SetBits(SST25VF0_CS_GPIO, SST25VF0_CS_PIN)

#define SUSPEND_SST25VF0()	GPIO_ResetBits(SST25VF0_HOLD_GPIO,SST25VF0_HOLD_PIN);
#define RELEASE_SST25VF0()	GPIO_SetBits(SST25VF0_HOLD_GPIO,SST25VF0_HOLD_PIN);

//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ 						  
//SPI�ڳ�ʼ��
STATIC VOID CHL_SPI_Init(VOID)
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
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2); 

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


VOID SpiOpen(SPI_TypeDef *pSPIx)
{  
	SPI_CalculateCRC(pSPIx, DISABLE);//forbit crc
	/* Enable SPIx */
	SPI_Cmd(pSPIx, ENABLE);
}

VOID SpiClose(SPI_TypeDef *pSPIx)
{ 
	SPI_Cmd(pSPIx, DISABLE);
}

VOID SpiSetSpeed(SPI_TypeDef *pSPIx, U8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	pSPIx->CR1&=0XFFC7;
	pSPIx->CR1|=SPI_BaudRatePrescaler;	//����SPI�ٶ� 
	SPI_Cmd(pSPIx, ENABLE); 

} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
U8 SpiReadWriteByte(SPI_TypeDef *pSPIx, U8 TxData)
{		
	U8 u8retry=0;	
	U8	u8Ret;
	while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
			
	}			  
	SPI_I2S_SendData(pSPIx, TxData); //ͨ������SPIx����һ������
	u8retry=0;
	while(SPI_I2S_GetFlagStatus(pSPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
	}
	
	u8Ret = SPI_I2S_ReceiveData(pSPIx);//����ͨ��SPIx������յ�����
SPI_ReadWriteByte_exit:	
	return  u8Ret;				    
}



STATIC VOID EWSR(VOID)
{
	SST25VF0_CS_Low();  
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_EnableWriteStatusReg);// enable writing to the status register 
	SST25VF0_CS_High(); 	
}

STATIC VOID WRSR(U8 byte)
{
	SST25VF0_CS_Low();			  // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_WriteStatusReg); // select write to status register 
	SpiReadWriteByte(SST25VF0_SPI, byte); 	// data that will change the status of BPx or BPL (only bits 2,3,4,5,7 can be written) 
	SST25VF0_CS_High();			// disable the device 
}

STATIC VOID EHLD(VOID)
{
	SST25VF0_CS_Low();				// enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_EHLDReg);		
	SST25VF0_CS_High();				// disable device 
}

STATIC VOID WREN(VOID)
{
	SST25VF0_CS_Low();  
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_WriteEnableReg);// enable writing to the status register 
	SST25VF0_CS_High();
}

//STATIC VOID WRDI(VOID)
//{
//	SST25VF0_CS_Low();  
//	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_WriteDisableReg);// enable writing to the status register 
//	SST25VF0_CS_High();
//}

STATIC VOID WaitBusy(VOID)
{
	U8 temp = 1;
	SST25VF0_CS_Low();
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadStatusReg);// send RDSR command 
	while (temp==1)
	{
		SpiReadWriteByte(SST25VF0_SPI, 0XFF);
		temp=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);//Get the Value of Busy bit in the status register
	}
	SST25VF0_CS_High();	
}

STATIC U8 ReadStatusRegister(VOID)
{
	U8 byte = 0;
	SST25VF0_CS_Low();				 // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadStatusReg);	 //send RDSR command 
	byte = SpiReadWriteByte(SST25VF0_SPI, 0xFF);//receive byte 
	SST25VF0_CS_High();			 //disable device 
	return byte;
}













//��ʼ��SPI FLASH��IO��
VOID SST25VF0_Init(VOID)
{ 
	RCC_SST25VF0_CONFIG();
	
    CHL_SPI_Init();
		
	SST25VF0_CS_Low();				 // enable device 
	
	RELEASE_SST25VF0();
        
	SST25VF0_CS_High();			//SPI FLASH��ѡ��
    
}  
/**********************************************
//��������:void ExternFlash_Init()
//��������:SST25VF064�ܽţ��Ĵ�����SPI��ʽ��ʼ��
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlash_Init(VOID)
{	
	EHLD();    //Ĭ���ϵ��ʱ��HOLDΪ��λ���ţ���������RES/HOLD�ܽŵĹ���ΪHOLD
	EWSR();    //ʹ��д�Ĵ���
	WRSR(0x00);//BPL=0,BP0~3=0000,NO Protect
}

U32 ReadID(U8 ID_addr)
{
	U32 byte;
	byte=0;
	SST25VF0_CS_Low();  				    // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadDidReg);			// send read ID command (90h or ABh) 
	SpiReadWriteByte(SST25VF0_SPI, 0X00);			// send address 
	SpiReadWriteByte(SST25VF0_SPI, 0X00);			// send address 
	SpiReadWriteByte(SST25VF0_SPI, ID_addr);	// send address - either 00H or 01H 
	byte = (byte| SpiReadWriteByte(SST25VF0_SPI, 0XFF))<<8;// receive byte 
	byte = (byte| SpiReadWriteByte(SST25VF0_SPI, 0XFF));// receive byte 
	SST25VF0_CS_High();				  // disable device 
	return byte;
}

U32 JedecIDRead(VOID) 
{
	U32 temp=0;
	SST25VF0_CS_Low();			 	                // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_JedecIdReg);		 	            // send JEDEC ID command (9Fh) 
	temp = (temp | SpiReadWriteByte(SST25VF0_SPI, 0XFF)) << 8;	// receive byte 
	temp = (temp | SpiReadWriteByte(SST25VF0_SPI, 0XFF)) << 8;	
	temp = (temp | SpiReadWriteByte(SST25VF0_SPI, 0XFF)); 	 	  // temp value = 0xBF254B 
	SST25VF0_CS_High();			 	              // disable device 
	return temp;
}

VOID ReadSID(U8 Dst, U8 *psave, U8 security_length) 
{
	u8 i=0;	
	if (security_length>32)
	{ security_length=32;}
	SST25VF0_CS_Low();				       // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadSidReg); 		
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));  //��ַ����
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));  //dummy,������,������ֵ
	for (i=Dst;i<(security_length+Dst);i++)
	{ 
		*psave++ = SpiReadWriteByte(SST25VF0_SPI, 0XFF); 
	}	
	SST25VF0_CS_High();			       // disable device 
}

VOID ProgSID(U8 *psecurityid) 
{
	U8 i=0;
	psecurityid+=8;
	SST25VF0_CS_Low();			 // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ProSidReg); 		
	SpiReadWriteByte(SST25VF0_SPI, 0X08);//address of user programmable area
	for (i=0;i<24;i++)
	{	
		SpiReadWriteByte(SST25VF0_SPI,(*psecurityid++));
	}
	SST25VF0_CS_High();		 // disable device 
}

VOID LockSID(VOID) 
{
	SST25VF0_CS_Low();				 // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_LockSidReg); 		
	SST25VF0_CS_High();		 // disable device 
}

U8 Read(U32 Dst) 
{
	U8 byte = 0;	
	SST25VF0_CS_Low();				                     // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadReg);			               // read command 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFFFF) >> 16))); // send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));
	byte = SpiReadWriteByte(SST25VF0_SPI, 0XFF);
	SST25VF0_CS_High();				                   // disable device 
	return byte;				                 // return one byte read 
}
/**********************************************
//��������:void ExternFlashBlockErase_64K(u32 Dst)
//��������:����64KB�Ŀ�
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashBlockErase_64K(U32 Dst)
{  	
	//WREN
	WREN();
	//Block Erase 32K
	SST25VF0_CS_Low();				  // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_SectorErase64KReg);		// send 64KByte Block Erase command 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI, (Dst & 0xFF));
	SST25VF0_CS_High();					// disable device 
	//Wait Busy
	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy 
}
/**********************************************
//��������:void ExternFlashBlockErase_32K(u32 Dst)
//��������:����32KB�Ŀ�
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashBlockErase_32K(U32 Dst)
{  	
	//WREN
	WREN();
	//Block Erase 32K
	SST25VF0_CS_Low();					// enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_SectorErase32KReg);		// send 32 KByte Block Erase command 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));
	SST25VF0_CS_High();				// disable device 
	//Wait Busy
	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy 
}
/**********************************************
//��������:void ExternFlashSectorErase(u32 Dst)
//��������:4KB��������
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashSectorErase_4K(U32 Dst)
{
	//WREN
	WREN();
	//Sector Erase
	SST25VF0_CS_Low();					// enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_SectorErase4KReg);		// send Sector Erase command 
	SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI, (((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI, (Dst & 0xFF));
	SST25VF0_CS_High();				// disable device 
	//Wait Busy
	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy 
}

/**********************************************
//��������:void ExternFlashChipErase()
//��������:��Ƭ����
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashChipErase(VOID)
{	
	//WREN
	WREN();
	//Chip Erase 					
	SST25VF0_CS_Low();					// enable device
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ChipeEraseFullReg);		// send Chip Erase command (60h or C7h)
	SST25VF0_CS_High();				// disable device
	//Wait Busy
	while ((ReadStatusRegister()& 0x01) == 0x01);	// waste time until not busy
}


/**********************************************
//��������:void ExternFlashHighSpeedRead(u32 Dst, u8 *psave,u32 no_bytes)
//��������:���������ȡ���ֽ�����
//�������:u32 Dst:��ַ, u8 *psave:��ŵ�ַ,u32 no_bytes:��ȡ�ֽ���
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashHighSpeedRead(U32 Dst, U8 *psave, U32 no_bytes)
{
	U32 i = 0;
	SST25VF0_CS_Low();				                    // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_HighSpeedReadReg); 			              // read command 
	SpiReadWriteByte(SST25VF0_SPI, (((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI, (((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI, (Dst & 0xFF));
	SpiReadWriteByte(SST25VF0_SPI, 0xFF);			                //dummy byte
	for (i = 0; i < no_bytes; i++)		  // read until no_bytes is reached 
	{
		*psave++ = SpiReadWriteByte(SST25VF0_SPI, 0XFF);	            // receive byte and store at address 80H - FFH 
	}
	SST25VF0_CS_High();					                  // disable device 
}

/**********************************************
//��������:void ExternFlashPageProgram(u32 Dst,u8 *pupper,u32 amount)
//��������:ҳ���
//�������:
//���ز���:
//˵��:
***********************************************/
VOID ExternFlashPageProgram(U32 Dst, U8 *pupper,U32 amount)
{
	U32 i;
	i=0;	
	//WREN
	WREN(); 
	//Page Program
	SST25VF0_CS_Low();					                  // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_PageProgramReg);                  // send Byte Program command 
	SpiReadWriteByte(SST25VF0_SPI, (((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
	SpiReadWriteByte(SST25VF0_SPI, (((Dst & 0xFFFF) >> 8)));
	SpiReadWriteByte(SST25VF0_SPI, (Dst & 0xFF));
	if(amount>(256-(Dst&0xFF)))        //д��ĳ��ȳ���ҳ�߽������ַ
	{
		for (i=0;i<(256-(Dst&0xFF));i++)
		{	
			SpiReadWriteByte(SST25VF0_SPI, (*pupper++));		        // send byte to be programmed 
		}
		SST25VF0_CS_High();						              // disable device 
		WaitBusy();//�������ȷ��ǰ���������д��flash�ٽ�������Ĳ���
		amount=amount-(256-(Dst&0xFF));  //��ȥ��д��ĸ�������������Ҫд���ʣ�����
		Dst=(Dst+0x100)&0xFFFFFF00;      //��ַ������һ��ҳ����ʼ
		SST25VF0_CS_Low();					               // enable device 
		SpiReadWriteByte(SST25VF0_SPI, SST25VF0_PageProgramReg); 				         // send Byte Program command 
		SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFFFF) >> 16)));// send 3 address bytes 
		SpiReadWriteByte(SST25VF0_SPI,(((Dst & 0xFFFF) >> 8)));
		SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));
		for (i=0;i<amount;i++)
		{	
			SpiReadWriteByte(SST25VF0_SPI, (*pupper++));		       // send byte to be programmed 
		}
		SST25VF0_CS_High();						             // disable device 
	}
	else
	{
		for (i=0;i<amount;i++)
		{	
			SpiReadWriteByte(SST25VF0_SPI, (*pupper++));		        // send byte to be programmed 
		}
		SST25VF0_CS_High();						              // disable device 
	}
	//Wait Busy
	while ((ReadStatusRegister()& 0x01) == 0x01);// waste time until not busy 
}


 





//	SST25VF0_Init();
//	//ExternFlash_Init();
//	printf("flash id:%d\r\n",JedecIDRead());
//	ExternFlashChipErase();
//	ExternFlashPageProgram(0,"abcdef",6);
//	printf("addr0:%c\r\n",Read(0));
//	printf("addr1:%c\r\n",Read(1));
//	printf("addr2:%c\r\n",Read(2));
//	printf("addr3:%c\r\n",Read(3));
//	printf("addr4:%c\r\n",Read(4));
//	ExternFlashChipErase();
//	printf("addr0:%c\r\n",Read(0));
//	printf("addr1:%c\r\n",Read(1));
//	printf("addr2:%c\r\n",Read(2));
//	printf("addr3:%c\r\n",Read(3));
//	printf("addr4:%c\r\n",Read(4));


