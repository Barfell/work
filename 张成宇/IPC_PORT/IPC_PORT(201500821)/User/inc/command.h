#ifndef __COMMAND_H
#define __COMMAND_H


#define	Usart1Command_Buf_Size	    4096
#define	Usart2Command_Buf_Size	    4096


//USART1 Receive user command struct
typedef struct
{
	u32	In1;								/* USART1_Buf RX Data In */
	u32 Count1;								/* USART1 RX Data count */
	u32 Out1;								/* USART1 RX Data out */
	u32 Buf_P1;								/* USART1_Buf Pointer */
	u16 Length1;							/* command length */
	u8	ID1;								/* command ID */
	u8	CMDState1;							/* status */
	u8	CMDBuf_In1;							/* CMDBuf in1 */
    char	CMDBuf1[100];					/* CMDBuf1 */
	u8	Buf1[Usart1Command_Buf_Size];		/* USART1_Buf */	
}Usart1CommandTypeDef;

//USART2 Receive user command struct
typedef struct
{
	u32	In2;								/* USART2_Buf RX Data In */
	u32 Count2;								/* USART2 RX Data count */
	u32 Out2;								/* USART2 RX Data out */
	u32 Buf_P2;								/* USART2_Buf Pointer */
	u16 Length2;							/* command length */
	u8	ID2;								/* command ID */
	u8	CMDState2;							/* status */
	u8	CMDBuf_In2;							/* CMDBuf in2 */
    char	CMDBuf2[100];					/* CMDBuf2 */
	u8	Buf2[Usart2Command_Buf_Size];		/* USART2_Buf */	
}Usart2CommandTypeDef;


extern	Usart1CommandTypeDef		Usart1Command;
extern	Usart2CommandTypeDef		Usart2Command;

extern void Process_Usart1Command(void);
extern void Process_Usart2Command(void);

#endif
