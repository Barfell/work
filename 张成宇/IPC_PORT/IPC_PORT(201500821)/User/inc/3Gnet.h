#ifndef __3GNET_H
#define __3GNET_H

/* MCU����3Gģ��UC864-E��������MCU_UC864PWRON�������߻����� */
#define MCU_UC864PWRON_UP()		GPIO_SetBits(GPIOD,GPIO_Pin_3)
#define MCU_UC864PWRON_DOWN()	GPIO_ResetBits(GPIOD,GPIO_Pin_3)

/* MCU����3Gģ��UC864-E��λ����MCU_UC864RST�������߻����� */
#define MCU_UC864RST_UP()		GPIO_SetBits(GPIOD,GPIO_Pin_4)
#define MCU_UC864RST_DOWN()		GPIO_ResetBits(GPIOD,GPIO_Pin_4)


extern void UC864_POWERON(void);
extern void UC864_RESET(void);

#endif
