1、移植系统的时候注意修改system_stm32f10x.c中晶振的值#define SYSCLK_FREQ_36MHz  36000000
2、使用片外SSTflash的话在DtuBoot()中设置g_u8FlashType = SST25VF0_FLASH;反之，直接升级片内flash