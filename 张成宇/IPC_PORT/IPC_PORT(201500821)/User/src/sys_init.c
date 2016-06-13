/******************** (C) COPYRIGHT 2012 SystemIntegration *********************
* �ļ�����: sys.c
* ��������: Dyj
* ����汾: V0.0.1
* ��������: 06/14/2012
* ��������: ϵͳӲ����ʼ��.
*******************************************************************************/



#include "stm32f10x.h"
#include "sys_init.h"
#include "command.h"
#include <stdio.h>
#include <string.h>


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{

	SystemInit();//Դ��system_stm32f10x.c�ļ�,ֻ��Ҫ���ô˺���,������RCC������.�����뿴2_RCC

	//SYSTICK��Ƶ--0.1ms��ϵͳʱ���ж�
	if (SysTick_Config(SystemFrequency / 10000))
  	{ 
  	  	//Capture error  
    	while (1);
  	}

	/*ʹ�����š�����1������2ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | 
	RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);	
    
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location�ж����ȼ�����.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	  
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); 
	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	  
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USART1 Interrupt */	 
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the EXTI1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	
	/*�������ж���������*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//12
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	   
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports,USART,and so on
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	/* MCU��Դ�������� MCU_PWR  PA12 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* ��ⰴ���Ƿ������� KEY_Press PA11  ����ʱΪ�ߵ�ƽ */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//��������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ��⹤�������Դʹ�ܵ�ѹ���� POWER_ON  PB6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//��������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);



	/* ������-----------------------------#  PB12 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	


	/* ��⹤�����帴λ���� RESET#  PB7 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//��������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	/* ���ذ��Դ�������� IPCPWR_CTRL  PB1 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*��Դ�ƿ������� LED_CTRL  PA8 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* MCU����3Gģ��UC864-E��������MCU_UC864PWRON PD3 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* MCU����3Gģ��UC864-E��λ����MCU_UC864PWRON PD4 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure USART1 Rx (PA.10) as input floating */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART2 Rx (PA.03) as input floating */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : USART_Baud_Rate
* Description    : �趨���ڲ�����.
* Input          : USARTx: USART1, USART2, USART3, UART4 or UART5.
*                  rate:This parameter can be: 4800 9600 19200 38400 57600 115200.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Baud_Rate(USART_TypeDef* USARTx,u32 rate)	
{
	USART_InitTypeDef USART_InitStructure;

  	USART_InitStructure.USART_BaudRate = rate;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure USARTx */
  	USART_Init(USARTx, &USART_InitStructure);
}

/*******************************************************************************
* Function Name  : USARTx_RX_IT_Cmd
* Description    : �Ƿ������ڽ����ж�.
* Input          : USARTx: USART1, USART2, USART3, UART4 or UART5.
*                  NewState:This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USARTx_RX_IT_Cmd(USART_TypeDef* USARTx,FunctionalState NewState)
{
    USART_ITConfig(USARTx, USART_IT_RXNE, NewState);
    /*�������жϺ�Ҫ���־�������һ�������п��ܳ���*/
    USART_ClearFlag(USARTx, USART_FLAG_TC);
	USART_ClearFlag(USARTx,USART_IT_RXNE);	    
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configures the USART1.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(void)
{
	USART_ClockInitTypeDef USART_ClockInitStructure;

	/*����USART1������Ϊ115200*/
    USART_Baud_Rate(USART1,115200);
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
    /* Enable the USARTx */
    USART_Cmd(USART1, ENABLE);
	/* Enable the USARTx rx it*/
	USARTx_RX_IT_Cmd(USART1, ENABLE);

	/*����USART2������Ϊ115200*/
    USART_Baud_Rate(USART2,115200);
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART2, &USART_ClockInitStructure);
    /* Enable the USARTx */
    USART_Cmd(USART2, ENABLE);
	/* Enable the USARTx rx it*/
	USARTx_RX_IT_Cmd(USART2, ENABLE);

}

/*******************************************************************************
* Function Name  : EXIT_Configuration
* Description    : EXIT_Configuration.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXIT_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1;				//�����ⲿ�ж���·
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//ʹ��EXTI��·Ϊ�ж�����ģʽ
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//����������·�½���Ϊ�ж�����
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line1);						//EXTI��·����һ�����ж�
	
	//pb12---������ 
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;				
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//EXTI_GenerateSWInterrupt(EXTI_Line12);						
	
}

/*******************************************************************************
* Function Name  : Clear_User_Buf_Flag
* Description    : ������ڻ�������־.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Clear_User_Buf_Flag(void)
{
	Usart1Command.In1 = 0;
	Usart2Command.In2 = 0;
	Usart1Command.Out1 = 0;
	Usart2Command.Out2 = 0;
	Usart1Command.Count1 = 0;
	Usart2Command.Count2 = 0;
	Usart1Command.Buf_P1 = 0;
	Usart2Command.Buf_P2 = 0;
	Usart1Command.CMDState1 = 0;
	Usart2Command.CMDState2 = 0;
}

/*******************************************************************************
* Function Name  : System_Init
* Description    : Ƭ��Ӳ����ʼ��.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void System_Init(void)
{
	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	EXIT_Configuration();
	Clear_User_Buf_Flag();
	OPEN_PWR();
	OPEN_IPCPWR();
	LED_ON();
    printf("\r\n");
	printf("\r\n****************************************");
	printf("\r\n*                                      *");
    printf("\r\n*            Fireware V0.0.1           *");
	printf("\r\n*                                      *");
	printf("\r\n****************************************");
	printf("\r\n");
	printf("\r\n");
}

