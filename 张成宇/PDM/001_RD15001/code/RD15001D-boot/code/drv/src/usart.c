#include "usart.h"	




STATIC U8 *g_pUsart1_tx_buf;    //�����õĻ���   
STATIC U8 *g_pUsart2_tx_buf;    //�����õĻ���
STATIC U8 *g_pUsart3_tx_buf;    //�����õĻ���  

CUsartInfo g_cUsart1Info, g_cUsart2Info, g_cUsart3Info;


U8 *g_pUsart1_rx_buf; //�����õĻ���
U8 *g_pUsart2_rx_buf; //�����õĻ���
U8 *g_pUsart3_rx_buf; //�����õĻ���

__align(4) U8 *pUsart1Data;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
__align(4) U8 *pUsart2Data;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
__align(4) U8 *pUsart3Data;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
     
__align(4) U8 *g_pUsart1BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
__align(4) U8 *g_pUsart2BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
__align(4) U8 *g_pUsart3BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������

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
//��ʼ��IO ����1 
//bound:������
VOID uart1_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //�����жϽṹ��  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //����IO��ʼ���ṹ��  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //���崮�ڽṹ��    
    USART_InitTypeDef USART_InitStructure;  
    //����DMA�ṹ��  
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
        g_pUsart1BackData = pHandleBackBuf;//����
        
        g_cUsart1Info.bFlagTx_Busy = FALSE;
        g_cUsart1Info.UsartRxCount = 0;
    }

 
    //�򿪴��ڶ�Ӧ������ʱ��    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
       
    //���ڷ�DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
    //DMA�����ж�����  
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMAͨ������  
    DMA_DeInit(DMA2_Stream7);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart1_tx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart1Info.Usart_sen_len ;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //����DMA1��ͨ��           
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);    
    //ʹ���ж�  
    DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE);     
  
    //������DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  
    //DMAͨ������  
    DMA_DeInit(DMA2_Stream5);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart1_rx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart1Info.Usart_rec_len;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //����DMA1��ͨ��           
    DMA_Init(DMA2_Stream5, &DMA_InitStructure);    
    //ʹ��ͨ��  
    DMA_Cmd(DMA2_Stream5,ENABLE);  
      
    //��ʼ�����ڲ���    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //��ʼ������   
    USART_Init(USART1,&USART_InitStructure);    
      
    //�ж�����  
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    
  
    //�����ж�    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //ͨ������Ϊ�����ж�    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�ж�ռ�ȵȼ�  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�ж���Ӧ���ȼ�   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�    
    NVIC_Init(&NVIC_InitStructure);     
          
    //����DMA��ʽ����  
    USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  
    //����DMA��ʽ����  
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  
  
    //�ж�����  
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);    
    //��������    
    USART_Cmd(USART1, ENABLE);      
  
    //����IO��ʱ��        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);  
  
    //�ܽ�ģʽ:�����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //����:����ģʽ  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //������������  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO���ٶ�  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //�ܽ�ָ��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  
    //��ʼ��  
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
//ʹ��DMA���з���
VOID Usart1_DMA_Send(U8 *data, U16 size)  
{  
    //�ȴ�����  
    while (g_cUsart1Info.bFlagTx_Busy == TRUE);
    
    g_cUsart1Info.bFlagTx_Busy = TRUE;  
    //��������  
    memcpy(g_pUsart1_tx_buf, data, size);  
    //���ô������ݳ���  
    DMA_SetCurrDataCounter(DMA2_Stream7, size);  
    //��DMA,��ʼ����  
    DMA_Cmd(DMA2_Stream7, ENABLE);  
}  

VOID DMA2_Stream7_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA2_Stream7, DMA_IT_TCIF7) != RESET)   
    {  
        //�����־λ  
        DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);  
        //�ر�DMA  
        DMA_Cmd(DMA2_Stream7, DISABLE);  
        //�򿪷�������ж�,������������ֽ�  
        USART_ITConfig(USART1, USART_IT_TC, ENABLE);  
    }  
}

//ʹ��DMA���н��� 
VOID USART1_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)  
    {  
        //�رշ�������ж�  
        USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
        //�������  
        g_cUsart1Info.bFlagTx_Busy = FALSE;  
           
    }
    //��������ж�  
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {  
        USART1->SR;  
        USART1->DR; //��USART_IT_IDLE��־  
        //�ر�DMA  
        DMA_Cmd(DMA2_Stream5,DISABLE);  
        //�����־λ  
        DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5);  
          
        //��ý���֡֡��  
        g_cUsart1Info.UsartRxCount = g_cUsart1Info.Usart_rec_len - DMA_GetCurrDataCounter(DMA2_Stream5);  
        
        ReceiveUsartData(USART1_TYPE);
        
        //���ô������ݳ���  
        DMA_SetCurrDataCounter(DMA2_Stream5, g_cUsart1Info.Usart_rec_len);  
        //��DMA  
        DMA_Cmd(DMA2_Stream5, ENABLE);   
    }       
       
} 

VOID uart2_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //�����жϽṹ��  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //����IO��ʼ���ṹ��  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //���崮�ڽṹ��    
    USART_InitTypeDef USART_InitStructure;  
    //����DMA�ṹ��  
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
  
    //�򿪴��ڶ�Ӧ������ʱ��    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
       
    //���ڷ�DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA�����ж�����  
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMAͨ������  
    DMA_DeInit(DMA1_Stream6);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart2_tx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart2Info.Usart_sen_len ;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //����DMA1��ͨ��           
    DMA_Init(DMA1_Stream6, &DMA_InitStructure);    
    //ʹ���ж�  
    DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,ENABLE);     
  
    //������DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMAͨ������  
    DMA_DeInit(DMA1_Stream5);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart2_rx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart2Info.Usart_rec_len;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //����DMA1��ͨ��           
    DMA_Init(DMA1_Stream5, &DMA_InitStructure);    
    //ʹ��ͨ��  
    DMA_Cmd(DMA1_Stream5,ENABLE);  
      
    //��ʼ�����ڲ���    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //��ʼ������   
    USART_Init(USART2,&USART_InitStructure);    
      
    //�ж�����  
    USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);    
  
    //�����ж�    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;               //ͨ������Ϊ�����ж�    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�ж�ռ�ȵȼ�  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�ж���Ӧ���ȼ�   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�    
    NVIC_Init(&NVIC_InitStructure);     
          
    //����DMA��ʽ����  
    USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  
    //����DMA��ʽ����  
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);  
  
    //�ж�����  
    USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);    
    //��������    
    USART_Cmd(USART2, ENABLE);      
  
    //����IO��ʱ��        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);  
  
    //�ܽ�ģʽ:�����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //����:����ģʽ  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //������������  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO���ٶ�  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //�ܽ�ָ��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  
    //��ʼ��  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
      
    //�ܽ�ģʽ:�����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //������������  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    //�ܽ�ָ��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
    //��ʼ��  
    GPIO_Init(GPIOA, &GPIO_InitStructure);        
}  


//ʹ��DMA���з���
VOID Usart2_DMA_Send(U8 *data, U16 size)  
{  
    //�ȴ�����  
    while (g_cUsart2Info.bFlagTx_Busy == TRUE);
    
    g_cUsart2Info.bFlagTx_Busy = TRUE;  
    //��������  
    memcpy(g_pUsart2_tx_buf, data, size);  
    //���ô������ݳ���  
    DMA_SetCurrDataCounter(DMA1_Stream6, size);  
    //��DMA,��ʼ����  
    DMA_Cmd(DMA1_Stream6, ENABLE);  
}  

VOID DMA1_Stream6_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA1_Stream6,DMA_IT_TCIF6) != RESET)   
    {  
        //�����־λ  
        DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);  
        //�ر�DMA  
        DMA_Cmd(DMA1_Stream6,DISABLE);  
        //�򿪷�������ж�,������������ֽ�  
        USART_ITConfig(USART2, USART_IT_TC, ENABLE);  
    }  
}  
//ʹ��DMA���н��� 
VOID USART2_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)  
    {  
        //�رշ�������ж�  
        USART_ITConfig(USART2,USART_IT_TC,DISABLE);  
        //�������  
        g_cUsart2Info.bFlagTx_Busy = FALSE;  
           
    }
    //��������ж�  
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {  
        USART2->SR;  
        USART2->DR; //��USART_IT_IDLE��־  
        //�ر�DMA  
        DMA_Cmd(DMA1_Stream5,DISABLE);  
        //�����־λ  
        DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);  
          
        //��ý���֡֡��  
        g_cUsart2Info.UsartRxCount = g_cUsart2Info.Usart_rec_len - DMA_GetCurrDataCounter(DMA1_Stream5);  
        
        ReceiveUsartData(USART2_TYPE);
        
        //���ô������ݳ���  
        DMA_SetCurrDataCounter(DMA1_Stream5, g_cUsart2Info.Usart_rec_len);  
        //��DMA  
        DMA_Cmd(DMA1_Stream5,ENABLE);   
    }       
       
}  
/////////////////////////////////////////////////////////////////////////////////////////////
VOID uart3_init(U32 bound, U16 SendSize, U16 ReceiveSize)
{  
    //�����жϽṹ��  
    NVIC_InitTypeDef NVIC_InitStructure ;  
    //����IO��ʼ���ṹ��  
    GPIO_InitTypeDef GPIO_InitStructure;  
    //���崮�ڽṹ��    
    USART_InitTypeDef USART_InitStructure;  
    //����DMA�ṹ��  
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
  
    //�򿪴��ڶ�Ӧ������ʱ��    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
       
    //���ڷ�DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMA�����ж�����  
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    //DMAͨ������  
    DMA_DeInit(DMA1_Stream3);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;   
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart3_tx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart3Info.Usart_sen_len;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
  
    //����DMA1��ͨ��           
    DMA_Init(DMA1_Stream3, &DMA_InitStructure);    
    //ʹ���ж�  
    DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE);     
  
    //������DMA����    
    //����DMAʱ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  
    //DMAͨ������  
    DMA_DeInit(DMA1_Stream1);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_pUsart3_rx_buf;  
    //dma���䷽��  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = g_cUsart3Info.Usart_rec_len ;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
      
    //ָ�����FIFOģʽ��ֱ��ģʽ������ָ������ �� ��ʹ��FIFOģʽ    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //ָ����FIFO��ֵˮƽ  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //ָ����Burstת�������ڴ洫��   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //ָ����Burstת��������Χת�� */    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //����DMA1��ͨ��           
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);    
    //ʹ��ͨ��  
    DMA_Cmd(DMA1_Stream1,ENABLE);  
      
    //��ʼ�����ڲ���    
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    
    USART_InitStructure.USART_Parity = USART_Parity_No;    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    USART_InitStructure.USART_BaudRate = bound;   
    //��ʼ������   
    USART_Init(USART3,&USART_InitStructure);    
      
    //�ж�����  
    USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);    
  
    //�����ж�    
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //ͨ������Ϊ�����ж�    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //�ж�ռ�ȵȼ�  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�ж���Ӧ���ȼ�   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�    
    NVIC_Init(&NVIC_InitStructure);     
          
    //����DMA��ʽ����  
    USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);  
    //����DMA��ʽ����  
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);  
  
    //�ж�����  
    USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
    USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_TXE,DISABLE);  
    USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);    
    //��������    
    USART_Cmd(USART3, ENABLE);      
  
    //����IO��ʱ��        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);    
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);  
  
    //�ܽ�ģʽ:�����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //����:����ģʽ  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
    //������������  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
    //IO���ٶ�  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    //�ܽ�ָ��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
    //��ʼ��  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    //�ܽ�ģʽ:�����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
    //������������  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    //�ܽ�ָ��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  
    //��ʼ��  
    GPIO_Init(GPIOD, &GPIO_InitStructure);        
}  


//ʹ��DMA���з���
VOID Usart3_DMA_Send(U8 *data, U16 size)  
{  
    //�ȴ�����  
    while (g_cUsart3Info.bFlagTx_Busy == TRUE);
    
    g_cUsart3Info.bFlagTx_Busy = TRUE;  
    //��������  
    memcpy(g_pUsart3_tx_buf, data, size);  
    //���ô������ݳ���  
    DMA_SetCurrDataCounter(DMA1_Stream3, size);  
    //��DMA,��ʼ����  
    DMA_Cmd(DMA1_Stream3, ENABLE);  
}  

VOID DMA1_Stream3_IRQHandler(VOID)  
{  
    if(DMA_GetITStatus(DMA1_Stream3,DMA_IT_TCIF3) != RESET)   
    {  
        //�����־λ  
        DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);  
        //�ر�DMA  
        DMA_Cmd(DMA1_Stream3, DISABLE);  
        //�򿪷�������ж�,������������ֽ�  
        USART_ITConfig(USART3, USART_IT_TC, ENABLE);  
    }  
}  
//ʹ��DMA���н��� 
VOID USART3_IRQHandler(VOID)  
{  
    if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)  
    {  
        //�رշ�������ж�  
        USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
        //�������  
        g_cUsart3Info.bFlagTx_Busy = FALSE;  
           
    }
    //��������ж�  
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  
    {  
        USART3->SR;  
        USART3->DR; //��USART_IT_IDLE��־  
        //�ر�DMA  
        DMA_Cmd(DMA1_Stream1,DISABLE);  
        //�����־λ  
        DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1);  
          
        //��ý���֡֡��  
        g_cUsart3Info.UsartRxCount = g_cUsart3Info.Usart_rec_len  - DMA_GetCurrDataCounter(DMA1_Stream1);  
        
        ReceiveUsartData(USART3_TYPE);

        //���ô������ݳ���  
        DMA_SetCurrDataCounter(DMA1_Stream1, g_cUsart3Info.Usart_rec_len );  
        //��DMA  
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
    
    *pCount = 0;//����ѷ��͵����ݳ���
}

VOID USART2_Send(U8 *pBuf, U16 *pCount)
{
    U16 u16Cnt;
    
    for(u16Cnt = 0; u16Cnt < *pCount; u16Cnt++)
    {
        USART_SendData(USART2, pBuf[u16Cnt]);   
        
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=SET);
    }
    *pCount = 0;//����ѷ��͵����ݳ���
}

VOID USART3_Send(U8 *pBuf, U16 *pCount)
{
    U16 u16Cnt;
    
    for(u16Cnt = 0; u16Cnt < *pCount; u16Cnt++)
    {
        USART_SendData(USART3, pBuf[u16Cnt]);   
        
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC)!=SET);
    }
    
    *pCount = 0;//����ѷ��͵����ݳ���
}


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
//////////////////////////////////////////////////////////////////
