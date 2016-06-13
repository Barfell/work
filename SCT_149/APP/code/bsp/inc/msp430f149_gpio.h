/**
 * @file  msp430f149_gpio.h
 * @author  wf
 * @version V1.0
 * @date  2015-11-19
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-19
 * +  file create
 */
#ifndef MSP430F149_GPIO_H
#define MSP430F149_GPIO_H
#include "i430type.h"


typedef enum
{
	GPIO_Pin_0 = 0x01,
	GPIO_Pin_1 = 0x02,
	GPIO_Pin_2 = 0x04,
	GPIO_Pin_3 = 0x08,
	GPIO_Pin_4 = 0x10,
	GPIO_Pin_5 = 0x20,
	GPIO_Pin_6 = 0x40,
	GPIO_Pin_7 = 0x80
}GPIO_PinTypeDef;

typedef enum
{
	GPIO_1 = 1,
	GPIO_2,
	GPIO_3,
	GPIO_4,
	GPIO_5,
	GPIO_6
}GPIO_PortTypeDef;

typedef enum 
{
	GPIO_Mode_IN = 1,
	GPIO_Mode_Out,
	GPIO_Mode_AF,
	GPIO_Mode_AFIN,
	GPIO_Mode_AFOUT
}GPIO_ModeTypeDef;

typedef enum 
{
	GPIO_Trigger_Up = 0X00,
	GPIO_Trigger_Down = 0xff
}GPIO_TriggerTypeDef;

void GPIO_SetPinOutputHigh(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinOutputLow(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_Init(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin, GPIO_ModeTypeDef GPIO_Mode);

void GPIO_SetPinInput(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinOutput(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinHigh(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinLow(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinDefault(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
void GPIO_SetPinAlternate(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);

void GPIO_SetPortOutputVaule(GPIO_PortTypeDef GPIOx, u8 u8value);

void GPIO_SetEXTIPin(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin, GPIO_TriggerTypeDef GPIO_Trigger);

void GPIO_SetPortDefault(GPIO_PortTypeDef GPIOx);
void GPIO_SetPortIntput(GPIO_PortTypeDef GPIOx);
void GPIO_SetPortOutput(GPIO_PortTypeDef GPIOx);

u8 GPIO_GetPinInputValue(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
u8 GPIO_GetPortInputValue(GPIO_PortTypeDef GPIOx);
u8 GPIO_GetPinOutputValue(GPIO_PortTypeDef GPIOx, GPIO_PinTypeDef GPIO_Pin);
u8 GPIO_GetPortOutputValue(GPIO_PortTypeDef GPIOx);



#endif