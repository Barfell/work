#ifndef _SENSOR_H_
#define _SENSOR_H_

//��ص�ѹ
float Get_INNER_Voltage(void);

//��ѹ��������ѹ
float Get_VOL_Voltage(void);

//������������ѹ
float Get_CURRENT_Voltage(void);
 
//���贫������ѹ
float Get_RES_Voltage(void);

//�����¶ȵ�ѹ
float Get_VW_Voltage(void);

double GetNTCTemperature(double NTCRes);

#endif