#include "board.h"

STATIC U8 *g_pData;

#if 0
STATIC VOID DebugMeasure(VOID)
{
    U8 stemp[40]={0x0};
    unsigned long miles;
    unsigned int gauges;
    double mileage_a;    
    calculate_mileage();
    Adc_Read();
   if(mileage_record.mileage_sign=='-')
        mileage_a=0-mileage_record.mileage;
    
    else mileage_a=mileage_record.mileage;
        miles=((unsigned long)(mileage_a *1000));
        
    stemp[0]=mileage_record.mileage_sign;
    stemp[1]=(miles/10000000)+'0' ;
    stemp[2]=(miles%10000000)/1000000+'0' ;
    stemp[3]=(miles%1000000)/100000+'0' ;
    stemp[4]=(miles%100000)/10000+'0' ;
    stemp[5]=(miles%10000)/1000+'0' ;
    stemp[6]='.';

    stemp[7]=(miles%1000)/100+'0' ;
    stemp[8]=(miles%100)/10+'0' ;
    stemp[9]=(miles%10)/1+'0' ;
    stemp[10]='\\';

    //下面的是轨距电压值
    gauges=systemvalue.gauge_DC*1000;
    systemvalue.gauge_DC=0;
    stemp[11]=(gauges/1000)+'0' ;
    stemp[12]='.';
    stemp[13]=(gauges%1000)/100+'0' ;
    stemp[14]=(gauges%100)/10+'0' ;
    stemp[15]=(gauges%10)/1+'0' ;;
    stemp[16]='\r';
    stemp[17]='\n';
    Usart1_DMA_Send(stemp, 18);
      
      //下面的是换算成轨距
//    gauges = systemvalue.gauge_mm;   
//    stemp[11]=(gauges/1000)+'0' ;
//    stemp[12]=(gauges%1000)/100+'0' ;
//    stemp[13]=(gauges%100)/10+'0' ;
//    stemp[14]=(gauges%10)/1+'0' ;
//    stemp[15]='.';
//    gauges = systemvalue.gauge_mm*100; 
//    stemp[16]=(gauges%100)/10+'0' ;
//    stemp[17]=(gauges%10)/1+'0' ;
//    stemp[18]='\r';
//    stemp[19]='\n';

//    Usart1_DMA_Send(stemp, 20); 

}
#endif

STATIC VOID DebugMeasure(VOID)
{

    unsigned long miles;
    unsigned int gauges;
    double mileage_a;    

    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    calculate_mileage();
    Adc_Read();
    if(mileage_record.mileage_sign=='-')
        mileage_a=0-mileage_record.mileage;
    else mileage_a=mileage_record.mileage;
        miles=((unsigned long)(mileage_a *1000));
    
    
        
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

    *(g_pData + 11) = '\\';        
    *(g_pData + 12) = mileage_record.mileage_sign;
    *(g_pData + 13) = (miles/10000000)+'0' ;
    *(g_pData + 14) = (miles%10000000)/1000000+'0' ;
    *(g_pData + 15) = (miles%1000000)/100000+'0' ;
    *(g_pData + 16) = (miles%100000)/10000+'0' ;
    *(g_pData + 17) = (miles%10000)/1000+'0' ;
    *(g_pData + 18) = '.';
    *(g_pData + 19) = (miles%1000)/100+'0' ;
    *(g_pData + 20) = (miles%100)/10+'0' ;
    *(g_pData + 21) = (miles%10)/1+'0' ;
   
    *(g_pData + 22) = '\\';
    //下面的是轨距电压值    
    gauges = systemvalue.gauge_DC;
    gauges=systemvalue.gauge_DC*1000;
    systemvalue.gauge_DC=0;
    *(g_pData + 23) = (gauges/1000)+'0' ;
    *(g_pData + 24) ='.';
    *(g_pData + 25) =(gauges%1000)/100+'0' ;
    *(g_pData + 26) =(gauges%100)/10+'0' ;
    *(g_pData + 27) =(gauges%10)/1+'0' ;;
  
    *(g_pData + 28) = '\r' ;
    *(g_pData + 29) = '\n' ;

    Usart1_DMA_Send(g_pData, 30);

    //下面的是换算成轨距
//    gauges = systemvalue.gauge_mm;   
//    g_pData[23]=(gauges/1000)+'0' ;
//    g_pData[24]=(gauges%1000)/100+'0' ;
//    g_pData[25]=(gauges%100)/10+'0' ;
//    g_pData[26]=(gauges%10)/1+'0' ;
//    g_pData[27]='.';
//    gauges = systemvalue.gauge_mm*100; 
//    g_pData[28]=(gauges%100)/10+'0' ;
//    g_pData[29]=(gauges%10)/1+'0' ;
//    g_pData[30]='\r';
//    g_pData[31]='\n';

//    Usart1_DMA_Send(g_pData, 32); 
    

}
U8 DisplayNum[18] = {0xFE ,0x01 ,0x05 ,0x10 ,0x09 ,0x00 ,0x81,0x82,0x31 ,0x32, 0x33, 0x34, 0x35, 0x36,0x37, 0x1e,0xEF ,0x0D};
VOID DisplayDataNum(U8 type,float num)
{
    U8 i = 0;
    U8 u8check = 0;
    U8 arr[7] = {0};
    sprintf((CHAR *)arr,"%6.2f",num);
    switch (type)
    {
        case 0:
            DisplayNum[3] = 0x10;
            DisplayNum[6] = 0x9b;//里程
            DisplayNum[7] = 0x9c;
        break;
        case 1:
            DisplayNum[3] = 0x11;
            DisplayNum[6] = 0x99;//规矩
            DisplayNum[7] = 0x9a;

        break;
        default:
            break;
    }
	u8check = 0x01 ^ 0x05 ^ DisplayNum[3] ^ 0x09 ^ DisplayNum[6] ^ DisplayNum[7];
    for(i=0;i<7;i++)
    {
        DisplayNum[8+i] = arr[i];
        u8check = u8check ^ arr[i];
    }
    DisplayNum[15] = u8check;
	WriteCommData(DisplayNum, 18);
}

STATIC VOID DebugGaugeMeasure(VOID)
{
    calculate_mileage();
    Adc_Read();

	DisplayDataNum(1, systemvalue.gauge_mm);
}
VOID TestMileageProc(VOID)
{
    
    g_pData = mymalloc(SRAMIN, 35);//5个间隔符，10个时间，17个里程轨距信息
    
    if(g_pData == NULL)
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
	printf("Mileage TEST\r\n");
	
	while(1)
	{	
        DebugMeasure();
        DelayMs(300);
	}

}

VOID TestGaugeProc(VOID)//用来在液晶上显示规矩的数据
{
	BOOL bStart = FALSE;
	U8 u8type;
	U16 u16Count;  
	U8 *pBuf = mymalloc(SRAMIN, 50);
	g_pData = mymalloc(SRAMIN, 35);//5个间隔符，10个时间，17个里程轨距信息
    
    if(g_pData == NULL)
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
	printf("gauge TEST\r\n");
	
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
					bStart = TRUE;
					break;
				case COMM_CMD_STOP:
					bStart = FALSE;
					break;
				default:
					break;
			}
			
		}
		if(bStart == TRUE)
		{	
			DebugGaugeMeasure();
			DelayMs(500);
		}
	}
	
	

}










            
   
