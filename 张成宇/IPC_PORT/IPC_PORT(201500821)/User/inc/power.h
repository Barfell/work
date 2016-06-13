#ifndef __POWER_H
#define __POWER_H


/* 检测按键是否按下 */
#define GET_KEY()	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)		//读KeyPress状态位

/* 检测工控主板电源使能电压引脚 POWER_ON  PB6*/
#define Get_IPC_POWERON()  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) //读取PB6状态位

/* 检测工控主板复位引脚 RESET#  PB7 */
#define Get_IPC_RESET()  	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //读取PB7状态位

/* 定义系统电源管理相关的变量 */
typedef struct
{
	u16 PowerKeyTime;			//电源键采样间隔
	u16 IPC_POWERONTime;		//工控主板POWERON引脚电平采样间隔
	u8  PowerKeyCount;			//电源键按下的采样次数
	u8	IPC_POWERONCount;		//工控主板POWERON引脚电平采样次数
}SystemPowerManageS;

extern SystemPowerManageS  SystemPowerManage;

extern void Process_PowerKey(void);
extern void Process_IPCPWRON(void);

#endif
