/* */
#include "bsp.h"
#include "lpc_types.h"
#include "SST39VF1601.h"
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_timer.h"

uint32_t system_base = 0x90000000;  // 4Guint8_t System Memory Address.
#define sysAddress(offset) ((volatile uint16_t *)(system_base + (offset<<1)))
   	// The user should modify this address accordingly.

/*********************************************************************//**
 * @brief 		Delay
 * @param[in]	delayCnt Delay value
 * @return 		None
 **********************************************************************/
void delay_ns(uint32_t delayCnt)
{
	uint32_t i;

	for ( i = 0; i < delayCnt; i++ );
	return;
}

/*********************************************************************//**
 * @brief 		Initialize external NOR FLASH memory
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void NORFLASHInit( void )
{
//	TIM_TIMERCFG_Type TIM_ConfigStruct;
	/**************************************************************************
	* Initialize EMC for NOR FLASH
	**************************************************************************/
	EMC_Init();
	delay_ns(100);

	EMC_StaMemConfigMW (1,EMC_StaticConfig_MW_16BITS);
	EMC_StaMemConfigPB(1,EMC_StaticConfig_PB);
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITWEN, EMC_StaticWaitWen_WAITWEN(2));
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITOEN, EMC_StaticWaitOen_WAITOEN(2));
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITRD, EMC_StaticWaitRd_WAITRD(0x1f));
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITPAGE, EMC_StaticwaitPage_WAITPAGE(0x1f));
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITWR, EMC_StaticWaitwr_WAITWR(0x1f));
	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITTURN, EMC_StaticWaitTurn_WAITTURN(0x1f));

	//delay time
 //	TIM_Waitms(10);
	delay_ns(150);

  	return;
}
/************************************************************************/
/* PROCEDURE:   Check_SST_39VF160X                                      */
/*                                                                      */
/* This procedure decides whether a physical hardware device has a      */
/* SST39VF160X 16 Mbit MPF+ Device installed or not.         		*/
/*                                                                      */
/* Input:                                                               */
/*          None                                                        */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates a SST39VF160X                       */
/*          return FALSE: indicates not a SST39VF160X                   */
/************************************************************************/
int Check_SST_39VF160X(void)
{
    uint16_t SST_id1;
    uint16_t SST_id2;
    int  ReturnStatus;

    //  Issue the Software Product ID code to 39VF160X
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0090;  // write data 0x0090 to device addr 0x5555
	delay_ns(100);

    // Read the product ID from 39VF160X
    SST_id1  = *sysAddress(0x0000);   // get first ID uint8_t
    SST_id2  = *sysAddress(0x0001);   // get second ID uint8_t

    // ------------------------------------------------------------
    // Determine whether there is a SST 39VF1601 installed or not
    // use the following code:

    if (((SST_id1 == SST_ID) && (SST_id2 == SST_39VF1601))||((SST_id1 == SST_ID) && (SST_id2 == SST_39VF1602)))
            ReturnStatus = TRUE;
    else
            ReturnStatus = FALSE;

    // ------------------------------------------------------------

    // Issue the Software Product ID Exit code, thus returning the
    // 39VF160X to the normal operation.
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00F0;  // write data 0x00F0 to device addr 0x5555
    delay_ns(100);   // Tida Max 150ns for 39VF160X
                                    
    return (ReturnStatus);
}


/************************************************************************/
/* PROCEDURE:   CFI_Query                                               */
/*                                                                      */
/* This procedure should be used to query for CFI information           */
/*                                                                      */
/* Input:                                                               */
/*          Src	Source address to store CFI_Query data string		*/
/*                                                                      */
/* Output:                                                              */
/*          None                                                        */
/************************************************************************/
void CFI_Query(uint16_t *Src)
{ 
	uint16_t index;
    //  Issue the CFI Query entry code to 39VF160X
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0098;  // write data 0x0098 to device addr 0x5555
    Delay(1);     // insert delay time = Tida

    // ----------------------------------------------------------
    //  Perform all CFI operations here:
    //  CFI_Query_address is from 0010H--0034H

    for (index = 0x0010; index <= 0x0034; index++)
    {
     	 *Src = *sysAddress(index);
         ++Src;
	// CFI query data is stored in user-defined memory space.
    }
    // ----------------------------------------------------------

        // Issue the CFI Exit code thus returning the 39VF160X
        // to the read operating mode

    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00F0;  // write data 0x00F0 to device addr 0x5555
    Delay(1);     // insert delay time = Tida
}


/************************************************************************/
/* PROCEDURE:   SecID_Query                                             */
/*                                                                      */
/* This procedure should be used to query for Security ID information.  */
/*                                                                      */
/* Input:                                                               */
/*          SST_SecID	Source address to store SST SecID string	*/
/*          User_SecID	Source address to store User SecID string	*/
/*                                                                      */
/* Output:                                                              */
/*          None                                                        */
/************************************************************************/
void SecID_Query(uint16_t *SST_SecID, uint16_t *User_SecID)
{
     uint16_t index;
	     //  Issue the SecID Entry code to 39VF160X
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0088;  // write data 0x0088 to device addr 0x5555
    Delay(1);      // insert delay time = Tida

    	//  Perform all Security ID operations here:
    	//  	SST programmed segment is from address 000000H--000007H,
    	//  	User programmed segment is from address 000010H--000017H.

    for (index = 0x0000; index <= 0x0007; index++)
    {
    	 *SST_SecID = *sysAddress(index);
         ++SST_SecID;
         *User_SecID = *sysAddress(index+0x0010);
         ++User_SecID;
	// Security query data is stored in user-defined memory space.
    }
        // Issue the Sec ID Exit code thus returning the 39VF160X
        // to the read operating mode
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00F0;  // write data 0x00F0 to device addr 0x5555
    Delay(1);      // insert delay time = Tida
}


/************************************************************************/
/* PROCEDURE:   Erase_One_Sector                                        */
/*                                                                      */
/* This procedure can be used to erase a total of 2048 uint16_ts.           */
/*                                                                      */
/* Input:                                                               */
/*      Dst     DESTINATION address where the erase operation starts    */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates success in sector-erase             */
/*          return FALSE: indicates failure in sector-erase             */
/************************************************************************/
int Erase_One_Sector(uint32_t Dst)
{
	uint32_t DestBuf = Dst;
   int  ReturnStatus;

	//  Issue the Sector Erase command to 39VF160X
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(0x5555) = 0x0080;     // write data 0x0080 to device addr 0x5555
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(DestBuf) = 0x0030;    // write data 0x0030 to device sector addr

   ReturnStatus = Check_Toggle_Ready(DestBuf);	// wait for TOGGLE bit ready

   return ReturnStatus;
}


/************************************************************************/
/* PROCEDURE:   Erase_One_Block                                         */
/*                                                                      */
/* This procedure can be used to erase a total of 32K uint16_ts.            */
/*                                                                      */
/* Input:                                                               */
/*      Dst     DESTINATION address where the erase operation starts    */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates success in block-erase              */
/*          return FALSE: indicates failure in block-erase              */
/************************************************************************/
int Erase_One_Block (uint32_t Dst)
{
   uint32_t DestBuf = Dst;
   int ReturnStatus;

    //  Issue the Block Erase command to 39VF160X
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(0x5555) = 0x0080;     // write data 0x0080 to device addr 0x5555
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(DestBuf) = 0x0050;    // write data 0x0050 to device sector addr

   ReturnStatus = Check_Toggle_Ready(DestBuf);	  	// wait for TOGGLE bit ready

   return ReturnStatus;
}


/************************************************************************/
/* PROCEDURE:   Erase_Entire_Chip                                       */
/*                                                                      */
/* This procedure can be used to erase the entire chip.                 */
/*                                                                      */
/* Input:                                                               */
/*      NONE                                                            */
/*                                                                      */
/* Output:                                                              */
/*      NONE                                                            */
/************************************************************************/
void Erase_Entire_Chip(void)
{
   //  Issue the Chip Erase command to 39VF160X
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(0x5555) = 0x0080;     // write data 0x0080 to device addr 0x5555
	*sysAddress(0x5555) = 0x00AA;     // write data 0x00AA to device addr 0x5555
	*sysAddress(0x2AAA) = 0x0055;     // write data 0x0055 to device addr 0x2AAA
	*sysAddress(0x5555) = 0x0010;     // write data 0x0010 to device addr 0x5555

   delay_ns(100);       	// Delay Tsce time
}


/************************************************************************/
/* PROCEDURE:   Program_One_uint16_t                                        */
/*                                                                      */
/* This procedure can be used to program ONE uint16_t of data to the        */
/* 39VF160X.                                                            */
/*                                                                      */
/* NOTE:  It is necessary to first erase the sector containing the      */
/*        uint16_t to be programmed.                                	*/
/*                                                                      */
/* Input:                                                               */
/*           Srcuint16_t The uint16_t which will be written to the 39VF160X     */
/*           Dst     DESTINATION address which will be written with the */
/*                   data passed in from Src                            */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates success in uint16_t-program             */
/*          return FALSE: indicates failure in uint16_t-program             */
/************************************************************************/
int Program_One_uint16_t (uint16_t *Srcuint16_t,   uint32_t Dst)
{
    uint32_t DestBuf = Dst;
    uint16_t *SourceBuf = Srcuint16_t;
    int ReturnStatus;

    *sysAddress(0x5555) = 0x00AA; // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055; // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00A0; // write data 0x00A0 to device addr 0x5555
    *sysAddress(DestBuf) = *SourceBuf; // transfer the uint16_t to destination

    ReturnStatus = Check_Toggle_Ready(DestBuf); // wait for TOGGLE bit ready

    return ReturnStatus;
}


/************************************************************************/
/* PROCEDURE:   Program_One_Sector                                      */
/*                                                                      */
/* This procedure can be used to program a total of 2048 uint16_ts of data  */
/* to the SST39VF160X.                                                  */
/*                                                                      */
/* NOTES: 1. It is necessary to first erase the sector before the	*/
/*        programming.                                			*/
/*        2. This sample code assumes the destination address passed	*/
/*        from the calling function is the starting address of the	*/
/*        sector.							*/
/*                                                                      */
/* Input:                                                               */
/*           Src     SOURCE address containing the data which will be   */
/*                   written to the 39VF160X                            */
/*           Dst     DESTINATION address which will be written with the */
/*                   data passed in from Src                            */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates success in sector-program           */
/*          return FALSE: indicates failure in sector-program           */
/************************************************************************/
int Program_One_Sector (uint16_t *Src, uint32_t Dst)
{

    uint16_t *SourceBuf;
    uint32_t DestBuf;
    int Index, ReturnStatus;

    SourceBuf = Src;
    DestBuf = Dst;
    ReturnStatus = Erase_One_Sector(DestBuf);	// erase the sector first
    if (!ReturnStatus)
    	return ReturnStatus;

    for (Index = 0; Index < SECTOR_SIZE; Index++)
    { 	// transfer data from source to destination
	ReturnStatus = Program_One_uint16_t( SourceBuf, DestBuf);
	++DestBuf;
	++SourceBuf;

        if (!ReturnStatus)
    	   return ReturnStatus;
    }

    return ReturnStatus;
}


/************************************************************************/
/* PROCEDURE:   Program_One_Block                                       */
/*                                                                      */
/* This procedure can be used to program a total of 32k uint16_ts of data   */
/* to the SST39VF160X.                                                  */
/*                                                                      */
/* NOTES: 1. It is necessary to first erase the block before the	*/
/*        programming.                                			*/
/*        2. This sample code assumes the destination address passed	*/
/*        from the calling function is the starting address of the	*/
/*        block.							*/
/*									*/
/* Input:                                                               */
/*           Src     SOURCE address containing the data which will be   */
/*                   written to the 39VF160X                            */
/*           Dst     DESTINATION address which will be written with the */
/*                   data passed in from Src                            */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates success in block-program            */
/*          return FALSE: indicates failure in block-program            */
/************************************************************************/
int Program_One_Block (uint16_t *Src, uint32_t Dst)
{
    uint16_t *SourceBuf;
    uint32_t DestBuf;
    int Index, ReturnStatus;

    SourceBuf = Src;
    DestBuf = Dst;
    ReturnStatus = Erase_One_Block(DestBuf);	// erase the block first
    if (!ReturnStatus)
    	return ReturnStatus;

    for (Index = 0; Index < BLOCK_SIZE; Index++)
    { 	// transfer data from source to destination
	ReturnStatus = Program_One_uint16_t( SourceBuf, DestBuf);
	++DestBuf;
	++SourceBuf;

        if (!ReturnStatus)
    	return ReturnStatus;
    }

    return ReturnStatus;
}


/************************************************************************/
/* PROCEDURE:   SecID_Lock_Status                                       */
/*                                                                      */
/* This procedure should be used to check the Lock Status of SecID	*/
/*                                                                      */
/* Input:                                                               */
/*          None                                                        */
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates SecID is Locked  			 */
/*          return FALSE: indicates SecID is Unlocked  	  	 */
/************************************************************************/
int SecID_Lock_Status(void)
{
    uint16_t SecID_Status;

         //  Issue the Sec ID Entry code to 39VF160X
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0088;  // write data 0x0088 to device addr 0x5555
    Delay(1);      // insert delay time = Tida

    	//  Read Lock Status of SecID segment
    SecID_Status = *sysAddress(0x00FF);
    SecID_Status &= 0x0008; // Unlocked: DQ3=1; Locked: DQ3=0

        // Issue the Sec ID Exit code thus returning the 39VF160X
        // to the read operating mode
    *sysAddress(0x5555) = 0x00AA;  // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00F0;  // write data 0x00F0 to device addr 0x5555
    Delay(1);      // insert delay time = Tida

    if (!SecID_Status)
    	return TRUE;		   // SecID segment is Locked

    return FALSE;   		   // SecID segment is Unlocked
}


/************************************************************************/
/* PROCEDURE:   User_SecID_uint16_t_Program                                 */
/*                                                                      */
/* This procedure can be used to program data into the User SecID       */
/* segment (from 000010H--000017H) in 39VF160X.       			*/
/*                                                                      */
/* NOTE:  1. It's recommended to lock out the SecID segment after the 	*/
/*	  completion of program.					*/
/*	  2. There's no way to unlock the SecID segment once it's	*/ 
/*	  locked.							*/
/*                                                                      */
/* Input:                                                               */
/*           Srcuint16_t	Source address to fetch data			*/
/*           Dst  	Destination address to write data		*/
/*           length  	number of uint16_t needs to be programmed		*/
/*                                                                      */
/* Output:                                                              */
/*          return TRUE:  indicates SecID program is successful         */
/*          return FALSE: indicates SecID program is failed or SecID    */
/*			  is locked.					*/
/************************************************************************/
int User_SecID_uint16_t_Program (uint16_t *Srcuint16_t, uint16_t *Dst, int length)
{
    uint16_t *DestBuf = Dst;
    uint16_t *SourceBuf = Srcuint16_t;
    int test, index=length;

    test = SecID_Lock_Status ();  // check whether the SecID is Locked or not
    if (test)                     // TRUE: SecID is Locked
    	return FALSE;

    while (index--)
    {
    	*sysAddress(0x5555) = 0x00AA; // write data 0x00AA to device addr 0x5555
    	*sysAddress(0x2AAA) = 0x0055; // write data 0x0055 to device addr 0x2AAA
    	*sysAddress(0x5555) = 0x00A5; // write data 0x00A5 to device addr 0x5555
    	*sysAddress(*DestBuf) = *SourceBuf; // transfer the uint16_t to destination	 YJ
      ++DestBuf;
      ++SourceBuf;
    	// Read the toggle bit to detect end-of-write for the Sec ID.
      	// Do Not use Data# Polling for User_SecID_uint16_t_Program.
      test = Check_Toggle_Ready((uint32_t)DestBuf); // wait for TOGGLE bit to get ready
      if (!test)
    	return FALSE;   // SecID uint16_t-Program failed!
    }

    return TRUE;
}


/************************************************************************/
/* PROCEDURE:   User_SecID_Lock_Out                                     */
/*                                                                      */
/* This procedure can be used to Lock Out the User Seccurity ID.        */
/* User Security ID segment, from 000010H--000017H, in 39VF160X.        */
/*                                                                      */
/* NOTE:  1. Call SecID_Lock_Status() first to verify the SecID is 	*/
/*	  unlocked.							*/
/*	  2. SecID segment can't be erased.				*/
/*	  3. SecID segment can't be unlocked once it's locked.		*/
/*                                                                      */
/* Input:    None                                                       */
/*                                                                      */
/* Output:   None                                                       */
/************************************************************************/
void User_SecID_Lock_Out (void)
{
    *sysAddress(0x5555) = 0x00AA; // write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055; // write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0085; // write data 0x0085 to device addr 0x5555
    *sysAddress(0x00FF) = 0x0000; // write data 0x0000 to any addr

    Delay(1);	// Wait for uint16_t-Program timeout, Tbp=10us
}


/************************************************************************/
/* PROCEDURE:   Erase_Suspend		                		*/
/*                                                                      */
/* This procedure can be used to temporarily suspend a Sector/Block-	*/
/* Erase operation in 39VF160X.  					*/
/*                                                                      */
/* Input:    None                                                       */
/*                                                                      */
/* Output:   None                                                       */
/************************************************************************/
void Erase_Suspend (void)
{
    *sysAddress(0x5555) = 0x00B0; // write data 0x00B0 to any addr, i.e. 0x5555

    Delay(1);	// The device automatically enters read mode
    		// typically within 20 us after the Erase-Suspend command issued.
}


/************************************************************************/
/* PROCEDURE:   Erase_Resume		              			*/
/*                                                                      */
/* This procedure can be used to resume a Sector-Erase or Block-Erase   */
/* operation that had been suspended in 39VF160X.  	 		*/
/*                                                                      */
/* Input:    None                                                       */
/*                                                                      */
/* Output:   None                                                       */
/************************************************************************/
void Erase_Resume (void)
{
    *sysAddress(0x5555) = 0x0030; // write data 0x0030 to any addr, i.e. 0x5555
}


/************************************************************************/
/* PROCEDURE:    Check_Toggle_Ready                                     */
/*                                                                      */
/* During the internal program cycle, any consecutive read operation    */
/* on DQ6 will produce alternating 0's and 1's i.e. toggling between    */
/* 0 and 1. When the program cycle is completed, DQ6 of the data will   */
/* stop toggling. After the DQ6 data bit stops toggling, the device is  */
/* ready for next operation.                                            */
/*                                                                      */
/* Input:                                                               */
/*           Dst        must already be set-up by the caller            */
/*                                                                      */
/* Output:   TRUE   Data toggling success                               */
/*           FALSE  Time out                                            */
/************************************************************************/
int Check_Toggle_Ready (uint32_t Dst)
{
    uint16_t PreData;
    uint16_t CurrData;
    unsigned long TimeOut = 0;

    PreData = *sysAddress(Dst);
    PreData = PreData & 0x0040;          // read DQ6
    while (TimeOut < MAX_TIMEOUT)	 // MAX_TIMEOUT=0x07FFFFFF
    {
        CurrData = *sysAddress(Dst);
        CurrData = CurrData & 0x0040;    // read DQ6 again
        if (PreData == CurrData)
        {
	    return TRUE;
        }
	PreData = CurrData;
        TimeOut++;
    }
    return FALSE;
}


/************************************************************************/
/* PROCEDURE:   Check_Data_Polling                                      */
/*                                                                      */
/* During the internal program cycle, any attempt to read DQ7 of the    */
/* last uint8_t loaded during the page/uint8_t-load cycle will receive the    */
/* complement of the true data.  Once the program cycle is completed,   */
/* DQ7 will show true data.                                             */
/*                                                                      */
/* Input:                                                               */
/*           Dst        must already be set-up by the caller            */
/*           TrueData 	this is the original (true) data            	*/
/*                                                                      */
/* Output:                                                              */
/*           TRUE   Data polling success                                */
/*           FALSE  Time out                                            */
/************************************************************************/
int Check_Data_Polling (uint32_t Dst, uint16_t TrueData)
{
    uint16_t CurrData;
    unsigned long int TimeOut = 0;

    TrueData = TrueData & 0x0080; 	// read D7
    while (TimeOut < MAX_TIMEOUT)	// MAX_TIMEOUT=0x07FFFFFF
    {
	 CurrData = *sysAddress(Dst);
	 CurrData = CurrData & 0x0080;   // read DQ7
	 if (TrueData == CurrData)
         {
	    return TRUE;
         }
	 TimeOut++;
    }
    return FALSE;
}  

