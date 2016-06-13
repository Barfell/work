#include "kernal.h"
#include "device.h"

STATIC U8 g_sztest[NAND_BYTENUMBER_PERPAGE] = {0};
STATIC U8 g_u8Page = 0;
STATIC U16 g_u16Block = 0;
STATIC U8 g_u8Data = 0;
STATIC NAND_IDTypeDef  cNand_ID_tag = {0};
STATIC NAND_ADDRESS cNAND_ADDRESS_tag = {0};

STATIC VOID HandleDetectNandflashBadBlock(VOID)
{
    U16 u16BlockCnt;
    U8 u8Retry = 0;
    U8 *pCmpBuf = mymalloc(SRAMIN, NAND_BYTENUMBER_PERPAGE);
    U32 EccCode;
    U32 EccCodeSub;
    U32 u32TotalCount = 0,u32FailCount = 0, u32RecoverCount = 0;
    uint32_t ret;

    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
    for(u16BlockCnt = 0; u16BlockCnt < NAND_BYTENUMBER_PERPAGE; u16BlockCnt++)
    {
        g_sztest[u16BlockCnt] = (u16BlockCnt & 0xff);

    }
            
    printf("\r\nNand test\r\n");
    NandBlockEraseInit();
    printf("\r\nNand test\r\n");
    
    cNAND_ADDRESS_tag.Block = 0;
    cNAND_ADDRESS_tag.Page = 0;
	
	u16BlockCnt = 0;
    
    while(cNAND_ADDRESS_tag.Block < NAND_MAXNUMBER_BLOCK)
    {
        u8Retry = 0;
        
        AdjustBadBlock(&cNAND_ADDRESS_tag);
        
RETRY_WRITE: 
        ret = FSMC_NAND_WriteSmallPage(g_sztest, cNAND_ADDRESS_tag, &EccCode);
                
        if(ret != NAND_PASS)
        {
            goto RETRY_WRITE;
        }
		FSMC_NAND_WriteSpareArea((U8 *)(&EccCode), cNAND_ADDRESS_tag);

		FSMC_NAND_ReadSpareArea((U8 *)(&EccCodeSub), cNAND_ADDRESS_tag);
 
        
RETRY_READ: 
        ret = FSMC_NAND_ReadSmallPage(pCmpBuf, cNAND_ADDRESS_tag, &EccCodeSub);
        
        
        if(ret != NAND_PASS)
        {
            goto RETRY_READ;
        }
       
        if(memcmp(g_sztest, pCmpBuf, NAND_BYTENUMBER_PERPAGE) != 0) 
        {
                       
            if(ECCCheck(EccCode, EccCodeSub, pCmpBuf) == 3)
            {
                u32FailCount++;
                if(memcmp(g_sztest, pCmpBuf, NAND_BYTENUMBER_PERPAGE) != 0)
                {
                   if(u8Retry < 1)
                   {
                       u8Retry++;
                       goto RETRY_READ;
                   }
                   else
                   {
                       
                       //SetNewBadBlock(cNAND_ADDRESS_tag);
                        printf("\r\nBad page = 0x%x, Block = 0x%x", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block);   
                       
                   }                                   

                }
                else
                {
                    u32RecoverCount++;
                    printf("\r\nRecover page = 0x%x, block = 0x%x", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block); 
                }
            }
			if(memcmp(g_sztest, pCmpBuf, NAND_BYTENUMBER_PERPAGE) == 0) 
			{
				printf("\r\nRecover page OK = 0x%x, block = 0x%x", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block);
			}
			else
			{
				printf("\r\nRecover page error = 0x%x, block = 0x%x", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block);
			}
        }
        u32TotalCount++; 
        memcpy(g_sztest, (U8 *)(&u32TotalCount), 4);
        cNAND_ADDRESS_tag.Page = cNAND_ADDRESS_tag.Page + 1;
        if(cNAND_ADDRESS_tag.Page == NAND_PAGENUMBER_PERBLOCK)
        {
            cNAND_ADDRESS_tag.Page = 0;
            cNAND_ADDRESS_tag.Block = cNAND_ADDRESS_tag.Block + 1;
        }
		
		if(cNAND_ADDRESS_tag.Block - u16BlockCnt == 50)
		{
			u16BlockCnt = cNAND_ADDRESS_tag.Block;
			printf("\r\n Current block = 0x%x",cNAND_ADDRESS_tag.Block);
		}
		
            
    }
        
}



STATIC VOID HandleCheckNandflashBadBlock(VOID)
{
    
    U8 *pCmpBuf = mymalloc(SRAMIN, NAND_ECC_BYTENUMBER);
    U16 u16Count = 0;
    cNAND_ADDRESS_tag.Block = 0;
    cNAND_ADDRESS_tag.Page = 0;

    memset(pCmpBuf, 0xff, NAND_ECC_BYTENUMBER);
    printf("\r\ncheck start\r\n");
    while(cNAND_ADDRESS_tag.Block < NAND_MAXNUMBER_BLOCK)
    {
        FSMC_NAND_ReadSpareArea(g_sztest, cNAND_ADDRESS_tag);
        if(memcmp(g_sztest, pCmpBuf, NAND_ECC_BYTENUMBER) != 0)
        {
            printf("bad block = %x", cNAND_ADDRESS_tag.Block);
			u16Count++;
        }
        cNAND_ADDRESS_tag.Block = cNAND_ADDRESS_tag.Block + 1;
           
    }
    printf("\r\ncheck over, fail count = %x\r\n", u16Count);    
}

STATIC VOID HandleEraseNandflash(VOID)
{
   
    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
    printf("\r\n%x\r\n", FSMC_NAND_EraseBlock(cNAND_ADDRESS_tag));
}

STATIC VOID HandleReadNandflash(VOID)
{
    U16 u16Count = 0;
    
    uint32_t ret;
    
    U32 EccCode;
    
    memset(g_sztest, 0x55, NAND_BYTENUMBER_PERPAGE);
    
    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
    ret = FSMC_NAND_ReadSmallPage(g_sztest, cNAND_ADDRESS_tag, &EccCode);
      
    for(u16Count = 0; u16Count < (NAND_BYTENUMBER_PERPAGE/g_cUsart1Info.Usart_sen_len); u16Count ++)
    { 
        Usart1_DMA_Send(g_sztest + (g_cUsart1Info.Usart_sen_len * u16Count), g_cUsart1Info.Usart_sen_len);
        DelayMs(50);
    }
    DelayMs(50);
    Usart1_DMA_Send((U8 *)(&EccCode), NAND_ECC_BYTENUMBER);
      
    printf("%x",ret);
}


STATIC VOID HandleReadSpareNandflash(VOID)
{

    uint32_t ret;
	
    memset(g_sztest, 0x55, NAND_BYTENUMBER_PERPAGE);
    
    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
  
    ret = FSMC_NAND_ReadSpareArea(g_sztest, cNAND_ADDRESS_tag);   
	
	Usart1_DMA_Send(g_sztest, NAND_ECC_BYTENUMBER);
	
	DelayMs(50);

      
    printf("%x", ret);
}

STATIC VOID HandleWriteSpareNandflash(VOID)
{
    uint32_t ret;

    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
    memset(g_sztest, g_u8Data, NAND_BYTENUMBER_PERPAGE);
   

    ret = FSMC_NAND_WriteSpareArea(g_sztest, cNAND_ADDRESS_tag);
    
    printf("%x", ret);
}


STATIC VOID HandleWriteNandflash(VOID)
{
    uint32_t ret;
    U32 EccCode;

    cNAND_ADDRESS_tag.Block = g_u16Block;
    cNAND_ADDRESS_tag.Page = g_u8Page;
    
    memset(g_sztest, g_u8Data, NAND_BYTENUMBER_PERPAGE);
   
    ret = FSMC_NAND_WriteSmallPage(g_sztest, cNAND_ADDRESS_tag, &EccCode);
    
    printf("%x", ret);
    
}
STATIC VOID HandleAutoWriteNandflash(VOID)
{
    
    U32 u32Value = 0;
    
    U32 u32Tick = 0;
    
    U32 u32Status;
    
    U32 EccCode;
    
    memset(&cNAND_ADDRESS_tag, 0, sizeof(NAND_ADDRESS));
    
    u32Tick = GetTickCount();
    
    printf("Nandflash Auto write Start =  %d\r\n", u32Tick);
	
    while(1)
    {
        memset(g_sztest, u32Value, NAND_BYTENUMBER_PERPAGE);
        
        u32Status = FSMC_NAND_WriteSmallPage(g_sztest, cNAND_ADDRESS_tag, &EccCode);
        
        if(u32Status != NAND_PASS)
        {
            u32Tick = GetTickCount();
            printf("Nandflash Write error page = %d, block = %d, error code = %x\r\n", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block, u32Status);
            printf("Nandflash Auto write Error = %d\r\n", u32Tick);
            while(1);
        }
        
        u32Value++;
        cNAND_ADDRESS_tag.Page++;
        if(cNAND_ADDRESS_tag.Page == NAND_PAGENUMBER_PERBLOCK)
        {
            cNAND_ADDRESS_tag.Page = 0;
            cNAND_ADDRESS_tag.Block++;
            if(cNAND_ADDRESS_tag.Block == NAND_MAXNUMBER_BLOCK)
            {
                u32Tick = GetTickCount();
                printf("Nandflash Auto write End = %d\r\n", u32Tick); 
                break;
 
            }
        }
    }       
    
}


STATIC VOID HandleAutoReadNandflash(VOID)
{
    
    U32 u32Value;
    
    U32 EccCode;
    
    U32 u32Tick = 0;
    
    U8 u8Testtest[NAND_BYTENUMBER_PERPAGE];
        
    memset(&cNAND_ADDRESS_tag, 0, sizeof(NAND_ADDRESS));
    
    u32Tick = GetTickCount();
    
    printf("Nandflash Auto Read Start =  %d\r\n", u32Tick);
    while(1)
    {        
        memset(u8Testtest, u32Value, NAND_BYTENUMBER_PERPAGE);

        FSMC_NAND_ReadSmallPage(g_sztest, cNAND_ADDRESS_tag, &EccCode);
        
        if(memcmp(u8Testtest, g_sztest, NAND_BYTENUMBER_PERPAGE) != 0)
        {
            printf("Nandflash Read error page = %d, block = %d\r\n", cNAND_ADDRESS_tag.Page, cNAND_ADDRESS_tag.Block);
            break;
        }
        
        u32Value++;
        cNAND_ADDRESS_tag.Page++;
        if(cNAND_ADDRESS_tag.Page == NAND_PAGENUMBER_PERBLOCK)
        {
            cNAND_ADDRESS_tag.Page = 0;
            cNAND_ADDRESS_tag.Block++;

            if(cNAND_ADDRESS_tag.Block == NAND_MAXNUMBER_BLOCK)
            {
                    
                printf("Nandflash Auto Read End\r\n"); 
                break;
            }
        }

    }       
    
}

STATIC VOID HandleAutoEraseNandflash(VOID)
{
    
    
    U32  u32Tick= 0;
    
    uint32_t ret;
    
    memset(&cNAND_ADDRESS_tag, 0, sizeof(NAND_ADDRESS));
    
    u32Tick = GetTickCount();
    
    printf("Nandflash Auto Erase Start = %d\r\n", u32Tick);
    while(1)
    {
        
        ret = FSMC_NAND_EraseBlock(cNAND_ADDRESS_tag);
        
        if(ret != NAND_READY)
        {
            printf("Nandflash Erase Error block = %d or 0x%x, Errcode = %x\r\n", cNAND_ADDRESS_tag.Block, cNAND_ADDRESS_tag.Block, ret); 
        }
       
        cNAND_ADDRESS_tag.Block++;

        if(cNAND_ADDRESS_tag.Block == NAND_MAXNUMBER_BLOCK)
        {
			 u32Tick = GetTickCount();
           
            printf("Nandflash Auto Erase End  = %d\r\n", u32Tick); 
            
            break;
        }
        
    }       
    
} 

VOID TestNandflash(VOID)
{
    U16 u16Count;
    U8 szTestTest[30];

    FSMC_NAND_Init();
    
	printf("Nandflash TEST\r\n");

    printf("Please input cmd and data\r\n");
    
    NAND_Reset();
    
    FSMC_NAND_ReadID(&cNand_ID_tag);
    
    printf("Nandflash Maker_ID = %x\r\n", cNand_ID_tag.Maker_ID);
    printf("Nandflash Device_ID = %x\r\n", cNand_ID_tag.Device_ID);
    printf("Nandflash Third_ID = %x\r\n", cNand_ID_tag.Third_ID);
    printf("Nandflash Fourth_ID = %x\r\n", cNand_ID_tag.Fourth_ID);
    printf("Nandflash Fifth_ID = %x\r\n", cNand_ID_tag.Fifth_ID);
	
    while(1)
	{	
        
        if(GetUsartCurrentLength(USART1_TYPE))
        {
            u16Count = GetUsartCurrentLength(USART1_TYPE);
            memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
            ClearUsartCurrentLength(USART1_TYPE);
            if(u16Count == 7)
            {
                if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x02) && (szTestTest[2] == 0xEF))//开始写测试
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleWriteNandflash(); 
                }

                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x01) && (szTestTest[2] == 0xEF))//开始读测试
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleReadNandflash(); 
                }

                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x03) && (szTestTest[2] == 0xEF))//开始擦除测试
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleEraseNandflash();
                    printf("\r\nERASE OK\r\n"); 
                }
                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x04) && (szTestTest[2] == 0xEF))//开始擦除全部测试
                {
                    HandleAutoEraseNandflash();
                    printf("\r\nERASE ALL OK\r\n"); 
                }
                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x05) && (szTestTest[2] == 0xEF))//开始写全部测试
                {
                    HandleAutoWriteNandflash();
                    printf("\r\nWRITE ALL OK\r\n"); 
                }
                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x06) && (szTestTest[2] == 0xEF))//开始读全部测试
                {
                    HandleAutoReadNandflash();
                    printf("\r\nREAD ALL OK\r\n"); 
                }

                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x07) && (szTestTest[2] == 0xEF))//读spare
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleReadSpareNandflash(); 
                }
                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x08) && (szTestTest[2] == 0xEF))//写spare
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleWriteSpareNandflash();
                }
                else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x09) && (szTestTest[2] == 0xEF))//测试坏块（格式化）
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleDetectNandflashBadBlock();
                    printf("\r\nDetect bad block over\r\n"); 
                }

				else if((szTestTest[0] == 0x01) && (szTestTest[1] == 0x0a) && (szTestTest[2] == 0xEF))////测试坏块（new chip）
                {
                    g_u8Data = szTestTest[3];
                    g_u8Page = szTestTest[4];
                    g_u16Block = MAKEWORD(szTestTest[6], szTestTest[5]);
                    
                    HandleCheckNandflashBadBlock();
                }
                else
                {
                    printf("\r\ninput ERROR\r\n");      
                }

            }

            else
            {
                    printf("\r\ninput ERROR\r\n");
            }
        }

	}  

}
