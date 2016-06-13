#include "includes.h"


extern U32 g_u32Uart3RevCount;


#define DT485SZIE     200


U8 CalcCheckSum(U8* pSrcData, U16 wDataLen)
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


VOID DT485_Init(VOID)
{
 	UartInit(USART3);
}





void DT485_Get(unsigned char *SensorType, unsigned char *SensorAddr, unsigned char *pBuf, U16 *pLength)
{
	unsigned int get_times = 0;//��ȡ����
	char RequesStr[30];//��Ҫ��ȡ���豸��
	char DATA485str[30];
	memset(RequesStr,0,30);
	memset(DATA485str,0,30);

	
/*��ȡ���ݵ�����㲥*/
	strcat(RequesStr,(char *)SENSOR_HEAD);
	strcat(RequesStr,(char *)SensorType);
	strcat(RequesStr,(char *)SensorAddr);
	strcat(RequesStr,(char *)"\r\n");
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
	UsartSend(USART3,(unsigned char *)RequesStr,strlen(RequesStr));
	//printf("485 request :%s\r\n",RequesStr);
	DelayMs(300);
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);

	
/*�ȴ�����*********/
	while(1)
	{
		if( (GetQueueLength(pUart3QueueInfo) != 0)  && (GetTickCount() - g_u32Uart3RevCount) > 30)//���յ����ݣ����ҽ���������
		{
			ReadUsartData(USART3, (unsigned char *)DATA485str, pLength);
			memcpy(pBuf,DATA485str,strlen(DATA485str)-2);
			break;
		}
		else
		{
			DelayMs(1);
			get_times++;
			if(get_times >4000)
				{break;}
		}
	}
	memset(RequesStr,0,30);
	memset(DATA485str,0,30);
	
}



