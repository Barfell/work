#include "iic.h"

#define RCC_IIC_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define IIC_GPIO			GPIOB
#define IIC_SDA_PIN			GPIO_Pin_9 
#define IIC_SCL_PIN			GPIO_Pin_8

//��ʼ��IIC
VOID IIC_Init(VOID)
{					     	
	RCC_IIC_CONFIG();
	
	GPIO_Set(IIC_GPIO, IIC_SDA_PIN | IIC_SCL_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

	GPIO_SetBits(IIC_GPIO, IIC_SDA_PIN);
	GPIO_SetBits(IIC_GPIO, IIC_SCL_PIN);
}
//����IIC��ʼ�ź�
VOID IIC_Start(VOID)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	DelayUs_Sft(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	DelayUs_Sft(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
VOID IIC_Stop(VOID)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	DelayUs_Sft(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	DelayUs_Sft(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
U8 IIC_Wait_Ack(VOID)
{
	U8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;DelayUs_Sft(1);	   
	IIC_SCL=1;DelayUs_Sft(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
VOID IIC_Ack(VOID)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	DelayUs_Sft(2);
	IIC_SCL=1;
	DelayUs_Sft(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
VOID IIC_NAck(VOID)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	DelayUs_Sft(2);
	IIC_SCL=1;
	DelayUs_Sft(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
VOID IIC_Send_Byte(U8 txd)
{                        
    U8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		DelayUs_Sft(2);   
		IIC_SCL=1;
		DelayUs_Sft(2); 
		IIC_SCL=0;	
		DelayUs_Sft(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
U8 IIC_Read_Byte(U8 ack)
{
	U8 i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        DelayUs_Sft(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		DelayUs_Sft(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



























