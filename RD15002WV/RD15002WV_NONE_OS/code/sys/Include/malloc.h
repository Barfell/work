#ifndef __MALLOC_H
#define __MALLOC_H

//���ߵ���
#include "tool.h"

#ifndef NULL
#define NULL 0
#endif

//���������ڴ��
#define SRAMIN	 0		//�ڲ��ڴ��
#define SRAMEX   1		//�ⲿ�ڴ��
#define SRAMCCM  2		//CCM�ڴ��(�˲���SRAM����CPU���Է���!!!)


#define SRAMBANK 	3	//����֧�ֵ�SRAM����.	


//mem1�ڴ�����趨.mem1��ȫ�����ڲ�SRAM����.
#define MEM1_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE			100*1024  						//�������ڴ� 100K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//�ڴ���С



//mem2�ڴ�����趨.mem2���ڴ�ش����ⲿSRAM����
#define MEM2_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM2_MAX_SIZE			960 *1024  						//�������ڴ�960K
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//�ڴ���С
		 
//mem3�ڴ�����趨.mem3����CCM,���ڹ���CCM(�ر�ע��,�ⲿ��SRAM,��CPU���Է���!!)
#define MEM3_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM3_MAX_SIZE			60 *1024  						//�������ڴ�60K
#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//�ڴ���С
		 


//�ڴ���������
struct _m_mallco_dev
{
	VOID (*init)(U8);					//��ʼ��
	U8 (*perused)(U8);		  	    	//�ڴ�ʹ����
	U8 	*membase[SRAMBANK];				//�ڴ�� ����SRAMBANK��������ڴ�
	U16 *memmap[SRAMBANK]; 				//�ڴ����״̬��
	U8  memrdy[SRAMBANK]; 				//�ڴ�����Ƿ����
};
EXTERN struct _m_mallco_dev mallco_dev;	 //��mallco.c���涨��

VOID mymemset(VOID *s,U8 c,U32 count);	//�����ڴ�
VOID mymemcpy(VOID *des,VOID *src,U32 n);//�����ڴ�     
VOID my_mem_init(U8 memx);				//�ڴ�����ʼ������(��/�ڲ�����)
U32 my_mem_malloc(U8 memx,U32 size);	//�ڴ����(�ڲ�����)
U8 my_mem_free(U8 memx,U32 offset);		//�ڴ��ͷ�(�ڲ�����)
U8 my_mem_perused(U8 memx);				//����ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
VOID myfree(U8 memx,VOID *ptr);  			//�ڴ��ͷ�(�ⲿ����)
VOID *mymalloc(U8 memx,U32 size);			//�ڴ����(�ⲿ����)
VOID *myrealloc(U8 memx,VOID *ptr,U32 size);//���·����ڴ�(�ⲿ����)

//�÷���p=mymalloc(SRAMIN,2048);//����2K�ֽ� Ĭ��ʹ���ڲ�ram��myfree(sramx,p);//�ͷ��ڴ�
#endif













