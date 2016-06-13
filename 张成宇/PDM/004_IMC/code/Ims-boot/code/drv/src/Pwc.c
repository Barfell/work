#include "Pwc.h" 

#define RCC_PWC_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define PWC_GPIO			GPIOB
#define PWC_PIN				GPIO_Pin_1


#define RCC_LED_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define LED_GPIO			GPIOA
#define LED_PIN				GPIO_Pin_8



#define RCC_KEY_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define KEY_GPIO			GPIOA
#define KEY_PIN				GPIO_Pin_11

#define RCC_PWRCTRL_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define PWRCTRL_GPIO			GPIOA
#define PWRCTRL_PIN				GPIO_Pin_12

#define RCC_PWR_CONFIG()	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define PWR_GPIO			GPIOB
#define PWR_PIN				GPIO_Pin_6


#define READ_KEY_STATE 		GPIO_ReadInputDataBit(KEY_GPIO, KEY_PIN)
#define READ_PWR_STATE 		GPIO_ReadInputDataBit(PWR_GPIO, PWR_PIN)


VOID LEDOff(VOID)
{
    GPIO_ResetBits(LED_GPIO, LED_PIN);
}

VOID LEDOn(VOID)
{
    GPIO_SetBits(LED_GPIO, LED_PIN);
}

VOID PWCOff(VOID)
{
	
    GPIO_ResetBits(PWC_GPIO, PWC_PIN);
}

VOID PWCOn(VOID)
{
    GPIO_SetBits(PWC_GPIO, PWC_PIN);
}

VOID PWRCTRLOff(VOID)
{
    GPIO_ResetBits(PWRCTRL_GPIO, PWRCTRL_PIN);
}

VOID PWRCTRLOn(VOID)
{
    GPIO_SetBits(PWRCTRL_GPIO, PWRCTRL_PIN);
}

VOID PWCInit(VOID)
{    	 
	RCC_PWC_CONFIG();
	RCC_LED_CONFIG();
	RCC_KEY_CONFIG();
	RCC_PWR_CONFIG();
	RCC_PWRCTRL_CONFIG();
	
	GPIO_Set(PWC_GPIO, PWC_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(LED_GPIO, LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(PWRCTRL_GPIO, PWRCTRL_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	
	GPIO_Set(KEY_GPIO, KEY_PIN, GPIO_Mode_IPD, GPIO_Speed_50MHz);
	GPIO_Set(PWR_GPIO, PWR_PIN, GPIO_Mode_IPD, GPIO_Speed_50MHz);

	
	PWCOn();
	LEDOn();
	PWRCTRLOn();
}



VOID ResetIpc(VOID)
{
	PWCOff();
	
	DelayMs_Sft(2000);
	
	PWCOn();
}

STATIC U16 g_u16KeyCount = 0;
STATIC U16 g_u16SystemCount = 0;
STATIC BOOL g_bStart = FALSE;
STATIC BOOL g_bClose = TRUE;
STATIC BOOL g_bJudge = FALSE;
VOID KeyThreadProc(VOID)
{
	if(g_u16KeyCount < 3000)
	{
		if(READ_KEY_STATE == Bit_SET)
		{
			g_u16KeyCount++;
			if((g_bStart == TRUE) && (g_bJudge == TRUE))
			{
				if(g_u16KeyCount > 200)
				{
					PWCOn();
					LEDOn();
					PWRCTRLOn();
					g_bStart = FALSE;
					g_bClose = TRUE;
					g_bJudge = FALSE;
					g_u16KeyCount = 0;
				}
				
			}
		}
		else
		{
			g_bJudge = TRUE;
			g_u16KeyCount = 0;
		}
	}
	else
	{
		if((g_bClose == TRUE) && (g_bJudge == TRUE))
		{
			PWCOff();
			LEDOff();
			g_bClose = FALSE;
			g_bStart = TRUE;
			g_bJudge = FALSE;
			
		}
		g_u16KeyCount = 0;
	}
	
	if(g_u16SystemCount < 2500)
	{
		if(READ_PWR_STATE == Bit_SET)
		{
			g_u16SystemCount++;
		}
		else
		{
			g_u16SystemCount = 0;
		}
	}
	else
	{
		PWCOff();
		LEDOff();
		g_bStart = FALSE;
		g_u16SystemCount = 0;
	}
}

