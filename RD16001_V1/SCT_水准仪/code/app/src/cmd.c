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

extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;

//��ԭʼ������ȡ��������������������ȡ����������ȡ  �ɹ��򷵻�1������ȡ�򷵻�0
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


//��������д���,�����ṹ�嶼����ȡ�ɹ����
void cmdProc(struct CmdType cmdstructure)
{
  if(cmdstructure.cmd == 0x01)/*����ʱ����������0*/
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
    {/*����1*/printf("cmd0\r\n");}
  if(cmdstructure.cmd == 0x02)
    {/*����1*/printf("cmd2\r\n");}
  if(cmdstructure.cmd == 0x03)
    {/*����1*/printf("cmd3\r\n");}
  if(cmdstructure.cmd == 0x04)
    {/*����1*/printf("cmd4\r\n");}
  if(cmdstructure.cmd == 0x06)
    {/*����1*/printf("cmd6\r\n");}
  if(cmdstructure.cmd == 0x05)
    {/*����1*/printf("cmd5\r\n");}
}


void cmdTask(void)
{
  unsigned int retryTimes = 0;
  struct CmdType cmd;
  char cmdString[20] = {'\0'};

  //printf("cmd mode.\r\n");
  while(1)
  {
    if(retryTimes == 30)//30s�ȴ�����ʱ��
      { printf("wait cmd time over\r\n"); retryTimes = 0; break;}
    delay_ms(500);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 20))//������յ�DTU�ظ�������
        {
            LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//��ȡ�ظ�������
              if(  cmdExtract( cmdString, &cmd ) == 1 )//���ݷ�������
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

