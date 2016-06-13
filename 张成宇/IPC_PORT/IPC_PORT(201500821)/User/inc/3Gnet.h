#ifndef __3GNET_H
#define __3GNET_H

/* MCU控制3G模块UC864-E启动引脚MCU_UC864PWRON设置拉高或拉低 */
#define MCU_UC864PWRON_UP()		GPIO_SetBits(GPIOD,GPIO_Pin_3)
#define MCU_UC864PWRON_DOWN()	GPIO_ResetBits(GPIOD,GPIO_Pin_3)

/* MCU控制3G模块UC864-E复位引脚MCU_UC864RST设置拉高或拉低 */
#define MCU_UC864RST_UP()		GPIO_SetBits(GPIOD,GPIO_Pin_4)
#define MCU_UC864RST_DOWN()		GPIO_ResetBits(GPIOD,GPIO_Pin_4)


extern void UC864_POWERON(void);
extern void UC864_RESET(void);

#endif
