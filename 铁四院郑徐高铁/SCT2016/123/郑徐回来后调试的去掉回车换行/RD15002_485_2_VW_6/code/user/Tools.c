#include  <includes.h>

void hextostr(char *str ,unsigned char hex)
{
	if( (hex / 16) > 9)
		{*str = (hex / 16)+'0'+ 7;}
	else
		{*str = (hex / 16)+'0';}

	if((hex%16) > 9)
		{*(str+1) = (hex%16)+'0' + 7;}
	else
		{*(str+1) = (hex%16)+'0';}
}


void usart_update_packet(unsigned char *p,unsigned int length)
{
	while(length != 0)
	{
		USART_SendData(USART3, *(p++) );
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		length--;
	}
}

void DlyMs(unsigned int dly)
{
	int i ,j;
	for(i = 0;i<20000;i++)
		{for(j=0;j<dly;j++);}
}
