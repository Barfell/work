/*****************************************************************************
 *   mci.h:  Header file for NXP LPC177x_8x Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __MCI_H 
#define __MCI_H

#define MCI_DMA_ENABLED		0

#define HIGH_LVL		(1)
#define LOW_LVL			(0)

/* SD/MMC Command list, per MMC spec. SD Memory Card Spec. Simplified version */
#define CMD0_GO_IDLE_STATE		0		/* GO_IDLE_STATE(MMC) or RESET(SD) */
#define CMD1_SEND_OP_COND		1		/* SEND_OP_COND(MMC) or ACMD41(SD) */
#define CMD2_ALL_SEND_CID		2		/* ALL_SEND_CID */
#define CMD3_SET_RELATIVE_ADDR	3		/* SET_RELATE_ADDR */
#define CMD6_SET_ACMD_BUS_WIDTH	6
#define CMD7_SELECT_CARD		7		/* SELECT/DESELECT_CARD */
#define CMD8_SEND_IF_COND		8		//Sending interface condition cmd
#define CMD9_SEND_CSD			9		/* SEND_CSD */
#define CMD12_STOP_TRANSMISSION	12		/* Stop either READ or WRITE operation */
#define CMD13_SEND_STATUS		13		/* SEND_STATUS */
#define CMD16_SET_BLOCK_LEN		16		/* SET_BLOCK_LEN */
#define CMD17_READ_SINGLE_BLOCK	17		/* READ_SINGLE_BLOCK */
#define CMD24_WRITE_BLOCK		24		/* WRITE_BLOCK */
#define ACMD41_SEND_APP_OP_COND	41		/* ACMD41 for SD card */		
#define CMD55_APP_CMD			55		/* APP_CMD, the following will a ACMD */

#define OCR_INDEX			0x00FF8000


#define CARD_STATUS_ACMD_ENABLE		1 << 5
#define CARD_STATUS_RDY_DATA		1 << 8
#define CARD_STATUS_CURRENT_STATE	0x0F << 9
#define CARD_STATUS_ERASE_RESET		1 << 13

#define SLOW_RATE			1
#define NORMAL_RATE			2

#define SD_1_BIT 			0
#define SD_4_BIT			1

#define CARD_UNKNOWN		0
#define MMC_CARD			1
#define SD_CARD				2
								 /* MCI clk freq = Pclk/(2* (Clkdiv +1) */
#if MCI_DMA_ENABLED
#define MCLKDIV_SLOW		60-1 /* 59 = 400,000Hz -> @48Mhz/(2*60) */ 
#define MCLKDIV_NORMAL		1-1  /* 0 = 24Mhz -> @48Mhz/(2*1) */
#else
#define MCLKDIV_SLOW		60-1 /* 59 = 400,000Hz -> @48Mhz/(2*60) */ 
#define MCLKDIV_NORMAL		3-1  /* 2 = 8Mhz -> @48Mhz/(2*3) */
#endif

#define DATA_TIMER_VALUE	0x10000

#define EXPECT_NO_RESP		0
#define EXPECT_SHORT_RESP	1
#define EXPECT_LONG_RESP	2

/* For the SD card I tested, the minimum block length is 512 */
/* For MMC, the restriction is loose, due to the variety of SD and MMC
card support, ideally, the driver should read CSD register to find the 
speed and block length for the card, and set them accordingly. */
/* In this driver example, it will support both MMC and SD cards, it
does read the information by send SEND_CSD to poll the card status,
but, it doesn't configure them accordingly. this is not intended to 
support all the SD and MMC card. */ 

/* DATA_BLOCK_LEN table
	DATA_BLOCK_LEN			Actual Size( BLOCK_LENGTH )
	11						2048
	10						1024
	9						512
	8						256
	7						128
	6						64
	5						32
	4						16
	3						8
	2						4
	1						2
*/

/* To simplify the programming, please note that, BLOCK_LENGTH is a multiple 
of FIFO_SIZE */
#define DATA_BLOCK_LEN		9	/* Block size field in DATA_CTRL *///512 byte
#define BLOCK_LENGTH		(1 << DATA_BLOCK_LEN)
								/* for SD card, 128, the size of the flash */
								/* card is 512 * 128 = 64K */
#define BLOCK_NUM			0x80		
#define FIFO_SIZE			16

#define BUS_WIDTH_1BIT		0
#define BUS_WIDTH_4BITS		10

/* MCI Status register bit information */
#define MCI_CMD_CRC_FAIL	(1 << 0)
#define MCI_DATA_CRC_FAIL	(1 << 1)
#define MCI_CMD_TIMEOUT		(1 << 2)
#define MCI_DATA_TIMEOUT	(1 << 3)
#define MCI_TX_UNDERRUN		(1 << 4)
#define MCI_RX_OVERRUN		(1 << 5)
#define MCI_CMD_RESP_END	(1 << 6)
#define MCI_CMD_SENT		(1 << 7)
#define MCI_DATA_END		(1 << 8)
#define MCI_START_BIT_ERR	(1 << 9)
#define MCI_DATA_BLK_END	(1 << 10)
#define MCI_CMD_ACTIVE		(1 << 11)
#define MCI_TX_ACTIVE		(1 << 12)
#define MCI_RX_ACTIVE		(1 << 13)
#define MCI_TX_HALF_EMPTY	(1 << 14)
#define MCI_RX_HALF_FULL	(1 << 15)
#define MCI_TX_FIFO_FULL	(1 << 16)
#define MCI_RX_FIFO_FULL	(1 << 17)
#define MCI_TX_FIFO_EMPTY	(1 << 18)
#define MCI_RX_FIFO_EMPTY	(1 << 19)
#define MCI_TX_DATA_AVAIL	(1 << 20)
#define MCI_RX_DATA_AVAIL	(1 << 21)

#define CMD_INT_MASK      (MCI_CMD_CRC_FAIL | MCI_CMD_TIMEOUT | MCI_CMD_RESP_END \
			             | MCI_CMD_SENT     | MCI_CMD_ACTIVE)

#define DATA_ERR_INT_MASK	(MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_TX_UNDERRUN \
			               | MCI_RX_OVERRUN | MCI_START_BIT_ERR)

#define ACTIVE_INT_MASK ( MCI_TX_ACTIVE | MCI_RX_ACTIVE)

#define FIFO_INT_MASK		(MCI_TX_HALF_EMPTY | MCI_RX_HALF_FULL \
                           | MCI_TX_FIFO_FULL  | MCI_RX_FIFO_FULL \
			               | MCI_TX_FIFO_EMPTY | MCI_RX_FIFO_EMPTY \
						   | MCI_DATA_BLK_END )

#define	FIFO_TX_INT_MASK (MCI_TX_HALF_EMPTY )
#define	FIFO_RX_INT_MASK (MCI_RX_HALF_FULL  )

#define DATA_END_INT_MASK    (MCI_DATA_END | MCI_DATA_BLK_END)

#define ERR_TX_INT_MASK (MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_TX_UNDERRUN | MCI_START_BIT_ERR)
#define ERR_RX_INT_MASK (MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_RX_OVERRUN  | MCI_START_BIT_ERR)

/* Error code on the command response. */
#define INVALID_RESPONSE	0xFFFFFFFF

typedef enum mci_card_state
{
	MCI_CARDSTATE_IDLE = 0,
	MCI_CARDSTATE_READY,
	MCI_CARDSTATE_IDENDTIFIED,
	MCI_CARDSTATE_STBY,
	MCI_CARDSTATE_TRAN,
	MCI_CARDSTATE_DATA,
	MCI_CARDSTATE_RCV,
	MCI_CARDSTATE_PRG,
	MCI_CARDSTATE_DIS,
}en_Mci_CardState;


typedef enum mci_func_error
{
	MCI_FUNC_OK = 0,
	MCI_FUNC_FAILED = -1,
	MCI_FUNC_BAD_PARAMETERS = -2,
	MCI_FUNC_BUS_NOT_IDLE = -3,
	MCI_FUNC_TIMEOUT = -3,
	MCI_FUNC_ERR_STATE = -4,
	MCI_FUNC_NOT_READY = -5,
}en_Mci_Func_Error;

typedef enum mci_card_type
{
	MCI_MMC_CARD = 1,
	MCI_SD_CARD = 0,
	MCI_CARD_UNKNOWN = -1,
}en_Mci_CardType;

typedef struct mci_cid
{
	uint8_t MID;			//Manufacturer ID
	uint16_t OID;			//OEM/Application ID
	uint8_t PNM_H;			//Product name 8-bits higher
	uint32_t PNM_L;			//Product name 32-bits Lower
	uint8_t PRV;			//Product revision
	uint32_t PSN;			//Product serial number
	uint8_t reserved;		//reserved: 4 bit
	uint16_t MDT;			//Manufacturing date: 12 bit
	uint8_t CRC;			//CRC7 checksum: 7 bit
	uint8_t unused;			//not used, always: 1 bit always 1
} st_Mci_CardId;


void MCI_TXEnable( void );
void MCI_TXDisable( void );
void MCI_RXEnable( void );
void MCI_RXDisable( void );

void MCI_IRQHandler( void ); 
uint32_t MCI_Init(uint8_t powerActiveLevel );
void  MCI_SendCmd( uint32_t CmdIndex, uint32_t Argument, uint32_t ExpectResp, uint32_t AllowTimeout );
uint32_t MCI_GetCmdResp( uint32_t CmdIndex, uint32_t NeedRespFlag, uint32_t *CmdRespStatus );
uint32_t MCI_CmdResp(uint32_t CmdIndex, uint32_t Argument, 
								uint32_t ExpectResp, uint32_t *CmdResp, uint32_t AllowTimeout);

void  MCI_Set_MCIClock( uint32_t clockrate );
uint32_t SD_Set_BusWidth( uint32_t width );
uint32_t MCI_Cmd_SendAcmdOpCond(uint8_t hcsVal);
uint32_t MCI_CardInit( void );
en_Mci_CardType MCI_GetCardType(void);
uint32_t MCI_CardReset( void );
uint32_t MCI_Cmd_SendIfCond(void);
uint32_t MCI_GetCID(st_Mci_CardId* cidValue);
uint32_t MCI_SetCardAddress( void );
uint32_t MCI_GetCSD(uint32_t* csdVal);
uint32_t MCI_Cmd_SelectCard( void );
uint32_t MCI_GetCardStatus(uint32_t* cardStatus);
uint32_t MCI_GetBlockEndFlag(void);
uint32_t MCI_SetBlockLen( uint32_t blockLength );
uint32_t MCI_Cmd_SendAcmdBusWidth( uint32_t buswidth );
uint32_t MCI_Cmd_StopTransmission( void );

uint32_t MCI_WriteBlock(uint8_t* memblock, uint32_t blockNum );
uint32_t MCI_ReadBlock(uint8_t* destBlock, uint32_t blockNum );

#endif /* end __MCI_H */
/****************************************************************************
**                            End Of File
****************************************************************************/
