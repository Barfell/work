#include "Tsa5017.h" 
#include "ads1248.h"
#define RCC_TSA5017_CONFIG()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define TSA5017_GPIO				GPIOB
#define TSA5017_SEL1_PIN			GPIO_Pin_0
#define TSA5017_SEL0_PIN			GPIO_Pin_1

VOID Tsa5017Init(VOID)
{    	 
	RCC_TSA5017_CONFIG();
	
	GPIO_Set(TSA5017_GPIO, TSA5017_SEL1_PIN | TSA5017_SEL0_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL1_PIN);//default CH1
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL0_PIN);
}
void Tsa5017_CH1(void)
{
	U8 szCmd[2] = {0};
	szCmd[0] = 1;//ch4:0x37 ch3 :0x25  ch2:0x13  ch1: 0x01//输入引脚
	ADS1248_WriteReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL1_PIN);
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL0_PIN);
	DelayMs(100);
}
void Tsa5017_CH2(void)
{
	U8 szCmd[2] = {0};
	szCmd[0] = 0x25;//ch4:0x37 ch3 :0x25  ch2:0x13  ch1: 0x01//输入引脚
	ADS1248_WriteReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	GPIO_SetBits(TSA5017_GPIO,TSA5017_SEL0_PIN);	
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL1_PIN);
	DelayMs(100);
}
void Tsa5017_CH3(void)
{
	U8 szCmd[2] = {0};
	szCmd[0] = 0x37;//ch4:0x37 ch3 :0x25  ch2:0x13  ch1: 0x01//输入引脚
	ADS1248_WriteReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	GPIO_ResetBits(TSA5017_GPIO,TSA5017_SEL0_PIN);
	GPIO_SetBits(TSA5017_GPIO,TSA5017_SEL1_PIN);
	DelayMs(100);
}
void Tsa5017_CH4(void)
{
	U8 szCmd[2] = {0};
	szCmd[0] = 0x13;//ch4:0x37 ch3 :0x25  ch2:0x13  ch1: 0x01//输入引脚
	ADS1248_WriteReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	GPIO_SetBits(TSA5017_GPIO,TSA5017_SEL1_PIN);
	GPIO_SetBits(TSA5017_GPIO,TSA5017_SEL0_PIN);
	DelayMs(100);
}


