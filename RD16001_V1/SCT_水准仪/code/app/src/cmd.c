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
#include <stdio.h>

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
  else if((*datstring == 0xfe) && (*(datstring+9) == 0xfe))
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
  return cmdflag;
}


//对命令进行处理,参数结构体都是提取成功后的
void cmdProc(struct CmdType cmdstructure)
{
  if(cmdstructure.cmd == 0x01)/*设置时间命令命令0*/
    {
        SetRtc(
        cmdstructure.para[0]*256+cmdstructure.para[0],
        cmdstructure.para[0],
        cmdstructure.para[0],
        0x01,
        cmdstructure.para[0],
        cmdstructure.para[0],
        cmdstructure.para[0]
         );
        printf("set time ok\r\n");
    }
  if(cmdstructure.cmd == 0x00)
    {/*命令1*/printf("cmd0\r\n");}
  if(cmdstructure.cmd == 0x02)
    {/*命令1*/printf("cmd2\r\n");}
  if(cmdstructure.cmd == 0x03)
    {/*命令1*/printf("cmd3\r\n");}
  if(cmdstructure.cmd == 0x04)
    {/*命令1*/printf("cmd4\r\n");}
  if(cmdstructure.cmd == 0x06)
    {/*命令1*/printf("cmd6\r\n");}
  if(cmdstructure.cmd == 0x05)
    {/*命令1*/printf("cmd5\r\n");}
}


void cmdTask(void)
{
  unsigned int retryTimes = 0;
  struct CmdType cmd;
  char cmdString[20] = {'\0'};

  //printf("cmd mode.\r\n");
  while(1)
  {
    if(retryTimes == 30)//30s等待命令时间
      { printf("wait cmd time over\r\n"); retryTimes = 0; break;}
    delay_ms(500);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 20))//假如接收到DTU回复的数据
        {
            LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//读取回复的数据
              if(  cmdExtract( cmdString, &cmd ) == 1 )//数据符合命令
              {
                retryTimes = 0;
                printf("cmd is ture.......\r\n");
                cmdProc(cmd);
                memset(cmdString,'\0',20);
              }
            memset(cmdString,'\0',20);
        }
  }
}

