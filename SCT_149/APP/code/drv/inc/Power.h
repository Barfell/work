#ifndef _POWER_H_
#define _POWER_H_


/*电源开关宏  使用前要配置好引脚模式，使用PowerIoInit();函数配置引脚*/
#define  POWER_MAIN_ON          (P2OUT |=  BIT0)
#define  POWER_MAIN_OFF         (P2OUT &= ~BIT0)

#define  POWER_MCU_ON           (P2OUT |=  BIT1)
#define  POWER_MCU_OFF          (P2OUT &= ~BIT1)

#define  POWER_ZIGBEE_ON        (P2OUT |=  BIT2)
#define  POWER_ZIGBEE_OFF       (P2OUT &= ~BIT2)

#define  POWER_ADC_ON           (P2OUT |=  BIT3)
#define  POWER_ADC_OFF          (P2OUT &= ~BIT3)

#define  DRIVER_EN_ON           (P6OUT |=  BIT3)
#define  DRIVER_EN_OFF          (P6OUT &=  ~BIT3)

void PowerIoInit(void);

#endif