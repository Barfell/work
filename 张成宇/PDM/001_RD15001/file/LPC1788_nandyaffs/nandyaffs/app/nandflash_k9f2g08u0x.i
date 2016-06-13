#line 1 "..\\Drivers\\nandflash_k9f2g08u0x.c"
 

















 
#line 1 "..\\app\\bsp.h"






















 
#line 1 "..\\Drivers\\lpc_types.h"
 



















 

 



 
#line 1 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"
 
 





 







 




  
 







#line 37 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 208 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"

     







     










     











#line 272 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"



 



#line 29 "..\\Drivers\\lpc_types.h"


 


 



 
typedef enum {FALSE = 0, TRUE = !FALSE} Bool;



 
typedef enum {RESET = 0, SET = !RESET} FlagStatus, IntStatus, SetState;




 
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;




 
typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;




 
typedef enum
{
	NONE_BLOCKING = 0,		 
	BLOCKING,				 
} TRANSFER_BLOCK_Type;


 
typedef void (*PFV)();

 
typedef int32_t(*PFI)();



 


 


 




 

 





 

 














 

 


 




 


 

 







 


 


 

 
typedef char CHAR;

 
typedef uint8_t UNS_8;

 
typedef int8_t INT_8;

 
typedef	uint16_t UNS_16;

 
typedef	int16_t INT_16;

 
typedef	uint32_t UNS_32;

 
typedef	int32_t INT_32;

 
typedef int64_t INT_64;

 
typedef uint64_t UNS_64;

 
typedef Bool BOOL_32;

 
typedef Bool BOOL_16;

 
typedef Bool BOOL_8;



 






 

 
#line 25 "..\\app\\bsp.h"











#line 1 "..\\Drivers\\phylan_dp83848c.h"
 


















 














 



 






 
#line 56 "..\\Drivers\\phylan_dp83848c.h"

 
#line 67 "..\\Drivers\\phylan_dp83848c.h"

 
#line 81 "..\\Drivers\\phylan_dp83848c.h"















#line 104 "..\\Drivers\\phylan_dp83848c.h"
















 



 


 




 


 



 








#line 37 "..\\app\\bsp.h"

















































extern void Delay (unsigned long tick);
void LED_ctr(uint8_t led_num,uint8_t on_off);

void Init_gpio_interrupt    (void);
void uninit_gpio_interrupt  (void);
void Easy_Web(void);
void Init_EMAC_Dp83848(void);

void Usb_MassStorage (void);
void USB_Dis_Connect (void);

void DAC_SineWave(void);
void DAC_SineWave_Dis(void);

int Pwm_Test_Beep(void);
void Pwm_Dis_Beep(void);
void Pwm_change_Freq(uint8_t state);

void Can_init(void);
void Can_Uninit(void);

uint8_t Nor_RW_test(uint32_t offset_adr);
uint8_t Nand_Test(void);

void rs485_tx_rx(void);
void rs485_tx_rx(void);



#line 21 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 1 "..\\Drivers\\nandflash_k9f2g08u0x.h"
 

















 




#line 1 "..\\Drivers\\lpc177x_8x_emc.h"
 

















 




#line 25 "..\\Drivers\\lpc177x_8x_emc.h"
#line 1 "..\\Startup\\LPC177x_8x.h"






















 









 

typedef enum IRQn
{
 
  NonMaskableInt_IRQn           = -14,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  Reserved0_IRQn                = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  MCI_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34,        
  UART4_IRQn                    = 35,        
  SSP2_IRQn                     = 36,        
  LCD_IRQn                      = 37,        
  GPIO_IRQn                     = 38,        
  PWM0_IRQn                     = 39,        
  EEPROM_IRQn                   = 40,        
} IRQn_Type;






 

 





#line 1 "..\\CM3_lib\\core_cm3.h"
 




















 






 


































 

 
 
 
 
 
 
 
 








 











#line 95 "..\\CM3_lib\\core_cm3.h"

















 

#line 121 "..\\CM3_lib\\core_cm3.h"





 


 





 
 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                          
}  NVIC_Type;
   





 
 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;

 












 






























 






 





















 









 


















 










































 









 









 














   





 
 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t RELOAD;                        
  volatile uint32_t CURR;                           
  volatile uint32_t CALIB;                         
} SysTick_Type;

 












 



 



 








   





 
 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;                          
  volatile const  uint32_t PID6;                          
  volatile const  uint32_t PID7;                          
  volatile const  uint32_t PID0;                          
  volatile const  uint32_t PID1;                          
  volatile const  uint32_t PID2;                          
  volatile const  uint32_t PID3;                          
  volatile const  uint32_t CID0;                          
  volatile const  uint32_t CID1;                          
  volatile const  uint32_t CID2;                          
  volatile const  uint32_t CID3;                          
} ITM_Type;

 



 
























 



 



 



 








   





 
 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;

 



 








   






 
 
typedef struct
{
  volatile const  uint32_t TYPE;                          
  volatile uint32_t CTRL;                          
  volatile uint32_t RNR;                           
  volatile uint32_t RBAR;                          
  volatile uint32_t RASR;                          
  volatile uint32_t RBAR_A1;                       
  volatile uint32_t RASR_A1;                       
  volatile uint32_t RBAR_A2;                       
  volatile uint32_t RASR_A2;                       
  volatile uint32_t RBAR_A3;                       
  volatile uint32_t RASR_A3;                       
} MPU_Type;

 









 









 



 









 



























   






 
 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;

 




































 






 






































   


 
#line 732 "..\\CM3_lib\\core_cm3.h"

#line 739 "..\\CM3_lib\\core_cm3.h"






   




 





#line 769 "..\\CM3_lib\\core_cm3.h"


 


 




#line 794 "..\\CM3_lib\\core_cm3.h"


 
 
 
 








 
extern uint32_t __get_PSP(void);








 
extern void __set_PSP(uint32_t topOfProcStack);








 
extern uint32_t __get_MSP(void);








 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 944 "..\\CM3_lib\\core_cm3.h"





 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}







 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1456 "..\\CM3_lib\\core_cm3.h"







 
 


 











 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          

  reg_value  =  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                    
  reg_value &= ~((0xFFFFul << 16) | (7ul << 8));              
  reg_value  =  (reg_value                       |
                (0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR =  reg_value;
}








 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) >> 8);    
}








 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}
















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 












 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if (ticks > (0xFFFFFFul << 0))  return (1);             

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->RELOAD  = (ticks & (0xFFFFFFul << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);   
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CURR   = 0;                                           
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL  = (1ul << 2) |
                   (1ul << 1)   |
                   (1ul << 0);                     
  return (0);                                                   
}






 





 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) |
                 (1ul << 2));                    
  __dsb(0);                                                      
  while(1);                                                     
}

   



 






 
 

extern volatile int ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1ul << 24))  &&       
      (((ITM_Type *) (0xE0000000))->TCR & (1ul << 0))                  &&       
      (((ITM_Type *) (0xE0000000))->TER & (1ul << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}










 
static __inline int ITM_ReceiveChar (void) {
  int ch = -1;                                

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}









 
static __inline int ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

   






   



 

 

 
#line 105 "..\\Startup\\LPC177x_8x.h"



 
 
 


#pragma anon_unions


 
typedef struct
{
  volatile uint32_t FLASHCFG;                    
       uint32_t RESERVED0[31];
  volatile uint32_t PLL0CON;                     
  volatile uint32_t PLL0CFG;                     
  volatile const  uint32_t PLL0STAT;                    
  volatile  uint32_t PLL0FEED;                    
       uint32_t RESERVED1[4];
  volatile uint32_t PLL1CON;                     
  volatile uint32_t PLL1CFG;                     
  volatile const  uint32_t PLL1STAT;                    
  volatile  uint32_t PLL1FEED;                    
       uint32_t RESERVED2[4];
  volatile uint32_t PCON;                        
  volatile uint32_t PCONP;                       
       uint32_t RESERVED3[14];
  volatile uint32_t EMCCLKSEL;                   
  volatile uint32_t CCLKSEL;                     
  volatile uint32_t USBCLKSEL;                   
  volatile uint32_t CLKSRCSEL;                   
  volatile uint32_t	CANSLEEPCLR;                 
  volatile uint32_t	CANWAKEFLAGS;                
       uint32_t RESERVED4[10];
  volatile uint32_t EXTINT;                      
       uint32_t RESERVED5[1];
  volatile uint32_t EXTMODE;                     
  volatile uint32_t EXTPOLAR;                    
       uint32_t RESERVED6[12];
  volatile uint32_t RSID;                        
       uint32_t RESERVED7[7];
  volatile uint32_t SCS;                         
  volatile uint32_t IRCTRIM;                     
  volatile uint32_t PCLKSEL;                     
       uint32_t RESERVED8[3];
  volatile uint32_t LCD_CFG;                     
       uint32_t RESERVED9[1];
  volatile uint32_t USBIntSt;                    
  volatile uint32_t DMAREQSEL;                   
  volatile uint32_t CLKOUTCFG;                   
  volatile uint32_t RSTCON0;                     
  volatile uint32_t RSTCON1;                     
       uint32_t RESERVED10[2];
  volatile uint32_t EMCDLYCTL;                   
  volatile uint32_t EMCCAL;                      
 } LPC_SC_TypeDef;

 
typedef struct
{
  volatile uint32_t P0_0;				 
  volatile uint32_t P0_1;
  volatile uint32_t P0_2;
  volatile uint32_t P0_3;
  volatile uint32_t P0_4;
  volatile uint32_t P0_5;
  volatile uint32_t P0_6;
  volatile uint32_t P0_7;

  volatile uint32_t P0_8;				 
  volatile uint32_t P0_9;
  volatile uint32_t P0_10;
  volatile uint32_t P0_11;
  volatile uint32_t P0_12;
  volatile uint32_t P0_13;
  volatile uint32_t P0_14;
  volatile uint32_t P0_15;

  volatile uint32_t P0_16;				 
  volatile uint32_t P0_17;
  volatile uint32_t P0_18;
  volatile uint32_t P0_19;
  volatile uint32_t P0_20;
  volatile uint32_t P0_21;
  volatile uint32_t P0_22;
  volatile uint32_t P0_23;

  volatile uint32_t P0_24;				 
  volatile uint32_t P0_25;
  volatile uint32_t P0_26;
  volatile uint32_t P0_27;
  volatile uint32_t P0_28;
  volatile uint32_t P0_29;
  volatile uint32_t P0_30;
  volatile uint32_t P0_31;

  volatile uint32_t P1_0;				 
  volatile uint32_t P1_1;
  volatile uint32_t P1_2;
  volatile uint32_t P1_3;
  volatile uint32_t P1_4;
  volatile uint32_t P1_5;
  volatile uint32_t P1_6;
  volatile uint32_t P1_7;

  volatile uint32_t P1_8;				 
  volatile uint32_t P1_9;
  volatile uint32_t P1_10;
  volatile uint32_t P1_11;
  volatile uint32_t P1_12;
  volatile uint32_t P1_13;
  volatile uint32_t P1_14;
  volatile uint32_t P1_15;

  volatile uint32_t P1_16;				 
  volatile uint32_t P1_17;
  volatile uint32_t P1_18;
  volatile uint32_t P1_19;
  volatile uint32_t P1_20;
  volatile uint32_t P1_21;
  volatile uint32_t P1_22;
  volatile uint32_t P1_23;

  volatile uint32_t P1_24;				 
  volatile uint32_t P1_25;
  volatile uint32_t P1_26;
  volatile uint32_t P1_27;
  volatile uint32_t P1_28;
  volatile uint32_t P1_29;
  volatile uint32_t P1_30;
  volatile uint32_t P1_31;

  volatile uint32_t P2_0;				 
  volatile uint32_t P2_1;
  volatile uint32_t P2_2;
  volatile uint32_t P2_3;
  volatile uint32_t P2_4;
  volatile uint32_t P2_5;
  volatile uint32_t P2_6;
  volatile uint32_t P2_7;

  volatile uint32_t P2_8;				 
  volatile uint32_t P2_9;
  volatile uint32_t P2_10;
  volatile uint32_t P2_11;
  volatile uint32_t P2_12;
  volatile uint32_t P2_13;
  volatile uint32_t P2_14;
  volatile uint32_t P2_15;

  volatile uint32_t P2_16;				 
  volatile uint32_t P2_17;
  volatile uint32_t P2_18;
  volatile uint32_t P2_19;
  volatile uint32_t P2_20;
  volatile uint32_t P2_21;
  volatile uint32_t P2_22;
  volatile uint32_t P2_23;

  volatile uint32_t P2_24;				 
  volatile uint32_t P2_25;
  volatile uint32_t P2_26;
  volatile uint32_t P2_27;
  volatile uint32_t P2_28;
  volatile uint32_t P2_29;
  volatile uint32_t P2_30;
  volatile uint32_t P2_31;

  volatile uint32_t P3_0;				 
  volatile uint32_t P3_1;
  volatile uint32_t P3_2;
  volatile uint32_t P3_3;
  volatile uint32_t P3_4;
  volatile uint32_t P3_5;
  volatile uint32_t P3_6;
  volatile uint32_t P3_7;

  volatile uint32_t P3_8;				 
  volatile uint32_t P3_9;
  volatile uint32_t P3_10;
  volatile uint32_t P3_11;
  volatile uint32_t P3_12;
  volatile uint32_t P3_13;
  volatile uint32_t P3_14;
  volatile uint32_t P3_15;

  volatile uint32_t P3_16;				 
  volatile uint32_t P3_17;
  volatile uint32_t P3_18;
  volatile uint32_t P3_19;
  volatile uint32_t P3_20;
  volatile uint32_t P3_21;
  volatile uint32_t P3_22;
  volatile uint32_t P3_23;

  volatile uint32_t P3_24;				 
  volatile uint32_t P3_25;
  volatile uint32_t P3_26;
  volatile uint32_t P3_27;
  volatile uint32_t P3_28;
  volatile uint32_t P3_29;
  volatile uint32_t P3_30;
  volatile uint32_t P3_31;

  volatile uint32_t P4_0;				 
  volatile uint32_t P4_1;
  volatile uint32_t P4_2;
  volatile uint32_t P4_3;
  volatile uint32_t P4_4;
  volatile uint32_t P4_5;
  volatile uint32_t P4_6;
  volatile uint32_t P4_7;

  volatile uint32_t P4_8;				 
  volatile uint32_t P4_9;
  volatile uint32_t P4_10;
  volatile uint32_t P4_11;
  volatile uint32_t P4_12;
  volatile uint32_t P4_13;
  volatile uint32_t P4_14;
  volatile uint32_t P4_15;

  volatile uint32_t P4_16;				 
  volatile uint32_t P4_17;
  volatile uint32_t P4_18;
  volatile uint32_t P4_19;
  volatile uint32_t P4_20;
  volatile uint32_t P4_21;
  volatile uint32_t P4_22;
  volatile uint32_t P4_23;

  volatile uint32_t P4_24;				 
  volatile uint32_t P4_25;
  volatile uint32_t P4_26;
  volatile uint32_t P4_27;
  volatile uint32_t P4_28;
  volatile uint32_t P4_29;
  volatile uint32_t P4_30;
  volatile uint32_t P4_31;

  volatile uint32_t P5_0;				 
  volatile uint32_t P5_1;
  volatile uint32_t P5_2;
  volatile uint32_t P5_3;
  volatile uint32_t P5_4;				 
} LPC_IOCON_TypeDef;

 
typedef struct
{
  volatile uint32_t DIR;
       uint32_t RESERVED0[3];
  volatile uint32_t MASK;
  volatile uint32_t PIN;
  volatile uint32_t SET;
  volatile  uint32_t CLR;
} LPC_GPIO_TypeDef;

typedef struct
{
  volatile const  uint32_t IntStatus;
  volatile const  uint32_t IO0IntStatR;
  volatile const  uint32_t IO0IntStatF;
  volatile  uint32_t IO0IntClr;
  volatile uint32_t IO0IntEnR;
  volatile uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  volatile const  uint32_t IO2IntStatR;
  volatile const  uint32_t IO2IntStatF;
  volatile  uint32_t IO2IntClr;
  volatile uint32_t IO2IntEnR;
  volatile uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;                      
  volatile uint32_t TCR;                     
  volatile uint32_t TC;                      
  volatile uint32_t PR;                      
  volatile uint32_t PC;                      
  volatile uint32_t MCR;                     
  volatile uint32_t MR0;                     
  volatile uint32_t MR1;                     
  volatile uint32_t MR2;                     
  volatile uint32_t MR3;                     
  volatile uint32_t CCR;                     
  volatile const  uint32_t CR0;                     
  volatile const  uint32_t CR1;					 
       uint32_t RESERVED0[2];
  volatile uint32_t EMR;                     
       uint32_t RESERVED1[12];
  volatile uint32_t CTCR;                    
} LPC_TIM_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;                      
  volatile uint32_t TCR;                     
  volatile uint32_t TC;                      
  volatile uint32_t PR;                      
  volatile uint32_t PC;                      
  volatile uint32_t MCR;                     
  volatile uint32_t MR0;                     
  volatile uint32_t MR1;                     
  volatile uint32_t MR2;                     
  volatile uint32_t MR3;                     
  volatile uint32_t CCR;                     
  volatile const  uint32_t CR0;                     
  volatile const  uint32_t CR1;					 
  volatile const  uint32_t CR2;					 
  volatile const  uint32_t CR3;					 
       uint32_t RESERVED0;
  volatile uint32_t MR4;					 
  volatile uint32_t MR5;					 
  volatile uint32_t MR6;					 
  volatile uint32_t PCR;					 
  volatile uint32_t LER;					 
       uint32_t RESERVED1[7];
  volatile uint32_t CTCR;					 
} LPC_PWM_TypeDef;

 




 

#line 471 "..\\Startup\\LPC177x_8x.h"
typedef struct
{
	union
	{
		volatile const  uint8_t  RBR;
		volatile  uint8_t  THR;
		volatile uint8_t  DLL;
		uint32_t RESERVED0;
	};
	union
	{
		volatile uint8_t  DLM;
		volatile uint32_t IER;
	};
	union
	{
		volatile const  uint32_t IIR;
		volatile  uint8_t  FCR;
	};
	volatile uint8_t  LCR;
	uint8_t  RESERVED1[7];
	volatile const  uint8_t  LSR;
	uint8_t  RESERVED2[7];
	volatile uint8_t  SCR;
	uint8_t  RESERVED3[3];
	volatile uint32_t ACR;
	volatile uint8_t  ICR;
	uint8_t  RESERVED4[3];
	volatile uint8_t  FDR;
	uint8_t  RESERVED5[7];
	volatile uint8_t  TER;
	uint8_t  RESERVED8[27];
	volatile uint8_t  RS485CTRL;
	uint8_t  RESERVED9[3];
	volatile uint8_t  ADRMATCH;
	uint8_t  RESERVED10[3];
	volatile uint8_t  RS485DLY;
	uint8_t  RESERVED11[3];
	volatile const  uint8_t  FIFOLVL;
}LPC_UART_TypeDef;



typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  MCR;
       uint8_t  RESERVED2[3];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  volatile const  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  SCR;
       uint8_t  RESERVED5[3];
  volatile uint32_t ACR;
       uint32_t RESERVED6;
  volatile uint32_t FDR;
       uint32_t RESERVED7;
  volatile uint8_t  TER;
       uint8_t  RESERVED8[27];
  volatile uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  volatile uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  volatile uint8_t  RS485DLY;
       uint8_t  RESERVED11[3];
  volatile const  uint8_t  FIFOLVL;
} LPC_UART1_TypeDef;

typedef struct
{
  union {
  volatile const  uint32_t  RBR;                    
  volatile  uint32_t  THR;                    
  volatile uint32_t  DLL;                    
  };
  union {
  volatile uint32_t  DLM;                    
  volatile uint32_t  IER;                    
  };
  union {
  volatile const  uint32_t  IIR;                    
  volatile  uint32_t  FCR;                    
  };
  volatile uint32_t  LCR;                    
  volatile uint32_t  MCR;                    
  volatile const  uint32_t  LSR;                    
  volatile const  uint32_t  MSR;                    
  volatile uint32_t  SCR;                    
  volatile uint32_t  ACR;                    
  volatile uint32_t  ICR;                    
  volatile uint32_t  FDR;                    
  volatile uint32_t  OSR;                    
  volatile  uint32_t  POP;                    
  volatile uint32_t  MODE;                   
       uint32_t  RESERVED0[2];
  volatile uint32_t  HDEN;                   
       uint32_t  RESERVED1;
  volatile uint32_t  SCI_CTRL;				 
  volatile uint32_t  RS485CTRL;              
  volatile uint32_t  ADRMATCH;               
  volatile uint32_t  RS485DLY;               
  volatile uint32_t  SYNCCTRL;               
  volatile uint32_t  TER;                    
       uint32_t  RESERVED2[989];
  volatile const  uint32_t  CFG;                    
  volatile  uint32_t  INTCE;                  
  volatile  uint32_t  INTSE;                  
  volatile const  uint32_t  INTS;                   
  volatile const  uint32_t  INTE;                   
  volatile  uint32_t  INTCS;                  
  volatile  uint32_t  INTSS;                  
       uint32_t  RESERVED3[3];
  volatile const  uint32_t  MID;                    
} LPC_UART4_TypeDef;

 
typedef struct
{
  volatile uint32_t CR0;                     
  volatile uint32_t CR1;                     
  volatile uint32_t DR;                      
  volatile const  uint32_t SR;                      
  volatile uint32_t CPSR;                    
  volatile uint32_t IMSC;                    
  volatile uint32_t RIS;                     
  volatile uint32_t MIS;                     
  volatile uint32_t ICR;                     
  volatile uint32_t DMACR;
} LPC_SSP_TypeDef;

 
typedef struct
{
  volatile uint32_t CONSET;                  
  volatile const  uint32_t STAT;                    
  volatile uint32_t DAT;                     
  volatile uint32_t ADR0;                    
  volatile uint32_t SCLH;                    
  volatile uint32_t SCLL;                    
  volatile  uint32_t CONCLR;                  
  volatile uint32_t MMCTRL;                  
  volatile uint32_t ADR1;                    
  volatile uint32_t ADR2;                    
  volatile uint32_t ADR3;                    
  volatile const  uint32_t DATA_BUFFER;             
  volatile uint32_t MASK0;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t MASK3;                   
} LPC_I2C_TypeDef;

 
typedef struct
{
  volatile uint32_t DAO;
  volatile uint32_t DAI;
  volatile  uint32_t TXFIFO;
  volatile const  uint32_t RXFIFO;
  volatile const  uint32_t STATE;
  volatile uint32_t DMA1;
  volatile uint32_t DMA2;
  volatile uint32_t IRQ;
  volatile uint32_t TXRATE;
  volatile uint32_t RXRATE;
  volatile uint32_t TXBITRATE;
  volatile uint32_t RXBITRATE;
  volatile uint32_t TXMODE;
  volatile uint32_t RXMODE;
} LPC_I2S_TypeDef;

 
typedef struct
{
  volatile uint8_t  ILR;
       uint8_t  RESERVED0[7];
  volatile uint8_t  CCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  volatile uint8_t  AMR;
       uint8_t  RESERVED3[3];
  volatile const  uint32_t CTIME0;
  volatile const  uint32_t CTIME1;
  volatile const  uint32_t CTIME2;
  volatile uint8_t  SEC;
       uint8_t  RESERVED4[3];
  volatile uint8_t  MIN;
       uint8_t  RESERVED5[3];
  volatile uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  volatile uint8_t  DOM;
       uint8_t  RESERVED7[3];
  volatile uint8_t  DOW;
       uint8_t  RESERVED8[3];
  volatile uint16_t DOY;
       uint16_t RESERVED9;
  volatile uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  volatile uint16_t YEAR;
       uint16_t RESERVED11;
  volatile uint32_t CALIBRATION;
  volatile uint32_t GPREG0;
  volatile uint32_t GPREG1;
  volatile uint32_t GPREG2;
  volatile uint32_t GPREG3;
  volatile uint32_t GPREG4;
  volatile uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  volatile uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  volatile uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  volatile uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  volatile uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  volatile uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  volatile uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  volatile uint16_t ALDOY;
       uint16_t RESERVED19;
  volatile uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  volatile uint16_t ALYEAR;
       uint16_t RESERVED21;
  volatile uint32_t ERSTATUS;
  volatile uint32_t ERCONTROL;
  volatile uint32_t ERCOUNTERS;
       uint32_t RESERVED22;
  volatile uint32_t ERFIRSTSTAMP0;
  volatile uint32_t ERFIRSTSTAMP1;
  volatile uint32_t ERFIRSTSTAMP2;
       uint32_t RESERVED23;
  volatile uint32_t ERLASTSTAMP0;
  volatile uint32_t ERLASTSTAMP1;
  volatile uint32_t ERLASTSTAMP2;
} LPC_RTC_TypeDef;

 
typedef struct
{
  volatile uint8_t  MOD;
       uint8_t  RESERVED0[3];
  volatile uint32_t TC;
  volatile  uint8_t  FEED;
       uint8_t  RESERVED1[3];
  volatile const  uint32_t TV;
       uint32_t RESERVED2;
  volatile uint32_t WARNINT;
  volatile uint32_t WINDOW;
} LPC_WDT_TypeDef;

 
typedef struct
{
  volatile uint32_t CR;                      
  volatile uint32_t GDR;                     
       uint32_t RESERVED0;
  volatile uint32_t INTEN;                   
  volatile uint32_t DR[8];                   
  volatile const  uint32_t STAT;                    
  volatile uint32_t ADTRM;
} LPC_ADC_TypeDef;

 
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CTRL;
  volatile uint32_t CNTVAL;
} LPC_DAC_TypeDef;

 
typedef struct
{
  volatile const  uint32_t CON;
  volatile  uint32_t CON_SET;
  volatile  uint32_t CON_CLR;
  volatile const  uint32_t CAPCON;
  volatile  uint32_t CAPCON_SET;
  volatile  uint32_t CAPCON_CLR;
  volatile uint32_t TC0;
  volatile uint32_t TC1;
  volatile uint32_t TC2;
  volatile uint32_t LIM0;
  volatile uint32_t LIM1;
  volatile uint32_t LIM2;
  volatile uint32_t MAT0;
  volatile uint32_t MAT1;
  volatile uint32_t MAT2;
  volatile uint32_t DT;
  volatile uint32_t CP;
  volatile uint32_t CAP0;
  volatile uint32_t CAP1;
  volatile uint32_t CAP2;
  volatile const  uint32_t INTEN;
  volatile  uint32_t INTEN_SET;
  volatile  uint32_t INTEN_CLR;
  volatile const  uint32_t CNTCON;
  volatile  uint32_t CNTCON_SET;
  volatile  uint32_t CNTCON_CLR;
  volatile const  uint32_t INTF;
  volatile  uint32_t INTF_SET;
  volatile  uint32_t INTF_CLR;
  volatile  uint32_t CAP_CLR;
} LPC_MCPWM_TypeDef;

 
typedef struct
{
  volatile  uint32_t CON;
  volatile const  uint32_t STAT;
  volatile uint32_t CONF;
  volatile const  uint32_t POS;
  volatile uint32_t MAXPOS;
  volatile uint32_t CMPOS0;
  volatile uint32_t CMPOS1;
  volatile uint32_t CMPOS2;
  volatile const  uint32_t INXCNT;
  volatile uint32_t INXCMP0;
  volatile uint32_t LOAD;
  volatile const  uint32_t TIME;
  volatile const  uint32_t VEL;
  volatile const  uint32_t CAP;
  volatile uint32_t VELCOMP;
  volatile uint32_t FILTERPHA;
  volatile uint32_t FILTERPHB;
  volatile uint32_t FILTERINX;
  volatile uint32_t WINDOW;
  volatile uint32_t INXCMP1;
  volatile uint32_t INXCMP2;
       uint32_t RESERVED0[993];
  volatile  uint32_t IEC;
  volatile  uint32_t IES;
  volatile const  uint32_t INTSTAT;
  volatile const  uint32_t IE;
  volatile  uint32_t CLR;
  volatile  uint32_t SET;
} LPC_QEI_TypeDef;

 
typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLOCK;
  volatile uint32_t ARGUMENT;
  volatile uint32_t COMMAND;
  volatile const  uint32_t RESP_CMD;
  volatile const  uint32_t RESP0;
  volatile const  uint32_t RESP1;
  volatile const  uint32_t RESP2;
  volatile const  uint32_t RESP3;
  volatile uint32_t DATATMR;
  volatile uint32_t DATALEN;
  volatile uint32_t DATACTRL;
  volatile const  uint32_t DATACNT;
  volatile const  uint32_t STATUS;
  volatile  uint32_t CLEAR;
  volatile uint32_t MASK0;
       uint32_t RESERVED0[2];
  volatile const  uint32_t FIFOCNT;
       uint32_t RESERVED1[13];
  volatile uint32_t FIFO;
} LPC_MCI_TypeDef;

 
typedef struct
{
  volatile uint32_t mask[512];               
} LPC_CANAF_RAM_TypeDef;

typedef struct                           
{
  volatile uint32_t AFMR;
  volatile uint32_t SFF_sa;
  volatile uint32_t SFF_GRP_sa;
  volatile uint32_t EFF_sa;
  volatile uint32_t EFF_GRP_sa;
  volatile uint32_t ENDofTable;
  volatile const  uint32_t LUTerrAd;
  volatile const  uint32_t LUTerr;
  volatile uint32_t FCANIE;
  volatile uint32_t FCANIC0;
  volatile uint32_t FCANIC1;
} LPC_CANAF_TypeDef;

typedef struct                           
{
  volatile const  uint32_t TxSR;
  volatile const  uint32_t RxSR;
  volatile const  uint32_t MSR;
} LPC_CANCR_TypeDef;

typedef struct                           
{
  volatile uint32_t MOD;
  volatile  uint32_t CMR;
  volatile uint32_t GSR;
  volatile const  uint32_t ICR;
  volatile uint32_t IER;
  volatile uint32_t BTR;
  volatile uint32_t EWL;
  volatile const  uint32_t SR;
  volatile uint32_t RFS;
  volatile uint32_t RID;
  volatile uint32_t RDA;
  volatile uint32_t RDB;
  volatile uint32_t TFI1;
  volatile uint32_t TID1;
  volatile uint32_t TDA1;
  volatile uint32_t TDB1;
  volatile uint32_t TFI2;
  volatile uint32_t TID2;
  volatile uint32_t TDA2;
  volatile uint32_t TDB2;
  volatile uint32_t TFI3;
  volatile uint32_t TID3;
  volatile uint32_t TDA3;
  volatile uint32_t TDB3;
} LPC_CAN_TypeDef;

 
typedef struct                           
{
  volatile const  uint32_t IntStat;
  volatile const  uint32_t IntTCStat;
  volatile  uint32_t IntTCClear;
  volatile const  uint32_t IntErrStat;
  volatile  uint32_t IntErrClr;
  volatile const  uint32_t RawIntTCStat;
  volatile const  uint32_t RawIntErrStat;
  volatile const  uint32_t EnbldChns;
  volatile uint32_t SoftBReq;
  volatile uint32_t SoftSReq;
  volatile uint32_t SoftLBReq;
  volatile uint32_t SoftLSReq;
  volatile uint32_t Config;
  volatile uint32_t Sync;
} LPC_GPDMA_TypeDef;

typedef struct                           
{
  volatile uint32_t CSrcAddr;
  volatile uint32_t CDestAddr;
  volatile uint32_t CLLI;
  volatile uint32_t CControl;
  volatile uint32_t CConfig;
} LPC_GPDMACH_TypeDef;

 
typedef struct
{
  volatile const  uint32_t Revision;              
  volatile uint32_t Control;
  volatile uint32_t CommandStatus;
  volatile uint32_t InterruptStatus;
  volatile uint32_t InterruptEnable;
  volatile uint32_t InterruptDisable;
  volatile uint32_t HCCA;
  volatile const  uint32_t PeriodCurrentED;
  volatile uint32_t ControlHeadED;
  volatile uint32_t ControlCurrentED;
  volatile uint32_t BulkHeadED;
  volatile uint32_t BulkCurrentED;
  volatile const  uint32_t DoneHead;
  volatile uint32_t FmInterval;
  volatile const  uint32_t FmRemaining;
  volatile const  uint32_t FmNumber;
  volatile uint32_t PeriodicStart;
  volatile uint32_t LSTreshold;
  volatile uint32_t RhDescriptorA;
  volatile uint32_t RhDescriptorB;
  volatile uint32_t RhStatus;
  volatile uint32_t RhPortStatus1;
  volatile uint32_t RhPortStatus2;
       uint32_t RESERVED0[40];
  volatile const  uint32_t Module_ID;

  volatile const  uint32_t IntSt;                
  volatile uint32_t IntEn;
  volatile  uint32_t IntSet;
  volatile  uint32_t IntClr;
  volatile uint32_t StCtrl;
  volatile uint32_t Tmr;
       uint32_t RESERVED1[58];

  volatile const  uint32_t DevIntSt;             
  volatile uint32_t DevIntEn;
  volatile  uint32_t DevIntClr;
  volatile  uint32_t DevIntSet;

  volatile  uint32_t CmdCode;              
  volatile const  uint32_t CmdData;

  volatile const  uint32_t RxData;               
  volatile  uint32_t TxData;
  volatile const  uint32_t RxPLen;
  volatile  uint32_t TxPLen;
  volatile uint32_t Ctrl;
  volatile  uint32_t DevIntPri;

  volatile const  uint32_t EpIntSt;              
  volatile uint32_t EpIntEn;
  volatile  uint32_t EpIntClr;
  volatile  uint32_t EpIntSet;
  volatile  uint32_t EpIntPri;

  volatile uint32_t ReEp;                 
  volatile  uint32_t EpInd;
  volatile uint32_t MaxPSize;

  volatile const  uint32_t DMARSt;               
  volatile  uint32_t DMARClr;
  volatile  uint32_t DMARSet;
       uint32_t RESERVED2[9];
  volatile uint32_t UDCAH;
  volatile const  uint32_t EpDMASt;
  volatile  uint32_t EpDMAEn;
  volatile  uint32_t EpDMADis;
  volatile const  uint32_t DMAIntSt;
  volatile uint32_t DMAIntEn;
       uint32_t RESERVED3[2];
  volatile const  uint32_t EoTIntSt;
  volatile  uint32_t EoTIntClr;
  volatile  uint32_t EoTIntSet;
  volatile const  uint32_t NDDRIntSt;
  volatile  uint32_t NDDRIntClr;
  volatile  uint32_t NDDRIntSet;
  volatile const  uint32_t SysErrIntSt;
  volatile  uint32_t SysErrIntClr;
  volatile  uint32_t SysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  volatile const  uint32_t I2C_RX;                  
  volatile  uint32_t I2C_TX;
  };
  volatile  uint32_t I2C_STS;
  volatile uint32_t I2C_CTL;
  volatile uint32_t I2C_CLKHI;
  volatile  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  volatile uint32_t USBClkCtrl;              
  volatile uint32_t OTGClkCtrl;
  };
  union {
  volatile const  uint32_t USBClkSt;
  volatile const  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

 
typedef struct
{
  volatile uint32_t MAC1;                    
  volatile uint32_t MAC2;
  volatile uint32_t IPGT;
  volatile uint32_t IPGR;
  volatile uint32_t CLRT;
  volatile uint32_t MAXF;
  volatile uint32_t SUPP;
  volatile uint32_t TEST;
  volatile uint32_t MCFG;
  volatile uint32_t MCMD;
  volatile uint32_t MADR;
  volatile  uint32_t MWTD;
  volatile const  uint32_t MRDD;
  volatile const  uint32_t MIND;
       uint32_t RESERVED0[2];
  volatile uint32_t SA0;
  volatile uint32_t SA1;
  volatile uint32_t SA2;
       uint32_t RESERVED1[45];
  volatile uint32_t Command;                 
  volatile const  uint32_t Status;
  volatile uint32_t RxDescriptor;
  volatile uint32_t RxStatus;
  volatile uint32_t RxDescriptorNumber;
  volatile const  uint32_t RxProduceIndex;
  volatile uint32_t RxConsumeIndex;
  volatile uint32_t TxDescriptor;
  volatile uint32_t TxStatus;
  volatile uint32_t TxDescriptorNumber;
  volatile uint32_t TxProduceIndex;
  volatile const  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  volatile const  uint32_t TSV0;
  volatile const  uint32_t TSV1;
  volatile const  uint32_t RSV;
       uint32_t RESERVED3[3];
  volatile uint32_t FlowControlCounter;
  volatile const  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  volatile uint32_t RxFilterCtrl;            
  volatile const  uint32_t RxFilterWoLStatus;
  volatile  uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  volatile uint32_t HashFilterL;
  volatile uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  volatile const  uint32_t IntStatus;               
  volatile uint32_t IntEnable;
  volatile  uint32_t IntClear;
  volatile  uint32_t IntSet;
       uint32_t RESERVED7;
  volatile uint32_t PowerDown;
       uint32_t RESERVED8;
  volatile uint32_t Module_ID;
} LPC_EMAC_TypeDef;

 
typedef struct
{
  volatile uint32_t TIMH;                    
  volatile uint32_t TIMV;
  volatile uint32_t POL;
  volatile uint32_t LE;
  volatile uint32_t UPBASE;
  volatile uint32_t LPBASE;
  volatile uint32_t CTRL;
  volatile uint32_t INTMSK;
  volatile const  uint32_t INTRAW;
  volatile const  uint32_t INTSTAT;
  volatile  uint32_t INTCLR;
  volatile const  uint32_t UPCURR;
  volatile const  uint32_t LPCURR;
       uint32_t RESERVED0[115];
  volatile uint32_t PAL[128];
       uint32_t RESERVED1[256];
  volatile uint32_t CRSR_IMG[256];
  volatile uint32_t CRSR_CTRL;
  volatile uint32_t CRSR_CFG;
  volatile uint32_t CRSR_PAL0;
  volatile uint32_t CRSR_PAL1;
  volatile uint32_t CRSR_XY;
  volatile uint32_t CRSR_CLIP;
       uint32_t RESERVED2[2];
  volatile uint32_t CRSR_INTMSK;
  volatile  uint32_t CRSR_INTCLR;
  volatile const  uint32_t CRSR_INTRAW;
  volatile const  uint32_t CRSR_INTSTAT;
} LPC_LCD_TypeDef;

 
typedef struct
{
  volatile uint32_t Control;
  volatile const  uint32_t Status;
  volatile uint32_t Config;
       uint32_t RESERVED0[5];
  volatile uint32_t DynamicControl;
  volatile uint32_t DynamicRefresh;
  volatile uint32_t DynamicReadConfig;
       uint32_t RESERVED1[1];
  volatile uint32_t DynamicRP;
  volatile uint32_t DynamicRAS;
  volatile uint32_t DynamicSREX;
  volatile uint32_t DynamicAPR;
  volatile uint32_t DynamicDAL;
  volatile uint32_t DynamicWR;
  volatile uint32_t DynamicRC;
  volatile uint32_t DynamicRFC;
  volatile uint32_t DynamicXSR;
  volatile uint32_t DynamicRRD;
  volatile uint32_t DynamicMRD;
       uint32_t RESERVED2[9];
  volatile uint32_t StaticExtendedWait;
       uint32_t RESERVED3[31];
  volatile uint32_t DynamicConfig0;
  volatile uint32_t DynamicRasCas0;
       uint32_t RESERVED4[6];
  volatile uint32_t DynamicConfig1;
  volatile uint32_t DynamicRasCas1;
       uint32_t RESERVED5[6];
  volatile uint32_t DynamicConfig2;
  volatile uint32_t DynamicRasCas2;
       uint32_t RESERVED6[6];
  volatile uint32_t DynamicConfig3;
  volatile uint32_t DynamicRasCas3;
       uint32_t RESERVED7[38];
  volatile uint32_t StaticConfig0;
  volatile uint32_t StaticWaitWen0;
  volatile uint32_t StaticWaitOen0;
  volatile uint32_t StaticWaitRd0;
  volatile uint32_t StaticWaitPage0;
  volatile uint32_t StaticWaitWr0;
  volatile uint32_t StaticWaitTurn0;
       uint32_t RESERVED8[1];
  volatile uint32_t StaticConfig1;
  volatile uint32_t StaticWaitWen1;
  volatile uint32_t StaticWaitOen1;
  volatile uint32_t StaticWaitRd1;
  volatile uint32_t StaticWaitPage1;
  volatile uint32_t StaticWaitWr1;
  volatile uint32_t StaticWaitTurn1;
       uint32_t RESERVED9[1];
  volatile uint32_t StaticConfig2;
  volatile uint32_t StaticWaitWen2;
  volatile uint32_t StaticWaitOen2;
  volatile uint32_t StaticWaitRd2;
  volatile uint32_t StaticWaitPage2;
  volatile uint32_t StaticWaitWr2;
  volatile uint32_t StaticWaitTurn2;
       uint32_t RESERVED10[1];
  volatile uint32_t StaticConfig3;
  volatile uint32_t StaticWaitWen3;
  volatile uint32_t StaticWaitOen3;
  volatile uint32_t StaticWaitRd3;
  volatile uint32_t StaticWaitPage3;
  volatile uint32_t StaticWaitWr3;
  volatile uint32_t StaticWaitTurn3;
} LPC_EMC_TypeDef;

 
typedef struct
{
  volatile uint32_t MODE;
  volatile uint32_t SEED;
  union {
  volatile const  uint32_t SUM;
  volatile  uint32_t WR_DATA_DWORD;
  volatile  uint16_t WR_DATA_WORD;
       uint16_t RESERVED_WORD;
  volatile  uint8_t WR_DATA_BYTE;
       uint8_t RESERVED_BYTE[3];
  };
} LPC_CRC_TypeDef;

 
typedef struct
{
  volatile uint32_t CMD;			 
  volatile uint32_t ADDR;
  volatile uint32_t WDATA;
  volatile uint32_t RDATA;
  volatile uint32_t WSTATE;			 
  volatile uint32_t CLKDIV;
  volatile uint32_t PWRDWN;			 
       uint32_t RESERVED0[975];
  volatile uint32_t INT_CLR_ENABLE;	 
  volatile uint32_t INT_SET_ENABLE;
  volatile uint32_t INT_STATUS;		 
  volatile uint32_t INT_ENABLE;
  volatile uint32_t INT_CLR_STATUS;
  volatile uint32_t INT_SET_STATUS;
} LPC_EEPROM_TypeDef;


#pragma no_anon_unions


 
 
 
 
#line 1253 "..\\Startup\\LPC177x_8x.h"

 
#line 1274 "..\\Startup\\LPC177x_8x.h"

 
#line 1290 "..\\Startup\\LPC177x_8x.h"

 
#line 1312 "..\\Startup\\LPC177x_8x.h"




 
 
 
#line 1373 "..\\Startup\\LPC177x_8x.h"

#line 26 "..\\Drivers\\lpc177x_8x_emc.h"



 
 

 

 

 




 
 

 

 

 




 
 

 

 





 
 

 

 

 

 

 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 




 
 





 
 

 

 

 

 




 
 

 




 
 

 

 

 

 

 

 

 

 

 




 
 




 
 




 

 




 

 




 
 




 
 




 







 







 


 
 
typedef enum
{
  EMC_DYN_MEM_REFRESH_TIMER,
  EMC_DYN_MEM_READ_CONFIG,
  EMC_DYN_MEM_TRP,
  EMC_DYN_MEM_TRAS,
  EMC_DYN_MEM_TSREX,
  EMC_DYN_MEM_TAPR,
  EMC_DYN_MEM_TDAL,
  EMC_DYN_MEM_TWR,
  EMC_DYN_MEM_TRC,
  EMC_DYN_MEM_TRFC,
  EMC_DYN_MEM_TXSR,
  EMC_DYN_MEM_TRRD,
  EMC_DYN_MEM_TMRD
} EMC_DYN_MEM_PAR;

 
typedef enum
{
  EMC_STA_MEM_WAITWEN,
  EMC_STA_MEM_WAITOEN,
  EMC_STA_MEM_WAITRD,
  EMC_STA_MEM_WAITPAGE,
  EMC_STA_MEM_WAITWR,
  EMC_STA_MEM_WAITTURN,
} EMC_STA_MEM_PAR;

 


 

extern void EMC_Init(void);
extern void EMC_ConfigEndianMode(uint32_t endian_mode);
extern void EMC_DynCtrlClockEnable(uint32_t clock_enable);
extern void EMC_DynCtrlClockControl(int32_t clock_control);
extern void EMC_DynCtrlSelfRefresh(uint32_t self_refresh_mode);
extern void EMC_DynCtrlMMC(uint32_t MMC_val);
extern void EMC_DynCtrlSDRAMInit(uint32_t SDRAM_command);
extern void EMC_DynCtrlPowerDownMode(uint32_t SDRAM_command);
extern void EMC_SetDynMemoryParameter(EMC_DYN_MEM_PAR par, uint32_t val);
extern void EMC_StaticExtendedWait(uint32_t Extended_wait_time_out);
extern void EMC_DynMemConfigMD(uint32_t index , uint32_t mem_dev);
extern void EMC_DynMemConfigAM(uint32_t index , uint32_t add_mapped);
extern void EMC_DynMemConfigB(uint32_t index , uint32_t buff_control);
extern void EMC_DynMemConfigP(uint32_t index , uint32_t permission);
extern void EMC_DynMemRAS(uint32_t index , uint32_t ras_val);
extern void EMC_DynMemCAS(uint32_t index , uint32_t cas_val);
extern void EMC_StaMemConfigMW(uint32_t index , uint32_t mem_width);
extern void EMC_StaMemConfigPM(uint32_t index , uint32_t page_mode);
extern void EMC_StaMemConfigPC(uint32_t index , uint32_t pol_val);
extern void EMC_StaMemConfigPB(uint32_t index , uint32_t pb_val);
extern void EMC_StaMemConfigEW(uint32_t index , uint32_t ex_wait);
extern void EMC_StaMemConfigB(uint32_t index , uint32_t buf_val);
extern void EMC_StaMemConfigpP(uint32_t index , uint32_t per_val);
extern void EMC_SetStaMemoryParameter(uint32_t index ,EMC_STA_MEM_PAR par, uint32_t val);


#line 25 "..\\Drivers\\nandflash_k9f2g08u0x.h"










 































#line 76 "..\\Drivers\\nandflash_k9f2g08u0x.h"








extern void NandFlash_Init( void );
extern void NandFlash_Reset( void );
extern void NandFlash_WaitForReady( void );	 
extern uint32_t NandFlash_ReadId( void );
extern Bool NandFlash_ReadStatus( uint32_t Cmd );
extern Bool NandFlash_BlockErase( uint32_t blockNum );
extern Bool NandFlash_ValidBlockCheck( void );

extern Bool NandFlash_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr );

extern int NandFlash_PageReadFromBeginning(uint32_t block, uint32_t page, uint8_t* bufPtr);
extern int NandFlash_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,
													uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);
extern int NandFlash_ReadFromAddr(uint32_t addrInWholeNand, uint8_t* bufPtr, uint32_t size);
extern int NandFlash_SectorRead(uint32_t sectorNum, uint8_t* bufPtr);

extern uint32_t  Nand_EraseBlockLarge(int BlockAddr);
extern int  Nand_WritePageWithSpare2048(int PageNum,const uint8_t * DataBuf,const uint8_t *Spare);
extern int Nand_ReadPageWithSpare2048(int PageNum,uint8_t *const DataBuf, uint8_t *const Spare);
#line 22 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 23 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 1 "..\\Drivers\\lpc177x_8x_clkpwr.h"
 

















 

 




 
#line 28 "..\\Drivers\\lpc177x_8x_clkpwr.h"
#line 29 "..\\Drivers\\lpc177x_8x_clkpwr.h"
#line 1 "..\\Startup\\system_LPC177x_8x.h"























 









#line 35 "..\\Startup\\system_LPC177x_8x.h"

extern uint32_t SystemCoreClock;       
extern uint32_t PeripheralClock;	     
extern uint32_t EMCClock;			         
extern uint32_t USBClock;			         
extern uint32_t SPIFIClock;			       









 
extern void SystemInit (void);









 
extern void SystemCoreClockUpdate (void);



 










 





#line 30 "..\\Drivers\\lpc177x_8x_clkpwr.h"






 


 



 





 








 
 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 




 
#line 156 "..\\Drivers\\lpc177x_8x_clkpwr.h"






 
 
extern uint32_t SystemCoreClock;      
extern uint32_t PeripheralClock;	  
extern uint32_t EMCClock;		  

 
extern uint32_t USBClock;		 
extern uint32_t SPIFIClock;		 

 


 

void CLKPWR_SetCLKDiv(uint8_t ClkType, uint8_t DivVal);
uint32_t CLKPWR_GetCLK(uint8_t ClkType);
void CLKPWR_ConfigPPWR(uint32_t PPType, FunctionalState NewState);
void CLKPWR_ConfigReset(uint8_t PType, FunctionalState NewState);
void CLKPWR_Sleep(void);
void CLKPWR_DeepSleep(void);
void CLKPWR_PowerDown(void);
void CLKPWR_DeepPowerDown(void);



 










 

 
#line 24 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 1 "..\\Drivers\\lpc177x_8x_pinsel.h"
 

















 

 



 
#line 27 "..\\Drivers\\lpc177x_8x_pinsel.h"
#line 28 "..\\Drivers\\lpc177x_8x_pinsel.h"

 


 



 

 


 

 
#line 56 "..\\Drivers\\lpc177x_8x_pinsel.h"


 
#line 198 "..\\Drivers\\lpc177x_8x_pinsel.h"



 

typedef enum
{
	PINSEL_BASICMODE_PLAINOUT  = 0,	 
	PINSEL_BASICMODE_PULLDOWN,		 
  	PINSEL_BASICMODE_PULLUP,		 
	PINSEL_BASICMODE_REPEATER		 
}PinSel_BasicMode;

typedef enum
{
	PINSEL_I2CMODE_FAST_STANDARD  = 0,	 
	PINSEL_I2CMODE_OPENDRAINIO,			 
	PINSEL_I2CMODE_FASTMODEPLUS,		 
	PINSEL_I2CMODE_HIDRIVE_OPENDRAIN	 
}PinSel_I2cMode;
 


 
void PINSEL_ConfigPin(uint8_t portnum, uint8_t pinnum, uint8_t funcnum);
void PINSEL_SetPinMode(uint8_t portnum, uint8_t pinnum, PinSel_BasicMode modenum);
void PINSEL_SetHysMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetSlewMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetInBufMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetI2CMode(uint8_t portnum, uint8_t pinnum, PinSel_I2cMode I2CMode);
void PINSEL_SetOpenDrainMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetAnalogPinMode (uint8_t portnum, uint8_t pinnum, uint8_t enable);
void PINSEL_DacEnable (uint8_t portnum, uint8_t pinnum, uint8_t enable);
void PINSEL_SetFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable);




 





 

 

#line 25 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 1 "..\\Drivers\\lpc177x_8x_timer.h"
 

















 

 



 
#line 27 "..\\Drivers\\lpc177x_8x_timer.h"
#line 28 "..\\Drivers\\lpc177x_8x_timer.h"






 


 

 


 
 




 
 

 




 
 

 

 




 
 

 

 

 

 




 
 

 

 

 

 

 




 

 

 

 

 

 

 

 

 




 
 

 

 





 


 


 



 
 
typedef enum
{
	TIM_MR0_INT =0,  
	TIM_MR1_INT =1,  
	TIM_MR2_INT =2,  
	TIM_MR3_INT =3,  
	TIM_CR0_INT =4,  
	TIM_CR1_INT =5,  
}TIM_INT_TYPE;

 
typedef enum
{
	TIM_TIMER_MODE = 0,				 
	TIM_COUNTER_RISING_MODE,		 
	TIM_COUNTER_FALLING_MODE,		 
	TIM_COUNTER_ANY_MODE			 
} TIM_MODE_OPT;

 
typedef enum
{
	TIM_PRESCALE_TICKVAL = 0,		 
	TIM_PRESCALE_USVAL				 
} TIM_PRESCALE_OPT;

 
typedef enum
{
	TIM_COUNTER_INCAP0 = 0,			 
	TIM_COUNTER_INCAP1,				 
} TIM_COUNTER_INPUT_OPT;

 
typedef enum
{
	TIM_EXTMATCH_NOTHING = 0,		 
	TIM_EXTMATCH_LOW,				 
	TIM_EXTMATCH_HIGH,				 
	TIM_EXTMATCH_TOGGLE				 
}TIM_EXTMATCH_OPT;

 
typedef enum {
	TIM_CAPTURE_NONE = 0,	 
	TIM_CAPTURE_RISING,		 
	TIM_CAPTURE_FALLING,	 
	TIM_CAPTURE_ANY			 
} TIM_CAP_MODE_OPT;

 
typedef struct
{

	uint8_t PrescaleOption;		


 
	uint8_t Reserved[3];		 
	uint32_t PrescaleValue;		 
} TIM_TIMERCFG_Type;

 
typedef struct {

	uint8_t CounterOption;		


 
	uint8_t CountInputSelect;
	uint8_t Reserved[2];
} TIM_COUNTERCFG_Type;

 
typedef struct {
	uint8_t MatchChannel;	
 
	uint8_t IntOnMatch;		


 
	uint8_t StopOnMatch;	


 
	uint8_t ResetOnMatch;	


 

	uint8_t ExtMatchOutputType;	




 
	uint8_t Reserved[3];	 
	uint32_t MatchValue;	 
} TIM_MATCHCFG_Type;

 
typedef struct {
	uint8_t CaptureChannel;	
 
	uint8_t RisingEdge;		


 
	uint8_t FallingEdge;		


 
	uint8_t IntOnCaption;	


 

} TIM_CAPTURECFG_Type;



 


 


 
 
void TIM_Init(LPC_TIM_TypeDef *TIMx, TIM_MODE_OPT TimerCounterMode, void *TIM_ConfigStruct);
void TIM_DeInit(LPC_TIM_TypeDef *TIMx);

 
void TIM_ClearIntPending(LPC_TIM_TypeDef *TIMx, TIM_INT_TYPE IntFlag);
void TIM_ClearIntCapturePending(LPC_TIM_TypeDef *TIMx, TIM_INT_TYPE IntFlag);
FlagStatus TIM_GetIntStatus(LPC_TIM_TypeDef *TIMx, TIM_INT_TYPE IntFlag);
FlagStatus TIM_GetIntCaptureStatus(LPC_TIM_TypeDef *TIMx, TIM_INT_TYPE IntFlag);

 
void TIM_ConfigStructInit(TIM_MODE_OPT TimerCounterMode, void *TIM_ConfigStruct);
void TIM_ConfigMatch(LPC_TIM_TypeDef *TIMx, TIM_MATCHCFG_Type *TIM_MatchConfigStruct);
void TIM_UpdateMatchValue(LPC_TIM_TypeDef *TIMx,uint8_t MatchChannel, uint32_t MatchValue);
void TIM_SetMatchExt(LPC_TIM_TypeDef *TIMx,TIM_EXTMATCH_OPT ext_match );
void TIM_ConfigCapture(LPC_TIM_TypeDef *TIMx, TIM_CAPTURECFG_Type *TIM_CaptureConfigStruct);
void TIM_Cmd(LPC_TIM_TypeDef *TIMx, FunctionalState NewState);

uint32_t TIM_GetCaptureValue(LPC_TIM_TypeDef *TIMx, TIM_COUNTER_INPUT_OPT CaptureChannel);
void TIM_ResetCounter(LPC_TIM_TypeDef *TIMx);

void TIM_Waitus(uint32_t time);
void TIM_Waitms(uint32_t time);



 








 

 
#line 26 "..\\Drivers\\nandflash_k9f2g08u0x.c"
#line 1 "..\\Drivers\\debug_frmwrk.h"
 
















 




#line 1 "..\\Drivers\\lpc177x_8x_uart.h"
 

















 

 



 
#line 27 "..\\Drivers\\lpc177x_8x_uart.h"
#line 28 "..\\Drivers\\lpc177x_8x_uart.h"







 


 



 




 

 


 

 



 
 

 


 

 


 

 



 

 



 

 
#line 93 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 108 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 122 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 139 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 149 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 162 "..\\Drivers\\lpc177x_8x_uart.h"

 

 
#line 175 "..\\Drivers\\lpc177x_8x_uart.h"

 

 


 

 
#line 190 "..\\Drivers\\lpc177x_8x_uart.h"

 

 






 

 




 

 



 

 
#line 227 "..\\Drivers\\lpc177x_8x_uart.h"

 

 


 

 
 


 

 







 


 


 



 
typedef enum {
	UART_DATABIT_5		= 0,     		 
	UART_DATABIT_6,		     			 
	UART_DATABIT_7,		     			 
	UART_DATABIT_8		     			 
} UART_DATABIT_Type;



 
typedef enum {
	UART_STOPBIT_1		= (0),   					 
	UART_STOPBIT_2,		 							 
} UART_STOPBIT_Type;



 
typedef enum {
	UART_PARITY_NONE 	= 0,					 
	UART_PARITY_ODD,	 						 
	UART_PARITY_EVEN, 							 
	UART_PARITY_SP_1, 							 
	UART_PARITY_SP_0 							 
} UART_PARITY_Type;



 
typedef enum {
	UART_FIFO_TRGLEV0 = 0,	 
	UART_FIFO_TRGLEV1, 		 
	UART_FIFO_TRGLEV2,		 
	UART_FIFO_TRGLEV3		 
} UART_FITO_LEVEL_Type;

 

 
typedef enum {
	UART_INTCFG_RBR = 0,	 
	UART_INTCFG_THRE,		 
	UART_INTCFG_RLS,		 
	UART1_INTCFG_MS,		 
	UART1_INTCFG_CTS,		 
	UART_INTCFG_ABEO,		 
	UART_INTCFG_ABTO		 
} UART_INT_Type;



 
typedef enum {
	UART_LINESTAT_RDR	= ((uint8_t)(1<<0)),			 
	UART_LINESTAT_OE	= ((uint8_t)(1<<1)),			 
	UART_LINESTAT_PE	= ((uint8_t)(1<<2)),			 
	UART_LINESTAT_FE	= ((uint8_t)(1<<3)),			 
	UART_LINESTAT_BI	= ((uint8_t)(1<<4)),			 
	UART_LINESTAT_THRE	= ((uint8_t)(1<<5)),		 
	UART_LINESTAT_TEMT	= ((uint8_t)(1<<6)),		 
	UART_LINESTAT_RXFE	= ((uint8_t)(1<<7))			 
} UART_LS_Type;



 
typedef enum {
	UART_AUTOBAUD_MODE0				= 0,			 
	UART_AUTOBAUD_MODE1,							 
} UART_AB_MODE_Type;



 
typedef struct {
	UART_AB_MODE_Type	ABMode;			 
	FunctionalState		AutoRestart;	 
} UART_AB_CFG_Type;



 
typedef enum {
	UART_AUTOBAUD_INTSTAT_ABEO		= ((uint32_t)(1<<8)),		 
	UART_AUTOBAUD_INTSTAT_ABTO		= ((uint32_t)(1<<9))			 
}UART_ABEO_Type;



 
typedef enum {
	UART_IrDA_PULSEDIV2		= 0,		
 
	UART_IrDA_PULSEDIV4,				
 
	UART_IrDA_PULSEDIV8,				
 
	UART_IrDA_PULSEDIV16,				
 
	UART_IrDA_PULSEDIV32,				
 
	UART_IrDA_PULSEDIV64,				
 
	UART_IrDA_PULSEDIV128,				
 
	UART_IrDA_PULSEDIV256				
 
} UART_IrDA_PULSE_Type;

 

 
typedef enum {
	INACTIVE = 0,			 
	ACTIVE = !INACTIVE 		 
}UART1_SignalState;



 
typedef enum {
	UART1_MODEM_STAT_DELTA_CTS	= ((uint8_t)(1<<0)),		 
	UART1_MODEM_STAT_DELTA_DSR	= ((uint8_t)(1<<1)),		 
	UART1_MODEM_STAT_LO2HI_RI	= ((uint8_t)(1<<2)),		 
	UART1_MODEM_STAT_DELTA_DCD	= ((uint8_t)(1<<3)),		 
	UART1_MODEM_STAT_CTS		= ((uint8_t)(1<<4)),			 
	UART1_MODEM_STAT_DSR		= ((uint8_t)(1<<5)),			 
	UART1_MODEM_STAT_RI			= ((uint8_t)(1<<6)),				 
	UART1_MODEM_STAT_DCD		= ((uint8_t)(1<<7))				 
} UART_MODEM_STAT_type;



 
typedef enum {
	UART1_MODEM_PIN_DTR			= 0,		 
	UART1_MODEM_PIN_RTS						 
} UART_MODEM_PIN_Type;



 
typedef enum {
	UART1_MODEM_MODE_LOOPBACK	= 0,		 
	UART1_MODEM_MODE_AUTO_RTS,				 
	UART1_MODEM_MODE_AUTO_CTS 				 
} UART_MODEM_MODE_Type;



 
typedef enum {
	UART1_RS485_DIRCTRL_RTS = 0,	 
	UART1_RS485_DIRCTRL_DTR			 
} UART_RS485_DIRCTRL_PIN_Type;

 

 
typedef struct {
  uint32_t Baud_rate;   		 
  UART_PARITY_Type Parity;    	





 
  UART_DATABIT_Type Databits;   




 
  UART_STOPBIT_Type Stopbits;   


 
} UART_CFG_Type;

 

 

typedef struct {
	FunctionalState FIFO_ResetRxBuf;	


 
	FunctionalState FIFO_ResetTxBuf;	


 
	FunctionalState FIFO_DMAMode;		


 
	UART_FITO_LEVEL_Type FIFO_Level;	




 
} UART_FIFO_CFG_Type;

 

 
typedef struct {
	FunctionalState NormalMultiDropMode_State; 

 
	FunctionalState Rx_State;					

 
	FunctionalState AutoAddrDetect_State;		

 
	FunctionalState AutoDirCtrl_State;			

 
	UART_RS485_DIRCTRL_PIN_Type DirCtrlPin;		



 
	 SetState DirCtrlPol_Level;					




 
	uint8_t MatchAddrValue;					 
	uint8_t DelayValue;						 
} UART1_RS485_CTRLCFG_Type;



 


 


 
 
void UART_Init(LPC_UART_TypeDef *UARTx, UART_CFG_Type *UART_ConfigStruct);
void UART_DeInit(LPC_UART_TypeDef* UARTx);
void UART_ConfigStructInit(UART_CFG_Type *UART_InitStruct);

 
void UART_SendByte(LPC_UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveByte(LPC_UART_TypeDef* UARTx);
uint32_t UART_Send(LPC_UART_TypeDef *UARTx, uint8_t *txbuf,
		uint32_t buflen, TRANSFER_BLOCK_Type flag);
uint32_t UART_Receive(LPC_UART_TypeDef *UARTx, uint8_t *rxbuf, 		uint32_t buflen, TRANSFER_BLOCK_Type flag);


 
void UART_FIFOConfig(LPC_UART_TypeDef *UARTx, UART_FIFO_CFG_Type *FIFOCfg);
void UART_FIFOConfigStructInit(UART_FIFO_CFG_Type *UART_FIFOInitStruct);

 
uint32_t UART_GetIntId(LPC_UART_TypeDef* UARTx);
uint8_t UART_GetLineStatus(LPC_UART_TypeDef* UARTx);

 
void UART_IntConfig(LPC_UART_TypeDef *UARTx, UART_INT_Type UARTIntCfg, 				FunctionalState NewState);

void UART_TxCmd(LPC_UART_TypeDef *UARTx, FunctionalState NewState);
FlagStatus UART_CheckBusy(LPC_UART_TypeDef *UARTx);
void UART_ForceBreak(LPC_UART_TypeDef* UARTx);

 
void UART_ABClearIntPending(LPC_UART_TypeDef *UARTx, UART_ABEO_Type ABIntType);
void UART_ABCmd(LPC_UART_TypeDef *UARTx, UART_AB_CFG_Type *ABConfigStruct, 				FunctionalState NewState);


 
void UART_FullModemForcePinState(LPC_UART1_TypeDef *UARTx, UART_MODEM_PIN_Type Pin, 							UART1_SignalState NewState);

void UART_FullModemConfigMode(LPC_UART1_TypeDef *UARTx, UART_MODEM_MODE_Type Mode, 							FunctionalState NewState);

uint8_t UART_FullModemGetStatus(LPC_UART1_TypeDef *UARTx);

 
void UART_RS485Config(LPC_UART_TypeDef *UARTx,
									UART1_RS485_CTRLCFG_Type *RS485ConfigStruct);
void UART_RS485ReceiverCmd(LPC_UART_TypeDef *UARTx, FunctionalState NewState);
void UART_RS485SendSlvAddr(LPC_UART_TypeDef *UARTx, uint8_t SlvAddr);
uint32_t UART_RS485SendData(LPC_UART_TypeDef *UARTx, uint8_t *pData, uint32_t size);

 
void UART_IrDAInvtInputCmd(LPC_UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDACmd(LPC_UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDAPulseDivConfig(LPC_UART_TypeDef *UARTx, UART_IrDA_PULSE_Type PulseDiv);


 











 

 
#line 24 "..\\Drivers\\debug_frmwrk.h"









#line 40 "..\\Drivers\\debug_frmwrk.h"
























extern void (*_db_msg)(LPC_UART_TypeDef *UARTx, const void *s);
extern void (*_db_msg_)(LPC_UART_TypeDef *UARTx, const void *s);
extern void (*_db_char)(LPC_UART_TypeDef *UARTx, uint8_t ch);
extern void (*_db_dec)(LPC_UART_TypeDef *UARTx, uint8_t decn);
extern void (*_db_dec_16)(LPC_UART_TypeDef *UARTx, uint16_t decn);
extern void (*_db_dec_32)(LPC_UART_TypeDef *UARTx, uint32_t decn);
extern void (*_db_hex)(LPC_UART_TypeDef *UARTx, uint8_t hexn);
extern void (*_db_hex_16)(LPC_UART_TypeDef *UARTx, uint16_t hexn);
extern void (*_db_hex_32)(LPC_UART_TypeDef *UARTx, uint32_t hexn);
extern void (*_db_hex_)(LPC_UART_TypeDef *UARTx, uint8_t hexn);
extern void (*_db_hex_16_)(LPC_UART_TypeDef *UARTx, uint16_t hexn);
extern void (*_db_hex_32_)(LPC_UART_TypeDef *UARTx, uint32_t hexn);

extern uint8_t (*_db_get_key)(LPC_UART_TypeDef *UARTx);
extern uint8_t (*_db_get_char)(LPC_UART_TypeDef *UARTx);
extern uint8_t (*_db_get_val)(LPC_UART_TypeDef *UARTx, uint8_t option, uint8_t numCh, uint32_t * val);

uint8_t UARTGetValue (LPC_UART_TypeDef *UARTx, uint8_t option,
											uint8_t numCh, uint32_t* val);
void UARTPutChar (LPC_UART_TypeDef *UARTx, uint8_t ch);
void UARTPuts(LPC_UART_TypeDef *UARTx, const void *str);
void UARTPuts_(LPC_UART_TypeDef *UARTx, const void *str);
void UARTPutDec(LPC_UART_TypeDef *UARTx, uint8_t decnum);
void UARTPutDec16(LPC_UART_TypeDef *UARTx, uint16_t decnum);
void UARTPutDec32(LPC_UART_TypeDef *UARTx, uint32_t decnum);
void UARTPutHex (LPC_UART_TypeDef *UARTx, uint8_t hexnum);
void UARTPutHex16 (LPC_UART_TypeDef *UARTx, uint16_t hexnum);
void UARTPutHex32 (LPC_UART_TypeDef *UARTx, uint32_t hexnum);
uint8_t UARTGetChar (LPC_UART_TypeDef *UARTx);
uint8_t UARTGetKey (LPC_UART_TypeDef *UARTx);
void debug_frmwrk_init(void);

#line 27 "..\\Drivers\\nandflash_k9f2g08u0x.c"

uint8_t InvalidBlockTable[2048];

 



 
void NandFlash_Init( void )
{
	uint32_t i;
	TIM_TIMERCFG_Type TIM_ConfigStruct;

	

 
	EMC_Init();

	((LPC_EMC_TypeDef *) ((0x20080000UL) + 0x1C000) )->Control = ((uint32_t )(1<<0));

	EMC_StaMemConfigMW (0,(((uint32_t )(0 & 0x03))));

	EMC_StaMemConfigPB(0,((uint32_t )(1 << 7))); 
											   

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWEN, ((uint32_t )(2 & 0x0f)));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITOEN, ((uint32_t )(2 & 0x0f)));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWR, ((uint32_t )(0x1f & 0x1f)));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITPAGE, ((uint32_t )(0x1f & 0x1f)));	

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWR, ((uint32_t )(0x1f & 0x1f)));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITTURN, ((uint32_t )(0x1f & 0x0f)));

    
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	
	TIM_Init(((LPC_TIM_TypeDef *) ((0x40000000UL) + 0x04000) ), TIM_TIMER_MODE,&TIM_ConfigStruct);

  	
	TIM_Waitms(2);

	 
	for ( i = 0; i < 2048; i++ )
	{
		InvalidBlockTable[i] = 0;
	}

	return;
}

 



 
void NandFlash_Reset( void )
{
	volatile uint8_t *pCLE;

	 
	pCLE = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	*pCLE = 0xFF;

	TIM_Waitms(2);
	return;
}

 








 
Bool NandFlash_ReadStatus(uint32_t Cmd)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pDATA;
	uint8_t StatusData;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pDATA = ((volatile uint8_t *)0x81000000);

	*pCLE = 0x70;

	while ( (*pDATA & 0xC0) != 0xC0 );

	StatusData = *pDATA;

	switch (Cmd)
	{
		case 0x80:
		case 0x60:
		  	if (StatusData & 0x01)	 
				return(FALSE);
		  	else
				return(TRUE);

		case 0x00:				 
		  	return(TRUE);

		default:
		  	break;
	}

	return(FALSE);
}
 



 
uint32_t NandFlash_ReadId( void )
{
	uint8_t a, b, c, d;
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));
	pDATA = ((volatile uint8_t *)0x81000000);

	*pCLE = 0x90;
	*pALE = 0;

	a = *pDATA;
	b = *pDATA;
	d = *pDATA;
	c = *pDATA;

	return ((a << 24) | (b << 16) | (c << 8) | d);
}

 







 
Bool NandFlash_BlockErase( uint32_t blockNum )
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	uint32_t rowAddr;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));

	rowAddr = blockNum * 64;
	
	*pCLE = 0x60;

	*pALE = (uint8_t)(rowAddr & 0x00FF);			 

	*pALE = (uint8_t)((rowAddr & 0xFF00) >> 8);	 

	*pALE = (uint8_t)((rowAddr & 0xFF0000) >> 16);	 

	*pCLE = 0xD0;
    
	Delay(10);

	return(NandFlash_ReadStatus(0x60));
}

 








 
Bool NandFlash_ValidBlockCheck( void )
{
	uint32_t block, page;
	Bool retValue = TRUE;

	uint8_t data = 0;

	for ( block = 0; block < 2048; block++ )
	{
		for ( page = 0; page < 2; page++ )
		{
			 
			NandFlash_PageReadFromAddr(block, page, (2048), &data, 1);

			if(data != 0xFF)
			{
				
				
				InvalidBlockTable[block] = 0;
				
				retValue = FALSE;
			}else{
			   	InvalidBlockTable[block] = 1;
			}
		}
	}

	return(retValue);
}

 











 

 












 
Bool NandFlash_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr )
{
	return (NandFlash_PageReadFromBeginning(pageNum, blockNum, bufPtr) != 0);
}

 











 
int NandFlash_PageReadFromBeginning(uint32_t blockNum, uint32_t pageNum, uint8_t* bufPtr)
{
	return (NandFlash_PageReadFromAddr(blockNum, pageNum, 0, bufPtr, (2048 + 64)));
}

 













 
int NandFlash_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,
											uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
	uint32_t curAddr = 0;

	curAddr += blockNum * ((2048 + 64) * 64);	

	curAddr += pageNum * (2048 + 64);	

	curAddr += addrInPage;

	return (NandFlash_ReadFromAddr(curAddr, bufPtr, size));
}

 









 
int NandFlash_ReadFromAddr(uint32_t addrInWholeNand, uint8_t* bufPtr, uint32_t size)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint8_t nand_buf;
	uint32_t i, curColumm, curRow;

	i = 0;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));
	pDATA = ((volatile uint8_t *)0x81000000);

	curColumm = addrInWholeNand % (2048 + 64);		
	curRow = addrInWholeNand / (2048 + 64);			

	*pCLE = 0x00;

	*pALE = (uint8_t)(curColumm & 0x000000FF);			 

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);		 

	*pALE = (uint8_t)(curRow & 0x000000FF);		 

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	 

	*pCLE = 0x30;

	Delay(1);

	
	for ( i = 0; i < ((2048 + 64) - curColumm); i++ )
	{
		*bufPtr = *pDATA;
		if((i + 1) >= size)
			break;
		bufPtr++;
	}

	
	return i;
}



int NandFlash_SectorRead(uint32_t sectorNum, uint8_t* bufPtr)
{
	uint32_t curAddr = 0;

	curAddr += sectorNum * 512;
	curAddr +=(sectorNum/4)*64;
	return (NandFlash_ReadFromAddr(curAddr, bufPtr, 512));
}




uint32_t  Nand_EraseBlockLarge(int BlockAddr)
{
    volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	uint32_t rowAddr;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));

	rowAddr = BlockAddr * 64;
	
	*pCLE = 0x60;
    
	*pALE = (uint8_t)(rowAddr & 0x00FF);			 
    
	*pALE = (uint8_t)((rowAddr & 0xFF00) >> 8);	 
    
	*pALE = (uint8_t)((rowAddr & 0xFF0000) >> 16);	 
    
	*pCLE = 0xD0;
    
	Delay(10);
    
	return 1;
}

int  Nand_WritePageWithSpare2048(int PageNum,const uint8_t * DataBuf,const uint8_t *Spare)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint32_t i, curAddr, curColumm,curRow;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));
	pDATA = ((volatile uint8_t *)0x81000000);

    if(DataBuf == ((void*) 0))
	    curColumm = 2048;
    else
        curColumm = 0;
    
	curRow = PageNum;

	*pCLE = 0x80;

	*pALE =  (uint8_t)(curColumm & 0x000000FF);		 

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);	 

	*pALE = (uint8_t)(curRow & 0x000000FF);		 

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	 

    if(DataBuf != ((void*) 0))
    {
    	for ( i = 0; i < 2048; i++ )
    	{
    		*pDATA = *DataBuf++;
    	}
    }

    if(Spare != ((void*) 0))
    {
        for ( i = 0; i < 64; i++ ) 
    	{
    		*pDATA = *Spare++;
    	}
    }
    
	*pCLE = 0x10;

	Delay(1);			

	return 1;
}

int Nand_ReadPageWithSpare2048(int PageNum,uint8_t *const DataBuf, uint8_t *const Spare)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint8_t nand_buf;
	uint32_t i, curColumm, curRow;
    volatile uint8_t j;
    
	i = 0;

	pCLE  = ((volatile uint8_t *)(0x80000000|(0x1<<20)));
	pALE  = ((volatile uint8_t *)(0x80000000|(0x1<<19)));
	pDATA = ((volatile uint8_t *)0x81000000);

	curColumm = 0;
	curRow = PageNum;

	*pCLE = 0x00;

	*pALE = (uint8_t)(curColumm & 0x000000FF);			 

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);		 

	*pALE = (uint8_t)(curRow & 0x000000FF);		 

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	 

	*pCLE = 0x30;

    
	Delay(1);
    
    if(DataBuf != ((void*) 0))
    {
        for(i=0;i<2048;i++)
        {
            DataBuf[i]=*pDATA;
        }
    }
    else
    {
        for(i=0;i<2048;i++)
        {
            j=*pDATA;
        } 
    }
    if(Spare!=((void*) 0))
    {
        for(i=0;i<64;i++)
        {
        	Spare[i]=*pDATA;
        }
    }
    else
    {
        for(i=0;i<64;i++)
        {
        	j=*pDATA;
        }
    }
    
	return 1;
}

