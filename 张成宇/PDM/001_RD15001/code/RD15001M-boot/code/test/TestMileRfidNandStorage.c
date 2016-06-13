#include "board.h"

#define OTHER_FRAM_ECC_ADDRESS_START        0X1B800             //在FRAM110K的位置开始存起 运行到末端128大概可以存放36M的数据
#define OTHER_FRAM_ECC_ADDRESS_END              0x1FFFF             //而里程轨距的数据量是30*20 = 600字节/秒，一小时是2M的数据，因此可以工作18个小时


#define RFID_DATA_UNIT_SIZE       17        //每个标签需要17个字节
//#define RFID_DATA_MAX_SIZE       289         //17个标签需要289个字节
#define RFID_DATA_MAX_SIZE       0x2000         //这里给8K的空间

#define TIMELENGTH  11
#define TAGLENGTH  4

STATIC U32 g_u32OtherOffset = 0;//里程轨距Ecc存储用的偏移计数

STATIC VOID GetCurrentTimeString(U8 *g_pData)
{
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    *(g_pData) = '#';
    *(g_pData + 1) = (u32Tick100us/1000000000)+'0' ;
    *(g_pData + 2) = ((u32Tick100us/100000000)%10)+'0' ;
    *(g_pData + 3) = ((u32Tick100us/10000000)%10)+'0' ;
    *(g_pData + 4) = ((u32Tick100us/1000000)%10)+'0' ;
    *(g_pData + 5) = ((u32Tick100us/100000)%10)+'0' ;
    *(g_pData + 6) = ((u32Tick100us/10000)%10)+'0' ;
    *(g_pData + 7) = ((u32Tick100us/1000)%10)+'0' ;
    *(g_pData + 8) = ((u32Tick100us/100)%10)+'0' ;
    *(g_pData + 9) = ((u32Tick100us/10)%10)+'0' ;
    *(g_pData + 10) = (u32Tick100us%10)+'0' ;

}

STATIC VOID GetCurrentTagString(U8 *g_pData, U8 u8Value)
{
    *(g_pData) = '#';
    *(g_pData + 1) = ((u8Value/100)%10)+'0' ;
    *(g_pData + 2) = ((u8Value/10)%10)+'0' ;
    *(g_pData + 3) = (u8Value%10)+'0' ;

}

STATIC RunRfidProc(VOID)
{
    while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);

    while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
}

STATIC StopRfidProc(VOID)
{
    U8 u8Cnt = 0;
    BOOL bRet;
    do
    {
        bRet = SendAndWaitRfidDataProc(STOPREADING);
        u8Cnt++;
    }while((bRet == FALSE) && (u8Cnt < 10));
    if(u8Cnt == 10)
    {
        EnterException(ERR_RFID_STOP);
    }


}
VOID TestOtherRfidNandStorage(VOID)//里程轨距rfid用nand+fram
{
    U8 u8Ret;
    U8 u8type, u8Retry;
        
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pRfidData = mymalloc(SRAMIN, RFID_DATA_MAX_SIZE);
        
    U16 u16Count, u16Cnt;
        
    U32 u32OtherUsbAddress = 0;
    U32 EccCodeSub = 0;
    U32 EccCode = 0;
    
    U32 u32RfidCount = 0;
    
    U32 u32Temp, u32TempSub;
	U8 u8Temp, u8TempSub;
    
    NAND_ADDRESS Other_nand_address = {0};
    NAND_ADDRESS Other_nand_addressSub = {0};

    U8 *szTestTest, *szTimeBuf, *szTagBuf, *szOutputBuf;
    
    szTestTest = mymalloc(SRAMIN, RFIDDATACOUNT);
    
    szTimeBuf = mymalloc(SRAMIN, TIMELENGTH);
    
    szTagBuf = mymalloc(SRAMIN, TAGLENGTH);
    
    szOutputBuf = mymalloc(SRAMIN, TIMELENGTH + TAGLENGTH + 2);

    printf("Other nand storage TEST!\r\n");
   
    if((pBuf == NULL) || (pRfidData == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
     
    pQueueOtherInfo->Front = 0;
    pQueueOtherInfo->Rear = 0;
    pQueueOtherInfo->WriteCount = 0;
    pQueueOtherInfo->ReadCount = 0;
    pQueueOtherInfo->AddCount = 0;
    
    g_bSave = FALSE;//默认不开始保存
    g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
    while(1)
    {
       u16Count = GetCommDataLength();
        if(u16Count == 10)
        {
            ReadCommData(pBuf, u16Count);
            HandleCommCmdProc(pBuf, &u8type);
            switch(u8type)
            {
                case COMM_CMD_START:
                    
                    printf("\r\nNand格式化\r\n");
                    NandBlockEraseInit();
                    printf("\r\nNand存储测试\r\n");
//                    TIMER_Init(5000-2,840-1);//TIMER_Init(50-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=100Khz的计数频率，计数50次为5ms 
                    TIMER_Init(50000-7,84-1);//TIMER_Init(50-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=100Khz的计数频率，计数50次为5ms 

                    uart3_init(115200, 256, 256);//开启RFID用的串口3
                    RfidInitProc();//初始化RFID设备
                    RunRfidProc();//开启RFID设备
                    SetOtherWorkState(TRUE);//使能里程轨距50ms输出  
                    break;
                case COMM_CMD_STOP:
                     
                    SetOtherWorkState(FALSE);//禁能里程轨距50ms输出  
                    StopRfidProc();//关掉RFID设备
                    break;
                case COMM_CMD_CLRMILEAGE:
                    mileage_init();         //清除里程数据
                    break;
                case COMM_CMD_SAVEDATA:
                    SetOtherWorkState(FALSE);//禁能里程轨距50ms输出
                    StopRfidProc();//关掉RFID设备
                    g_bSave = TRUE;
                    
                    break;
                default:
                    break;
            }
            
        }
        if(g_bSave == TRUE)
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
        }
        if(GetQueueLength(pQueueOtherInfo) > QUEUEUNIT)
        {            
            GetQueue(pBuf, pOtherData, pQueueOtherInfo, QUEUEUNIT);
            
            DeleteQueue(pQueueOtherInfo);
            
            AdjustBadBlock(&Other_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Other_nand_address, &EccCode);
            
            FramWriteInduce(g_u32OtherOffset, 4, (U8 *)(&EccCode));
            
            g_u32OtherOffset = g_u32OtherOffset + 4;
            
            if(g_u32OtherOffset == OTHER_FRAM_ECC_ADDRESS_END)//满128K的数据
            {
                EnterException(ERR_OTHER_SPACE_FULL);
            }
            
            Other_nand_address.Page ++;
        
            if(Other_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Other_nand_address.Page = 0;
                Other_nand_address.Block++;
                if(Other_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

                        printf("\r\n存Nand测试满，结束\r\n");
                        while(1);

                }
            } 
        }
        else if(GetUsartCurrentLength(USART3_TYPE) != 0)
        {
            u16Count = GetUsartCurrentLength(USART3_TYPE);
            ClearUsartCurrentLength(USART3_TYPE);
            memcpy(szTestTest, g_pUsart3_rx_buf, u16Count);
//            Usart1_DMA_Send(szTestTest, u16Count);
            for(u16Cnt = 0; u16Cnt < u16Count; u16Cnt++)
            {
                if((szTestTest[u16Cnt] == 0xff) && (szTestTest[u16Cnt + 1] == 0x18) && (szTestTest[u16Cnt + 2] == 0x22))
                {
                    if(CompareTag(szTestTest + u16Cnt + 15) == TRUE)
                    {
                        GetCurrentTagString(szTagBuf, g_cRfidVar.u8Tag);
                        GetCurrentTimeString(szTimeBuf);
                        memcpy(szOutputBuf, szTimeBuf, TIMELENGTH);
                        memcpy(szOutputBuf + TIMELENGTH, szTagBuf, TAGLENGTH);
                        szOutputBuf[TIMELENGTH + TAGLENGTH] = '\r';
                        szOutputBuf[TIMELENGTH + TAGLENGTH + 1] = '\n';
                        memcpy(pRfidData + u32RfidCount, szOutputBuf, TIMELENGTH + TAGLENGTH + 2);
                        u32RfidCount = u32RfidCount + TIMELENGTH + TAGLENGTH + 2;
//                        Usart1_DMA_Send(szOutputBuf, TIMELENGTH + TAGLENGTH + 2);
                        
                        break;
                    }
                }
                
            }
            
        }
        if(bUsbPlugin == TRUE)
        {
//////////////////////////
            printf("RFID Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:RFID.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                u8Ret = f_write(file, pRfidData, u32RfidCount, &bw);
                
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_WRITE_FAIL);
                } 
     
                DisplaySavePercent(RFID_DISPLAY, 9, 9);
                       
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
                
            }
//////////////////////////
            printf("OTHER Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:OTHER.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
                
                while((Other_nand_addressSub.Page < Other_nand_address.Page) || (Other_nand_addressSub.Block < Other_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Other_nand_addressSub);
            
RETRY_OTHER_READ:        
                    FramReadInduce(g_u32OtherOffset, 4, (U8 *)(&EccCode));
                    
                    g_u32OtherOffset = g_u32OtherOffset + 4;
                    
                    
                    FSMC_NAND_ReadSmallPage(pBuf, Other_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            u8Retry++;
                            goto RETRY_OTHER_READ;
                        }
                        else
                        {
                        // SetNewBadBlock(nand_addressSub); 
                        }
                                                          
                    }
                    Other_nand_addressSub.Page ++;
                
                    if(Other_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Other_nand_addressSub.Page = 0;
                        Other_nand_addressSub.Block++;
                        if(Other_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
                        {
                                printf("\r\n存Nand测试满，结束\r\n");
                                while(1);
                            
                        }
                    }
                    
                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32OtherUsbAddress = u32OtherUsbAddress + QUEUEUNIT;

OTHER_SAVE:         u8Ret = f_lseek(file, u32OtherUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto OTHER_SAVE;
                    } 
                    u32Temp = Other_nand_address.Page + Other_nand_address.Block * 128;
                    u32TempSub = Other_nand_addressSub.Page + Other_nand_addressSub.Block * 128;
					u8Temp = (u32TempSub * 10)/u32Temp;
					u8TempSub = ((u32TempSub * 100)/u32Temp) % 10;
                    DisplaySavePercent(MILE_DIPLAY, u8Temp, u8TempSub);
                        
                    
                }
                u32Temp = GetQueueLength(pQueueOtherInfo);
                GetQueue(pBuf, pOtherData, pQueueOtherInfo, u32Temp);
                u8Ret = f_write(file, pBuf, u32Temp, &bw); 
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
                
                DisplaySaveEnd();
                
                while(1);
            }
             
        }
            
    }
          
}
