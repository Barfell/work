#ifndef _BSP_FLASH_H
#define _BSP_FLASH_H
void MCUFlashUnlock(void);
unsigned char MCUFlashErase(unsigned char sector);
unsigned char MCUFlashWrite(int FlashAddress, int Data);
void flash_w_buffer(int FlashAddress, char *Data);
void Flash_w_Length(int FlashAddress, char *Data, int length);
char* flash_r_buffer(int FlashAddress, int length);

#endif

