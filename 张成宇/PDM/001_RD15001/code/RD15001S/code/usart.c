/*Abstract :USART communication.
*
*Version NO.:1.0
*Writer     :Woy
*Date       :2015-06-10
**************************************************/
#include "C8051F340.h"
#include "system.h"
#include "uart.h"
#include "Init.h"

U32 g_u32Uart1TimeCount = 0; 
U32 g_u32Uart2TimeCount = 0;

CQueueInfo xdata g_cQueueInfo1 = {0}, g_cQueueInfo2 = {0};
PQueueInfo xdata pQueueUsart1Info, pQueueUsart2Info;
/*********************************************
         ���ڳ�ʼ��
*********************************************/ 
void UartInit(void)
{
	// uart0 
    TR1	  = 1;
	TMOD  = 0x20;   		//T1 is selected as baud rate generator of UART0,T1 is 8-bit auto load timer
    TCON  = 0x40;	//T1 is running
    SCON0 = 0x10;	//8-bit UART with variable baud rate,UART0 recieve enable
	ES0 = 1;						//enable uart0 interrupt
	EA=1; //���жϵ��򿪣����򴮿�0�жϲ�����ES0��SCON0֮�⣻������������������֮��
//	EIE2 = 0x02;					//enable uart1 interrupt
//	CKCON = 0x00;  			//T1clk = SYSCLK/12; nemo, old is CKCON = 0x08;
//	CKCON = 0x01;  			//T1clk = SYSCLK/04; nemo, old is CKCON = 0x08;
//	TH1 = 256-SYSCLK/12/9600/2; 	//TH1 = 0x98,Baud rate is 9600bps
//	TH1 = 256-SYSCLK/12/(9600*2); 	//TH1 = 0x98,Baud rate is 4800bps

//��Ƭ���ڲ�12M����ʱ�Ĳ���������
//	TH1 = 0x98;	CKCON = 0x00;	//12M,12��Ƶ��4800��T1clk = SYSCLK/12;
//	TH1 = ��������; CKCON = 0x01;	//12M,04��Ƶ��4800��T1clk = SYSCLK/04;
//	TH1 = 0xcc; CKCON = 0x00;	//12M,12��Ƶ��9600��T1clk = SYSCLK/12;
//	TH1 = 0x64; CKCON = 0x01;	//12M,04��Ƶ��9600��T1clk = SYSCLK/04;
//	TH1 = 0xe6; CKCON = 0x00;	//12M,12��Ƶ��19200��T1clk = SYSCLK/12;
//	TH1 = 0xb2; CKCON = 0x01;	//12M,04��Ƶ��19200��T1clk = SYSCLK/04;
//	TH1 = 0xf3; CKCON = 0x00;	//12M,12��Ƶ��38400��T1clk = SYSCLK/12;
//	TH1 = 0xd9; CKCON = 0x01;	//12M,04��Ƶ��38400��T1clk = SYSCLK/04;
//	TH1 = 0xf8; CKCON = 0x00;	//12M,12��Ƶ��57600����T1clk = SYSCLK/12;
//	TH1 = 0xe6; CKCON = 0x01;	//12M,04��Ƶ��57600��T1clk = SYSCLK/04;

//��Ƭ���ڲ�48M����ʱ�Ĳ���������
//   CLKMUL  = 0x00;                     // Select internal oscillator as input to clock multiplier
//   CLKMUL |= 0x80;                     // Enable clock multiplier
//   Delay();                            // Delay for clock multiplier to begin
//   CLKMUL |= 0xC0;                     // Initialize the clock multiplier
//   Delay();                            // Delay for clock multiplier to begin
//   while(!(CLKMUL & 0x20));            // Wait for multiplier to lock
//   CLKSEL  = 0x03;                     // Select system clock

//	TH1 = ��������; CKCON = 0x00;	//48M,12��Ƶ��4800��T1clk = SYSCLK/12;
//	TH1 = ��������; CKCON = 0x01;	//48M,04��Ƶ��4800��T1clk = SYSCLK/04;
//	TH1 = 0x30; CKCON = 0x00;	//48M,12��Ƶ��9600��T1clk = SYSCLK/12;
//	TH1 = ��������; CKCON = 0x01;	//48M,04��Ƶ��9600��T1clk = SYSCLK/04;
//	TH1 = 0x98; CKCON = 0x00;	//48M,12��Ƶ��19200��T1clk = SYSCLK/12;
//	TH1 = ��������; CKCON = 0x01;	//48M,04��Ƶ��19200��T1clk = SYSCLK/04;
//	TH1 = 0xcc; CKCON = 0x00;	//48M,12��Ƶ��38400��T1clk = SYSCLK/12;
//	TH1 = 0x64; CKCON = 0x01;	//48M,04��Ƶ��38400��T1clk = SYSCLK/04;
//	TH1 = 0xde; CKCON = 0x00;	//48M,12��Ƶ��57600��T1clk = SYSCLK/12;
//	TH1 = 0x98; CKCON = 0x01;	//48M,04��Ƶ��57600��T1clk = SYSCLK/04;
	TH1 = 0xcc; CKCON = 0x01;	//48M,04��Ƶ��115200��T1clk = SYSCLK/04;


   	SMOD1 = 0x0C;                       // UART1 8λ����
    SBRLL1    = 0x30;
    SBRLH1    = 0xFF;	 //115200
//    SCON1     = 0x10;
	SCON1 = 0x70;                       // ���������巢�ͺͽ����ж�
    SBCON1    = 0x43; // enable baud rate generator
	EIP2=0X02; //����2���ȼ���
	EIE2 =0X02;//������2�ж�

	pQueueUsart1Info = &g_cQueueInfo1;
	pQueueUsart2Info = &g_cQueueInfo2;

}

//======================================================================================//
/***UART1 string transmit****/
void Uart1_Tx(uchar *string, uchar snum)
{
	uchar *tstr,iloop;
	tstr = string;
	ES0 = 0;	 //Disable uart0 interrupt when transmitting

	for (iloop=0; iloop<snum; iloop++)
	{
		SBUF0 = *tstr ;
		while (TI0==0);
		TI0 = 0;
		tstr++;
	}
	ES0 = 1;	 //Enable uart0 interrupt when transmitted
}
//======================================================================================//
void Uart1_Tx_End(uchar *string)
{
 	uchar iLoop;
	iLoop=0;
	ES0 = 0;
	while((*string!='\0')&&(iLoop<100))
	{
	 	 SBUF0 = *string;
		 while(TI0==0);
		 TI0 = 0;
		 string++;
		 iLoop++;
	}
	ES0 = 1;
}
//======================================================================================//

/******Uart0 Received interrupt************/
void Uart1_Rx_ISR4() interrupt 4
{
	if(RI0)
	{
	 	RI0 = 0;
		if(AddQueue(&g_cQueueInfo1, SBUF0) == TRUE)
		{
			g_u32Uart1TimeCount = GetTickCount();
		}
	}//if
}
//======================================================================================//

/***UART1 string transmit****/
void Uart2_Tx(uchar *string, uchar snum)
{
	uchar *tstr,iloop;
	tstr = string;
	EIE2 = 0x00;   //Disable uart1 interrupt when transmitting
	for (iloop=0; iloop<snum; iloop++)
	{
		SBUF1 = *tstr ;
		while ((SCON1 & 0x02)==0);
		SCON1 &= 0xFD;
		tstr++;
	}
	EIE2 = 0x02;	 //Enable uart0 interrupt when transmitted
}

//======================================================================================//

void Uart2_Tx_End(uchar *string)
{
	uchar iLoop;
	iLoop=0;
	EIE2 = 0x00; 
	while((*string!='\0')&&(iLoop<100))
	{
	 	 SBUF1 = *string;
		 while ((SCON1 & 0x02)==0);
		 SCON1 &= 0xFD;
		 string++;
		 iLoop++;
	}
	EIE2 = 0x02;
}

//======================================================================================// 
/*******Uart1 Received interrupt********/
void Uart2_Rx_ISR16() interrupt 16
{
	uchar RI1;	
	RI1 = SCON1 & 0x01;
	
	if(RI1 == 0x01)
	{
		SCON1 &= 0xFE;
		if(AddQueue(&g_cQueueInfo2, SBUF1) == TRUE)
		{
			g_u32Uart2TimeCount = GetTickCount();
		}
	}
}

void ClearUart1Length(void)
{
	memset(pQueueUsart1Info, 0, sizeof(g_cQueueInfo1));
}
void ClearUart2Length(void)
{
	memset(pQueueUsart2Info, 0, sizeof(g_cQueueInfo2));
}

void ReceiveUsart1Data(uchar *pBuf, U16 *pLength)
{
	uchar ucvalue;
	U16 ulCount = 0;
	U32 u32Tick;

	while(GetQueueLength(pQueueUsart1Info) != 0)
	{
		u32Tick = GetTickCount();
		if((u32Tick - g_u32Uart1TimeCount)> 5)
		{
		    while(DeleteQueue(pQueueUsart1Info, &ucvalue) == TRUE)
		    {		
		       pBuf[ulCount] = ucvalue; 
			   ulCount++;
				
		    }
		}
	}
	
	*pLength = ulCount;
}

void ReceiveUsart2Data(uchar *pBuf, U16 *pLength)
{
	uchar ucvalue;
	U16 ulCount = 0;
	U32 u32Tick;

	while(GetQueueLength(pQueueUsart2Info) != 0)
	{
		u32Tick = GetTickCount();
		if((u32Tick - g_u32Uart2TimeCount)> 5)
		{
		    while(DeleteQueue(pQueueUsart2Info, &ucvalue) == TRUE)
		    {		
		       pBuf[ulCount] = ucvalue; 
			   ulCount++;
		    }
		}
	}
	
	*pLength = ulCount;
}

void EnterException(unsigned char ucErrCode)
{
	uchar xdata szData[6];
	sprintf(szData, "%d", ucErrCode);
    while(1)
    {
		Uart1_Tx(szData,1);
        DelayMs(1000);
    }  
    
}

