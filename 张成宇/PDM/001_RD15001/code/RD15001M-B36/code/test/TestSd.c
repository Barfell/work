#include "sdio_sdcard.h"
#include "usart.h"
VOID TestSdProc(VOID)
{
    U8 *buf;
    U32 sd_size;
    DelayMs(2000);
    while(SD_Init())
    {
        printf("SD Card Error!\r\n");
        DelayMs(1000);
    }
    buf = (U8 *)mymalloc(SRAMIN, SD_UNIT_SIZE);
	memset(buf, 35, SD_UNIT_SIZE);
	if(buf != NULL)
	{
		SD_WriteDisk(buf, 0, 1);
		if(SD_ReadDisk(buf,0,1)==0)	
		{
			printf("Sending Data...\r\n");
			for(sd_size = 0; sd_size < SD_UNIT_SIZE;sd_size++)
            {
				printf("%d",buf[sd_size]);
            }
            printf("\r\nSD Test ok!");
            while(1)
            {
                printf("SD Test ok!");
                DelayMs(1000);
            }
		}
		
	}
	else
	{		
        printf("malloc error:\r\n");
        while(1);     
	}
    myfree(SRAMIN, buf);
}

//例子：发送的数据是00 00 04 bf
//看UE中的地址比如0x98000，0x98000/0X200 = 4BF
VOID TestSdReadProc(VOID)
{
    U8 *buf;
    U8 szTestTest[5]={0};
    U16 u16Count,u16Sectora,u16Sectorb;
    U32 sd_size, u32Sector;
    DelayMs(2000);
    while(SD_Init())
    {
        printf("SD Card Error!\r\n");
        DelayMs(1000);
    }
    buf = (U8 *)mymalloc(SRAMIN, SD_UNIT_SIZE);
	memset(buf, 35, SD_UNIT_SIZE);
	if(buf != NULL)
	{
        while(1)
        {
            if(GetUsartCurrentLength(USART1_TYPE))
            {
                u16Count = GetUsartCurrentLength(USART1_TYPE);
                ClearUsartCurrentLength(USART1_TYPE);
                memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
                if(u16Count == 4)
                {
                    u16Sectora = MAKEWORD(szTestTest[1], szTestTest[0]);
                    u16Sectorb = MAKEWORD(szTestTest[3], szTestTest[2]);
                    u32Sector = MAKELONG(u16Sectorb, u16Sectora);
                    if(SD_ReadDisk(buf,u32Sector,1)==0)	
                    {
                       // printf("Sending Data...\r\n");
                        for(sd_size = 0; sd_size < SD_UNIT_SIZE;sd_size++)
                        {
                            printf("%x",buf[sd_size]);
                        }
                        //printf("\r\nSD Test ok!");    
                    }
                }
                
            }
        }
		
	}
	else
	{		
        printf("malloc error:\r\n");
        while(1);     
	}
//    myfree(SRAMIN, buf);
}
