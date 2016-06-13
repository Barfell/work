#include "SST25VF0.h" 

#define SST25VF0_SPI			SPI1

#define RCC_SPI_CONFIG()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE),RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)
#define SPI_GPIO				GPIOA
#define SPI_PIN					GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define GPIO_PINAF_CONGIG()		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1)
#define RCC_SPI_CONTROL()		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE)
#define SST25VF0_CS_GPIO		GPIOA
#define SST25VF0_CS_PIN			GPIO_Pin_4

#define SST25VF0_HOLD_GPIO	    GPIOC	
#define SST25VF0_HOLD_PIN		GPIO_Pin_4	

#define SST25VF0_MISO_GPIO	    GPIOA	
#define SST25VF0_MISO_PIN		GPIO_Pin_6	

#define SST25VF0_CS_Low()   GPIO_ResetBits(SST25VF0_CS_GPIO, SST25VF0_CS_PIN)
#define SST25VF0_CS_High()  GPIO_SetBits(SST25VF0_CS_GPIO, SST25VF0_CS_PIN)

#define SUSPEND_SST25VF0()	GPIO_ResetBits(SST25VF0_HOLD_GPIO,SST25VF0_HOLD_PIN);
#define RELEASE_SST25VF0()	GPIO_SetBits(SST25VF0_HOLD_GPIO,SST25VF0_HOLD_PIN);

U8 SpiReadWriteByte(SPI_TypeDef *pSPIx, U8 TxData)
{
//    INTX_DISABLE();
	while (SPI_I2S_GetFlagStatus(SST25VF0_SPI, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  

	SPI_I2S_SendData(SST25VF0_SPI, TxData); //通过外设SPIx发送一个byte  数据

	while (SPI_I2S_GetFlagStatus(SST25VF0_SPI, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  

//    INTX_ENABLE();
	return SPI_I2S_ReceiveData(SST25VF0_SPI); //返回通过SPIx最近接收的数据				    
}

//以下是SPI模块的初始化代码，配置成主机模式 						  
//SPI口初始化
STATIC VOID CHL_SPI_Init(VOID)
{	 

	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_SPI_CONFIG();

    GPIO_Set(SPI_GPIO, SPI_PIN, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_Set(SST25VF0_CS_GPIO, SST25VF0_CS_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_SetBits(SST25VF0_CS_GPIO, SST25VF0_CS_PIN);
    
	GPIO_PINAF_CONGIG();

	//这里只针对SPI口初始化
	RCC_SPI_CONTROL();
	
	SPI_Cmd(SST25VF0_SPI, DISABLE); //禁能SPI外设
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	//SPI1用的是84M的时钟，2分频也就是42M	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SST25VF0_SPI, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
    
    SPI_Cmd(SST25VF0_SPI, ENABLE); //使能SPI外设

    SpiReadWriteByte(SST25VF0_SPI, 0xff);//启动传输	


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

STATIC VOID WRDI(VOID)
{
	SST25VF0_CS_Low();  
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_WriteDisableReg);// enable writing to the status register 
	SST25VF0_CS_High();
}

STATIC VOID WaitBusy(VOID)
{
	U8 temp = 1;
	SST25VF0_CS_Low();
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadStatusReg);// send RDSR command 
	while (temp==1)
	{
		SpiReadWriteByte(SST25VF0_SPI, 0XFF);
		temp=GPIO_ReadInputDataBit(SST25VF0_MISO_GPIO,SST25VF0_MISO_PIN);//Get the Value of Busy bit in the status register
	}
	SST25VF0_CS_High();	
}

U8 ReadStatusRegister(VOID)
{
	U8 byte = 0;
	SST25VF0_CS_Low();				 // enable device 
	SpiReadWriteByte(SST25VF0_SPI, SST25VF0_ReadStatusReg);	 //send RDSR command 
	byte = SpiReadWriteByte(SST25VF0_SPI, 0xFF);//receive byte 
	SST25VF0_CS_High();			 //disable device 
	return byte;
}

//初始化SPI FLASH的IO口
VOID SST25VF0_Init(VOID)
{ 
    CHL_SPI_Init();
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOG时钟
    	
//	GPIO_Set(SST25VF0_CS_GPIO, SST25VF0_CS_PIN, GPIO_Mode_OUT, GPIO_Speed_50MHz,  GPIO_OType_PP, GPIO_PuPd_UP);
	GPIO_Set(SST25VF0_HOLD_GPIO, SST25VF0_HOLD_PIN, GPIO_Mode_OUT, GPIO_Speed_50MHz,  GPIO_OType_PP, GPIO_PuPd_UP);
	
//	SST25VF0_CS_Low();				 // enable device 
	
	RELEASE_SST25VF0();
        
//	SST25VF0_CS_High();			//SPI FLASH不选中
    
}  
/**********************************************
//函数名称:void ExternFlash_Init()
//功能描述:SST25VF064管脚，寄存器，SPI方式初始化
//输入参数:
//返回参数:
//说明:
***********************************************/
VOID ExternFlash_Init(VOID)
{	
	EHLD();    //默认上电的时候HOLD为复位引脚，这里配置RES/HOLD管脚的功能为HOLD
	EWSR();    //使能写寄存器
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
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));  //地址周期
	SpiReadWriteByte(SST25VF0_SPI,(Dst & 0xFF));  //dummy,空周期,随意数值
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
//函数名称:void ExternFlashBlockErase_64K(u32 Dst)
//功能描述:擦除64KB的块
//输入参数:
//返回参数:
//说明:
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
//函数名称:void ExternFlashBlockErase_32K(u32 Dst)
//功能描述:擦除32KB的块
//输入参数:
//返回参数:
//说明:
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
//函数名称:void ExternFlashSectorErase(u32 Dst)
//功能描述:4KB扇区擦除
//输入参数:
//返回参数:
//说明:
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
//函数名称:void ExternFlashChipErase()
//功能描述:整片擦除
//输入参数:
//返回参数:
//说明:
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
//函数名称:void ExternFlashHighSpeedRead(u32 Dst, u8 *psave,u32 no_bytes)
//功能描述:快速随机读取多字节数据
//输入参数:u32 Dst:地址, u8 *psave:存放地址,u32 no_bytes:读取字节数
//返回参数:
//说明:
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
//函数名称:void ExternFlashPageProgram(u32 Dst,u8 *pupper,u32 amount)
//功能描述:页编程
//输入参数:
//返回参数:
//说明:
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
	if(amount>(256-(Dst&0xFF)))        //写入的长度超出页边界结束地址
	{
		for (i=0;i<(256-(Dst&0xFF));i++)
		{	
			SpiReadWriteByte(SST25VF0_SPI, (*pupper++));		        // send byte to be programmed 
		}
		SST25VF0_CS_High();						              // disable device 
		WaitBusy();//这里必须确认前面的数据已写入flash再进行下面的操作
		amount=amount-(256-(Dst&0xFF));  //减去已写入的个数，等于下面要写入的剩余个数
		Dst=(Dst+0x100)&0xFFFFFF00;      //地址跳到下一个页的起始
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
//	while ((ReadStatusRegister()& 0x01) == 0x01);// waste time until not busy 
	WRDI();
	
}

void SST25ByteProgram(u32 addr,u8 byte)
{
    u8 ad[3];
    WREN(); 
    ad[0]=(u8)((addr&0xFFFFFF)>>16);
    ad[1]=(u8)((addr&0xFFFF)>>8);
    ad[2]=(u8)(addr&0xFF);
    SST25VF0_CS_Low();
    SpiReadWriteByte(SST25VF0_SPI,SST25VF0_ByteProgram);
    SpiReadWriteByte(SST25VF0_SPI,ad[0]);
    SpiReadWriteByte(SST25VF0_SPI,ad[1]);
    SpiReadWriteByte(SST25VF0_SPI,ad[2]);
    SpiReadWriteByte(SST25VF0_SPI,byte);
    SST25VF0_CS_High();
    WRDI();
//    while ((ReadStatusRegister()& 0x01) == 0x01);// waste time until not busy 
} 
 





