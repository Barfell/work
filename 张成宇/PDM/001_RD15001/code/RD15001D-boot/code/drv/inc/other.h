#ifndef _OTHER_H
#define _OTHER_H

#include "board.h"

enum
{
    ERR_RFID_STEP_1 = 1,
    ERR_RFID_STEP_2,
    ERR_RFID_STEP_3,
    ERR_RFID_STEP_4,
    ERR_RFID_STEP_5,
    ERR_RFID_STEP_6,
    ERR_RFID_STEP_7,
    ERR_RFID_STEP_8,
    ERR_RFID_STOP,
    ERR_NAND_BADBLOCK_FULL,
    ERR_NAND_FULL,
    ERR_NAND_MALLOC_FAIL,
    ERR_GPS_NAND_FULL,
    ERR_INS_NAND_FULL,
    ERR_OTHER_NAND_FULL,
    ERR_RFID_NAND_FULL,
    ERR_UPAN_OPEN_FAIL,
    ERR_UPAN_WRITE_FAIL,
    ERR_UPAN_READ_FAIL,
    ERR_UPAN_CLOSE_FAIL,
    ERR_USATT1_MALLOC_FAIL,
    ERR_USATT2_MALLOC_FAIL,
    ERR_USATT3_MALLOC_FAIL,
    ERR_OTHER_MALLOC_FAIL,
    ERR_OTHER_SPACE_FULL,
    ERR_INS_SPACE_FULL,
    ERR_GPS_SPACE_FULL,
    ERR_COMM_MALLOC_FAIL,
    ERR_TEST_MALLOC_FAIL,
    ERR_SD_WRITE_FAIL,
    ERR_SD_READ_FAIL,    
    ERR_ADD_FAIL,
};

VOID NMI_Handler(VOID);
VOID HardFault_Handler(VOID);
VOID MemManage_Handler(VOID);
VOID BusFault_Handler(VOID);
VOID UsageFault_Handler(VOID);
VOID SVC_Handler(VOID);
VOID DebugMon_Handler(VOID);
VOID PendSV_Handler(VOID);
VOID SysTick_Handler(VOID);
VOID EnterException(U32 u32ErrCode);
VOID OtherInit(VOID);
VOID HandleOtherDataProc(VOID);
BOOL GetOtherWorkState(VOID);
VOID SetOtherWorkState(BOOL bValue);


#ifdef __cplusplus
 extern "C" {
#endif 


#ifdef __cplusplus
}
#endif



#endif
