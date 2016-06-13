/*****************************************************************************
 IIC 总线温度传感器SA56004驱动主程序
******************************************************************************/
#include <math.h>
#include "SA56004.h"
#include "lpc177x_8x_i2c.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc_types.h"
#include "LPC177x_8x.h"

#define SA56004_I2C		I2C_0
#define Sa56004_I2CADDR (0x98 >> 1)

uint8_t Sa56004_Init(uint32_t i2cClockFreq)
{
	// Config Pin for I2C_SDA and I2C_SCL of I2C0
	// It's because the SA56004 IC is linked to LPC177x_8x by I2C0 clearly
	uint8_t Sa56004_ID;
	PINSEL_ConfigPin (0, 27, 1);
	PINSEL_ConfigPin (0, 28, 1);

	I2C_Init(SA56004_I2C, i2cClockFreq);

	/* Enable I2C1 operation */
	I2C_Cmd(SA56004_I2C, ENABLE);
		
	Sa50064_Read(I2C_0,RMID_R,&Sa56004_ID);
	if(Sa56004_ID == 0xA1){
		Sa50064_Write(SA56004_I2C,CON_W,0x14); //disable remote T_CRIT and local T_CRIT
		Sa50064_Write(SA56004_I2C,CR_W,0x09);  // Conversion rate 32Hz
	    Sa50064_Write(SA56004_I2C,AM_RW,0x00);	//The ALERT output is in interrupte mode
		Sa50064_Write(SA56004_I2C,LHS_W,0x1E);
		Sa50064_Write(SA56004_I2C,LLS_W,0x00);
		return 1;
	}
	return 0;
}


void Sa56004_DeInit(void)
{
	/* Enable I2C1 operation */
	I2C_Cmd(SA56004_I2C, DISABLE);

	return;
}

uint8_t Sa56004_R_Test(uint8_t *sign,uint8_t *rx_data){
	uint8_t rx_buf = 0;

	if(Sa50064_Read(SA56004_I2C,LTHB_R,&rx_buf)){
	  if(rx_buf&(1<<7))
	  	*sign = 1;						  //bit7如果为1表示负温，符号标志位表示为1
	  else
	    *sign = 0;

	  rx_buf = (int_fast8_t)rx_buf;		  //强制类型转换为有符号整型
	  *rx_data = abs(rx_buf);
	  return 1;
	}
	return 0;	//返回一个无效的数

}

