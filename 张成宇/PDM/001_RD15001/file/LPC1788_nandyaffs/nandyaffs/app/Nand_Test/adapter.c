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

//����С��λΪblock		д��С��λΪpage
//���������
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
  	BadTab[10]=m; //  �������
}


// һ���Ӧ64ҳ	һҳ��Ӧ2048���ֽ�
// Block ���
 static void  ReadBlock(uint32_t Block,uint8_t *Buff)
{

	uint32_t i;
	uint8_t *tmp;
	
         tmp=Buff;
	for(i=0;i<64;i++)
	{
		//����ҳ��	���	������
		NandFlash_PageRead( i, Block, tmp) ;
		tmp+=2048;
	}

}

//Block ���
static void  WriteBlock(uint32_t Block,uint8_t *Buff)
{
	uint32_t i;
	uint8_t *tmp;

         tmp=Buff;
	for(i=0;i<64;i++)
	{
		//����ҳ��	���	������
		NandFlash_PageProgram(i,Block,tmp);
 		tmp+=2048;
	}
}

//offset ��ʾblock��ƫ��sector����
//size  bytes��
static void  WriteOnBlockBuff(uint32_t offset,uint32_t size,uint8_t *buff)
{
	uint32_t i,n;
	
         i=offset*512;
	for(n=0;n<size;)
	{
		 BlockBuff[i++] = buff[n++];	 
	}
		
}

// ��Ӧ FATFS����������
//sector ��ʼ������
//count ����������
//buff ��������
void  FAT_ReadNF(uint32_t sector,uint32_t count,uint8_t *buff)
{
	uint32_t i,j,block1,block2,offset;
	uint8_t *tmp;
	uint32_t tmp_sector;
	
	// 256��sector��Ӧ1 ��block
	//512*256=64*2048
	block1=sector/256; //��ʼsector������block��
	block2=(sector+count-1)/256;// ����sector������blcok��

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

	
         offset=sector%256;	// blcok��ƫ��sector����
	tmp_sector=256*block1+offset;
	tmp=buff;

	 if((offset+count)>256)		// ��2��block
	 	j=(256-offset);
	 else
	 	j = count;

	 for(i=0;i<j;i++)
	{
		NandFlash_SectorRead(tmp_sector+i,tmp);
	        tmp+=512;
	}
	 
	 // ��2��block
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
// ��Ӧ FATFSд��������
//sector ��ʼ������
//count д��������
//buff д������
void  FAT_WriteNF2G08(uint32_t sector,uint8_t count,uint8_t *buff)
{
 
	//Count���Ϊ255,����Sector*Count����Խ2��Block
	uint32_t   block1=0,block2=0;//,tmp;
	uint32_t  offset,size,i;
	
 	//����2��blcok		����2��blcokʱ��blcok1==blcok2
         block1=sector/256;				//  4*64   ��ʼsector������block��
         block2=(sector+count-1)/256;	// ����sector������blcok��
	
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
		  
         offset=sector%256;// ����ƫ��sector��
         
          if((offset+count)>256)		// ��2��block
         	size=(256-offset)*512;	// ��1��blcok��Ҫд��bytes
         else						// ���д�����sector����ͬһ��blcok��
         	size=count*512;		//�ܹ�Ҫд��bytes
         	
         WriteOnBlockBuff(offset,size,buff);	
         WriteBlock(block1,BlockBuff);

	// ��2��block
         if(block2!=block1)
         {
          	ReadBlock(block2,BlockBuff);
         	size=(count+offset-256)*512; // ��2��blcok��Ҫд��bytes
         	WriteOnBlockBuff(0,size,buff);	
         	WriteBlock(block2,BlockBuff);
         }	
}
