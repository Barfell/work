
#include "bsp.h"
#include "lpc_types.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_gpio.h"

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		External interrupt 3 handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
//static uint8_t led_on_off = 0;
extern uint8_t press_sta;

void GPIO_IRQHandler(void)
{
	static uint8_t led_on_off = 0;

	if(GPIO_GetIntStatus(BRD_PIO_USED_INTR_PORT_S1, BRD_PIO_USED_INTR_PIN_S1, 1))
	{
		GPIO_ClearInt(BRD_PIO_USED_INTR_PORT_S1, BRD_PIO_USED_INTR_MASK_S1);
		GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, led_on_off);
		GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, 0);
		led_on_off = ~led_on_off;
		return;
	}

	if(GPIO_GetIntStatus(BRD_PIO_USED_INTR_PORT_S2, BRD_PIO_USED_INTR_PIN_S2, 1))
	{
		GPIO_ClearInt(BRD_PIO_USED_INTR_PORT_S2, BRD_PIO_USED_INTR_MASK_S2);
		GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, 0);
		GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, led_on_off);
		led_on_off = ~led_on_off;
		return;
	}

	if(GPIO_GetIntStatus(BRD_PIO_USED_INTR_PORT_S3, BRD_PIO_USED_INTR_PIN_S3, 1))
	{
		GPIO_ClearInt(BRD_PIO_USED_INTR_PORT_S3, BRD_PIO_USED_INTR_MASK_S3);
		GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, led_on_off);
		GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, led_on_off);
		led_on_off = ~led_on_off;
		return;
	}

	if(GPIO_GetIntStatus(BRD_PIO_USED_INTR_PORT_S4, BRD_PIO_USED_INTR_PIN_S4, 1))
	{
		GPIO_ClearInt(BRD_PIO_USED_INTR_PORT_S4, BRD_PIO_USED_INTR_MASK_S4);
		GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, ~led_on_off);
		GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, led_on_off);
		led_on_off = ~led_on_off;
		return;
	}

	if(GPIO_GetIntStatus(0, 12, 1))
	{
		GPIO_ClearInt(0, (1<<12));
		GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, ~led_on_off);
		GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, led_on_off);
		led_on_off = ~led_on_off;
		press_sta = 1;
		return;
	}
}

void Init_gpio_interrupt(void){
  	PINSEL_ConfigPin(BRD_PIO_USED_INTR_PORT_S1,BRD_PIO_USED_INTR_PIN_S1,0);
	GPIO_SetDir(BRD_PIO_USED_INTR_PORT_S1, BRD_PIO_USED_INTR_MASK_S1, GPIO_DIRECTION_INPUT);

	PINSEL_ConfigPin(BRD_PIO_USED_INTR_PORT_S2,BRD_PIO_USED_INTR_PIN_S2,0);
	GPIO_SetDir(BRD_PIO_USED_INTR_PORT_S2, BRD_PIO_USED_INTR_MASK_S2, GPIO_DIRECTION_INPUT);

	PINSEL_ConfigPin(BRD_PIO_USED_INTR_PORT_S3,BRD_PIO_USED_INTR_PIN_S3,0);
	GPIO_SetDir(BRD_PIO_USED_INTR_PORT_S3, BRD_PIO_USED_INTR_MASK_S3, GPIO_DIRECTION_INPUT);

	PINSEL_ConfigPin(BRD_PIO_USED_INTR_PORT_S4,BRD_PIO_USED_INTR_PIN_S4,0);
	GPIO_SetDir(BRD_PIO_USED_INTR_PORT_S4, BRD_PIO_USED_INTR_MASK_S4, GPIO_DIRECTION_INPUT);

	// Enable GPIO interrupt that connects with key
	GPIO_IntCmd(BRD_PIO_USED_INTR_PORT_S1, BRD_PIO_USED_INTR_MASK_S1, 1);  //0:Rising edge  1:falling edge
	GPIO_IntCmd(BRD_PIO_USED_INTR_PORT_S2, BRD_PIO_USED_INTR_MASK_S2, 1);  //0:Rising edge  1:falling edge
	GPIO_IntCmd(BRD_PIO_USED_INTR_PORT_S3, BRD_PIO_USED_INTR_MASK_S3, 1);  //0:Rising edge  1:falling edge
	GPIO_IntCmd(BRD_PIO_USED_INTR_PORT_S4, BRD_PIO_USED_INTR_MASK_S4, 1);  //0:Rising edge  1:falling edge

	NVIC_SetPriority(GPIO_IRQn, 1);		//设置中断优先级
	NVIC_EnableIRQ(GPIO_IRQn);
}

void uninit_gpio_interrupt(void){

	// Disable GPIO interrupt that connects with key
	NVIC_DisableIRQ(GPIO_IRQn);

}


