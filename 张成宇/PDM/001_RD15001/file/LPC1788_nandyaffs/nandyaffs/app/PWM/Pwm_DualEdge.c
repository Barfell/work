/***********************************************************************//**
 * @file		Pwm_DualEdge.c
 * @purpose		This program illustrates the PWM signal on 6 Channels in
 * 			  	both edge mode and single mode.
 * @version		2.0
 **********************************************************************/
#include "lpc177x_8x_pwm.h"
#include "lpc177x_8x_pinsel.h"
#include "bsp.h"

#define _USING_PWM_NO					0


/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main PWM program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int Pwm_Test_Beep(void)
{
//	uint8_t pwmChannel;
	PWM_TIMERCFG_Type PWMCfgDat;
	PWM_MATCHCFG_Type PWMMatchCfgDat;

	/* PWM block section -------------------------------------------- */
	/* Initialize PWM peripheral, timer mode
	 * PWM prescale value = 1 (absolute value - tick value) */
	PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;
	PWMCfgDat.PrescaleValue = 1;
	PWM_Init(_USING_PWM_NO, PWM_MODE_TIMER, (void *) &PWMCfgDat);

	// Initialize PWM pin connect
	PINSEL_ConfigPin (1, 11, 3);//PWM0.6


	/* Set match value for PWM match channel 0 = 1000, update immediately */
	PWM_MatchUpdate(_USING_PWM_NO, 0, 1000, PWM_MATCH_UPDATE_NOW);

	/* PWM Timer/Counter will be reset when channel 0 matching
	 * no interrupt when match
	 * no stop when match */
	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = 0;
	PWMMatchCfgDat.ResetOnMatch = ENABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(_USING_PWM_NO, &PWMMatchCfgDat);

	/* Edge setting ------------------------------------ */
	PWM_ChannelConfig(_USING_PWM_NO, 6, PWM_CHANNEL_SINGLE_EDGE);

	/* Match value setting ------------------------------------ */
	PWM_MatchUpdate(_USING_PWM_NO, 6, 500, PWM_MATCH_UPDATE_NOW);

	/* Enable PWM Channel Output ------------------------------------ */
	/* Channel 6 */
	PWM_ChannelCmd(_USING_PWM_NO, 6, ENABLE);

	/* Reset and Start counter */
	PWM_ResetCounter(_USING_PWM_NO);

	PWM_CounterCmd(_USING_PWM_NO, ENABLE);

	/* Start PWM now */
	PWM_Cmd(_USING_PWM_NO, ENABLE);

    /* Loop forever */
    return 1;
}

void Pwm_change_Freq(uint8_t state){
	static uint32_t freq = 1000; //dafault 1KHz
	if(state == 1)				 //减小输出频率
	  freq += 50;
	else						 //增大输出频率
	  freq -= 50;
	
	if(freq >50000 || freq < 50)
		return ;

	/* Set match value for PWM match channel 0 = 1000, update immediately */
	PWM_MatchUpdate(_USING_PWM_NO, 0, freq, PWM_MATCH_UPDATE_NOW);

	/* Match value setting ------------------------------------ */
	PWM_MatchUpdate(_USING_PWM_NO, 6, freq/2, PWM_MATCH_UPDATE_NOW);
		

}
/*disable pwm , timer counter*/
void Pwm_Dis_Beep(void){
	PWM_Cmd(_USING_PWM_NO, DISABLE);
	PWM_CounterCmd(_USING_PWM_NO, DISABLE);
	PWM_ChannelCmd(_USING_PWM_NO, 6, DISABLE);
}
