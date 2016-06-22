/**************************************************
*
*对数据进行打包的功能
*
***************************************************
*/

#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "freq.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include "s485.h"
#include "cmd.h"
#include "ecc.h"
#include "ramloop.h"
#include "key.h"
#include "dtu.h"
#include <stdio.h>




#define START_SYMBOL		0XFE
#define PROTOCOL_EDITION	0X01
#define DATA_DIRECTION		0X01
#define	MAINCMD_INTERNET 	0X06		
#define	SUBCMD_SENSOR	 	0X0001		
#define	FIRST_END_SYMBOL	0X0D
#define	SECOND_END_SYMBOL	0X0A

enum
{
	NENCRYPTION_NCOMPRESSION = 0X00,
	ENCRYPTION_NCOMPRESSION,
	NENCRYPTION_COMPRESSION,
	ENCRYPTION_COMPRESSION,
	
};

//自己编写的获取数组内容（字符串、数值数据）的长度函数
//参数：数组、数组的大小
//返回：内容长度
unsigned int getDataLength(char *dat, unsigned int arryLength)
{
  unsigned int length;
  unsigned int i=0;
  while( *(dat+arryLength-1 - i) == '\0' && (i <= arryLength-1))
  {
    i++;
  }
  length = arryLength-i;
  return length;
}

//将数据打包
//参数：打包的数据，数据长度，打包后的数据
void packData(char *data, unsigned int datalength, char *packeddata)
{
  char dataTopack[400] = {'\0'};
  unsigned int i,strLength;
  char dataCrc = *data;
  
  //附加信息
  /**************************************************/
  dataTopack[0] = START_SYMBOL;		//FE
  dataTopack[1] = PROTOCOL_EDITION;	//01
  dataTopack[2] = (char)0x00;//整个数据包长度（信息头、数据包总数、当前包号、数据、校验、终止符）		
  dataTopack[3] = (char)0x00;		
  dataTopack[4] = (char)datalength+25>>8;		
  dataTopack[5] = (char)datalength+25;
  /**************************************************/
  dataTopack[6]  = DATA_DIRECTION;//传输方向：0x01 上行 0x10下行					
  dataTopack[7]  = MAINCMD_INTERNET;//internet数据交互				
  dataTopack[8]  = (char)SUBCMD_SENSOR>>8;//子命令			
  dataTopack[9]  = (char)SUBCMD_SENSOR;			
  dataTopack[10] = NENCRYPTION_NCOMPRESSION;//命令索引(0x00\0x01\0x02\0x03)(是否加密是否压缩)		
  /**************************************************/
  dataTopack[11] = 0;//数据包总数
  dataTopack[12] = 0;
  dataTopack[13] = 0;
  dataTopack[14] = 1;
  /**************************************************/
  dataTopack[15] = 0;//当前包序号
  dataTopack[16] = 0;
  dataTopack[17] = 0;
  dataTopack[18] = 1;

  
  //提出数据
  /**************************************************/
  for(i=0;i<datalength;i++)
  {
    *( (dataTopack+19) + i ) =  *( data + i );
  }
  
  
  
  strLength = datalength+19;
  //校验 4个字节(异或)   除了终止符和校验值，都进行异或操作
  /**************************************************/
  for(i=1;i<=strLength;i++)
    {
      dataCrc ^= dataTopack[i];
    }
  dataTopack[strLength+0] = 0;
  dataTopack[strLength+1] = 0;
  dataTopack[strLength+2] = 0;
  dataTopack[strLength+3] = dataCrc;
  strLength = strLength+4;
  //终止符 2个字节
  /**************************************************/
  dataTopack[strLength+0] = FIRST_END_SYMBOL;
  dataTopack[strLength+1] = SECOND_END_SYMBOL;
  strLength+=2;

  memcpy(packeddata,dataTopack,strLength);
}

