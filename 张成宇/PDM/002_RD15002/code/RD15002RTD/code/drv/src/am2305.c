#include "am2305.h"


#define AM2305_GPIO_IN()          	GPIO_Set(AM2305_SDA_GPIO,AM2305_SDA_PIN,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz)
#define AM2305_GPIO_OUT()         	GPIO_Set(AM2305_SDA_GPIO,AM2305_SDA_PIN,GPIO_Mode_Out_PP,GPIO_Speed_50MHz)

#define AM2305_PIN_IN           	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define AM2305_PIN_OUT          	PBout(9)

#define RCC_AM2305_CONFIG()     	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define AM2305_SDA_GPIO         	GPIOB
#define AM2305_SDA_PIN          	GPIO_Pin_9

#define AM2305_Set_H()         	 	GPIO_SetBits(AM2305_SDA_GPIO,AM2305_SDA_PIN)
#define AM2305_Set_L()		    	GPIO_ResetBits(AM2305_SDA_GPIO,AM2305_SDA_PIN)



STATIC U8 g_szAM2305Data[5] = {0x00,0x00,0x00,0x00,0x00};

STATIC U16 g_u16AM2305Cnt;

VOID AM2305_Init(VOID)
{
	RCC_AM2305_CONFIG();
}

//��ʼ�¶�ת��
VOID AM2305_Start(VOID)	   
{                  	
    AM2305_GPIO_OUT();
    /*������ʼ�ź�    ����Min=0.8ms,Max=20ms Typical=1ms*/
    AM2305_Set_L();
    DelayMs(1);
    AM2305_Set_H();
    /*�����ͷ����� 	Min=30us��Max=50us*/
    DelayUs_Sft(35);
    AM2305_GPIO_IN();
    GPIO_ReadInputDataBit(AM2305_SDA_GPIO,AM2305_SDA_PIN);
    DelayUs_Sft(2);
}

U8 AM2305_ReceiveByte(VOID)
{
    U16 i,cnt;
    U8 buffer,tmp;
    buffer = 0;
    for(i = 0;i < 8;i++)
    {
        cnt = 0;
        while(!AM2305_PIN_IN)
        {
			if(++cnt >= 3000)
			{
				break;
			}
        }
        /*��ʱMin=26us Max=28us ���� "0" �ĸߵ�ƽʱ��*/
        DelayUs_Sft(50);//��ʱ50us
        /*�жϴ�������������λ*/
        tmp = 0;
        if(AM2305_PIN_IN)
        {
            tmp = 1;
        }
        cnt = 0;
        while(AM2305_PIN_IN)//�ȴ��ߵ�ƽ ����
        {
		   	if(++cnt >= 3000)
			{
			  break;
			}
        }
        buffer <<=1;
		buffer |= tmp;
    }
    return buffer;
}

U8 AM2305_Run(void)
{
    U8 i, u8ret = 1;
    AM2305_Start();
    DelayUs_Sft(5);

    if(AM2305_PIN_IN == 0)
    {

        g_u16AM2305Cnt = 0;
        /*�жϴӻ��Ƿ񷢳��� 80us �͵�ƽ��Ӧ�ź��Ƿ����*/
        while(!AM2305_PIN_IN)
        {
            if(++g_u16AM2305Cnt > 55000)
            {

                break;
                
            }
        }
        g_u16AM2305Cnt = 0;
        while(AM2305_PIN_IN)
        {
            if(++g_u16AM2305Cnt > 55000)
            {

                break;
            }
        }
        /*���ݽ��� ������������40λ����*/
        /*��5���ֽ� ��λ���� 5���ֽڷֱ�Ϊ */
        /*ʪ�ȸ�λ ʪ�ȵ�λ �¶ȸ�λ �¶ȵ�λ У���*/
        /*У���Ϊ ʪ�ȸ�λ+ʪ�ȵ�λ+�¶ȸ�λ+�¶ȵ�λ*/
        for(i = 0;i < 5;i++)
        {
            g_szAM2305Data[i] = AM2305_ReceiveByte();
        }
		u8ret = 0;
    }
    return u8ret;
}


VOID GetAm2305Data(U8 *pBuf)
{
	U8 u8Cnt;
	for(u8Cnt = 0; u8Cnt < 5; u8Cnt++)
	{
		pBuf[u8Cnt] = g_szAM2305Data[u8Cnt];
	}
}


