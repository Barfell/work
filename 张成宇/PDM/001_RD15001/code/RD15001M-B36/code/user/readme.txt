1、增加浮点运算是在编译器选项C++里面增加定义__FPU_USED即可
2、使用DSP功能把对应的lib添加进工程后再添加ARM_MATH_CM4,__CC_ARM,ARM_MATH_MATRIX_CHECK,ARM_MATH_ROUNDING这些宏就可以使用了。



一、OS:
1、出现tick挂掉的原因是在中断里面调用的函数a，这个函数a还要依赖tick，这个时候就会挂掉。
2、2015/03/25：UINT STDCALL EnterIrqLvl(UINT uIrqLvl),VOID STDCALL ExitIrqLvl(UINT uIrqLvl)调试USB过程中发现在openusb的时候会出现当前isr为16的情况，
故这里特殊处理把
if(iISR >= 16)
{
	uIrqLvlCur = (UCHAR)IRQn2IRQLTbl[iISR-16];
}
改为
if(iISR >= 16)
{
	if(iISR == 16)
		uIrqLvlCur = PASSIVE_IRQLVL;   //modified by syan
	else
		uIrqLvlCur = (UCHAR)IRQn2IRQLTbl[iISR-16];
}

同时因为systick的优先级为7，故usb的优先级应该高于systick

问题可能是SYSTIMER_IRQLVL引起的问题，而这个SYSTIMER_IRQLVL是usmart扫描定时器所用的中断，因为出现malloc不成功是因为当前的中断时SYSTIMER_IRQLVL

3、系统时间现在用定时器3，100us一次中断，4个字节大概要119.3个小时才会溢出。


二、驱动
1、串口
a、USMART最大接收缓冲室200个字节。
b、默认的超时时间是32ms

2、

3、FRAM:
128K*8bit，最高是40MHZ,使用的是SPI1,这个是挂在APB2上的，因为APB2目前是2分频，也就是84M,因此SPI配置成4分频，这样就是24M,这个地方不能配置成很低的速度，
否则会导致无法从SPI操作中脱离，主要是跟系统时钟的中断调度混乱了。
使用21M的速度写128k用了1572ms，读用了705ms
使用42M的速度写128k用了1354ns，读用了548ms
这里用超过40M的速度也没发现有什么问题。
注意：最大操作不能超过128k BYTES

4、USB,SDIO的速度是24MHZ,

5、ADC用的是PC0,ADC123,channel 10

6、里程是一开机就开始初始化，也就是说开机时为00000.00mm处。

7、
mf_scan_files（"2"）

8、
跟从机的通信，可以收数据，但是调用WriteFile(DEV_COMM, szTestSend, 20, 0);发数据给主机的时候总是会导致系统tma失能。

9、NANDFLASH
K9GBG08U0A:32g*8bit的nand flash，最小单位是1页，1个device=4152个block，1个block=128page。一页是8K
Nandflash Maker_ID = ec
Nandflash Device_ID = d7
Nandflash Third_ID = 94：支持cache program，可以2页同时进行编程。4 Level cell,内部只有1个片子。
Nandflash Fourth_ID = 7a：block size为1MB，每个page为8KB，没有多余字节。
Nandflash Fifth_ID = 54：2个plane，ECC为24bit/1KB
Nandflash Sixth_ID = 43：20nm，支持EDO。

坏块管理：
每次写下去读取ECC值，然后再回读一次，看ECC值是多少。如果两次的值一样则证明写下去的数据没问题。（写一次是1.8ms，标称是1.3ms，回读一次时220us。）




CMD:
测试程序命令
//1、FRAM
55 AA 01 01 AA 55
//2、ADC
55 AA 02 01 AA 55
//3、USB
55 AA 03 01 AA 55
//4、SD
55 AA 04 01 AA 55
//5、UART
55 AA 05 01 AA 55
//6、MILE
55 AA 06 01 AA 55
//7、NAND
55 AA 07 01 AA 55
//8、RFID
////a、测试
55 AA 08 01 AA 55
////b、crc计算
55 AA 08 02 AA 55
//LED
55 AA 09 01 AA 55
//COMM
55 AA 0A 01 AA 55
//APP
55 AA 0B 01 AA 55


一、RFID:
//1.g_szGetCurrentProgram
FF 00 0C 1D 03
//1-1.g_szBootFirmware
FF 00 04 1D 0B
//2.g_szSetFrequencyChannel
FF 01 97 06 4B BB
//3.g_szSetProtocol
FF 02 93 00 05 51 7D
//4.g_szSetAntenna
FF 03 91 02 01 01 42 C5
//5.g_szClearBuffer
FF 00 2A 1D 25
//6.g_szSearchTag
//10MS 难以检索到标签
FF 05 22 00 00 13 00 0A 2A E7
//500MS 可以检索到标签
FF 05 22 00 00 13 01 F4 2B 19
//7.g_szGetTagdata
FF 03 29 01 FF 00 1B 03
//8.g_szContinueReading
//要不断的上传数据的话必须执行这条指令再执行2F指令
FF 03 9A 01 0C 00 A3 5D

FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 01 FF DD 2B
//9.g_szStopReading
FF 03 2F 00 00 02 5E 86

//X1.关机指令 01 90 00
AA 55 AA
//X2.开机指令 02 90 00
55 AA 55
//X3.读取RFID状态 03 90 00
AA 00 AA
//X4.测试指令   04 90 00
55 00 55


二、NANDFLASH:
//开始测试 (前面三个字节是命令，第四个字节是写的数据，这里写0x32)
01 01 EF 32







三、FRAM
//BYTEMODE
01
//STRINGMODE
02
//最大测试大小128k
00 02 00 00
//STRINGMODE 2K
00 00 08 00


//1.g_szGetCurrentProgram
FF 00 0C 1D 03
//1-1.g_szBootFirmware
FF 00 04 1D 0B
//2.g_szSetFrequencyChannel
FF 01 97 06 4B BB
//3.g_szSetProtocol
FF 02 93 00 05 51 7D
//4.g_szSetAntenna
FF 03 91 02 01 01 42 C5
//5.g_szClearBuffer
FF 00 2A 1D 25
//6.g_szSearchTag
//10MS 难以检索到标签
FF 05 22 00 00 13 00 0A 2A E7
//500MS 可以检索到标签
FF 05 22 00 00 13 01 F4 2B 19
//7.g_szGetTagdata
FF 03 29 01 FF 00 1B 03
//获取唯一ID
ff 03 29 00 00 00 f4 22
//8.g_szContinueReading
//要不断的上传数据的话必须执行这条指令再执行2F指令
FF 03 9A 01 0C 00 A3 5D

FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 01 FF DD 2B
//获取唯一ID命令
FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 00 00 dc d4

//9.g_szStopReading
FF 03 2F 00 00 02 5E 86

//距离
FF 02 92 0B B8 4A E1


//X1.关机指令 01 90 00
AA 01 AA
//X2.开机指令 02 90 00
AA 02 AA 
//X3.读取RFID状态 03 90 00
AA 03 AA
//X4.测试指令   04 90 00
AA 04 AA 
//X5.自动指令 05 90 00
AA 05 AA
//X6.自动唯一ID指令 06 90 00
AA 06 AA 
//7.增强速度指令 07 90 00
AA 07 AA
//X8.增强距离指令 08 90 00
AA 08 AA


//以下是速度测试
//1、
FF 03 9B 05 02 02 DE EA
//2、
FF 03 9B 05 12 00 CE E8
//3、
FF 03 9B 05 10 00 CC E8
//4、
FF 03 9B 05 11 00 CD E8
//5、
FF 03 9B 05 00 00 DC E8
//6、
FF 04 9B 05 01 00 00 A3 FD


二、NANDFLASH:
//开始测试 (前面三个字节是命令，第四个字节是写的数据，这里写0x32)
01 01 EF 38
三、FRAM:
//MODE 
02
//02-MODE-2K
00 00 08 00
//01-MODE-128K
00 02 00 00


CMD:
测试程序命令
//1、FRAM
55 AA 01 01 AA 55
//2、ADC
55 AA 02 01 AA 55
//3、USB
55 AA 03 01 AA 55
//4、SD
55 AA 04 01 AA 55
//5、UART
55 AA 05 01 AA 55
//6、MILE
55 AA 06 01 AA 55
//7、NAND
55 AA 07 01 AA 55
//8、RFID
////a、测试
55 AA 08 01 AA 55
////b、crc计算
55 AA 08 02 AA 55
//LED
55 AA 09 01 AA 55
//COMM
55 AA 0A 01 AA 55
//U盘
mf_scan_files("1:")				//u8 mf_scan_files(u8 * path)
//FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW
#define	FA_READ				0x01
#define	FA_OPEN_EXISTING	0x00
#define	FA_WRITE			0x02
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define FA__WRITTEN			0x20
#define FA__DIRTY			0x40

mf_open("1:test.txt",7)			//u8 mf_open(u8*path,u8 mode)  

mf_write("what are you doing",14)	//u8 mf_write(u8*dat,u16 len)

mf_read(14)						//u8 mf_read(u16 len)

mf_close()						//u8 mf_close(void)

绿：send1
橙：rx1
黑5

白2：send2
蓝3：rx2
黑5


注意：
1、不能再函数中声明很大的数据，必须用malloc


FSMC_NAND_WriteSmallPage(pBuf, nand_address, 1, &EccCode);

DelayMs_Sft(1);//

FSMC_NAND_WriteByteArea((U8 *)(&EccCode), nand_address, ECC_BYTE_NUMBER);


写校验值下去前必须要有延时。否则会出现某些数据无法写成功




