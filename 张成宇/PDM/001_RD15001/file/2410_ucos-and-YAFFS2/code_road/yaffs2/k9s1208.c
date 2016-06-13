#include <string.h>
#include "def.h"
#include "option.h"
#include "2410addr.h"
//#include "2410lib.h"
//#include "2410slib.h" 


#define BAD_CHECK	(0)
#define ECC_CHECK	(0)

void K9S1208_Program(U32 blockIndex, U32 srcAddress, U32 fileSize);

//*************** H/W dependent functions ***************
U16 NF_CheckId(void);
int NF_EraseBlock(U32 blockNum);
int NF_ReadPage(U32 block,U32 page,U8 *buffer);
int NF_WritePage(U32 block,U32 page,U8 *buffer);
	//buffer size is 512 bytes
static int NF_IsBadBlock(U32 block);
static int NF_MarkBadBlock(U32 block);
static void NF_Reset(void);

void NF_Init(void);
//*******************************************************


void K9S1208_Program(U32 block, U32 srcAddress, U32 fileSize)
{
    int i;
    int programError=0;
    U32 blockIndex;
    U8 *srcPt,*saveSrcPt;

    srcPt=(U8 *)srcAddress;
     blockIndex = block;
    while(1)
    {
        saveSrcPt=srcPt;	

#if BAD_CHECK       
	if(NF_IsBadBlock(blockIndex))	// 1:bad 0:good
        {
	    blockIndex++;   // for next block
	    continue;
	}
#endif
	if(!NF_EraseBlock(blockIndex))
	{
	    blockIndex++;   // for next block
	    continue;
	}
	    
	for(i=0;i<32;i++)
	{
	    if(!NF_WritePage(blockIndex,i,srcPt))// block num, page num, buffer
	    {
	        programError=1;
	        break;
	    }
#if ECC_CHECK    
	    if(!NF_ReadPage(blockIndex,i,srcPt))
	    {
//		Uart_Printf("ECC Error(block=%d,page=%d!!!\n",blockIndex,i);
	    }
#endif	    
		srcPt+=512;	// Increase buffer addr one pase size
	    if((U32)srcPt>=(srcAddress+fileSize)) // Check end of buffer
		break;	// Exit for loop
	}
        if(programError==1)
	{
	    blockIndex++;
	    srcPt=saveSrcPt;
	    programError=0;
	    continue;
	}
	if((U32)srcPt>=(srcAddress+fileSize))
	    break;	// Exit while loop
	blockIndex++;
    }
}

//*************************************************
//*************************************************
//**           H/W dependent functions           **
//************************************************* 
//*************************************************

//The code is made for bi-endian mode

// block0: reserved for boot strap
// block1~4095: used for OS image
// badblock SE: xx xx xx xx xx 00 ....
// good block SE: ECC0 ECC1 ECC2 FF FF FF ....

#define WRITEVERIFY  (0)  //verifing is enable at writing.

/*
#define FC_CMD()    {rPDATA|=CLE;rPDATA&=~(ALE|CE);}
#define FC_ADDR()   {rPDATA|=ALE;rPDATA&=~(CLE|CE);}
#define FC_DATA()   {rPDATA&=~(ALE|CLE|CE);}
#define FC_INACTIVE() {rPDATA|=CE;rPDATA&=~(ALE|CLE);}
*/

#define NF_CMD(cmd)	{rNFCMD=cmd;}
#define NF_ADDR(addr)	{rNFADDR=addr;}	
#define NF_nFCE_L()	{rNFCONF&=~(1<<11);}
#define NF_nFCE_H()	{rNFCONF|=(1<<11);}
#define NF_RSTECC()	{rNFCONF|=(1<<12);}
#define NF_RDDATA() 	(rNFDATA)
#define NF_WRDATA(data) {rNFDATA=data;}

#define NF_WAITRB()    {while(!(rNFSTAT&(1<<0)));} 
	    //wait tWB and check F_RNB pin.   

#define ID_K9S1208V0M	0xec76

#if 1
// HCLK=100Mhz
#define TACLS		0  //1clk(0ns) 
#define TWRPH0		3  //3clk(25ns)
#define TWRPH1		0  //1clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns
#else
// HCLK=50Mhz
#define TACLS		0  //1clk(0ns)
#define TWRPH0		1  //2clk(25ns)
#define TWRPH1		0  //1clk(10ns)
#endif


static U8 seBuf[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

// 1block=(512+16)bytes x 32pages
// 4096block

// A[23:14][13:9]
//  block   page

int NF_EraseBlock(U32 block)
{
    U32 blockPage=(block<<5);
    int i;

#if BAD_CHECK
    if(NF_IsBadBlock(block))
	return 0;
#endif

    NF_nFCE_L();
    
    NF_CMD(0x60);   // Erase one block 1st command

    NF_ADDR(blockPage&0xff);	    // Page number=0
    NF_ADDR((blockPage>>8)&0xff);   
    NF_ADDR((blockPage>>16)&0xff);

    NF_CMD(0xd0);   // Erase one blcok 2nd command
    
   for(i=0;i<10;i++); //wait tWB(100ns)//??????

    NF_WAITRB();    // Wait tBERS max 3ms.
    NF_CMD(0x70);   // Read status command

    if (NF_RDDATA()&0x1) // Erase error
    {	
    	NF_nFCE_H();
//	Uart_Printf("[ERASE_ERROR:block#=%d]\n",block);
	NF_MarkBadBlock(block);
	return 0;
    }
    else 
    {
    	NF_nFCE_H();
        return 1;
    }
}


static int NF_IsBadBlock(U32 block)
{
    int i;
    unsigned int blockPage;
    U8 data;
    
    
    blockPage=(block<<5);	// For 2'nd cycle I/O[7:5] 
    
    NF_nFCE_L();    
    NF_CMD(0x50);		// Spare array read command
    NF_ADDR(517&0xf);		// Read the mark of bad block in spare array(M addr=5) 
    NF_ADDR(blockPage&0xff);	// The mark of bad block is in 0 page
    NF_ADDR((blockPage>>8)&0xff);   // For block number A[24:17]
    NF_ADDR((blockPage>>16)&0xff);  // For block number A[25]

   for(i=0;i<10;i++);	// wait tWB(100ns) //?????
    
    NF_WAITRB();	// Wait tR(max 12us)
    
    data=NF_RDDATA();

    NF_nFCE_H();    

    if(data!=0xff)
    {
 //   	Uart_Printf("[block %d has been marked as a bad block(%x)]\n",block,data);
    	return 1;
    }
    else
    {
    	return 0;
    }
}


static int NF_MarkBadBlock(U32 block)
{
    int i;
    U32 blockPage=(block<<5);
 
    seBuf[0]=0xff;
    seBuf[1]=0xff;    
    seBuf[2]=0xff;    
    seBuf[5]=0x44;   // Bad blcok mark=0
    
    NF_nFCE_L(); 
    NF_CMD(0x50);   //????
    NF_CMD(0x80);   // Write 1st command
    
    NF_ADDR(0x0);		    // The mark of bad block is 
    NF_ADDR(blockPage&0xff);	    // marked 5th spare array 
    NF_ADDR((blockPage>>8)&0xff);   // in the 1st page.
    NF_ADDR((blockPage>>16)&0xff);  //
    
    for(i=0;i<16;i++)
    {
	NF_WRDATA(seBuf[i]);	// Write spare array
    }

    NF_CMD(0x10);   // Write 2nd command
    
    for(i=0;i<10;i++);  //tWB = 100ns. ///???????

    NF_WAITRB();      // Wait tPROG(200~500us)
  
    NF_CMD(0x70);
    
    for(i=0;i<3;i++);  //twhr=60ns////??????
    
    if (NF_RDDATA()&0x1) // Spare arrray write error
    {	
    	NF_nFCE_H();
  //  	Uart_Printf("[Program error is occurred but ignored]\n");
    }
    else 
    {
    	NF_nFCE_H();
    }

 //   Uart_Printf("[block #%d is marked as a bad block]\n",block);
    return 1;
}


int NF_ReadPage(U32 block,U32 page,U8 *buffer)
{
    int i;
    unsigned int blockPage;
    U8 ecc0,ecc1,ecc2;
    U8 *bufPt=buffer;
    U8 se[16];	   
    
    page=page&0x1f;
    blockPage=(block<<5)+page;
    NF_RSTECC();    // Initialize ECC
    
    NF_nFCE_L();    
    NF_CMD(0x00);   // Read command
    NF_ADDR(0);	    // Column = 0
    NF_ADDR(blockPage&0xff);	    //
    NF_ADDR((blockPage>>8)&0xff);   // Block & Page num.
    NF_ADDR((blockPage>>16)&0xff);  //

    for(i=0;i<10;i++); //wait tWB(100ns)/////??????
    
    NF_WAITRB();    // Wait tR(max 12us)
    for(i=0;i<512;i++)
    {
    	*bufPt++=NF_RDDATA();	// Read one page
    }
    ecc0=rNFECC0;
    ecc1=rNFECC1;
    ecc2=rNFECC2;
    for(i=0;i<16;i++)
    {
    	se[i]=NF_RDDATA();	// Read spare array
    }
    
    //__RdPage528(pPage);
    NF_nFCE_H();    

    if(ecc0==se[0] && ecc1==se[1] && ecc2==se[2])
    {
	//Uart_Printf("[ECC OK:%x,%x,%x]\n",se[0],se[1],se[2]);
    	return 1;
    }
    else
    {
	//Uart_Printf("[ECC ERROR(RD):read:%x,%x,%x, reg:%x,%x,%x]\n",
	//	se[0],se[1],se[2],ecc0,ecc1,ecc2);
    	return 0;
    }    	
}


int NF_WritePage(U32 block,U32 page,U8 *buffer)
{
    int i;
    U32 blockPage=(block<<5)+page;
    U8 *bufPt=buffer;

    NF_RSTECC();    // Initialize ECC
    
    NF_nFCE_L(); 
    NF_CMD(0x0);//??????
    NF_CMD(0x80);   // Write 1st command
    NF_ADDR(0);			    // Column 0
    NF_ADDR(blockPage&0xff);	    //
    NF_ADDR((blockPage>>8)&0xff);   // Block & page num.
    NF_ADDR((blockPage>>16)&0xff);  //

    for(i=0;i<512;i++)
    {
	NF_WRDATA(*bufPt++);	// Write one page to NFM from buffer
    }  
    
    seBuf[0]=rNFECC0;
    seBuf[1]=rNFECC1;
    seBuf[2]=rNFECC2;
    seBuf[5]=0xff;		// Marking good block
    
    for(i=0;i<16;i++)
    {
	NF_WRDATA(seBuf[i]);	// Write spare array(ECC and Mark)
    }  

    NF_CMD(0x10);   // Write 2nd command
    
    for(i=0;i<10;i++);  //tWB = 100ns. ////??????

    NF_WAITRB();    //wait tPROG 200~500us;
 
    NF_CMD(0x70);   // Read status command   
    
    for(i=0;i<3;i++);  //twhr=60ns
    
    if (NF_RDDATA()&0x1) // Page write error
    {	
    	NF_nFCE_H();
	//Uart_Printf("[PROGRAM_ERROR:block#=%d]\n",block);
	NF_MarkBadBlock(block);
	return 0;
    }
    else 
    {
    	NF_nFCE_H();
    #if (WRITEVERIFY==1)
	//return NF_VerifyPage(block,page,pPage);	
    #else
	return 1;
    #endif
    }
}



U16 NF_CheckId(void)
{
    int i;
    U16 id;
    
    NF_nFCE_L();
    NF_CMD(0x90);
    NF_ADDR(0x0);
    
    for(i=0;i<10;i++); //wait tWB(100ns)////?????
    
    id=NF_RDDATA()<<8;	// Maker code(K9S1208V:0xec)
    id|=NF_RDDATA();	// Devide code(K9S1208V:0x76)
    NF_nFCE_H();
    return id;
}
static void NF_Reset(void)
{
    int i;
    U16 id;
    
    
    NF_nFCE_L();

    NF_CMD(0xFF);	//reset command

    for(i=0;i<10;i++);  //tWB = 100ns. //??????
    NF_WAITRB();      //wait 200~500us;
    NF_nFCE_H();
}



void NF_Init(void)
{
    rNFCONF=(1<<15)|(1<<14)|(1<<13)|(1<<12)|(1<<11)|(TACLS<<8)|(TWRPH0<<4)|(TWRPH1<<0);	
    // 1  1    1     1,   1      xxx,  r xxx,   r xxx        
    // En 512B 4step ECCR nFCE=H tACLS   tWRPH0   tWRPH1
    
    NF_Reset();
}
