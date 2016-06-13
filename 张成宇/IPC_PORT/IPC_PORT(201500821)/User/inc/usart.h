#ifndef __USART_H
#define __USART_H


extern void USARTx_Putc(USART_TypeDef* USARTx,char c);
extern void USART_PutString(USART_TypeDef* USARTx, char *Buffer);
extern void USART_SendString(USART_TypeDef* USARTx, char *Buffer,u16 length);
extern void USART_SendWord(USART_TypeDef* USARTx, u32 DataWord);

#endif
