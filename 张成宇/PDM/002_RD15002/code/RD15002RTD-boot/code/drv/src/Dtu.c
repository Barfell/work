#include "Dtu.h" 

#define RCC_DTU_CONFIG()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE),RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define DTU_PWR_GPIO			GPIOA
#define DTU_PWR_PIN				GPIO_Pin_0
#define DTU_ON_OFF_GPIO			GPIOB
#define DTU_ON_OFF_PIN			GPIO_Pin_3
#define DTU_DCD_GPIO			GPIOA
#define DTU_DCD_PIN				GPIO_Pin_15


VOID DtuInit(VOID)
{    	 
	RCC_DTU_CONFIG();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //����AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //��ֹJTAG����
	
	GPIO_Set(DTU_PWR_GPIO, DTU_PWR_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	
	GPIO_Set(DTU_ON_OFF_GPIO, DTU_ON_OFF_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	
	GPIO_Set(DTU_DCD_GPIO, DTU_DCD_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);//����OPPP���ţ�͸�������£��ж�ģ�鴦������̬��������̬���ߣ�����̬���ͣ�����̬
	
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
	return bRet;
}


