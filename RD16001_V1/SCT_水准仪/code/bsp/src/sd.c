#include "msp430.h"
#include "SD.h"
#include "stdio.h"


void SDInit(void)
{
  unsigned long int i = 0;
  SD16CTL = SD16SSEL_1 + SD16DIV_3;       //SD16REFON +      // 1.2V ref, SMCLK mclk/16
  SD16CCTL2 |= SD16SNGL;                        // Single conv
  for (i = 0; i < 0x36000; i++);                // Delay for 1.2V ref startup
  for (i = 0; i < 0x36000; i++);
  for (i = 0; i < 0x36000; i++);
  for (i = 0; i < 0x36000; i++);
}





#pragma vector=SD16A_VECTOR
__interrupt void SD16AISR(void)
{
//  static unsigned int index = 0;
//
//  switch (SD16IV)
//  {
//    case 2:                                   // SD16MEM Overflow
//      break;
//    case 4:                                   // SD16MEM0 IFG
//      break;
//    case 6:                                   // SD16MEM1 IFG
//      break;
//    case 8:                                   // SD16MEM2 IFG
//      results[index] = SD16MEM2;              // Save CH2 results (clears IFG)
//      if (++index == Num_of_Results)
//      {
//        index = 0;                            // SET BREAKPOINT HERE
//        printf("results[0]:%d\r\n",results[0]);
//        printf("results[1]:%d\r\n",results[1]);
//        printf("results[2]:%d\r\n",results[2]);
//        printf("results[3]:%d\r\n",results[3]);
//        printf("results[4]:%d\r\n",results[4]);
//        printf("results[5]:%d\r\n",results[5]);
//        printf("results[6]:%d\r\n",results[6]);
//        printf("results[7]:%d\r\n",results[7]);
//        
//      }
//      break;
//  }
}
