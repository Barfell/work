#ifndef __BOARD_INIT_H
#define __BOARD_INIT_H
void SetClock(void);
void BoardGPIOConfig(void);
void Time2_Config(void);
void Time3_Config(void);	 
void Time4_Config(void);
void Nvic_Config(void);
char * read_dev_id(void);
#endif


