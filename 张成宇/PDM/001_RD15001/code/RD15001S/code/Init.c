#include <c8051f340.h>
#include <intrins.h> 
#include "uart.h" 
#include "Init.h"
/*********************************************
         	��������
*********************************************/ 	 
static U32 xdata g_u32Tick = 0;  //1ms  
 /*********************************************
         ��ʱ��2����
*********************************************/ 
void timer2_init()							// init timer2 as the system tick timer
{
	TMR2CN    = 0x04;
	TMR2RLH   =0xf0; TMR2RLL   = 0x5f; 	 	//1ms��1kHZ 						// 16bit reload timer,sysclk/12 as clk. enable��1ms every cycle; timer clock = 48MHz/12 = 4MHz; reload reg =0xffff - 4000 = 0xf05f;
	IE       |= 0x20; 						//enable interrupt
	ET2       = 1;
}

void timer2_isr(void) interrupt 5  	//25ms interrupt
{
	TF2H = 0;						//clearn interrupt
	g_u32Tick++;
}

U32 GetTickCount(void)
{
	return 	g_u32Tick;
}

/*********************************************
			VDD������ʹ�� 
*********************************************/ 
// reset something	 
void reset_sources_init()
{
    int i 	  = 0;
    VDM0CN    = 0x80;				// ���縴λ/VDD������ʹ��
    for (i = 0; i < 2400; i++)		// �ȴ�100us
	{
		;
	}
//    REG0CN    = 0x80;        		// ��ѹ�����ƼĴ������ر���ѹ��
//    REF0CN    = 0x03;        		// ��ѹ��׼���ƼĴ�����                           
									// 	   1���ڲ�ģ��ƫѹ������ʹ��;		   
									// 	   2���ڲ���׼��������ʹ�ܣ��ڲ���ѹ��׼��������VREF����.
}
/*********************************************
         PCA����
*********************************************/ 
void PCA0_Init (void)
{
   PCA0MD &= ~0x40;              // Disable the Watchdog Timer	 //12���l
}

/*********************************************
         �ڲ���������
*********************************************/ 
void Oscillator_Init (void)
{
//	OSCICN = 0x83;  			// Set the internal oscillator to Select internal oscillator as input to clock multiplier                                    // 12 MHz
////   CLKMUL  = 0x00;                     
////   CLKMUL |= 0x80;            // Enable clock multiplier
////   Delay();                   // Delay for clock multiplier to begin
////   CLKMUL |= 0xC0;            // Initialize the clock multiplier
////   Delay();                   // Delay for clock multiplier to begin
////   while(!(CLKMUL & 0x20));   // Wait for multiplier to lock
////   CLKSEL  = 0x03;            // Select system clock

    int i = 0;
//    OSCICN    = 0x83;		  	// Set the internal oscillator to Select internal oscillator as input to clock multiplier   
//    CLKMUL    = 0x80;			// Enable clock multiplier
//    for (i = 0; i < 20; i++);    // Wait 5us for initialization
//    CLKMUL    |= 0xC0;			 // Initialize the clock multiplier
//    while ((CLKMUL & 0x20) == 0);  // Wait for multiplier to lock

//	OSCICN    = 0x83;                        //ϵͳʱ��12MHZ
    FLSCL     = 0x90;
    CLKMUL    = 0x80;
    for (i = 0; i < 20; i++);    // Wait 5us for initialization
    CLKMUL    |= 0xC0;
    while ((CLKMUL & 0x20) == 0);
    CLKSEL    = 0x03;
    OSCICN    = 0x83;
}

/*********************************************
         �˿ڳ�ʼ��
*********************************************/ 
void PORT_Init (void)
{
	P0MDOUT   = 0x90;
	P1MDOUT   = 0x60;
	P2MDOUT   = 0x10;
	P4MDOUT   = 0x03;
	P0SKIP    = 0xCF;
	P1SKIP    = 0x3F;
	XBR0      = 0x01;
	XBR1      = 0xC0;
	XBR2      = 0x01;



//	P0MDOUT   = 0x90;
//    P1MDOUT   = 0x40;
//    P2MDOUT   = 0x10;
//    P4MDOUT   = 0x03;
//    P0SKIP    = 0x4F;
//    P1SKIP    = 0x0F;
//    XBR0      = 0x01;	 // route UART 0 to crossbar
//    XBR1      = 0xD1;
//    XBR2      = 0x01;	// route UART 1 to crossbar

}

/*********************************************
         ��ʼ������
*********************************************/  	
void Init_Device (void)
{
   PCA0_Init ();                       // Disable the Watchdog Timer first
   reset_sources_init();
   Oscillator_Init ();
   PORT_Init ();
   UartInit();
   timer2_init();
//   RfidInitProc();
}
/********************************************\
|* ���ܣ� ��ʱ	����Ϊ48Mʱ				   	*|
\********************************************/
void DelayUs(unsigned int t)
{
  unsigned int i;
  unsigned int j;
     for(j=0;j<t;j++)
     	for(i=3;i>0;i--);  //��ʱ��Լ 1us
}
/********************************************\
|* ���ܣ� ��ʱ	����Ϊ48Mʱ					*|
|* ��ʱ��Լ 1ms			    				*|
\********************************************/ 
void DelayMs(unsigned int t)
{
  unsigned int i;
  unsigned int j;
  t=t*10;
  for(j=0;j<t;j++)
     for(i=390;i>0;i--);  //��ʱ��Լ 1ms
}
