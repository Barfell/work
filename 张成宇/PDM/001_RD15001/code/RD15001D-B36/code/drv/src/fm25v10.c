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
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI_SOURCE->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI_SOURCE->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI_SOURCE,ENABLE); //ʹ��SPI2 
} 

//SPI2 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
U8 CHL_SPI_ReadWriteByte(U8 TxData)
{
    INTX_DISABLE();
	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  

	SPI_I2S_SendData(SPI_SOURCE, TxData); //ͨ������SPIx����һ��byte  ����

	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ��byte  

    INTX_ENABLE();
	return SPI_I2S_ReceiveData(SPI_SOURCE); //����ͨ��SPIx������յ�����				    
}

VOID CHL_SPI_ReadWriteByteEx(U8 TxData, U8 *RxData)
{
    INTX_DISABLE();
	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  

	SPI_I2S_SendData(SPI_SOURCE, TxData); //ͨ������SPIx����һ��byte  ����

	while (SPI_I2S_GetFlagStatus(SPI_SOURCE, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ��byte  
    INTX_ENABLE();
	*RxData = SPI_I2S_ReceiveData(SPI_SOURCE); //����ͨ��SPIx������յ�����				    
}

//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ 						  
//SPI�ڳ�ʼ��
STATIC VOID CHL_SPI_Init(VOID)
{	 
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_SPI_CONFIG();

    GPIO_Set(SPI_GPIO, SPI_PIN, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_Set(SPI_CS_GPIO, SPI_CS_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    GPIO_SetBits(SPI_CS_GPIO, SPI_CS_PIN);
    
	GPIO_PINAF_CONGIG();

	//����ֻ���SPI�ڳ�ʼ��
	RCC_SPI_CONTROL();
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	//SPI1�õ���84M��ʱ�ӣ�2��ƵҲ����42M	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI_SOURCE, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���	
    
    SPI_Cmd(SPI_SOURCE, ENABLE); //ʹ��SPI����

    CHL_SPI_ReadWriteByte(0xff);//��������	
}  

//FM25V10дʹ��	
//��WEL��λ   
STATIC VOID FM25V10_Write_Enable(VOID)   
{
	FramCS_Low();                            //ʹ������   
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);      //����дʹ��  
	FramCS_High();                            //ȡ��Ƭѡ     	      
} 

//��ʼ��SPI FLASH��IO��
VOID FM25V10_Init(VOID)
{ 
    CHL_SPI_Init();
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOGʱ��

    GPIO_Set(FM25V10_HOLD_GPIO, FM25V10_HOLD_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    RELEASE_FM25V10();
    
    FramCS_High();			//SPI FLASH��ѡ��
    
}  
//��ȡFM25V10��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//WPEN  1   0   0   BP1 BP0 WEL 0
//WPEN: ���W�ܽ�ʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:1��ʾдʹ�ܣ�ͨ��WREN��WRDI�������û����
//Ĭ��:0x00
U8 FM25V10_ReadSR(VOID)   
{  
	u8 byte=0;   
	FramCS_Low();                            //ʹ������   
	CHL_SPI_ReadWriteByte(FM25V10_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=CHL_SPI_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	FramCS_High();                            //ȡ��Ƭѡ     
	return byte;   
} 

//дFM25V10״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
VOID FM25V10_Write_SR(U8 sr)   
{  
    FM25V10_Write_Enable();
	FramCS_Low();                            //ʹ������   
	CHL_SPI_ReadWriteByte(FM25V10_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	CHL_SPI_ReadWriteByte(sr);               //д��һ���ֽ�  
	FramCS_High();                           //ȡ��Ƭѡ     	      
}   

//��ȡоƬID
//����ֵ����:				     
U16 FM25V10_ReadID(VOID)
{
	u16 Temp = 0;
    FM25V10_Write_Enable();
	FramCS_Low();				    
	CHL_SPI_ReadWriteByte(FM25V10_ReadDeviceID);//���Ͷ�ȡID����	    
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
//����˯��ģʽ
VOID FM25V10_PowerDown(VOID)   
{ 
  	FramCS_Low();                            //ʹ������   
    CHL_SPI_ReadWriteByte(FM25V10_EnterSleepMode);        //����˯������
	FramCS_High();                            //ȡ��Ƭѡ     	      
}   
//����,�ڷ���sleep�������ȥsleep����������һ��Ƭѡ���½��ؽ���ظ�������Ϊ��֤������Ӧ�ٷ���һ��dummy�ֽڡ�
VOID FM25V10_WAKEUP(VOID)   
{  
  	FramCS_Low();                           //ʹ������   
    CHL_SPI_ReadWriteByte(0xff);                //  send FM25V10 a dummy code  
	FramCS_High();                           //ȡ��Ƭѡ     	      
    DelayUs_Sft(400);                               //�ȴ�
}   

VOID FramWriteByte(U32 address,U8 da)
{
    u8 temH,temM,temL;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);         //дʹ��
    FramCS_High(); 
    
   // DelayUs_Sft(2);

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteMemoryData);        //д����
    CHL_SPI_ReadWriteByte(temH);         //��λ��ַ
    CHL_SPI_ReadWriteByte(temM);         //��λ��ַ
    CHL_SPI_ReadWriteByte(temL);         //��λ��ַ
    CHL_SPI_ReadWriteByte(da);           //д������
    FramCS_High(); 
    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteDisable);         //д����
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
    CHL_SPI_ReadWriteByte(FM25V10_ReadData);      //������
    CHL_SPI_ReadWriteByte(temH);      //��λ��ַ
    CHL_SPI_ReadWriteByte(temM);      //��λ��ַ
    CHL_SPI_ReadWriteByte(temL);      //��λ��ַ
    temp = CHL_SPI_ReadWriteByte(0xF0);
    FramCS_High();            //ƬѡCS=1
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
    CHL_SPI_ReadWriteByte(FM25V10_WriteEnable);         //дʹ��
    FramCS_High(); 

    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteMemoryData);        //д����
    CHL_SPI_ReadWriteByte(temH);         //��λ��ַ
    CHL_SPI_ReadWriteByte(temM);         //��λ��ַ
    CHL_SPI_ReadWriteByte(temL);         //��λ��ַ
    //SPIx_ReadWriteByte(da);           //д������
    for(i=0;i<number;i++)
    {
        CHL_SPI_ReadWriteByte(*p++);
    }
    FramCS_High(); 
    FramCS_Low(); 
    CHL_SPI_ReadWriteByte(FM25V10_WriteDisable);         //д����
    FramCS_High(); 
}

VOID FramReadInduce(U32 address,U32 number,U8 *p)
{
    u8 temH,temM,temL;
    u32 i;
    temH=(u8)((address&0xff0000)>>16);
    temM=(u8)((address&0x00ff00)>>8);
    temL=(u8)(address&0x0000ff);

    FramCS_Low();           //ƬѡCS=0
    CHL_SPI_ReadWriteByte(FM25V10_ReadData);      //������
    CHL_SPI_ReadWriteByte(temH);      //��λ��ַ
    CHL_SPI_ReadWriteByte(temM);      //��λ��ַ
    CHL_SPI_ReadWriteByte(temL);      //��λ��ַ
    //temp = SPIx_ReadWriteByte(0xF0); //������
    for(i=0;i<number;i++)
    {
        *p++ = CHL_SPI_ReadWriteByte(0xF0);
    }
    FramCS_High();          //ƬѡCS=1
}










