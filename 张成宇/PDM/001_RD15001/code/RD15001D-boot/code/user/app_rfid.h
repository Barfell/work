#ifndef __APP_RFID_H
#define __APP_RFID_H	
#include "board.h"


#define RFIDDATACOUNT   50

#define RFID_RESET()        GPIO_ResetBits(RFID_RET_GPIO, RFID_RET_PIN)
#define RFID_UNRESET()      GPIO_SetBits(RFID_RET_GPIO, RFID_RET_PIN)

#define RFID_SHUTDOWN()     GPIO_ResetBits(RFID_SHUTDOWN_GPIO, RFID_SHUTDOWN_PIN)
#define RFID_UNSHUTDOWN()   GPIO_SetBits(RFID_SHUTDOWN_GPIO, RFID_SHUTDOWN_PIN)


#define RCC_RFID_CONFIG()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)   

#define RFID_RET_GPIO       GPIOE       
#define RFID_RET_PIN        GPIO_Pin_3

#define RFID_SHUTDOWN_GPIO  GPIOE    
#define RFID_SHUTDOWN_PIN   GPIO_Pin_2



enum
{
    BOOTLOADER_RUNNING,
    APPLICTATION_RUNNING
};

enum
{
    GETCURRENTPROGRAM = 0,
    BOOTFIRMWARE,
    SETFREQUENCYCHANNEL,
    SETPROTOCOL,
    SETANTENNA,
    CLEARBUFFER,
    SEARCHTAG,
    GETTAGDATA,   
    GETTAGDATAId,
    PRIMECONTINUEREADING,
    CONTINUEREADING,
    ENHANCEDISTANCE,
    ENHANCESPEED1,
    ENHANCESPEED2,
    ENHANCESPEED3,
    ENHANCESPEED4,
    ENHANCESPEED5,
    ENHANCESPEED6,
    CONTINUEREADINGEX,
    STOPREADING
    
};

enum
{
    RFID_TAG1 = 0,
    RFID_TAG2,
    RFID_TAG3,
    RFID_TAG4,
    RFID_TAG5,
    RFID_TAG6,
    RFID_TAG7,
    RFID_TAG8,
    RFID_TAG9,
    RFID_TAG10,
    RFID_TAG11,
    RFID_TAG12,
    RFID_TAG13
};

typedef struct  _tagRfid
{
    U8 u8CmdType;
    U8 szCmdSenddata[RFIDDATACOUNT];
    U8 szReceivedata[RFIDDATACOUNT];
    U8 u8SendCount;
    U8 u8ReceiveCount;
    U8 u8RfidState;
    U8 u8Tag;
       
} CRfidVar, *PCRfidVar; 


extern CRfidVar g_cRfidVar;

BOOL CompareTag(U8 *pBuf);
BOOL SendAndWaitRfidDataProc(U8 u8CmdType);
U16 CalculateRfidCrc(U8 *u8Buf, U16 len);
VOID RfidInitProc(VOID);

#endif 















