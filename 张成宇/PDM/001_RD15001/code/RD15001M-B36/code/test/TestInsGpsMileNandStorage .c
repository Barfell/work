#include "kernal.h"
#include "device.h"
//component
#include "exfuns.h"
#include "usbh_usr.h" 
#include "fontupd.h"
#include "ff.h"
#include "fattester.h"
//app
#include "app_usb.h"


#define INS_NAND_BLOCK_START                    0X0
#define INS_NAND_BLOCK_END                      0X7FF               //在2048块处结束，也就是说给予1G的空间存储

#define GPS_NAND_BLOCK_START                    0X800
#define GPS_NAND_BLOCK_END                      0X8FF               //在2303块处结束，也就是说给予128M的空间存储

#define OTHER_NAND_BLOCK_START                  0X900
#define OTHER_NAND_BLOCK_END                    0XCE7               //在3304块处结束，也就是说给予500M的空间存储

#define RFID_NAND_BLOCK_START                  0XCE8
#define RFID_NAND_BLOCK_END                    0XFFF               //在4096块处结束，也就是说给予396M的空间存储
typedef struct _tagEccInfo
{
    U32 u32ImuEccCount;
    U32 u32GpsEccCount;
    U32 u32MileEccCount;
    U32 u32RfidEccCount;
}CEccInfo, *PEccInfo;

STATIC U32 g_u32BeepCount = 0;
STATIC BOOL g_bBeepWork = FALSE;
BOOL g_bImu = FALSE;

VOID BeepRunProc(VOID)
{
	BeepOn();
	g_bBeepWork = TRUE;
	g_u32BeepCount = GetTickCount();
    

}
VOID BeepStopProc(VOID)
{
	if(g_bBeepWork == TRUE)
	{
		if((GetTickCount() - g_u32BeepCount) > 100)
		{
			g_bBeepWork = FALSE;
			BeepOff();
		}
	}

}

STATIC U8 CalcPosSum(U8* pSrcData, U16 wDataLen)
{
    U8 bCheckSum;
    int i;
    
    if(pSrcData == NULL)
        return 0;
	if(wDataLen == 0xFFFF)
       return 0;
    
    bCheckSum = pSrcData[0];
    
    for(i = 1; i <= wDataLen - 1; i++)
    {
        bCheckSum += pSrcData[i]; 
    }
    return bCheckSum;    
}

BOOL ParsePacket(U8 *pBuf, U16 u16Length)
{
	U8 u8Value;
	BOOL bRet = FALSE;
	if(u16Length == 43)
	{
		u8Value = CalcPosSum(pBuf + 2, 40);
		if(u8Value == pBuf[42])
		{
			bRet = TRUE;
		}
	}
	return bRet;
}

VOID TestInsGpsOtherNandStorage(VOID)//INS+GPS+里程轨距用nand+fram
{
    U8 u8Ret;
	U8 szBuf[30];
    U16 u16Count;
    
    PEccInfo pEccInfo = mymalloc(SRAMIN, sizeof(CEccInfo));
    
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pReadBuf = mymalloc(SRAMIN, QUEUEUNIT);
        
    U8 u8type;
	
    U8 u8Retry;
    
	U8 u8Temp, u8TempSub;
    U32 u32Temp, u32TempSub;
    
    U32 u32InsUsbAddress = 0;
    U32 u32GpsUsbAddress = 0;
    U32 u32OtherUsbAddress = 0;
	U32 u32RfidUsbAddress = 0;
    
    U32 EccCodeSub = 0;
    U32 EccCode = 0;
    
    NAND_ADDRESS Ins_nand_address = {0}, Gps_nand_address = {0}, Other_nand_address = {0}, Rfid_nand_address = {0};
    NAND_ADDRESS Ins_nand_addressSub = {0}, Gps_nand_addressSub = {0}, Other_nand_addressSub = {0},Rfid_nand_addressSub = {0};

    printf("Imu + Gps + Other nand storage TEST!\r\n");
   
    if((pBuf == NULL) || (pReadBuf == NULL) || (pEccInfo == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
    memset(pEccInfo, 0, sizeof(CEccInfo));
    
    pQueueUsart1Info->Front = 0;
    pQueueUsart1Info->Rear = 0;
    pQueueUsart1Info->WriteCount = 0;
    pQueueUsart1Info->ReadCount = 0;
    pQueueUsart1Info->AddCount = 0;
    
    pQueueUsart2Info->Front = 0;
    pQueueUsart2Info->Rear = 0;
    pQueueUsart2Info->WriteCount = 0;
    pQueueUsart2Info->ReadCount = 0;
    pQueueUsart2Info->AddCount = 0;
	
	pQueueUsart3Info->Front = 0;
    pQueueUsart3Info->Rear = 0;
    pQueueUsart3Info->WriteCount = 0;
    pQueueUsart3Info->ReadCount = 0;
    pQueueUsart3Info->AddCount = 0;
     
    pQueueUsart4Info->Front = 0;
    pQueueUsart4Info->Rear = 0;
    pQueueUsart4Info->WriteCount = 0;
    pQueueUsart4Info->ReadCount = 0;
    pQueueUsart4Info->AddCount = 0;
    
    g_bSave = FALSE;//默认不开始保存
    g_bStart = FALSE;
    Ins_nand_address.Block = INS_NAND_BLOCK_START;
    Gps_nand_address.Block = GPS_NAND_BLOCK_START;
    Other_nand_address.Block = OTHER_NAND_BLOCK_START;
	Rfid_nand_address.Block = RFID_NAND_BLOCK_START;
    u16Count = 7;
    USART1_Send("$output", &u16Count);//发命令给IMU，IMU接收到数据后将会回传惯导数据
    while(1)
    {
//        if(g_bImu == FALSE)
//        {
//            ReceiveCommData();
//        }



//----------检测是否有显示板发过来的命令------------------------------
		u8type = GetKeyNumber();
		if(u8type != KEY_INVALID)
		{
			BeepRunProc();
			
			SetKeyNumber(KEY_INVALID);
			 switch(u8type)
			 {
				case KEY_1://擦除FLASH
					ClearUsartCurrentLength(USART3_TYPE);
                    if(g_bStart == FALSE)
                    {
                        printf("\r\nNand格式化\r\n");
                        sprintf((char *)szBuf, "nand formate start...");
    //					DisplayString(0, LINE_1, szBuf);
                        NandBlockEraseInit();
                        printf("\r\nNand存储测试\r\n");
                        sprintf((char *)szBuf, "Start test...");
                        DisplayString(0, LINE_1, szBuf);
                        g_bImu = TRUE;

    //					TIMER_Init(50-1,8400-1);//TIMER_Init(50-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数50次为5ms 
                        g_bStart = TRUE;
                    }
					break;
				case KEY_2://停止测量、保存数据
					//ClearUsartCurrentLength(USART3_TYPE);
					sprintf((char *)szBuf, "Start save...");
					DisplayString(0, LINE_1, szBuf);
					g_bSave = TRUE;
					g_bStart = FALSE;
			
//					sprintf((char *)szBuf, "stop and save...");
//					DisplayString(0, LINE_1, szBuf);
					break;
				case KEY_3:
					ClearUsartCurrentLength(USART3_TYPE);
			
//					sprintf((char *)szBuf, "clear...");
//					DisplayString(0, LINE_1, szBuf);
					break;
				case KEY_4://停止测量
					ClearUsartCurrentLength(USART3_TYPE);
					g_bStart = FALSE;
//					sprintf((char *)szBuf, "stop...");
//					DisplayString(0, LINE_1, szBuf);
					break;
				 
			 }
			

		}

		
//----------保存数据，USB进入到OTG模式-------------------------------------------KEY2
        if(g_bSave == TRUE)
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
        }






		
//-----------检测数据是否存满了缓存----------------------------------------------------- 
        if(GetQueueLength(pQueueUsart1Info) > QUEUEUNIT)
        {

            GetQueue(pBuf, pUsart1Data, pQueueUsart1Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart1Info);
            
            AdjustBadBlock(&Ins_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Ins_nand_address, &EccCode);

            FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), Ins_nand_address);
                                  
            
            Ins_nand_address.Page ++;
        
            if(Ins_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Ins_nand_address.Page = 0;
                Ins_nand_address.Block++;
                if(Ins_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

					printf("\r\n存Nand测试满，结束\r\n");
					while(1);

                }
            } 
			BeepRunProc();
//			sprintf((char *)szBuf, "IMU  B=%d,P=%d", Ins_nand_address.Block, Ins_nand_address.Page);
//			DisplayString(0, LINE_3, szBuf);
        }
///////////
        if(GetQueueLength(pQueueUsart2Info) > QUEUEUNIT)
        { 
		
            GetQueue(pBuf, pUsart2Data, pQueueUsart2Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart2Info);
            
            AdjustBadBlock(&Gps_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Gps_nand_address, &EccCode);
            
            FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), Gps_nand_address);
			
            
            
            Gps_nand_address.Page ++;
        
            if(Gps_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Gps_nand_address.Page = 0;
                Gps_nand_address.Block++;
                if(Gps_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

					printf("\r\n存Nand测试满，结束\r\n");
					while(1);

                }
            }
			BeepRunProc();
//			sprintf((char *)szBuf, "GPS  B=%d,P=%d", Gps_nand_address.Block, Gps_nand_address.Page);
//			DisplayString(0, LINE_4, szBuf);			
        }
///////////        
        if(GetQueueLength(pQueueUsart3Info) > QUEUEUNIT)
        { 
			
            GetQueue(pBuf, pUsart3Data, pQueueUsart3Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart3Info);
            
            AdjustBadBlock(&Rfid_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Rfid_nand_address, &EccCode);
            
            FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), Rfid_nand_address);
                        
            Rfid_nand_address.Page ++;
        
            if(Rfid_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Rfid_nand_address.Page = 0;
                Rfid_nand_address.Block++;
                if(Rfid_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

					printf("\r\n存Nand测试满，结束\r\n");
					while(1);

                }
            }
			BeepRunProc();
//			sprintf((char *)szBuf, "RFID B=%d,P=%d", Rfid_nand_address.Block, Rfid_nand_address.Page);
//			DisplayString(0, LINE_5, szBuf);
        }
///////////        
        if(GetQueueLength(pQueueUsart4Info) > QUEUEUNIT)
        { 			
            GetQueue(pBuf, pUsart4Data, pQueueUsart4Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart4Info);
            
            AdjustBadBlock(&Other_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Other_nand_address, &EccCode);
            
            FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), Other_nand_address);
                        
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
			BeepRunProc();
//			sprintf((char *)szBuf, "MILE B=%d,P=%d", Other_nand_address.Block, Other_nand_address.Page);
//			DisplayString(0, LINE_5, szBuf);
        }




		
//-----------------------如果USB插入，则开始保存数据--------------------------------------
        if(bUsbPlugin == TRUE)
        {
/////////////////
            printf("IMU Save Start \r\n");
			BeepRunProc();
//			sprintf((char *)szBuf, "IMU  start save...");
//			DisplayString(0, LINE_6, szBuf);
            
            u8Ret = f_open(file,(const TCHAR*)"1:IMU.bin",FA_CREATE_NEW | FA_READ | FA_WRITE);
			if(u8Ret != 0)
			{
				u8Ret = f_unlink((const TCHAR*)"1:IMU.bin");
			}

			u8Ret = f_open(file,(const TCHAR*)"1:IMU.bin",FA_CREATE_ALWAYS | FA__WRITTEN | FA_READ | FA_WRITE);	
			          
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                
                Ins_nand_addressSub.Block = INS_NAND_BLOCK_START;
                
                while((Ins_nand_addressSub.Page < Ins_nand_address.Page) || (Ins_nand_addressSub.Block < Ins_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Ins_nand_addressSub);
            
                    FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Ins_nand_addressSub);
                    
                    
                    
RETRY_INS_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Ins_nand_addressSub, &EccCodeSub);
					
					
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            u8Retry++;
                            pEccInfo->u32ImuEccCount = pEccInfo->u32ImuEccCount + 1;
                            goto RETRY_INS_READ;
                        }
                        else
                        {
							//SetNewBadBlock(Ins_nand_addressSub); 
                        }
                                                          
                    }
                    Ins_nand_addressSub.Page ++;
                
                    if(Ins_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Ins_nand_addressSub.Page = 0;
                        Ins_nand_addressSub.Block++;
                        if(Ins_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
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
                    
                    u32InsUsbAddress = u32InsUsbAddress + QUEUEUNIT;

INS_SAVE:           u8Ret = f_lseek(file, u32InsUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto INS_SAVE;
                    } 
                    u32Temp = Ins_nand_address.Page + Ins_nand_address.Block * 128;
                    u32TempSub = Ins_nand_addressSub.Page + Ins_nand_addressSub.Block * 128;
					u8Temp = ((u32TempSub * 10)/u32Temp % 10);
					u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
                    if((u8Temp != 0) && (u8TempSub != 0))
					{
						if((Ins_nand_addressSub.Block % 2 == 0) && (Ins_nand_addressSub.Page == 0))
						{
							BeepRunProc();
							sprintf((char *)szBuf, "Imu process: %d%d%%",u8Temp,u8TempSub);
							DisplayString(0, LINE_7, szBuf);
						}
					}						
                    
                }
                                             
                u32Temp = GetQueueLength(pQueueUsart1Info);
                GetQueue(pBuf, pUsart1Data, pQueueUsart1Info, u32Temp);
                u8Ret = f_write(file, pBuf, u32Temp, &bw); 
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
				BeepRunProc();
//				sprintf((char *)szBuf, "INS Save over");
//				DisplayString(0, LINE_7, szBuf);
				DelayMs_Sft(100);

            }
//////////////////////////////////////////////
            printf("GPS  Save Start \r\n");
			BeepRunProc();
//          sprintf((char *)szBuf, "GPS  start save...");
//			DisplayString(0, LINE_8, szBuf);
            u8Ret = f_open(file,(const TCHAR*)"1:GPS.bin",FA_CREATE_NEW | FA_READ | FA_WRITE);
			if(u8Ret != 0)
			{
				u8Ret = f_unlink((const TCHAR*)"1:GPS.bin");
			}

			u8Ret = f_open(file,(const TCHAR*)"1:GPS.bin",FA_CREATE_ALWAYS | FA__WRITTEN | FA_READ | FA_WRITE);	         
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                Gps_nand_addressSub.Block = GPS_NAND_BLOCK_START;

                while((Gps_nand_addressSub.Page < Gps_nand_address.Page) || (Gps_nand_addressSub.Block < Gps_nand_address.Block))
                {
					u8Retry = 0;

					AdjustBadBlock(&Gps_nand_addressSub);

					FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Gps_nand_addressSub);                    
                    
RETRY_GPS_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Gps_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            pEccInfo->u32GpsEccCount = pEccInfo->u32GpsEccCount + 1;
                            u8Retry++;
                            goto RETRY_GPS_READ;
                        }
                        else
                        {
							//SetNewBadBlock(Gps_nand_addressSub); 
                        }
                                                          
                    }
                    Gps_nand_addressSub.Page ++;
                
                    if(Gps_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Gps_nand_addressSub.Page = 0;
                        Gps_nand_addressSub.Block++;
                        if(Gps_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
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
                    
                    u32GpsUsbAddress = u32GpsUsbAddress + QUEUEUNIT;

GPS_SAVE:           u8Ret = f_lseek(file, u32GpsUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto GPS_SAVE;
                    } 
                    u32Temp = Gps_nand_address.Page + Gps_nand_address.Block * 128;
                    u32TempSub = Gps_nand_addressSub.Page + Gps_nand_addressSub.Block * 128;
					u8Temp = ((u32TempSub * 10)/u32Temp % 10);
					u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
                    if((u8Temp != 0) && (u8TempSub != 0))
					{
						if((Gps_nand_addressSub.Block % 2 == 0) && (Gps_nand_addressSub.Page == 0))
						{
							BeepRunProc();
							sprintf((char *)szBuf, "Gps process:%d%d%%",u8Temp,u8TempSub);
							DisplayString(0, LINE_7, szBuf); 
						}
					}						
                    
                }
                                             
                u32Temp = GetQueueLength(pQueueUsart2Info);
                GetQueue(pBuf, pUsart2Data, pQueueUsart2Info, u32Temp);
                u8Ret = f_write(file, pBuf, u32Temp, &bw); 
                u8Ret = f_close(file);


                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
				BeepRunProc();
//				sprintf((char *)szBuf, "GPS  Save over");
//				DisplayString(0, LINE_9, szBuf);
				DelayMs_Sft(100);

 
            }            
//////////////////////////////////////////////            
            printf("MILE Save Start \r\n");
			BeepRunProc();
//			sprintf((char *)szBuf, "MILE start save...");
//			DisplayString(0, LINE_10, szBuf);
            
			u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",FA_CREATE_NEW | FA_READ | FA_WRITE);
			if(u8Ret != 0)
			{
				u8Ret = f_unlink((const TCHAR*)"1:MILE.txt");
			}

			u8Ret = f_open(file,(const TCHAR*)"1:MILE.txt",FA_CREATE_ALWAYS | FA__WRITTEN | FA_READ | FA_WRITE);	
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                Other_nand_addressSub.Block = OTHER_NAND_BLOCK_START;
                
                while((Other_nand_addressSub.Page < Other_nand_address.Page) || (Other_nand_addressSub.Block < Other_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Other_nand_addressSub);
            
                    FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Other_nand_addressSub);
                    
                    
                    
RETRY_OTHER_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Other_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            pEccInfo->u32MileEccCount = pEccInfo->u32MileEccCount + 1;
                            u8Retry++;
                            goto RETRY_OTHER_READ;
                        }
                        else
                        {
							//SetNewBadBlock(Other_nand_addressSub); 
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
					u8Temp = ((u32TempSub * 10)/u32Temp % 10);
					u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
                    if((u8Temp != 0) && (u8TempSub != 0))
					{
						if((Other_nand_addressSub.Block % 2 == 0) && (Other_nand_addressSub.Page == 0))
						{
							BeepRunProc();
							sprintf((char *)szBuf, "Other process:%d%d%%",u8Temp,u8TempSub);
							DisplayString(0, LINE_7, szBuf);
						}
					}
                        
                    
                }
                                             
                u32Temp = GetQueueLength(pQueueUsart4Info);
                GetQueue(pBuf, pUsart4Data, pQueueUsart4Info, u32Temp);
                u8Ret = f_write(file, pBuf, u32Temp, &bw); 
                u8Ret = f_close(file);


                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
				BeepRunProc();
//				sprintf((char *)szBuf, "MILE Save over");
//				DisplayString(0, LINE_11, szBuf);
				
            }
 ////////////////////////////////////////
			printf("RFID Save Start \r\n");
			BeepRunProc();
//			sprintf((char *)szBuf, "RFID start save...");
//			DisplayString(0, LINE_10, szBuf);
            
			u8Ret = f_open(file,(const TCHAR*)"1:RFID.txt",FA_CREATE_NEW | FA_READ | FA_WRITE);
			if(u8Ret != 0)
			{
				u8Ret = f_unlink((const TCHAR*)"1:RFID.txt");
			}

			u8Ret = f_open(file,(const TCHAR*)"1:RFID.txt",FA_CREATE_ALWAYS | FA__WRITTEN | FA_READ | FA_WRITE);	
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                Rfid_nand_addressSub.Block = RFID_NAND_BLOCK_START;
                
                while((Rfid_nand_addressSub.Page < Rfid_nand_address.Page) || (Rfid_nand_addressSub.Block < Rfid_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Rfid_nand_addressSub);
            
                    FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Rfid_nand_addressSub);
                    
                    
                    
RETRY_RFID_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Rfid_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            pEccInfo->u32RfidEccCount = pEccInfo->u32RfidEccCount + 1;
                            u8Retry++;
                            goto RETRY_RFID_READ;
                        }
                        else
                        {
							//SetNewBadBlock(Rfid_nand_addressSub); 
                        }
                                                          
                    }
                    Rfid_nand_addressSub.Page ++;
                
                    if(Rfid_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Rfid_nand_addressSub.Page = 0;
                        Rfid_nand_addressSub.Block++;
                        if(Rfid_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
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
                    
                    u32RfidUsbAddress = u32RfidUsbAddress + QUEUEUNIT;

RFID_SAVE:         u8Ret = f_lseek(file, u32RfidUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto RFID_SAVE;
                    } 
                    
                    u32Temp = Rfid_nand_address.Page + Rfid_nand_address.Block * 128;
                    u32TempSub = Rfid_nand_addressSub.Page + Rfid_nand_addressSub.Block * 128;
					u8Temp = ((u32TempSub * 10)/u32Temp % 10);
					u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
                    if((u8Temp != 0) && (u8TempSub != 0))
					{
						if((Rfid_nand_addressSub.Block % 2 == 0) && (Rfid_nand_addressSub.Page == 0))
						{
							BeepRunProc();
							sprintf((char *)szBuf, "Rfid process:%d%d%%",u8Temp,u8TempSub);
							DisplayString(0, LINE_7, szBuf);
						}
					}
                        
                    
                }
                                             
                u32Temp = GetQueueLength(pQueueUsart3Info);
                GetQueue(pBuf, pUsart3Data, pQueueUsart3Info, u32Temp);
                u8Ret = f_write(file, pBuf, u32Temp, &bw); 
                u8Ret = f_close(file);


                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
				BeepRunProc();
//				sprintf((char *)szBuf, "RFID Save over");
//				DisplayString(0, LINE_11, szBuf);
				
            }
 ////////////////////////////////////////
            u8Ret = f_open(file,(const TCHAR*)"1:Debug.txt",FA_CREATE_NEW | FA_READ | FA_WRITE);
			if(u8Ret != 0)
			{
				u8Ret = f_unlink((const TCHAR*)"1:Debug.txt");
			}

			u8Ret = f_open(file,(const TCHAR*)"1:Debug.txt",FA_CREATE_ALWAYS | FA__WRITTEN | FA_READ | FA_WRITE);	
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                memset(szBuf, 0, sizeof(szBuf));
                sprintf((char *)szBuf, "Imu=%d,Gps=%d,Mile=%d,rfid=%d", pEccInfo->u32ImuEccCount, pEccInfo->u32GpsEccCount, pEccInfo->u32MileEccCount, pEccInfo->u32RfidEccCount);
                u8Ret = f_write(file, szBuf, sizeof(szBuf), &bw);
                    
                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_WRITE_FAIL);
                } 
				
				u8Ret = f_close(file);


                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
            }
 ////////////////////////////////////////
			DelayMs_Sft(100);
			DisplayClear(0, LINE_6, 128, LINE_12 - LINE_6, FALSE);
			DelayMs_Sft(100);
			BeepRunProc();
			sprintf((char *)szBuf, "Save all over");
			DisplayString(30, LINE_9, szBuf);			
            printf("\r\n全部保存结束\r\n");
            while(1);
        }


		
    }
          
}
