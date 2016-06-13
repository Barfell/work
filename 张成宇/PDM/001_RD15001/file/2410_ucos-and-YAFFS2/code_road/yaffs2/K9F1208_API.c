#include "TypeCpu.h"
#include <string.h>
#include "def.h"
#include "option.h"
#include "2410addr.h"

static const INT16U K9F1208_CHUNK_SIZE = 512;
static const INT16U K9F1208_TAG_SIZE = 16;
static const INT16U CHUNK_NUM_PER_BLOCK = 32;
static const INT16U BLOCK_NUM_PER_K9F1208 = 2048;

#define TACLS		0  //1clk(0ns) 
#define TWRPH0		3  //3clk(25ns)
#define TWRPH1		0  //1clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns

#define NF_CMD(cmd)	{rNFCMD=cmd;}
#define NF_ADDR(addr)	{rNFADDR=addr;}	
#define NF_nFCE_L()	{rNFCONF&=~(1<<11);}
#define NF_nFCE_H()	{rNFCONF|=(1<<11);}
#define NF_RSTECC()	{rNFCONF|=(1<<12);}
#define NF_RDDATA() 	(rNFDATA)
#define NF_WRDATA(data) {rNFDATA=data;}

#define NF_WAITRB()    {while(!(rNFSTAT&(1<<0)));} 

int K9F1208_Init()
{
	int i = 0;

    rNFCONF=(1<<15)|(1<<14)|(1<<13)|(0<<12)|(1<<11)|(TACLS<<8)|(TWRPH0<<4)|(TWRPH1<<0);	
    // 1  1    1     1,   1      xxx,  r xxx,   r xxx        
    // En 512B 4step ECCR nFCE=H tACLS   tWRPH0   tWRPH1
	
	NF_nFCE_L();
	NF_CMD(0xFF);	//reset command
	for (i = 0; i < 10; i++);	//tWB = 100ns. //??????
	NF_WAITRB();	  //wait 200~500us;
	NF_nFCE_H();
	return 1;
}

int K9F1208_WriteChunk(INT16U block_no, INT16U chunk_no, const INT8U *chunk_data, const INT8U *tag_data)
{
    int i = 0;
    U32 blockPage = (block_no << 5) + chunk_no;

    NF_nFCE_L();
	NF_CMD(0);
    NF_CMD(0x80);   // Write 1st command
    NF_ADDR(0);
    NF_ADDR(blockPage & 0xff);	    //
    NF_ADDR((blockPage >> 8) & 0xff);   // Block & page num.
    NF_ADDR((blockPage >> 16) & 0xff);  //

    for(i = 0; i < 512; i++)
		NF_WRDATA(chunk_data[i]);	// Write one page to NFM from buffer
    
    for(i = 0; i < 16; i++)
		NF_WRDATA(tag_data[i]);	// Write spare array(ECC and Mark)

    NF_CMD(0x10);   // Write 2nd command
    
    for(i = 0; i < 10; i++);  //tWB = 100ns. ////??????
    
    NF_WAITRB();    //wait tPROG 200~500us;
    
    NF_CMD(0x70);   // Read status command   
    
    for(i=0;i<3;i++);  //twhr=60ns
    
    if (NF_RDDATA()&0x1) // Page write error
    {	
    	NF_nFCE_H();
		return 0;
    }
    else 
    {
    	NF_nFCE_H();
		return 1;
    }
}

int K9F1208_ReadChunk(INT16U block_no, INT16U chunk_no, INT8U *chunk_data, INT8U *tag_data)
{
    int i = 0;
    unsigned int blockPage = 0;
   
    chunk_no = chunk_no & 0x1f;
    blockPage = (block_no << 5) + chunk_no;

    NF_nFCE_L();    
    NF_CMD(0x00);   // Read command
	NF_ADDR(0);
    NF_ADDR(blockPage & 0xff);	    //
    NF_ADDR((blockPage >> 8) & 0xff);   // Block & Page num.
    NF_ADDR((blockPage >> 16) & 0xff);  //

    for (i = 0; i < 10; i++); //wait tWB(100ns)/////??????

    NF_WAITRB();    // Wait tR(max 12us)

    for (i = 0; i < 512; i++)
    	chunk_data[i] = NF_RDDATA();	// Read one page
	
    for (i = 0; i < 16; i++)
    	tag_data[i] = NF_RDDATA();	// Read spare array
    
    NF_nFCE_H();    

	return 1;
}

int K9F1208_EraseBlock(INT16U block_no)
{
	U32 blockPage = (block_no << 5);
	int i = 0;

	NF_nFCE_L();
	NF_CMD(0x60);	// Erase one block 1st command
	NF_ADDR(blockPage & 0xff);		// Page number=0
	NF_ADDR((blockPage >> 8) & 0xff);	
	NF_ADDR((blockPage >> 16) & 0xff);
	NF_CMD(0xd0);	// Erase one blcok 2nd command
	
	for(i=0;i<10;i++); //wait tWB(100ns)//??????

	NF_WAITRB();	// Wait tBERS max 3ms.
	NF_CMD(0x70);	// Read status command

	if (NF_RDDATA()&0x1) // Erase error
	{	
		NF_nFCE_H();
		return 0;
	}
	else 
	{
		NF_nFCE_H();
		return 1;
	}
}

