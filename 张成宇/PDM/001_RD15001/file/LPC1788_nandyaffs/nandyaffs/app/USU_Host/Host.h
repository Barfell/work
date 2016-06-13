#ifndef __HOST_H__
#define __HOST_H__
int gUSBConnected;

volatile	uint32_t   HOST_RhscIntr = 1;         /* Root Hub Status Change interrupt                       */
volatile	uint32_t   HOST_WdhIntr  = 0;         /* Semaphore to wait until the TD is submitted            */
volatile	uint8_t    HOST_TDControlStatus = 0;
volatile	HCED        *EDCtrl;                    /* Control endpoint descriptor structure                  */
volatile	HCED        *EDBulkIn;                  /* BulkIn endpoint descriptor  structure                  */
volatile	HCED        *EDBulkOut;                 /* BulkOut endpoint descriptor structure                  */
volatile	HCTD        *TDHead;                    /* Head transfer descriptor structure                     */
volatile	HCTD        *TDTail;                    /* Tail transfer descriptor structure                     */
volatile	HCCA        *Hcca;                      /* Host Controller Communications Area structure          */ 
			uint16_t  *TDBufNonVol;               /* Identical to TDBuffer just to reduce compiler warnings */
volatile	uint8_t  *TDBuffer;                  /* Current Buffer Pointer of transfer descriptor          */
volatile	uint8_t  *FATBuffer;                 /* Buffer used by FAT file system                         */
volatile	uint8_t  *UserBuffer;                /* Buffer used by application                             */

volatile	uint32_t  UnrecoverableIntCount = 0;
#endif