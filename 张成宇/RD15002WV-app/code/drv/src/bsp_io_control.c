#include "bsp_io_control.h"


void SW_12V(unsigned char onOroff)
{
	if(onOroff == 1 )
		{GPIO_SetBits(GPIOC,GPIO_Pin_1);}
	else
		{GPIO_ResetBits(GPIOC,GPIO_Pin_1);}
}

void SW_5V(unsigned char onOroff)
{
	if(onOroff == 1 )
		{GPIO_SetBits(GPIOC,GPIO_Pin_2);}
	else
		{GPIO_ResetBits(GPIOC,GPIO_Pin_2);}
}

void SW_3V(unsigned char onOroff)
{
	if(onOroff == 1 )
		{GPIO_SetBits(GPIOB,GPIO_Pin_3);}
	else
		{GPIO_ResetBits(GPIOB,GPIO_Pin_3);}
}

void SW_DTU(unsigned char onOroff)
{
	if(onOroff == 1 )
		{GPIO_SetBits(GPIOE,GPIO_Pin_4);}
	else
		{GPIO_ResetBits(GPIOE,GPIO_Pin_4);}
}

void SW_VW_TRCN(unsigned char onOroff)
{
	if(onOroff == 1 )
		{GPIO_SetBits(GPIOB,GPIO_Pin_10);}
	else
		{GPIO_ResetBits(GPIOB,GPIO_Pin_10);}
}


void SW_VW(unsigned char onOroff)
{
	switch(onOroff)
	{
		case 2:	GPIO_SetBits(GPIOE,GPIO_Pin_8);//001
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);
				break;
		case 3:	GPIO_ResetBits(GPIOE,GPIO_Pin_8);//010
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);
				break;
		case 4:	GPIO_SetBits(GPIOE,GPIO_Pin_8);//011
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);
				break;
		case 5:	GPIO_ResetBits(GPIOE,GPIO_Pin_8);//100
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
				break;
		case 6:	GPIO_SetBits(GPIOE,GPIO_Pin_8);//101
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
				break;
		case 7:	GPIO_ResetBits(GPIOE,GPIO_Pin_8);//110
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
				break;
		case 8:	GPIO_SetBits(GPIOE,GPIO_Pin_8);//111
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
				break;
		case 1:	GPIO_ResetBits(GPIOE,GPIO_Pin_8);//000
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);
				break;
		default:break;
	}
}


