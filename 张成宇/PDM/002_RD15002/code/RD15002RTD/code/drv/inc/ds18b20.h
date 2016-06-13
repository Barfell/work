#include "kernal.h"
#ifndef __DS18B20_H 
#define __DS18B20_H  
    
 
//IO 方向设置 



#define DS18B20_IO_IN()          	GPIO_Set(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz)
#define DS18B20_IO_OUT()         	GPIO_Set(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_PP,GPIO_Speed_50MHz)

#define DS18B20_DQ_OUT BIT_ADDR(GPIOB_ODR_Addr,9)  //输出  数据端口 PA0  
#define DS18B20_DQ_IN GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
  
u8 DS18B20_Init(void);//初始化DS18B20 
short DS18B20_Get_Temp(void);//获取温度 
void DS18B20_Start(void);//开始温度转换 
void DS18B20_Write_Byte(u8 dat);//写入一个字节 
u8 DS18B20_Read_Byte(void);//读出一个字节 
u8 DS18B20_Read_Bit(void);//读出一个位 
u8 DS18B20_Check(void);//检测是否存在 DS18B20 
void DS18B20_Rst(void);//复位 DS18B20     
#endif 
