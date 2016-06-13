/************************************************************************
*实现UART下载功能
*版本 V1.0
*创建人：YJ
*
*************************************************************************/
//#include <stdlib.h>
#include "lpc_types.h"
#include "download.h"
#include "debug_frmwrk.h"

uint32_t download_addr,download_len;

int32_t LoadFromUart( int argc)
{
	int32_t i, size;
	uint16_t CheckSum,ref_chksum=0;
	uint8_t * buf = ( uint8_t * ) DFT_DOWNLOAD_ADDR;
	uint8_t RxTmp[8];

	if ( argc < 2 )
		download_addr = DFT_DOWNLOAD_ADDR;

	buf = ( uint8_t * ) download_addr;

	put_str_( "Now download file from uart0 to 0x%x...\n");

	i = 0;
	while ( i < 4 )
		RxTmp[i++] = getchar();

	i = 0;
	size = *( uint32_t * ) RxTmp - 4;
	while ( i < size )
		buf[i++] = getchar();

	download_len = size - 2;	
	ref_chksum  = (buf[size-1]<<8)|buf[size-2];
	ref_chksum  = ref_chksum;
	CheckSum = 0;

	for (size -= 3;size>=0;size--)
		CheckSum += buf[size];

	if ( ref_chksum != CheckSum )
	{
		put_str_( "\nCheckSum error!\n" );
		download_len = -1;
		return FALSE;
	}
	else {
		put_str_( "\nReceived bytes success\n");
		return TRUE;
		}

}



