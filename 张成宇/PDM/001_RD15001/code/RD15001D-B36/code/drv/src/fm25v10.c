#include "FM25V10.h" 

#define FM25V10_HOLD_GPIO	    GPIOC	
#define FM25V10_HOLD_PIN		GPIO_Pin_4	 

#define SPI_SOURCE				SPI1
#define RCC_SPI_CONFIG()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE),RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)
#define SPI_GPIO				GPIOA
#define SPI_PIN					GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
#define GPIO_PINAF_CONGIG()		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1)
#define RCC_SPI_CONTROL()		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE)
#define SPI_CS_GPIO				GPIOA
#define SPI_CS_PIN				GPIO_Pin_4


#define FramCS_Low()   GPIO_ResetBits(SPI_CS_GPIO, SPI_CS_PIN)
#define FramCS_High()  GPIO_SetBits(SPI_CS_GPIO, SPI_CS_PIN)

//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
VOID CHL_SPI_SetSpeed(U8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI_SOURCE->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI_SOURCE->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPI_SOURCE,ENABLE); //使能SPI2 
} 

//SPI2 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
U8 CHL_SPI_ReadWriteByte(U8 TxData)
{
    INTX_DISABLE();
	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  

	SPI_I2S_SendData(SPI_SOURCE, TxData); //通过外设SPIx发送一个byte  数据

	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  

    INTX_ENABLE();
	return SPI_I2S_ReceiveData(SPI_SOURCE); //返回通过SPIx最近接收的数据				    
}

VOID CHL_SPI_ReadWriteByteEx(U8 TxData, U8 *RxData)
{
    INTX_DISABLE();
	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  

	SPI_I2S_SendData(SPI_SOURCE, TxData); //通过外设SPIx发送一个byte  数据

	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
    INTX_ENABLE();
	*RxData = SPI_I2S_ReceiveData(SPI_SOURCE); //返回通过SPIx最近接收的数据				    
}

//以下是SPI模块的初始化代码，配置成主机模式 						  
//SPI口初始化
STATIC VOID CHL_SPI_Init(VOID)
{	 
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_SPI_CONFIG();

    GPIO_Set(SPI_GPIO, SPI_PIN, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_Set(SPI_CS_GPIO, SPI_CS_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_SetBits(SPI_CS_GPIO, SPI_CS_PIN);
    
	GPIO_PINAF_CONGIG();

	//这里只针对SPI口初始化
	RCC_SPI_CONTROL();
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	//SPI1用的是84M的时钟，2分频也就是42M	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI_SOURCE, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器	
    
    SPI_Cmd(SPI_SOURCE, ENABLE); //使能SPI外设

    CHL_SPI_ReadWriteByte(0xff);//启动传输	
}  

//FM25V10写使能	
//将WEL置位   
STATIC VOID FM25V10_Write_Enable(VOID)   
{
	FramCS_Low();                            //使能器件   
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);      //发送写使能  
	FramCS_High();                            //取消片选     	      
} 

//初始化SPI FLASH的IO口
VOID FM25V10_Init(VOID)
{ 
    CHL_SPI_Init();
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOG时钟

    GPIO_Set(FM25V10_HOLD_GPIO, FM25V10_HOLD_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    RELEASE_FM25V10();
    
    FramCS_High();			//SPI FLASH不选中
    
}  
//读取FM25V10的状态寄存器
//BIT7  6   5   4   3   2   1   0
//WPEN  1   0   0   BP1 BP0 WEL 0
//WPEN: 配合W管脚使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:1表示写使能，通过WREN和WRDI命令设置或清除
//默认:0x00
U8 FM25V10_ReadSR(VOID)   
{  
	u8 byte=0;   
	FramCS_Low();                            //使能器件   
	CHL_SPI_ReadWriteByte(FM25V10_ReadStatusReg);    //发送读取状态寄存器命令    
	byte=CHL_SPI_ReadWriteByte(0Xff);             //读取一个字节  
	FramCS_High();                            //取消片选     
	return byte;   
} 

//写FM25V10状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
VOID FM25V10_Write_SR(U8 sr)   
{  
    FM25V10_Write_Enable();
	FramCS_Low();                            //使能器件   
	CHL_SPI_ReadWriteByte(FM25V10_WriteStatusReg);   //发送写取状态寄存器命令    
	CHL_SPI_ReadWriteByte(sr);               //写入一个字节  
	FramCS_High();                           //取消片选     	      
}   

//读取芯片ID
//返回值如下:				     
U16 FM25V10_ReadID(VOID)
{
	u16 Temp = 0;
    FM25V10_Write_Enable();
	FramCS_Low();				    
	CHL_SPI_ReadWriteByte(FM25V10_ReadDeviceID);//发送读取ID命令	    
	CHL_SPI_ReadWriteByte(0x00); 	    
	CHL_SPI_ReadWriteByte(0x00); 	    
	CHL_SPI_ReadWriteByte(0x00); 
    CHL_SPI_ReadWriteByte(0x00); 
    CHL_SPI_ReadWriteByte(0x00); 
    CHL_SPI_ReadWriteByte(0x00);
    CHL_SPI_ReadWriteByte(0x00);
	Temp|=CHL_SPI_ReadWriteByte(0xFF)<<8;  
	Temp|=CHL_SPI_ReadWriteByte(0xFF);	 
	FramCS_High();				    
	return Temp;
}   		    
//进入睡眠模式
VOID FM25V10_PowerDown(VOID)   
{ 
  	FramCS_Low();                            //使能器件   
    CHL_SPI_ReadWriteByte(FM25V10_EnterSleepMode);        //发送睡眠命令
	FramCS_High();                            //取消片选     	      
}   
//唤醒,在发送sleep命令后会进去sleep，但是在下一个片选的下降沿将会回复，但是为保证正常，应再发送一个dummy字节。
VOID FM25V10_WAKEUP(VOID)   
{  
  	FramCS_Low();                           //使能器件   
    CHL_SPI_ReadWriteByte(0xff);                //  send FM25V10 a dummy code  
	FramCS_High();                           //取消片选     	      
    DelayUs_Sft(400);                               //等待
}   

VOID FramWriteByte(U32 address,U8 da)
{
    u8 temH,temM,temL;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);         //写使能
    FramCS_High(); 
    
   // DelayUs_Sft(2);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteMemoryData);        //写命令
    CHL_SPI_ReadWriteByte(temH);         //高位地址
    CHL_SPI_ReadWriteByte(temM);         //中位地址
    CHL_SPI_ReadWriteByte(temL);         //低位地址
    CHL_SPI_ReadWriteByte(da);           //写入数据
    FramCS_High(); 
    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteDisable);         //写禁能
    FramCS_High(); 
}

U8 FramReadByte(U32 address)
{
    u8 temp;
    u8 temH,temM,temL;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_ReadData);      //读命令
    CHL_SPI_ReadWriteByte(temH);      //高位地址
    CHL_SPI_ReadWriteByte(temM);      //中位地址
    CHL_SPI_ReadWriteByte(temL);      //低位地址
    temp = CHL_SPI_ReadWriteByte(0xF0);
    FramCS_High();            //片选CS=1
    return temp;
}

VOID FramWriteInduce(U32 address,U32 number,U8 *p)
{
    u8 temH,temM,temL;
    u32 i;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);         //写使能
    FramCS_High(); 

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteMemoryData);        //写命令
    CHL_SPI_ReadWriteByte(temH);         //高位地址
    CHL_SPI_ReadWriteByte(temM);         //中位地址
    CHL_SPI_ReadWriteByte(temL);         //低位地址
    //SPIx_ReadWriteByte(da);           //写入数据
    for(i=0;i<number;i++)
    {
        CHL_SPI_ReadWriteByte(*p++);
    }
    FramCS_High(); 
    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteDisable);         //写禁能
    FramCS_High(); 
}

VOID FramReadInduce(U32 address,U32 number,U8 *p)
{
    u8 temH,temM,temL;
    u32 i;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low();           //片选CS=0
    CHL_SPI_ReadWriteByte(FM25V10_ReadData);      //读命令
    CHL_SPI_ReadWriteByte(temH);      //高位地址
    CHL_SPI_ReadWriteByte(temM);      //中位地址
    CHL_SPI_ReadWriteByte(temL);      //低位地址
    //temp = SPIx_ReadWriteByte(0xF0); //读数据
    for(i=0;i<number;i++)
    {
        *p++ = CHL_SPI_ReadWriteByte(0xF0);
    }
    FramCS_High();          //片选CS=1
}










