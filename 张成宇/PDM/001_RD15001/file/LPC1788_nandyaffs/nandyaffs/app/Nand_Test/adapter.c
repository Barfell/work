#include "bsp.h"
#include "lpc_types.h"
#include "sdram_k4s561632j.h"
#include "debug_frmwrk.h"
#include "adaptor.h"
#include "nandflash_k9f2g08u0x.h"

static uint8_t BlockBuff[NANDFLASH_PAGE_PER_BLOCK*NANDFLASH_NUMOF_BLOCK];
//static uint8_t *BlockBuff=(uint8_t *)SDRAM_BASE_ADDR;
extern uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];

static void  ReadBlock(uint32_t Block,uint8_t *Buff);
static void  WriteBlock(uint32_t Block,uint8_t *Buff);
static void  WriteOnBlockBuff(uint32_t offset,uint32_t size,uint8_t *buff);

uint32_t  BadTab[11]={0};
uint32_t RedrTab[10]={2047,2046,2045,2044,2043,2042,2041,2040}; 

//擦最小单位为block		写最小单位为page
//读是随机的
//----------------------------------------------------------------------
// mark invalid block
void CheckBad(void)
{
	uint32_t i=0,m=0;
	
	for(i=0;i<NANDFLASH_NUMOF_BLOCK;i++){
		if(InvalidBlockTable[i]==FALSE){
			BadTab[m]=i;// record invalid block
			m++;
			if(m>=10)
				break;
		}
	}
	
 	//BadTab[m]=0;m++;
 	//BadTab[m]=1;m++;
  	BadTab[10]=m; //  坏块个数
}


// 一块对应64页	一页对应2048个字节
// Block 块号
 static void  ReadBlock(uint32_t Block,uint8_t *Buff)
{

	uint32_t i;
	uint8_t *tmp;
	
         tmp=Buff;
	for(i=0;i<64;i++)
	{
		//块内页号	块号	缓冲区
		NandFlash_PageRead( i, Block, tmp) ;
		tmp+=2048;
	}

}

//Block 块号
static void  WriteBlock(uint32_t Block,uint8_t *Buff)
{
	uint32_t i;
	uint8_t *tmp;

         tmp=Buff;
	for(i=0;i<64;i++)
	{
		//块内页号	块号	缓冲区
		NandFlash_PageProgram(i,Block,tmp);
 		tmp+=2048;
	}
}

//offset 表示block内偏移sector个数
//size  bytes数
static void  WriteOnBlockBuff(uint32_t offset,uint32_t size,uint8_t *buff)
{
	uint32_t i,n;
	
         i=offset*512;
	for(n=0;n<size;)
	{
		 BlockBuff[i++] = buff[n++];	 
	}
		
}

// 对应 FATFS读扇区函数
//sector 起始扇区号
//count 读扇区个数
//buff 读缓冲区
void  FAT_ReadNF(uint32_t sector,uint32_t count,uint8_t *buff)
{
	uint32_t i,j,block1,block2,offset;
	uint8_t *tmp;
	uint32_t tmp_sector;
	
	// 256个sector对应1 个block
	//512*256=64*2048
	block1=sector/256; //起始sector所处的block号
	block2=(sector+count-1)/256;// 结束sector所处的blcok号

	for(i=0;i<BadTab[10];i++)
         {
         	if(block1==BadTab[i])
         		block1=RedrTab[i];
			
         	if(block2==BadTab[i])
         	{
			block2=RedrTab[i];	
			break;
                   }
         }

	
         offset=sector%256;	// blcok内偏移sector个数
	tmp_sector=256*block1+offset;
	tmp=buff;

	 if((offset+count)>256)		// 跨2个block
	 	j=(256-offset);
	 else
	 	j = count;

	 for(i=0;i<j;i++)
	{
		NandFlash_SectorRead(tmp_sector+i,tmp);
	        tmp+=512;
	}
	 
	 // 跨2个block
         if(block2!=block1)
	 {
		tmp_sector=256*block2;
		j=count - j;
		for(i=0;i<j;i++)
		{
			NandFlash_SectorRead(tmp_sector+i,tmp);
		        tmp+=512;
		}
	 }
	
}

//--------------------------------------------------------------
// 对应 FATFS写扇区函数
//sector 起始扇区号
//count 写扇区个数
//buff 写缓冲区
void  FAT_WriteNF2G08(uint32_t sector,uint8_t count,uint8_t *buff)
{
 
	//Count最大为255,所以Sector*Count最多跨越2个Block
	uint32_t   block1=0,block2=0;//,tmp;
	uint32_t  offset,size,i;
	
 	//最多跨2个blcok		不跨2个blcok时，blcok1==blcok2
         block1=sector/256;				//  4*64   起始sector所处的block号
         block2=(sector+count-1)/256;	// 结束sector所处的blcok号
	
	for(i=0;i<BadTab[10];i++)
     {
     	if(block1==BadTab[i])
     		block1=RedrTab[i];

     	if(block2==BadTab[i])
     	{
    	block2=RedrTab[i];	
    	break;
               }
     }
	
         ReadBlock(block1,BlockBuff);
          NandFlash_BlockErase(block1);
		  
         offset=sector%256;// 块内偏移sector数
         
          if((offset+count)>256)		// 跨2个block
         	size=(256-offset)*512;	// 第1个blcok内要写的bytes
         else						// 所有待操作sector都在同一个blcok内
         	size=count*512;		//总共要写的bytes
         	
         WriteOnBlockBuff(offset,size,buff);	
         WriteBlock(block1,BlockBuff);

	// 跨2个block
         if(block2!=block1)
         {
          	ReadBlock(block2,BlockBuff);
         	size=(count+offset-256)*512; // 第2个blcok内要写的bytes
         	WriteOnBlockBuff(0,size,buff);	
         	WriteBlock(block2,BlockBuff);
         }	
}
