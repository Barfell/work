#include "ads1248.h"
#include "spi.h"
#include "tsa5017.h"
#include "math.h"

#define RCC_ADS1248_CONFIG()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#define ADS1248_RST_GPIO			GPIOB
#define ADS1248_RST_PIN				GPIO_Pin_4
#define ADS1248_START_GPIO			GPIOA
#define ADS1248_START_PIN			GPIO_Pin_12

#define ADS1248_CS1_GPIO			GPIOA
#define ADS1248_CS1_PIN				GPIO_Pin_4
#define ADS1248_CS2_GPIO			GPIOB
#define ADS1248_CS2_PIN				GPIO_Pin_7
#define ADS1248_CS3_GPIO			GPIOB
#define ADS1248_CS3_PIN				GPIO_Pin_6
#define ADS1248_CS4_GPIO			GPIOB
#define ADS1248_CS4_PIN				GPIO_Pin_5

#define ADS1248_CS1_L()				GPIO_ResetBits(ADS1248_CS1_GPIO, ADS1248_CS1_PIN);DelayUs_Sft(5)
#define ADS1248_CS1_H()				GPIO_SetBits(ADS1248_CS1_GPIO, ADS1248_CS1_PIN)
#define ADS1248_CS2_L()				GPIO_ResetBits(ADS1248_CS2_GPIO, ADS1248_CS2_PIN)
#define ADS1248_CS2_H()				GPIO_SetBits(ADS1248_CS2_GPIO, ADS1248_CS2_PIN)
#define ADS1248_CS3_L()				GPIO_ResetBits(ADS1248_CS3_GPIO, ADS1248_CS3_PIN)
#define ADS1248_CS3_H()				GPIO_SetBits(ADS1248_CS3_GPIO, ADS1248_CS3_PIN)
#define ADS1248_CS4_L()				GPIO_ResetBits(ADS1248_CS1_GPIO, ADS1248_CS4_PIN)
#define ADS1248_CS4_H()				GPIO_SetBits(ADS1248_CS1_GPIO, ADS1248_CS4_PIN)


#define ADS1248_RDY_GPIO			GPIOA
#define ADS1248_RDY_PIN				GPIO_Pin_11
#define ADS1248_AD12V_GPIO			GPIOA				//电源检测
#define ADS1248_AD12V_PIN			GPIO_Pin_1			//电源检测

#define ADS1248_RESET_L()			GPIO_ResetBits(ADS1248_RST_GPIO, ADS1248_RST_PIN)
#define ADS1248_RESET_H()			GPIO_SetBits(ADS1248_RST_GPIO, ADS1248_RST_PIN)
#define ADS1248_START_L()			GPIO_ResetBits(ADS1248_START_GPIO, ADS1248_START_PIN)
#define ADS1248_START_H()			GPIO_SetBits(ADS1248_START_GPIO, ADS1248_START_PIN)

#define ADC_READ_RDY_STATE			GPIO_ReadInputDataBit(ADS1248_RDY_GPIO, ADS1248_RDY_PIN)			

STATIC U8 drdy_isr_flag = 0;
// function prototype
VOID ADS1248_WriteByte(U8 u8Value)
{
	ADS1248_CS1_L();
	SpiReadWriteByte(ADS1248_SPI, u8Value);
	ADS1248_CS1_H();
}


U8 ADS1248_ReadByte(VOID)
{
	U8 u8Value;
	ADS1248_CS1_L();
	u8Value = SpiReadWriteByte(ADS1248_SPI, 0XFF);
	ADS1248_CS1_H();
	return u8Value;
}

VOID ADS_SetIdac(U8 idac1_ch, U8 idac2_ch, U8 idac_mag)
{
	ADS1248_WriteByte(ADS_WREG|ADS_IDAC0);  // the first register:ADS_IDAC0
   	ADS1248_WriteByte(1);  					// write two bytes
   	ADS1248_WriteByte(idac_mag); 			// IDACs current
   	ADS1248_WriteByte(idac1_ch|idac2_ch);  	
}

VOID ADS_SetPGAGain(U8 pag_gain, U8 data_rate)
{
	ADS1248_WriteByte(ADS_WREG|ADS_SYS0);
	ADS1248_WriteByte(0);  		// write a byte
	ADS1248_WriteByte(pag_gain|data_rate);  
}


U32 ADS_DataReadOnce(VOID)
{
	 U32 dat_ads = 0;
	 U8 temp[3] = {0};
	 ADS1248_WriteByte(ADS_RDATA);
	 temp[0] = ADS1248_ReadByte();
	 //dat_ads = temp;
	 //dat_ads <<= 8;
	 temp[1] = ADS1248_ReadByte();
	 //dat_ads += temp;
	 //dat_ads <<= 8;
	 temp[2] = ADS1248_ReadByte();
	 //dat_ads += temp;
	 dat_ads = temp[0]*65536+temp[1]*256+temp[2];
	 //dat_ads = temp[0]*256+temp[1];
	 /*for(i=0;i<24;i++)
	 {
	 	ADS_SCLK = 1;
		dat_ads <<= 1;
		NOP();
		NOP();
		if(ADS_DOUT == 1)
			dat_ads |= 0x00000001;
		NOP();
		NOP();
		ADS_SCLK = 0;
		NOP();
		NOP();
	 } */
	 return dat_ads;
}

U32 ADS_DataReadCotinu(VOID)
{
	 U32 dat_ads = 0;
	 drdy_isr_flag = 0;
	 while(drdy_isr_flag != 1)  { ;}    // 等待转换结束

	 ADS1248_WriteByte(ADS_RDATAC);

	 drdy_isr_flag = 0;
	 while(drdy_isr_flag != 1)  { ;}    // 等待转换结束
	 //temp[0] = ADS1248_ReadByte();
	 //dat_ads = temp;
	 //dat_ads <<= 8;
	 //temp[1] = ADS1248_ReadByte();
	 //dat_ads += temp;
	 //dat_ads <<= 8;
	 //temp[2] = ADS1248_ReadByte();
	 //dat_ads += temp;
	 //dat_ads = temp[0]*65536+temp[1]*256+temp[2];
	 
//	 for(i=0;i<24;i++)
//	 {
//	 	ADS_SCLK = 1;
//		dat_ads <<= 1;
//		NOP();
//		NOP();
//		if(ADS_DOUT == 1)
//			dat_ads |= 0x00000001;
//		NOP();
//		NOP();
//		ADS_SCLK = 0;
//		NOP();
//		NOP();
//	 } 
	 return dat_ads;
}
/*
 * 函数名：ADS1248_WriteReg
 * 描述  ：写ADS1248的寄存器
 * 输入  ： RegAddr 寄存器起始地址
 *   *Buffer 存放待写入数据的指针
 *   length 数据字节数
 * 输出  ：无
 * 返回  ：无
 */
VOID ADS1248_WriteReg(U8 RegAddr, U8 *Buffer, U8 u8Length)
{
	U8 szCmd[2], u8Count;
	ADS1248_CS1_L();
	szCmd[0] = ADS_WREG | RegAddr;
	szCmd[1] = u8Length - 1;
	SpiReadWriteByte(ADS1248_SPI, szCmd[0]);
	SpiReadWriteByte(ADS1248_SPI, szCmd[1]);
	for(u8Count = 0; u8Count < u8Length; u8Count++)
	{
		SpiReadWriteByte(ADS1248_SPI, *(Buffer + u8Count));
	}
	szCmd[0] = ADS_NOP;  //发一条空操作，保证上条指令被从机读走
	SpiReadWriteByte(ADS1248_SPI, szCmd[0]);
	ADS1248_CS1_H();
}
VOID ADS1248_ReadReg(U8 RegAddr, U8 *Buffer,U8 u8Length)  
{  
	U8 szCmd[2], u8Count;  
	ADS1248_CS1_L();
	szCmd[0] = ADS_RREG | RegAddr;  
	szCmd[1] = u8Length - 1;  
	SpiReadWriteByte(ADS1248_SPI, szCmd[0]);
	SpiReadWriteByte(ADS1248_SPI, szCmd[1]);
	for(u8Count = 0; u8Count < u8Length; u8Count++)
	{
		*(Buffer + u8Count) = SpiReadWriteByte(ADS1248_SPI, 0XFF);
	}	 
//	szCmd[0] = ADS_NOP;  
//	SpiReadWriteByte(ADS1248_SPI, szCmd[0]);
//	u8Count = ADS1248_ReadByte();
//	printf("ReadReg 0xff: %d\r\n",u8Count);	
	ADS1248_CS1_H();  
} 
/*--------------------------------------------------------- 
  忙状态判断，最长等待时间，200 X 10 ms=2S 
---------------------------------------------------------*/  
U8 ADS1248_WaitBusy()  
{  
    U16 u16Count;  
    ADS1248_CS1_L();  
    u16Count = 0;  
    while(ADC_READ_RDY_STATE > 0)
	{  
		DelayMs(10);  
		u16Count++; 
		if(u16Count>200)
			return 1;  
	}  
	ADS1248_CS1_H();  
	return 0;  
} 
/*--------------------------------------------------------- 
 执行校准---系统校准->偏移校准->增益校准 
---------------------------------------------------------*/  
U8 ADS1248_Calibrate(U8 Gain)  
{  
    U8 R=0, Cmd;  
    ADS1248_WriteReg(ADS_SYS0, &Gain, 1);     //设置校准增益  
  
    Cmd=0x00;  
    ADS1248_WriteReg(ADS_MUX1,&Cmd,1);       //恢复正常模式  
    ADS1248_WriteByte(ADS_SYSOCAL);     			//系统偏移自校准  
    R|=ADS1248_WaitBusy();              		//等待校准完成  
  
    Cmd=0x01;  
    ADS1248_WriteReg(ADS_MUX1,&Cmd,1);       //设置AINP+AINN=(AVDD+AVSS)/2   
    ADS1248_WriteByte(ADS_SYSOCAL);      	//系统偏移自校准  
    R|=ADS1248_WaitBusy();              		//等待校准完成  
  
    Cmd=0x02;  
    ADS1248_WriteReg(ADS_MUX1,&Cmd,1);       //设置AINP=VREF+,AINN=VREF-; for gain calibration  
    ADS1248_WriteByte(ADS_SYSGCAL);      		//系统增益校准  
    R|=ADS1248_WaitBusy();                        
  
    return R;  
}  
VOID ADS1248_Init(VOID)
{
	U8 szCmd[2] = {0};

	RCC_ADS1248_CONFIG();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);
	GPIO_Set(ADS1248_RST_GPIO, ADS1248_RST_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_CS1_GPIO, ADS1248_CS1_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_CS2_GPIO, ADS1248_CS1_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_CS3_GPIO, ADS1248_CS1_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_CS4_GPIO, ADS1248_CS1_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_START_GPIO, ADS1248_START_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GPIO_Set(ADS1248_RDY_GPIO, ADS1248_RDY_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	ADS1248_RESET_L();
	DelayMs_Sft(50);
	ADS1248_RESET_H();
	DelayMs_Sft(50);
	ADS1248_START_H();  // continuously  为了保险起见，操作寄存器一直让START为高。
	
	ADS1248_WriteReg(ADS_WAKEUP, szCmd, 0); // the first register:	ADS_WAKEUP
	DelayMs(100);
	
	szCmd[0] = 0x13;//ch4:0x37 ch3 :0x25  ch2:0x13  ch1: 0x01//输入引脚
	ADS1248_WriteReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	
	szCmd[0] = CLK_Inter|REF_Inter;// internal oscillator in use, internal reference selected;
	ADS1248_WriteReg(ADS_MUX1, szCmd, 1); // the first register:	ADS_MUX1
	DelayMs(100);
	szCmd[0] = PGAGain_16|DataRate_40; 	// PGA gain = 16, data rate = 40SPS;
	ADS1248_WriteReg(ADS_SYS0, szCmd, 1); // the first register:	ADS_SYS0

	szCmd[0] = IMAG_500;//IMAG_500
	ADS1248_WriteReg(ADS_IDAC0, szCmd, 1);// the first register:ADS_IDAC0  
	
	szCmd[0] = 0x8b;						//设置两路输出0x8b
	ADS1248_WriteReg(ADS_IDAC1, szCmd, 1);// the first register:ADS_IDAC1

} 

#define A 3.9083e-3
#define B -5.775e-7
#define C -4.183e-12
#define READTIMES 		30 		//读取次数
#define LOSTVALUE		5	  	//丢弃值

//铂电阻的阻值随温度的变化而变化的计算公式：
//-200<t<0℃ Rt=R0[1+At+Bt*t+C(t-100)t*t*t] （1）
//0≤t<850℃ Rt=R0（1+At+Bt2） （2）
//Rt为t℃时的电阻值，R0为0℃时的阻值。公式中的A,B,系数为实验测定。这里给出标准的
//DIN IEC751系数：A=3.9083E-3、 B=-5.775E-7、 C=-4.183E-12
//根据韦达公式求得阻值大于等于100欧姆的Rt -〉t的换算公式：
//0≤t<850℃ t=(sqrt((A*R0)^2-4*B*R0*(R0-Rt))-A*R0)/2/B/R0
STATIC double Pt100(double PT100Res)
{
//	double fT,fR,fT0;
	double fT;
//	u8 i;
//	fR = PT100Res;
//	fT0 = (fR/100 - 1)/A;
//	for(i=0;i<50;i++)
//	{
//		fT = fT0 + (fR - 100*(1+A*fT0 + B*fT0*fT0))/(100*(A + 2*B*fT0));
//		if(fabs(fT - fT0)<0.001) break;
//		else(fT = fT0);
//	}	
	fT=(sqrt((A*100)*(A*100)-4*B*100*(100-PT100Res))-A*100)/2/B/100;
	return(fT);
}

VOID PT100TempProcess(U8 u8Channel, float *PT100Res,U8 *pADS_MUX0, double *pPT100Temp)
{
	double PT100Temp;
	U32 u32Value[READTIMES];
	double Voltage[READTIMES];
	double temp,sum;
	u32 i,j,k;
	u8 szCmd[2] = {0};
	switch(u8Channel)
	{
		case 1: Tsa5017_CH1();
				break;
		case 2: Tsa5017_CH2();
				break;
		case 3: Tsa5017_CH3();
				break;
		case 4: Tsa5017_CH4();
				break;
	}
	DelayMs(50);
	ADS1248_ReadReg(ADS_MUX0, szCmd, 1); // the first register:	ADS_MUX0
	*pADS_MUX0 = szCmd[0];
	for(i = 0;i<READTIMES;i++)
	{
	u32Value[i] = ADS_DataReadOnce();
	DelayMs(5);
	Voltage[i] = ((double)u32Value[i])*(2.048/8388608/16);//16777216
	for(k = 0;k<500;k++)
		{
			k = k;
		}	
	}
	for(i=0;i < READTIMES - 1;i++)//排序
	{
		for(j=i+1;j<READTIMES;j++)
		{
			if(Voltage[i]>Voltage[j])//升序排列
			{
				temp = Voltage[i];
				Voltage[i] = Voltage[j];
				Voltage[j] = temp;
			}
		}
	}	
	sum = 0; 	
	for(i=LOSTVALUE;i<READTIMES-LOSTVALUE;i++)sum+=Voltage[i];
	temp=sum/(READTIMES-2*LOSTVALUE);
	*PT100Res = temp/0.0005;	
	PT100Temp = Pt100(*PT100Res);
//	PT100Temp = (PT100Res - 100)/0.385;
	*pPT100Temp = PT100Temp;
}
