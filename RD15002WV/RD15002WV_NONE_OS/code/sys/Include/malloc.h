#ifndef __MALLOC_H
#define __MALLOC_H

//工具调用
#include "tool.h"

#ifndef NULL
#define NULL 0
#endif

//定义三个内存池
#define SRAMIN	 0		//内部内存池
#define SRAMEX   1		//外部内存池
#define SRAMCCM  2		//CCM内存池(此部分SRAM仅仅CPU可以访问!!!)


#define SRAMBANK 	3	//定义支持的SRAM块数.	


//mem1内存参数设定.mem1完全处于内部SRAM里面.
#define MEM1_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM1_MAX_SIZE			100*1024  						//最大管理内存 100K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//内存表大小



//mem2内存参数设定.mem2的内存池处于外部SRAM里面
#define MEM2_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM2_MAX_SIZE			960 *1024  						//最大管理内存960K
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//内存表大小
		 
//mem3内存参数设定.mem3处于CCM,用于管理CCM(特别注意,这部分SRAM,仅CPU可以访问!!)
#define MEM3_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM3_MAX_SIZE			60 *1024  						//最大管理内存60K
#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//内存表大小
		 


//内存管理控制器
struct _m_mallco_dev
{
	VOID (*init)(U8);					//初始化
	U8 (*perused)(U8);		  	    	//内存使用率
	U8 	*membase[SRAMBANK];				//内存池 管理SRAMBANK个区域的内存
	U16 *memmap[SRAMBANK]; 				//内存管理状态表
	U8  memrdy[SRAMBANK]; 				//内存管理是否就绪
};
EXTERN struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

VOID mymemset(VOID *s,U8 c,U32 count);	//设置内存
VOID mymemcpy(VOID *des,VOID *src,U32 n);//复制内存     
VOID my_mem_init(U8 memx);				//内存管理初始化函数(外/内部调用)
U32 my_mem_malloc(U8 memx,U32 size);	//内存分配(内部调用)
U8 my_mem_free(U8 memx,U32 offset);		//内存释放(内部调用)
U8 my_mem_perused(U8 memx);				//获得内存使用率(外/内部调用) 
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
VOID myfree(U8 memx,VOID *ptr);  			//内存释放(外部调用)
VOID *mymalloc(U8 memx,U32 size);			//内存分配(外部调用)
VOID *myrealloc(U8 memx,VOID *ptr,U32 size);//重新分配内存(外部调用)

//用法：p=mymalloc(SRAMIN,2048);//申请2K字节 默认使用内部ram；myfree(sramx,p);//释放内存
#endif













