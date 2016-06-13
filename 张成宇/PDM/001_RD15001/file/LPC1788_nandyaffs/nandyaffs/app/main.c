/******************** (C) COPYRIGHT 2010 Ucdragon ************
 ÓÅÁú¿Æ¼¼ YL_LPC1788¼Æ¹À°å²âÊÔÖ÷ÎÄ¼þ
 ×÷Õß£ºYJ
 °æ±¾£ºV1.0
 Ä¿ÆÚ£º2011 06 29
 **********************************************************************/
#include "lpc_types.h"
#include "lpc177x_8x_nvic.h"
#include "system_LPC177x_8x.h"
#include "lpc177x_8x_uart.h"
//#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_gpio.h"
#include "sdram_k4s561632j.h"
//#include "SST39VF6401.h"
#include "nandflash_k9f2g08u0x.h"
//#include "yl_1788_touch.h"
#include "debug_frmwrk.h"
#include "download.h"
//#include "drv_glcd.h"
#include "bsp.h"
//#include "SA56004.h"
#include <stdlib.h>
#include "yaffsfs.h"
#include "yaffs_guts.h"

extern uint32_t download_addr,download_len;
char * ptr=NULL;

/************************** PRIVATE FUNCTION *************************/
const unsigned char boot_msg[] =
"**************************************************************************\n\r"
"Hello NXP Ucdragon \n\r"
"\t - MCU: LPC177x_8x \n\r"
"\t - Core: Cortex-M3 \n\r"
"\t - Comunicate via: UART0 - 115200 bps \n\r"
"\t - YL-LPC1788 Test\n\r"
"***************************************************************************\n\r";

void fstest(void);

/*********************************************************************
 * @brief		Print bootload msg
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void print_boot_msg(void)
{
	put_str_(boot_msg);
}

const unsigned char menu[] =
"**************************************************************************\n\r"
"YL-LPC1788 Peripheral Device Test Menu \r"
"###### Select Menu ###### \r"
"[J] Test NandFlash\r"
"[ESC] Return Menu\r"
"***************************************************************************\n\r";

/*********************************************************************//**
 * @brief		Print menu
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	put_str_(menu);
}

/*ÓÃ»§²Ëµ¥¹¦ÄÜÊµÏÖ */
void use_menu(void);

/*³õÊ¼»¯ÏµÍ³¶¨Ê±Æ÷ */
void init_systick(void)
{
	uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);

	/* Generate interrupt each 1 ms   */
	SysTick_Config(cclk/1000 - 1);
}

/* SysTick Counter */
volatile unsigned long SysTickCnt = 0;
/*********************************************************************//**
 * @brief		SysTick handler sub-routine (1ms)
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SysTick_Handler (void)
{
	SysTickCnt++;
}

/*********************************************************************//**
 * @brief		Delay function
 * @param[in]	tick - number milisecond of delay time
 * @return 		None
 **********************************************************************/
void Delay (unsigned long tick)
{
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick);
}

int main(void)
{	
    
    
	SDRAMInit();
    init_systick();	  //±ØÐëÏÈ³õÊ¼»¯SDRAMInit,·ñÔò³ö´í¡£ÓÅÏÈ³õÊ¼»¯£¬ºóÐøDelayº¯Êý»áµ÷ÓÃ
	NandFlash_Init();
	NandFlash_Reset();
	
	/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */
	debug_frmwrk_init();
	Delay(500);
	// print welcome screen
	print_boot_msg();	

    fstest();
    
}

void fstest(void)
{
    int32_t i,file;
    uint32_t FlashID;
    uint8_t  BufToRead[256];
    uint8_t  BufWriteTo[256];
    
    /*uint8_t  BufToRead[2048];
    uint8_t  BufWriteTo[2048];
    uint8_t  spare1[64];
    uint8_t  spare2[64];

    Nand_EraseBlockLarge(1023);

    for(i=0;i<2048;i++)
    {
        BufWriteTo[i]=0xaa;
        BufToRead[i] = 0;
    }
    for(i=0;i<64;i++)
    {
        spare1[i]=0x55;
        spare2[i]=0;
    }
    Nand_WritePageWithSpare2048(65535,BufWriteTo,spare1);
    Nand_ReadPageWithSpare2048(65535,BufToRead,spare2);
    for(i=0;i<2048;i++)
    {
        _DBH(BufToRead[i]);
    }
    for(i=0;i<64;i++)
    {
        _DBH(spare2[i]);
    }
    while(1);*/
    
    /*put_str("Read NAND Flash ID:  ");

	FlashID = NandFlash_ReadId();
	if ( (FlashID & 0xFFFF0000) != K9FXX_ID )
	{
		put_str_("Error in reading NAND Flash ID, testing terminated!");
		while( 1 );
	}

	_DBH32_(FlashID);put_str_("");*/
    
    for(i=0;i<256;i++)
    {
        BufToRead[i]=0;
        BufWriteTo[i]=54;
    }
    
    yaffs_StartUp();
    
    put_str_("yaffs start up");

    i=yaffs_mount("//");
    
    if(i != 0)
    {
        put_str_("yaffs mount error");
        while(1);
    }
    else
    {
        put_str_("yaffs mount finsh");
    }
    
    i=yaffs_mkdir("/heyuanjie",S_IFDIR);
    if(i != 0)
    {
        put_str_("yaffs mkdir error");
    }
    else
    {
        put_str_("yaffs mkdir finsh");
    }

    // ·µ»ØµÄÊÇhandle
    file= yaffs_open("/heyuanjie/a.txt", O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);

    
    put_str_("yaffs open finsh");
    
    _DBH32_(file);

    put_str_("yaffs write");
    i=yaffs_write(file,BufWriteTo,256);
    
    _DBH32_(i);

    //put_str_("yaffs lseek");
    //i=yaffs_lseek(file,0,SEEK_END);
    //_DBH32_(i);
    
    put_str_("yaffs read");
    i=yaffs_pread(file,BufToRead,256,0);

    _DBH32_(i);
    
    for(i=0;i<256;i++)
        _DBD(BufToRead[i]);
    
    yaffs_close(file);
    while(1);
}
