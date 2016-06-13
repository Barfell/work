#include "board.h"


#define INS_FRAM_ECC_ADDRESS_START          0X0                 //��FRAM0��λ�ÿ�ʼ���� ���е�ĩ��80k��ſ��Դ��160M������
#define INS_FRAM_ECC_ADDRESS_END                0x13FFF             //��INS��������8K�ֽ�/�룬һСʱ��28M�����ݣ���˿��Թ���5��Сʱ

#define OTHER_FRAM_ECC_ADDRESS_START        0X1B800             //��FRAM110K��λ�ÿ�ʼ���� ���е�ĩ��128��ſ��Դ��36M������
#define OTHER_FRAM_ECC_ADDRESS_END              0x1FFFF             //����̹�����������30*20 = 600�ֽ�/�룬һСʱ��2M�����ݣ���˿��Թ���18��Сʱ

#define INS_NAND_BLOCK_START                0X0
#define INS_NAND_BLOCK_END                  0X3FF               //��1024�鴦������Ҳ����˵����1G�Ŀռ�洢

#define OTHER_NAND_BLOCK_START                  0X800
#define OTHER_NAND_BLOCK_END                    0XBFF               //��3072�鴦������Ҳ����˵����1G�Ŀռ�洢

STATIC U32 g_u32InsOffset = 0;//INS����Ecc�洢�õ�ƫ�Ƽ���

STATIC U32 g_u32OtherOffset = 0;//��̹��Ecc�洢�õ�ƫ�Ƽ���

VOID TestInsOtherNandStorage(VOID)//INS+��̹����nand+fram
{
    U8 u8Ret;
        
    U8 *pBuf = mymalloc(SRAMIN, QUEUEUNIT);

    U8 *pReadBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    U16 u16Count;
    
    U8 u8type, u8Retry;
    
   
    
    U32 u32OtherUsbAddress = 0;
    U32 u32InsUsbAddress = 0;
    U32 EccCodeSub = 0;
    U32 EccCode = 0;
    
    NAND_ADDRESS Ins_nand_address ={0}, Other_nand_address = {0};
    NAND_ADDRESS Ins_nand_addressSub = {0}, Other_nand_addressSub = {0};

    printf("Ins + Other nand storage TEST!\r\n");
   
    if((pBuf == NULL) || (pReadBuf == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
    
    
    
    pQueueUsart1Info->Front = 0;
    pQueueUsart1Info->Rear = 0;
    pQueueUsart1Info->WriteCount = 0;
    pQueueUsart1Info->ReadCount = 0;
    pQueueUsart1Info->AddCount = 0;
     
    pQueueOtherInfo->Front = 0;
    pQueueOtherInfo->Rear = 0;
    pQueueOtherInfo->WriteCount = 0;
    pQueueOtherInfo->ReadCount = 0;
    pQueueOtherInfo->AddCount = 0;
    
    g_bSave = FALSE;//Ĭ�ϲ���ʼ����
    g_u32InsOffset = INS_FRAM_ECC_ADDRESS_START;
    Ins_nand_address.Block = INS_NAND_BLOCK_START;
    g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
    Other_nand_address.Block = OTHER_NAND_BLOCK_START;
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
                    TIMER_Init(50-1,8400-1);//TIMER_Init(50-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����50��Ϊ5ms 
                
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
        if(GetQueueLength(pQueueUsart1Info) > QUEUEUNIT)
        {            
            GetQueue(pBuf, pUsart1Data, pQueueUsart1Info, QUEUEUNIT);
            
            DeleteQueue(pQueueUsart1Info);
            
            AdjustBadBlock(&Ins_nand_address);

            FSMC_NAND_WriteSmallPage(pBuf, Ins_nand_address, &EccCode);
            
            FramWriteInduce(g_u32InsOffset, 4, (U8 *)(&EccCode));
            
            g_u32InsOffset = g_u32InsOffset + 4;
            
            if(g_u32InsOffset == INS_FRAM_ECC_ADDRESS_END)
            {
                EnterException(ERR_INS_SPACE_FULL);
            }
            
            Ins_nand_address.Page ++;
        
            if(Ins_nand_address.Page == NAND_PAGENUMBER_PERBLOCK)
            {
                Ins_nand_address.Page = 0;
                Ins_nand_address.Block++;
                if(Ins_nand_address.Block == NAND_MAXNUMBER_BLOCK)
                {

                        printf("\r\n��Nand������������\r\n");
                        while(1);

                }
            } 
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
             printf("INS Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:INS.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                g_u32InsOffset = INS_FRAM_ECC_ADDRESS_START;
                Ins_nand_addressSub.Block = INS_NAND_BLOCK_START;
                while((Ins_nand_addressSub.Page < Ins_nand_address.Page) || (Ins_nand_addressSub.Block < Ins_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Ins_nand_addressSub);
            
       
                    FramReadInduce(g_u32InsOffset, 4, (U8 *)(&EccCode));
                    
                    g_u32InsOffset = g_u32InsOffset + 4;
                    
                    
RETRY_INS_READ: 
                    FSMC_NAND_ReadSmallPage(pBuf, Ins_nand_addressSub, &EccCodeSub);
                        
                    if(ECCCheck(EccCode, EccCodeSub, pBuf) == 3)
                    {
                        if(u8Retry < 1)
                        {
                            u8Retry++;
                            goto RETRY_INS_READ;
                        }
                        else
                        {
                        // SetNewBadBlock(nand_addressSub); 
                        }
                                                          
                    }
                    Ins_nand_addressSub.Page ++;
                
                    if(Ins_nand_addressSub.Page == NAND_PAGENUMBER_PERBLOCK)
                    {
                        Ins_nand_addressSub.Page = 0;
                        Ins_nand_addressSub.Block++;
                        if(Ins_nand_addressSub.Block == NAND_MAXNUMBER_BLOCK)
                        {
                                printf("\r\n���ڴ�Nand������������\r\n");
                                while(1);
                            
                        }
                    }
                    
                    u8Ret = f_write(file, pBuf, QUEUEUNIT, &bw);
                    
                    if(u8Ret != 0)
                    {
                        EnterException(ERR_UPAN_WRITE_FAIL);
                    } 
                    
                    u32InsUsbAddress = u32InsUsbAddress + QUEUEUNIT;

INS_SAVE:       u8Ret = f_lseek(file, u32InsUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto INS_SAVE;
                    } 
                        
                    
                }
                                             
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }

 
            }
//////////////////////////////////////////////            
            printf("OTHER Save Start \r\n");
            
            u8Ret = f_open(file,(const TCHAR*)"1:OTHER.txt",0x23);
                    
            if(u8Ret != 0)
            {
                EnterException(ERR_UPAN_OPEN_FAIL);
            }
            else
            {
                g_u32OtherOffset = OTHER_FRAM_ECC_ADDRESS_START;
                Other_nand_addressSub.Block = OTHER_NAND_BLOCK_START;
                
                while((Other_nand_addressSub.Page < Other_nand_address.Page) || (Other_nand_addressSub.Block < Other_nand_address.Block))
                {
                    u8Retry = 0;
                                
                    AdjustBadBlock(&Other_nand_addressSub);
            
       
                    FramReadInduce(g_u32OtherOffset, 4, (U8 *)(&EccCode));
                    
                    g_u32OtherOffset = g_u32OtherOffset + 4;
                    
                    
RETRY_OTHER_READ: 
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

OTHER_SAVE:       u8Ret = f_lseek(file, u32OtherUsbAddress);
                    
                    if(u8Ret != 0)
                    {
                        goto OTHER_SAVE;
                    } 
                        
                    
                }
                                             
                u8Ret = f_close(file);

                if(u8Ret != 0)
                {
                    EnterException(ERR_UPAN_CLOSE_FAIL);
                }
            }
 //////////////////////////////////////// 
            printf("\r\nȫ���������\r\n");
            while(1);
        }
    
        if(g_bSave == TRUE)
        {
            USBH_Process(&USB_OTG_Core, &USB_Host);
        }
        
    }
          
}
