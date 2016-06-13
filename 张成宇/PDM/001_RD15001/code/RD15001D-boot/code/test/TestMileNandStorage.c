#include "board.h"

#define OTHER_FRAM_ECC_ADDRESS_START        0X1B800             //��FRAM110K��λ�ÿ�ʼ���� ���е�ĩ��128��ſ��Դ��36M������
#define OTHER_FRAM_ECC_ADDRESS_END              0x1FFFF             //����̹�����������30*20 = 600�ֽ�/�룬һСʱ��2M�����ݣ���˿��Թ���18��Сʱ

STATIC U32 g_u32OtherOffset = 0;//��̹��Ecc�洢�õ�ƫ�Ƽ���

VOID TestOtherNandStorage(VOID)//��̹����nand+fram
{
    U8 u8Ret;
        
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);
   
    U8 u8type, u8Retry;
    
    
    
    U16 u16Count;
        
    U32 u32OtherUsbAddress = 0;
    U32 EccCodeSub = 0;
    U32 EccCode = 0;
    
    U32 u32Temp, u32TempSub;
	U8 u8Temp, u8TempSub;
    
    NAND_ADDRESS Other_nand_address = {0};
    NAND_ADDRESS Other_nand_addressSub = {0};

    printf("Other nand storage TEST!\r\n");
   
    if(pBuf == NULL)
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
     
    pQueueOtherInfo->Front = 0;
    pQueueOtherInfo->Rear = 0;
    pQueueOtherInfo->WriteCount = 0;
    pQueueOtherInfo->ReadCount = 0;
    pQueueOtherInfo->AddCount = 0;
    
    g_bSave = FALSE;//Ĭ�ϲ���ʼ����
    g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
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
                    
                    printf("\r\nNand��ʽ��\r\n");
                    NandBlockEraseInit();
                    printf("\r\nNand�洢����\r\n");
                    SetOtherWorkState(TRUE);//ʹ����̹��50ms���  
                    break;
                case COMM_CMD_STOP:
                    
                    SetOtherWorkState(FALSE);//������̹��50ms���  
                    
                    break;
                case COMM_CMD_CLRMILEAGE:
                    mileage_init();         //����������
                    break;
                case COMM_CMD_SAVEDATA:
                    SetOtherWorkState(FALSE);//������̹��50ms���
                    g_bSave = TRUE;
                    
                    break;
                default:
                    break;
            }
            
        }
        if(g_bSave == TRUE)
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
        }
        if(GetQueueLength(pQueueOtherInfo) > QUEUEUNIT)
        {            
            GetQueue(pBuf, pOtherData, pQueueOtherInfo, QUEUEUNIT);
            
            DeleteQueue(pQueueOtherInfo);
            
            AdjustBadBlock(&Other_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Other_nand_address, &EccCode);
            
            FramWriteInduce(g_u32OtherOffset, 4, (U8 *)(&EccCode));
            
            g_u32OtherOffset = g_u32OtherOffset + 4;
            
            if(g_u32OtherOffset == OTHER_FRAM_ECC_ADDRESS_END)//��128K������
            {
                EnterException(ERR_OTHER_SPACE_FULL);
            }
            
            Other_nand_address.Page ++;
        
            if(Other_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Other_nand_address.Page = 0;
                Other_nand_address.Block++;
                if(Other_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

                        printf("\r\n��Nand������������\r\n");
                        while(1);

                }
            } 
        }
        if(bUsbPlugin == TRUE)
        {
            printf("OTHER Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:OTHER.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
                
                while((Other_nand_addressSub.Page < Other_nand_address.Page) || (Other_nand_addressSub.Block < Other_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Other_nand_addressSub);
            
RETRY_OTHER_READ:        
                    FramReadInduce(g_u32OtherOffset, 4, (U8 *)(&EccCode));
                    
                    g_u32OtherOffset = g_u32OtherOffset + 4;
                    
                    
                    FSMC_NAND_ReadSmallPage(pBuf, Other_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            u8Retry++;
                            goto RETRY_OTHER_READ;
                        }
                        else
                        {
                        // SetNewBadBlock(nand_addressSub); 
                        }
                                                          
                    }
                    Other_nand_addressSub.Page ++;
                
                    if(Other_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Other_nand_addressSub.Page = 0;
                        Other_nand_addressSub.Block++;
                        if(Other_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
                        {
                                printf("\r\n��Nand������������\r\n");
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
                        DisplaySavePercent(MILE_DIPLAY, u8Temp, u8TempSub);
                        
                    
                }
                                             
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
                
                DisplaySaveEnd();
                
                while(1);
            }
             
        }
            
    }
          
}
