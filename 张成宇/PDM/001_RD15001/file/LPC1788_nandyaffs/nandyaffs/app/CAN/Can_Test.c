/***********************************************************************//**
 * @file		can_test_bypass_mode.c
 * @purpose		This example used to test Bypass mode
 * @version		1.0
 * @date		29. October. 2010
 * @author		NXP MCU SW Application Team
 *---------------------------------------------------------------------
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
#include "lpc177x_8x_can.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_clkpwr.h"
#include "debug_frmwrk.h"
#include "bsp.h"

#define TRANSMIT_CAN_NO		(CAN_2)//(CAN_1)
#define RECVD_CAN_NO		(CAN_1)//(CAN_2)//(CAN_1)

#if (RECVD_CAN_NO == CAN_2)
#define RECVD_CAN_CNTRL		(CAN2_CTRL)
#else
#define RECVD_CAN_CNTRL		(CAN1_CTRL)
#endif


/* Example group ----------------------------------------------------------- */
/** @defgroup CAN_test_bypass_mode	CAN_test_bypass_mode
 * @ingroup CAN_Examples
 * @{
 */
/************************** PRIVATE VARIABLES *************************/
uint8_t msg[]=
	"*******************************************************************************\n\r"
	"Hello NXP Semiconductors \n\r"
	"CAN bypass demo \n\r"
	"\t - MCU: LPC17xx \n\r"
	"\t - Core: ARM CORTEX-M3 \n\r"
	"\t - Communicate via: UART0 - 115200 bps \n\r"
	"Use two CAN peripherals: CAN1 and CAN2 to communicate\n\r"
	"This example used to test Bypass mode\n\r"
	"*******************************************************************************\n\r";

/** CAN variable definition **/
CAN_MSG_Type TXMsg, RXMsg; // messages for test Bypass mode
uint32_t CANRxCount, CANTxCount = 0;

/************************** PRIVATE FUNCTIONS *************************/
void CAN_IRQHandler(void);

void CAN_InitMessage(void);
void PrintMessage(CAN_MSG_Type* msg);
void print_msg(void);


/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		CAN_IRQ Handler, control receive message operation
 * param[in]	none
 * @return 		none
 **********************************************************************/
void CAN_IRQHandler()
{
	uint8_t IntStatus;
	uint32_t data1;

	/* get interrupt status
	 * Note that: Interrupt register CANICR will be reset after read.
	 * So function "CAN_IntGetStatus" should be call only one time
	 */
	IntStatus = CAN_IntGetStatus(RECVD_CAN_NO);

	//check receive interrupt
	if((IntStatus >> 0) & 0x01)
	{
		CAN_ReceiveMsg(RECVD_CAN_NO, &RXMsg);
		PrintMessage(&RXMsg);

		CANRxCount++; //count success received message

		//increase data for next TX Message
		TXMsg.id ++;

		data1 = (TXMsg.dataA[0])|(((TXMsg.dataA[1]))<<8)|((TXMsg.dataA[2])<<16)|((TXMsg.dataA[3])<<24);

		if(data1 == 0xFFFFFFFF)
			data1 = 0;
		else
			data1++;

		*((uint8_t *) &TXMsg.dataA[0])= *((uint8_t *) &TXMsg.dataB[0])= data1 & 0x000000FF;
		*((uint8_t *) &TXMsg.dataA[1])= *((uint8_t *) &TXMsg.dataB[1])=(data1 & 0x0000FF00)>>8;;
		*((uint8_t *) &TXMsg.dataA[2])= *((uint8_t *) &TXMsg.dataB[2])=(data1 & 0x00FF0000)>>16;
		*((uint8_t *) &TXMsg.dataA[3])= *((uint8_t *) &TXMsg.dataB[3])=(data1 & 0xFF000000)>>24;

		CAN_SendMsg(TRANSMIT_CAN_NO, &TXMsg);
	}
}

/*-------------------------PRIVATE FUNCTIONS----------------------------*/
/*********************************************************************//**
 * @brief		Print Message via COM1
 * param[in]	msg: point to CAN_MSG_Type object that will be printed
 * @return 		none
 **********************************************************************/
void PrintMessage(CAN_MSG_Type* CAN_Msg)
{
	uint32_t data;

	put_str("Message ID:     ");

	_DBH32(CAN_Msg->id); put_str_("");

	put_str("Message length: ");

	_DBH32(CAN_Msg->len); put_str_(" BYTES");

	put_str("Message type:   ");

	if(CAN_Msg->type==DATA_FRAME)
	{
		 put_str_("DATA FRAME ");
	}
	else
		 put_str_("REMOTE FRAME ");

	put_str("Message format: ");

	if(CAN_Msg->format==STD_ID_FORMAT)
	{
		 put_str_("STANDARD ID FRAME FORMAT");
	}
	else
		 put_str_("EXTENDED ID FRAME FORMAT");

	put_str("Message dataA:  ");

	data = (CAN_Msg->dataA[0])|(CAN_Msg->dataA[1]<<8)|(CAN_Msg->dataA[2]<<16)|(CAN_Msg->dataA[3]<<24);

	_DBH32(data); put_str_("");

	data = (CAN_Msg->dataB[0])|(CAN_Msg->dataB[1]<<8)|(CAN_Msg->dataB[2]<<16)|(CAN_Msg->dataB[3]<<24);

	put_str("Message dataB:  ");

	_DBH32(data); put_str_("");

	 put_str_("");
}

/*********************************************************************//**
 * @brief		Initialize transmit and receive message for Bypass operation
 * @param[in]	none
 * @return 		none
 **********************************************************************/
void CAN_InitMessage(void)
{
	TXMsg.format = EXT_ID_FORMAT;
	TXMsg.id = 0x00001234;
	TXMsg.len = 8;
	TXMsg.type = DATA_FRAME;
	TXMsg.dataA[0] = TXMsg.dataA[1] = TXMsg.dataA[2] = TXMsg.dataA[3] = 0x00000000;
	TXMsg.dataB[0] = TXMsg.dataB[1] = TXMsg.dataB[2] = TXMsg.dataB[3] = 0x00000000;

	RXMsg.format = 0x00;
	RXMsg.id = 0x00;
	RXMsg.len = 0x00;
	RXMsg.type = 0x00;
	RXMsg.dataA[0] = RXMsg.dataA[1] = RXMsg.dataA[2] = RXMsg.dataA[3] = 0x00000000;
	RXMsg.dataB[0] = RXMsg.dataB[1] = RXMsg.dataB[2] = RXMsg.dataB[3] = 0x00000000;
}

/*********************************************************************//**
 * @brief		print menu
 * @param[in]	none
 * @return 		none
 **********************************************************************/
void print_msg(void)
{
	 put_str_(msg);
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main CAN program body
 * @param[in]	none
 * @return 		int
 **********************************************************************/
void Can_init(void)
{
	print_msg();

	/* Pin configuration
	 * CAN1: select P0.0 as RD1. P0.1 as TD1
	 * CAN2: select P0.4 as RD2, P0.5 as RD2
	 */

#if (TRANSMIT_CAN_NO == CAN_1)
	PINSEL_ConfigPin (0, 0, 1);

	PINSEL_ConfigPin (0, 1, 1);
#else
	PINSEL_ConfigPin (0, 4, 2);

	PINSEL_ConfigPin (0, 5, 2);
#endif

#if (RECVD_CAN_NO != TRANSMIT_CAN_NO)
#if (RECVD_CAN_NO == CAN_1)
	PINSEL_ConfigPin (0, 0, 1);

	PINSEL_ConfigPin (0, 1, 1);
#else
	PINSEL_ConfigPin (0, 4, 2);

	PINSEL_ConfigPin (0, 5, 2);
#endif
#endif


	//Initialize CAN1 & CAN2
	CAN_Init(TRANSMIT_CAN_NO, 125000);

#if (RECVD_CAN_NO != TRANSMIT_CAN_NO)
	CAN_Init(RECVD_CAN_NO, 125000);
#else
	CAN_ModeConfig(CAN_ID_1, CAN_SELFTEST_MODE, ENABLE);
#endif

	//Enable Interrupt
	////CAN_IRQCmd(TRANSMIT_CAN_NO, CANINT_TIE1, ENABLE);

	CAN_IRQCmd(RECVD_CAN_NO, CANINT_RIE, ENABLE);

	//Enable CAN Interrupt
	NVIC_EnableIRQ(CAN_IRQn);

	CAN_InitMessage();

	PrintMessage(&TXMsg);

	CAN_SetAFMode(CAN_ACC_BP);

	 put_str_("OK! Start CAN operation now...");

	/** To test Bypass Mode: we send infinite messages to CAN2 and check
	 * receive process via COM1
	 */
	CAN_SendMsg(TRANSMIT_CAN_NO, &TXMsg);

#if (RECVD_CAN_NO == TRANSMIT_CAN_NO)
	CAN_SetCommand(TRANSMIT_CAN_NO, CAN_CMR_SRR);
#endif
}

void Can_Uninit(void) {
	NVIC_DisableIRQ(CAN_IRQn);
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN1, DISABLE);
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN2, DISABLE);
}

/*
 * @}
 */
