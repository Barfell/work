#include "board.h"
#include "stm32f4xx.h"

//下发进入boot命令
#define SB_FORCE_BOOT_CMD           0x00
// Commands to Bootloader
#define SB_WRITE_CMD                0x01    //写数据到Flash的命令
#define SB_READ_CMD                 0x02    //写完bin文件后，从头开始从flash中回读回来
#define SB_ENABLE_CMD               0x03    //写入CRC值
#define SB_HANDSHAKE_CMD            0x04
#define SB_HANDSHAKE_Ex_CMD         0x05



//Start byte
#define SB_SOF                      0xFE

// Bootloader Serial Interface Subsystem
#define SB_RPC_SYS_BOOT             0x4D

// Status codes
#define SB_SUCCESS                  0
#define SB_FAILURE                  1
#define SB_INVALID_FCS              2
#define SB_INVALID_FILE             3
#define SB_FILESYSTEM_ERROR         4
#define SB_ALREADY_STARTED          5
#define SB_NO_RESPOSNE              6
#define SB_VALIDATE_FAILED          7
#define SB_CANCELED                 8  

enum
{
	SB_NULL = 0,
    SB_FORCE_BOOT,
    SB_WRITE,
    SB_READ,
    SB_ENABLE,
    SB_HANDSHAKE,
    SB_HANDSHAKE_Ex,
};

STATIC U32 g_u32Offset = 0;

//计算数据的校验和
STATIC U8 CalcCheckSum(U8* pSrcData, U16 wDataLen)
{
    U8 bCheckSum;
    int i;
    
    if(pSrcData == NULL)
        return 0;
    
    bCheckSum = pSrcData[0];
    if(wDataLen == 0xFFFF)
       return 0;
    for(i = 1; i <= wDataLen - 1; i++)
    {
        bCheckSum ^= pSrcData[i]; 
    }
    return bCheckSum;    
}

STATIC U8 ParseCmd(U8 *pBuf, U16 u16Cnt)
{
    U8 u8Type = SB_NULL;
    U8 u8Value;
    U8 u8Length;
    
	u8Length = pBuf[1];
	if((pBuf[0] == SB_SOF) && (pBuf[2] == SB_RPC_SYS_BOOT))
	{
		u8Value = CalcCheckSum(pBuf + 1, 3 + u8Length);
		if(u8Value == pBuf[4 + u8Length])//校验成功
		{
			switch(pBuf[3])
			{
				case SB_FORCE_BOOT_CMD:
					u8Type = SB_FORCE_BOOT;
					break;
				case SB_ENABLE_CMD:
					u8Type = SB_ENABLE;
					break;
				case SB_HANDSHAKE_CMD:
					u8Type = SB_HANDSHAKE;
					break;
				case SB_HANDSHAKE_Ex_CMD:
					u8Type = SB_HANDSHAKE_Ex;
				default:
					break;
			}
		}
		else if(pBuf[1] == 0xff)//这里特殊处理来兼容上位机软件
		{
			switch(pBuf[3])
			{
				case SB_WRITE_CMD:
					u8Type = SB_WRITE;
					break;
				case SB_READ_CMD:
					u8Type = SB_READ;
					break;
			}
		}
	}
    
    return u8Type;
}

STATIC VOID Response(U8 *pBuf)
{
	U16 u16Cnt;
    pBuf[1] = 0x01;
    pBuf[3] = pBuf[3] | 0x80;
    pBuf[4] = SB_SUCCESS;
    pBuf[5] = CalcCheckSum(pBuf + 1, 4);
	u16Cnt = 6;
	USART2_Send(pBuf, &u16Cnt);
}
STATIC VOID EnterBootProc(VOID)
{
    NVIC_SystemReset();
}

STATIC VOID EnterWriteProc(U8 *pBuf, U16 u16Count)
{
//    printf("开始更新固件...\r\n");	
//	if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
//	{	 
		iap_write_appbin(FLASH_APP1_ADDR + g_u32Offset, pBuf, u16Count);//更新FLASH代码   
		g_u32Offset = g_u32Offset + 2048;
//		printf("固件更新完成!\r\n");	
//	}else 
//	{   
//		printf("非FLASH应用程序!\r\n");
//	}
}
STATIC VOID EnterReadProc(VOID)
{
    
}

void ReadyToJump(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;  
    NVIC_Init(&NVIC_InitStructure);  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //通道设置为串口中断    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure);   
	
	 
    //DMA发送中断设置  
	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,DISABLE);  
	DMA_Cmd(DMA1_Stream5,DISABLE);  
	
	
	
	  //采用DMA方式发送  
    USART_DMACmd(USART2,USART_DMAReq_Tx,DISABLE);  
    //采用DMA方式接收  
    USART_DMACmd(USART2,USART_DMAReq_Rx,DISABLE);  
	
	USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_IDLE,DISABLE);    
	
	USART_Cmd(USART2, DISABLE);  
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, DISABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, DISABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, DISABLE);  
	
}
STATIC VOID EnterAppProc(VOID)
{

	uart1_deinit();	
	ReadyToJump();
	
	if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
	{	 
		iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
	}
	else //非FLASH应用程序,无法执行
	{
 
	}		
}



VOID TestBoot(VOID)
{
	U32 u32TickCount;
	U16 u16Count;
    U8 szTestTest[30];
    U8 u8Type;
	
	u32TickCount = GetSecondOfWeek();
	
	while(1)
    {
        if(GetUsartCurrentLength(USART2_TYPE) != 0)
        { 
			u16Count = GetUsartCurrentLength(USART2_TYPE);
            memcpy(szTestTest, g_pUsart2_rx_buf, u16Count);
            ClearUsartCurrentLength(USART2_TYPE);
            u8Type = ParseCmd(szTestTest, u16Count);
			if(u8Type != SB_NULL)
			{
				u32TickCount = GetSecondOfWeek();//重新计算超时时间
				switch(u8Type)
				{
					case SB_FORCE_BOOT:
						Response(szTestTest);
						EnterBootProc();
						break;
					case SB_WRITE:
						EnterWriteProc(szTestTest + 4, u16Count - 7);
						Response(szTestTest);
						break;
					case SB_READ:
						EnterReadProc();
						Response(szTestTest);
						break;
					case SB_ENABLE:
						Response(szTestTest);
						EnterAppProc();					
						break;
					case SB_HANDSHAKE:
						Response(szTestTest);
						g_u32Offset = 0;
						break;
					case SB_HANDSHAKE_Ex:
						Response(szTestTest);
						break;
					default:
						break;
				}
			}
        }
		
		if((GetSecondOfWeek() - u32TickCount) > 3)
		{
			EnterAppProc();
			u32TickCount = GetSecondOfWeek();
		}
        
    }
}

