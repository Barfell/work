#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include "ramloop.h"
#include "key.h"
#include "cmd.h"
#include "dtu.h"
#include "cfg.h"
#include <stdio.h>


extern unsigned int IntervalTime;








extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;


//把原始数据提取出来，假如是命令则提取，不是则不提取  成功则返回1，不提取则返回0
/*
0xFE <0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX> <CMD> <0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX 0xXX> 0XFE>
HEAD <           DEVICE ID 8 BYTE            > <CMD> <            CMD'S PARA 8BYTE                 >
fe 53 43 54 31 35 30 30 32 0f 20 16 04 22 05 11 34 00 fe
*/
unsigned char cmdExtract(char *datstring, struct CmdType *cmdstructure)
{
  unsigned char cmdflag = 0;
  if( (*datstring == 0xfe) && (*(datstring+18) == 0xfe) )
    {
      //start   (0xfe)
      cmdstructure->start     = *(datstring);
      //device  (8byte) "SCT16002"
      cmdstructure->device[0] = *(datstring + 1);
      cmdstructure->device[1] = *(datstring + 2);
      cmdstructure->device[2] = *(datstring + 3);
      cmdstructure->device[3] = *(datstring + 4);
      cmdstructure->device[4] = *(datstring + 5);
      cmdstructure->device[5] = *(datstring + 6);
      cmdstructure->device[6] = *(datstring + 7);
      cmdstructure->device[7] = *(datstring + 8);
      //cmd     (1byte)
      cmdstructure->cmd       = *(datstring + 9);
      //        (8byte ch8 、rtc_para、8-485-id)
      cmdstructure->para[0]   = *(datstring + 10);//ch1
      cmdstructure->para[1]   = *(datstring + 11);//ch2
      cmdstructure->para[2]   = *(datstring + 12);//ch3
      cmdstructure->para[3]   = *(datstring + 13);//ch4
      cmdstructure->para[4]   = *(datstring + 14);//ch5
      cmdstructure->para[5]   = *(datstring + 15);//ch6
      cmdstructure->para[6]   = *(datstring + 16);//ch7
      cmdstructure->para[7]   = *(datstring + 17);//ch8
      //        (end)
      cmdstructure->end       = *(datstring + 18);
      //判断是否是发给本机的命令
      if(memcmp(cmdstructure->device, MACHINE_ID, 8) == 0)
      {
        cmdflag = 1;
      }
      else
      {
        memset(cmdstructure,0,sizeof(cmdstructure));
      }
    }
  return cmdflag;
}


//对命令进行处理,参数结构体都是提取成功后的
void cmdProc(struct CmdType cmdstructure)
{
  if(cmdstructure.cmd == 0x00)
    {/*擦除FLASH*/
        
    }
  if(cmdstructure.cmd == 0x01)
    {/*进入升级模式*/
      //printf("cmd0\r\n");
    }
  if(cmdstructure.cmd == 0x02)
    {/*退出升级模式*/
      //printf("cmd2\r\n");
    }
  if(cmdstructure.cmd == 0x03)
    {/*写标记指令*/
      //printf("cmd3\r\n");
    }
  if(cmdstructure.cmd == 0x04)
    {/*写应用地址命令*/
      //printf("cmd4\r\n");
    }
  if(cmdstructure.cmd == 0x05)
    {/*写硬件版本命令*/
      //printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x06)
    {/*写软件版本命令*/
     // printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x07)
    {/*重启命令*/
      //printf("cmd7\r\n");
    }
  if(cmdstructure.cmd == 0x08)
    {/*获取升级文件长度指令*/
      //printf("cmd8\r\n");
    }
  if(cmdstructure.cmd == 0x09)
    {/*清除标志*/
      //printf("cmd9\r\n");
    }
  if(cmdstructure.cmd == 0x0A)
    {/*数据拷贝成功后启动升级*/
      //printf("cmdA\r\n");
    }
  if(cmdstructure.cmd == 0x0B)
    {/*获取当前模式*/
      //printf("cmdB\r\n");
    }
  
  
  
  
  
  
  
  
  
  
  
  /*设置非协议模式*/
  if(cmdstructure.cmd == 0x0C)
    {
      FlashInit();
      FlashEreaseSector(PROTOCOL_TYPE_ADDR);
      FlashWriteByte(PROTOCOL_TYPE_ADDR,cmdstructure.para[0]);
      printf("protocol ok\r\n");
    }
  
  /*设置当前设备的ID*/
  if(cmdstructure.cmd == 0x0D)
    {
      printf("cmdD\r\n");
    }
  
  /*设置时间间隔*/
  if(cmdstructure.cmd == 0x0E)
    {
        FlashInit();
        FlashEreaseSector(NEXT_INTERVAL_TIME_ADDR);
        FlashWriteByte(NEXT_INTERVAL_TIME_ADDR,cmdstructure.para[0]);
        FlashWriteByte(NEXT_INTERVAL_TIME_ADDR+1,cmdstructure.para[1]);
      
        FlashInit();
        FlashEreaseSector(SET_INTERVAL_TIME_FLAG_ADDR);
        FlashWriteByte(SET_INTERVAL_TIME_FLAG_ADDR, 0X55);
        
        printf("interval ok\r\n");
    }
  
  /*设置时间*/
  if(cmdstructure.cmd == 0x0F)
    {
      SetRtc(
        cmdstructure.para[0]*256+cmdstructure.para[1],
        cmdstructure.para[2],
        cmdstructure.para[3],
        cmdstructure.para[4],
        cmdstructure.para[5],
        cmdstructure.para[6],
        cmdstructure.para[7]
         );
      printf("sync time ok\r\n");
    }
  
  /*设置通道类型*/
  if(cmdstructure.cmd == 0x10)
    {
          FlashInit();
          FlashEreaseSector(CHANNEL_TYPE_ADDR);
          FlashWriteAddr(CHANNEL_TYPE_ADDR,cmdstructure.para,8);
          printf("channel type ok\r\n");
    }
  
  /*设置设备连接方式*/
  if(cmdstructure.cmd == 0x11)
    {
      FlashInit();
      FlashEreaseSector(CONNECT_TYPE_ADDR);
      FlashWriteByte(CONNECT_TYPE_ADDR,cmdstructure.para[0]);//
      printf("connect type ok\r\n");
    }
  
  /*设置设备连接的485传感器的编号ID（485传感器）（8个数据）*/
  if(cmdstructure.cmd == 0x12)
    {
        FlashInit();
        FlashEreaseSector(SENSOR_ID_ADDR);
        FlashWriteAddr(SENSOR_ID_ADDR,cmdstructure.para,8);
        printf("sensor id ok\r\n");
    }
  
  /*设置8个子设备的设备ID编号（0-255）SCT16001....*/
  if(cmdstructure.cmd == 0x13)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_ID);
      FlashWriteAddr(SUB_DEVICE_ID,cmdstructure.para,8);
      printf("subdev id ok\r\n");
    }
  
  /*设置8个子设备的设备通道类型 VW 485 */
  if(cmdstructure.cmd == 0x14)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_TYPE_ADDR);
      FlashWriteAddr(SUB_DEVICE_TYPE_ADDR,cmdstructure.para,8);
      printf("subdev type ok\r\n");
    }
  
  /*设置8个子设备的设备连接的485传感器的ID*/
  if(cmdstructure.cmd == 0x15)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_SENSOR_ID_ADDR);
      FlashWriteAddr(SUB_DEVICE_SENSOR_ID_ADDR,cmdstructure.para,8);
      printf("subdev sensor id ok\r\n");
    }
}






/**************************************************
              命令解析任务
***************************************************
*/
void cmdTask(void)
{
  unsigned int retryTimes = 0;
  unsigned char cmdTimes = 0;
  struct CmdType cmd;
  char cmdString[200] = {'\0'};
  
  cmdTimes = *(unsigned char*)CMD_TIME_ADDR;
  while(1)
  {
    if(retryTimes == cmdTimes)//等待命令时间
      { retryTimes = 0; break;}
    delay_ms(1000);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick() - Uart0time) > 5))//接收到数据
      {
          retryTimes = 0;
          LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//读取回复的数据
          if(  cmdExtract( cmdString, &cmd ) == 1 )//数据符合命令
            {
              cmdProc(cmd);
              memset(cmdString,'\0',200);
            }
          else
            {
              //printf("cmd not correct!\r\n");
            }
          memset(cmdString,'\0',200);
      }
  }
}

/*
fe 53 43 54 31 36 30 31 32 0e 00 01 00 00 00 00 00 00 fe  时间间隔

fe 53 43 54 31 36 30 31 32 0f 20 16 05 17 02 11 05 10 fe  时间


fe 53 43 54 31 36 30 31 32 14 00 01 00 00 00 00 00 00 fe 子设备的连接的传感器类型

fe 53 43 54 31 36 30 31 32 15 00 0f 00 00 00 00 00 00 fe  子设备所连接的485传感器的ID


*/