#include "malloc.h"	   

//�ڴ��(32�ֽڶ���)
__align(32) U8 mem1base[MEM1_MAX_SIZE];													//�ڲ�SRAM�ڴ��
__align(32) U8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));					//�ⲿSRAM�ڴ��
__align(32) U8 mem3base[MEM3_MAX_SIZE] __attribute__((at(0X10000000)));					//�ڲ�CCM�ڴ��
//�ڴ�����
U16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];													//�ڲ�SRAM�ڴ��MAP
U16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE)));	//�ⲿSRAM�ڴ��MAP
U16 mem3mapbase[MEM3_ALLOC_TABLE_SIZE] __attribute__((at(0X10000000+MEM3_MAX_SIZE)));	//�ڲ�CCM�ڴ��MAP
//�ڴ�������	   
CONST U32 memtblsize[SRAMBANK]={MEM1_ALLOC_TABLE_SIZE,MEM2_ALLOC_TABLE_SIZE,MEM3_ALLOC_TABLE_SIZE};	//�ڴ���С
CONST U32 memblksize[SRAMBANK]={MEM1_BLOCK_SIZE,MEM2_BLOCK_SIZE,MEM3_BLOCK_SIZE};					//�ڴ�ֿ��С
CONST U32 memsize[SRAMBANK]={MEM1_MAX_SIZE,MEM2_MAX_SIZE,MEM3_MAX_SIZE};							//�ڴ��ܴ�С


//�ڴ���������
struct _m_mallco_dev mallco_dev=
{
	my_mem_init,						//�ڴ��ʼ��
	my_mem_perused,						//�ڴ�ʹ����
	mem1base,mem2base,mem3base,			//�ڴ��
	mem1mapbase,mem2mapbase,mem3mapbase,//�ڴ����״̬��
	0,0,0,  		 					//�ڴ����δ����
};

//�����ڴ�
//*des:Ŀ�ĵ�ַ
//*src:Դ��ַ
//n:��Ҫ���Ƶ��ڴ泤��(�ֽ�Ϊ��λ)
VOID mymemcpy(VOID *des,VOID *src,U32 n)  
{  
    U8 *xdes=des;
	U8 *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  
//�����ڴ�
//*s:�ڴ��׵�ַ
//c :Ҫ���õ�ֵ
//count:��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
VOID mymemset(VOID *s,U8 c,U32 count)  
{  
    U8 *xs = s;  
    while(count--)*xs++=c;  
}	   
//�ڴ�����ʼ��  
//memx:�����ڴ��
VOID my_mem_init(U8 memx)  
{  
    mymemset(mallco_dev.memmap[memx], 0,memtblsize[memx]*2);//�ڴ�״̬����������  
	mymemset(mallco_dev.membase[memx], 0,memsize[memx]);	//�ڴ��������������  
	mallco_dev.memrdy[memx]=1;								//�ڴ�����ʼ��OK  
}  
//��ȡ�ڴ�ʹ����
//memx:�����ڴ��
//����ֵ:ʹ����(0~100)
U8 my_mem_perused(U8 memx)  
{  
    U32 used=0;  
    U32 i;  
    for(i=0;i<memtblsize[memx];i++)  
    {  
        if(mallco_dev.memmap[memx][i])used++; 
    } 
    return (used*100)/(memtblsize[memx]);  
}  
//�ڴ����(�ڲ�����)
//memx:�����ڴ��
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ 
U32 my_mem_malloc(U8 memx,U32 size)  
{  
    signed long offset=0;  
    U32 nmemb;	//��Ҫ���ڴ����  
	U32 cmemb=0;//�������ڴ����
    U32 i;  
    if(!mallco_dev.memrdy[memx])mallco_dev.init(memx);//δ��ʼ��,��ִ�г�ʼ�� 
    if(size==0)return 0XFFFFFFFF;//����Ҫ����
    nmemb=size/memblksize[memx];  	//��ȡ��Ҫ����������ڴ����
    if(size%memblksize[memx])nmemb++;  
    for(offset=memtblsize[memx]-1;offset>=0;offset--)//���������ڴ������  
    {     
		if(!mallco_dev.memmap[memx][offset])cmemb++;//�������ڴ��������
		else cmemb=0;								//�����ڴ������
		if(cmemb==nmemb)							//�ҵ�������nmemb�����ڴ��
		{
            for(i=0;i<nmemb;i++)  					//��ע�ڴ��ǿ� 
            {  
                mallco_dev.memmap[memx][offset+i]=nmemb;  
            }  
            return (offset*memblksize[memx]);//����ƫ�Ƶ�ַ  
		}
    }  
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ��  
}  
//�ͷ��ڴ�(�ڲ�����) 
//memx:�����ڴ��
//offset:�ڴ��ַƫ��
//����ֵ:0,�ͷųɹ�;1,�ͷ�ʧ��;  
U8 my_mem_free(U8 memx,U32 offset)  
{  
    int i;  
    if(!mallco_dev.memrdy[memx])//δ��ʼ��,��ִ�г�ʼ��
	{
		mallco_dev.init(memx);    
        return 1;//δ��ʼ��  
    }  
    if(offset<memsize[memx])//ƫ�����ڴ����. 
    {  
        int index=offset/memblksize[memx];			//ƫ�������ڴ�����  
        int nmemb=mallco_dev.memmap[memx][index];	//�ڴ������
        for(i=0;i<nmemb;i++)  						//�ڴ������
        {  
            mallco_dev.memmap[memx][index+i]=0;  
        }  
        return 0;  
    }else return 2;//ƫ�Ƴ�����.  
}  
//�ͷ��ڴ�(�ⲿ����) 
//memx:�����ڴ��
//ptr:�ڴ��׵�ַ 
VOID myfree(U8 memx,VOID *ptr)  
{  
	U32 offset;   
	if(ptr==NULL)return;//��ַΪ0.  
 	offset=(U32)ptr-(U32)mallco_dev.membase[memx];     
    my_mem_free(memx,offset);	//�ͷ��ڴ�      
}  
//�����ڴ�(�ⲿ����)
//memx:�����ڴ��
//size:�ڴ��С(�ֽ�)
//����ֵ:���䵽���ڴ��׵�ַ.
VOID *mymalloc(U8 memx,U32 size)  
{  
    U32 offset;   
	offset=my_mem_malloc(memx,size);  	   	 	   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (VOID*)((U32)mallco_dev.membase[memx]+offset);  
}  
//���·����ڴ�(�ⲿ����)
//memx:�����ڴ��
//*ptr:���ڴ��׵�ַ
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:�·��䵽���ڴ��׵�ַ.
VOID *myrealloc(U8 memx,VOID *ptr,U32 size)  
{
    U32 offset;    
    offset=my_mem_malloc(memx,size);   	
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    mymemcpy((VOID*)((U32)mallco_dev.membase[memx]+offset),ptr,size);	//�������ڴ����ݵ����ڴ�   
        myfree(memx,ptr);  											  		//�ͷž��ڴ�
        return (VOID*)((U32)mallco_dev.membase[memx]+offset);  				//�������ڴ��׵�ַ
    }  
}


