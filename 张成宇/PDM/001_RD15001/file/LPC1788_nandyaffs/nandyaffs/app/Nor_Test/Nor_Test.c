#include "bsp.h"
#include "lpc_types.h"
#include "SST39VF6401.h"
#include "debug_frmwrk.h"

uint8_t Nor_RW_test(uint32_t offset_adr){
	volatile uint16_t i,*buf;
	uint32_t R_adr,W_adr;
		R_adr = offset_adr;
		W_adr = offset_adr;
	if(!Erase_Entire_Chip())
		put_str_("Erase Entire chip fail!");
   for(i=1;i<=SECTOR_SIZE;i++){
	 Program_One_uint16_t(&i,W_adr);
	 W_adr++;
   }
   put_str_("write data to nor flash finish!");

   for(i=1;i<=SECTOR_SIZE;i++){
	 buf = sysAddress(R_adr);
	 if(*buf != i){
	 put_str_("Verifying fail, testing terminated!");
	 return 0;
	 }
	 R_adr++;
   }

  	put_str_("Verifying success, testing terminated!");
	return 1;
}
