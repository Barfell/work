/********************************************************************************
APP�˴�������
//����Ҫ��IAR ����������.XCL�ļ������޸ģ���FLASH���з��䣬����ο�������MSP430��Ƭ���Ķ���������
1.�û�APP�����������
2.Ӳ�����ܵ�������FLASH�����BOOT���ж������������򿽱��������ж�������ַ��
3.���ÿ��Ź���Ӳ����λ����msp430ÿ�θ�λ�����Ȱ�PCָ�������ж��������RESETλ�ã�����λ�ÿ��Կ������������ֲᣩ


BOOT�˵Ĵ�������
1.���뵽BOOT�ĵ�һ��������Ǳ��������ж�������BOOT���ж�������������
	���ܽ��뵽BOOT˵���ǵ�һ��Ӳ�����У�������APP�˽��յ������������ת��BOOT����������£����ǵ�һ��Ӳ�����еĻ�����λ������APP�У�
2.����APP��flash���򣬵ȴ��������ݰ���
3.���������ݰ�������ϣ�д�뵽APP Flash��ɣ���
4.������Ϻ󣬽�APP ���ж�����������������ݿ����������ж�������ַ��׼��APP���л�����
5.���ÿ��Ź���Ӳ����λ��
********************************************************************************
*/
#include "kernel.h"             //��������˰��ӵĸ�������,�Լ�һЩϵͳ��С������������ʱCRCУ���....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_flash.h"
/*_----------------��������---------------------*/
#include "Power.h"
/*_----------------���ܺ���---------------------*/
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include "Boot.h"
#include "msp430f149_wdt.h"

void BootProc(void)
{
  printf("bootloader init done.\r\n");
  printf("begin to save Vector in BOOT area.\r\n");
  FeedWatchDog();
  Vector_HARD2BOOT();//����BOOT��������
  printf("begin to wipe APP area.\r\n");
  FeedWatchDog();
  EarseAppFlash();//����App��FLASH��׼��д���µ�app�̼�
  printf("wipe Flash done.\r\nready to download the fireware.(�밴���Ͱ���)\r\n");
  while(1)
  {
    delay_ms(10);
    FeedWatchDog();
  }
}

//asciiתHEX
unsigned char AsciiToHex(unsigned char cNum)
{
	if(cNum>='0'&&cNum<='9')
	{
		cNum -= '0';
	}
	else if(cNum>='A'&&cNum<='F')
	{
		cNum -= 'A';
		cNum += 10;
	}
	return cNum;
}

/***********************���¶��ж����������************************************/
//��APP������������������������
void Vector_APP2HARD(void)
{
  unsigned int i;
  FlashEreaseSector(HARDWARE_VECTOR_BUTTOM);
  delay_ms(20);
  FCTL1 = FWKEY + WRT;
  for(i=0;i<32;i++)
  {
    *(char *)(HARDWARE_VECTOR_BUTTOM + i) = *(char*)(APP_VECTOR_BUTTOM + i);
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK; 
}

//����BOOT������
void Vector_HARD2BOOT(void)
{
  unsigned int i;
  FlashEreaseSector(BOOT_VECTOR_BUTTOM);
  FeedWatchDog();
  delay_ms(20);
  FCTL1 = FWKEY + WRT;
  for(i=0;i<32;i++)
  {
    *(char*)(BOOT_VECTOR_BUTTOM + i) = *(char *)(HARDWARE_VECTOR_BUTTOM + i);
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK; 
}
  
  
  
//��ת֮ǰ�Ȱ�APP���ж�����������������ж���������
void GoToApp(void)
{
  printf("Copy App vector to VECTOR area.\r\n");
  Vector_APP2HARD();            //��app��������ŵ������ж���������
  printf("Copy Done, jump to app ....\r\n");
  WDTCTL = 0x0000;
}

//����App�洢���������
void EarseAppFlash(void)
{
  unsigned int j;
  for(j=0; j<(APP_ADDR_TOP - APP_ADDR_BUTTOM); j+=0xff )
  {
    FlashEreaseSector(APP_ADDR_BUTTOM + j+1);
    delay_ms(20);
    FeedWatchDog();
  }
}





unsigned int  AddrToWrite_HEX = 0;//@����ĵ�ַ��HEX���͵ģ�
unsigned char UpdateData_HEX = 0;//�������ݣ�HEX���͵ģ�

unsigned char AddrToWrite[4];//@����ĵ�ַ�����黺�����͵ģ�
unsigned char UpdateData[2];//�������ݣ����黺�����͵ģ�
unsigned char Addr_i = 0;//���ڽ�����ַʱ��
unsigned char Data_i = 0;//���ڽ�����������ʱ��
unsigned char Flag_AT = 0;//�Ƿ���� ��@��
unsigned int WritePosition = 0;//дflashʱ���ƫ�Ʊ���



//�����Լ�����
/************************TXT�̼���ʽ***********************
@5000
44 54 00 52 44 31 35 30 30 31 00 55 61 72 74 20
72 65 63 69 76 65 64 20 64 61 74 61 3A 25 73 00
25 73 0D 0A 00 25 73 20 69 73 20 6E 6F 74 20 61
@51AA
01 
@51AC
31 40 00 0A 3C 40 02 02 3D 40 B8 00 B0 12 A2 70
3C 40 00 02 3D 40 AA 51 3E 40 01 00 B0 12 BE 71
B0 12 16 6D B0 12 C2 71 0A 12 0B 12 08 12 09 12
06 12 07 12 0C 12 30 40 C6 71 30 40 CA 71 FF 3F
@DFE2
DA 6E 
@DFE6
74 71 F8 6E 9C 67 A0 6F E6 6B 
@DFF2
A4 6D 
@DFFE
AC 51 
q

***********************************************************
*/
#pragma vector = UART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  u8 u8data = 0;
  FeedWatchDog();
  u8data = U0RXBUF;
  
  //������@�󣬺�����λ���ǵ�ַλ
  if(Flag_AT == 1)
  {
    AddrToWrite[Addr_i] = u8data;
    Addr_i++;
    if(Addr_i == 4)//�Ѿ��������ĸ��ַ�
    {
      Addr_i = 0;
      Flag_AT = 0;
      AddrToWrite_HEX =  4096*AsciiToHex(AddrToWrite[0]);
      AddrToWrite_HEX =  256 *AsciiToHex(AddrToWrite[1]) + AddrToWrite_HEX;
      AddrToWrite_HEX =  16  *AsciiToHex(AddrToWrite[2]) + AddrToWrite_HEX;
      AddrToWrite_HEX =       AsciiToHex(AddrToWrite[3]) + AddrToWrite_HEX;
      WritePosition = 0;
      goto OutFunc;
    }
  }
  
  //'@' û�г���
  else
  {
    //���粻�ǻس����л��߿ո��ʱ��
    if(u8data != ' ' && u8data != '\r' && u8data != '\n' && u8data != 0X0A && u8data != 0X0D)
    {
        //��ַλ
        if(u8data == '@')
        {
          Flag_AT = 1;
          FCTL1 = FWKEY + WRT;
          goto OutFunc;
        }
        //��q�� ����λ�� 
        if(u8data == 'q')
        {
          FCTL1 = FWKEY;                            // Clear WRT bit
          GoToApp();
        }
        //data����
        else
        {
          UpdateData[Data_i] = u8data;
          Data_i++;
          if(Data_i == 2)
            {
              Data_i = 0; 
              UpdateData_HEX = 16 * AsciiToHex(UpdateData[0]);
              UpdateData_HEX = UpdateData_HEX + AsciiToHex(UpdateData[1]);
              //д�뵽APP FLASH��
              *(char *)(AddrToWrite_HEX + WritePosition) = UpdateData_HEX;
              WritePosition++;
            }
        }
    }
  }
  
OutFunc:
}



