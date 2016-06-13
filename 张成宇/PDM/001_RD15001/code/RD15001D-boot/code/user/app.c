#include "board.h"

#define COMMCMDITEM     4
const U8 szCommCmd[COMMCMDITEM][10] = 
{
    {0xFE ,0x01 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xEF ,0x0D},
    {0xFE ,0x01 ,0x02 ,0x00 ,0x00 ,0x00 ,0x00 ,0x03 ,0xEF ,0x0D},
    {0xFE ,0x01 ,0x03 ,0x00 ,0x00 ,0x00 ,0x00 ,0x02 ,0xEF ,0x0D},
    {0xFE ,0x01 ,0x04 ,0x00 ,0x00 ,0x00 ,0x00 ,0x05 ,0xEF ,0x0D},
    
};
enum
{
    COMM_CMD_START = 0,
    COMM_CMD_STOP,
    COMM_CMD_CLRMILEAGE,
    COMM_CMD_SAVEDATA,
};
typedef struct  _tagSysInfo
{
    U8 u8CmdType;
    
} CSysInfo, *PSysInfo; 

STATIC CSysInfo    cSysInfo = {0};

STATIC BOOL g_bSysRun = TRUE;

STATIC U8 g_u8Cnt = 0;

STATIC BOOL HandleCommCmdProc(U8 *pBuf, U16 u16Cnt)
{
    BOOL bRet = FALSE;
    U8 u8Count;
    for(u8Count = 0; u8Count < COMMCMDITEM; u8Count++)
    {
        if(memcmp(pBuf, szCommCmd + u8Count, 10) == 0)
        {
            bRet = TRUE;
            cSysInfo.u8CmdType = u8Count;  
            break;   
        }
    }
    return bRet;
    
}

EXTERN VOID mileage_init(VOID);

STATIC VOID HandleCommCmdSubProc(VOID)
{
    switch(cSysInfo.u8CmdType)
    {
        case COMM_CMD_START:
            g_bSysRun = TRUE;
            break;
        case COMM_CMD_STOP:
            g_bSysRun = FALSE;
            break;
        case COMM_CMD_CLRMILEAGE:
            mileage_init();
            break;
        case COMM_CMD_SAVEDATA:
            SaveUsbProc(GPSDATA);
            SaveUsbProc(INSDATA);
            SaveUsbProc(OTHERDATA);
            SaveUsbProc(RFIDDATA);
            break;
        default:
            break;
    }
}
STATIC VOID HandleUsart1DataProc(U8 *pBuf, U16 u16cnt)
{
    U8 *pData = (U8 *)malloc(u16cnt + 13);//3个间隔符，10个时间。
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    if(pData != NULL)
    {
        memcpy(pData, pBuf, u16cnt);
        *(pData + u16cnt) = '#';
        *(pData + u16cnt + 1) = (u32Tick100us/1000000000)+'0' ;
        *(pData + u16cnt + 2) = ((u32Tick100us/100000000)%10)+'0' ;
        *(pData + u16cnt + 3) = ((u32Tick100us/10000000)%10)+'0' ;
        *(pData + u16cnt + 4) = ((u32Tick100us/1000000)%10)+'0' ;
        *(pData + u16cnt + 5) = ((u32Tick100us/100000)%10)+'0' ;
        *(pData + u16cnt + 6) = ((u32Tick100us/10000)%10)+'0' ;
        *(pData + u16cnt + 7) = ((u32Tick100us/1000)%10)+'0' ;
        *(pData + u16cnt + 8) = ((u32Tick100us/100)%10)+'0' ;
        *(pData + u16cnt + 9) = ((u32Tick100us/10)%10)+'0' ;
        *(pData + u16cnt + 10) = (u32Tick100us%10)+'0' ;
        *(pData + u16cnt + 11) = '\r' ;
        *(pData + u16cnt + 12) = '\n' ;

/*
        if((g_u16GpsDataCount + u16cnt + 13) > SAVEDATASIZE)
        {
            memcpy(g_szGpsData + g_u16GpsDataCount, pData, SAVEDATASIZE - g_u16GpsDataCount);//满一页数据
            SaveNandflash(GPSDATA);
            memcpy(g_szGpsData, pData + (SAVEDATASIZE - g_u16GpsDataCount), u16cnt + 13
        }
        else
        {
            memcpy(g_szGpsData, pData, u16cnt + 13);
            g_u16GpsDataCount = g_u16GpsDataCount + u16cnt + 13;
        }
        
        if(g_u16GpsDataCount == SAVEDATASIZE)
        {
            SaveNandflash(GPSDATA);
            g_u16GpsDataCount = 0;
        }
        */
        SaveFram(pData, u16cnt + 13, GPSDATA);
        //WriteFile(DEV_COM1, pData, u16cnt + 13, 0);
    }
    
}

STATIC VOID HandleUsart2DataProc(U8 *pBuf, U16 u16cnt)
{
    U8 *pData = (U8 *)malloc(u16cnt + 13);//3个间隔符，10个时间。
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    if(pData != NULL)
    {
        memcpy(pData, pBuf, u16cnt);
        *(pData + u16cnt) = '#';
        *(pData + u16cnt + 1) = (u32Tick100us/1000000000)+'0' ;
        *(pData + u16cnt + 2) = ((u32Tick100us/100000000)%10)+'0' ;
        *(pData + u16cnt + 3) = ((u32Tick100us/10000000)%10)+'0' ;
        *(pData + u16cnt + 4) = ((u32Tick100us/1000000)%10)+'0' ;
        *(pData + u16cnt + 5) = ((u32Tick100us/100000)%10)+'0' ;
        *(pData + u16cnt + 6) = ((u32Tick100us/10000)%10)+'0' ;
        *(pData + u16cnt + 7) = ((u32Tick100us/1000)%10)+'0' ;
        *(pData + u16cnt + 8) = ((u32Tick100us/100)%10)+'0' ;
        *(pData + u16cnt + 9) = ((u32Tick100us/10)%10)+'0' ;
        *(pData + u16cnt + 10) = (u32Tick100us%10)+'0' ;
        *(pData + u16cnt + 11) = '\r' ;
        *(pData + u16cnt + 12) = '\n' ;

/*
        memcpy(g_szInsData, pData, u16cnt + 13);
        g_u16InsDataCount = g_u16InsDataCount + u16cnt + 13;
        if(g_u16InsDataCount == SAVEDATASIZE)
        {
            SaveNandflash(INSDATA);
            g_u16InsDataCount = 0;
        } 
        */
        SaveFram(pData, u16cnt + 13, INSDATA);
        //WriteFile(DEV_COM1, pData, u16cnt + 13, 0);
    }
    
}

STATIC VOID HandleOtherDataProc(VOID)
{
    unsigned long miles;
    unsigned int gauges;
    double mileage_a;  
    U8 *pData = (U8 *)malloc(32);//5个间隔符，10个时间，17个里程轨距信息
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    if(pData != NULL)
    {
        calculate_mileage();
        Adc_Read();
        if(mileage_record.mileage_sign=='-')
            mileage_a=0-mileage_record.mileage;
        else mileage_a=mileage_record.mileage;
            miles=((unsigned long)(mileage_a *1000));
        
        gauges = systemvalue.gauge_mm;     
        
        *(pData) = '#';
        *(pData + 1) = (u32Tick100us/1000000000)+'0' ;
        *(pData + 2) = ((u32Tick100us/100000000)%10)+'0' ;
        *(pData + 3) = ((u32Tick100us/10000000)%10)+'0' ;
        *(pData + 4) = ((u32Tick100us/1000000)%10)+'0' ;
        *(pData + 5) = ((u32Tick100us/100000)%10)+'0' ;
        *(pData + 6) = ((u32Tick100us/10000)%10)+'0' ;
        *(pData + 7) = ((u32Tick100us/1000)%10)+'0' ;
        *(pData + 8) = ((u32Tick100us/100)%10)+'0' ;
        *(pData + 9) = ((u32Tick100us/10)%10)+'0' ;
        *(pData + 10) = (u32Tick100us%10)+'0' ;

        *(pData + 11) = '*';        
        *(pData + 12) = mileage_record.mileage_sign;
        *(pData + 13) = (miles/10000000)+'0' ;
        *(pData + 14) = (miles%10000000)/1000000+'0' ;
        *(pData + 15) = (miles%1000000)/100000+'0' ;
        *(pData + 16) = (miles%100000)/10000+'0' ;
        *(pData + 17) = (miles%10000)/1000+'0' ;
        *(pData + 18) = '.';
        *(pData + 19) = (miles%1000)/100+'0' ;
        *(pData + 20) = (miles%100)/10+'0' ;
        *(pData + 21) = (miles%10)/1+'0' ;
       
        *(pData + 22) = '$';      
        *(pData + 23) = (gauges/1000)+'0' ;
        *(pData + 24) = (gauges%1000)/100+'0' ;
        *(pData + 25) = (gauges%100)/10+'0' ;
        *(pData + 26) = (gauges%10)/1+'0' ;
        *(pData + 27) = '.';
        gauges = systemvalue.gauge_mm*100; 
        *(pData + 28) = (gauges%100)/10+'0' ;
        *(pData + 29) = (gauges%10)/1+'0' ;
      
        *(pData + 30) = '\r' ;
        *(pData + 31) = '\n' ;

        /*
       //
        memcpy(g_szOtherData, pData, u16cnt + 32);
        g_u16OtherDataCount = g_u16OtherDataCount + u16cnt + 32;
        if(g_u16OtherDataCount == SAVEDATASIZE)
        {
            SaveNandflash(OTHERDATA);
            g_u16OtherDataCount = g_u16OtherDataCount - SAVEDATASIZE;
        }
        */
        SaveFram(pData, 32, OTHERDATA);
        //WriteFile(DEV_COM1, pData, u16cnt + 32, 0);
    }
    
}

STATIC VOID HandleUsart3DataProc(U8 *pBuf, U16 u16cnt)
{
    
    unsigned long miles;
    unsigned int gauges;
    double mileage_a;  
    U8 *pData = (U8 *)malloc(u16cnt + 32);//5个间隔符，10个时间，17个里程轨距信息
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    if(pData != NULL)
    {
        calculate_mileage();
        Adc_Read();
        if(mileage_record.mileage_sign=='-')
            mileage_a=0-mileage_record.mileage;
        else mileage_a=mileage_record.mileage;
            miles=((unsigned long)(mileage_a *1000));
        
        gauges = systemvalue.gauge_mm;     
        memcpy(pData, pBuf, u16cnt);
        
        *(pData + u16cnt) = '#';
        *(pData + u16cnt + 1) = (u32Tick100us/1000000000)+'0' ;
        *(pData + u16cnt + 2) = ((u32Tick100us/100000000)%10)+'0' ;
        *(pData + u16cnt + 3) = ((u32Tick100us/10000000)%10)+'0' ;
        *(pData + u16cnt + 4) = ((u32Tick100us/1000000)%10)+'0' ;
        *(pData + u16cnt + 5) = ((u32Tick100us/100000)%10)+'0' ;
        *(pData + u16cnt + 6) = ((u32Tick100us/10000)%10)+'0' ;
        *(pData + u16cnt + 7) = ((u32Tick100us/1000)%10)+'0' ;
        *(pData + u16cnt + 8) = ((u32Tick100us/100)%10)+'0' ;
        *(pData + u16cnt + 9) = ((u32Tick100us/10)%10)+'0' ;
        *(pData + u16cnt + 10) = (u32Tick100us%10)+'0' ;

        *(pData + u16cnt + 11) = '*';        
        *(pData + u16cnt + 12) = mileage_record.mileage_sign;
        *(pData + u16cnt + 13) = (miles/10000000)+'0' ;
        *(pData + u16cnt + 14) = (miles%10000000)/1000000+'0' ;
        *(pData + u16cnt + 15) = (miles%1000000)/100000+'0' ;
        *(pData + u16cnt + 16) = (miles%100000)/10000+'0' ;
        *(pData + u16cnt + 17) = (miles%10000)/1000+'0' ;
        *(pData + u16cnt + 18) = '.';
        *(pData + u16cnt + 19) = (miles%1000)/100+'0' ;
        *(pData + u16cnt + 20) = (miles%100)/10+'0' ;
        *(pData + u16cnt + 21) = (miles%10)/1+'0' ;
       
        *(pData + u16cnt + 22) = '$';      
        *(pData + u16cnt + 23) = (gauges/1000)+'0' ;
        *(pData + u16cnt + 24) = (gauges%1000)/100+'0' ;
        *(pData + u16cnt + 25) = (gauges%100)/10+'0' ;
        *(pData + u16cnt + 26) = (gauges%10)/1+'0' ;
        *(pData + u16cnt + 27) = '.';
        gauges = systemvalue.gauge_mm*100; 
        *(pData + u16cnt + 28) = (gauges%100)/10+'0' ;
        *(pData + u16cnt + 29) = (gauges%10)/1+'0' ;
      
        *(pData + u16cnt + 30) = '\r' ;
        *(pData + u16cnt + 31) = '\n' ;
        
        SaveFram(pData, u16cnt + 32, RFIDDATA);
//        memcpy(g_szRfidData, pData, u16cnt + 13);
//        g_u16RfidDataCount = g_u16RfidDataCount + u16cnt + 13;

        //WriteFile(DEV_COM1, pData, u16cnt + 32, 0);
    }
    
}

//主应用入口
VOID AppMain(VOID)
{
    U16 u16Count,u16Cnt;
    U8 szReceiveBuf[1024];  
    
	while(1)
	{	
                            
        USBH_Process(&USB_OTG_Core, &USB_Host);
	}    
    
}
////////////////////////////////////测试入口开始/////////////////////////////////////////////////
STATIC VOID AnalyzeTestCmd(U8 *pBuf, U16 u16Count)
{
    //1、FRAM
    if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x01) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestFramProc();       
    }
    //2、ADC
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x02) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestAdcProc();
    }
    //3、USB
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x03) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestUsbhost();
    }
    //4、SD
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x04) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
//        TestSdProc();       
    }
    //5、UART
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x05) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestUsart1();
    }
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x05) && (*(pBuf + 3) == 0x02) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestUsart2();
    }
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x05) && (*(pBuf + 3) == 0x03) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestUsart3();
    }
    //6、MILE
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x06) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestMileageProc();       
    }
    //7、NAND
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x07) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestNandflash();        
    }
    //8、a、RFID 测试
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x08) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
//        TestRFID();
    }
    //b、rfid crc计算
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x08) && (*(pBuf + 3) == 0x02) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
//        TestCalcuate();
    }
    //9、LED 
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x09) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        TestLedProc();
    }
    //10、comm
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x0A) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
//        TestCommProc();
    }
    //11、app
    else if((*pBuf == 0x55) && (*(pBuf + 1) == 0xAA) && (*(pBuf + 2) == 0x0b) && (*(pBuf + 3) == 0x01) && (*(pBuf + 4) == 0xAA) && (*(pBuf + 5) == 0x55))
    {
        AppMain();
    }
    else
    {
        printf("select test program error\r\n");
        printf("Please input again\r\n");
        
    }
    
}

VOID HandleMainProc(VOID)
{
	U8 szTestTest[20];
    U16 u16Count;
    printf("Please select test program\r\n");
    while(1)
	{	
        if(GetUsartCurrentLength(USART1_TYPE) != 0)
        {
            u16Count = GetUsartCurrentLength(USART1_TYPE);
            ClearUsartCurrentLength(USART1_TYPE);
            memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
            AnalyzeTestCmd(szTestTest, u16Count);
            
        }			
	} 
    
    
}
////////////////////////////////////测试入口结束/////////////////////////////////////////////////


