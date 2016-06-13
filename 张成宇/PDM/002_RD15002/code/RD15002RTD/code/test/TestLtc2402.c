#include "ltc2402.h"
#include "spi.h"
#include "tsa5017.h"

double ch1 = 0;
double ch0 = 0;
void TestLTC2402(void)
{
    u8 temp[4] = {0,};
    u8 EOC = 3;
    u32 Ltc2402buf = 0;
    double Ltc2402result = 0;
//    LTC2402Init();//60hz internal osc
//	SPI_InitTypeDef Spi_InitStruct;		
//	SpiCreate(LTC2402_SPI, &Spi_InitStruct, FALSE, FALSE);	
//	SpiOpen(LTC2402_SPI);
//	Tsa5017Init();
//	Tsa5017_CH2();
	Ltc2402SoftInit();



while(1)
	{   
        EOC = LTC2402_TEST_EOC_Start();
        if((EOC & 0x80) == 0)		
        {
			temp[0] = EOC;
            temp[1] = LTC2402_ReadByte();
            temp[2] = LTC2402_ReadByte();
            temp[3] = LTC2402_ReadByte();
			Ltc2402buf = ((temp[0]<<24)+(temp[1]<<16)+(temp[2]<<8)+(temp[3]<<0));
            Ltc2402buf = Ltc2402buf&0x0FFFFFF0;
            Ltc2402buf = Ltc2402buf >>4;
//				Ltc2402result = (((double)Ltc2402buf)/16777216.0)*3.298;
			Ltc2402result = (((double)Ltc2402buf)/16777216.0)*3.298;
			if(EOC & 0x40)
			{           
				printf("Channe1 Ltc2402buf = 0X%X\r\n",Ltc2402buf);
				printf("Channe1 resulf = %.6f\r\n",Ltc2402result);
//				ch1 = Ltc2402result;
				ch1=0;
            
			}
			else
			{
				printf("Channe0 Ltc2402buf = 0X%X\r\n",Ltc2402buf);
				printf("Channe0 resulf = %.6f\r\n",Ltc2402result);
				ch0 = Ltc2402result;
				
			}
			if(ch0 > ch1)
				printf("offset = %.6f\r\n",(ch0 - ch1));
			else
				printf("offset = %.6f\r\n",(ch1 - ch0));
			
			DelayMs(1000);

			temp[0] = 0;
			temp[1] = 0;
			temp[2] = 0;
			temp[3] = 0;
			
        }
		LTC2402_TEST_EOC_End();
		DelayMs(200);
        
	}
    
//	while(1)
//	{   
//        EOC = LTC2402_TEST_EOC();
//        if(EOC ==0)		
//        {
////            EOC = LTC2402_TEST_EOC();
////            printf("EOC = %d\r\n",EOC);
////            DelayMs(1000);
//            temp[0] = LTC2402_ReadByte();
//            temp[1] = LTC2402_ReadByte();
//            temp[2] = LTC2402_ReadByte();
//            temp[3] = LTC2402_ReadByte();
//            Ltc2402buf = ((temp[0]<<24)+(temp[1]<<16)+(temp[2]<<8)+(temp[3]<<0));
//            Ltc2402buf = Ltc2402buf&0x1FFFFFE0;
//            Ltc2402buf = Ltc2402buf >>5;
//            printf("Ltc2402buf = %d\r\n",Ltc2402buf);
//            Ltc2402result = (((double)Ltc2402buf)/16777216.0)*3.3;
//            DelayMs(1000);
//            printf("resulf = %.3f\r\n",Ltc2402result);
//        }
//        temp[0] = 0;
//        temp[1] = 0;
//        temp[2] = 0;
//        temp[3] = 0;
//	}
	
}

