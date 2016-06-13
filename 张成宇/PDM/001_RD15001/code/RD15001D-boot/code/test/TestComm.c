#include "board.h"

VOID TestCommProc(VOID)
{
    U8 u8type;
    U16 u16Cnt;
    U8 *pBuf = mymalloc(SRAMIN, 50);
    if(pBuf != NULL)
    {
        CommInit();
        printf("COMM TEST\r\n");
        
        
        while(1)
        {
            u16Cnt = GetCommDataLength();
            if(u16Cnt == 10)
            {
                ReadCommData(pBuf, 10);
                USART1_Send(pBuf, &u16Cnt);
                HandleCommCmdProc(pBuf, &u8type);
                switch(u8type)
                {
                    case COMM_CMD_START:                        
                        Led_On();
                        DisplayRfidNum(1,1);
                        //DisplaySavePercent(RFID_DISPLAY, 7, 0);
                        break;
                    case COMM_CMD_STOP:
                        Led_Off();
                        DisplayRfidNum(1,7);
                        //DisplaySavePercent(INS_DISPLAY, 7, 0);
                        break;
                    case COMM_CMD_CLRMILEAGE:
                        DisplayRfidNum(0,4);
                        //DisplaySavePercent(GPS_DISPLAY, 7, 0);
                        break;
                    case COMM_CMD_SAVEDATA:
                        DisplayRfidNum(0,6);
                        //DisplaySavePercent(MILE_DIPLAY, 7, 0);
                        break;
                    default:
                        break;
                }
                
            }
            

        }
    }

}
