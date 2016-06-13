#include <msp430.h>
#include "test.h"
#include "cfg.h"
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
#include "level.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include "includes.h"




//$DTLOG,010001
//��ȡ��������ID
void GetSensor485ID(unsigned char ch, char *IDstring)
{
  char DeviceID[20]  = {'\0'};
  char temString[20]  = {'\0'};
  unsigned char ID   = 0;
  strcat(DeviceID,"$DTLOG,010");
  
  switch(ch)
  {
    case 1: ID = *(unsigned char*)(SENSOR_ID_ADDR+0);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 2: ID = *(unsigned char*)(SENSOR_ID_ADDR+1);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 3: ID = *(unsigned char*)(SENSOR_ID_ADDR+2);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 4: ID = *(unsigned char*)(SENSOR_ID_ADDR+3);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 5: ID = *(unsigned char*)(SENSOR_ID_ADDR+4);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 6: ID = *(unsigned char*)(SENSOR_ID_ADDR+5);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 7: ID = *(unsigned char*)(SENSOR_ID_ADDR+6);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 8: ID = *(unsigned char*)(SENSOR_ID_ADDR+7);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
  default:sprintf(temString, "000");break;
  }
  strcat(DeviceID,temString);
  strcat(DeviceID,"\r\n");
  strcat(IDstring,DeviceID);
}





void Task485(char *dat)
{
  char retData[300] ={'\0'};
  char retTemp[150] = {'\0'};
  char time485[50] = {'\0'};//��ȡ485���������ݵ�ʱ���
  unsigned char measure485Times = 0;//�������Դ���
  char value485[100] = {'\0'};//485�������Ĳ�������
  char cmd485[30] = {'\0'};//485������������
  float vol = 0.0;
  
  unsigned int wakeTime = 0;
  
  GetSensor485ID(SUB_NUM,cmd485);
  
  //printf("sensor id:%s\r\n",cmd485);
  
  
  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  
  while(1)
  {
    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,time485,MACHINE_ID,vol);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        
        wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
        sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
        strcat(retData,retTemp);
        memset(retTemp,0,150);

        sprintf(retTemp,"#%s-CH1:%s",MACHINE_ID,value485);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        
        
        memcpy(dat,retData,strlen(retData));
        memset(time485,'\0',50);
        memset(value485,'\0',100);
        delay_ms(3000);
        break;
      }
    else
     {
        measure485Times++;
        if(measure485Times == 2)
          {
            GetRtc(time485);
            sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,time485,MACHINE_ID,vol);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
            sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
            strcat(retData,retTemp);
            memset(retTemp,0,150);

            sprintf(retTemp,"#%s-CH1:%s",MACHINE_ID,value485);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            
            
            memcpy(dat,retData,strlen(retData));
            measure485Times = 0;
            memset(time485,'\0',50);
            memset(value485,'\0',100);
            break;
          }
        memset(time485,'\0',50);
        delay_ms(3000);
     }
  }
}


void FreqTask(char *dat)
{
  char retData[200] ={'\0'};
  char retTemp[150] = {'\0'};
  char timevw[50]= {'\0'};//��ȡVW���������ݵ�ʱ���
  unsigned char measureVWTime = 0;//���Խ��в����Ĵ���
  float measureFreq = 0.0;//VW�������
  float vol = 0.0;//��Դ��ѹ
  unsigned int wakeTime = 0;
  float VWtemp = 0.0;

  
  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  
  VWtemp = Get_VW_Voltage();//��ѹ
  VWtemp = 9950/VWtemp - 21290;//����
  VWtemp = GetNTCTemperature(VWtemp);//�¶�
  
  while(1)
  {
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
        GetRtc(timevw);
        sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,timevw,MACHINE_ID,vol);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        
        wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
        sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
        strcat(retData,retTemp);
        memset(retTemp,0,150);

        sprintf(retTemp,"#%s-CH1:F-%.2f T-%.2f",MACHINE_ID,measureFreq,VWtemp);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        memcpy(dat,retData,strlen(retData));
        break;
      }
    else
     {
        measureVWTime++;
        if(measureVWTime == 2)
          {
            GetRtc(timevw);
            sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,timevw,MACHINE_ID,vol);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            
            wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
            sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
            strcat(retData,retTemp);
            memset(retTemp,0,150);

            sprintf(retTemp,"#%s-CH1:F-%.2f T-%.2f",MACHINE_ID,measureFreq,VWtemp);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            memcpy(dat,retData,strlen(retData));
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        delay_ms(500);
     }
  }
}

//
//void Tilt(char *dat)
//{
//  char temp[250] ={'\0'};
//  char retData[150] ={'\0'};
//  unsigned char measure485Times = 3;//�������Դ���
//  char value485[100] = {'\0'};//485�������Ĳ�������
//  char AsciiValue[200] = {'\0'};
//  
//  char cmd1[] = {0x01,0x03,0x00,0x64,0x00,0x03,0x44,0x14};
//  char cmd2[] = {0x01,0x03,0x00,0x69,0x00,0x0D,0x54,0x13};
//  
//  unsigned char length = 0;
//  unsigned char length485 = 0;
//  
//  
//  float vol = 0.0;
//  char timevw[50]= {'\0'};
//  
//    //��ȡ��Դ��ѹ
//  SDInit();
//  delay_ms(1000);
//  vol = Get_INNER_Voltage();
//  SDOff();
//
//  GetRtc(timevw);
//  while(1)
//  {
//    if( GetTilt(cmd1,value485) == 1 )
//      {
//        sprintf(retData,"#%s-time:%s#%s-votagle:%.2fV#%s-CH1:", MACHINE_ID,timevw,MACHINE_ID,vol,MACHINE_ID);
//        length = strlen(retData);
//        
//        memcpy(temp,retData,length);
//        length485 = getDataLength(value485,100);//���ص����ݵĳ���
//        memcpy(temp+length,value485,length485);
//        
//        
//        
//        
//        memset(value485,'\0',100);
//        memset(retData,'\0',150);
//        break;
//      }
//    else
//     {
//        measure485Times--;
//        if(measure485Times == 0)
//          {
//            sprintf(retData,"#%s-time:%s#%s-votagle:%.2fV#%s-CH1:", MACHINE_ID,timevw,MACHINE_ID,vol,MACHINE_ID);
//            length = strlen(retData);
//            memcpy(temp,retData,strlen(retData));
//            memset(value485,'\0',100);
//            memset(retData,0,150);
//            measure485Times = 3;
//            break;
//          }
//     }
//  }
//  
//  length = length+length485;
//  
//  while(1)
//  {
//    if( GetTilt(cmd2,value485) == 1 )
//      {
//        length485 = getDataLength(value485,100);
//        
//        memcpy(temp+length,value485,length485);
//        length485 = 0;
//        length=0;
//        memset(value485,'\0',100);
//        break;
//      }
//    else
//     {
//       measure485Times--;
//        if(measure485Times == 0)
//          {
//            break;
//          }
//     }
//  }
//  
//  
//  length = getDataLength(temp,250);
//  memcpy(dat,temp,length);
//}


//
//void Tilt(char *dat)
//{
//  char temp[350] ={'\0'};
//  char retData[150] ={'\0'};
//  unsigned char measure485Times = 3;//�������Դ���
//  char value485[100] = {'\0'};//485�������Ĳ�������
//  char AsciiValue[200] = {'\0'};
//  
////  char cmd1[] = {0x01,0x03,0x00,0x64,0x00,0x03,0x44,0x14};
////  char cmd2[] = {0x01,0x03,0x00,0x69,0x00,0x0D,0x54,0x13};
//  char cmd1[] = {0x02,0x03,0x00,0x64,0x00,0x03,0x44,0x27};
//  char cmd2[] = {0x02,0x03,0x00,0x69,0x00,0x0D,0x54,0x20};
//  
//  unsigned char length = 0;
//  unsigned char length485 = 0;
//  
//  
//  float vol = 0.0;
//  char timevw[50]= {'\0'};
//  
//  signed long D1 =0;
//  signed long D2 =0;
//  signed long D3 =0;
//  signed long D4 =0;
//  
//    //��ȡ��Դ��ѹ
//  SDInit();
//  delay_ms(1000);
//  vol = Get_INNER_Voltage();
//  SDOff();
//
//  GetRtc(timevw);
//  while(1)
//  {
//    if( GetTilt(cmd1,value485) == 1 )
//      {
//        sprintf(retData,"#%s-time:%s#%s-votagle:%.2fV#%s-CH1:", MACHINE_ID,timevw,MACHINE_ID,vol,MACHINE_ID);
//        length = strlen(retData);
//        memcpy(temp,retData,length);
//        
//
//        HexBufToAsciiBuf(AsciiValue, value485+3, 4);
//        strcat(temp,"Tilt:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);  
//        HexBufToAsciiBuf(AsciiValue, value485+7, 2);
//        strcat(temp," Temp:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        
//        
//        
//        memset(value485,'\0',100);
//        memset(AsciiValue,'\0',200);
//        memset(retData,'\0',150);
//        break;
//      }
//    else
//     {
//        measure485Times--;
//        if(measure485Times == 0)
//          {
//            sprintf(retData,"#%s-time:%s#%s-votagle:%.2fV#%s-CH1:", MACHINE_ID,timevw,MACHINE_ID,vol,MACHINE_ID);
//            length = strlen(retData);
//            memcpy(temp,retData,strlen(retData));
//            memset(value485,'\0',100);
//            memset(retData,0,150);
//            measure485Times = 3;
//            break;
//          }
//     }
//  }
//  
// // length = length + (length485*2);
//  
//  while(1)
//  {
//    if( GetTilt(cmd2,value485) == 1 )
//      {
//        length485 = getDataLength(value485,100);
//        
//        
//        memset(AsciiValue,'\0',200);
//        AsciiValue[0] = value485[3];
//        AsciiValue[1] = value485[4];
//        AsciiValue[2] = value485[5];
//        AsciiValue[3] = value485[6];
//        AsciiValue[4] = value485[7];
//        AsciiValue[5] = value485[8];
//        AsciiValue[6] = value485[9];
//        AsciiValue[7] = value485[10];
//        strcat(temp," Tag:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        
//        
//        
//        HexBufToAsciiBuf(AsciiValue, value485+11, 4);
//        strcat(temp," a:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        HexBufToAsciiBuf(AsciiValue, value485+15, 4);
//        strcat(temp," b:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        HexBufToAsciiBuf(AsciiValue, value485+19, 4);
//        strcat(temp," c:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        HexBufToAsciiBuf(AsciiValue, value485+23, 4);
//        strcat(temp," d:");
//        strcat(temp,AsciiValue);
//        memset(AsciiValue,'\0',200);
//        
//        
//        
//        length485 = 0;
//        length=0;
//        memset(value485,'\0',100);
//        memset(AsciiValue,'\0',200);
//        break;
//      }
//    else
//     {
//       measure485Times--;
//        if(measure485Times == 0)
//          {
//            break;
//          }
//     }
//  }
//  
//  
// // length = getDataLength(temp,350);
//  memcpy(dat,temp,strlen(temp));
//  memset(temp,0,350);
//}





void Tilt(char *dat)
{
  char temp[350] ={'\0'};
  unsigned char measure485Times = 3;//�������Դ���
  
  char cmd1[] = {0x01,0x03,0x00,0x64,0x00,0x03,0x44,0x14};
  char cmd2[] = {0x01,0x03,0x00,0x69,0x00,0x0D,0x54,0x13};
  
  char cmd3[] = {0x02,0x03,0x00,0x64,0x00,0x03,0x44,0x27};
  char cmd4[] = {0x02,0x03,0x00,0x69,0x00,0x0D,0x54,0x20};
  
  
  
  float vol = 0.0;
  char timevw[50]= {'\0'};
  unsigned int wakeTime = 0;
  
  
  
  char measureString1[100];
  char measureString2[100];
  //����ֵ
  signed long int D1 =0;
  signed long int D2 =0;
  signed long int D3 =0;
  signed long int D4 =0;
  signed long int F =0;
  
  //����ʽϵ��
  float a1 =0.000344;
  float b1 =0.002471;
  float c1 =0.0;
  float d1 =0.0;
  
  float a2 =0.003094;
  float b2 =0.002472;
  float c2 =0.0;
  float d2 =0.0;
  
  char temp_x[4]={'\0'};
  
  
  //�Ƕ�
  float tiltX = 0.0;
  float tiltY = 0.0;

  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  GetRtc(timevw);
  
  
  
  
/*******************X��**************************/
  //measure
  while(1)
  {
    if( GetTilt(cmd1,measureString1) == 1 )
      {break;}
    else
     {
        measure485Times--;
        if(measure485Times == 0)
          {break;}
     }
  }
  measure485Times = 3;
  //tag
  while(1)
  {
    if( GetTilt(cmd2,measureString2) == 1 )
      {break;}
    else
     {
        measure485Times--;
        if(measure485Times == 0)
          { measure485Times = 3; break;}
     }
  }
  
  D1 = measureString1[3];
  D2 = measureString1[4];
  D3 = measureString1[5];
  D4 = measureString1[6];
  F  = D1<<24 | D2<<16 | D3<<8 | D4;
//  
//  memcpy(temp_x,measureString2+11,4);
//  a = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+15,4);
//  b = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+19,4);
//  c = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+23,4);
//  d = Hex_To_Decimal(temp_x);
  
  tiltX = a1 + b1*F;
  
  
  
  
  
  memset(measureString1,0,100);
  memset(measureString2,0,100);
/*******************Y��**************************/
  //measure
  while(1)
  {
    if( GetTilt(cmd3,measureString1) == 1 )
      {break;}
    else
     {
        measure485Times--;
        if(measure485Times == 0)
          {break;}
     }
  }
  measure485Times = 3;
  //tag
  while(1)
  {
    if( GetTilt(cmd4,measureString2) == 1 )
      {break;}
    else
     {
        measure485Times--;
        if(measure485Times == 0)
          { measure485Times = 3; break;}
     }
  }
  
  D1 = measureString1[3];
  D2 = measureString1[4];
  D3 = measureString1[5];
  D4 = measureString1[6];
  F  = D1<<24 | D2<<16 | D3<<8 | D4;
//  
//  memcpy(temp_x,measureString2+11,4);
//  a = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+15,4);
//  b = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+19,4);
//  c = Hex_To_Decimal(temp_x);
//  memcpy(temp_x,measureString2+23,4);
//  d = Hex_To_Decimal(temp_x);
  
  tiltY = a2 + b2*F;
  
  
  
  
/*******************Y��**************************/  
  wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
  sprintf(temp,"#%s-time:%s#%s-votagle:%.2f V#%s-interval:%d Min#%s-CH1: tiltX:%.3f  tiltY:%.3f", MACHINE_ID,timevw,MACHINE_ID,vol,MACHINE_ID,wakeTime,MACHINE_ID,tiltX,tiltY);
  memcpy(dat,temp,strlen(temp));
  memset(temp,0,350);
}




















/***************************************************************
                ��Ҫ������
****************************************************************
*/
void signel_Task(void)
{
  char UpLoadData[500] = {'\0'};//��Ҫ�ϴ�������
  char PROTOCOL_UpLoadData[600] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
  unsigned char detectTime = 0;//dtu����ʱ��
  
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  //Ĭ��ϵͳʱ��
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
  
  if( 0xAA != *(unsigned char *)DEVICE_FIRST_TIME_POWERON_ADDR)
  {
    /*�Ƿ��ǵ�һ�ο���*/
    FlashInit();
    FlashEreaseSector(DEVICE_FIRST_TIME_POWERON_ADDR);
    FlashWriteByte(DEVICE_FIRST_TIME_POWERON_ADDR,0xAA);
    
    /*�ɼ�ʱ����*/
    FlashInit();
    FlashEreaseSector(INTERVAL_TIME_ADDR);
    FlashWriteByte(INTERVAL_TIME_ADDR, (unsigned char)( INTERVAL_TIME/256 ) );//�߰�λ
    FlashWriteByte(INTERVAL_TIME_ADDR+1,(unsigned char)(INTERVAL_TIME % 256) ); //�Ͱ�λ
    
    /*cmd�ȴ�ʱ��*/
    FlashInit();
    FlashEreaseSector(CMD_TIME_ADDR);
    FlashWriteByte(CMD_TIME_ADDR, CMD_TIME );
    
    
    /*Ĭ�ϵ��豸��ͨ�����ͺ����ӷ�ʽ*/
    //Ĭ�ϵ����ӷ�ʽ0x00:RF  0x01:dtu
    FlashInit();
    FlashEreaseSector(CONNECT_TYPE_ADDR);
    FlashWriteByte(CONNECT_TYPE_ADDR,0x00);
    
    //Ĭ��ͨ�����ͣ�0X00:vw  0X01:485
    FlashInit();
    FlashEreaseSector(CHANNEL_TYPE_ADDR);
    FlashWriteByte(CHANNEL_TYPE_ADDR+0,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+1,0x02);
    FlashWriteByte(CHANNEL_TYPE_ADDR+2,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+3,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+4,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+5,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+6,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+7,0x00);
    
    //Ĭ��ͨ������485�������ı��
    FlashInit();
    FlashEreaseSector(SENSOR_ID_ADDR);
    FlashWriteByte(SENSOR_ID_ADDR+0,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+1,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+2,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+3,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+4,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+5,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+6,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+7,0x00);
    
    //Ĭ���ϴ��Ƿ��Э�� 0x00:unprotocol 0x01:protocol
    FlashInit();
    FlashEreaseSector(PROTOCOL_TYPE_ADDR);
    FlashWriteByte(PROTOCOL_TYPE_ADDR,0x00);  
    
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*������Դ*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_OFF;
  LED(1);
  delay_ms(2000);
  LED(0);

  while(1)
  {
      PWR_ON;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
/*--------------------- ��ʼ��ͨ��ģ�� -----------------------------------*/
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 1)//DTU
        {
          _EINT();
          DtuInit();
          while(1)
          {
            if(DtuStatu() == 1)//���Ϸ�����
              { break; }
            if(DtuStatu() == 0)//û�����Ϸ�����
              {
                delay_ms(1000);
                detectTime++;
                if(detectTime == 180)
                { 
                  detectTime = 0; 
                  goto DISCONNECT;
                }
              }
          }
        }
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 0)//RF
        {
          RFInit();
          delay_ms(1000);
        }
       

    //fe 53 43 54 31 36 30 30 33 0f 20 16 05 13 05 08 50 00 fe
/*-------------ͬ��ʱ����ߵȴ���������---------------------------------*/
      cmdTask();
      

      
      PWR_ON;
      COLL_PWR_ON;
      TRAN_PWR_OFF;
/*---------------- ���ݲɼ�-------CH0 ----------------------------------*/
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+SUB_NUM-1) == 0x01)//485
        {
          Init485();
          Task485(UpLoadData);
        }
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+SUB_NUM-1) == 0x00)//vw
        {
          FreqInit();
          FreqTask(UpLoadData);
        }
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+SUB_NUM-1) == 0x02)//485
        {
          Init485();
          Tilt(UpLoadData);
        }
      
      
      
      
      
      PWR_ON;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
      RFInit();
      delay_ms(1000);
/*---------------------------�ϴ�����-----------------------------------*/
      if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
        {
          packData(UpLoadData, getDataLength(UpLoadData,500), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,600));
          memset(UpLoadData ,'\0',500);
          memset(PROTOCOL_UpLoadData ,'\0',600);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
        {
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,500));
          memset( UpLoadData , '\0', 500 );
        }
      delay_ms(3000);
    TRAN_PWR_OFF;  
    
DISCONNECT:
      /*�̶�һ��ʱ���ϴ����ݣ�����һ���ж�һ���Ƿ��Ѿ������ϴ����ݵ�ʱ��*/
      LowperMeneagement();//�͹���
      delay_ms(500);
  }
}

