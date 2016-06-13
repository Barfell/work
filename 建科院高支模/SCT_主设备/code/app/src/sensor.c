#include "msp430.h"
#include "sd.h"
#include "sensor.h"
#include "kernel.h"
#include "stdio.h"
#include "math.h"


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



//电池电压
float Get_INNER_Voltage(void)
{
  float vol = 0.0;
  
  SDInit();
  delay_ms(1000);
  vol = GetSD16Voltage(4);
  //printf("vol:%f\r\n",vol);
  vol += 0.22;
  
  vol = vol*54.75 /3.75;//5.1m  ---   两个750K并联
  SDOff();
  
  return vol;
}


//电压传感器电压
float Get_VOL_Voltage(void)
{
  float vol = 0.0;
  
//  SDInit();
//  delay_ms(1000);
//  vol = GetSD16Voltage(2);
//  vol = vol*9.0 /1.0;//0-5v输入，0-0.55v
//  SDOff();
  
  return vol;
}

//电流传感器电压
float Get_CURRENT_Voltage(void)
{
  float vol = 0.0;
  
//  SDInit();
//  delay_ms(1000);
//  vol = GetSD16Voltage(2);
//  vol = vol/25;//4-20ma输入，0.1-0.5v
//  SDOff();
  
  return vol;
}
 


//电阻传感器电压
float Get_RES_Voltage(void)
{
  float vol = 0.0;
  
//  SDInit();
//  delay_ms(1000);
//  vol = GetSD16Voltage(1);
//  vol = vol*51.0 /3.75;
//  SDOff();
  
  return vol;
}


//振弦温度电压
float Get_VW_Voltage(void)
{
  float vol = 0.0;
  
  SDInit();
  delay_ms(1000);
  vol = GetSD16Voltage(5);
  SDOff();
  
  return vol;
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
			fTem = 0;
		}
	g_dTem = fTem;
	return(fTem);
}

