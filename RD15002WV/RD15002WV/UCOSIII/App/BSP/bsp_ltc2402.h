#ifndef __BSP_LTC2402_H
#define __BSP_LTC2402_H

#define LTC2402_CS_LOW 			GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define LTC2402_CS_HIGH		 	GPIO_SetBits(GPIOA,GPIO_Pin_8)

void LTC2402Init(void);

unsigned int LTC2402Read(void);

unsigned char ConversionSatue(void);

unsigned int GetLTC2402Value(void);
#endif


