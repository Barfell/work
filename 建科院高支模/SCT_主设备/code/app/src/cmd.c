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








extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;


//��ԭʼ������ȡ��������������������ȡ����������ȡ  �ɹ��򷵻�1������ȡ�򷵻�0
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
      //        (8byte ch8 ��rtc_para��8-485-id)
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
      //�ж��Ƿ��Ƿ�������������
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


//��������д���,�����ṹ�嶼����ȡ�ɹ����
void cmdProc(struct CmdType cmdstructure)
{
  if(cmdstructure.cmd == 0x00)
    {/*����FLASH*/
        
    }
  if(cmdstructure.cmd == 0x01)
    {/*��������ģʽ*/
      //printf("cmd0\r\n");
    }
  if(cmdstructure.cmd == 0x02)
    {/*�˳�����ģʽ*/
      //printf("cmd2\r\n");
    }
  if(cmdstructure.cmd == 0x03)
    {/*д���ָ��*/
      //printf("cmd3\r\n");
    }
  if(cmdstructure.cmd == 0x04)
    {/*дӦ�õ�ַ����*/
      //printf("cmd4\r\n");
    }
  if(cmdstructure.cmd == 0x05)
    {/*дӲ���汾����*/
      //printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x06)
    {/*д����汾����*/
     // printf("cmd6\r\n");
    }
  if(cmdstructure.cmd == 0x07)
    {/*��������*/
      //printf("cmd7\r\n");
    }
  if(cmdstructure.cmd == 0x08)
    {/*��ȡ�����ļ�����ָ��*/
      //printf("cmd8\r\n");
    }
  if(cmdstructure.cmd == 0x09)
    {/*�����־*/
      //printf("cmd9\r\n");
    }
  if(cmdstructure.cmd == 0x0A)
    {/*���ݿ����ɹ�����������*/
      //printf("cmdA\r\n");
    }
  if(cmdstructure.cmd == 0x0B)
    {/*��ȡ��ǰģʽ*/
      //printf("cmdB\r\n");
    }
  
  
  
  
  
  
  
  
  
  
  
  /*���÷�Э��ģʽ*/
  if(cmdstructure.cmd == 0x0C)
    {
      FlashInit();
      FlashEreaseSector(PROTOCOL_TYPE_ADDR);
      FlashWriteByte(PROTOCOL_TYPE_ADDR,cmdstructure.para[0]);
      printf("protocol ok\r\n");
    }
  
  /*���õ�ǰ�豸��ID*/
  if(cmdstructure.cmd == 0x0D)
    {
      printf("cmdD\r\n");
    }
  
  /*����ʱ����*/
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
  
  /*����ʱ��*/
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
  
  /*����ͨ������*/
  if(cmdstructure.cmd == 0x10)
    {
          FlashInit();
          FlashEreaseSector(CHANNEL_TYPE_ADDR);
          FlashWriteAddr(CHANNEL_TYPE_ADDR,cmdstructure.para,8);
          printf("channel type ok\r\n");
    }
  
  /*�����豸���ӷ�ʽ*/
  if(cmdstructure.cmd == 0x11)
    {
      FlashInit();
      FlashEreaseSector(CONNECT_TYPE_ADDR);
      FlashWriteByte(CONNECT_TYPE_ADDR,cmdstructure.para[0]);//
      printf("connect type ok\r\n");
    }
  
  /*�����豸���ӵ�485�������ı��ID��485����������8�����ݣ�*/
  if(cmdstructure.cmd == 0x12)
    {
        FlashInit();
        FlashEreaseSector(SENSOR_ID_ADDR);
        FlashWriteAddr(SENSOR_ID_ADDR,cmdstructure.para,8);
        printf("sensor id ok\r\n");
    }
  
  /*����8�����豸���豸ID��ţ�0-255��SCT16001....*/
  if(cmdstructure.cmd == 0x13)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_ID);
      FlashWriteAddr(SUB_DEVICE_ID,cmdstructure.para,8);
      printf("subdev id ok\r\n");
    }
  
  /*����8�����豸���豸ͨ������ VW 485 */
  if(cmdstructure.cmd == 0x14)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_TYPE_ADDR);
      FlashWriteAddr(SUB_DEVICE_TYPE_ADDR,cmdstructure.para,8);
      printf("subdev type ok\r\n");
    }
  
  /*����8�����豸���豸���ӵ�485��������ID*/
  if(cmdstructure.cmd == 0x15)
    {
      FlashInit();
      FlashEreaseSector(SUB_DEVICE_SENSOR_ID_ADDR);
      FlashWriteAddr(SUB_DEVICE_SENSOR_ID_ADDR,cmdstructure.para,8);
      printf("subdev sensor id ok\r\n");
    }
}






/**************************************************
              �����������
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
    if(retryTimes == cmdTimes)//�ȴ�����ʱ��
      { retryTimes = 0; break;}
    delay_ms(1000);
    retryTimes++;
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick() - Uart0time) > 5))//���յ�����
      {
          retryTimes = 0;
          LoopRAMReadLength(&Uart0loop, cmdString, Uart0loop.LoopDatLength);//��ȡ�ظ�������
          if(  cmdExtract( cmdString, &cmd ) == 1 )//���ݷ�������
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
fe 53 43 54 31 36 30 31 32 0e 00 01 00 00 00 00 00 00 fe  ʱ����

fe 53 43 54 31 36 30 31 32 0f 20 16 05 17 02 11 05 10 fe  ʱ��


fe 53 43 54 31 36 30 31 32 14 00 01 00 00 00 00 00 00 fe ���豸�����ӵĴ���������

fe 53 43 54 31 36 30 31 32 15 00 0f 00 00 00 00 00 00 fe  ���豸�����ӵ�485��������ID


*/