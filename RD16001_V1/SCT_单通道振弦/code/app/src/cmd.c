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


//��������д���,�����ṹ�嶼����ȡ�ɹ����
void cmdProc(struct CmdType cmdstructure)
{
  if(cmdstructure.cmd == 0x00)
    {/*����FLASH*/
        
    }
  if(cmdstructure.cmd == 0x01)
    {/*��������ģʽ*/
      printf("cmd0\r\n");
    }
  if(cmdstructure.cmd == 0x02)
    {/*�˳�����ģʽ*/
      printf("cmd2\r\n");
    }
  if(cmdstructure.cmd == 0x03)
    {/*д���ָ��*/
      printf("cmd3\r\n");
    }
  if(cmdstructure.cmd == 0x04)
    {/*дӦ�õ�ַ����*/
      printf("cmd4\r\n");
    }
  if(cmdstructure.cmd == 0x05)
    {/*дӲ���汾����*/
      printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x06)
    {/*д����汾����*/
      printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x07)
    {/*��������*/
      printf("cmd7\r\n");
    }
  if(cmdstructure.cmd == 0x08)
    {/*��ȡ�����ļ�����ָ��*/
      printf("cmd8\r\n");
    }
  if(cmdstructure.cmd == 0x09)
    {/*�����־*/
      printf("cmd9\r\n");
    }
  if(cmdstructure.cmd == 0x0A)
    {/*���ݿ����ɹ�����������*/
      printf("cmdA\r\n");
    }
  if(cmdstructure.cmd == 0x0B)
    {/*��ȡ��ǰģʽ*/
      printf("cmdB\r\n");
    }
  if(cmdstructure.cmd == 0x0C)
    {/*���÷�Э��ģʽ*/
      printf("cmdC\r\n");
      FlashInit();
      FlashEreaseSector(PROTOCOL_TYPE_ADDR);
      FlashWriteByte(PROTOCOL_TYPE_ADDR,cmdstructure.para[0]);  
    }
  if(cmdstructure.cmd == 0x0D)
    {/*����Э��ģʽ*/
      printf("cmdD\r\n");
    }
  if(cmdstructure.cmd == 0xF1)
    {/*����ʱ����*/
      printf("cmdF1\r\n");
      IntervalTime = cmdstructure.para[0];
      printf("set IntervalTime ok.   IntervalTime:%d\r\n",IntervalTime);
    }
  if(cmdstructure.cmd == 0xF2)
    {/*����ʱ��*/
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
    {/*����ͨ������*/
      printf("cmdF3\r\n");
      FlashInit();
      FlashEreaseSector(CHANNEL_TYPE_ADDR);
      FlashWriteAddr(CHANNEL_TYPE_ADDR,cmdstructure.para,8);
      printf("chanel info: ch1:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+0));
      printf("chanel info: ch2:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+1));
      printf("chanel info: ch3:%d\r\n",*(unsigned char*)(CHANNEL_TYPE_ADDR+2));
    }
  if(cmdstructure.cmd == 0xF4)
    {/*�豸���ӷ�ʽ*/
      printf("cmdF4\r\n");
      FlashInit();
      FlashEreaseSector(CONNECT_TYPE_ADDR);
      FlashWriteByte(CONNECT_TYPE_ADDR,cmdstructure.para[0]);
      printf("device connect type: %d\r\n",*(unsigned char*)(CONNECT_TYPE_ADDR+0));
    }
  if(cmdstructure.cmd == 0xF5)
    {/*����1*/printf("cmdF5\r\n");}
  if(cmdstructure.cmd == 0xF6)
    {/*����1*/printf("cmdF6\r\n");}
}






/**************************************************
              �����������
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
    if(retryTimes == 20)//30s�ȴ�����ʱ��
      { retryTimes = 0; break;}
    delay_ms(500);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 20))//������յ�DTU�ظ�������
        {
            LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//��ȡ�ظ�������
              if(  cmdExtract( cmdString, &cmd ) == 1 )//���ݷ�������
              {
                retryTimes = 0;
                cmdProc(cmd);
                memset(cmdString,'\0',20);
              }
            memset(cmdString,'\0',20);
        }
  }
}

