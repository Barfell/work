#ifndef YL_LPC1788_TOUCH_H_
#define YL_LPC1788_TOUCH_H_

#include "LPC177x_8x.h"

/*Type A I/O Control registers */
#define IO_Pull_up 	  0x0|(0x2<<3)|(0x5<<5)		//Gpio pull-up
#define ADC_In 	     (0x1)|(0x0<<3)				//ADC Input
#define IO_No_UD     (0x3)|(0x0<<3)|(0x5<<5)	//Gpio no pull-up	and pull-down

#define XR 12
#define XL 23
#define YU 25
#define YD 24

void touch_init(void);
void Touch_INT_EN(void);
void Touch_INT_Dis(void);
void Read_XY_coordinate(void);

#endif
