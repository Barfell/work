#include "kernal.h"
#ifndef __DS18B20_H 
#define __DS18B20_H  
    
 
//IO �������� 



#define DS18B20_IO_IN()          	GPIO_Set(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz)
#define DS18B20_IO_OUT()         	GPIO_Set(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_PP,GPIO_Speed_50MHz)

#define DS18B20_DQ_OUT BIT_ADDR(GPIOB_ODR_Addr,9)  //���  ���ݶ˿� PA0  
#define DS18B20_DQ_IN GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
  
u8 DS18B20_Init(void);//��ʼ��DS18B20 
short DS18B20_Get_Temp(void);//��ȡ�¶� 
void DS18B20_Start(void);//��ʼ�¶�ת�� 
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ� 
u8 DS18B20_Read_Byte(void);//����һ���ֽ� 
u8 DS18B20_Read_Bit(void);//����һ��λ 
u8 DS18B20_Check(void);//����Ƿ���� DS18B20 
void DS18B20_Rst(void);//��λ DS18B20     
#endif 
