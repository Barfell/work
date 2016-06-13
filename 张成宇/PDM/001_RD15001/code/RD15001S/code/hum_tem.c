/*Abstract :Am2305 temprature & Humidity Transmitter Read.
*
*Version NO.:1.0
*Writer     :Woy
*Date       :2015-06-10
**************************************************/
#include "C8051F340.h"
#include "system.h"
#include "hum_tem.h"
#include "Init.h"
sbit Sensor_SDA        = P0^6;

//////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////
static unsigned char xdata Sensor_Check;		  //У���
static unsigned char xdata Sensor_AnswerFlag;  //�յ���ʼ��־λ
static unsigned char xdata Sensor_ErrorFlag;   //��ȡ�����������־
static unsigned int  xdata Sys_CNT;
static unsigned int  xdata Tmp;

unsigned char xdata Sensor_Data[5]={0x00,0x00,0x00,0x00,0x00};


/********************************************\
|* ���ܣ� �����������͵ĵ����ֽ�	        *|
\********************************************/
static unsigned char Read_SensorData(void)
{
	unsigned int xdata i,xdata cnt;
	unsigned char xdata buffer,xdata tmp;
	buffer = 0;
	for(i=0;i<8;i++)
	{
		cnt=0;
		while(!Sensor_SDA)	//����ϴε͵�ƽ�Ƿ����
		{
		  if(++cnt >= 3000)
		   {
			  break;
		   }
		}
		//��ʱMin=26us Max50us ��������"0" �ĸߵ�ƽ
		DelayUs(40);	 //��ʱ30us   
		
		//�жϴ�������������λ
		tmp =0;
		if(Sensor_SDA)	 
		{
		  tmp = 1;
		}  
		cnt =0;
		while(Sensor_SDA)		//�ȴ��ߵ�ƽ ����
		{
		   	if(++cnt >= 2000)
			{
			  break;
			}
		}
		buffer <<=1;
		buffer |= tmp;	
	}
	return buffer;
}

unsigned char Am2305_Read(void)
{
	unsigned char xdata i;
	//��������(Min=800US Max=20Ms) 
    Sensor_SDA = 0;
	DelayMs(1);  //��ʱ2Ms
	  
	//�ͷ����� ��ʱ(Min=30us Max=50us)
	Sensor_SDA = 1; 	
	DelayUs(30);//��ʱ30us
	//������Ϊ���� �жϴ�������Ӧ�ź� 
	Sensor_SDA = 1; 
     	  
	Sensor_AnswerFlag = 0;  // ��������Ӧ��־	 
	 DelayUs(2);
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	if(Sensor_SDA ==0)
	{
	   Sensor_AnswerFlag = 1;//�յ���ʼ�ź�
	   Sys_CNT = 0;
	   //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
	   while((!Sensor_SDA))
	   {
	     if(++Sys_CNT>3000) //��ֹ������ѭ��
		 {
		   Sensor_ErrorFlag = 1;
		   return 0;
		  } 
	    }
	    Sys_CNT = 0;
	    //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	    while((Sensor_SDA))
	    {
	       if(++Sys_CNT>3000) //��ֹ������ѭ��
		   {
		     Sensor_ErrorFlag = 1;
		     return 0;
		   } 
	    } 		 
	    // ���ݽ���	������������40λ���� 
	    // ��5���ֽ� ��λ����  5���ֽڷֱ�Ϊʪ�ȸ�λ ʪ�ȵ�λ �¶ȸ�λ �¶ȵ�λ У���
	    // У���Ϊ��ʪ�ȸ�λ+ʪ�ȵ�λ+�¶ȸ�λ+�¶ȵ�λ
	    for(i=0;i<5;i++)
	    {
	      Sensor_Data[i] = Read_SensorData();
	    }
	  }
	  else
	  {
	    Sensor_AnswerFlag = 0;	  // δ�յ���������Ӧ
		memset(Sensor_Data, 0, 5);	
	  }
	  return 1;	  

}
////////////////////////////////////////////////////////////The end//////////////////////////////////////////////////////////////////