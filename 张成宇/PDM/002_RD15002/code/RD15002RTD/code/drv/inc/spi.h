#ifndef __SPI_H                           /* avoid multiple inclusion */
#define __SPI_H

#include "kernal.h"

typedef struct _tagSpiInfo
{
    SPI_TypeDef* pSPIx;
    SPI_InitTypeDef* pSPI_InitStruct;
    BOOL SPI_EnableTxInt;
    BOOL SPI_EnableRxInt;
    
    //pin
    U16 SPI_PinRx;
    U16 SPI_PinTx;
    U16 SPI_PinClk;
    U16 SPI_PinNss;
   
    //gio
    GPIO_TypeDef* SPI_PinRxGpio;
    GPIO_TypeDef* SPI_PinTxGpio;
    GPIO_TypeDef* SPI_PinClkGpio;
    GPIO_TypeDef* SPI_PinNssGpio; 
   
    U32 SPI_Clk;
    U32 SPI_NssGpioClk;
    U32 SPI_RxGpioClk;
    U32 SPI_TxGpioClk;
    U32 SPI_ClkGpioClk;
    U32 SPI_APB2PeriphAfioClk;
   
   
    U8 SPI_IRQChannel;
    U8 SPINss_IRQChannel;
   		
}CSpiInfo, *PSpiInfo;

VOID SpiCreate(SPI_TypeDef* pSPIx,SPI_InitTypeDef* pSPI_InitStruct, BOOL EnableTxInt, BOOL EnableRxInt);
VOID SpiOpen(SPI_TypeDef *pSPIx);
VOID SpiClose(SPI_TypeDef *pSPIx);
VOID SpiSetSpeed(SPI_TypeDef *pSPIx, U8 SPI_BaudRatePrescaler);
U8 SpiReadWriteByte(SPI_TypeDef *pSPIx, U8 TxData);


EXTERN PSpiInfo pSpi1Info;
EXTERN PSpiInfo pSpi2Info;

#endif
