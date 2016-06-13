/***********************************************************************
 * @file	: bsp.h
 * @brief	: Contains basic information about the board that can
 			  be using with the current code package. It may 
 			  include some header file for the components mounted
 			  on the board. Or else some neccessary hardware (IOs) 
 			  settings for the using board may be involved.
 * @version	: 1.0
 * @date	: 03. March. 2011
 * @author	: NXP MCU SW Application Team
 * @note	: 
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **************************************************************************/
#include "lpc_types.h"

#ifndef _BSP_H
#define _BSP_H

#define _DEFAULT_BOARD				(0)
#define _UCDRAGON_EB_BOARD			(1)

#define _CURR_USING_BRD				(_UCDRAGON_EB_BOARD)

#if (_CURR_USING_BRD == _UCDRAGON_EB_BOARD)
//Driver for PHY of LAN DP83848C IC
#include "phylan_dp83848c.h"

//LED indicators preset	定义LED使用GPIO端口
#define BRD_LED_1_CONNECTED_PORT		(1)
#define BRD_LED_1_CONNECTED_PIN			(12)
#define BRD_LED_1_CONNECTED_MASK		(1 << BRD_LED_1_CONNECTED_PIN)

#define BRD_LED_2_CONNECTED_PORT		(1)
#define BRD_LED_2_CONNECTED_PIN			(13)
#define BRD_LED_2_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

//PIO interrupt preset 定按键S1~S4使用端口
#define BRD_PIO_USED_INTR_PORT_S1			(2)
#define BRD_PIO_USED_INTR_PIN_S1			(11)
#define BRD_PIO_USED_INTR_MASK_S1			(1 << BRD_PIO_USED_INTR_PIN_S1)

#define BRD_PIO_USED_INTR_PORT_S2			(2)
#define BRD_PIO_USED_INTR_PIN_S2			(19)
#define BRD_PIO_USED_INTR_MASK_S2			(1 << BRD_PIO_USED_INTR_PIN_S2)

#define BRD_PIO_USED_INTR_PORT_S3			(2)
#define BRD_PIO_USED_INTR_PIN_S3			(21)
#define BRD_PIO_USED_INTR_MASK_S3			(1 << BRD_PIO_USED_INTR_PIN_S3)

#define BRD_PIO_USED_INTR_PORT_S4			(2)
#define BRD_PIO_USED_INTR_PIN_S4			(25)
#define BRD_PIO_USED_INTR_MASK_S4			(1 << BRD_PIO_USED_INTR_PIN_S4)




//ADC input preset on this board					 LPC
#define BRD_ADC_PREPARED_CHANNEL		(ADC_CHANNEL_2)
#define BRD_ADC_PREPARED_INTR			(ADC_ADINTEN2)

#define BRD_ADC_PREPARED_CH_PORT		(0)
#define BRD_ADC_PREPARED_CH_PIN			(25)
#define BRD_ADC_PREPARED_CH_FUNC_NO		(1)

//MCI power active levell
#define BRD_MCI_POWERED_ACTIVE_LEVEL	(0)


//Timer preset
#define BRD_TIMER_USED				(LPC_TIM0)
#define BRD_TIM_INTR_USED			(TIMER0_IRQn)

#define BRD_TIM_CAP_LINKED_PORT		(1)
#define BRD_TIM_CAP_LINKED_PIN		(26)

extern void Delay (unsigned long tick);
void LED_ctr(uint8_t led_num,uint8_t on_off);

void Init_gpio_interrupt    (void);
void uninit_gpio_interrupt  (void);
void Easy_Web(void);
void Init_EMAC_Dp83848(void);

void Usb_MassStorage (void);
void USB_Dis_Connect (void);

void DAC_SineWave(void);
void DAC_SineWave_Dis(void);

int Pwm_Test_Beep(void);
void Pwm_Dis_Beep(void);
void Pwm_change_Freq(uint8_t state);

void Can_init(void);
void Can_Uninit(void);

uint8_t Nor_RW_test(uint32_t offset_adr);
uint8_t Nand_Test(void);

void rs485_tx_rx(void);
void rs485_tx_rx(void);

#endif			//end if (_CURR_USING_BRD == _UCDRAGON_EB_BOARD)

#endif
