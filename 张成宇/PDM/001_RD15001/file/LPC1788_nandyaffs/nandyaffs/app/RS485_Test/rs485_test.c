#include "bsp.h"
#include "lpc177x_8x_uart.h"
#include "lpc177x_8x_pinsel.h"

#define UART_RS485		(LPC_UART2)

uint8_t slaveA_msg[] = "Msg Hello Ucdragon ";

void init_rs485(void){
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;

	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	// RS485 configuration
	UART1_RS485_CTRLCFG_Type rs485cfg;

		//TXD2
	PINSEL_ConfigPin(0, 10, 1);

	//RXD2
	PINSEL_ConfigPin(0, 11, 1);

	//P1.19, function 6: OE2: UART OE2 Output Enable for UART2
	PINSEL_ConfigPin(1, 19, 6);	

	/* Initialize UART Configuration parameter structure to default state:
	* Baudrate = 9600 bps
	* 8 data bit
	* 1 Stop bit
	* Parity: None
	* Note: Parity will be enabled later in UART_RS485Config() function.
	*/
	UART_ConfigStructInit(&UARTConfigStruct);

	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init((LPC_UART_TypeDef *)UART_RS485, &UARTConfigStruct);

	/* Initialize FIFOConfigStruct to default state:
	* 				- FIFO_DMAMode = DISABLE
	* 				- FIFO_Level = UART_FIFO_TRGLEV0
	* 				- FIFO_ResetRxBuf = ENABLE
	* 				- FIFO_ResetTxBuf = ENABLE
	* 				- FIFO_State = ENABLE
	*/
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig((LPC_UART_TypeDef *)UART_RS485, &UARTFIFOConfigStruct);

	// Configure RS485
	/*
	* - Auto Direction in Tx/Rx driving is enabled
	* - Direction control pin is set to DTR1
	* - Direction control pole is set to "1" that means direction pin
	* will drive to high state before transmit data.
	* - Multidrop mode is disable
	* - Auto detect address is disabled
	* - Receive state is enable
	*/
	rs485cfg.AutoDirCtrl_State = ENABLE;
	rs485cfg.DirCtrlPin = UART1_RS485_DIRCTRL_DTR;
	rs485cfg.DirCtrlPol_Level = SET;
	rs485cfg.DelayValue = 50;
	rs485cfg.NormalMultiDropMode_State = DISABLE;
	rs485cfg.AutoAddrDetect_State = DISABLE;
	rs485cfg.MatchAddrValue = 0;
	rs485cfg.Rx_State = ENABLE;
	UART_RS485Config(UART_RS485, &rs485cfg);

	/* Enable UART Rx interrupt */
	UART_IntConfig((LPC_UART_TypeDef *)UART_RS485, UART_INTCFG_RBR, ENABLE);

	/* Enable UART line status interrupt */
	UART_IntConfig((LPC_UART_TypeDef *)UART_RS485, UART_INTCFG_RLS, ENABLE);

		// Enable UART Transmit
	UART_TxCmd((LPC_UART_TypeDef *)UART_RS485, ENABLE);

 }

 void rs485_tx_rx(void){
	UART_RS485SendData(UART_RS485, slaveA_msg, sizeof(slaveA_msg));
 }