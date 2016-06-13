#include "board.h"

EXTERN BOOL bUsbPlugin;

#define NANDBUFFERUNIT    0x2000  //8k

#define MAXQUEUEBUFFERSIZE    0x4000  //24k

typedef U32 NandQueueDataType;



CQueueInfo cNandQueueUsartInfo = {0};

QueueDataType GetNandQueueLength(PNandQueueInfo pNandQueueInfo)
{
    QueueDataType Ret;
	Ret = (pNandQueueInfo->Rear - pNandQueueInfo->Front + MAXQUEUEBUFFERSIZE) % MAXQUEUEBUFFERSIZE;
    return Ret;
}
BOOL AddNandQueue(U8 *pBuf, PNandQueueInfo pNandQueueInfo, NandQueueDataType OffSet)
{
    BOOL bState;
    U16 u16Cnt;
	if((pNandQueueInfo->Rear + OffSet) % MAXQUEUEBUFFERSIZE == pNandQueueInfo->Front)
	{
		bState = FALSE;
	}
    else
    {
        u16Cnt = MAXQUEUEBUFFERSIZE - pNandQueueInfo->Rear;
        if(GetUsartCurrentLength(USART1_TYPE) > u16Cnt)
        {
            
            memcpy(pBuf + pNandQueueInfo->Rear, g_pUsart1_rx_buf, u16Cnt);
            memcpy(pBuf, g_pUsart1_rx_buf + u16Cnt, OffSet - u16Cnt);
        }
        else
        {
            memcpy(pBuf + pNandQueueInfo->Rear, g_pUsart1_rx_buf, GetUsartCurrentLength(USART1_TYPE));
        }
    	pNandQueueInfo->Rear = (pNandQueueInfo->Rear + OffSet) % MAXQUEUEBUFFERSIZE;
    	bState = TRUE;
    }
    return bState;
}

BOOL DeleteNandQueue(PNandQueueInfo pNandQueueInfo)
{
    BOOL bState;
	if(pNandQueueInfo->Front == pNandQueueInfo->Rear)
	{
		bState = FALSE;
	}
    else
    {
    	pNandQueueInfo->Front = (pNandQueueInfo->Front + NANDBUFFERUNIT) % MAXQUEUEBUFFERSIZE;
        bState = TRUE;
    }
	return bState;
}


EXTERN VOID NandBlockEraseInit(VOID);

VOID TestNandStorage(VOID)
{
    NAND_ADDRESS nand_address = {0};
    NAND_ADDRESS nand_addressSub = {0};
    U8 *pBuf = mymalloc(SRAMIN, MAXQUEUEBUFFERSIZE);
    U8 *pWriteBuf = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U16 u16Count;
//    U16 u16Cnt = 0;
    U8 u8Ret;
    U32 u32Count;
    U8 szTestBuf[40];
    U32 u32TickCnt, u32EccCode;
    BOOL bStart = FALSE;

    if((pBuf == NULL) && (pWriteBuf != NULL))
    {
        printf("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n");
        Usart2_DMA_Send("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n", 29);
        while(1);
    }
    else
    {
        printf("\r\nNand∏Ò ΩªØ\r\n");
        Usart2_DMA_Send("\r\nNand∏Ò ΩªØ\r\n", 14);
        NandBlockEraseInit();
        printf("\r\nNand¥Ê¥¢≤‚ ‘\r\n");
        Usart2_DMA_Send("\r\nNand¥Ê¥¢≤‚ ‘\r\n", 16);
        ClearUsartCurrentLength(USART1_TYPE);
       
        while(1)
        {
                      
            if(GetUsartCurrentLength(USART1_TYPE) != 0)
            {
                AddNandQueue(pBuf, &cNandQueueUsartInfo, GetUsartCurrentLength(USART1_TYPE));
                ClearUsartCurrentLength(USART1_TYPE);
                if(GetNandQueueLength(&cNandQueueUsartInfo) > NANDBUFFERUNIT) 
                {
                    u16Count = MAXQUEUEBUFFERSIZE - cNandQueueUsartInfo.Front;
                    
                    if(u16Count < NANDBUFFERUNIT)
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, u16Count);
                        memcpy(pWriteBuf + u16Count, pBuf, NANDBUFFERUNIT - u16Count);
                        
                    }
                    else
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, NANDBUFFERUNIT);
                    }
//                    pWriteBuf[0] = u16Cnt;
//                    u16Cnt++;
                    FSMC_NAND_WriteSmallPage(pWriteBuf, nand_address, &u32EccCode);
                    nand_address.Page ++;
                    if(nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        nand_address.Page = 0;
                        nand_address.Block++;
                        if(nand_address.Block == NAND_ZONE_SIZE)
                        {
                            nand_address.Block = 0;
                            nand_address.Zone++;

                            if(nand_address.Zone == NAND_MAX_ZONE)
                            {
                                printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘¬˙£¨Ω· ¯\r\n");
                                while(1);
                            }
                        }
                    } 
                    DeleteNandQueue(&cNandQueueUsartInfo);
                    sprintf((char *)szTestBuf, "page = %3d, block = %3d, zone = %3d", nand_address.Page, nand_address.Block, nand_address.Zone);
                    Usart2_DMA_Send(szTestBuf, 37);
                }
                
                bStart = TRUE;

                u32TickCnt = GetTickCount(); 
            }
            if(bStart == TRUE)
            {
                if((GetTickCount() - u32TickCnt) > 80000)
                {
                    Usart2_DMA_Send("\r\nReceive over\r\n", 16);
                    sprintf((char *)szTestBuf, "page = %3d, block = %3d, zone = %3d", nand_address.Page, nand_address.Block, nand_address.Zone);
                    Usart2_DMA_Send(szTestBuf, 37);
                    bStart = FALSE;
                }
                
            }
            
            
            
            if(bUsbPlugin == TRUE)
            {
                printf("Save Start \r\n");
                Usart2_DMA_Send("Save Start \r\n", 12);
                
                u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",0x23);
                        
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_OPEN_FAIL);
                }
                u32Count = 0;
                

                while((nand_addressSub.Page < nand_address.Page) || (nand_addressSub.Block < nand_address.Block))
                {
                    
                    FSMC_NAND_ReadSmallPage(pWriteBuf, nand_addressSub, &u32EccCode);

                    u8Ret = f_write(file, pWriteBuf, NANDBUFFERUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    nand_addressSub.Page++;

                    if(nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        nand_addressSub.Page = 0;
                        nand_addressSub.Block++;
                        if(nand_addressSub.Block == NAND_ZONE_SIZE)
                        {
                            nand_addressSub.Block = 0;
                            nand_addressSub.Zone++;

                            if(nand_addressSub.Zone == NAND_MAX_ZONE)
                            {
                                printf("\r\nSave Full\r\n");
                                Usart2_DMA_Send("\r\nSave Full\r\n", 13);
                                while(1);
                            }
                        }
                    } 
                    sprintf((char *)szTestBuf, "Current point = %7x\r\n", u32Count);
                    Usart2_DMA_Send(szTestBuf, 25);
                    sprintf((char *)szTestBuf, "page = %3d, block = %3d, zone = %3d\r\n", nand_addressSub.Page, nand_addressSub.Block, nand_addressSub.Zone);
                    Usart2_DMA_Send(szTestBuf, 37);
                    u32Count = u32Count + NANDBUFFERUNIT;
                    
                    f_lseek(file, u32Count);
                    
                }
                                
                u16Count = MAXQUEUEBUFFERSIZE - cNandQueueUsartInfo.Front;
                
                if(u16Count < GetNandQueueLength(&cNandQueueUsartInfo))
                {
                    memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, u16Count);
                    memcpy(pWriteBuf + u16Count, pBuf, GetNandQueueLength(&cNandQueueUsartInfo) - u16Count);
                    
                }
                else
                {
                    memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, GetNandQueueLength(&cNandQueueUsartInfo));
                }
                
                
                u8Ret = f_write(file, pWriteBuf, GetNandQueueLength(&cNandQueueUsartInfo), &bw);
                
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_WRITE_FAIL);
                } 
                
                
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }

                printf("Save End \r\n");
                Usart2_DMA_Send("Save End \r\n", 12);

                while(1);
                
            }
            
            USBH_Process(&USB_OTG_Core, &USB_Host);
            
        }
        
    }
}
typedef struct  _tagNandBadBlockInfo
{
    U16 BlockData;
    struct  _tagNandBadBlockInfo *pNext;
    
}CNandBadBlockInfo, *PNandBadBlockInfo;

typedef struct  _tagNandBadPageInfo
{
    U16 PageData;
    U16 BlockData;
    struct  _tagNandBadPageInfo *pNext;
    
}CNandBadPageInfo, *PNandBadPageInfo;

CNandBadBlockInfo g_cNandBadBlockInfo = {0};
PNandBadBlockInfo g_pCurrentNandBadBlockInfo = &g_cNandBadBlockInfo;

CNandBadPageInfo  g_cNandBadPageInfo = {0};
PNandBadPageInfo  g_pCurrentNandBadPageInfo = &g_cNandBadPageInfo;

STATIC VOID BadBlockManage(NAND_ADDRESS nand_address)
{
    PNandBadBlockInfo pNandBadBlockInfo = mymalloc(SRAMIN, sizeof(CNandBadBlockInfo));
    if(pNandBadBlockInfo != NULL)
    {
        g_pCurrentNandBadBlockInfo->BlockData = nand_address.Block;
        g_pCurrentNandBadBlockInfo->pNext = pNandBadBlockInfo;
        g_pCurrentNandBadBlockInfo = g_pCurrentNandBadBlockInfo->pNext;
    }
    
}

STATIC VOID BadPageManage(NAND_ADDRESS nand_address)
{
    PNandBadPageInfo pNandBadPageInfo = mymalloc(SRAMIN, sizeof(CNandBadPageInfo));
    if(pNandBadPageInfo != NULL)
    {
        g_pCurrentNandBadPageInfo->PageData = nand_address.Page;
        g_pCurrentNandBadPageInfo->BlockData = nand_address.Block;
        g_pCurrentNandBadPageInfo->pNext = pNandBadPageInfo;
        g_pCurrentNandBadPageInfo = g_pCurrentNandBadPageInfo->pNext;
    }
    
}

STATIC VOID AdjustBadBlock(NAND_ADDRESS *pnand_address)
{
    PNandBadBlockInfo pNandBadBlockInfo = &g_cNandBadBlockInfo;
    PNandBadPageInfo pNandBadPageInfo = &g_cNandBadPageInfo;
    while(pNandBadBlockInfo->pNext != NULL)
    {
        if(pNandBadBlockInfo->BlockData > pnand_address->Block)
        {
            break;
        }
        if(pNandBadBlockInfo->BlockData == pnand_address->Block)
        {
            pnand_address->Block = pnand_address->Block + 1;
            if(pnand_address->Block == NAND_ZONE_SIZE)
            {
                pnand_address->Block = 0;
                pnand_address->Zone++;

                if(pnand_address->Zone == NAND_MAX_ZONE)
                {
                    printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘¬˙£¨Ω· ¯\r\n");
                    while(1);
                }
            }
            goto AdjustBadBlock_exit;
        }
        pNandBadBlockInfo = pNandBadBlockInfo->pNext;
    }
    
    while(pNandBadPageInfo->pNext != NULL)
    {
        if(pNandBadPageInfo->PageData > pnand_address->Page)
        {
            break;
        }
        
        if(pNandBadPageInfo->PageData == pnand_address->Page)
        {
            pnand_address->Page = pnand_address->Page + 1;
            if(pnand_address->Page == NAND_PAGENUMBER_PERBLOCK)
            {
                pnand_address->Page = 0;
                pnand_address->Block++;
                if(pnand_address->Block == NAND_ZONE_SIZE)
                {
                    pnand_address->Block = 0;
                    pnand_address->Zone++;

                    if(pnand_address->Zone == NAND_MAX_ZONE)
                    {
                        printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘¬˙£¨Ω· ¯\r\n");
                        while(1);
                    }
                }
            }
            break;
        }
        pNandBadPageInfo = pNandBadPageInfo->pNext;
        
    }
    
    
AdjustBadBlock_exit:
    pNandBadBlockInfo = NULL;//INVALID
    
    
}              
//STATIC BOOL JudgeBadBlock(uint16_t block)
//{
//    BOOL bRet = TRUE;
//    PNandBadBlockInfo pNandBadBlockInfo = &cNandBadBlockInfo;
//    while(pNandBadBlockInfo->pNext != NULL)
//    {
//        if(pNandBadBlockInfo->BlockData > block)
//        {
//            break;
//        }
//        if(pNandBadBlockInfo->BlockData == block)
//        {
//            bRet = FALSE;
//            break;
//        }
//        pNandBadBlockInfo = pNandBadBlockInfo->pNext;
//    }
//    return bRet;
//}
typedef struct _tagEccInfo
{
    uint16_t Zone;
    uint16_t Block;
    uint16_t Page;
    U32 EccAddress;
    U8 szEcc[4];
    struct _tagEccInfo *pNext;
    
}CEccInfo, *PEccInfo;

CEccInfo g_cEccInfo = {0};
PEccInfo g_pCurrentEccInfo = &g_cEccInfo;
U32 g_u32EccAddress = 0;

STATIC VOID StoreEccProc(U8 *pBuf, NAND_ADDRESS nand_address) 
{
    PEccInfo pEccInfo = mymalloc(SRAMIN, sizeof(CEccInfo));
    
    if(pEccInfo != NULL)
    {
        g_pCurrentEccInfo->Zone = nand_address.Zone;
        g_pCurrentEccInfo->Block = nand_address.Block;
        g_pCurrentEccInfo->Page = nand_address.Page;
        g_pCurrentEccInfo->EccAddress = g_u32EccAddress;
        memcpy(g_pCurrentEccInfo->szEcc, pBuf, 4);
        g_pCurrentEccInfo->pNext = pEccInfo;
        g_pCurrentEccInfo = g_pCurrentEccInfo->pNext;
        
        FramWriteInduce(g_u32EccAddress, 4, pBuf);
        g_u32EccAddress = g_u32EccAddress + 4;
        
    } 
}
STATIC VOID GetEccProc(U8 *pBuf, NAND_ADDRESS nand_address) 
{
    PEccInfo pEccInfo = &g_cEccInfo;
//    U8 u8Value;
    while(pEccInfo->pNext != NULL)
    {
        if((pEccInfo->Block == nand_address.Block) && (pEccInfo->Zone == nand_address.Zone) && (pEccInfo->Page == nand_address.Page))
        {
            FramReadInduce(pEccInfo->EccAddress, 4, pBuf);
//            u8Value = pBuf[0];
//            pBuf[0] = pBuf[3];
//            pBuf[3] = u8Value;
//            u8Value = pBuf[1];
//            pBuf[1] = pBuf[2];
//            pBuf[2] = u8Value;
            break;
        }
        
        pEccInfo = pEccInfo->pNext;
    }
    
}
EXTERN U32 g_TestdataCount;


VOID TestNandStorageEx(VOID)
{
    NAND_ADDRESS nand_address = {0};
    NAND_ADDRESS nand_addressSub = {0};
    U8 *pBuf = mymalloc(SRAMIN, MAXQUEUEBUFFERSIZE);
    U8 *pWriteBuf = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U8 *pWriteBufSub = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U8 szWriteBufSubEx[20];
    U8 szWriteBufSubExEx[20];
    U16 u16Count;
    U32 u32Count;
    U8 u8Ret;
    
    U32  u32EccCode[16], u32EccCodeSub[16];
    U8 *pSpare = (U8 *)&u32EccCode;
    U8 szTestBuf[40];
    U32 u32TickCnt;
    BOOL bStart = FALSE;
    U8 u8Cnt = 0;
    
    U32 u32TotalCount = 0,u32FailCount = 0, u32RecoverCount = 0;
    

    if((pBuf == NULL) && (pWriteBuf != NULL))
    {
        printf("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n");
        Usart2_DMA_Send("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n", 29);
        while(1);
    }
    else
    {
        printf("\r\nNand∏Ò ΩªØ\r\n");
        Usart2_DMA_Send("\r\nNand∏Ò ΩªØ\r\n", 14);
        NandBlockEraseInit();
        printf("\r\nNand¥Ê¥¢≤‚ ‘\r\n");
        Usart2_DMA_Send("\r\nNand¥Ê¥¢≤‚ ‘\r\n", 16);
        ClearUsartCurrentLength(USART1_TYPE);
        g_TestdataCount = 0;
//        nand_address.Block = 7;
//        nand_addressSub.Block = 7;
//        
//        nand_address.Page = 120;
//        nand_addressSub.Page = 120;
        while(1)
        {
                      
            if(GetUsartCurrentLength(USART1_TYPE) != 0)
            {
                AddNandQueue(pBuf, &cNandQueueUsartInfo, GetUsartCurrentLength(USART1_TYPE));
                ClearUsartCurrentLength(USART1_TYPE);
                if(GetNandQueueLength(&cNandQueueUsartInfo) > NANDBUFFERUNIT) 
                {
                    u16Count = MAXQUEUEBUFFERSIZE - cNandQueueUsartInfo.Front;
                    
                    if(u16Count < NANDBUFFERUNIT)
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, u16Count);
                        memcpy(pWriteBuf + u16Count, pBuf, NANDBUFFERUNIT - u16Count);
                        
                    }
                    else
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, NANDBUFFERUNIT);
                    }
                    u8Cnt = 0;
                    memset(szWriteBufSubEx, 0, 20);
                    memset(szWriteBufSubExEx, 0xff, 20);
                    FSMC_NAND_WriteSmallPage(pWriteBuf, nand_address, u32EccCode);
NANDRESUME:         FSMC_NAND_ReadSmallPage(pWriteBufSub, nand_address, u32EccCodeSub);
                    
                    if(memcmp(pWriteBuf, pWriteBufSub, 0X2000) != 0)
                    
                    {
                        u32FailCount++;
                        //printf("\r\nError page = %x, block = %x, zone = %x\r\n", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block, cNAND_ADDRESS_tag.Zone);   
                        for(u8Cnt = 0; u8Cnt < 16; u8Cnt++)
                        {
                            if(u32EccCode[u8Cnt] != u32EccCodeSub[u8Cnt])
                            {
                                if(memcmp(pWriteBuf + u8Cnt*512, pWriteBufSub + u8Cnt*512, 512) != 0)
                                {
                                    u8Ret = ECCCheck(u32EccCode[u8Cnt], u32EccCodeSub[u8Cnt], pWriteBufSub + u8Cnt*512);
                                    if(u8Ret != 3)
                                    {
                                        if(memcmp(pWriteBuf + u8Cnt*512, pWriteBufSub + u8Cnt*512, 512) != 0)
                                        {
        //                                    printf("\r\n0x%x, 0x%x, 0x%x\r\n", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block, cNAND_ADDRESS_tag.Zone);   

        //                                    printf("error");
                                           printf("\r\ntotal = %d, Fail = %x, recover = %x", u32TotalCount, u32FailCount, u32RecoverCount);   

                                        }
                                        else
                                        {
                                            u32RecoverCount++;
                                            
                                            
                                        }
                                    }
                                    else
                                    {
                                        BadBlockManage(nand_address);
                                        nand_address.Block++;
                                        goto exit_nand;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        nand_address.Page ++;
                        if(nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
                        {
                            nand_address.Page = 0;
                            nand_address.Block++;
                            if(nand_address.Block == NAND_ZONE_SIZE)
                            {
                                nand_address.Block = 0;
                                nand_address.Zone++;

                                if(nand_address.Zone == NAND_MAX_ZONE)
                                {
                                    printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘¬˙£¨Ω· ¯\r\n");
                                    while(1);
                                }
                            }
                        } 
                    }
exit_nand:                   
                    u32TotalCount++;
                    
          
                }
                
                bStart = TRUE;

                u32TickCnt = GetTickCount(); 
            }
            if(bStart == TRUE)
            {
                if((GetTickCount() - u32TickCnt) > 80000)
                {
                    Usart2_DMA_Send("\r\nReceive over\r\n", 16);
                    sprintf((char *)szTestBuf, "page = %3d, block = %3d, zone = %3d", nand_address.Page, nand_address.Block, nand_address.Zone);
                    Usart2_DMA_Send(szTestBuf, 37);
                    bStart = FALSE;
                }
                
            }
        }
    }
            
     
}


#if 0
VOID TestNandStorageExEx(VOID)//≤‚ ‘±£¥Ê∂¯“—
{
    NAND_ADDRESS nand_address = {0};
    NAND_ADDRESS nand_addressSub = {0};
    U8 *pBuf = mymalloc(SRAMIN, MAXQUEUEBUFFERSIZE);
    U8 *pWriteBuf = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U8 *pWriteBufSub = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U8 szWriteBufSubEx[20];
    U8 szWriteBufSubExEx[20];
    U16 u16Count;
    U32 u32Count;
    U8 u8Ret;
    
    uint32_t  u32EccCode, u32EccCodeSub;
    U8 *pSpare = (U8 *)&u32EccCode;
    U8 szTestBuf[40];
    U32 u32TickCnt;
    BOOL bStart = FALSE;
    U8 u8Cnt = 0;
    

    if((pBuf == NULL) && (pWriteBuf != NULL))
    {
        printf("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n");
        Usart2_DMA_Send("\r\nNand¥Ê¥¢≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n", 29);
        while(1);
    }
    else
    {
      
        while(1)
        {
                                  
            if(bUsbPlugin == TRUE)
            {
                printf("Save Start \r\n");
                Usart2_DMA_Send("Save Start \r\n", 12);
                
                u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",0x23);
                        
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_OPEN_FAIL);
                }
                u32Count = 0;
                

                //while((nand_addressSub.Page < nand_address.Page) || (nand_addressSub.Block < nand_address.Block))
                while((nand_addressSub.Page < 120) || (nand_addressSub.Block <15))
                {
//                    if(JudgeBadBlock(nand_addressSub.Block) == FALSE)
//                        nand_addressSub.Block++;
                    AdjustBadBlock(&nand_addressSub);
                    
                   // FSMC_NAND_ReadSmallPage(pWriteBuf, nand_addressSub, &u32EccCodeSub);
                                                            
                    GetEccProc(pSpare, nand_addressSub); 
                    u8Cnt = 0;
                    
                    do
                    {
                    
                        FSMC_NAND_ReadSmallPage(pWriteBuf, nand_addressSub, &u32EccCodeSub);
                        u8Cnt++;
                        
                    }while((*((U32 *)pSpare) != u32EccCodeSub) && (u8Cnt < 3));
                    
                    if(u8Cnt == 3)
                    {
                        memset(pWriteBuf, 0xAA, 8);
                        pWriteBuf[4] = nand_addressSub.Zone;
                        pWriteBuf[5] = LOBYTE(nand_addressSub.Block);
                        pWriteBuf[6] = HIBYTE(nand_addressSub.Block);
                        pWriteBuf[7] = HIBYTE(nand_addressSub.Page);
                        
                    }
                    
                    u8Ret = f_write(file, pWriteBuf, NANDBUFFERUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    nand_addressSub.Page++;

                    if(nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        nand_addressSub.Page = 0;
                        nand_addressSub.Block++;
                        if(nand_addressSub.Block == NAND_ZONE_SIZE)
                        {
                            nand_addressSub.Block = 0;
                            nand_addressSub.Zone++;

                            if(nand_addressSub.Zone == NAND_MAX_ZONE)
                            {
                                printf("\r\nSave Full\r\n");
                                Usart2_DMA_Send("\r\nSave Full\r\n", 13);
                                while(1);
                            }
                        }
                    } 
                    sprintf(szTestBuf, "Current point = %7x\r\n", u32Count);
                    Usart2_DMA_Send(szTestBuf, 25);
                    sprintf(szTestBuf, "page = %3d, block = %3d, zone = %3d\r\n", nand_addressSub.Page, nand_addressSub.Block, nand_addressSub.Zone);
                    Usart2_DMA_Send(szTestBuf, 37);
                    u32Count = u32Count + NANDBUFFERUNIT;
                    
                    f_lseek(file, u32Count);
                    
                }
                                
                u16Count = MAXQUEUEBUFFERSIZE - cNandQueueUsartInfo.Front;
                
                if(u16Count < GetQueueLength(&cNandQueueUsartInfo))
                {
                    memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, u16Count);
                    memcpy(pWriteBuf + u16Count, pBuf, GetQueueLength(&cNandQueueUsartInfo) - u16Count);
                    
                }
                else
                {
                    memcpy(pWriteBuf, pBuf + cQueueUsartInfo.Front, GetQueueLength(&cNandQueueUsartInfo));
                }
                
                
                u8Ret = f_write(file, pWriteBuf, GetQueueLength(&cNandQueueUsartInfo), &bw);
                
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_WRITE_FAIL);
                } 
                
                
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }

                printf("Save End \r\n");
                Usart2_DMA_Send("Save End \r\n", 12);

                while(1);
                
            }
            
            USBH_Process(&USB_OTG_Core, &USB_Host);
            
        }
        
    }
}


///////////////////////////////////////////////////////////////////////////////////////////





VOID TestUsartToNand(VOID)
{
    NAND_ADDRESS nand_address = {0};
    U8 *pBuf = mymalloc(SRAMIN, MAXQUEUEBUFFERSIZE);
    U8 *pWriteBuf = mymalloc(SRAMIN, NANDBUFFERUNIT);
    U16 u16Count,u16Cnt = 0;
    U8 u8Ret,u8Cnt;
    U32 u32Count, u32EccCode;

    if((pBuf == NULL) && (pWriteBuf != NULL))
    {
        printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘ …Í«Îƒ⁄¥Ê ß∞‹\r\n");
        while(1);
    }
    else
    {
        NandBlockEraseInit();
        printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘\r\n");
       
        while(1)
        { 
            if(GetUsartCurrentLength(USART1_TYPE) != 0)
            {
                AddQueue(pBuf, &cNandQueueUsartInfo, GetUsartCurrentLength(USART1_TYPE));
                GetUsartCurrentLength(USART1_TYPE) = 0;
                if(GetQueueLength(&cNandQueueUsartInfo) > NANDBUFFERUNIT) 
                {
                    u16Count = MAXQUEUEBUFFERSIZE - cNandQueueUsartInfo.Front;
                    if(u16Count < NANDBUFFERUNIT)
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, u16Count);
                        memcpy(pWriteBuf + u16Count, pBuf, NANDBUFFERUNIT - u16Count);
                        
                    }
                    else
                    {
                        memcpy(pWriteBuf, pBuf + cNandQueueUsartInfo.Front, NANDBUFFERUNIT);
                    }
                    pWriteBuf[0] = u16Cnt;
                    u16Cnt++;
                    FSMC_NAND_WriteSmallPage(pWriteBuf, nand_address, &u32EccCode);
                    nand_address.Page ++;
                    if(nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        nand_address.Page = 0;
                        //nand_address.Block++;

                        printf("\r\n¥Æø⁄¥ÊNand≤‚ ‘¬˙£¨Ω· ¯\r\n");
                        
                        u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",0x23);//gps+ ±±Í 
                        
                        if(u8Ret != 0)
                        {
                            EnterException(ERR_UPAN_OPEN_FAIL);
                        }
                        u32Count = 0;
                        for(u8Cnt = 0; u8Cnt < NAND_PAGENUMBER_PERBLOCK; u8Cnt++)
                        {
                            nand_address.Page = u8Cnt;
                            
                            FSMC_NAND_ReadSmallPage(pWriteBuf, nand_address, &u32EccCode);
   
                            u8Ret = f_write(file, pWriteBuf, NANDBUFFERUNIT, &bw);
                            
                            if(u8Ret != 0)
                            {
                                EnterException(ERR_UPAN_WRITE_FAIL);
                            } 
                            u32Count = u32Count + NANDBUFFERUNIT;
                            
                            f_lseek(file, u32Count);
                            
                        }
                        u8Ret = f_close(file);
                        
                        if(u8Ret != 0)
                        {
                            EnterException(ERR_UPAN_CLOSE_FAIL);
                        }
                        
                        printf("save over \r\n");
                        
                        while(1);
                    } 
                    
                    
                    DeleteQueue(&cQueueUsartInfo);
                }
                    
            }
            
            USBH_Process(&USB_OTG_Core, &USB_Host);
            
        }
        
    }
}

#endif
