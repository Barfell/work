#include "SST25VF0.h" 


#define SST_DATA_UNIT_SIZE			0x100		//256
#define SST_DATA_UNIT_NUMBER		0x1000
#define SST_MAX_SIZE 				0x100000 	//1Mbytes

VOID TestSST25VF0(VOID)
{
	U32 u32Value;
	U32 u32Count, u32Loop;
//	U8 szData[SST_DATA_UNIT_SIZE] = {0};
//	U8 szReadData[SST_DATA_UNIT_SIZE] = {0};
	U8 *szData;
	U8 *szReadData;
	U8 u8Value;
	
	szData = (U8 *)mymalloc(SRAMIN, SST_DATA_UNIT_SIZE);
	
	szReadData = (U8 *)mymalloc(SRAMIN, SST_DATA_UNIT_SIZE);
	
	if((szData == NULL) || (szReadData == NULL))
	{
		EnterException(ERR_OTHER_MALLOC_FAIL);
	}
	
	SST25VF0_Init();
	
	ExternFlash_Init();
	
	ExternFlashChipErase();
	
	u32Value = JedecIDRead();

	printf("Jedec ID = 0X%X\r\n", u32Value);
	
	if(SST25VF080B_JEDEC_ID != u32Value)
	{
		printf("Jedec ID error = 0X%X\r\n", u32Value);
	}
	
	for(u32Loop = 0; u32Loop < SST_DATA_UNIT_SIZE; u32Loop++)
	{
		szData[u32Loop] = u32Loop;
		ExternFlashPageProgram(u32Loop, szData+u32Loop, 1);
	}

	for(u32Loop = 0; u32Loop < SST_DATA_UNIT_SIZE; u32Loop++)
	{
		szReadData[u32Loop] = Read(u32Loop);;
	}
	
	ExternFlashHighSpeedRead(0, szReadData, SST_DATA_UNIT_SIZE);
	
	if(memcmp(szData, szReadData, SST_DATA_UNIT_SIZE) != 0)
	{
		printf("Read error\r\n");
	}
	
	for(u32Count = 0; u32Count < SST_DATA_UNIT_SIZE; u32Count++)
	{
		u8Value = Read(u32Count);
		if(szData[u32Count] != u8Value)
		{
			printf("Read error = 0x%X\r\n", u32Count);
		}
	}
		
////256个字节		
//	for(u32Loop = 0; u32Loop  < SST_MAX_SIZE;)
//	{
//	
//		ExternFlashHighSpeedRead(u32Loop, szData, SST_DATA_UNIT_SIZE);
//		u32Loop = u32Loop + SST_DATA_UNIT_SIZE;
//		for(u32Count = 0; u32Count < SST_DATA_UNIT_SIZE; u32Count++)
//		{
//			if(szData[u32Count] != 0xff)
//			{
//				printf("error position = 0x%X", u32Count + u32Loop);
//			}
//		}
//		
//	}
//////////////////////////////////////////////////////	
////单个字节	
//	for(u32Loop = 0; u32Loop < SST_MAX_SIZE; u32Loop++)
//	{
//		if(Read(u32Loop) != 0xff)
//		{
//			printf("error position = 0x%X", u32Loop);
//		}
//			
//	}
	printf("test ok");
	
	while(1);

	
}


