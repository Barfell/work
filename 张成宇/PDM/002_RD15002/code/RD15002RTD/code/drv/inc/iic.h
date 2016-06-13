#ifndef __IIC_H
#define __IIC_H
#include "kernal.h"

   	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO操作函数	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //输入SDA 

//IIC所有操作函数
VOID IIC_Init(VOID);                //初始化IIC的IO口				 
VOID IIC_Start(VOID);				//发送IIC开始信号
VOID IIC_Stop(VOID);	  			//发送IIC停止信号
VOID IIC_Send_Byte(U8 txd);			//IIC发送一个字节
VOID IIC_Ack(VOID);					//IIC发送ACK信号
VOID IIC_NAck(VOID);				//IIC不发送ACK信号
VOID IIC_Write_One_Byte(U8 daddr,U8 addr,U8 data);
U8 IIC_Read_One_Byte(U8 daddr,U8 addr);
U8 IIC_Read_Byte(U8 ack);			//IIC读取一个字节
U8 IIC_Wait_Ack(VOID); 				//IIC等待ACK信号
#endif
















