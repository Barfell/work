#include "ds18b20.h" 




#define Delay	DelayUs_Sft
void DS18B20_Rst(void)     
{                  
 DS18B20_IO_OUT(); //SET PA0 OUTPUT
 GPIO_ResetBits(GPIOB, GPIO_Pin_9); //���� DQ  
    Delay(750);    //���� 750us 
   GPIO_SetBits(GPIOB, GPIO_Pin_9); //DQ=1  
 Delay(40);     //15US 
} 

u8 DS18B20_Check(void)      
{    
 u8 retry=0; 
 DS18B20_IO_IN();//SET PA0 INPUT   
    while (DS18B20_DQ_IN&&retry<200) 
 { 
  retry++; 
  Delay(1); 
 };   
 if(retry>=200)return 1; 
 else retry=0; 
    while (!DS18B20_DQ_IN&&retry<240) 
	{ 
  retry++;
    Delay(1); 
 }; 
 if(retry>=240)return 1;      
 return 0; 
} 

u8 DS18B20_Read_Bit(void)     // read one bit 
{ 
    u8 data; 
 DS18B20_IO_OUT();//SET PA0 OUTPUT 
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);  
 Delay(2); 
    GPIO_SetBits(GPIOB, GPIO_Pin_9);  
 DS18B20_IO_IN();//SET PA0 INPUT 
 Delay(12); 
 if(DS18B20_DQ_IN)data=1; 
    else data=0;   
    Delay(50);            
    return data; 
}

/*u8 DS18B20_Read_Byte(void)    // read one byte 
{         
    u8 i,j,dat; 
    dat=0; 
 for (i=1;i<=8;i++)  
 { 
        j=DS18B20_Read_Bit(); 
        dat=(j<<7)|(dat>>1); 
    }           
    return dat; 
} */

u8 DS18B20_Read_Byte(void) 
{
 unsigned char i,Dat;
 DS18B20_IO_OUT();
GPIO_SetBits(GPIOB, GPIO_Pin_9);
 Delay(5);
 for(i=8;i>0;i--)
 {
   Dat >>= 1;
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);    //�Ӷ�ʱ��ʼ�������ź��߱�����15u�ڣ��Ҳ�������������15u�����
  Delay(5);   //5us
 GPIO_SetBits(GPIOB, GPIO_Pin_9);
  Delay(5);   //5us
  DS18B20_IO_IN();
  if(DS18B20_DQ_IN)
    Dat|=0x80;
  else
   Dat&=0x7f;  
  Delay(65);   //65us
  DS18B20_IO_OUT();
  GPIO_SetBits(GPIOB, GPIO_Pin_9);
 }
 return Dat;
}

/*
void DS18B20_Write_Byte(u8 dat)      
 {              
    u8 j; 
    u8 testb; 
 DS18B20_IO_OUT();//SET PA0 OUTPUT; 
    for (j=1;j<=8;j++)  
 {         testb=dat&0x01; 
        dat=dat>>1; 
        if (testb)  
        { 
            GPIO_ResetBits(GPIOB, GPIO_Pin_9);// Write 1 
            Delay(2);                          
            GPIO_SetBits(GPIOB, GPIO_Pin_9); 
         //   Delay(60);              
        } 
        else  
        { 
            GPIO_ResetBits(GPIOB, GPIO_Pin_9);// Write 0 
            Delay(60);              
            GPIO_SetBits(GPIOB, GPIO_Pin_9); 
			            Delay(5);       
        } 
    } 
}*/ 

void DS18B20_Write_Byte(u8 dat) 
{
 unsigned char i;
 DS18B20_IO_OUT();
 for(i=8;i>0;i--)
 {
   GPIO_ResetBits(GPIOB, GPIO_Pin_9);    //��15u���������������ϣ�DS18B20��15-60u����
  Delay(5);    //5us
  if(dat&0x01 )
   GPIO_SetBits(GPIOB, GPIO_Pin_9); 
  else
   GPIO_ResetBits(GPIOB, GPIO_Pin_9);
  Delay(65);    //65us
 GPIO_SetBits(GPIOB, GPIO_Pin_9);
  Delay(2);    //������λ��Ӧ����1us
   dat=dat>>1;  
 } 
}


void DS18B20_Start(void)// ds1820 start convert 
{                         
    DS18B20_Rst();     
 DS18B20_Check();   
    DS18B20_Write_Byte(0xcc);// skip rom 
    DS18B20_Write_Byte(0x44);// convert 
}  

u8 DS18B20_Init(void) 
{ 
// RCC->APB2ENR|=1<<2;    //ʹ�� PORTA��ʱ��  
// GPIOB->CRL&=0XFFFFFFF0;//PORTA.0  ������� 
// GPIOB->CRL|=0X00000003; 
// GPIOB->ODR|=1<<0;      //���1 
	 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PORTG��ʱ�� 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				//PORTG.11 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_9);    //���1
 DS18B20_Rst(); 
 return DS18B20_Check(); 
}   

short DS18B20_Get_Temp(void) 
{  u8 temp; 
u8 TL,TH; 
 short tem; 
    DS18B20_Start ();
	Delay(100);                    // ds1820 start convert 
    DS18B20_Rst(); 
	Delay(100);
    DS18B20_Check();
	Delay(100);   
    DS18B20_Write_Byte(0xcc);// skip rom 
	Delay(100);
DS18B20_Write_Byte(0xbe);// convert

   // DS18B20_Write_Byte(0xbe);// convert
	Delay(100);      
    TL=DS18B20_Read_Byte(); // LSB 
	Delay(100);   
    TH=DS18B20_Read_Byte(); // MSB
	Delay(100); 
	    if(TH>7) 
    { 
        TH=~TH; 
        TL=~TL;  
        temp=0;//�¶�Ϊ��   
    }else temp=1;//�¶�Ϊ��       
    tem=TH; //��ø߰�λ 
    tem<<=8;     
    tem+=TL;//��õװ�λ 
    tem=(float)tem*0.625;//ת��      
 if(temp)return tem; //�����¶�ֵ 
 else 
 return -tem;     
}
