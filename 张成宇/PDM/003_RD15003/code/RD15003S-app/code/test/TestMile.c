#include "mile.h"
#include "serial.h"

STATIC U8 *g_pData;
EXTERN VOID MileRunProc(VOID);

U16 g_u16TimeFrequency = 50;

STATIC VOID DebugMeasure(VOID)
{

    U32 miles;
    float mileage_a;    

    U32 u32Tick;
//	U16 u16Value;
//	u16Value = (GPIO_ReadInputData(GPIOA) & 0x000c);//PA6,PA7
//	u16Value = (GPIO_ReadInputData(GPIOA) & 0x00c0);//PA6,PA7
//	u16Value = (GPIO_ReadInputData(GPIOB) & 0x00c0);//PB6,PB7
    u32Tick = GetTickCount();
    *(g_pData) = '#';
    *(g_pData + 1) = (u32Tick/1000000000)+'0' ;
    *(g_pData + 2) = ((u32Tick/100000000)%10)+'0' ;
    *(g_pData + 3) = ((u32Tick/10000000)%10)+'0' ;
    *(g_pData + 4) = ((u32Tick/1000000)%10)+'0' ;
    *(g_pData + 5) = ((u32Tick/100000)%10)+'0' ;
    *(g_pData + 6) = ((u32Tick/10000)%10)+'0' ;
    *(g_pData + 7) = ((u32Tick/1000)%10)+'0' ;
    *(g_pData + 8) = ((u32Tick/100)%10)+'0' ;
    *(g_pData + 9) = ((u32Tick/10)%10)+'0' ;
    *(g_pData + 10) = (u32Tick%10)+'0' ;
	
	CalculateMile();
    if(cMileARecordInfo.MileSign=='-')
        mileage_a=0-cMileARecordInfo.mileage;
    else mileage_a=cMileARecordInfo.mileage;
        miles=((U32)(mileage_a *1000)); 

    *(g_pData + 11) = '\\';        
    *(g_pData + 12) = cMileARecordInfo.MileSign;
    *(g_pData + 13) = (miles/10000000)+'0' ;
    *(g_pData + 14) = (miles%10000000)/1000000+'0' ;
    *(g_pData + 15) = (miles%1000000)/100000+'0' ;
    *(g_pData + 16) = (miles%100000)/10000+'0' ;
    *(g_pData + 17) = (miles%10000)/1000+'0' ;
    *(g_pData + 18) = '.';
    *(g_pData + 19) = (miles%1000)/100+'0' ;
    *(g_pData + 20) = (miles%100)/10+'0' ;
    *(g_pData + 21) = (miles%10)/1+'0' ;
//	*(g_pData + 22) = '\r' ;
//    *(g_pData + 23) = '\n' ;	
//	Usart1_DMA_Send(g_pData, 24); 
	
	if(cMileBRecordInfo.MileSign=='-')
        mileage_a=0-cMileBRecordInfo.mileage;
    else mileage_a=cMileBRecordInfo.mileage;
        miles=((U32)(mileage_a *1000));
	
	*(g_pData + 22) = '\\';        
    *(g_pData + 23) = cMileBRecordInfo.MileSign;
    *(g_pData + 24) = (miles/10000000)+'0' ;
    *(g_pData + 25) = (miles%10000000)/1000000+'0' ;
    *(g_pData + 26) = (miles%1000000)/100000+'0' ;
    *(g_pData + 27) = (miles%100000)/10000+'0' ;
    *(g_pData + 28) = (miles%10000)/1000+'0' ;
    *(g_pData + 29) = '.';
    *(g_pData + 30) = (miles%1000)/100+'0' ;
    *(g_pData + 31) = (miles%100)/10+'0' ;
    *(g_pData + 32) = (miles%10)/1+'0' ;
	
	if(cMileCRecordInfo.MileSign=='-')
        mileage_a=0-cMileCRecordInfo.mileage;
    else mileage_a=cMileCRecordInfo.mileage;
        miles=((U32)(mileage_a *1000));
	
	*(g_pData + 33) = '\\';        
    *(g_pData + 34) = cMileCRecordInfo.MileSign;
    *(g_pData + 35) = (miles/10000000)+'0' ;
    *(g_pData + 36) = (miles%10000000)/1000000+'0' ;
    *(g_pData + 37) = (miles%1000000)/100000+'0' ;
    *(g_pData + 38) = (miles%100000)/10000+'0' ;
    *(g_pData + 39) = (miles%10000)/1000+'0' ;
    *(g_pData + 40) = '.';
    *(g_pData + 41) = (miles%1000)/100+'0' ;
    *(g_pData + 42) = (miles%100)/10+'0' ;
    *(g_pData + 43) = (miles%10)/1+'0' ;

    *(g_pData + 44) = '\r' ;
    *(g_pData + 45) = '\n' ;	
	Usart1_DMA_Send(g_pData, 46); 
	 
}

VOID HandleUartData(U8 *pBuf, U16 u16Length)
{
	if(u16Length == 6)
	{
		if((pBuf[0] == 0xfe) && (pBuf[5] == 0xef))//A
		{
			cMileASwitchInfo.MileUnitNumber = MAKELONG(MAKEWORD(pBuf[1], pBuf[2]), MAKEWORD(pBuf[3], pBuf[4]));
		}
		else if((pBuf[0] == 0xfd) && (pBuf[5] == 0xdf))//B
		{
			cMileBSwitchInfo.MileUnitNumber = MAKELONG(MAKEWORD(pBuf[1], pBuf[2]), MAKEWORD(pBuf[3], pBuf[4]));
		}
		else if((pBuf[0] == 0xfc) && (pBuf[5] == 0xcf))//c
		{
			cMileCSwitchInfo.MileUnitNumber = MAKELONG(MAKEWORD(pBuf[1], pBuf[2]), MAKEWORD(pBuf[3], pBuf[4]));
		}
		else if((pBuf[0] == 0xfb) && (pBuf[5] == 0xbf))//time internal
		{
			g_u16TimeFrequency =  MAKELONG(MAKEWORD(pBuf[1], pBuf[2]), MAKEWORD(pBuf[3], pBuf[4]));
		}
	}
		
}

VOID TestMileageProc(VOID)
{
	U32 u32Tick, u32LastTick;
	S32 s32Count;
	U8 szData[50];
	U16 u16Length;
    
    g_pData = malloc(35);//5个间隔符，10个时间，17个里程轨距信息
    
    if(g_pData == NULL)
    {
        EnterException(ERR_MALLOC_FAIL);
    }
	printf("Mileage TEST\r\n");
	
	while(1)
	{	
		MileRunProc();
		u32Tick = GetTickCount();
		if((u32Tick - u32LastTick) >= g_u16TimeFrequency)
		{
			u32LastTick = u32Tick;
			DebugMeasure();
		}
		
		if(GetQueueLength(pUart1QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);
			if(s32Count > 10)
			{
				ReadUsartData(USART1, szData, &u16Length);
				
				HandleUartData(szData, u16Length);
			}
		}
			
	}

}

BOOL g_bMileTrigger = FALSE;

STATIC VOID DebugMeasureEx(VOID)
{

	U16	u16Value;
//    U32 u32Tick;
//    u32Tick = GetTickCount();
	u16Value = GPIO_ReadInputData(GPIOA) & 0x00c0;
//    *(g_pData) = '#';
//    *(g_pData + 1) = (u32Tick/1000000000)+'0' ;
//    *(g_pData + 2) = ((u32Tick/100000000)%10)+'0' ;
//    *(g_pData + 3) = ((u32Tick/10000000)%10)+'0' ;
//    *(g_pData + 4) = ((u32Tick/1000000)%10)+'0' ;
//    *(g_pData + 5) = ((u32Tick/100000)%10)+'0' ;
//    *(g_pData + 6) = ((u32Tick/10000)%10)+'0' ;
//    *(g_pData + 7) = ((u32Tick/1000)%10)+'0' ;
//    *(g_pData + 8) = ((u32Tick/100)%10)+'0' ;
//    *(g_pData + 9) = ((u32Tick/10)%10)+'0' ;
//    *(g_pData + 10) = (u32Tick%10)+'0' ;
//    UsartSend(USART1, g_pData, 11);  
	printf("0x%x\r\n", u16Value);

}



VOID TestMileageProcEx(VOID)
{
    
    g_pData = malloc(35);//5个间隔符，10个时间，17个里程轨距信息
    
    if(g_pData == NULL)
    {
        EnterException(ERR_MALLOC_FAIL);
    }
	printf("Mileage TEST\r\n");
	
	while(1)
	{
		if(g_bMileTrigger == TRUE)
		{
			DebugMeasureEx();
			g_bMileTrigger = FALSE;
		}
        
	}

}







            
   
