#ifndef _POWER_H_
#define _POWER_H_


/*��Դ���غ�  ʹ��ǰҪ���ú�����ģʽ��ʹ��PowerIoInit();������������*/
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