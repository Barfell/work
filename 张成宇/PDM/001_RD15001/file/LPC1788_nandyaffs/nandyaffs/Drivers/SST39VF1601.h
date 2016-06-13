/* */
#include "lpc_types.h"

#ifndef __SST39VF1601_H
#define __SST39VF1601_H

#define SECTOR_SIZE             2048    // Must be 2048 uint16_ts for 39VF160X
#define BLOCK_SIZE              32768   // Must be 32K uint16_ts for 39VF160X

#define SST_ID                  0x00BF  // SST Manufacturer's ID code
#define SST_39VF1601            0x234B  // SST39VF1601 device code
#define SST_39VF1602            0x234A  // SST39VF1602 device code

#define MAX_TIMEOUT	0x07FFFFFF   // A ceiling constant used by Check_Toggle_
	// Ready() and Check_Data_Polling().
      	// The user should modify this constant accordingly.

// --------------------------------------------------------------------

int Check_SST_39VF160X(void);
void CFI_Query(uint16_t*);
void SecID_Query(uint16_t*, uint16_t*);
int Erase_One_Sector(uint32_t);
int Erase_One_Block (uint32_t);
void Erase_Entire_Chip(void);
int Program_One_uint16_t (uint16_t*, uint32_t);
int Program_One_Sector (uint16_t*, uint32_t);
int Program_One_Block (uint16_t *Src, uint32_t Dst);
int SecID_Lock_Status(void);
int User_SecID_uint16_t_Program (uint16_t*, uint16_t*, int);
void User_SecID_Lock_Out (void);
void Erase_Suspend (void);
void Erase_Resume (void);
int Check_Toggle_Ready (uint32_t);
int Check_Data_Polling (uint32_t, uint16_t);
void delay_ns(uint32_t delayCnt);
void NORFLASHInit( void );

#endif

