/***********************************************************************//**
 * @file		lpc177x_8x_crc.c
 * @brief		Contains all functions support for CRC firmware library on
 * 				LPC177x_8x
 * @version		1.0
 * @date		13. Dec. 2010
 * @author		NXP MCU SW Application Team
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "lpc177x_8x_crc.h"
#include "lpc177x_8x_clkpwr.h"


/* Private Variables ----------------------------------------------------------- */
volatile CRC_Type crc_cur_type;

/* Public Functions ----------------------------------------------------------- */
/** @addtogroup CRC_Public_Functions
 * @{
 */
/*********************************************************************//**
 * @brief 		Initialize CRC operation
 * @param[in]	CRCType CRC standard type, should be:
 * 				- CRC_POLY_CRCCCITT: CRC-CCITT polynomial
 * 				- CRC_POLY_CRC16: CRC-16 polynomial
 * 				- CRC_POLY_CRC32: CRC-32 polynomial
 * @return 		None
 **********************************************************************/
void CRC_Init(CRC_Type CRCType)
{
	if(CRCType == CRC_POLY_CRCCCITT)
	{
		LPC_CRC->MODE = 0x00;
		LPC_CRC->SEED = 0xFFFF;
		crc_cur_type = CRC_POLY_CRCCCITT;
	}
	else if(CRCType == CRC_POLY_CRC16)
	{
		LPC_CRC->MODE = 0x15;
		LPC_CRC->SEED = 0x0000;
		crc_cur_type = CRC_POLY_CRC16;

	}
	else if(CRCType == CRC_POLY_CRC32)
	{
		LPC_CRC->MODE = 0x36;
		LPC_CRC->SEED = 0xFFFFFFFF;
		crc_cur_type = CRC_POLY_CRC32;
	}
	else
	{
		//Invalid input parameter
		while(1);//error loop
	}
}
/*********************************************************************//**
 * @brief 		CRC reset
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void CRC_Reset(void)
{
	if(crc_cur_type == CRC_POLY_CRCCCITT)
		LPC_CRC->SEED = 0xFFFF;
	else if (crc_cur_type == CRC_POLY_CRC16)
		LPC_CRC->SEED = 0x0000;
	else if (crc_cur_type == CRC_POLY_CRC32)
		LPC_CRC->SEED = 0xFFFFFFFF;
}

/*********************************************************************//**
 * @brief 		CRC data checksum calculation
 * @param[in]	data	input data
 * @return 		data checksum result
 **********************************************************************/
uint32_t CRC_CalcDataChecksum(uint32_t data, CRC_WR_SIZE SizeType)
{
	if(SizeType == CRC_WR_8BIT)
		LPC_CRC->WR_DATA_BYTE = (uint8_t)data;
	else if(SizeType == CRC_WR_16BIT)
		LPC_CRC->WR_DATA_WORD = (uint16_t)data;
	else
		LPC_CRC->WR_DATA_DWORD = data;
	return(LPC_CRC->SUM);
}

/*********************************************************************//**
 * @brief 		CRC block data checksum calculation
 * @param[in]	blockdata	pointer to block input data
 * @param[in]	blocksize	size of block data
 * @param[in]	SizeType	size of data width per write, should be:
 				- CRC_WR_8BIT : 8-bit write
				- CRC_WR_16BIT: 16-bit write
				- CRC_WR_32BIT: 32-bit write
 * @return 		block data checksum result
 **********************************************************************/
uint32_t CRC_CalcBlockChecksum(void *blockdata, uint32_t blocksize, CRC_WR_SIZE SizeType)
{
#if (SizeType == CRC_WR_8BIT)
        uint8_t *reg, *data;
        reg = (uint8_t *)&(LPC_CRC->WR_DATA_BYTE);
        data = (uint8_t *)blockdata;
#elif (SizeType == CRC_WR_16BIT)
        uint16_t *reg, *data;
        reg = (uint16_t *)&(LPC_CRC->WR_DATA_WORD);
        data = (uint16_t *)blockdata;
#else
        uint32_t *reg, *data;
        reg =  (uint32_t *)&(LPC_CRC->WR_DATA_DWORD);
        data = (uint32_t *)blockdata;
#endif
    while(blocksize !=0)
    {
		*reg = *data;
		(data)++;
		blocksize--;
    }
	return(LPC_CRC->SUM);
}

/**
 * @}
 */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

