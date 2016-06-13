#include "kernel.h" 

STATIC volatile U32 g_u32TickCount = 0;
STATIC volatile U32 g_u32Second = 0;


VOID SysTick_Handler(VOID)
{
    g_u32TickCount ++; 

    if(g_u32TickCount%1000 == 0)
    {
		g_u32Second++;
    }
}


U32 GetSecondOfWeek(VOID)
{
    return g_u32Second;
}

VOID SetSecondOfWeek(U32 u32Cnt)
{
    g_u32Second = u32Cnt;
}

STATIC VOID RCC_Configuration(VOID)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);


  if(RCC_WaitForHSEStartUp() == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* ADCCLK = PCLK2/4 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  
    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

}

VOID OsInit(VOID)
{
    /*!< At this stage the microcontroller clock setting is already configured, 
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f10x_xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f10x.c file
	*/      

	/* Setup SysTick Timer for 1 msec interrupts.
	------------------------------------------
	1. The SysTick_Config() function is a CMSIS function which configure:
	- The SysTick Reload register with value passed as function parameter.
	- Configure the SysTick IRQ priority to the lowest value (0x0F).
	- Reset the SysTick Counter register.
	- Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
	- Enable the SysTick Interrupt.
	- Start the SysTick Counter.

	2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
	SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
	inside the misc.c file.

	3. You can change the SysTick IRQ priority by calling the
	NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
	call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

	4. To adjust the SysTick time base, use the following formula:

	Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)

	- Reload Value is the parameter to be passed for SysTick_Config() function
	- Reload Value should not exceed 0xFFFFFF
	*/
	if (SysTick_Config(SystemCoreClock / 1000))	   //这里使得没个TimeDelay的值延时1us,如果要延时1ms则相应的除以1000就可以了
	{ 
		/* Capture error */ 
		while (1);
	} 
	
	RCC_Configuration();
    
}



U32 GetTickCount(VOID)
{
    return g_u32TickCount;
}


VOID DelayMs(U32 nTime)
{ 
	volatile U32 u32Tick;	
	u32Tick = nTime + g_u32TickCount;
	do
    {
		__nop();
		
    }while(g_u32TickCount < u32Tick);

}

//SOFT
VOID DelayMs_Sft(U32 nTime)
{ 
   
    DelayUs_Sft(nTime*1000);
}
//SOFT
VOID DelayUs_Sft(U32 nTime)
{ 
    U32 u32Cnt, u32Count;
    
	for(u32Count = 0; u32Count < nTime; u32Count++)
	{
		for(u32Cnt = 0; u32Cnt < 5; u32Cnt++);
	}

}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm VOID WFI_SET(VOID)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm VOID INTX_DISABLE(VOID)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm VOID INTX_ENABLE(VOID)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm VOID MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}


VOID NMI_Handler(VOID)
{
}

EXTERN VOID WriteFlashFlag(VOID);

VOID HardFault_Handler(VOID)
{
    /* Go to infinite loop when Hard Fault exception occurs */
	printf("hard fault \r\n");
	DelayMs_Sft(1000);
	NVIC_SystemReset();
   
}


VOID MemManage_Handler(VOID)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

VOID BusFault_Handler(VOID)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}


VOID UsageFault_Handler(VOID)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

VOID SVC_Handler(VOID)
{
}

VOID DebugMon_Handler(VOID)
{
}

VOID PendSV_Handler(VOID)
{
}

VOID EnterException(U32 u32ErrCode)
{
	printf("error code = %x \r\n", u32ErrCode);
	DelayMs(1000);
	
	DelayMs_Sft(1000);
	NVIC_SystemReset(); 
    
}
