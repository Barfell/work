#include "device.h"

#define RCC_STIM300_CONFIG()	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
//现在拿来控制CPLD输出同步脉冲
//#define TOV_GPIO				GPIOE
//#define TOV_PIN					GPIO_Pin_2

#define RST_GPIO				GPIOE
#define RST_PIN					GPIO_Pin_3

//开启5v电源使用
#define PEN_GPIO				GPIOE
#define PEN_PIN					GPIO_Pin_4


VOID Stim300Unwork(VOID)
{
    GPIO_ResetBits(RST_GPIO, RST_PIN);
}

VOID Stim300work(VOID)
{
    GPIO_SetBits(RST_GPIO, RST_PIN);
}

VOID Stim300PwrOn(VOID)
{
    GPIO_SetBits(PEN_GPIO, PEN_PIN);
}

VOID Stim300PwrOff(VOID)
{
    GPIO_ResetBits(PEN_GPIO, PEN_PIN);
}

VOID TestStim300Proc(VOID)
{
	
	U16 u16Length;
	
	uart1_init(921600, 4096, 2048);//imu
	uart2_init(115200, 4096, 4096);//mile

    RCC_STIM300_CONFIG();
	
	GPIO_Set(RST_GPIO, RST_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	
	GPIO_Set(PEN_GPIO, PEN_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	Stim300PwrOn();
	
	Stim300Unwork();
	
	DelayMs(10);
	
    Stim300work();
	
		
	
	while(1)
	{
		u16Length = GetUsartCurrentLength(USART1_TYPE);
		if(u16Length != 0)
		{			
			USART2_Send(g_pUsart1_rx_buf, &u16Length);
			
			ClearUsartCurrentLength(USART1_TYPE);
		}
		
		u16Length = GetUsartCurrentLength(USART2_TYPE);
		if(u16Length != 0)
		{
			USART1_Send(g_pUsart2_rx_buf, &u16Length);
			ClearUsartCurrentLength(USART2_TYPE);
		}
	}
	    
}

#define INS_NAND_BLOCK_START                    0X0
#define INS_NAND_BLOCK_END                      0X3FF               //在1024块处结束，也就是说给予512M的空间存储

#define MILE_NAND_BLOCK_START                  0X400
#define MILE_NAND_BLOCK_END                    0X5FF               //在1536块处结束，也就是说给予256M的空间存储


typedef struct _tagEccInfo
{
    U32 u32ImuEccCount;
    U32 u32MileEccCount;
}CEccInfo, *PEccInfo;


CSysRunInfo cSysRunInfo = {FALSE, FALSE, FALSE};


U32 g_u32BeepCount = 0;
BOOL g_bBeepWork = FALSE;

VOID IndicationRunProc(VOID)
{
	BeepOn();
	DatLedOn();
	g_bBeepWork = TRUE;
	g_u32BeepCount = GetTickCount();
    

}
VOID IndicationStopThreadProc(VOID)
{
	if(g_bBeepWork == TRUE)
	{
		if((GetTickCount() - g_u32BeepCount) > 100)
		{
			g_bBeepWork = FALSE;
			BeepOff();
			DatLedOff();
		}
	}

}

BOOL g_bFunction = FALSE;

STATIC BOOL g_bWork = FALSE;

STATIC U8 szClearMileAData[6] = {0Xfe, 0X00, 0X00, 0X00, 0X00, 0Xef};
STATIC U8 szClearMileBData[6] = {0Xfd, 0X00, 0X00, 0X00, 0X00, 0Xdf};
STATIC U8 szClearMileCData[6] = {0Xfc, 0X00, 0X00, 0X00, 0X00, 0Xcf};
STATIC U8 szSetMileInternalCData[6] = {0Xfb, 0X00, 0X00, 0X00, 0X00, 0Xbf};
enum
{
	CMD_SET_MILE_A = 1,
	CMD_SET_MILE_B,
	CMD_SET_MILE_C, 
	CMD_SET_MILE_INTERNAL,
};

STATIC VOID ControlMileProc(U8 u8Type, U32 u32Value)
{
	U8 *pBuf;
	U16 u16Count;
	U32 u32SynCnt;
	U8 *g_pSyndataCount =  (U8 *)&u32SynCnt;
	u32SynCnt = u32Value;
	switch(u8Type)
	{
		case CMD_SET_MILE_A:
			pBuf = szClearMileAData;
			break;
		case CMD_SET_MILE_B:
			pBuf = szClearMileBData;
		
			break;
		case CMD_SET_MILE_C:
			pBuf = szClearMileCData;
		
			break;
		case CMD_SET_MILE_INTERNAL:
			pBuf = szSetMileInternalCData;
		
			break;
	}
	pBuf[1] = *g_pSyndataCount ;
	pBuf[2] = *(g_pSyndataCount + 1) ;
	pBuf[3] = *(g_pSyndataCount + 2) ;
	pBuf[4] = *(g_pSyndataCount + 3) ;
	
	u16Count = 6;
	USART2_Send(pBuf, &u16Count);
}

STATIC VOID DetectKeyState(VOID)
{
	if(g_bFunction == TRUE)
	{
		if(g_bWork == FALSE)
		{
			

			Stim300work();
			DelayMs_Sft(1000);
			SysLedOn();
			CpldOn();//开ETR
			SetEtrSynCount(0);
			ControlMileProc(CMD_SET_MILE_A, 0);
			DelayMs_Sft(20);
			ControlMileProc(CMD_SET_MILE_B, 0);
			DelayMs_Sft(20);
			ControlMileProc(CMD_SET_MILE_C, 0);
			DelayMs_Sft(20);
			ControlMileProc(CMD_SET_MILE_INTERNAL, 50);
			
			NandBlockEraseInit();
			ExternFlash_Init();
			
			cSysRunInfo.bImu = TRUE;
			cSysRunInfo.bStart = TRUE;
			cSysRunInfo.bSave = FALSE;
			g_bWork = TRUE;
		}
	}
	else
	{
		if(g_bWork == TRUE)
		{
			cSysRunInfo.bImu = FALSE;
			cSysRunInfo.bStart = FALSE;
			cSysRunInfo.bSave = TRUE;
			
			Stim300PwrOff();
			
		}
		
	}
}

STATIC VOID ParseDebugImuCmd(U8 *pBuf, U16 u16Length)
{
	if(u16Length == 16)
	{
		if(memcmp(pBuf, "Run stim300 test", 16) == 0)
		{
			cSysRunInfo.bImu = TRUE;
			cSysRunInfo.bStart = TRUE;
			cSysRunInfo.bSave = FALSE;
			
			Stim300work();
			SysLedOn();
			CpldOn();//开ETR
			SetEtrSynCount(0);
			
			NandBlockEraseInit();
			
		}
		else if(memcmp(pBuf, "End stim300 test", 16) == 0)
		{
			cSysRunInfo.bImu = FALSE;
			cSysRunInfo.bStart = FALSE;
			cSysRunInfo.bSave = TRUE;
			
			Stim300PwrOff();
			SysLedOff();
			DatLedOn();
		}
		else
		{
			USART1_Send(g_pUsart2_rx_buf, &u16Length);
			ClearUsartCurrentLength(USART2_TYPE);
		}
		
	}
	
}


//00
STATIC VOID GetPreDataParameter(NAND_ADDRESS *pIns_nand_address, NAND_ADDRESS *Mile_nand_address)
{
	pIns_nand_address->Block = 0xff;//默认128M
	pIns_nand_address->Page = 0;
	
	Mile_nand_address->Block = 0xff + MILE_NAND_BLOCK_START;
	Mile_nand_address->Page = 0;
}


VOID ReadMeasureData(U8 *pBuf, U8 *pReadBuf, PEccInfo pEccInfo)
{

	U8 u8Ret, u8Retry;
	U8 u8Temp, u8TempSub;
	U8 szBuf[30];
	U32 u32Temp, u32TempSub;

	U32 u32InsUsbAddress = 0;
	U32 u32MileUsbAddress = 0;

	U32 EccCodeSub = 0;
	U32 EccCode = 0;
	NAND_ADDRESS Ins_nand_address = {0}, Mile_nand_address = {0};
    NAND_ADDRESS Ins_nand_addressSub = {0}, Mile_nand_addressSub = {0};
	
	GetPreDataParameter(&Ins_nand_address, &Mile_nand_address);
	
	SysLedOn();
	
	IndicationRunProc();            
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
					IndicationRunProc();
				}
			}						
			
		}
									 
		u8Ret = f_close(file);

		if(u8Ret != 0)
		{
			EnterException(ERR_UPAN_CLOSE_FAIL);
		}
		IndicationRunProc();

		DelayMs_Sft(100);

	}
//////////////////////////////////////////////
	IndicationRunProc();            
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
		Mile_nand_addressSub.Block = MILE_NAND_BLOCK_START;
		
		while((Mile_nand_addressSub.Page < Mile_nand_address.Page) || (Mile_nand_addressSub.Block < Mile_nand_address.Block))
		{
			u8Retry = 0;
						
			AdjustBadBlock(&Mile_nand_addressSub);
	
			FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Mile_nand_addressSub);
			
			
			
RETRY_MILE_READ: 
			FSMC_NAND_ReadSmallPage(pBuf, Mile_nand_addressSub, &EccCodeSub);
				
			if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
			{
				if(u8Retry < 1)
				{
					pEccInfo->u32MileEccCount = pEccInfo->u32MileEccCount + 1;
					u8Retry++;
					goto RETRY_MILE_READ;
				}
				else
				{
					//SetNewBadBlock(Mile_nand_addressSub); 
				}
												  
			}
			Mile_nand_addressSub.Page ++;
		
			if(Mile_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
			{
				Mile_nand_addressSub.Page = 0;
				Mile_nand_addressSub.Block++;
				if(Mile_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
				{
					while(1);
					
				}
			}
			
			u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
			
			if(u8Ret != 0)
			{
				EnterException(ERR_UPAN_WRITE_FAIL);
			} 
			
			u32MileUsbAddress = u32MileUsbAddress + QUEUEUNIT;

MILE_SAVE:         u8Ret = f_lseek(file, u32MileUsbAddress);
			
			if(u8Ret != 0)
			{
				goto MILE_SAVE;
			} 
			
			u32Temp = Mile_nand_address.Page + Mile_nand_address.Block * 128;
			u32TempSub = Mile_nand_addressSub.Page + Mile_nand_addressSub.Block * 128;
			u8Temp = ((u32TempSub * 10)/u32Temp % 10);
			u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
			if((u8Temp != 0) && (u8TempSub != 0))
			{
				if((Mile_nand_addressSub.Block % 2 == 0) && (Mile_nand_addressSub.Page == 0))
				{
					IndicationRunProc();
				}
			}
				
			
		}
		u8Ret = f_close(file);


		if(u8Ret != 0)
		{
			EnterException(ERR_UPAN_CLOSE_FAIL);
		}
		IndicationRunProc();
		
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
		sprintf((char *)szBuf, "Imu error = %d,Mile error = %d", pEccInfo->u32ImuEccCount, pEccInfo->u32MileEccCount);
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
	IndicationRunProc();		
	DatLedOff();
	SysLedOff();			
	while(1);			
		
}

VOID TestStim300StorageProc(VOID)
{
	
	U8 u8Ret;
	U8 szBuf[30];
    U16 u16Length;
    
    PEccInfo pEccInfo = mymalloc(SRAMIN, sizeof(CEccInfo));
    
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pReadBuf = mymalloc(SRAMIN, QUEUEUNIT);
        
	
    U8 u8Retry;
    
	U8 u8Temp, u8TempSub;
    U32 u32Temp, u32TempSub;
    
    U32 u32InsUsbAddress = 0;
    U32 u32MileUsbAddress = 0;
    
    U32 EccCodeSub = 0;
    U32 EccCode = 0;
    
    NAND_ADDRESS Ins_nand_address = {0}, Mile_nand_address = {0};
    NAND_ADDRESS Ins_nand_addressSub = {0}, Mile_nand_addressSub = {0};
	
	uart1_init(921600, 2048, 2048);//imu
	uart2_init(115200, 2048, 2048);//mile

    RCC_STIM300_CONFIG();
	
	GPIO_Set(RST_GPIO, RST_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	GPIO_Set(PEN_GPIO, PEN_PIN, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	Stim300PwrOff();
	
	DelayMs(100);
	
	Stim300PwrOn();
	
	Stim300Unwork();
	
   
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
	
    
    cSysRunInfo.bSave = FALSE;//默认不开始保存
    cSysRunInfo.bStart = FALSE;
	
    Ins_nand_address.Block = INS_NAND_BLOCK_START;
    Mile_nand_address.Block = MILE_NAND_BLOCK_START;
	
	
		
	while(1)
	{
		
//		u16Length = GetUsartCurrentLength(USART2_TYPE);
//		if(u16Length != 0)
//		{
//			ParseDebugImuCmd(g_pUsart2_rx_buf, u16Length);
//			ClearUsartCurrentLength(USART2_TYPE);
//		}
		if(cSysRunInfo.bSave == FALSE)
		{
			if(bUsbPlugin == TRUE)
			{
				ReadMeasureData(pBuf, pReadBuf, pEccInfo);
			}
		}
		
//		if(cSysRunInfo.bSave == TRUE)
//        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
//        }
		////////////
		DetectKeyState();
		////////////        
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
					while(1);//over

                }
            } 
			IndicationRunProc();
        }
///////////
        if(GetQueueLength(pQueueUsart2Info) > QUEUEUNIT)
        { 
		
            GetQueue(pBuf, pUsart2Data, pQueueUsart2Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart2Info);
            
            AdjustBadBlock(&Mile_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Mile_nand_address, &EccCode);
            
            FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), Mile_nand_address);
			
            
            
            Mile_nand_address.Page ++;
        
            if(Mile_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Mile_nand_address.Page = 0;
                Mile_nand_address.Block++;
                if(Mile_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {
					while(1);//over
                }
            }
			IndicationRunProc();			
        }
/////////// 
		
		
		
		if((bUsbPlugin == TRUE) && (cSysRunInfo.bSave == TRUE))
        {
/////////////////
			IndicationRunProc();            
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
							IndicationRunProc();
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
				IndicationRunProc();

				DelayMs_Sft(100);

            }
//////////////////////////////////////////////
			IndicationRunProc();            
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
                Mile_nand_addressSub.Block = MILE_NAND_BLOCK_START;
                
                while((Mile_nand_addressSub.Page < Mile_nand_address.Page) || (Mile_nand_addressSub.Block < Mile_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Mile_nand_addressSub);
            
                    FSMC_NAND_ReadSpareArea((U8 *)(&EccCode), Mile_nand_addressSub);
                    
                    
                    
RETRY_MILE_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Mile_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            pEccInfo->u32MileEccCount = pEccInfo->u32MileEccCount + 1;
                            u8Retry++;
                            goto RETRY_MILE_READ;
                        }
                        else
                        {
							//SetNewBadBlock(Mile_nand_addressSub); 
                        }
                                                          
                    }
                    Mile_nand_addressSub.Page ++;
                
                    if(Mile_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Mile_nand_addressSub.Page = 0;
                        Mile_nand_addressSub.Block++;
                        if(Mile_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
                        {
                            while(1);
                            
                        }
                    }
                    
                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32MileUsbAddress = u32MileUsbAddress + QUEUEUNIT;

MILE_SAVE:         u8Ret = f_lseek(file, u32MileUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto MILE_SAVE;
                    } 
                    
                    u32Temp = Mile_nand_address.Page + Mile_nand_address.Block * 128;
                    u32TempSub = Mile_nand_addressSub.Page + Mile_nand_addressSub.Block * 128;
					u8Temp = ((u32TempSub * 10)/u32Temp % 10);
					u8TempSub = (((u32TempSub * 100)/u32Temp) % 10);
                    if((u8Temp != 0) && (u8TempSub != 0))
					{
						if((Mile_nand_addressSub.Block % 2 == 0) && (Mile_nand_addressSub.Page == 0))
						{
							IndicationRunProc();
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
				IndicationRunProc();
				
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
                sprintf((char *)szBuf, "Imu error = %d,Mile error = %d", pEccInfo->u32ImuEccCount, pEccInfo->u32MileEccCount);
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
			IndicationRunProc();		
			DatLedOff();
			SysLedOff();			
            while(1);			
		}
			
	}
	
	
}

