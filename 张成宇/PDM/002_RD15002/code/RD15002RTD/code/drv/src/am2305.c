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

//开始温度转换
VOID AM2305_Start(VOID)	   
{                  	
    AM2305_GPIO_OUT();
    /*主机起始信号    拉低Min=0.8ms,Max=20ms Typical=1ms*/
    AM2305_Set_L();
    DelayMs(1);
    AM2305_Set_H();
    /*主机释放总线 	Min=30us，Max=50us*/
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
        /*延时Min=26us Max=28us 数据 "0" 的高电平时间*/
        DelayUs_Sft(50);//延时50us
        /*判断传感器发送数据位*/
        tmp = 0;
        if(AM2305_PIN_IN)
        {
            tmp = 1;
        }
        cnt = 0;
        while(AM2305_PIN_IN)//等待高电平 结束
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
        /*判断从机是否发出的 80us 低电平响应信号是否结束*/
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
        /*数据接收 传感器共发送40位数据*/
        /*即5个字节 高位先送 5个字节分别为 */
        /*湿度高位 湿度地位 温度高位 温度地位 校验和*/
        /*校验和为 湿度高位+湿度低位+温度高位+温度地位*/
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


