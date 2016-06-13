/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_NAND_H
#define __FSMC_NAND_H

#include "kernal.h"
//#include "other.h"
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


typedef struct
{
  uint8_t Maker_ID;
  uint8_t Device_ID;
  uint8_t Third_ID;
  uint8_t Fourth_ID;
  uint8_t Fifth_ID; 
}NAND_IDTypeDef;

typedef struct 
{
  uint16_t Block;
  uint8_t Page;
} NAND_ADDRESS;  




/** 
  * @brief  NAND memory status
  */  
#define NAND_VALID_ADDRESS         ((uint32_t)0x00000100)
#define NAND_INVALID_ADDRESS       ((uint32_t)0x00000200)
#define NAND_TIMEOUT_ERROR         ((uint32_t)0x00000400)
#define NAND_BUSY                  ((uint32_t)0x00000000)
#define NAND_ERROR                 ((uint32_t)0x00000001)
#define NAND_READY                 ((uint32_t)0x00000040)
#define NAND_PASS                 	((uint32_t)0x00000140)

#define NAND_BYTENUMBER_PERPAGE     ((uint16_t)0x800) /* 每页2k bytes */
#define NAND_PAGENUMBER_PERBLOCK    ((uint32_t)0x0040) /* 每块64页 */
#define NAND_BYTENUMBER_PERBLOCK    ((uint32_t)0x20000) /* 每块64*2k=128k bytes */
#define NAND_ECC_BYTENUMBER			((uint16_t)0x04) /* ECC只用到4个字节*/
#define MAXBADBLOCKNUMBER          	0x28        //最大坏块数是40
#define NAND_MAXNUMBER_BLOCK        ((uint16_t)0x800) /* 每片最大2048块*/


VOID FSMC_NAND_Init(VOID);
VOID NAND_Reset(VOID);
VOID FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID);
uint32_t FSMC_NAND_ReadSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, U32 *pEccCode);
uint32_t FSMC_NAND_ReadSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address);
uint32_t FSMC_NAND_WriteSmallPage(uint8_t *pBuffer, NAND_ADDRESS Address, U32 *pEccCode);
uint32_t FSMC_NAND_WriteSpareArea(uint8_t *pBuffer, NAND_ADDRESS Address);
uint32_t FSMC_NAND_EraseBlock(NAND_ADDRESS Address);
uint32_t NAND_ReadStatus(VOID);
uint32_t NAND_GetStatus(VOID);
VOID NandBlockEraseInit(VOID);
VOID SetNewBadBlock(NAND_ADDRESS nand_address);
VOID AdjustBadBlock(NAND_ADDRESS *pnand_address);
U8 ECCCheck(U32 ECCMem,U32 ECCNew,U8* Data);

#ifdef __cplusplus
}
#endif

#endif 
