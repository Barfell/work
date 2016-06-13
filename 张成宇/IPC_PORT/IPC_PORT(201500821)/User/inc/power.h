#ifndef __POWER_H
#define __POWER_H


/* ��ⰴ���Ƿ��� */
#define GET_KEY()	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)		//��KeyPress״̬λ

/* ��⹤�������Դʹ�ܵ�ѹ���� POWER_ON  PB6*/
#define Get_IPC_POWERON()  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) //��ȡPB6״̬λ

/* ��⹤�����帴λ���� RESET#  PB7 */
#define Get_IPC_RESET()  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //��ȡPB7״̬λ

/* ����ϵͳ��Դ������صı��� */
typedef struct
{
	u16 PowerKeyTime;			//��Դ���������
	u16 IPC_POWERONTime;		//��������POWERON���ŵ�ƽ�������
	u8  PowerKeyCount;			//��Դ�����µĲ�������
	u8	IPC_POWERONCount;		//��������POWERON���ŵ�ƽ��������
}SystemPowerManageS;

extern SystemPowerManageS  SystemPowerManage;

extern void Process_PowerKey(void);
extern void Process_IPCPWRON(void);

#endif
