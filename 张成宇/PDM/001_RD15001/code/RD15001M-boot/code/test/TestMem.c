#include "sys.h"
#include "board.h"
//最大可以申请100kbytes的数据也就是0x19000
VOID TestMem(VOID)
{
    U8 *pBuf;
    U32 u32Value = 0;
    
    printf("\r\n内存测试\r\n");
    
    u32Value = 0x800;
    while(1)
    {
        
        pBuf = mymalloc(SRAMIN, u32Value);//申请2K字节 默认使用内部ram
        if(pBuf != NULL)
        {
            printf("\r\n内存申请成功 = %x\r\n", u32Value);
            myfree(SRAMIN, pBuf);//释放内存
        }
        else
        {
            printf("\r\n内存申请失败 = %x\r\n", u32Value);
            while(1);
        }
        u32Value ++;
    }
}
