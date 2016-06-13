#include "board.h"

EXTERN U32 g_TestdataCount;
EXTERN U32 g_TestdataCount2; 

#define OTHER_ADDRESS  0X400000  //2G      //约莫是惯导数据的3小时测试量。 
#define GPS_ADDRESS  0X200000  //1G      
#define INS_ADDRESS  0 

VOID TestSaveEX(VOID)//直接读取SD卡的数据到U盘中
{
    U8 u8Ret;

    U32 u32InsWriteSectorAddress = INS_ADDRESS, u32InsReadSectorAddress = INS_ADDRESS, u32InsUsbAddress = 0;
    U32 u32GpsWriteSectorAddress = GPS_ADDRESS, u32GpsReadSectorAddress = GPS_ADDRESS, u32GpsUsbAddress = 0;
    U32 u32OtherWriteSectorAddress = OTHER_ADDRESS, u32OtherReadSectorAddress = OTHER_ADDRESS, u32OtherUsbAddress = 0;
    
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pBackupBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    U16 u16Count;
    
    printf("SD Card TEST!\r\n");
    
    while(SD_Init())
    {
        printf("SD Card Error!\r\n");
        DelayMs(1000);
    }

    if((pBuf == NULL) || (pBackupBuf == NULL))
    {
        EnterException(ERR_USATT1_MALLOC_FAIL);
    }
    
    u32InsWriteSectorAddress = u32InsWriteSectorAddress + 0x32000;//100M
    u32GpsWriteSectorAddress = u32GpsWriteSectorAddress + 0x5000;   //10M
    
    u32OtherWriteSectorAddress = u32OtherWriteSectorAddress + 0x5000; //10M
    
    
    while(1)
    {
        if(bUsbPlugin == TRUE)
        {
            printf("INS Save Start \r\n");
            u16Count = 17;
            USART2_Send("INS save start \r\n", &u16Count);
            
            u8Ret = f_open(file,(const TCHAR*)"1:INS.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
            while(u32InsReadSectorAddress != u32InsWriteSectorAddress)
            {
                if(SD_ReadDisk(pBuf, u32InsReadSectorAddress, SD_COUNT)==0)	
                {
                    u32InsReadSectorAddress = u32InsReadSectorAddress + SD_COUNT;

                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32InsUsbAddress = u32InsUsbAddress + QUEUEUNIT;
                    
                    
INS_SD_SAVE:       u8Ret = f_lseek(file, u32InsUsbAddress);
                    
                    if(u8Ret != 0)
                    {
//                        printf("file seek error = %x \r\n", u32InsUsbAddress);
                        goto INS_SD_SAVE;
                    } 
                    
                }
                
                else
                {
                    EnterException(ERR_SD_READ_FAIL);
                }
            }
                            
            u16Count = MAXQUEUESIZE - pQueueUsart1Info->Front;
            
            if(u16Count < GetQueueLength(pQueueUsart1Info))
            {
                memcpy(pBuf, pUsart1Data + pQueueUsart1Info->Front, u16Count);
                memcpy(pBuf + u16Count, pUsart1Data, GetQueueLength(pQueueUsart1Info) - u16Count);
                
            }
            else
            {
                memcpy(pBuf, pUsart1Data + pQueueUsart1Info->Front, GetQueueLength(pQueueUsart1Info));
            }
            
            
            u8Ret = f_write(file, pBuf, GetQueueLength(pQueueUsart1Info), &bw);
            
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_WRITE_FAIL);
            } 
            
            
            u8Ret = f_close(file);

            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_CLOSE_FAIL);
            }

            printf("INS Save End \r\n");
            u16Count = 15;
            USART2_Send("INS Save end \r\n", &u16Count);
            
 ///////////////////////////////////////////////////////////////           
            printf("GPS Save Start \r\n");
            u16Count = 17;
            USART2_Send("GPS save start \r\n", &u16Count);
            
            u8Ret = f_open(file,(const TCHAR*)"1:GPS.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
            while(u32GpsReadSectorAddress != u32GpsWriteSectorAddress)
            {
                if(SD_ReadDisk(pBuf, u32GpsReadSectorAddress, SD_COUNT)==0)	
                {
                    u32GpsReadSectorAddress = u32GpsReadSectorAddress + SD_COUNT;

                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32GpsUsbAddress = u32GpsUsbAddress + QUEUEUNIT;
                    
                    
GPS_SD_SAVE:        u8Ret = f_lseek(file, u32GpsUsbAddress);
                    
                    if(u8Ret != 0)
                    {
//                        printf("file seek error = %x \r\n", u32GpsUsbAddress);
                        goto GPS_SD_SAVE;
                    } 
                    
                }
                
                else
                {
                    EnterException(ERR_SD_READ_FAIL);
                }
            }
                            
            u16Count = MAXQUEUESIZE - pQueueUsart2Info->Front;
            
            if(u16Count < GetQueueLength(pQueueUsart2Info))
            {
                memcpy(pBuf, pUsart2Data + pQueueUsart2Info->Front, u16Count);
                memcpy(pBuf + u16Count, pUsart2Data, GetQueueLength(pQueueUsart2Info) - u16Count);
                
            }
            else
            {
                memcpy(pBuf, pUsart2Data + pQueueUsart2Info->Front, GetQueueLength(pQueueUsart2Info));
            }
            
            
            u8Ret = f_write(file, pBuf, GetQueueLength(pQueueUsart2Info), &bw);
            
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_WRITE_FAIL);
            } 
            
            
            u8Ret = f_close(file);

            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_CLOSE_FAIL);
            }

            printf("GPS Save End \r\n");
            u16Count = 15;
            USART2_Send("GPS Save end \r\n", &u16Count);
            
////////////////////////////////////////////////////////
            printf("OTHER Save Start \r\n");
            u16Count = 19;
            USART2_Send("OTHER save start \r\n", &u16Count);
            
            u8Ret = f_open(file,(const TCHAR*)"1:OTHER.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
            while(u32OtherReadSectorAddress != u32OtherWriteSectorAddress)
            {
                if(SD_ReadDisk(pBuf, u32OtherReadSectorAddress, SD_COUNT)==0)    
                {
                    u32OtherReadSectorAddress = u32OtherReadSectorAddress + SD_COUNT;

                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32OtherUsbAddress = u32OtherUsbAddress + QUEUEUNIT;
                    
                    
OTHER_SD_SAVE:       u8Ret = f_lseek(file, u32OtherUsbAddress);
                    
                    if(u8Ret != 0)
                    {
//                        printf("file seek error = %x \r\n", u32OtherUsbAddress);
                        goto OTHER_SD_SAVE;
                    } 
                    
                }
                
                else
                {
                    EnterException(ERR_SD_READ_FAIL);
                }
            }
                            
            u16Count = MAXQUEUESIZE - pQueueOtherInfo->Front;
            
            if(u16Count < GetQueueLength(pQueueOtherInfo))
            {
                memcpy(pBuf, pOtherData + pQueueOtherInfo->Front, u16Count);
                memcpy(pBuf + u16Count, pOtherData, GetQueueLength(pQueueOtherInfo) - u16Count);
                
            }
            else
            {
                memcpy(pBuf, pOtherData + pQueueOtherInfo->Front, GetQueueLength(pQueueOtherInfo));
            }
            
            
            u8Ret = f_write(file, pBuf, GetQueueLength(pQueueOtherInfo), &bw);
            
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_WRITE_FAIL);
            } 
            
            
            u8Ret = f_close(file);

            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_CLOSE_FAIL);
            }

            printf("OTHER Save End \r\n");
            u16Count = 15;
            USART2_Send("OTHER Save end \r\n", &u16Count);

            while(1);
            
        }
        
        USBH_Process(&USB_OTG_Core, &USB_Host);
    }
    
}

VOID TestSdStorage(VOID)
{
    U8 u8Ret;
    
    U32 u32WriteSectorAddress = 0, u3ReadSectorAddress = 0, u32UsbAddress = 0;
    
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pBackupBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    U16 u16Count;
    
    printf("SD Card TEST!\r\n");
    
    while(SD_Init())
    {
        printf("SD Card Error!\r\n");
        DelayMs(1000);
    }

    if((pBuf == NULL) || (pBackupBuf == NULL))
    {
        EnterException(ERR_USATT1_MALLOC_FAIL);
    }
    g_TestdataCount = 0;
    pQueueUsart1Info->Front = 0;
    pQueueUsart1Info->Rear = 0;
    
    while(1)
    {
             
        if(GetQueueLength(pQueueUsart1Info) > QUEUEUNIT) 
        {
            memcpy(pBackupBuf, pUsart1Data, MAXQUEUESIZE);//放置中断干扰
            
            GetQueue(pBuf, pBackupBuf, pQueueUsart1Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart1Info);
            
            if(SD_WriteDisk(pBuf, u32WriteSectorAddress, SD_COUNT) == 0)
            {
              //  printf("sector %x\r\n", u32WriteSectorAddress);
                u32WriteSectorAddress = u32WriteSectorAddress + SD_COUNT;
               // u16Count = 8;
               // USART2_Send("rec...\r\n", &u16Count);
                    
            }
            else
            {
                EnterException(ERR_SD_WRITE_FAIL);
            }
        }
        
        if(GetQueueLength(pQueueUsart2Info) > QUEUEUNIT) 
        {
            memcpy(pBackupBuf, pUsart2Data, MAXQUEUESIZE);//放置中断干扰
            
            GetQueue(pBuf, pBackupBuf, pQueueUsart2Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart2Info);
            
            if(SD_WriteDisk(pBuf, u32WriteSectorAddress, SD_COUNT) == 0)
            {
              //  printf("sector %x\r\n", u32WriteSectorAddress);
                u32WriteSectorAddress = u32WriteSectorAddress + SD_COUNT;
               // u16Count = 8;
               // USART2_Send("rec...\r\n", &u16Count);
                    
            }
            else
            {
                EnterException(ERR_SD_WRITE_FAIL);
            }
        }
  
        if(bUsbPlugin == TRUE)
        {
            printf("Save Start \r\n");
//            Usart2_DMA_Send("Save Start \r\n", 12);
            u16Count = 8;
            USART2_Send("start \r\n", &u16Count);
            
            u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            
            while(u3ReadSectorAddress != u32WriteSectorAddress)
            {
                if(SD_ReadDisk(pBuf, u3ReadSectorAddress, SD_COUNT)==0)	
                {
                    u3ReadSectorAddress = u3ReadSectorAddress + SD_COUNT;

                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32UsbAddress = u32UsbAddress + QUEUEUNIT;
                    
                    
SD_SAVE:            u8Ret = f_lseek(file, u32UsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        printf("file seek error = %x \r\n", u32UsbAddress);
                        goto SD_SAVE;
                    } 
                    
                }
                
                else
                {
                    EnterException(ERR_SD_READ_FAIL);
                }
            }
                            
            u16Count = MAXQUEUESIZE - pQueueUsart1Info->Front;
            
            if(u16Count < GetQueueLength(pQueueUsart1Info))
            {
                memcpy(pBuf, pUsart1Data + pQueueUsart1Info->Front, u16Count);
                memcpy(pBuf + u16Count, pUsart1Data, GetQueueLength(pQueueUsart1Info) - u16Count);
                
            }
            else
            {
                memcpy(pBuf, pUsart1Data + pQueueUsart1Info->Front, GetQueueLength(pQueueUsart1Info));
            }
            
            
            u8Ret = f_write(file, pBuf, GetQueueLength(pQueueUsart1Info), &bw);
            
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
//            Usart2_DMA_Send("Save End \r\n", 12);
            u16Count = 6;
            USART2_Send("end \r\n", &u16Count);

            while(1);
            
        }
        
        USBH_Process(&USB_OTG_Core, &USB_Host);
        
    }   
    
}
U8 szTestComm1[] = {0xFE ,0x01 ,0x05 ,0x00 ,0x00 ,0x00 ,0x00 ,0x02 ,0xEF ,0x0D};//显示
U8 szTestComm2[] = {0xFE ,0x01 ,0x06 ,0x00 ,0x00 ,0x00 ,0x00 ,0x05 ,0xEF ,0x0D};//显示

VOID TestOtherSdStorage(VOID)//里程轨距
{
    U8 u8Ret;
    
    U32 u32OtherWriteSectorAddress = OTHER_ADDRESS, u32OtherReadSectorAddress = OTHER_ADDRESS, u32OtherUsbAddress = 0;
    
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pBackupBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    PQueueInfo pQueueBackInfo = mymalloc(SRAMIN, sizeof(CQueueInfo));
    
    U16 u16Count;
    
    U8 u8type;

    printf("SD Card TEST!\r\n");
    
    while(SD_Init())
    {
        printf("SD Card Error!\r\n");
        DelayMs(1000);
    }

    if((pBuf == NULL) || (pBackupBuf == NULL) || (pQueueBackInfo == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }

    pQueueOtherInfo->Front = 0;
    pQueueOtherInfo->Rear = 0;
    pQueueOtherInfo->WriteCount = 0;
    pQueueOtherInfo->ReadCount = 0;
    pQueueOtherInfo->AddCount = 0;
    
    g_bSave = FALSE;//默认不开始保存
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
                    SetOtherWorkState(TRUE);//使能里程轨距50ms输出   
                    break;
                case COMM_CMD_STOP:
                    SetOtherWorkState(FALSE);//禁能里程轨距50ms输出  
                    break;
                case COMM_CMD_CLRMILEAGE:
                    mileage_init();         //清除里程数据
                    break;
                case COMM_CMD_SAVEDATA:
                    g_bSave = TRUE;
                    SetOtherWorkState(FALSE);//禁能里程轨距50ms输出  
                    break;
                default:
                    break;
            }
            
        }
        memcpy(pQueueBackInfo, pQueueOtherInfo,  sizeof(CQueueInfo)); //防止中断干扰 
        if(GetQueueLength(pQueueBackInfo) > QUEUEUNIT)
        {
            memcpy(pBackupBuf, pOtherData, MAXQUEUESIZE);//防止中断干扰
            memcpy(pQueueBackInfo, pQueueOtherInfo,  sizeof(CQueueInfo)); //防止中断干扰 
            
            GetQueue(pBuf, pBackupBuf, pQueueBackInfo, QUEUEUNIT);
            
            DeleteQueue(pQueueOtherInfo);
            
            if(SD_WriteDisk(pBuf, u32OtherWriteSectorAddress, SD_COUNT) == 0)
            {
                u32OtherWriteSectorAddress = u32OtherWriteSectorAddress + SD_COUNT;
                pQueueOtherInfo->WriteCount = pQueueOtherInfo->WriteCount + QUEUEUNIT;              
            }
            else
            {
                EnterException(ERR_SD_WRITE_FAIL);
            }
        }
        if(bUsbPlugin == TRUE)
        {
            WriteCommData(szTestComm1, 10);
            printf("OTHER Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:OTHER.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                while(u32OtherReadSectorAddress != u32OtherWriteSectorAddress)
                {
                    if(SD_ReadDisk(pBuf, u32OtherReadSectorAddress, SD_COUNT)==0)    
                    {
                        u32OtherReadSectorAddress = u32OtherReadSectorAddress + SD_COUNT;
                        
                        pQueueOtherInfo->ReadCount = pQueueOtherInfo->ReadCount + QUEUEUNIT;

                        u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                        
                        if(u8Ret != 0)
                        {
                            EnterException(ERR_UPAN_WRITE_FAIL);
                        } 
                        
                        u32OtherUsbAddress = u32OtherUsbAddress + QUEUEUNIT;
                        
                        
OTHER_SD_SAVE:       u8Ret = f_lseek(file, u32OtherUsbAddress);
                        
                        if(u8Ret != 0)
                        {
                            goto OTHER_SD_SAVE;
                        } 
                        
                    }
                    
                    else
                    {
                        EnterException(ERR_SD_READ_FAIL);
                    }
                }
                                
                u16Count = MAXQUEUESIZE - pQueueOtherInfo->Front;
                
                if(u16Count < GetQueueLength(pQueueOtherInfo))
                {
                    memcpy(pBuf, pOtherData + pQueueOtherInfo->Front, u16Count);
                    memcpy(pBuf + u16Count, pOtherData, GetQueueLength(pQueueOtherInfo) - u16Count);
                    
                }
                else
                {
                    memcpy(pBuf, pOtherData + pQueueOtherInfo->Front, GetQueueLength(pQueueOtherInfo));
                }
                
                pQueueOtherInfo->ReadCount = pQueueOtherInfo->ReadCount + GetQueueLength(pQueueOtherInfo);
                
                u8Ret = f_write(file, pBuf, GetQueueLength(pQueueOtherInfo), &bw);
                
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_WRITE_FAIL);
                } 
                
                
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }

                printf("OTHER Save End \r\n");
            }
            WriteCommData(szTestComm2, 10);
            while(1);
            
        }
        if(g_bSave == TRUE)
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
        }
        
    }
          
}

