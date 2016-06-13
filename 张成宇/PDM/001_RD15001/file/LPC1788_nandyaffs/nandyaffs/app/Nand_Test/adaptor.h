
#ifndef _ADAPTOR_H
#define _ADAPTOR_H

#include "bsp.h"
#include "lpc_types.h"
#include "nandflash_k9f2g08u0x.h"
#include "debug_frmwrk.h"

void CheckBad(void);

void  FAT_ReadNF(uint32_t sector,uint32_t count,uint8_t *buff);
void  FAT_WriteNF2G08(uint32_t sector,uint8_t count,uint8_t *buff);

#endif
