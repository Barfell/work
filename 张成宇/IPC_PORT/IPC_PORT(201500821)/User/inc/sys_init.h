#ifndef __SYS_INIT_H
#define __SYS_INIT_H

/* MUC整个系统电源锁定引脚开断 */
#define OPEN_PWR()	GPIO_SetBits(GPIOA,GPIO_Pin_12)					//开启整个系统电源
#define CLOSE_PWR()	GPIO_ResetBits(GPIOA,GPIO_Pin_12)				//关断整个系统电源

/* 工控机电源锁定引脚开断 */
#define OPEN_IPCPWR()	GPIO_SetBits(GPIOB,GPIO_Pin_1)					//开启工控机电源
#define CLOSE_IPCPWR()	GPIO_ResetBits(GPIOB,GPIO_Pin_1)				//关断工控机电源

/* 控制LED灯亮灭 */
#define LED_ON()	GPIO_SetBits(GPIOA,GPIO_Pin_8)					//灯亮
#define LED_OFF()	GPIO_ResetBits(GPIOA,GPIO_Pin_8)				//灯灭

extern void System_Init(void);

#endif
