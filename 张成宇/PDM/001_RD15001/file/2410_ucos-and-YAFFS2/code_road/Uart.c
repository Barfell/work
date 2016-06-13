
char ReadChar()
{
	while (!((*(volatile unsigned *)0x50000010) & 0x00000001));
	return (*(volatile unsigned char *)0x50000024);
}

void WriteChar(char content)
{
	while(!((*(volatile unsigned *)0x50000010) & 0x00000002));
	(*(volatile unsigned char *)0x50000020) = content;
}

