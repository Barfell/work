
#include "bsp.h"
#include "lpc177x_8x_adc.h"
#include "yl_1788_touch.h"
#include "lpc_types.h"
#include "debug_frmwrk.h"

uint8_t press_sta = 0;

void touch_init(void){
	 LPC_IOCON -> P0_12 = IO_Pull_up;		//P0.12 set gpio pullup
	 LPC_GPIO0 -> DIR  &= ~(0x1<<XR);	//P0.12 input
	
	 LPC_IOCON -> P0_23	= IO_No_UD;
	 LPC_GPIO0 -> DIR  &= ~(0x1<<XL);	//P0.23 input

	 LPC_IOCON -> P0_24 = IO_Pull_up;	//P0.24 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<YD);	//P0.24 output dir
	 LPC_GPIO0 -> CLR  |= (0x1<<YD);	//P0.24 output 0
	
	 LPC_IOCON -> P0_25 = IO_Pull_up;	//P0.25 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<YU);	//P0.25 output dir
	 LPC_GPIO0 -> CLR  |= (0x1<<YU);	//P0.25 output 0
	Delay(1);
}

 /*----------------------------------------------------------------------------
  config the Y  Pins for touch
 *----------------------------------------------------------------------------*/
void config_pins_y(void){
	 LPC_IOCON -> P0_12 = IO_No_UD;		//P0.12 set gpio no pullup and no pulldown
	 LPC_GPIO0 -> DIR  &= ~(0x1<<XR);	//P0.12 input
	
	 LPC_IOCON -> P0_23 = ADC_In;		//P0.23 set gpio pullup
	
	 LPC_IOCON -> P0_24 = IO_Pull_up;	//P0.24 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<YD);	//P0.24 output dir
	 LPC_GPIO0 -> SET  |= (0x1<<YD);	//P0.24 output 1
	
	 LPC_IOCON -> P0_25 = IO_Pull_up;	//P0.25 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<YU);	//P0.25 output dir
	 LPC_GPIO0 -> CLR  |= (0x1<<YU);	//P0.25 output 0
	 Delay(1);
}

 /*----------------------------------------------------------------------------
  config the X  Pins for touch
 *----------------------------------------------------------------------------*/
void config_pins_x(void){
	 LPC_IOCON -> P0_25 = IO_No_UD;		//P0.25 set gpio no pullup and no pulldown
	 LPC_GPIO0 -> DIR  &= ~(0x1<<YU);	//P0.25 input
	
	 LPC_IOCON -> P0_24 = ADC_In;		//P0.24 set gpio pullup
	
	 LPC_IOCON -> P0_23 = IO_Pull_up;	//P0.23 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<XL);	//P0.23 output dir
	 LPC_GPIO0 -> CLR  |= (0x1<<XL);	//P0.23 output 0
	
	 LPC_IOCON -> P0_12 = IO_Pull_up;	//P0.12 set gpio pullup
	 LPC_GPIO0 -> DIR  |= (0x1<<XR);	//P0.12 output dir
	 LPC_GPIO0 -> SET  |= (0x1<<XR);	//P0.12 output 1
	 Delay(1);
}

/*----------------------------------------------------------------------------
  read the x position
 *----------------------------------------------------------------------------*/
 uint16_t read_ch_x(void){
	uint16_t adc_value=0;
	uint32_t i;
 	config_pins_x();
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);
			ADC_StartCmd(LPC_ADC, ADC_START_NOW);

	//Wait conversion complete
	while (!(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_1, ADC_DATA_DONE)));
	
	for(i=0;i<=100;i++);	
	adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_1);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, DISABLE);
	//Display the result of conversion on the UART
	put_str("x:"); _DBH16(adc_value);put_str_(""); 
	return adc_value;
 }

 /*----------------------------------------------------------------------------
  read the y position
 *----------------------------------------------------------------------------*/
 uint16_t read_ch_y(void){
	
	uint16_t adc_value_y=0;
	uint32_t i;
 	config_pins_y();
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);

	//Wait conversion complete
	while (!(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_0, ADC_DATA_DONE)));
	
	for(i=0;i<=100;i++);						   //延时，重要！
	adc_value_y = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, DISABLE);
	//Display the result of conversion on the UART
	put_str("y:"); _DBH16(adc_value_y);put_str_(""); 

	return adc_value_y;
 }

  /*----------------------------------------------------------------------------
  enable the gpio interrupt for touchpanel
 *----------------------------------------------------------------------------*/
 void Touch_INT_EN(void){
  LPC_GPIOINT->IO0IntClr |= (1<<12);
  LPC_GPIOINT -> IO0IntEnF |= (1<<12);				 //Enable the GPIO p0.23 interrupt
  NVIC_SetPriority(GPIO_IRQn, 1);		//设置中断优先级
  NVIC_EnableIRQ(GPIO_IRQn);
  }

/*----------------------------------------------------------------------------
  enable the gpio interrupt for touchpanel
*----------------------------------------------------------------------------*/
 void Touch_INT_Dis(void){
  LPC_GPIOINT -> IO0IntEnF &= ~(1<<12);				 //Disable the GPIO p0.23 interrupt
  LPC_GPIOINT->IO0IntClr |= (1<<12);
  NVIC_DisableIRQ(GPIO_IRQn);
  }


void Read_XY_coordinate(void){
	if(press_sta){
		press_sta = 0;
		Touch_INT_Dis();
		read_ch_x();
		read_ch_y();
		touch_init();
		Touch_INT_EN();
	}else{
	return;
	}
}

