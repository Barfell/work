#ifndef _BOOT_H_
#define _BOOT_H_



#define APP_ADDR_TOP                    0x18000
#define APP_VECTOR_TOP                  0x17FFF
#define APP_VECTOR_BUTTOM               0x17FE0
#define APP_ADDR_BUTTOM                 0x11000


#define BOOT_ADDR_TOP                   0x6000
#define BOOT_VECTOR_TOP                 0x5FFF
#define BOOT_VECTOR_BUTTOM              0x5FE0
#define BOOT_ADDR_BUTTOM                0x1100


#define HARDWARE_VECTOR_TOP             0XFFFF
#define HARDWARE_VECTOR_BUTTOM          0XFFE0

void BootProc(void);
void EarseAppFlash(void);
unsigned char AsciiToHex(unsigned char cNum);
void Vector_APP2HARD(void);
void Vector_HARD2BOOT(void);

void GoToApp(void);


#endif