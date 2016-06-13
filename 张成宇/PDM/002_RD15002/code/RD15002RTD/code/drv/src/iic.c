#include "iic.h"

#define RCC_IIC_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define IIC_GPIO			GPIOB
#define IIC_SDA_PIN			GPIO_Pin_9 
#define IIC_SCL_PIN			GPIO_Pin_8

//初始化IIC
VOID IIC_Init(VOID)
{					     	
	RCC_IIC_CONFIG();
	
	GPIO_Set(IIC_GPIO, IIC_SDA_PIN | IIC_SCL_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

	GPIO_SetBits(IIC_GPIO, IIC_SDA_PIN);
	GPIO_SetBits(IIC_GPIO, IIC_SCL_PIN);
}
//产生IIC起始信号
VOID IIC_Start(VOID)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	DelayUs_Sft(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	DelayUs_Sft(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
VOID IIC_Stop(VOID)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	DelayUs_Sft(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	DelayUs_Sft(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
U8 IIC_Wait_Ack(VOID)
{
	U8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
VOID IIC_Send_Byte(U8 txd)
{                        
    U8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
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
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
U8 IIC_Read_Byte(U8 ack)
{
	U8 i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}



























