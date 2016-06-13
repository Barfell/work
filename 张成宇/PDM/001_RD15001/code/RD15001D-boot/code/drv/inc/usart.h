#ifndef __USART_H
#define __USART_H

#include "board.h"

enum
{
    ERR_TYPE = 0,
    USART1_TYPE,
    USART2_TYPE,
    USART3_TYPE,
};

typedef struct _tagUsartInfo
{
	BOOL bFlagTx_Busy;
    U16 Usart_rec_len;//�����������ֽ��� 
    U16 Usart_sen_len;//����������ֽ��� 
    U16 UsartRxCount; //��ǰ���ڵ����ݳ���
    
}CUsartInfo, *PUsartInfo;

EXTERN CUsartInfo g_cUsart1Info, g_cUsart2Info, g_cUsart3Info;


EXTERN U8 *pUsart1Data;
EXTERN U8 *pUsart2Data;
EXTERN U8 *pUsart3Data;
EXTERN U8 *pOtherData;      //�����õĻ��λ���      ��С��MAXQUEUESIZE������

EXTERN U8  *g_pUsart1_rx_buf; 
EXTERN U8  *g_pUsart2_rx_buf; 
EXTERN U8  *g_pUsart3_rx_buf; 


EXTERN U8 *g_pUsart1BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
EXTERN U8 *g_pUsart2BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
EXTERN U8 *g_pUsart3BackData;    //�����õĻ��λ���      ��С��MAXQUEUESIZE������
EXTERN U8 *g_pOtherBackData;

EXTERN U16 g_Usart1BackDataCount;      
EXTERN U16 g_Usart2BackDataCount;    
EXTERN U16 g_Usart3BackDataCount;
EXTERN U16 g_OtherBackDataCount;

EXTERN PQueueInfo pQueueUsart1Info;
EXTERN PQueueInfo pQueueUsart2Info;
EXTERN PQueueInfo pQueueUsart3Info;
EXTERN PQueueInfo pQueueOtherInfo;


VOID uart1_init(U32 bound, U16 SendSize, U16 ReceiveSize);
VOID uart2_init(U32 bound, U16 SendSize, U16 ReceiveSize);
VOID uart3_init(U32 bound, U16 SendSize, U16 ReceiveSize);

VOID Usart1_DMA_Send(U8 *data, U16 size);
VOID Usart2_DMA_Send(U8 *data, U16 size);
VOID Usart3_DMA_Send(U8 *data, U16 size);

//����ķ���û������DMA
VOID USART1_Send(U8 *pBuf, U16 *pCount);
VOID USART2_Send(U8 *pBuf, U16 *pCount);
VOID USART3_Send(U8 *pBuf, U16 *pCount);

VOID ClearUsartCurrentLength(U8 type);
U16 GetUsartCurrentLength(U8 type);
VOID SetUsartCurrentLength(U8 type, U16 u16Value);
VOID uart1_deinit(VOID);
#endif


