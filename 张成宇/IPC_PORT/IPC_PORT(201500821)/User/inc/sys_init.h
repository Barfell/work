#ifndef __SYS_INIT_H
#define __SYS_INIT_H

/* MUC����ϵͳ��Դ�������ſ��� */
#define OPEN_PWR()	GPIO_SetBits(GPIOA,GPIO_Pin_12)					//��������ϵͳ��Դ
#define CLOSE_PWR()	GPIO_ResetBits(GPIOA,GPIO_Pin_12)				//�ض�����ϵͳ��Դ

/* ���ػ���Դ�������ſ��� */
#define OPEN_IPCPWR()	GPIO_SetBits(GPIOB,GPIO_Pin_1)					//�������ػ���Դ
#define CLOSE_IPCPWR()	GPIO_ResetBits(GPIOB,GPIO_Pin_1)				//�ضϹ��ػ���Դ

/* ����LED������ */
#define LED_ON()	GPIO_SetBits(GPIOA,GPIO_Pin_8)					//����
#define LED_OFF()	GPIO_ResetBits(GPIOA,GPIO_Pin_8)				//����

extern void System_Init(void);

#endif
