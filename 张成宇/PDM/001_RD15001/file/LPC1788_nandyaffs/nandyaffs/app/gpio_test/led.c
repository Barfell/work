
#include "bsp.h"
#include "lpc_types.h"
#include "lpc177x_8x_gpio.h"
/*LEDµÆ¿ØÖÆ */
void LED_ctr(uint8_t led_num,uint8_t on_off)
{
	if (led_num == 1){
//	GPIO_SetDir(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);
	GPIO_OutputValue(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, on_off);
	}

	if (led_num == 2){
//	GPIO_SetDir(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);
	GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, on_off);
	}
	Delay(500);	  //delay 500ms
}

