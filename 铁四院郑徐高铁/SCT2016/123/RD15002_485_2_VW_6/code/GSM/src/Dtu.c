#include "includes.h"

#define RCC_DTU_CONFIG()		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//DTU( ONOFF-PE2 DCD-PE3)
//POWER  PE4
#define DTU_PWR_GPIO			GPIOE
#define DTU_PWR_PIN				GPIO_Pin_4

#define DTU_ON_OFF_GPIO			GPIOE
#define DTU_ON_OFF_PIN			GPIO_Pin_2

#define DTU_DCD_GPIO			GPIOE
#define DTU_DCD_PIN				GPIO_Pin_3


VOID DtuInit(VOID)
{    	 
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//DTU( ONOFF-PE2 DCD-PE3)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);//用于OPPP拨号，透传功能下，判断模块处于数据态还是命令态，高：命令态，低：数据态
	
	DtuPwrOn();

	DtuOn();
}

VOID DtuPwrOn(VOID)
{
    GPIO_SetBits(DTU_PWR_GPIO, DTU_PWR_PIN);
}

VOID DtuPwrOff(VOID)
{
    GPIO_ResetBits(DTU_PWR_GPIO, DTU_PWR_PIN);
}

VOID DtuOn(VOID)
{
    GPIO_ResetBits(DTU_ON_OFF_GPIO, DTU_ON_OFF_PIN);
}

VOID DtuOff(VOID)
{
    GPIO_SetBits(DTU_ON_OFF_GPIO, DTU_ON_OFF_PIN);
}

BOOL DetectOnline(VOID)
{
	BOOL bRet = FALSE;
	if(GPIO_ReadInputDataBit(DTU_DCD_GPIO, DTU_DCD_PIN) == 1)
	{
		bRet = TRUE;
	}
	return bRet;  //修改测试用
}


