#ifndef __IIC_H
#define __IIC_H
#include "kernal.h"

   	   		   
//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO��������	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 

//IIC���в�������
VOID IIC_Init(VOID);                //��ʼ��IIC��IO��				 
VOID IIC_Start(VOID);				//����IIC��ʼ�ź�
VOID IIC_Stop(VOID);	  			//����IICֹͣ�ź�
VOID IIC_Send_Byte(U8 txd);			//IIC����һ���ֽ�
VOID IIC_Ack(VOID);					//IIC����ACK�ź�
VOID IIC_NAck(VOID);				//IIC������ACK�ź�
VOID IIC_Write_One_Byte(U8 daddr,U8 addr,U8 data);
U8 IIC_Read_One_Byte(U8 daddr,U8 addr);
U8 IIC_Read_Byte(U8 ack);			//IIC��ȡһ���ֽ�
U8 IIC_Wait_Ack(VOID); 				//IIC�ȴ�ACK�ź�
#endif
















