#include "sys.h"
#include "board.h"
//����������100kbytes������Ҳ����0x19000
VOID TestMem(VOID)
{
    U8 *pBuf;
    U32 u32Value = 0;
    
    printf("\r\n�ڴ����\r\n");
    
    u32Value = 0x800;
    while(1)
    {
        
        pBuf = mymalloc(SRAMIN, u32Value);//����2K�ֽ� Ĭ��ʹ���ڲ�ram
        if(pBuf != NULL)
        {
            printf("\r\n�ڴ�����ɹ� = %x\r\n", u32Value);
            myfree(SRAMIN, pBuf);//�ͷ��ڴ�
        }
        else
        {
            printf("\r\n�ڴ�����ʧ�� = %x\r\n", u32Value);
            while(1);
        }
        u32Value ++;
    }
}
