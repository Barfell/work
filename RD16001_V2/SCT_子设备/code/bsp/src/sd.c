#include "msp430.h"
#include "sd.h"
#include "kernel.h"
#include "stdio.h"

#define VREF 0.600

void SDInit(void)
{
  unsigned long int i = 0;
  SD16CTL = SD16SSEL_1 + SD16DIV_3 + SD16REFON;       //SD16REFON +      // 1.2V ref, SMCLK mclk/16《内部电压基准》
  SD16CCTL1 |= SD16SNGL;
  SD16CCTL2 |= SD16SNGL;                        // Single conv
  SD16CCTL3 |= SD16SNGL;
  SD16CCTL4 |= SD16SNGL;
  SD16CCTL5 |= SD16SNGL;
  for (i = 0; i < 0x36000; i++);                // Delay for 1.2V ref startup
  for (i = 0; i < 0x36000; i++);
  for (i = 0; i < 0x36000; i++);
  for (i = 0; i < 0x36000; i++);
}


void SDOff(void)
{

  SD16CTL &= ~SD16SSEL_1;
  SD16CTL &= ~SD16DIV_3;
  SD16CTL &= ~SD16REFON;    
  
  
  SD16CCTL1 &= ~SD16SNGL;
  SD16CCTL2 &= ~SD16SNGL;                       
  SD16CCTL3 &= ~SD16SNGL;
  SD16CCTL4 &= ~SD16SNGL;
  SD16CCTL5 &= ~SD16SNGL;

}


float GetSD16Voltage(unsigned char ch)
{
  unsigned int results;
  float adc;
  switch(ch)
  {
    case 0:
      SD16CCTL0 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL0 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM0;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL0 &= ~SD16SC;
      break;
    case 1:
      SD16CCTL1 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL1 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM1;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL1 &= ~SD16SC;
      break;
    case 2:
      SD16CCTL2 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL2 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM2;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL2 &= ~SD16SC;
      break;
    case 3:
      SD16CCTL3 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL3 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM3;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL3 &= ~SD16SC;
      break;
    case 4:
      SD16CCTL4 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL4 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM4;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL4 &= ~SD16SC;
      break;
    case 5:
      SD16CCTL5 |= SD16SC + SD16UNI;       // Set bit to start conversion
      delay_ms(200);
      while ((SD16CCTL5 & SD16IFG)==0);       // Poll interrupt flag for CH5
      results  = SD16MEM5;                     // Save CH5 results (clears IFG)
      adc = ((float)results/(float)65535)*VREF;
      SD16CCTL5 &= ~SD16SC;
      break;
  }
  return adc;
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
