#ifndef _SA56004_H
#define _SA56004_H
#include "lpc_types.h"

#define   LTHB_R 0x00 //local temperature high byte
#define   ATLB_R 0x22//local temperature low byte

#define   SR_R	 0x01 //status register
#define   CON_R  0x02 //configuration register
#define   CON_W  0x09 //
#define   CR_R   0x04 //conversion rate Read
#define   CR_W   0x0A //conversion rate Write
#define   LHS_R  0x05 //local high setpoint
#define   LHS_W  0x0B //local high setpoint
#define   LLS_R  0x05
#define   LLS_W  0x0c
#define   One_Shot_W 0x0F //writing register initiates a one shot conversion
#define   RMID_R 0xFE //read manufacturer¡¯s ID
#define   AM_RW	 0xBF //alert mode



uint8_t Sa56004_Init(uint32_t i2cClockFreq);
void Sa56004_DeInit(void);
uint8_t Sa50064_Write(uint8_t i2cId,uint8_t off_addr,uint8_t data);
uint8_t Sa50064_Read(uint8_t i2cId,uint8_t off_addr,uint8_t *data);
uint8_t Sa56004_R_Test(uint8_t *sign,uint8_t *rx_data);

#endif
