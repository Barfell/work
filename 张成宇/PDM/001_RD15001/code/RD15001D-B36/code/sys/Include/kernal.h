#ifndef __BSP_H
#define __BSP_H	

//bsp调用
#include "stm32f4xx.h" 
#include "stm32f4xx_conf.h"
//工具调用
#include "tool.h"
//私有调用
#include "malloc.h"	 

#define WDG_CLEAR
//ERROR CODE
enum
{
    ERR_RFID_STEP_1 = 1,
    ERR_RFID_STEP_2,
    ERR_RFID_STEP_3,
    ERR_RFID_STEP_4,
    ERR_RFID_STEP_5,
    ERR_RFID_STEP_6,
    ERR_RFID_STEP_7,
    ERR_RFID_STEP_8,
    ERR_RFID_STOP,
    ERR_NAND_BADBLOCK_FULL,
    ERR_NAND_FULL,
    ERR_NAND_MALLOC_FAIL,
    ERR_GPS_NAND_FULL,
    ERR_INS_NAND_FULL,
    ERR_OTHER_NAND_FULL,
    ERR_RFID_NAND_FULL,
    ERR_UPAN_OPEN_FAIL,
    ERR_UPAN_WRITE_FAIL,
    ERR_UPAN_READ_FAIL,
    ERR_UPAN_CLOSE_FAIL,
    ERR_USATT1_MALLOC_FAIL,
    ERR_USATT2_MALLOC_FAIL,
    ERR_USATT3_MALLOC_FAIL,
	ERR_USATT4_MALLOC_FAIL,
    ERR_OTHER_MALLOC_FAIL,
    ERR_OTHER_SPACE_FULL,
    ERR_INS_SPACE_FULL,
    ERR_GPS_SPACE_FULL,
    ERR_COMM_MALLOC_FAIL,
    ERR_TEST_MALLOC_FAIL,
    ERR_SD_WRITE_FAIL,
    ERR_SD_READ_FAIL,    
    ERR_ADD_FAIL,
};
																	    
	 
//位带操作
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

//以下为汇编函数
VOID WFI_SET(VOID);		//执行WFI指令
VOID INTX_DISABLE(VOID);//关闭所有中断
VOID INTX_ENABLE(VOID);	//开启所有中断
VOID MSR_MSP(u32 addr);	//设置堆栈地址 

VOID OsInit(VOID);
VOID DelayMs(U32 nTime);
VOID DelayMs_Sft(U32 nTime);
VOID DelayUs_Sft(U32 nTime);
U32 GetTickCount(VOID);
U32 GetSecondOfWeek(VOID);
VOID SetSecondOfWeek(U32 u32Cnt);
VOID EnterException(U32 u32ErrCode);



//enum
//{
//	HM_INVALID = 0,
//	HM_TMA,	        //HM_TMA消息值不能修改
//	HM_UART,
//	HM_RING,
//	HM_CID,
//	HM_KEY,
//	HM_MCARD,
//	HM_HARDHOOK,
//	HM_DATA,        //FSK数据
//	HM_DIAL,
//    HM_BLTH,        //蓝牙
//	HM_AUDIOCOM,    //音频通信
//    HM_USB,
//    HM_POWER,
//	HM_MAX = 0x40
//};


///**********************************************************************************
//* Module:		按键设备驱动和应用接口
//* Function:		定义统一的全键盘虚拟按键码
//* Description:	1、该文件所定义的虚拟按键基于PC机的全键盘，与Win32开发环境的虚拟按键
//* 				码提供完整兼容。
//*				2、终端设备往往是全键盘码的子集。
//*				3、另外，从实际产品应用出发，该文件也对PC全键盘码进行部分转义定义。
//*				ExDefine注释段均为转义定义
//*				4、历史意义上，此文件的定义与ASCII表的字符含义定义有兼容性。
//*				5、定义该文件的目的，是使所有产品可以使用同样的按键常量，从而避免不
//*				同项目在不同编译时刻的常量差异，以及可能引发的版本问题。
//***********************************************************************************
//* LOG	DATE		AUTHOR		ACTION
//***********************************************************************************
//* 2011/03/10	tao.lan		移植
//***********************************************************************************/
//#define	VK_LBUTTON				0x01
//#define	VK_RBUTTON				0x02
//#define	VK_CANCEL				0x03
//#define	VK_MBUTTON				0x04
//#define	VK_XBUTTON1				0x05
//#define	VK_XBUTTON2				0x06

//#define	VK_BACK					0x08
//#define	VK_TAB					0x09

//#define	VK_LF					0x0A
//#define	VK_VT					0x0B

//#define	VK_CLEAR			    0x0C
//#define	VK_RETURN				0x0D

//#define	VK_SO				    0x0E
//#define	VK_SI					0x0F

//#define	VK_SHIFT				0x10
//#define	VK_CONTROL				0x11
//#define	VK_MENU					0x12
//#define	VK_PAUSE				0x13
//#define	VK_CAPITAL				0x14

//#define	VK_KANA					0x15
//#define	VK_HANGEUL				0x15
//#define	VK_HANGUL				0x15
//#define	VK_JUNJA				0x17
//#define	VK_FINAL				0x18
//#define	VK_HANJA				0x19
//#define	VK_KANJI				0x19

//#define	VK_SUBSTITUTE			0x1A

//#define	VK_ESCAPE				0x1B

//#define	VK_CONVERT				0x1C
//#define	VK_NONCONVERT			0x1D
//#define	VK_ACCEPT				0x1E
//#define	VK_MODECHANGE			0x1F

//#define	VK_SPACE				0x20
//#define	VK_PRIOR				0x21
//#define	VK_NEXT					0x22
//#define	VK_END					0x23
//#define	VK_HOME					0x24
//#define	VK_LEFT					0x25
//#define	VK_UP					0x26
//#define	VK_RIGHT				0x27
//#define	VK_DOWN					0x28
//#define	VK_SELECT				0x29
//#define	VK_PRINT				0x2A
//#define	VK_EXECUTE				0x2B
//#define	VK_SNAPSHOT				0x2C
//#define	VK_INSERT				0x2D
//#define	VK_DELETE				0x2E
//#define	VK_HELP					0x2F

//#define	VK_0					0x30
//#define	VK_1					0x31
//#define	VK_2					0x32
//#define	VK_3					0x33
//#define	VK_4					0x34
//#define	VK_5					0x35
//#define	VK_6					0x36
//#define	VK_7					0x37
//#define	VK_8					0x38
//#define	VK_9					0x39

//#define	VK_COLON				0x3A
//#define	VK_SEMICOLON			0x3B
//#define	VK_LESS					0x3C
//#define	VK_EQU					0x3D
//#define	VK_BIG					0x3E
//#define	VK_QUESTION				0x3F
//#define	VK_AT					0x40

//#define	VK_A					0x41
//#define	VK_B					0x42
//#define	VK_C					0x43
//#define	VK_D					0x44
//#define	VK_E					0x45
//#define	VK_F					0x46
//#define	VK_G					0x47
//#define	VK_H					0x48
//#define	VK_I					0x49
//#define	VK_J					0x4A
//#define	VK_K					0x4B
//#define	VK_L					0x4C
//#define	VK_M					0x4D
//#define	VK_N					0x4E
//#define	VK_O					0x4F
//#define	VK_P					0x50
//#define	VK_Q					0x51
//#define	VK_R					0x52
//#define	VK_S					0x53
//#define	VK_T					0x54
//#define	VK_U					0x55
//#define	VK_V					0x56
//#define	VK_W					0x57
//#define	VK_X					0x58
//#define	VK_Y					0x59
//#define	VK_Z					0x5A

//#define	VK_LWIN					0x5B
//#define	VK_RWIN					0x5C
//#define	VK_APPS					0x5D

//#define	VK_SLEEP				0x5F

//#define	VK_NUMPAD0				0x60
//#define	VK_NUMPAD1				0x61
//#define	VK_NUMPAD2				0x62
//#define	VK_NUMPAD3				0x63
//#define	VK_NUMPAD4				0x64
//#define	VK_NUMPAD5				0x65
//#define	VK_NUMPAD6				0x66
//#define	VK_NUMPAD7				0x67
//#define	VK_NUMPAD8				0x68
//#define	VK_NUMPAD9				0x69
//#define	VK_MULTIPLY				0x6A
//#define	VK_ADD					0x6B
//#define	VK_SEPARATOR			0x6C
//#define	VK_SUBTRACT				0x6D
//#define	VK_DECIMAL				0x6E
//#define	VK_DIVIDE				0x6F
//#define	VK_F1					0x70
//#define	VK_F2					0x71
//#define	VK_F3					0x72
//#define	VK_F4					0x73
//#define	VK_F5					0x74
//#define	VK_F6					0x75
//#define	VK_F7					0x76
//#define	VK_F8					0x77
//#define	VK_F9					0x78
//#define	VK_F10					0x79
//#define	VK_F11					0x7A
//#define	VK_F12					0x7B
//#define	VK_F13					0x7C
//#define	VK_F14					0x7D
//#define	VK_F15					0x7E
//#define	VK_F16					0x7F
//#define	VK_F17					0x80
//#define	VK_F18					0x81
//#define	VK_F19					0x82
//#define	VK_F20					0x83
//#define	VK_F21					0x84
//#define	VK_F22					0x85
//#define	VK_F23					0x86
//#define	VK_F24					0x87

//#define	VK_UNASSIGNED1			0x88
//#define	VK_UNASSIGNED2			0x89
//#define	VK_UNASSIGNED3			0x8A
//#define	VK_UNASSIGNED4			0x8B
//#define	VK_UNASSIGNED5			0x8C
//#define	VK_UNASSIGNED6			0x8D
//#define	VK_UNASSIGNED7			0x8E
//#define	VK_UNASSIGNED8			0x8F

//#define	VK_NUMLOCK				0x90
//#define	VK_SCROLL				0x91

//#define	VK_OEM_NEC_EQUAL		0x92

//#define	VK_OEM_FJ_JISHO			0x92
//#define	VK_OEM_FJ_MASSHOU		0x93
//#define	VK_OEM_FJ_TOUROKU		0x94
//#define	VK_OEM_FJ_LOYA			0x95
//#define	VK_OEM_FJ_ROYA			0x96

//#define	VK_UNASSIGNED9			0x97
//#define	VK_UNASSIGNED10			0x98
//#define	VK_UNASSIGNED11			0x99
//#define	VK_UNASSIGNED12			0x9A
//#define	VK_UNASSIGNED13			0x9B
//#define	VK_UNASSIGNED14			0x9C
//#define	VK_UNASSIGNED15			0x9D
//#define	VK_UNASSIGNED16			0x9E
//#define	VK_UNASSIGNED17			0x9F

//#define	VK_LSHIFT				0xA0
//#define	VK_RSHIFT				0xA1
//#define	VK_LCONTROL				0xA2
//#define	VK_RCONTROL				0xA3
//#define	VK_LMENU				0xA4
//#define	VK_RMENU				0xA5

//#define	VK_BROWSER_BACK			0xA6
//#define	VK_BROWSER_FORWARD		0xA7
//#define	VK_BROWSER_REFRESH		0xA8
//#define	VK_BROWSER_STOP			0xA9
//#define	VK_BROWSER_SEARCH		0xAA
//#define	VK_BROWSER_FAVORITES	0xAB
//#define	VK_BROWSER_HOME			0xAC

//#define	VK_VOLUME_MUTE			0xAD
//#define	VK_VOLUME_DOWN			0xAE
//#define	VK_VOLUME_UP			0xAF
//#define	VK_MEDIA_NEXT_TRACK		0xB0
//#define	VK_MEDIA_PREV_TRACK		0xB1
//#define	VK_MEDIA_STOP			0xB2
//#define	VK_MEDIA_PLAY_PAUSE		0xB3
//#define	VK_LAUNCH_MAIL			0xB4
//#define	VK_LAUNCH_MEDIA_SELECT	0xB5
//#define	VK_LAUNCH_APP1			0xB6
//#define	VK_LAUNCH_APP2			0xB7

//#define	VK_RESERVED1			0xB8
//#define	VK_RESERVED2			0xB9

//#define	VK_OEM_1				0xBA
//#define	VK_OEM_PLUS				0xBB
//#define	VK_OEM_COMMA			0xBC
//#define	VK_OEM_MINUS			0xBD
//#define	VK_OEM_PERIOD			0xBE
//#define	VK_OEM_2				0xBF
//#define	VK_OEM_3				0xC0

//#define	VK_RESERVED3			0xC1
//#define	VK_RESERVED4			0xC2
//#define	VK_RESERVED5			0xC3
//#define	VK_RESERVED6			0xC4
//#define	VK_RESERVED7			0xC5
//#define	VK_RESERVED8			0xC6
//#define	VK_RESERVED9			0xC7
//#define	VK_RESERVED10			0xC8
//#define	VK_RESERVED11			0xC9
//#define	VK_RESERVED12			0xCA
//#define	VK_RESERVED13			0xCB
//#define	VK_RESERVED14			0xCC
//#define	VK_RESERVED15			0xCD
//#define	VK_RESERVED16			0xCE
//#define	VK_RESERVED17			0xCF
//#define	VK_RESERVED18			0xD0
//#define	VK_RESERVED19			0xD1
//#define	VK_RESERVED20			0xD2
//#define	VK_RESERVED21			0xD3
//#define	VK_RESERVED22			0xD4
//#define	VK_RESERVED23			0xD5
//#define	VK_RESERVED24			0xD6
//#define	VK_RESERVED25			0xD7

//#define	VK_UNASSIGNED18			0xD8
//#define	VK_UNASSIGNED19			0xD9
//#define	VK_UNASSIGNED20			0xDA

//#define	VK_OEM_4				0xDB
//#define	VK_OEM_5				0xDC
//#define	VK_OEM_6				0xDD
//#define	VK_OEM_7				0xDE
//#define	VK_OEM_8				0xDF

//#define	VK_RESERVED26			0xE0

//#define	VK_OEM_AX				0xE1
//#define	VK_OEM_102				0xE2
//#define	VK_ICO_HELP				0xE3
//#define	VK_ICO_00				0xE4

//#define	VK_PROCESSKEY			0xE5

//#define	VK_ICO_CLEAR			0xE6

//#define	VK_PACKET				0xE7

//#define	VK_UNASSIGNED21			0xE8

//#define	VK_OEM_RESET			0xE9
//#define	VK_OEM_JUMP				0xEA
//#define	VK_OEM_PA1				0xEB
//#define	VK_OEM_PA2				0xEC
//#define	VK_OEM_PA3				0xED
//#define	VK_OEM_WSCTRL			0xEE
//#define	VK_OEM_CUSEL			0xEF
//#define	VK_OEM_ATTN				0xF0
//#define	VK_OEM_FINISH			0xF1
//#define	VK_OEM_COPY				0xF2
//#define	VK_OEM_AUTO				0xF3
//#define	VK_OEM_ENLW				0xF4
//#define	VK_OEM_BACKTAB			0xF5

//#define	VK_ATTN					0xF6
//#define	VK_CRSEL				0xF7
//#define	VK_EXSEL				0xF8
//#define	VK_EREOF				0xF9
//#define	VK_PLAY					0xFA
//#define	VK_ZOOM					0xFB
//#define	VK_NONAME				0xFC
//#define	VK_PA1					0xFD
//#define	VK_OEM_CLEAR			0xFE

//// ExDefine
//#define	VK_INVALID				0xFF
//#define	VK_NULL					0x00
//#define	VK_POWER				VK_NULL
//#define	VK_H1					VK_F1
//#define	VK_H2					VK_F2
//#define	VK_H3					VK_F3
//#define	VK_H4					VK_F4
//#define	VK_H5					VK_F5
//#define	VK_H6					VK_F6
//#define	VK_H7					VK_F7
//#define	VK_H8					VK_F8
//#define	VK_H9					VK_F9
//#define	VK_H10					VK_F10
//#define	VK_H11					VK_F11
//#define	VK_H12					VK_F12
//#define	VK_H13					VK_F13
//#define	VK_H14					VK_F14
//#define	VK_H15					VK_F15
//#define	VK_H16					VK_F16
//#define	VK_H17					VK_F17
//#define	VK_H18					VK_F18
//#define	VK_H19					VK_F19
//#define	VK_H20					VK_F20
//#define	VK_H21					VK_F21
//#define	VK_H22					VK_F22
//#define	VK_H23					VK_F23
//#define	VK_H24					VK_F24
//#define	VK_OK					VK_RETURN
//#define	VK_IME					VK_LSHIFT
//#define	VK_STAR					VK_COLON
//#define	VK_SHARP				VK_SEMICOLON
//#define	VK_DEL					VK_DELETE
//#define	VK_REDIAL				VK_QUESTION
//#define	VK_HANDFREE				VK_AT
//#define	VK_EXIT					VK_HOME

//#define KEY_INVALID             VK_INVALID
//#define KEY_HANDFREE	        VK_HANDFREE

//#define HK_1	VK_H1
//#define HK_2	VK_H2
//#define HK_3	VK_H3
//#define HK_4	VK_H4
//#define HK_5	VK_H5
//#define HK_6	VK_H6
//#define HK_7	VK_H7
//#define HK_8	VK_H8
//#define HK_9	VK_H9

#endif











