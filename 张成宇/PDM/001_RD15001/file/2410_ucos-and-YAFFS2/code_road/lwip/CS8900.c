
void WriteCS8900Reg(unsigned short addr,  unsigned short val)
{
	(*(volatile unsigned short *)0x1900030a) = addr;
	(*(volatile unsigned short *)0x1900030c) = val;
}

unsigned short ReadCS8900Reg(unsigned short addr)
{
	(*(volatile unsigned short *)0x1900030a) = addr;
	return (*(volatile unsigned short *)0x1900030c);
}

