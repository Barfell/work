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


extern unsigned char IntervalTime;

extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;


//把原始数据提取出来，假如是命令则提取，不是则不提取  成功则返回1，不提取则返回0
unsigned char cmdExtract(char *datstring, struct CmdType *cmdstructure)
{
  unsigned char cmdflag = 0;
  if( (*datstring == 0xfe) && (*(datstring+6) == 0xfe))
    {
      cmdstructure->start   = *(datstring);
      cmdstructure->cmd     = *(datstring + 1);
      cmdstructure->para[0] = *(datstring + 2);
      cmdstructure->para[1] = *(datstring + 3);
      cmdstructure->para[2] = *(datstring + 4);
      cmdstructure->para[3] = *(datstring + 5);
      cmdstructure->end     = *(datstring + 6);
      cmdflag = 1;
    }
  else if((*datstring == 0xfe) && (*(datstring+1) == 0xf2) && (*(datstring+9) == 0xfe) )
    {
      cmdstructure->start   = *(datstring);
      cmdstructure->cmd     = *(datstring + 1);
      cmdstructure->para[0] = *(datstring + 2);//year
      cmdstructure->para[1] = *(datstring + 3);//year
      cmdstructure->para[2] = *(datstring + 4);//month
      cmdstructure->para[3] = *(datstring + 5);//day
      cmdstructure->para[4] = *(datstring + 6);//hour
      cmdstructure->para[5] = *(datstring + 7);//min
      cmdstructure->para[6] = *(datstring + 8);//sec
      cmdstructure->end     = *(datstring + 9);
      cmdflag = 1;
    }
  else if((*datstring == 0xfe) && (*(datstring+1) == 0xf3) && (*(datstring+10) == 0xfe) )
    {
      cmdstructure->start   = *(datstring);
      cmdstructure->cmd     = *(datstring + 1);
      cmdstructure->para[0] = *(datstring + 2);//ch1
      cmdstructure->para[1] = *(datstring + 3);//ch2
      cmdstructure->para[2] = *(datstring + 4);//ch3
      cmdstructure->para[3] = *(datstring + 5);//ch4
      cmdstructure->para[4] = *(datstring + 6);//ch5
      cmdstructure->para[5] = *(datstring + 7);//ch6
      cmdstructure->para[6] = *(datstring + 8);//ch7
      cmdstructure->para[6] = *(datstring + 9);//ch8
      cmdstructure->end     = *(datstring + 10);
      cmdflag = 1;
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
      printf("cmd0\r\n");
    }
  if(cmdstructure.cmd == 0x02)
    {/*退出升级模式*/
      printf("cmd2\r\n");
    }
  if(cmdstructure.cmd == 0x03)
    {/*写标记指令*/
      printf("cmd3\r\n");
    }
  if(cmdstructure.cmd == 0x04)
    {/*写应用地址命令*/
      printf("cmd4\r\n");
    }
  if(cmdstructure.cmd == 0x05)
    {/*写硬件版本命令*/
      printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x06)
    {/*写软件版本命令*/
      printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x07)
    {/*重启命令*/
      printf("cmd7\r\n");
    }
  if(cmdstructure.cmd == 0x08)
    {/*获取升级文件长度指令*/
      printf("cmd8\r\n");
    }
  if(cmdstructure.cmd == 0x09)
    {/*清除标志*/
      printf("cmd9\r\n");
    }
  if(cmdstructure.cmd == 0x0A)
    {/*数据拷贝成功后启动升级*/
      printf("cmdA\r\n");
    }
  if(cmdstructure.cmd == 0x0B)
    {/*获取当前模式*/
      printf("cmdB\r\n");
    }
  if(cmdstructure.cmd == 0x0C)
    {/*设置非协议模式*/
      printf("cmdC\r\n");
      FlashInit();
      FlashEreaseSector(PROTOCOL_TYPE_ADDR);
      FlashWriteByte(PROTOCOL_TYPE_ADDR,cmdstructure.para[0]);  
    }
  if(cmdstructure.cmd == 0x0D)
    {/*设置协议模式*/
      printf("cmdD\r\n");
    }
  if(cmdstructure.cmd == 0xF1)
    {/*设置时间间隔*/
      printf("cmdF1\r\n");
      IntervalTime = cmdstructure.para[0];
      printf("set IntervalTime ok.   IntervalTime:%d\r\n",IntervalTime);
    }
  if(cmdstructure.cmd == 0xF2)
    {/*设置时间*/
      printf("cmdF2\r\n");
      SetRtc(
        cmdstructure.para[0]*256+cmdstructure.para[1],
        cmdstructure.para[2],
        cmdstructure.para[3],
        0x01,
        cmdstructure.para[4],
        cmdstructure.para[5],
        cmdstructure.para[6]
         );
      printf("set time ok\r\n");
    }
  if(cmdstructure.cmd == 0xF3)
    {/*设置通道类型*/
      printf("cmdF3\r\n");
      FlashInit();
      FlashEreaseSector(CHANNEL_TYPE_ADDR);
      FlashWriteAddr(CHANNEL_TYPE_ADDR,cmdstructure.para,8);
      printf("chanel info: ch1:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+0));
      printf("chanel info: ch2:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+1));
      printf("chanel info: ch3:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+2));
    }
  if(cmdstructure.cmd == 0xF4)
    {/*设备连接方式*/
      printf("cmdF4\r\n");
      FlashInit();
      FlashEreaseSector(CONNECT_TYPE_ADDR);
      FlashWriteByte(CONNECT_TYPE_ADDR,cmdstructure.para[0]);
      printf("device connect type: %d\r\n",*(unsigned char*)(CONNECT_TYPE_ADDR+0));
    }
  if(cmdstructure.cmd == 0xF5)
    {/*命令1*/printf("cmdF5\r\n");}
  if(cmdstructure.cmd == 0xF6)
    {/*命令1*/printf("cmdF6\r\n");}
}






/**************************************************
              命令解析任务
***************************************************
*/
void cmdTask(void)
{
  unsigned int retryTimes = 0;
  struct CmdType cmd;
  char cmdString[20] = {'\0'};

  printf("cmd mode.\r\n");
  while(1)
  {
    if(retryTimes == 20)//30s等待命令时间
      { retryTimes = 0; break;}
    delay_ms(500);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 20))//假如接收到DTU回复的数据
        {
            LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//读取回复的数据
              if(  cmdExtract( cmdString, &cmd ) == 1 )//数据符合命令
              {
                retryTimes = 0;
                cmdProc(cmd);
                memset(cmdString,'\0',20);
              }
            memset(cmdString,'\0',20);
        }
  }
}

