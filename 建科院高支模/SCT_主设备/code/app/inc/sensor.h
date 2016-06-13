#ifndef _SENSOR_H_
#define _SENSOR_H_

//电池电压
float Get_INNER_Voltage(void);

//电压传感器电压
float Get_VOL_Voltage(void);

//电流传感器电压
float Get_CURRENT_Voltage(void);
 
//电阻传感器电压
float Get_RES_Voltage(void);

//振弦温度电压
float Get_VW_Voltage(void);

double GetNTCTemperature(double NTCRes);

#endif