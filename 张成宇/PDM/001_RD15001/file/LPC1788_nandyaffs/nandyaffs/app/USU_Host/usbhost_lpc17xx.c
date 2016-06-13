/*
**************************************************************************************************************
*                                                 NXP USB Host Stack
*
*                                     (c) Copyright 2008, NXP SemiConductors
*                                     (c) Copyright 2008, OnChip  Technologies LLC
*                                                 All Rights Reserved
*
*                                                  www.nxp.com
*                                               www.onchiptech.com
*
* File           : usbhost_lpc17xx.c
* Programmer(s)  : Ravikanth.P
* Version        :
*
**************************************************************************************************************
*/

/*
**************************************************************************************************************
*                                            INCLUDE HEADER FILES
**************************************************************************************************************
*/

#include  "usbhost_lpc17xx.h"
#include  "lpc_types.h"
#include  "debug_frmwrk.h"
//#include   "Host.h"

/*
**************************************************************************************************************
**/
extern	volatile	uint32_t	HOST_RhscIntr ;         /* Root Hub Status Change interrupt                       */
extern	volatile	uint32_t	HOST_WdhIntr  ;         /* Semaphore to wait until the TD is submitted            */
extern	volatile	uint8_t		HOST_TDControlStatus ;                   
extern				uint16_t	*TDBufNonVol;               /* Identical to TDBuffer just to reduce compiler warnings */                                       
extern  volatile	uint32_t	UnrecoverableIntCount ; 
extern	volatile	HCED		*EDCtrl;                    /* Control endpoint descriptor structure                  */
extern  volatile	HCED		*EDBulkIn;        /* BulkIn endpoint descriptor  structure                    */
extern  volatile	HCED		*EDBulkOut;       /* BulkOut endpoint descriptor structure                    */
extern  volatile	HCTD		*TDHead;          /* Head transfer descriptor structure                       */
extern  volatile	HCTD		*TDTail;          /* Tail transfer descriptor structure                       */
extern	volatile	HCCA		*Hcca;
extern  volatile	uint8_t		*TDBuffer;        /* Current Buffer Pointer of transfer descriptor            */
extern  volatile	uint8_t		*FATBuffer;       /* Buffer used by FAT file system                           */
extern  volatile	uint8_t		*UserBuffer;      /* Buffer used by application                               */

                                          /*   GLOBAL VARIABLES
/***************************************************************************************************************
*/

/*
**************************************************************************************************************
*                                         DELAY IN MILLI SECONDS
*
* Description: This function provides a delay in milli seconds
*
* Arguments  : delay    The delay required
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Host_DelayMS (uint32_t  delay)
{
    volatile  uint32_t  i;


    for (i = 0; i < delay; i++) {
        Host_DelayUS(1000);
    }
}

/*
**************************************************************************************************************
*                                         DELAY IN MICRO SECONDS
*
* Description: This function provides a delay in micro seconds
*
* Arguments  : delay    The delay required
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Host_DelayUS (uint32_t  delay)
{
    volatile  uint32_t  i;


    for (i = 0; i < (4 * delay); i++) {    /* This logic was tested. It gives app. 1 micro sec delay        */
        ;
    }
}

/*
**************************************************************************************************************
*                                         INITIALIZE THE HOST CONTROLLER
*
* Description: This function initializes lpc17xx host controller
*
* Arguments  : None
*
* Returns    : 
*
**************************************************************************************************************
*/

void  Host_Init (void)
{
	uint32_t HostBaseAddr;

    LPC_SC->PCONP   |= 0x80000000;
    LPC_USB->OTGClkCtrl   = 0x0000001B;  /* Enable USB host clock                      */
    while ((LPC_USB->OTGClkSt & 0x0000001B) != 0x1B);
	
	LPC_USB->StCtrl = 0x3;

	LPC_IOCON->P0_29 &= ~0x07; /* USB_D+1 @ P0.29 */
	LPC_IOCON->P0_29 |= 0x01; /* USB_D+1 @ P0.29 */

	LPC_IOCON->P0_30 &= ~0x07; /* USB_D-1 @ P0.30 */
	LPC_IOCON->P0_30 |= 0x01; /* USB_D-1 @ P0.30 */

	LPC_IOCON->P1_19 &= ~0x07; /* USB_PPWR1N @ P1.19 */
	LPC_IOCON->P1_19 |= 0x02; /* USB_PPWR1N @ P1.19 */

	LPC_IOCON->P1_22 &= ~0x07; /* USB_PWRD1 @ P1.22 */
	LPC_IOCON->P1_22 |= 0x10; /*  P1.22 Pull UP resistor enable */

 	LPC_IOCON->P1_27 &= ~0x07; /* USB_OVRCR1N @ P1.27 */
	LPC_IOCON->P1_27 |= 0x10; /*  P1.27 Pull UP resistor enable */

//#if 0
//	LPC_IOCON->P0_31 &= ~0x9F; /* USB_D+2 @ P0.31 */
//	LPC_IOCON->P0_31 |= 0x01; /* USB_D+2 @ P0.31 */

//	LPC_IOCON->P0_12 &= ~0x1F; /* USB_PPWR2N @ P0.12 */
//	LPC_IOCON->P0_12 |= 0x01; /* USB_PPWR2N @ P0.12 */
//	LPC_IOCON->P1_30 &= ~0x1F; /* USB_PWRD2 @ P1.30 */
//	LPC_IOCON->P1_30 |= 0x01; /* USB_PWRD2 @ P1.30 */
//	LPC_IOCON->P1_31 &= ~0x1F; /* USB_OVRCR2N @ P1.31 */
//	LPC_IOCON->P1_31 |= 0x01; /* USB_OVRCR2N @ P1.31 */
//#endif 
	put_str("Initializing Host Stack\n");

	/* Set up host base address and TD and ED descriptors */
	HostBaseAddr = HOST_BASE_ADDR;

    Hcca       = (volatile  HCCA       *)(HostBaseAddr+0x000);
    TDHead     = (volatile  HCTD       *)(HostBaseAddr+0x100);
    TDTail     = (volatile  HCTD       *)(HostBaseAddr+0x110);
    EDCtrl     = (volatile  HCED       *)(HostBaseAddr+0x120); 
    EDBulkIn   = (volatile  HCED       *)(HostBaseAddr+0x130);
    EDBulkOut  = (volatile  HCED       *)(HostBaseAddr+0x140);
    TDBuffer   = (volatile  uint8_t *)(HostBaseAddr+0x150);
    FATBuffer  = (volatile  uint8_t *)(HostBaseAddr+0x1D0);
    UserBuffer = (volatile  uint8_t *)(HostBaseAddr+0x1000);
  
    /* Initialize all the TDs, EDs and HCCA to 0  */
    Host_EDInit(EDCtrl);
    Host_EDInit(EDBulkIn);
    Host_EDInit(EDBulkOut);
    Host_TDInit(TDHead);
    Host_TDInit(TDTail);
    Host_HCCAInit(Hcca);

    Host_DelayMS(50);                /* Wait 50 ms before apply reset              */
    LPC_USB->Control       = 0;    /* HARDWARE RESET                             */
    LPC_USB->ControlHeadED = 0;    /* Initialize Control list head to Zero       */
    LPC_USB->BulkHeadED    = 0;    /* Initialize Bulk list head to Zero          */
    
    /* SOFTWARE RESET                             */
    LPC_USB->CommandStatus = OR_CMD_STATUS_HCR;
    LPC_USB->FmInterval    = DEFAULT_FMINTERVAL;  /* Write Fm Interval and Largest Data Packet Counter */

                                                    /* Put HC in operational state                */
    LPC_USB->Control  = (LPC_USB->Control & (~OR_CONTROL_HCFS)) | OR_CONTROL_HC_OPER;
    LPC_USB->RhStatus = OR_RH_STATUS_LPSC;        /* Set Global Power                           */
    
    LPC_USB->HCCA = (uint32_t)Hcca;
    LPC_USB->InterruptStatus |= LPC_USB->InterruptStatus;                   /* Clear Interrrupt Status                    */

    LPC_USB->InterruptEnable  = OR_INTR_ENABLE_MIE |
                         OR_INTR_ENABLE_WDH |
                         OR_INTR_ENABLE_RHSC |
                         OR_INTR_ENABLE_UE;


    /* Enable the USB Interrupt */
	NVIC_EnableIRQ(USB_IRQn);               /* enable USB interrupt */
	NVIC_SetPriority (USB_IRQn, 0);			/* highest priority */

    put_str("Host Initialized\n");
}




/***************************************************************************************************************
*                                     PROCESS TRANSFER DESCRIPTOR
*
* Description: This function processes the transfer descriptor
*
* Arguments  : ed            Endpoint descriptor that contains this transfer descriptor
*              token         SETUP, IN, OUT
*              buffer        Current Buffer Pointer of the transfer descriptor
*              buffer_len    Length of the buffer
*
* Returns    : OK       if TD submission is successful
*              ERROR    if TD submission fails
*
**************************************************************************************************************
*/

int32_t  Host_ProcessTD (volatile  HCED       *ed,
                            volatile  uint32_t  token,
                            volatile  uint8_t *buffer,
                                      uint32_t  buffer_len)
{
    volatile  uint32_t   td_toggle;


    if (ed == EDCtrl) {
        if (token == TD_SETUP) {
            td_toggle = TD_TOGGLE_0;
        } else {
            td_toggle = TD_TOGGLE_1;
        }
    } else {
        td_toggle = 0;
    }
    TDHead->Control = (TD_ROUNDING    |
                      token           |
                      TD_DELAY_INT(0) |                           
                      td_toggle       |
                      TD_CC);
    TDTail->Control = 0;
    TDHead->CurrBufPtr   = (uint32_t) buffer;
    TDTail->CurrBufPtr   = 0;
    TDHead->Next         = (uint32_t) TDTail;
    TDTail->Next         = 0;
    TDHead->BufEnd       = (uint32_t)(buffer + (buffer_len - 1));
    TDTail->BufEnd       = 0;

    ed->HeadTd  = (uint32_t)TDHead | ((ed->HeadTd) & 0x00000002);
    ed->TailTd  = (uint32_t)TDTail;
    ed->Next    = 0;

    if (ed == EDCtrl) {
        LPC_USB->ControlHeadED  = (uint32_t)ed;
        LPC_USB->CommandStatus |= OR_CMD_STATUS_CLF;
        LPC_USB->Control       |= OR_CONTROL_CLE;
    } else {
        LPC_USB->BulkHeadED     = (uint32_t)ed;
        LPC_USB->CommandStatus |= OR_CMD_STATUS_BLF;
        LPC_USB->Control       |= OR_CONTROL_BLE;
    }    

    Host_WDHWait();

//    if (!(TDHead->Control & 0xF0000000)) {
	if (!HOST_TDControlStatus) {
        return (OK);
    } else {      
        return (ERR_TD_FAIL);
    }
}

/*
**************************************************************************************************************
*                                       ENUMERATE THE DEVICE
*
* Description: This function is used to enumerate the device connected
*
* Arguments  : None
*
* Returns    : None
*
**************************************************************************************************************
*/

int32_t  Host_EnumDev (void)
{
    int32_t  rc;

    put_str("Connect a Mass Storage device\n");
    while (!HOST_RhscIntr);
    Host_DelayMS(100);                             /* USB 2.0 spec says atleast 50ms delay beore port reset */
	if ( HOST_RhscIntr & 0x01 )
	{
	  LPC_USB->RhPortStatus1 = OR_RH_PORT_PRS; // Initiate port reset
	  while (LPC_USB->RhPortStatus1 & OR_RH_PORT_PRS)
		; // Wait for port reset to complete...
	  LPC_USB->RhPortStatus1 = OR_RH_PORT_PRSC; // ...and clear port reset signal
	}
	if ( HOST_RhscIntr & 0x02 )
	{
	  LPC_USB->RhPortStatus2 = OR_RH_PORT_PRS; // Initiate port reset
	  while (LPC_USB->RhPortStatus2 & OR_RH_PORT_PRS)
		; // Wait for port reset to complete...
	  LPC_USB->RhPortStatus2 = OR_RH_PORT_PRSC; // ...and clear port reset signal
	}
    Host_DelayMS(200);                                                 /* Wait for 100 MS after port reset  */

    EDCtrl->Control = 8 << 16;                                         /* Put max pkt size = 8              */
                                                                       /* Read first 8 bytes of device desc */
    rc = HOST_GET_DESCRIPTOR(USB_DESCRIPTOR_TYPE_DEVICE, 0, TDBuffer, 8);
    if (rc != OK) {
        putchar(rc);
        return (rc);
    }
    EDCtrl->Control = TDBuffer[7] << 16;                               /* Get max pkt size of endpoint 0    */
    rc = HOST_SET_ADDRESS(1);                                          /* Set the device address to 1       */
    if (rc != OK) {
        putchar(rc);
        return (rc);
    }
    Host_DelayMS(2);
    EDCtrl->Control = (EDCtrl->Control) | 1;                          /* Modify control pipe with address 1 */
                                                                      /* Get the configuration descriptor   */
    rc = HOST_GET_DESCRIPTOR(USB_DESCRIPTOR_TYPE_CONFIGURATION, 0, TDBuffer, 9);
    if (rc != OK) {
        putchar(rc);
        return (rc);
    }
                                                                       /* Get the first configuration data  */
    rc = HOST_GET_DESCRIPTOR(USB_DESCRIPTOR_TYPE_CONFIGURATION, 0, TDBuffer, ReadLE16U(&TDBuffer[2]));
    if (rc != OK) {
        putchar(rc);
        return (rc);
    }
    rc = MS_ParseConfiguration();                                      /* Parse the configuration           */
    if (rc != OK) {
        putchar(rc);
        return (rc);
    }
    rc = USBH_SET_CONFIGURATION(1);                                    /* Select device configuration 1     */
    if (rc != OK) {
        putchar(rc);
    }
    Host_DelayMS(100);                                               /* Some devices may require this delay */
    return (rc);
}

/*
**************************************************************************************************************
*                                        RECEIVE THE CONTROL INFORMATION
*
* Description: This function is used to receive the control information
*
* Arguments  : bm_request_type
*              b_request
*              w_value
*              w_index
*              w_length
*              buffer
*
* Returns    : OK       if Success
*              ERROR    if Failed
*
**************************************************************************************************************
*/
   
int32_t  Host_CtrlRecv (         uint8_t   bm_request_type,
                                    uint8_t   b_request,
                                    uint16_t   w_value,
                                    uint16_t   w_index,
                                    uint16_t   w_length,
                          volatile  uint8_t  *buffer)
{
    int32_t  rc;


    Host_FillSetup(bm_request_type, b_request, w_value, w_index, w_length);
    rc = Host_ProcessTD(EDCtrl, TD_SETUP, TDBuffer, 8);
    if (rc == OK) {
        if (w_length) {
            rc = Host_ProcessTD(EDCtrl, TD_IN, TDBuffer, w_length);
        }
        if (rc == OK) {
            rc = Host_ProcessTD(EDCtrl, TD_OUT, NULL, 0);
        }
    }
    return (rc);
}

/*
**************************************************************************************************************
*                                         SEND THE CONTROL INFORMATION
*
* Description: This function is used to send the control information
*
* Arguments  : None
*
* Returns    : OK		              if Success
*              ERR_INVALID_BOOTSIG    if Failed
*
**************************************************************************************************************
*/

int32_t  Host_CtrlSend (          uint8_t   bm_request_type,
                                     uint8_t   b_request,
                                     uint16_t   w_value,
                                     uint16_t   w_index,
                                     uint16_t   w_length,
                           volatile  uint8_t  *buffer)
{
    int32_t  rc;

    Host_FillSetup(bm_request_type, b_request, w_value, w_index, w_length);

    rc = Host_ProcessTD(EDCtrl, TD_SETUP, TDBuffer, 8);
    if (rc == OK) {
        if (w_length) {
            rc = Host_ProcessTD(EDCtrl, TD_OUT, TDBuffer, w_length);
        }
        if (rc == OK) {
            rc = Host_ProcessTD(EDCtrl, TD_IN, NULL, 0);
        }
    }
    return (rc);
}

/*
**************************************************************************************************************
*                                          FILL SETUP PACKET
*
* Description: This function is used to fill the setup packet
*
* Arguments  : None
*
* Returns    : OK		              if Success
*              ERR_INVALID_BOOTSIG    if Failed
*
**************************************************************************************************************
*/

void  Host_FillSetup (uint8_t   bm_request_type,
                      uint8_t   b_request,
                      uint16_t   w_value,
                      uint16_t   w_index,
                      uint16_t   w_length)
{
	int i;
	for (i=0;i<w_length;i++)
		TDBuffer[i] = 0;
	
    TDBuffer[0] = bm_request_type;
    TDBuffer[1] = b_request;
    WriteLE16U(&TDBuffer[2], w_value);
    WriteLE16U(&TDBuffer[4], w_index);
    WriteLE16U(&TDBuffer[6], w_length);
}



/*
**************************************************************************************************************
*                                         INITIALIZE THE TRANSFER DESCRIPTOR
*
* Description: This function initializes transfer descriptor
*
* Arguments  : Pointer to TD structure
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Host_TDInit (volatile  HCTD *td)
{

    td->Control    = 0;
    td->CurrBufPtr = 0;
    td->Next       = 0;
    td->BufEnd     = 0;
}

/*
**************************************************************************************************************
*                                         INITIALIZE THE ENDPOINT DESCRIPTOR
*
* Description: This function initializes endpoint descriptor
*
* Arguments  : Pointer to ED strcuture
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Host_EDInit (volatile  HCED *ed)
{

    ed->Control = 0;
    ed->TailTd  = 0;
    ed->HeadTd  = 0;
    ed->Next    = 0;
}

/*
**************************************************************************************************************
*                                 INITIALIZE HOST CONTROLLER COMMUNICATIONS AREA
*
* Description: This function initializes host controller communications area
*
* Arguments  : Pointer to HCCA
*
* Returns    : 
*
**************************************************************************************************************
*/

void  Host_HCCAInit (volatile  HCCA  *hcca)
{
    uint32_t  i;

    for (i = 0; i < 32; i++) {

        hcca->IntTable[i] = 0;
        hcca->FrameNumber = 0;
        hcca->DoneHead    = 0;
    }

}

/*
**************************************************************************************************************
*                                         WAIT FOR WDH INTERRUPT
*
* Description: This function is infinite loop which breaks when ever a WDH interrupt rises
*
* Arguments  : None
*
* Returns    : None
*
**************************************************************************************************************
*/

void  Host_WDHWait (void)
{
  while (!HOST_WdhIntr) {
    ;
  }
  HOST_WdhIntr = 0;
}

/*
**************************************************************************************************************
*                                         READ LE 32U
*
* Description: This function is used to read an unsigned integer from a charecter buffer in the platform
*              containing little endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*
* Returns    : val     Unsigned integer
*
**************************************************************************************************************
*/

uint32_t  ReadLE32U (volatile  uint8_t  *pmem)
{
    uint32_t   val;

    ((uint8_t *)&val)[0] = pmem[0];
    ((uint8_t *)&val)[1] = pmem[1];
    ((uint8_t *)&val)[2] = pmem[2];
    ((uint8_t *)&val)[3] = pmem[3];
    return (val);
}

/*
**************************************************************************************************************
*                                        WRITE LE 32U
*
* Description: This function is used to write an unsigned integer into a charecter buffer in the platform 
*              containing little endian processor.
*
* Arguments  : pmem    Pointer to the charecter buffer
*              val     Integer value to be placed in the charecter buffer
*
* Returns    : None
*
**************************************************************************************************************
*/

void  WriteLE32U (volatile  uint8_t  *pmem,
                            uint32_t   val)
{
    pmem[0] = ((uint8_t *)&val)[0];
    pmem[1] = ((uint8_t *)&val)[1];
    pmem[2] = ((uint8_t *)&val)[2];
    pmem[3] = ((uint8_t *)&val)[3];
}

/*
**************************************************************************************************************
*                                          READ LE 16U
*
* Description: This function is used to read an unsigned short integer from a charecter buffer in the platform
*              containing little endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*
* Returns    : val     Unsigned short integer
*
**************************************************************************************************************
*/

uint16_t  ReadLE16U (volatile  uint8_t  *pmem)
{
    uint16_t   val;

    ((uint8_t *)&val)[0] = pmem[0];
    ((uint8_t *)&val)[1] = pmem[1];
    return (val);
}

/*
**************************************************************************************************************
*                                         WRITE LE 16U
*
* Description: This function is used to write an unsigned short integer into a charecter buffer in the
*              platform containing little endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*              val     Value to be placed in the charecter buffer
*
* Returns    : None
*
**************************************************************************************************************
*/

void  WriteLE16U (volatile  uint8_t  *pmem,
                            uint16_t   val)
{
    pmem[0] = ((uint8_t *)&val)[0];
    pmem[1] = ((uint8_t *)&val)[1];
}

/*
**************************************************************************************************************
*                                         READ BE 32U
*
* Description: This function is used to read an unsigned integer from a charecter buffer in the platform
*              containing big endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*
* Returns    : val     Unsigned integer
*
**************************************************************************************************************
*/

uint32_t  ReadBE32U (volatile  uint8_t  *pmem)
{
    uint32_t   val;

    ((uint8_t *)&val)[0] = pmem[3];
    ((uint8_t *)&val)[1] = pmem[2];
    ((uint8_t *)&val)[2] = pmem[1];
    ((uint8_t *)&val)[3] = pmem[0];
    return (val);
}

/*
**************************************************************************************************************
*                                         WRITE BE 32U
*
* Description: This function is used to write an unsigned integer into a charecter buffer in the platform
*              containing big endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*              val     Value to be placed in the charecter buffer
*
* Returns    : None
*
**************************************************************************************************************
*/

void  WriteBE32U (volatile  uint8_t  *pmem,
                            uint32_t   val)
{
    pmem[0] = ((uint8_t *)&val)[3];
    pmem[1] = ((uint8_t *)&val)[2];
    pmem[2] = ((uint8_t *)&val)[1];
    pmem[3] = ((uint8_t *)&val)[0];
}

/*
**************************************************************************************************************
*                                         READ BE 16U
*
* Description: This function is used to read an unsigned short integer from a charecter buffer in the platform
*              containing big endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*
* Returns    : val     Unsigned short integer
*
**************************************************************************************************************
*/

uint16_t  ReadBE16U (volatile  uint8_t  *pmem)
{
    uint16_t  val;

    ((uint8_t *)&val)[0] = pmem[1];
    ((uint8_t *)&val)[1] = pmem[0];
    return (val);
}

/*
**************************************************************************************************************
*                                         WRITE BE 16U
*
* Description: This function is used to write an unsigned short integer into the charecter buffer in the
*              platform containing big endian processor
*
* Arguments  : pmem    Pointer to the charecter buffer
*              val     Value to be placed in the charecter buffer
*
* Returns    : None
*
**************************************************************************************************************
*/

void  WriteBE16U (volatile  uint8_t  *pmem,
                            uint16_t   val)
{
    pmem[0] = ((uint8_t *)&val)[1];
    pmem[1] = ((uint8_t *)&val)[0];
}
