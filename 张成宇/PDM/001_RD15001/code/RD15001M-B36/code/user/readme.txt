1�����Ӹ����������ڱ�����ѡ��C++�������Ӷ���__FPU_USED����
2��ʹ��DSP���ܰѶ�Ӧ��lib��ӽ����̺������ARM_MATH_CM4,__CC_ARM,ARM_MATH_MATRIX_CHECK,ARM_MATH_ROUNDING��Щ��Ϳ���ʹ���ˡ�



һ��OS:
1������tick�ҵ���ԭ�������ж�������õĺ���a���������a��Ҫ����tick�����ʱ��ͻ�ҵ���
2��2015/03/25��UINT STDCALL EnterIrqLvl(UINT uIrqLvl),VOID STDCALL ExitIrqLvl(UINT uIrqLvl)����USB�����з�����openusb��ʱ�����ֵ�ǰisrΪ16�������
���������⴦���
if(iISR >= 16)
{
	uIrqLvlCur = (UCHAR)IRQn2IRQLTbl[iISR-16];
}
��Ϊ
if(iISR >= 16)
{
	if(iISR == 16)
		uIrqLvlCur = PASSIVE_IRQLVL;   //modified by syan
	else
		uIrqLvlCur = (UCHAR)IRQn2IRQLTbl[iISR-16];
}

ͬʱ��Ϊsystick�����ȼ�Ϊ7����usb�����ȼ�Ӧ�ø���systick

���������SYSTIMER_IRQLVL��������⣬�����SYSTIMER_IRQLVL��usmartɨ�趨ʱ�����õ��жϣ���Ϊ����malloc���ɹ�����Ϊ��ǰ���ж�ʱSYSTIMER_IRQLVL

3��ϵͳʱ�������ö�ʱ��3��100usһ���жϣ�4���ֽڴ��Ҫ119.3��Сʱ�Ż������


��������
1������
a��USMART�����ջ�����200���ֽڡ�
b��Ĭ�ϵĳ�ʱʱ����32ms

2��

3��FRAM:
128K*8bit�������40MHZ,ʹ�õ���SPI1,����ǹ���APB2�ϵģ���ΪAPB2Ŀǰ��2��Ƶ��Ҳ����84M,���SPI���ó�4��Ƶ����������24M,����ط��������óɺܵ͵��ٶȣ�
����ᵼ���޷���SPI���������룬��Ҫ�Ǹ�ϵͳʱ�ӵ��жϵ��Ȼ����ˡ�
ʹ��21M���ٶ�д128k����1572ms��������705ms
ʹ��42M���ٶ�д128k����1354ns��������548ms
�����ó���40M���ٶ�Ҳû������ʲô���⡣
ע�⣺���������ܳ���128k BYTES

4��USB,SDIO���ٶ���24MHZ,

5��ADC�õ���PC0,ADC123,channel 10

6�������һ�����Ϳ�ʼ��ʼ����Ҳ����˵����ʱΪ00000.00mm����

7��
mf_scan_files��"2"��

8��
���ӻ���ͨ�ţ����������ݣ����ǵ���WriteFile(DEV_COMM, szTestSend, 20, 0);�����ݸ�������ʱ�����ǻᵼ��ϵͳtmaʧ�ܡ�

9��NANDFLASH
K9GBG08U0A:32g*8bit��nand flash����С��λ��1ҳ��1��device=4152��block��1��block=128page��һҳ��8K
Nandflash Maker_ID = ec
Nandflash Device_ID = d7
Nandflash Third_ID = 94��֧��cache program������2ҳͬʱ���б�̡�4 Level cell,�ڲ�ֻ��1��Ƭ�ӡ�
Nandflash Fourth_ID = 7a��block sizeΪ1MB��ÿ��pageΪ8KB��û�ж����ֽڡ�
Nandflash Fifth_ID = 54��2��plane��ECCΪ24bit/1KB
Nandflash Sixth_ID = 43��20nm��֧��EDO��

�������
ÿ��д��ȥ��ȡECCֵ��Ȼ���ٻض�һ�Σ���ECCֵ�Ƕ��١�������ε�ֵһ����֤��д��ȥ������û���⡣��дһ����1.8ms�������1.3ms���ض�һ��ʱ220us����




CMD:
���Գ�������
//1��FRAM
55 AA 01 01 AA 55
//2��ADC
55 AA 02 01 AA 55
//3��USB
55 AA 03 01 AA 55
//4��SD
55 AA 04 01 AA 55
//5��UART
55 AA 05 01 AA 55
//6��MILE
55 AA 06 01 AA 55
//7��NAND
55 AA 07 01 AA 55
//8��RFID
////a������
55 AA 08 01 AA 55
////b��crc����
55 AA 08 02 AA 55
//LED
55 AA 09 01 AA 55
//COMM
55 AA 0A 01 AA 55
//APP
55 AA 0B 01 AA 55


һ��RFID:
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
//10MS ���Լ�������ǩ
FF 05 22 00 00 13 00 0A 2A E7
//500MS ���Լ�������ǩ
FF 05 22 00 00 13 01 F4 2B 19
//7.g_szGetTagdata
FF 03 29 01 FF 00 1B 03
//8.g_szContinueReading
//Ҫ���ϵ��ϴ����ݵĻ�����ִ������ָ����ִ��2Fָ��
FF 03 9A 01 0C 00 A3 5D

FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 01 FF DD 2B
//9.g_szStopReading
FF 03 2F 00 00 02 5E 86

//X1.�ػ�ָ�� 01 90 00
AA 55 AA
//X2.����ָ�� 02 90 00
55 AA 55
//X3.��ȡRFID״̬ 03 90 00
AA 00 AA
//X4.����ָ��   04 90 00
55 00 55


����NANDFLASH:
//��ʼ���� (ǰ�������ֽ���������ĸ��ֽ���д�����ݣ�����д0x32)
01 01 EF 32







����FRAM
//BYTEMODE
01
//STRINGMODE
02
//�����Դ�С128k
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
//10MS ���Լ�������ǩ
FF 05 22 00 00 13 00 0A 2A E7
//500MS ���Լ�������ǩ
FF 05 22 00 00 13 01 F4 2B 19
//7.g_szGetTagdata
FF 03 29 01 FF 00 1B 03
//��ȡΨһID
ff 03 29 00 00 00 f4 22
//8.g_szContinueReading
//Ҫ���ϵ��ϴ����ݵĻ�����ִ������ָ����ִ��2Fָ��
FF 03 9A 01 0C 00 A3 5D

FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 01 FF DD 2B
//��ȡΨһID����
FF 10 2F 00 00 01 22 00 00 05 07 22 10 00 1B 03 E8 00 00 dc d4

//9.g_szStopReading
FF 03 2F 00 00 02 5E 86

//����
FF 02 92 0B B8 4A E1


//X1.�ػ�ָ�� 01 90 00
AA 01 AA
//X2.����ָ�� 02 90 00
AA 02 AA 
//X3.��ȡRFID״̬ 03 90 00
AA 03 AA
//X4.����ָ��   04 90 00
AA 04 AA 
//X5.�Զ�ָ�� 05 90 00
AA 05 AA
//X6.�Զ�ΨһIDָ�� 06 90 00
AA 06 AA 
//7.��ǿ�ٶ�ָ�� 07 90 00
AA 07 AA
//X8.��ǿ����ָ�� 08 90 00
AA 08 AA


//�������ٶȲ���
//1��
FF 03 9B 05 02 02 DE EA
//2��
FF 03 9B 05 12 00 CE E8
//3��
FF 03 9B 05 10 00 CC E8
//4��
FF 03 9B 05 11 00 CD E8
//5��
FF 03 9B 05 00 00 DC E8
//6��
FF 04 9B 05 01 00 00 A3 FD


����NANDFLASH:
//��ʼ���� (ǰ�������ֽ���������ĸ��ֽ���д�����ݣ�����д0x32)
01 01 EF 38
����FRAM:
//MODE 
02
//02-MODE-2K
00 00 08 00
//01-MODE-128K
00 02 00 00


CMD:
���Գ�������
//1��FRAM
55 AA 01 01 AA 55
//2��ADC
55 AA 02 01 AA 55
//3��USB
55 AA 03 01 AA 55
//4��SD
55 AA 04 01 AA 55
//5��UART
55 AA 05 01 AA 55
//6��MILE
55 AA 06 01 AA 55
//7��NAND
55 AA 07 01 AA 55
//8��RFID
////a������
55 AA 08 01 AA 55
////b��crc����
55 AA 08 02 AA 55
//LED
55 AA 09 01 AA 55
//COMM
55 AA 0A 01 AA 55
//U��
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

�̣�send1
�ȣ�rx1
��5

��2��send2
��3��rx2
��5


ע�⣺
1�������ٺ����������ܴ�����ݣ�������malloc


FSMC_NAND_WriteSmallPage(pBuf, nand_address, 1, &EccCode);

DelayMs_Sft(1);//

FSMC_NAND_WriteByteArea((U8 *)(&EccCode), nand_address, ECC_BYTE_NUMBER);


дУ��ֵ��ȥǰ����Ҫ����ʱ����������ĳЩ�����޷�д�ɹ�




