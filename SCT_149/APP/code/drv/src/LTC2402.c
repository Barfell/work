#include "msp430f149_spi.h"
#include "LTC2402.h"
#include "kernel.h"
#include "math.h"

#define LTC2402_ReferenceResistance     19600.0

#define LTC2402_ReferenceVoltage        5.1

#define PT_ZeroTemRes    100

#define PT_A 	3.9083e-3

#define PT_B    -5.775e-7

#define PT_C    -4.183e-12

#define PT_Min	5

#define PT_Max	200 

#define	NTC_A	1.4051e-3

#define NTC_B	2.369e-4

#define NTC_C	1.019e-7

#define NTC_Min	250

#define	NTC_Max 100000

double g_dRes = 3.2;

double g_dTem = 3.2;

unsigned char LTC2402_TEST_EOC(void)
{
	delay_ms(1000);
	return SpiReadByte();
}

unsigned char LTC2402_ReadByte(void)
{
	unsigned char u8charValue;
	u8charValue = SpiWriteReadByte(0XFF);    
	return u8charValue;
}

void LTC2402Init(void)
{
  SpiInit();
}


//获取电阻值
double LTC2402_GetResistance(void)
{
	unsigned char u8charresbuf[4] = {0};
	unsigned char EOC = 0;
	unsigned long u32resbuf = 0;
	double convertionresult = 0;
	double current = 0;
	double RES = 0;
	double ch1 = 0;
	double ch0 = 0;
	unsigned char i = 0;
	
	for(i = 0;i < 2;i++)
	{
		EOC = LTC2402_TEST_EOC();
		if(  (EOC & 0x80) == 0  )//转换完毕
		{
				u8charresbuf[0] = EOC;
				u8charresbuf[1] = SpiReadByte();
				u8charresbuf[2] = SpiReadByte();
				u8charresbuf[3] = SpiReadByte();
				u32resbuf = (((unsigned long)u8charresbuf[0]<<24)+((unsigned long)u8charresbuf[1]<<16)+((unsigned long)u8charresbuf[2]<<8)+((unsigned long)u8charresbuf[3]<<0));
				u32resbuf = u32resbuf&0x0FFFFFF0;
				u32resbuf = u32resbuf >>4;
				convertionresult = (((double)u32resbuf)/16777216.0)*LTC2402_ReferenceVoltage;
				if(  EOC & 0x40  )
				{
					ch1 = convertionresult;
					ch1=0;
				}
				else
				{
					ch0 = convertionresult;
					//ch0 = 0;
				}
				u8charresbuf[0] = 0;
				u8charresbuf[1] = 0;
				u8charresbuf[2] = 0;
				u8charresbuf[3] = 0;
		}
	}
        
        
    if(ch0 > ch1)
	{
		RES = ch0 - ch1;
	}
    else
	{
		RES = ch1 - ch0;
	}
   
        
//RES为检测的电压值
#ifdef SENSOR_VW
    current = (LTC2402_ReferenceVoltage - RES)/LTC2402_ReferenceResistance;
    RES = RES/current;
	g_dRes = RES;
#endif
        
#ifdef SENSOR_RESISTENCE
        RES = RES;//( 1000.0/(2.5-RES) ) - 1000;
#endif
        
#ifdef SENSOR_VOLTAGE
        RES = ( RES * 3);
#endif
        
#ifdef SENSOR_CURRENT
        RES = (100.0 / RES );
#endif
    return RES;    
}


//计算温度
double GetNTCTemperature(double NTCRes)
{
	double fTem;
	if(NTCRes>PT_Min && NTCRes < PT_Max)
		{
			fTem = (sqrt((PT_A*PT_ZeroTemRes)*(PT_A*PT_ZeroTemRes)-4*PT_B*PT_ZeroTemRes*(PT_ZeroTemRes-NTCRes))-PT_A*PT_ZeroTemRes)/2/PT_B/PT_ZeroTemRes;
		}
	else if(NTCRes>NTC_Min && NTCRes < NTC_Max)
		{
			fTem = (1/((NTC_A) + (NTC_B*(log(NTCRes))) + (NTC_C*(log(NTCRes))*(log(NTCRes))*(log(NTCRes))))) - 273.2;
		}
	else
		{
			//printf("Get resistance Error");
			fTem = 0;
		}
	g_dTem = fTem;
	return(fTem);
}

