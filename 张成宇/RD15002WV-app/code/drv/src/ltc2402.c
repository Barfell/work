#include "ltc2402.h"
#include "spi.h"
#include "math.h"

#define LTC2402_CS_PORT     GPIOA
#define LTC2402_CS_PIN      GPIO_Pin_8

#define LTC2402_CS_Low()    GPIO_ResetBits(LTC2402_CS_PORT, LTC2402_CS_PIN)
#define LTC2402_CS_High()   GPIO_SetBits(LTC2402_CS_PORT, LTC2402_CS_PIN)

#define LTC2402_SWPOWER_RCC     RCC_AHB1Periph_GPIOC
#define LTC2402_SWPOWER_PORT    GPIOC
#define LTC2402_SWPOWER_PIN     GPIO_Pin_1
#define LTC2402_SWPOWER_Low()   GPIO_ResetBits(LTC2402_SWPOWER_PORT, LTC2402_SWPOWER_PIN)
#define LTC2402_SWPOWER_High()  GPIO_SetBits(LTC2402_SWPOWER_PORT, LTC2402_SWPOWER_PIN)

#define LTC2402_SWBIT0_RCC		RCC_AHB1Periph_GPIOE
#define LTC2402_SWBIT0_PORT     GPIOE
#define LTC2402_SWBIT0_PIN      GPIO_Pin_8
#define LTC2402_SWBIT0_Low()    GPIO_ResetBits(LTC2402_SWBIT0_PORT, LTC2402_SWBIT0_PIN)
#define LTC2402_SWBIT0_High()   GPIO_SetBits(LTC2402_SWBIT0_PORT, LTC2402_SWBIT0_PIN)

#define LTC2402_SWBIT1_RCC		RCC_AHB1Periph_GPIOC
#define LTC2402_SWBIT1_PORT     GPIOC
#define LTC2402_SWBIT1_PIN      GPIO_Pin_4
#define LTC2402_SWBIT1_Low()    GPIO_ResetBits(LTC2402_SWBIT1_PORT, LTC2402_SWBIT1_PIN)
#define LTC2402_SWBIT1_High()   GPIO_SetBits(LTC2402_SWBIT1_PORT, LTC2402_SWBIT1_PIN)

#define LTC2402_SWBIT2_RCC		RCC_AHB1Periph_GPIOC
#define LTC2402_SWBIT2_PORT     GPIOC
#define LTC2402_SWBIT2_PIN      GPIO_Pin_5
#define LTC2402_SWBIT2_Low()    GPIO_ResetBits(LTC2402_SWBIT2_PORT, LTC2402_SWBIT2_PIN)
#define LTC2402_SWBIT2_High()   GPIO_SetBits(LTC2402_SWBIT2_PORT, LTC2402_SWBIT2_PIN)
void LTC2402_SWitchInit(void)
{
    RCC_AHB1PeriphClockCmd(LTC2402_SWPOWER_RCC, ENABLE);
	GPIO_Set(LTC2402_SWPOWER_PORT, LTC2402_SWPOWER_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    LTC2402_SWPOWER_High();
    
	RCC_AHB1PeriphClockCmd(LTC2402_SWBIT0_RCC, ENABLE);
	GPIO_Set(LTC2402_SWBIT0_PORT, LTC2402_SWBIT0_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);

	RCC_AHB1PeriphClockCmd(LTC2402_SWBIT1_RCC, ENABLE);
	GPIO_Set(LTC2402_SWBIT1_PORT, LTC2402_SWBIT1_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);

	RCC_AHB1PeriphClockCmd(LTC2402_SWBIT2_RCC, ENABLE);
	GPIO_Set(LTC2402_SWBIT2_PORT, LTC2402_SWBIT2_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);

	LTC2402_SWBIT0_Low();
	LTC2402_SWBIT1_Low();
	LTC2402_SWBIT2_Low();

}

/*************************************/
#define LTC2402_ReferenceResistance     19600.0
#define LTC2402_ReferenceVoltage        4.99
#define LTC2402_ConvertDelay()          DelayMs(200)
/*************************************/
/**
 * @brief	use this function need 400ms once.
 * @return  return the resistance of measured.
 */
double LTC2402_GetResistance(void)
{
    u8 u8resbuf[4] = {0,};
    u8 EOC = 3;
    u32 u32resbuf = 0;
    double convertionresult = 0;
	double current = 0;
	double RES = 0;
	double ch1 = 0;
	double ch0 = 0;
	u8 i = 0;
    /*Get ch0 and ch1 convertion result*/
    for(i = 0;i < 2;i++)
    {
    	EOC = LTC2402_TEST_EOC();
	    if((EOC & 0x80) == 0)
    	{
			u8resbuf[0] = EOC;
	        u8resbuf[1] = LTC2402_ReadByte();
	        u8resbuf[2] = LTC2402_ReadByte();
	        u8resbuf[3] = LTC2402_ReadByte();
            
             /*Get LTC2402 convertion result*/
			u32resbuf = ((u8resbuf[0]<<24)+(u8resbuf[1]<<16)+(u8resbuf[2]<<8)+(u8resbuf[3]<<0));
	        u32resbuf = u32resbuf&0x0FFFFFF0;           
	        u32resbuf = u32resbuf >>4;
			convertionresult = (((double)u32resbuf)/16777216.0)*LTC2402_ReferenceVoltage;
            
			if(EOC & 0x40)/*channel 1 */
			{           
//				printf("Channe1 Ltc2402buf = 0X%X\r\n",u32resbuf);
//				printf("Channe1 resulf = %.6f\r\n",convertionresult);
                ch1 = convertionresult;
                /*ch1 always is 0*/
				ch1=0;       
			}
			else/*channel 0 */
			{
//				printf("Channe0 Ltc2402buf = 0X%X\r\n",u32resbuf);
//				printf("Channe0 resulf = %.6f\r\n",convertionresult);
				ch0 = convertionresult;			
			}				
			u8resbuf[0] = 0;
			u8resbuf[1] = 0;
			u8resbuf[2] = 0;
			u8resbuf[3] = 0;
    	}
    }
    if(ch0 > ch1)
    {
    	RES = ch0 - ch1;
//		printf("offset = %.6f\r\n",(ch0 - ch1));
    }
	else
	{
		RES = ch1 - ch0;
//		printf("offset = %.6f\r\n",(ch1 - ch0));
	}
    /* Get LTC2402 convertion currents */
	current = (LTC2402_ReferenceVoltage - RES)/LTC2402_ReferenceResistance;
    
	RES = RES/current;
    
    return RES;    
}
/**
 * @brief	switch measure channel
 * @param u8channel: 1~8 
 */
void LTC2402_SwitchChannel(u8 u8channel)
{
    switch(u8channel)
    {
    	case 1:
	    	LTC2402_SWBIT0_Low();
	    	LTC2402_SWBIT1_Low();
	    	LTC2402_SWBIT2_Low();
    	break;
    	case 2:
    		LTC2402_SWBIT0_High();
	    	LTC2402_SWBIT1_Low();
	    	LTC2402_SWBIT2_Low();
    	break;
    	case 3:
    		LTC2402_SWBIT0_Low();
	    	LTC2402_SWBIT1_High();
	    	LTC2402_SWBIT2_Low();
    	break;
    	case 4:
    		LTC2402_SWBIT0_High();
	    	LTC2402_SWBIT1_High();
	    	LTC2402_SWBIT2_Low();
    	break;
    	case 5:
    		LTC2402_SWBIT0_Low();
	    	LTC2402_SWBIT1_Low();
	    	LTC2402_SWBIT2_High();
    	break;
    	case 6:
    		LTC2402_SWBIT0_High();
	    	LTC2402_SWBIT1_Low();
	    	LTC2402_SWBIT2_High();
    	break;
    	case 7:
    		LTC2402_SWBIT0_Low();
	    	LTC2402_SWBIT1_High();
	    	LTC2402_SWBIT2_High();
    	break;
    	case 8:
    		LTC2402_SWBIT0_High();
	    	LTC2402_SWBIT1_High();
	    	LTC2402_SWBIT2_High();
    	break;
    	default:
    	break;
    }
    DelayMs(15);
}
/**
 * @brief	EOC is HIGH during the conversion and goes LOW when the conversion is complete.
 * @return  return the EOC value of LTC2402.
 */
u8 LTC2402_TEST_EOC(void)
{
    LTC2402_ConvertDelay();
	return LTC2402_ReadByte();
}
/**
 * @brief	Read LTC2402 return AD value
 * @return  return LTC2402 conversion value.
 */
u8 LTC2402_ReadByte(void)
{
	U8 u8Value;
	u8Value = SPI1_ReadWriteByte(0XFF);    
	return u8Value;
}
/**
 * @brief	Initialize SPI1 and CS choose LTC2402. 
 */
void LTC2402Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
    GPIO_Set(LTC2402_CS_PORT, LTC2402_CS_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    
    LTC2402_CS_Low();
    
    SPI1_Init();
    
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);
    
    DelayMs(200);  
    
}

#define LTC2402_READTIMES 10
#define LTC2402_LOSTIMES 3
/**
 * @brief	Measure LTC2402_READTIMES times and give up LTC2402_LOSTIMES*2 value then calc the remind value average.
 * @note	The function use (200*LTC2402_READTIMES)ms time delay necessary. 
 * @return	Return the average value 
 */
double LTC2402_GetAverageResistance(void)
{
    u8 i = 0;
    u8 j = 0;
    double sum = 0;
    double temp = 0;
    double Res[LTC2402_READTIMES];
    
    for(i=0;i < LTC2402_READTIMES;i++)
    {
        /*Get Resistance value from LTC2402*/
        Res[i] = LTC2402_GetResistance();
    }
	for(i=0;i < LTC2402_READTIMES - 1;i++)
	{
		for( j = i+1; j < LTC2402_READTIMES; j++ )
		{
			if(Res[i]>Res[j])
			{
				temp = Res[i];
				Res[i] = Res[j];
				Res[j] = temp;
			}
		}
	}	
    
	for(i = LTC2402_LOSTIMES;i < LTC2402_READTIMES-LTC2402_LOSTIMES; i++)
    {
        sum += Res[i];
    }
	temp = sum/(LTC2402_READTIMES-2*LTC2402_LOSTIMES);
    
    return temp;
}

/*Use PT100 Temperature Sensor,Zero Temperatute is 100R and PT1000 is 1000R*/
#define PT_ZeroTemRes    100
#define PT_A 	3.9083e-3
#define PT_B    -5.775e-7
#define PT_C    -4.183e-12
#define PT_Min	5
#define PT_Max	200
/**
 * @brief	Calc temperature through PT Resistance
 * @note 	Use PT_Min adn PT_Max limit Resistance value
 * @param  	PTRes: The PT Resistance value 
 * @return 	Temperature sensor value 
 */
double GetPTTemperature(double PTRes)
{
	double fTem;
	if(PTRes>PT_Min && PTRes < PT_Max)
	{
		fTem = (sqrt((PT_A*PT_ZeroTemRes)*(PT_A*PT_ZeroTemRes)-4*PT_B*PT_ZeroTemRes*(PT_ZeroTemRes-PTRes))-PT_A*PT_ZeroTemRes)/2/PT_B/PT_ZeroTemRes;
		//printf("PT  Temperature is %.6f\r\n",fTem);
		printf(" %.6f\r\n",fTem);
	}else
	{
		printf("Get resistance Error\r\n");
	}
	return(fTem);
}

/*Use NTC3K	GLW8000 Temperature Sensor ,25 Temperature is 3000R*/
#define	NTC_A	1.4051e-3
#define NTC_B	2.369e-4
#define NTC_C	1.019e-7
#define NTC_Min	250
#define	NTC_Max 100000
/**
 * @brief	Calc temperature through NTC Resistance
 * @note 	Use NTC_Min adn NTC_Max limit Resistance value
 * @param  	NTCRes: The NTC Resistance value 
 * @return 	Temperature sensor value 
 */
double GetNTCTemperature(double NTCRes)
{
	double fTem;
	if(NTCRes>PT_Min && NTCRes < PT_Max)
	{
		fTem = (sqrt((PT_A*PT_ZeroTemRes)*(PT_A*PT_ZeroTemRes)-4*PT_B*PT_ZeroTemRes*(PT_ZeroTemRes-NTCRes))-PT_A*PT_ZeroTemRes)/2/PT_B/PT_ZeroTemRes;
		//printf("PT  Temperature is %.6f\r\n",fTem);
		printf(" %.6f\r\n",fTem);
	}
	else if(NTCRes>NTC_Min && NTCRes < NTC_Max)
	{
		fTem = (1/((NTC_A) + (NTC_B*(log(NTCRes))) + (NTC_C*(log(NTCRes))*(log(NTCRes))*(log(NTCRes))))) - 273.2;
		//printf("NTC Temperature is %.6f\r\n",fTem);
		printf(" %.6f\r\n",fTem);
	}
	else
	{
		printf("Get resistance Error\r\n");
	}
	
	return(fTem);
}

