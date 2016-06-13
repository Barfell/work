#include "app_save.h"


//FRAM      MEMMAP
/*
//0~4K no use
//4k~44k--40k 5页数据
#define FRAM_GPS_START_ADDRESS              0x1000          //4k
#define FRAM_GPS_END_ADDRESS                0xAFFF          //44k

//44k~84k--40k 5页数据
#define FRAM_INS_START_ADDRESS              0xB000          //44k
#define FRAM_INS_END_ADDRESS                0x15FFF         //84k

//84k~124k--40k 5页数据
#define FRAM_OTHER_START_ADDRESS            0x16000         //84k
#define FRAM_OTHER_END_ADDRESS              0x1EFFF         //124k

//84k~124k--40k 5页数据
#define FRAM_RFID_START_ADDRESS            0x16000         //84k
#define FRAM_RFID_END_ADDRESS              0x1EFFF         //124k

//124k~128k no use
*/
//FRAM      MEMMAP 
//0k~40k--40k 5页数据
#define FRAM_GPS_START_ADDRESS              0x0             //0k
#define FRAM_GPS_END_ADDRESS                0x9FFF          //40k
    
//40k~80k--40k 5页数据
#define FRAM_INS_START_ADDRESS              0xA000          //40k
#define FRAM_INS_END_ADDRESS                0x13FFF         //80k
    
//80k~120k--40k 5页数据
#define FRAM_OTHER_START_ADDRESS            0x14000         //80k
#define FRAM_OTHER_END_ADDRESS              0x1DFFF         //120k
    
//120k~128k--8k 1页数据
#define FRAM_RFID_START_ADDRESS             0x1E000         //120k
#define FRAM_RFID_END_ADDRESS               0x1FFFF         //128k
//NAND    MEMMAP
//NAND_ADDRESS_tag.Zone = 0x00;
//NAND_ADDRESS_tag.Block = 0x00;
//NAND_ADDRESS_tag.Page = 0x00;
//1页 = 8KB，一个块 = 128页， 一个区 = 1024块， 共4个区,
//第一个区存储GPS，区号是0，Block最大是1023，页最大是127.容量为1GBYTES.
//第二个区存储INS，区号是1，Block最大是1023，页最大是127.容量为1GBYTES.
//第三个区存储里程和轨距和RFID，区号是2，Block最大是1023，页最大是127.容量为1GBYTES.
//第四个区暂时不使用，区号是0，Block最大是1023，页最大是127.容量为1GBYTES.

#define NAND_GPS_ZONE           0
#define NAND_INS_ZONE           1
#define NAND_OTHER_ZONE         2
#define NAND_RFID_ZONE          3

#define MAXQUEUESIZE	0XA000      //40K

//#define MAXQUEUESIZE	0XA000      //40K
typedef U32 QueueDataType;

typedef struct _tagQueueInfo
{
	QueueDataType Front;
	QueueDataType Rear;
    QueueDataType Start;
    QueueDataType End;
    
}CQueueInfo, *PQueueInfo;


typedef struct _tagSaveVar
{
    BOOL bNandFlashEmptyFlag;
    
}CSaveVar,*PSaveVar;

STATIC CQueueInfo cQueueGpsInfo, cQueueInsInfo, cQueueOtherInfo, cQueueRfidInfo;

STATIC CSaveVar cSaveGpsVar, cSaveInsVar, cSaveOtherVar, cSaveRfidVar;
STATIC NAND_ADDRESS NandGpsAddress, NandInsAddress, NandOtherAddress, NandRfidAddress;

QueueDataType GetQueueLength(PQueueInfo pQueueInfo)
{
    QueueDataType Ret;
    pQueueInfo->Rear = pQueueInfo->Rear - pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front - pQueueInfo->Start;
	Ret = (pQueueInfo->Rear - pQueueInfo->Front + MAXQUEUESIZE) % MAXQUEUESIZE;
    pQueueInfo->Rear = pQueueInfo->Rear + pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front + pQueueInfo->Start;
    return Ret;
}
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType OffSet)
{
    BOOL bState;
    pQueueInfo->Rear = pQueueInfo->Rear - pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front - pQueueInfo->Start;
	if((pQueueInfo->Rear + OffSet) % MAXQUEUESIZE == pQueueInfo->Front)
	{
		bState = FALSE;
	}
    else
    {
    	pQueueInfo->Rear = (pQueueInfo->Rear + OffSet) % MAXQUEUESIZE;
    	bState = TRUE;
    }
    pQueueInfo->Rear = pQueueInfo->Rear + pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front + pQueueInfo->Start;
    return bState;
}

BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType OffSet)
{
    BOOL bState;
    pQueueInfo->Rear = pQueueInfo->Rear - pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front - pQueueInfo->Start;
	if(pQueueInfo->Front == pQueueInfo->Rear)
	{
		bState = FALSE;
	}
    else
    {
    	pQueueInfo->Front = (pQueueInfo->Front + OffSet) % MAXQUEUESIZE;
        bState = TRUE;
    }
    pQueueInfo->Rear = pQueueInfo->Rear + pQueueInfo->Start;
    pQueueInfo->Front= pQueueInfo->Front + pQueueInfo->Start;
	return bState;
}
//QueueDataType GetQueueLength(PQueueInfo pQueueInfo)
//{
//	return (cQueueInfo.Rear - cQueueInfo.Front);
//}
//BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType OffSet)
//{
//    BOOL bState;
//	if((pQueueInfo->Rear + OffSet)  > pQueueInfo->End)
//	{
//		bState = FALSE;
//	}
//    else
//    {
//    	pQueueInfo->Rear = (pQueueInfo->Rear + OffSet);
//    	bState = TRUE;
//    }
//    return bState;
//}

//BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType OffSet)
//{
//    BOOL bState;
//	if(pQueueInfo->Front == pQueueInfo->Rear)
//	{
//		bState = FALSE;
//	}
//    else
//    {
//    	pQueueInfo->Front = pQueueInfo->Front + OffSet;
//        bState = TRUE;
//    }
//	return bState;
//}

VOID SaveDataInit(VOID)
{
    memset(&cSaveGpsVar, 0, sizeof(CSaveVar));
    memset(&cSaveInsVar, 0, sizeof(CSaveVar));
    memset(&cSaveOtherVar, 0, sizeof(CSaveVar));
    memset(&cSaveRfidVar, 0, sizeof(CSaveVar));

    cSaveGpsVar.bNandFlashEmptyFlag = TRUE;
    cSaveInsVar.bNandFlashEmptyFlag = TRUE;
    cSaveOtherVar.bNandFlashEmptyFlag = TRUE;
    cSaveRfidVar.bNandFlashEmptyFlag = TRUE;

    cQueueGpsInfo.Front = FRAM_GPS_START_ADDRESS;
    cQueueGpsInfo.Rear= FRAM_GPS_START_ADDRESS;
    cQueueGpsInfo.Start= FRAM_GPS_START_ADDRESS;
    cQueueGpsInfo.End= FRAM_GPS_END_ADDRESS;
    
    cQueueInsInfo.Front = FRAM_INS_START_ADDRESS;
    cQueueInsInfo.Rear= FRAM_INS_START_ADDRESS;
    cQueueInsInfo.Start= FRAM_INS_START_ADDRESS;
    cQueueInsInfo.End= FRAM_INS_END_ADDRESS;
    
    cQueueOtherInfo.Front = FRAM_OTHER_START_ADDRESS;
    cQueueOtherInfo.Rear= FRAM_OTHER_START_ADDRESS;
    cQueueOtherInfo.Start= FRAM_OTHER_START_ADDRESS;
    cQueueOtherInfo.End= FRAM_OTHER_END_ADDRESS;
    
    cQueueRfidInfo.Front = FRAM_RFID_START_ADDRESS;
    cQueueRfidInfo.Rear= FRAM_RFID_START_ADDRESS;
    cQueueRfidInfo.Start= FRAM_RFID_START_ADDRESS;
    cQueueRfidInfo.End= FRAM_RFID_END_ADDRESS;
    
    memset(&NandGpsAddress, 0, sizeof(NAND_ADDRESS));
    memset(&NandInsAddress, 0, sizeof(NAND_ADDRESS));
    memset(&NandOtherAddress, 0, sizeof(NAND_ADDRESS));
    memset(&NandRfidAddress, 0, sizeof(NAND_ADDRESS));
    
    NandGpsAddress.Zone = NAND_GPS_ZONE;
    NandInsAddress.Zone = NAND_INS_ZONE;
    NandOtherAddress.Zone = NAND_OTHER_ZONE;
    NandRfidAddress.Zone = NAND_RFID_ZONE;
      
    NAND_Reset();
    
}

VOID SaveFram(U8 *pBuf, U16 u16Cnt, U8 u8Type)
{
    CQueueInfo *pQueueInfo;
    switch(u8Type)
    {
        case GPSDATA:           
            pQueueInfo = &cQueueGpsInfo;
            break;
        case INSDATA:
            pQueueInfo = &cQueueInsInfo;
            break;
        case OTHERDATA:
            pQueueInfo = &cQueueOtherInfo;
            break;
        case RFIDDATA:
            pQueueInfo = &cQueueRfidInfo;
            break;
        default:
            break; 
    }
    
    if(AddQueue(pQueueInfo, u16Cnt) == TRUE)
    {
//        WriteFile(DEV_COM1, pBuf, u16Cnt, 0);
        FramWriteInduce(pQueueInfo->Rear - u16Cnt, u16Cnt, pBuf);
        
//        FramReadInduce(pQueueInfo->Rear - u16Cnt, u16Cnt, pBuf);
        
//        WriteFile(DEV_COM1, pBuf, u16Cnt, 0);
    } 
}

VOID SaveNandflash(U8 u8Type)
{
    U8 u8Cnt = 0;
    U8 szBuf[SAVEDATASIZE] = {0}; 
    U32 u32EccCode;
    
    PQueueInfo pQueueInfo;
    NAND_ADDRESS nandAddress;
    NAND_ADDRESS *pNandAddress;
    CSaveVar *pSaveVar;
    switch(u8Type)
    {
        case GPSDATA:
            pQueueInfo = &cQueueGpsInfo;
            memcpy(&nandAddress, &NandGpsAddress, sizeof(NAND_ADDRESS));
            pNandAddress = &NandGpsAddress;
            pSaveVar = &cSaveGpsVar;
        
            break;
        case INSDATA:
            pQueueInfo = &cQueueInsInfo;
            memcpy(&nandAddress, &NandInsAddress, sizeof(NAND_ADDRESS));
            pNandAddress = &NandInsAddress;
            pSaveVar = &cSaveInsVar;
            break;
        case OTHERDATA:
            pQueueInfo = &cQueueOtherInfo;
            memcpy(&nandAddress, &NandOtherAddress, sizeof(NAND_ADDRESS));
            pNandAddress = &NandOtherAddress;
            pSaveVar = &cSaveOtherVar;
            break;
        case RFIDDATA:
            pQueueInfo = &cQueueRfidInfo;
            memcpy(&nandAddress, &NandRfidAddress, sizeof(NAND_ADDRESS));
            pNandAddress = &NandRfidAddress;
            pSaveVar = &cSaveRfidVar;
        default:
            break; 
    }
    
    if((GetQueueLength(pQueueInfo)/SAVEDATASIZE) > 0)
    {
        FramReadInduce(pQueueInfo->Front, SAVEDATASIZE, szBuf);//前8个数据invalid
       // FramReadInduce(0, SAVEDATASIZE, szBuf);//前8个数据invalid
//        for(u8Cnt = 0; u8Cnt < 8; u8Cnt++)
//            WriteFile(DEV_COM1, szBuf + 1024*u8Cnt, 1024, 0);
        FSMC_NAND_WriteSmallPage(szBuf, nandAddress, &u32EccCode);

        //FSMC_NAND_ReadSmallPage(szBuf, nandAddress, &u32EccCode);
//        for(u8Cnt = 0; u8Cnt < 8; u8Cnt++)
//            WriteFile(DEV_COM1, szBuf + 1024*u8Cnt, 1024, 0);
           
        
        pNandAddress->Page++;
        if(pNandAddress->Page == 128)
        {
            pNandAddress->Page = 0;
            pNandAddress->Block++;
            if(pNandAddress->Block == 1024)
            {
                EnterException(ERR_GPS_NAND_FULL);//存储满
            }
        }
        pSaveVar->bNandFlashEmptyFlag = FALSE;
        DeleteQueue(pQueueInfo, SAVEDATASIZE);
    }
    
}

VOID SaveUsbProc(U8 u8Type)
{
    U8 szBuf[SAVEDATASIZE] = {0};
    U8 u8Ret;
    U8 u8Cnt;
    U32 u32EccCode;
    CSaveVar cSaveVar;
    NAND_ADDRESS nandAddress;
    NAND_ADDRESS *pnandAddress;
    switch(u8Type)
    {
        case GPSDATA:
            
            memcpy(&cSaveVar, &cSaveGpsVar, sizeof(CSaveVar));
            
            memset(&nandAddress, 0, sizeof(NAND_ADDRESS));

            pnandAddress = &NandGpsAddress;

        
            u8Ret = mf_open("1:GPS.txt",3);//gps+时标 
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }

    
            break;
        case INSDATA:
            
            memcpy(&cSaveVar, &cSaveInsVar, sizeof(CSaveVar));
            
            memset(&nandAddress, 0, sizeof(NAND_ADDRESS));

            pnandAddress = &NandInsAddress;

        
            u8Ret = mf_open("1:INS.txt",3);//gps+时标 
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
           
            break;
            
        case OTHERDATA:
            
            memcpy(&cSaveVar, &cSaveOtherVar, sizeof(CSaveVar));
            
            memset(&nandAddress, 0, sizeof(NAND_ADDRESS));

            pnandAddress = &NandOtherAddress;
            
            u8Ret = mf_open("1:MILE.txt",3);//gps+时标 
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
            break;
        case RFIDDATA:
            
            memcpy(&cSaveVar, &cSaveRfidVar, sizeof(CSaveVar));
            
            memset(&nandAddress, 0, sizeof(NAND_ADDRESS));

            pnandAddress = &NandRfidAddress;

            u8Ret = mf_open("1:RFID.txt",3);//gps+时标 
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
                 
            break;
            
        default:
            break; 
    } 

    if(cSaveVar.bNandFlashEmptyFlag == FALSE)//非空
    {
        
        while((pnandAddress->Page != nandAddress.Page) || (pnandAddress->Block != nandAddress.Block))
        {   
            
            FSMC_NAND_ReadSmallPage(szBuf, nandAddress, &u32EccCode);
            u8Ret = mf_write(szBuf + 16, SAVEDATASIZE - 16);
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_WRITE_FAIL);
            } 
            nandAddress.Page++;
            if(nandAddress.Page == 128)
            {
                nandAddress.Page = 0;
                nandAddress.Block++;                      
            }
            
        }   
        
        cSaveVar.bNandFlashEmptyFlag = TRUE;

    }
    u8Ret = mf_close();
    if(u8Ret != 0)
    {
        EnterException(ERR_UPAN_CLOSE_FAIL);
    }
}
   
//    mf_open("1:GPS.txt",7);//gps+时标             7：FA_CREATE_NEW，FA_READ，FA_WRITE
//    mf_open("1:GUANDAO.txt",7);//惯导+时标          7：FA_CREATE_NEW，FA_READ，FA_WRITE
//    mf_open("1:OTHER.txt",7);//里程轨距+时标      7：FA_CREATE_NEW，FA_READ，FA_WRITE
//mf_scan_files("1:")				//u8 mf_scan_files(u8 * path)
////FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW
//#define	FA_READ				0x01
//#define	FA_OPEN_EXISTING	0x00
//#define	FA_WRITE			0x02
//#define	FA_CREATE_NEW		0x04
//#define	FA_CREATE_ALWAYS	0x08
//#define	FA_OPEN_ALWAYS		0x10
//#define FA__WRITTEN			0x20
//#define FA__DIRTY			0x40

//mf_open("1:test.txt",7)			//u8 mf_open(u8*path,u8 mode)  

//mf_write("what are you doing",14)	//u8 mf_write(u8*dat,u16 len)

//mf_read(14)						//u8 mf_read(u16 len)

//mf_close()						//u8 mf_close(void)
    
