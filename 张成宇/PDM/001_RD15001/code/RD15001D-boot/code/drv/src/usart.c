#include "usart.h"	




STATIC U8 *g_pUsart1_tx_buf;    //发送用的缓冲   
STATIC U8 *g_pUsart2_tx_buf;    //发送用的缓冲
STATIC U8 *g_pUsart3_tx_buf;    //发送用的缓冲  

CUsartInfo g_cUsart1Info, g_cUsart2Info, g_cUsart3Info;


U8 *g_pUsart1_rx_buf; //接收用的缓冲
U8 *g_pUsart2_rx_buf; //接收用的缓冲
U8 *g_pUsart3_rx_buf; //接收用的缓冲

__align(4) U8 *pUsart1Data;    //处理用的环形缓冲      大小由MAXQUEUESIZE来决定
__align(4) U8 *pUsart2Data;    //处理用的环形缓冲      大小由MAXQUEUESIZE来决定
__align(4) U8 *pUsart3Data;    //处理用的环形缓冲      大小由MAXQUEUESIZE来决定
     
__align(4) U8 *g_pUsart1BackData;    //备份用的环形缓冲      大小由MAXQUEUESIZE来决定
__align(4) U8 *g_pUsart2BackData;    //备份用的环形缓冲      大小由MAXQUEUESIZE来决定
__align(4) U8 *g_pUsart3BackData;    //备份用的环形缓冲      大小由MAXQUEUESIZE来决定

U16 g_Usart1BackDataCount = 0;      
U16 g_Usart2BackDataCount = 0;    
U16 g_Usart3BackDataCount = 0;


PQueueInfo pQueueUsart1Info, pQueueUsart2Info, pQueueUsart3Info;

STATIC VOID ReceiveUsartData(U8 type)
{
    U16 u16BackDataCount, u16RxDataCount;
    U8 *pBufDest, *pBufSrc, *pBufRoot;
    PQueueInfo pQueueInfo;
    switch(type)
    {
        case USART1_TYPE:
            u16BackDataCount = g_Usart1BackDataCount;
            u16RxDataCount = g_cUsart1Info.UsartRxCount;
            pBufDest = pUsart1Data;
            pBufSrc = g_pUsart1BackData;
            pBufRoot = g_pUsart1_rx_buf;
            pQueueInfo = pQueueUsart1Info;
            break;
        case USART2_TYPE:
            u16BackDataCount = g_Usart2BackDataCount;
            u16RxDataCount = g_cUsart2Info.UsartRxCount;
            pBufDest = pUsart2Data;
            pBufSrc = g_pUsart2BackData;
            pBufRoot = g_pUsart2_rx_buf;
            pQueueInfo = pQueueUsart2Info;
            break;
        case USART3_TYPE:
            u16BackDataCount = g_Usart3BackDataCount;
            u16RxDataCount = g_cUsart3Info.UsartRxCount;
            pBufDest = pUsart3Data;
            pBufSrc = g_pUsart3BackData;
            pBufRoot = g_pUsart3_rx_buf;
            pQueueInfo = pQueueUsart3Info;
            break;
        default:
            break;
        
    }
    
  
    
    if(u16BackDataCount != 0)
    {
        if(((pQueueInfo->Rear + u16BackDataCount) % MAXQUEUESIZE >= pQueueInfo->Front) && ((pQueueInfo->Rear + u16BackDataCount) > MAXQUEUESIZE))
        {
            
        }
        else
        {
            AddQueue(pBufDest, pBufSrc, pQueueInfo, u16BackDataCount, u16BackDataCount);
            u16BackDataCount = 0;
        }
    }
    
    if(AddQueue(pBufDest, pBufRoot, pQueueInfo, u16RxDataCount, u16RxDataCount) == FALSE)
    {
        memcpy(pBufSrc + u16BackDataCount, pBufRoot, u16RxDataCount);
        u16BackDataCount = u16BackDataCount + u16RxDataCount;
    }
    
        
}

VOID ClearUsartCurrentLength(U8 type)
{
    switch(type)
    {
        case USART1_TYPE:
            g_cUsart1Info.UsartRxCount = 0;
            break;
        case USART2_TYPE:
            g_cUsart2Info.UsartRxCount = 0;
            break;
        case USART3_TYPE:
            g_cUsart3Info.UsartRxCount = 0;
            break;
        default:
            break;
        
    }
    
}

U16 GetUsartCurrentLength(U8 type)
{
    U16 u16Ret;
    switch(type)
    {
        case USART1_TYPE:
            u16Ret = g_cUsart1Info.UsartRxCount;
            break;
        case USART2_TYPE:
            u16Ret = g_cUsart2Info.UsartRxCount;
            break;
        case USART3_TYPE:
            u16Ret = g_cUsart3Info.UsartRxCount;
            break;
        default:
            break;
        
    }
    return u16Ret;
}

VOID SetUsartCurrentLength(U8 type, U16 u16Value)
{
    switch(type)
    {
        case USART1_TYPE:
            g_cUsart1Info.UsartRxCount = u16Value;
            break;
        case USART2_TYPE:
            g_cUsart2Info.UsartRxCount = u16Value;
            break;
        case USART3_TYPE:
            g_cUsart3Info.UsartRxCount = u16Value;
            break;
        default:
            break;
        
    }
}
//初始化IO 串口1 
//bound:波特率
VOID uart1_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //定义中断结构体  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //定义IO初始化结构体  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //定义串口结构体    
    USART_InitTypeDef USART_InitStructure;  
    //定义DMA结构体  
    DMA_InitTypeDef DMA_InitStructure;  

    U8 *pSendBuf,  *pReceiveBuf, *pHandleReceiveBuf, *pHandleBackBuf;
    
    PQueueInfo pQueueInfo;
    
    pSendBuf = mymalloc(SRAMIN, SendSize);

    pReceiveBuf = mymalloc(SRAMIN, ReceiveSize);
    
    pHandleReceiveBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    pHandleBackBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    pQueueInfo = mymalloc(SRAMIN, sizeof(CQueueInfo));

    if((pSendBuf == NULL) || (pReceiveBuf == NULL) || (pQueueInfo == NULL) || (pHandleReceiveBuf == NULL) || (pHandleBackBuf == NULL))
    {
        EnterException(ERR_USATT1_MALLOC_FAIL);
    }
    else
    {
        pUsart1Data = pHandleReceiveBuf;
        pQueueUsart1Info = pQueueInfo;
        g_pUsart1_rx_buf = pReceiveBuf;
        g_pUsart1_tx_buf = pSendBuf;
        g_cUsart1Info.Usart_rec_len = ReceiveSize;
        g_cUsart1Info.Usart_sen_len = SendSize;
        g_pUsart1BackData = pHandleBackBuf;//备份
        
        g_cUsart1Info.bFlagTx_Busy = FALSE;
        g_cUsart1Info.UsartRxCount = 0;
    }

 
    //打开串口对应的外设时钟    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
       
    //串口发DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
    //DMA发送中断设置  
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMA通道配置  
    DMA_DeInit(DMA2_Stream7);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart1_tx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart1Info.Usart_sen_len ;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //配置DMA1的通道           
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);    
    //使能中断  
    DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);     
  
    //串口收DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
    //DMA通道配置  
    DMA_DeInit(DMA2_Stream5);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart1_rx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart1Info.Usart_rec_len;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //配置DMA1的通道           
    DMA_Init(DMA2_Stream5, &DMA_InitStructure);    
    //使能通道  
    DMA_Cmd(DMA2_Stream5,ENABLE);  
      
    //初始化串口参数    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //初始化串口   
    USART_Init(USART1,&USART_InitStructure);    
      
    //中断配置  
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    
  
    //配置中断    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //通道设置为串口中断    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure);     
          
    //采用DMA方式发送  
    USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  
    //采用DMA方式接收  
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  
  
    //中断配置  
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    
    //启动串口    
    USART_Cmd(USART1, ENABLE);      
  
    //设置IO口时钟        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);  
  
    //管脚模式:输出口  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //类型:推挽模式  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //上拉下拉设置  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO口速度  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //管脚指定  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  
    //初始化  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
     
}  

VOID uart1_deinit(VOID)
{

	myfree(SRAMIN, g_pUsart1_tx_buf);
	
	myfree(SRAMIN, g_pUsart1_rx_buf);
	
	myfree(SRAMIN, pUsart1Data);
	
	myfree(SRAMIN, g_pUsart1BackData);
	
	myfree(SRAMIN, pQueueUsart1Info);
	
	myfree(SRAMIN, pQueueUsart1Info);
	
	DMA_DeInit(DMA2_Stream7); 
	
	DMA_DeInit(DMA2_Stream5);
	
	DMA_Cmd(DMA2_Stream5, DISABLE); 
	
	DMA_Cmd(DMA2_Stream7, DISABLE);
	
	USART_Cmd(USART1, DISABLE);
}
//使用DMA进行发送
VOID Usart1_DMA_Send(U8 *data, U16 size)  
{  
    //等待空闲  
    while (g_cUsart1Info.bFlagTx_Busy == TRUE);
    
    g_cUsart1Info.bFlagTx_Busy = TRUE;  
    //复制数据  
    memcpy(g_pUsart1_tx_buf, data, size);  
    //设置传输数据长度  
    DMA_SetCurrDataCounter(DMA2_Stream7, size);  
    //打开DMA,开始发送  
    DMA_Cmd(DMA2_Stream7, ENABLE);  
}  

VOID DMA2_Stream7_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA2_Stream7, DMA_IT_TCIF7) != RESET)   
    {  
        //清除标志位  
        DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);  
        //关闭DMA  
        DMA_Cmd(DMA2_Stream7, DISABLE);  
        //打开发送完成中断,发送最后两个字节  
        USART_ITConfig(USART1, USART_IT_TC, ENABLE);  
    }  
}

//使用DMA进行接收 
VOID USART1_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)  
    {  
        //关闭发送完成中断  
        USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
        //发送完成  
        g_cUsart1Info.bFlagTx_Busy = FALSE;  
           
    }
    //接收完成中断  
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {  
        USART1->SR;  
        USART1->DR; //清USART_IT_IDLE标志  
        //关闭DMA  
        DMA_Cmd(DMA2_Stream5,DISABLE);  
        //清除标志位  
        DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5);  
          
        //获得接收帧帧长  
        g_cUsart1Info.UsartRxCount = g_cUsart1Info.Usart_rec_len - DMA_GetCurrDataCounter(DMA2_Stream5);  
        
        ReceiveUsartData(USART1_TYPE);
        
        //设置传输数据长度  
        DMA_SetCurrDataCounter(DMA2_Stream5, g_cUsart1Info.Usart_rec_len);  
        //打开DMA  
        DMA_Cmd(DMA2_Stream5, ENABLE);   
    }       
       
} 

VOID uart2_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //定义中断结构体  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //定义IO初始化结构体  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //定义串口结构体    
    USART_InitTypeDef USART_InitStructure;  
    //定义DMA结构体  
    DMA_InitTypeDef DMA_InitStructure;  

    U8 *pSendBuf,  *pReceiveBuf, *pHandleReceiveBuf, *pHandleBackBuf;
    
    PQueueInfo pQueueInfo;
    
    pSendBuf = mymalloc(SRAMIN, SendSize);

    pReceiveBuf = mymalloc(SRAMIN, ReceiveSize);
    
    pHandleReceiveBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    pHandleBackBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    pQueueInfo = mymalloc(SRAMIN, sizeof(CQueueInfo));

    if((pSendBuf == NULL) || (pReceiveBuf == NULL) || (pQueueInfo == NULL) || (pHandleReceiveBuf == NULL) || (pHandleBackBuf == NULL))
    {
        EnterException(ERR_USATT2_MALLOC_FAIL);
    }
    else
    {
        pUsart2Data = pHandleReceiveBuf;
        pQueueUsart2Info = pQueueInfo;
        g_pUsart2_rx_buf = pReceiveBuf;
        g_pUsart2_tx_buf = pSendBuf;
        g_cUsart2Info.Usart_rec_len = ReceiveSize;
        g_cUsart2Info.Usart_sen_len = SendSize;
        g_pUsart2BackData = pHandleBackBuf;

        g_cUsart2Info.bFlagTx_Busy = FALSE;
        g_cUsart2Info.UsartRxCount = 0;
    }
  
    //打开串口对应的外设时钟    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
       
    //串口发DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA发送中断设置  
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMA通道配置  
    DMA_DeInit(DMA1_Stream6);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart2_tx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart2Info.Usart_sen_len ;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //配置DMA1的通道           
    DMA_Init(DMA1_Stream6, &DMA_InitStructure);    
    //使能中断  
    DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);     
  
    //串口收DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA通道配置  
    DMA_DeInit(DMA1_Stream5);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart2_rx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart2Info.Usart_rec_len;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //配置DMA1的通道           
    DMA_Init(DMA1_Stream5, &DMA_InitStructure);    
    //使能通道  
    DMA_Cmd(DMA1_Stream5,ENABLE);  
      
    //初始化串口参数    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //初始化串口   
    USART_Init(USART2,&USART_InitStructure);    
      
    //中断配置  
    USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);    
  
    //配置中断    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //通道设置为串口中断    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure);     
          
    //采用DMA方式发送  
    USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  
    //采用DMA方式接收  
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);  
  
    //中断配置  
    USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);    
    //启动串口    
    USART_Cmd(USART2, ENABLE);      
  
    //设置IO口时钟        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);  
  
    //管脚模式:输出口  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //类型:推挽模式  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //上拉下拉设置  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO口速度  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //管脚指定  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  
    //初始化  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
      
    //管脚模式:输入口  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //上拉下拉设置  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    //管脚指定  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
    //初始化  
    GPIO_Init(GPIOA, &GPIO_InitStructure);        
}  


//使用DMA进行发送
VOID Usart2_DMA_Send(U8 *data, U16 size)  
{  
    //等待空闲  
    while (g_cUsart2Info.bFlagTx_Busy == TRUE);
    
    g_cUsart2Info.bFlagTx_Busy = TRUE;  
    //复制数据  
    memcpy(g_pUsart2_tx_buf, data, size);  
    //设置传输数据长度  
    DMA_SetCurrDataCounter(DMA1_Stream6, size);  
    //打开DMA,开始发送  
    DMA_Cmd(DMA1_Stream6, ENABLE);  
}  

VOID DMA1_Stream6_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6) != RESET)   
    {  
        //清除标志位  
        DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);  
        //关闭DMA  
        DMA_Cmd(DMA1_Stream6,DISABLE);  
        //打开发送完成中断,发送最后两个字节  
        USART_ITConfig(USART2, USART_IT_TC, ENABLE);  
    }  
}  
//使用DMA进行接收 
VOID USART2_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)  
    {  
        //关闭发送完成中断  
        USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
        //发送完成  
        g_cUsart2Info.bFlagTx_Busy = FALSE;  
           
    }
    //接收完成中断  
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {  
        USART2->SR;  
        USART2->DR; //清USART_IT_IDLE标志  
        //关闭DMA  
        DMA_Cmd(DMA1_Stream5,DISABLE);  
        //清除标志位  
        DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);  
          
        //获得接收帧帧长  
        g_cUsart2Info.UsartRxCount = g_cUsart2Info.Usart_rec_len - DMA_GetCurrDataCounter(DMA1_Stream5);  
        
        ReceiveUsartData(USART2_TYPE);
        
        //设置传输数据长度  
        DMA_SetCurrDataCounter(DMA1_Stream5, g_cUsart2Info.Usart_rec_len);  
        //打开DMA  
        DMA_Cmd(DMA1_Stream5,ENABLE);   
    }       
       
}  
/////////////////////////////////////////////////////////////////////////////////////////////
VOID uart3_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //定义中断结构体  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //定义IO初始化结构体  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //定义串口结构体    
    USART_InitTypeDef USART_InitStructure;  
    //定义DMA结构体  
    DMA_InitTypeDef DMA_InitStructure; 

    
    U8 *pSendBuf,  *pReceiveBuf, *pHandleReceiveBuf, *pHandleBackBuf;
        
    PQueueInfo pQueueInfo;
    
    pSendBuf = mymalloc(SRAMIN, SendSize);

    pReceiveBuf = mymalloc(SRAMIN, ReceiveSize);
    
    pHandleReceiveBuf = mymalloc(SRAMIN, MAXQUEUESIZE);

    pHandleBackBuf = mymalloc(SRAMIN, MAXQUEUESIZE);
    
    pQueueInfo = mymalloc(SRAMIN, sizeof(CQueueInfo));

    if((pSendBuf == NULL) || (pReceiveBuf == NULL) || (pQueueInfo == NULL) || (pHandleReceiveBuf == NULL) || (pHandleBackBuf == NULL))
    {
        EnterException(ERR_USATT3_MALLOC_FAIL);
    }
    else
    {
        pUsart3Data = pHandleReceiveBuf;
        pQueueUsart3Info = pQueueInfo;
        g_pUsart3_rx_buf = pReceiveBuf;
        g_pUsart3_tx_buf = pSendBuf;
        g_cUsart3Info.Usart_rec_len = ReceiveSize;
        g_cUsart3Info.Usart_sen_len = SendSize;
        g_pUsart3BackData = pHandleBackBuf;

        g_cUsart3Info.bFlagTx_Busy = FALSE;
        g_cUsart3Info.UsartRxCount = 0;
    }
  
    //打开串口对应的外设时钟    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
       
    //串口发DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA发送中断设置  
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMA通道配置  
    DMA_DeInit(DMA1_Stream3);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart3_tx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart3Info.Usart_sen_len;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //配置DMA1的通道           
    DMA_Init(DMA1_Stream3, &DMA_InitStructure);    
    //使能中断  
    DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);     
  
    //串口收DMA配置    
    //启动DMA时钟  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA通道配置  
    DMA_DeInit(DMA1_Stream1);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart3_rx_buf;  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = g_cUsart3Info.Usart_rec_len ;  
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //指定如果FIFO模式或直接模式将用于指定的流 ： 不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移 */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //配置DMA1的通道           
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);    
    //使能通道  
    DMA_Cmd(DMA1_Stream1,ENABLE);  
      
    //初始化串口参数    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //初始化串口   
    USART_Init(USART3,&USART_InitStructure);    
      
    //中断配置  
    USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);    
  
    //配置中断    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //通道设置为串口中断    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //中断占先等级  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //中断响应优先级   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //打开中断    
    NVIC_Init(&NVIC_InitStructure);     
          
    //采用DMA方式发送  
    USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);  
    //采用DMA方式接收  
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);  
  
    //中断配置  
    USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);    
    //启动串口    
    USART_Cmd(USART3, ENABLE);      
  
    //设置IO口时钟        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);    
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);  
  
    //管脚模式:输出口  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //类型:推挽模式  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //上拉下拉设置  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO口速度  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //管脚指定  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
    //初始化  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    //管脚模式:输入口  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //上拉下拉设置  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    //管脚指定  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  
    //初始化  
    GPIO_Init(GPIOD, &GPIO_InitStructure);        
}  


//使用DMA进行发送
VOID Usart3_DMA_Send(U8 *data, U16 size)  
{  
    //等待空闲  
    while (g_cUsart3Info.bFlagTx_Busy == TRUE);
    
    g_cUsart3Info.bFlagTx_Busy = TRUE;  
    //复制数据  
    memcpy(g_pUsart3_tx_buf, data, size);  
    //设置传输数据长度  
    DMA_SetCurrDataCounter(DMA1_Stream3, size);  
    //打开DMA,开始发送  
    DMA_Cmd(DMA1_Stream3, ENABLE);  
}  

VOID DMA1_Stream3_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA1_Stream3,DMA_IT_TCIF3) != RESET)   
    {  
        //清除标志位  
        DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);  
        //关闭DMA  
        DMA_Cmd(DMA1_Stream3, DISABLE);  
        //打开发送完成中断,发送最后两个字节  
        USART_ITConfig(USART3, USART_IT_TC, ENABLE);  
    }  
}  
//使用DMA进行接收 
VOID USART3_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)  
    {  
        //关闭发送完成中断  
        USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
        //发送完成  
        g_cUsart3Info.bFlagTx_Busy = FALSE;  
           
    }
    //接收完成中断  
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  
    {  
        USART3->SR;  
        USART3->DR; //清USART_IT_IDLE标志  
        //关闭DMA  
        DMA_Cmd(DMA1_Stream1,DISABLE);  
        //清除标志位  
        DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1);  
          
        //获得接收帧帧长  
        g_cUsart3Info.UsartRxCount = g_cUsart3Info.Usart_rec_len  - DMA_GetCurrDataCounter(DMA1_Stream1);  
        
        ReceiveUsartData(USART3_TYPE);

        //设置传输数据长度  
        DMA_SetCurrDataCounter(DMA1_Stream1, g_cUsart3Info.Usart_rec_len );  
        //打开DMA  
        DMA_Cmd(DMA1_Stream1,ENABLE);   
    }       
       
}  


VOID USART1_Send(U8 *pBuf, U16 *pCount)
{
    U16 u16Cnt;
    
    for(u16Cnt = 0; u16Cnt < *pCount; u16Cnt++)
    {
        USART_SendData(USART1, pBuf[u16Cnt]);   
        
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!=SET);
    }
    
    *pCount = 0;//清除已发送的数据长度
}

VOID USART2_Send(U8 *pBuf, U16 *pCount)
{
    U16 u16Cnt;
    
    for(u16Cnt = 0; u16Cnt < *pCount; u16Cnt++)
    {
        USART_SendData(USART2, pBuf[u16Cnt]);   
        
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=SET);
    }
    *pCount = 0;//清除已发送的数据长度
}

VOID USART3_Send(U8 *pBuf, U16 *pCount)
{
    U16 u16Cnt;
    
    for(u16Cnt = 0; u16Cnt < *pCount; u16Cnt++)
    {
        USART_SendData(USART3, pBuf[u16Cnt]);   
        
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC)!=SET);
    }
    
    *pCount = 0;//清除已发送的数据长度
}


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
//////////////////////////////////////////////////////////////////
