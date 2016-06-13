//≤ªƒ‹”√
void uart_init(void)
{ 
	TMOD      = 0x20;   //T1 is selected as baud rate generator of UART0
                        //T1 is 8-bit auto load timer
    CKCON     = 0x00;   //sysclk/12 is configed as T1 prescale clock
    TH1       = 0xF3;   //Baud rate is 9600bps:CB;19200:E6;38400:F3
    TCON      = 0x40;   //T1 is running
    
    SCON0     = 0x10;   //8-bit UART with variable baud rate 
                        //UART0 recieve enable
	SCON1     = 0x10;   //UART1 recieve enalbe
    SMOD1     = 0x0C;   //Config UART1 8-bit data,no pariy
    SBCON1    = 0x43;   //Enable baud rate generator and prescaler = 1
    SBRLL1    = 0x63;   //Baud rate is 9600bps :FD8F;19200:FEC7; 38400:FF63
    SBRLH1    = 0xFF;

	ES0 = 1;
	EIE2 = 0x02;
}