#include "SST25VF064C.h" 
#include "Serial.h" 


#define SST_DATA_UNIT_NUMBER		0x8000
#define SST_MAX_SIZE 				0x800000 	

VOID TestSST25VF0(VOID)
{
	U32 u32Value;
	U32 u32Count, u32Loop;
	U8 szData[SST_DATA_UNIT_SIZE] = {0};
	U8 szReadData[SST_DATA_UNIT_SIZE] = {0};
	U8 u8Value;
	
	SST25VF0_Init();
	
	ExternFlash_Init();

	u32Value = JedecIDRead();

	printf("Jedec ID = 0X%X", u32Value);
	
	if(SST25VF064C_JEDEC_ID != u32Value)
	{
		printf("Jedec ID error = 0X%X", u32Value);
	}
	
	for(u32Loop = 0; u32Loop < SST_DATA_UNIT_SIZE; u32Loop++)
	{
		szData[u32Loop] = u32Loop;
	}
	
	ExternFlashPageProgram(0, szData, SST_DATA_UNIT_SIZE);
	
	
	ExternFlashHighSpeedRead(0, szReadData, SST_DATA_UNIT_SIZE);
	
	if(memcmp(szData, szReadData, SST_DATA_UNIT_SIZE) != 0)
	{
		printf("Read error");
	}
	
	for(u32Count = 0; u32Count < SST_DATA_UNIT_SIZE; u32Count++)
	{
		u8Value = Read(u32Count);
		if(szData[u32Count] != u8Value)
		{
			printf("Read error = 0x%X", u32Count);
		}
	}
		
////256���ֽ�		
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
////�����ֽ�	
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

VOID TestSST25VF0_Storage(VOID)
{
	

	U32 u32Value;

	U32 u32WriteOffset = 0, u32ReadOffset = 0;
	U16 u16Length;
	U8 szData[1100];

	
	
	SST25VF0_Init();
	
	ExternFlash_Init();

	u32Value = JedecIDRead();

	printf("Jedec ID = 0X%X", u32Value);
	
	if(SST25VF064C_JEDEC_ID != u32Value)
	{
		printf("Jedec ID error = 0X%X", u32Value);
	}
	
	while(1)
	{
		if(GetQueueLength(pUart1QueueInfo))
		{
			if((GetTickCount() - GetUartReceiveTime(USART1)) > 20)
			{
				ReadUsartData(USART1, szData, &u16Length);
				if(u16Length == 3)
				{
					if((szData[0] == 0xfe) && (szData[1] == 0x55) && (szData[2] == 0xef))
					{
						ExternFlashChipErase();
						printf("Erase over");
					}
					else if((szData[0] == 0xfe) && (szData[1] == 0xaa) && (szData[2] == 0xef))
					{
						do
						{
							ExternFlashHighSpeedRead(u32ReadOffset, szData, SST_DATA_UNIT_SIZE);
							u32ReadOffset = u32ReadOffset + SST_DATA_UNIT_SIZE;
							UsartSend(USART1, szData, SST_DATA_UNIT_SIZE);
							
						}while(u32ReadOffset < 0x10000);
						//while(u32ReadOffset < u32WriteOffset);
						 
						
					}
					
				}
				else if(u16Length == SST_DATA_UNIT_SIZE)
				{
					ExternFlashPageProgram(u32WriteOffset, szData, SST_DATA_UNIT_SIZE);
					u32WriteOffset = u32WriteOffset + SST_DATA_UNIT_SIZE;
				}
				
			}
		}
		
	}
	
	
}
