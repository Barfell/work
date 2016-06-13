/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * msp430x14x devices.
 *
 * Copyright 1996-2015 IAR Systems AB.
 *
 *
 *
 ********************************************************************/

#ifndef __IO430X14X
#define __IO430X14X

#ifdef  __IAR_SYSTEMS_ICC__

#include "intrinsics.h"
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430x14x.h file for use with ICC430/A430 only
#endif


#ifdef __IAR_SYSTEMS_ICC__
#pragma language=save
#pragma language=extended


#ifdef __cplusplus
#define __READ    /* not supported */
#else
#define __READ    const
#endif


/*-------------------------------------------------------------------------
 *   Standard Bits
 *-------------------------------------------------------------------------*/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

/*-------------------------------------------------------------------------
 *   Status register bits
 *-------------------------------------------------------------------------*/

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)


#define LPM0      __bis_SR_register(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */



/*-------------------------------------------------------------------------
 *   Special Function
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char IE1;   /* Interrupt Enable 1 */

  struct
  {
    unsigned char WDTIE           : 1; /*  */
    unsigned char OFIE            : 1; /*  */
    unsigned char                : 2;
    unsigned char NMIIE           : 1; /*  */
    unsigned char ACCVIE          : 1; /*  */
    unsigned char URXIE0          : 1; /*  */
    unsigned char UTXIE0          : 1; /*  */
  }IE1_bit;
} @0x0000;


enum {
  WDTIE           = 0x0001,
  OFIE            = 0x0002,
  NMIIE           = 0x0010,
  ACCVIE          = 0x0020,
  URXIE0          = 0x0040,
  UTXIE0          = 0x0080
};


__no_init volatile union
{
  unsigned char IFG1;   /* Interrupt Flag 1 */

  struct
  {
    unsigned char WDTIFG          : 1; /*  */
    unsigned char OFIFG           : 1; /*  */
    unsigned char                : 2;
    unsigned char NMIIFG          : 1; /*  */
    unsigned char                : 1;
    unsigned char URXIFG0         : 1; /*  */
    unsigned char UTXIFG0         : 1; /*  */
  }IFG1_bit;
} @0x0002;


enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  NMIIFG          = 0x0010,
  URXIFG0         = 0x0040,
  UTXIFG0         = 0x0080
};


__no_init volatile union
{
  unsigned char ME1;   /* Module Enable 1 */

  struct
  {
    unsigned char                : 6;
    unsigned char URXE0           : 1; /*  */
    unsigned char UTXE0           : 1; /*  */
  }ME1_bit;
} @0x0004;


enum {
  URXE0           = 0x0040,
  UTXE0           = 0x0080
};


__no_init volatile union
{
  unsigned char IE2;   /* Interrupt Enable 2 */

  struct
  {
    unsigned char                : 4;
    unsigned char URXIE1          : 1; /*  */
    unsigned char UTXIE1          : 1; /*  */
  }IE2_bit;
} @0x0001;


enum {
  URXIE1          = 0x0010,
  UTXIE1          = 0x0020
};


__no_init volatile union
{
  unsigned char IFG2;   /* Interrupt Flag 2 */

  struct
  {
    unsigned char                : 4;
    unsigned char URXIFG1         : 1; /*  */
    unsigned char UTXIFG1         : 1; /*  */
  }IFG2_bit;
} @0x0003;


enum {
  URXIFG1         = 0x0010,
  UTXIFG1         = 0x0020
};


__no_init volatile union
{
  unsigned char ME2;   /* Module Enable 2 */

  struct
  {
    unsigned char                : 4;
    unsigned char URXE1           : 1; /*  */
    unsigned char UTXE1           : 1; /*  */
  }ME2_bit;
} @ 0x0005;


enum {
  URXE1           = 0x0010,
  UTXE1           = 0x0020
};



#define U0IE                IE1       /* UART0 Interrupt Enable Register */
#define U0IFG               IFG1      /* UART0 Interrupt Flag Register */
#define U0ME                ME1      /* UART0 Module Enable Register */
#define USPIE0              (0x40)
#define U1IE                IE2       /* UART1 Interrupt Enable Register */
#define U1IFG               IFG2      /* UART1 Interrupt Flag Register */
#define U1ME                ME2       /* UART1 Module Enable Register */
#define USPIE1              (0x10)

/*-------------------------------------------------------------------------
 *   Watchdog Timer
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short WDTCTL;   /* Watchdog Timer Control */

  struct
  {
    unsigned short WDTIS0          : 1; /*  */
    unsigned short WDTIS1          : 1; /*  */
    unsigned short WDTSSEL         : 1; /*  */
    unsigned short WDTCNTCL        : 1; /*  */
    unsigned short WDTTMSEL        : 1; /*  */
    unsigned short WDTNMI          : 1; /*  */
    unsigned short WDTNMIES        : 1; /*  */
    unsigned short WDTHOLD         : 1; /*  */
  }WDTCTL_bit;
} @ 0x0120;


enum {
  WDTIS0          = 0x0001,
  WDTIS1          = 0x0002,
  WDTSSEL         = 0x0004,
  WDTCNTCL        = 0x0008,
  WDTTMSEL        = 0x0010,
  WDTNMI          = 0x0020,
  WDTNMIES        = 0x0040,
  WDTHOLD         = 0x0080
};



#define __MSP430_HAS_WDT__            /* Definition to show that Module is available */

#define WDTPW               (0x5A00u)
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)                 /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)          /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1)          /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)   /* 1.9ms   " */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL)                          /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)                   /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)                   /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)            /* 1.9ms   " */

/*-------------------------------------------------------------------------
 *   Multiplier
 *-------------------------------------------------------------------------*/



  /* Multiply Unsigned/Operand 1 */
__no_init volatile unsigned short MPY @ 0x0130;



  /* Multiply Signed/Operand 1 */
__no_init volatile unsigned short MPYS @ 0x0132;



  /* Multiply Unsigned and Accumulate/Operand 1 */
__no_init volatile unsigned short MAC @ 0x0134;



  /* Multiply Signed and Accumulate/Operand 1 */
__no_init volatile unsigned short MACS @ 0x0136;



  /* Operand 2 */
__no_init volatile unsigned short OP2 @ 0x0138;



  /* Result Low Word */
__no_init volatile unsigned short RESLO @ 0x013A;



  /* Result High Word */
__no_init volatile unsigned short RESHI @ 0x013C;



  /* Sum Extend */
__no_init volatile unsigned __READ short SUMEXT @ 0x013E;


#define __MSP430_HAS_MPY__            /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port 1/2
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned __READ char P1IN;   /* Port 1 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P1IN_bit;
} @0x0020;


enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};


__no_init volatile union
{
  unsigned char P1OUT;   /* Port 1 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1OUT_bit;
} @0x0021;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1DIR;   /* Port 1 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1DIR_bit;
} @0x0022;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IFG;   /* Port 1 Interrupt Flag */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IFG_bit;
} @0x0023;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IES;   /* Port 1 Interrupt Edge Select */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IES_bit;
} @0x0024;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1IE;   /* Port 1 Interrupt Enable */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1IE_bit;
} @0x0025;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P1SEL;   /* Port 1 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P1SEL_bit;
} @0x0026;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned __READ char P2IN;   /* Port 2 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P2IN_bit;
} @0x0028;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2OUT;   /* Port 2 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2OUT_bit;
} @0x0029;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2DIR;   /* Port 2 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2DIR_bit;
} @0x002A;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IFG;   /* Port 2 Interrupt Flag */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IFG_bit;
} @0x002B;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IES;   /* Port 2 Interrupt Edge Select */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IES_bit;
} @0x002C;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2IE;   /* Port 2 Interrupt Enable */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2IE_bit;
} @0x002D;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P2SEL;   /* Port 2 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P2SEL_bit;
} @ 0x002E;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};
*/



#define __MSP430_HAS_PORT1__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port 3/4
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned __READ char P3IN;   /* Port 3 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P3IN_bit;
} @0x0018;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3OUT;   /* Port 3 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3OUT_bit;
} @0x0019;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3DIR;   /* Port 3 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3DIR_bit;
} @0x001A;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P3SEL;   /* Port 3 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P3SEL_bit;
} @0x001B;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned __READ char P4IN;   /* Port 4 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P4IN_bit;
} @0x001C;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P4OUT;   /* Port 4 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P4OUT_bit;
} @0x001D;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P4DIR;   /* Port 4 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P4DIR_bit;
} @0x001E;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P4SEL;   /* Port 4 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P4SEL_bit;
} @ 0x001F;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};
*/



#define __MSP430_HAS_PORT3__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port 5/6
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned __READ char P5IN;   /* Port 5 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P5IN_bit;
} @0x0030;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P5OUT;   /* Port 5 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P5OUT_bit;
} @0x0031;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P5DIR;   /* Port 5 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P5DIR_bit;
} @0x0032;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P5SEL;   /* Port 5 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P5SEL_bit;
} @0x0033;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned __READ char P6IN;   /* Port 6 Input */

  struct
  {
    unsigned __READ char P0              : 1; /*  */
    unsigned __READ char P1              : 1; /*  */
    unsigned __READ char P2              : 1; /*  */
    unsigned __READ char P3              : 1; /*  */
    unsigned __READ char P4              : 1; /*  */
    unsigned __READ char P5              : 1; /*  */
    unsigned __READ char P6              : 1; /*  */
    unsigned __READ char P7              : 1; /*  */
  }P6IN_bit;
} @0x0034;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P6OUT;   /* Port 6 Output */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P6OUT_bit;
} @0x0035;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P6DIR;   /* Port 6 Direction */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P6DIR_bit;
} @0x0036;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char P6SEL;   /* Port 6 Selection */

  struct
  {
    unsigned char P0              : 1; /*  */
    unsigned char P1              : 1; /*  */
    unsigned char P2              : 1; /*  */
    unsigned char P3              : 1; /*  */
    unsigned char P4              : 1; /*  */
    unsigned char P5              : 1; /*  */
    unsigned char P6              : 1; /*  */
    unsigned char P7              : 1; /*  */
  }P6SEL_bit;
} @ 0x0037;


/*
enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080
};
*/



#define __MSP430_HAS_PORT5__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   USART 0  UART/SPI Mode
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char U0CTL;   /* USART 0 Control */

  struct
  {
    unsigned char SWRST           : 1; /* USART Software Reset */
    unsigned char MM              : 1; /* Master Mode off/on */
    unsigned char SYNC            : 1; /* UART / SPI mode */
    unsigned char LISTEN          : 1; /* Listen mode */
    unsigned char CHAR            : 1; /* Data 0:7-bits / 1:8-bits */
    unsigned char SPB             : 1; /* Stop Bits 0:one / 1: two */
    unsigned char PEV             : 1; /* Parity 0:odd / 1:even */
    unsigned char PENA            : 1; /* Parity enable */
  }U0CTL_bit;
} @0x0070;


enum {
  SWRST           = 0x0001,
  MM              = 0x0002,
  SYNC            = 0x0004,
  LISTEN          = 0x0008,
  CHAR            = 0x0010,
  SPB             = 0x0020,
  PEV             = 0x0040,
  PENA            = 0x0080
};


__no_init volatile union
{
  unsigned char U0TCTL;   /* USART 0 Transmit Control */

  struct
  {
    unsigned char TXEPT           : 1; /* TX Buffer empty */
    unsigned char STC             : 1; /* SPI: STC enable 0:on / 1:off */
    unsigned char TXWAKE          : 1; /* TX Wake up mode */
    unsigned char URXSE           : 1; /* Receive Start edge select */
    unsigned char SSEL0           : 1; /* Clock Source Select 0 */
    unsigned char SSEL1           : 1; /* Clock Source Select 1 */
    unsigned char CKPL            : 1; /* Clock Polarity */
    unsigned char CKPH            : 1; /* SPI: Clock Phase */
  }U0TCTL_bit;
} @0x0071;


enum {
  TXEPT           = 0x0001,
  STC             = 0x0002,
  TXWAKE          = 0x0004,
  URXSE           = 0x0008,
  SSEL0           = 0x0010,
  SSEL1           = 0x0020,
  CKPL            = 0x0040,
  CKPH            = 0x0080
};


__no_init volatile union
{
  unsigned char U0RCTL;   /* USART 0 Receive Control */

  struct
  {
    unsigned char RXERR           : 1; /* RX Error Error */
    unsigned char RXWAKE          : 1; /* RX Wake up detect */
    unsigned char URXWIE          : 1; /* RX Wake up interrupt enable */
    unsigned char URXEIE          : 1; /* RX Error interrupt enable */
    unsigned char BRK             : 1; /* Break detected */
    unsigned char OE              : 1; /* Overrun Error */
    unsigned char PE              : 1; /* Parity Error */
    unsigned char FE              : 1; /* Frame Error */
  }U0RCTL_bit;
} @0x0072;


enum {
  RXERR           = 0x0001,
  RXWAKE          = 0x0002,
  URXWIE          = 0x0004,
  URXEIE          = 0x0008,
  BRK             = 0x0010,
  OE              = 0x0020,
  PE              = 0x0040,
  FE              = 0x0080
};


  /* USART 0 Modulation Control */
__no_init volatile unsigned char U0MCTL @ 0x0073;



  /* USART 0 Baud Rate 0 */
__no_init volatile unsigned char U0BR0 @ 0x0074;



  /* USART 0 Baud Rate 1 */
__no_init volatile unsigned char U0BR1 @ 0x0075;



  /* USART 0 Receive Buffer */
__no_init volatile unsigned __READ char U0RXBUF @ 0x0076;



  /* USART 0 Transmit Buffer */
__no_init volatile unsigned char U0TXBUF @ 0x0077;


#define __MSP430_HAS_UART0__          /* Definition to show that Module is available */

#define UCTL0               U0CTL     /* USART 0 Control */
#define UTCTL0              U0TCTL    /* USART 0 Transmit Control */
#define URCTL0              U0RCTL    /* USART 0 Receive Control */
#define UMCTL0              U0MCTL    /* USART 0 Modulation Control */
#define UBR00               U0BR0     /* USART 0 Baud Rate 0 */
#define UBR10               U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF0              U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF0              U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL0_              U0CTL_    /* USART 0 Control */
#define UTCTL0_             U0TCTL_   /* USART 0 Transmit Control */
#define URCTL0_             U0RCTL_   /* USART 0 Receive Control */
#define UMCTL0_             U0MCTL_   /* USART 0 Modulation Control */
#define UBR00_              U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR10_              U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF0_             U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF0_             U0TXBUF_  /* USART 0 Transmit Buffer */
#define UCTL_0              U0CTL     /* USART 0 Control */
#define UTCTL_0             U0TCTL    /* USART 0 Transmit Control */
#define URCTL_0             U0RCTL    /* USART 0 Receive Control */
#define UMCTL_0             U0MCTL    /* USART 0 Modulation Control */
#define UBR0_0              U0BR0     /* USART 0 Baud Rate 0 */
#define UBR1_0              U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF_0             U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF_0             U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL_0_             U0CTL_    /* USART 0 Control */
#define UTCTL_0_            U0TCTL_   /* USART 0 Transmit Control */
#define URCTL_0_            U0RCTL_   /* USART 0 Receive Control */
#define UMCTL_0_            U0MCTL_   /* USART 0 Modulation Control */
#define UBR0_0_             U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR1_0_             U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF_0_            U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF_0_            U0TXBUF_  /* USART 0 Transmit Buffer */

/*-------------------------------------------------------------------------
 *   USART 1
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char U1CTL;   /* USART 1 Control */

  struct
  {
    unsigned char SWRST           : 1; /* USART Software Reset */
    unsigned char MM              : 1; /* Master Mode off/on */
    unsigned char SYNC            : 1; /* UART / SPI mode */
    unsigned char LISTEN          : 1; /* Listen mode */
    unsigned char CHAR            : 1; /* Data 0:7-bits / 1:8-bits */
    unsigned char SPB             : 1; /* Stop Bits 0:one / 1: two */
    unsigned char PEV             : 1; /* Parity 0:odd / 1:even */
    unsigned char PENA            : 1; /* Parity enable */
  }U1CTL_bit;
} @0x0078;


/*
enum {
  SWRST           = 0x0001,
  MM              = 0x0002,
  SYNC            = 0x0004,
  LISTEN          = 0x0008,
  CHAR            = 0x0010,
  SPB             = 0x0020,
  PEV             = 0x0040,
  PENA            = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char U1TCTL;   /* USART 1 Transmit Control */

  struct
  {
    unsigned char TXEPT           : 1; /* TX Buffer empty */
    unsigned char STC             : 1; /* SPI: STC enable 0:on / 1:off */
    unsigned char TXWAKE          : 1; /* TX Wake up mode */
    unsigned char URXSE           : 1; /* Receive Start edge select */
    unsigned char SSEL0           : 1; /* Clock Source Select 0 */
    unsigned char SSEL1           : 1; /* Clock Source Select 1 */
    unsigned char CKPL            : 1; /* Clock Polarity */
    unsigned char CKPH            : 1; /* SPI: Clock Phase */
  }U1TCTL_bit;
} @0x0079;


/*
enum {
  TXEPT           = 0x0001,
  STC             = 0x0002,
  TXWAKE          = 0x0004,
  URXSE           = 0x0008,
  SSEL0           = 0x0010,
  SSEL1           = 0x0020,
  CKPL            = 0x0040,
  CKPH            = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char U1RCTL;   /* USART 1 Receive Control */

  struct
  {
    unsigned char RXERR           : 1; /* RX Error Error */
    unsigned char RXWAKE          : 1; /* RX Wake up detect */
    unsigned char URXWIE          : 1; /* RX Wake up interrupt enable */
    unsigned char URXEIE          : 1; /* RX Error interrupt enable */
    unsigned char BRK             : 1; /* Break detected */
    unsigned char OE              : 1; /* Overrun Error */
    unsigned char PE              : 1; /* Parity Error */
    unsigned char FE              : 1; /* Frame Error */
  }U1RCTL_bit;
} @0x007A;


/*
enum {
  RXERR           = 0x0001,
  RXWAKE          = 0x0002,
  URXWIE          = 0x0004,
  URXEIE          = 0x0008,
  BRK             = 0x0010,
  OE              = 0x0020,
  PE              = 0x0040,
  FE              = 0x0080,
};

*/

  /* USART 1 Modulation Control */
__no_init volatile unsigned char U1MCTL @ 0x007B;



  /* USART 1 Baud Rate 0 */
__no_init volatile unsigned char U1BR0 @ 0x007C;



  /* USART 1 Baud Rate 1 */
__no_init volatile unsigned char U1BR1 @ 0x007D;



  /* USART 1 Receive Buffer */
__no_init volatile unsigned __READ char U1RXBUF @ 0x007E;



  /* USART 1 Transmit Buffer */
__no_init volatile unsigned char U1TXBUF @ 0x007F;


#define __MSP430_HAS_UART1__          /* Definition to show that Module is available */

#define UCTL1               U1CTL     /* USART 1 Control */
#define UTCTL1              U1TCTL    /* USART 1 Transmit Control */
#define URCTL1              U1RCTL    /* USART 1 Receive Control */
#define UMCTL1              U1MCTL    /* USART 1 Modulation Control */
#define UBR01               U1BR0     /* USART 1 Baud Rate 0 */
#define UBR11               U1BR1     /* USART 1 Baud Rate 1 */
#define RXBUF1              U1RXBUF   /* USART 1 Receive Buffer */
#define TXBUF1              U1TXBUF   /* USART 1 Transmit Buffer */
#define UCTL1_              U1CTL_    /* USART 1 Control */
#define UTCTL1_             U1TCTL_   /* USART 1 Transmit Control */
#define URCTL1_             U1RCTL_   /* USART 1 Receive Control */
#define UMCTL1_             U1MCTL_   /* USART 1 Modulation Control */
#define UBR01_              U1BR0_    /* USART 1 Baud Rate 0 */
#define UBR11_              U1BR1_    /* USART 1 Baud Rate 1 */
#define RXBUF1_             U1RXBUF_  /* USART 1 Receive Buffer */
#define TXBUF1_             U1TXBUF_  /* USART 1 Transmit Buffer */
#define UCTL_1              U1CTL     /* USART 1 Control */
#define UTCTL_1             U1TCTL    /* USART 1 Transmit Control */
#define URCTL_1             U1RCTL    /* USART 1 Receive Control */
#define UMCTL_1             U1MCTL    /* USART 1 Modulation Control */
#define UBR0_1              U1BR0     /* USART 1 Baud Rate 0 */
#define UBR1_1              U1BR1     /* USART 1 Baud Rate 1 */
#define RXBUF_1             U1RXBUF   /* USART 1 Receive Buffer */
#define TXBUF_1             U1TXBUF   /* USART 1 Transmit Buffer */
#define UCTL_1_             U1CTL_    /* USART 1 Control */
#define UTCTL_1_            U1TCTL_   /* USART 1 Transmit Control */
#define URCTL_1_            U1RCTL_   /* USART 1 Receive Control */
#define UMCTL_1_            U1MCTL_   /* USART 1 Modulation Control */
#define UBR0_1_             U1BR0_    /* USART 1 Baud Rate 0 */
#define UBR1_1_             U1BR1_    /* USART 1 Baud Rate 1 */
#define RXBUF_1_            U1RXBUF_  /* USART 1 Receive Buffer */
#define TXBUF_1_            U1TXBUF_  /* USART 1 Transmit Buffer */

/*-------------------------------------------------------------------------
 *   Timer A3
 *-------------------------------------------------------------------------*/



  /* Timer A Interrupt Vector Word */
__no_init volatile unsigned __READ short TAIV @ 0x012E;



__no_init volatile union
{
  unsigned short TACTL;   /* Timer A Control */

  struct
  {
    unsigned short TAIFG           : 1; /* Timer A counter interrupt flag */
    unsigned short TAIE            : 1; /* Timer A counter interrupt enable */
    unsigned short TACLR           : 1; /* Timer A counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TASSEL0         : 1; /* Timer A clock source select 0 */
    unsigned short TASSEL1         : 1; /* Timer A clock source select 1 */
  }TACTL_bit;
} @0x0160;


enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200
};


__no_init volatile union
{
  unsigned short TACCTL0;   /* Timer A Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL0_bit;
} @0x0162;


enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000
};


__no_init volatile union
{
  unsigned short TACCTL1;   /* Timer A Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL1_bit;
} @0x0164;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TACCTL2;   /* Timer A Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TACCTL2_bit;
} @0x0166;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer A Counter Register */
__no_init volatile unsigned short TAR @ 0x0170;



  /* Timer A Capture/Compare 0 */
__no_init volatile unsigned short TACCR0 @ 0x0172;



  /* Timer A Capture/Compare 1 */
__no_init volatile unsigned short TACCR1 @ 0x0174;



  /* Timer A Capture/Compare 2 */
__no_init volatile unsigned short TACCR2 @ 0x0176;


#define __MSP430_HAS_TA3__            /* Definition to show that Module is available */
/* Alternate register names */
#define CCTL0               TACCTL0   /* Timer A Capture/Compare Control 0 */
#define CCTL1               TACCTL1   /* Timer A Capture/Compare Control 1 */
#define CCTL2               TACCTL2   /* Timer A Capture/Compare Control 2 */
#define CCR0                TACCR0    /* Timer A Capture/Compare 0 */
#define CCR1                TACCR1    /* Timer A Capture/Compare 1 */
#define CCR2                TACCR2    /* Timer A Capture/Compare 2 */
#define CCTL0_              TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define CCTL1_              TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define CCTL2_              TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define CCR0_               TACCR0_   /* Timer A Capture/Compare 0 */
#define CCR1_               TACCR1_   /* Timer A Capture/Compare 1 */
#define CCR2_               TACCR2_   /* Timer A Capture/Compare 2 */
/* Alternate register names - 5xx style */
#define TA0IV               TAIV      /* Timer A Interrupt Vector Word */
#define TA0CTL              TACTL     /* Timer A Control */
#define TA0CCTL0            TACCTL0   /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1            TACCTL1   /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2            TACCTL2   /* Timer A Capture/Compare Control 2 */
#define TA0R                TAR       /* Timer A Counter Register */
#define TA0CCR0             TACCR0    /* Timer A Capture/Compare 0 */
#define TA0CCR1             TACCR1    /* Timer A Capture/Compare 1 */
#define TA0CCR2             TACCR2    /* Timer A Capture/Compare 2 */
#define TA0IV_              TAIV_     /* Timer A Interrupt Vector Word */
#define TA0CTL_             TACTL_    /* Timer A Control */
#define TA0CCTL0_           TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_           TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2_           TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define TA0R_               TAR_      /* Timer A Counter Register */
#define TA0CCR0_            TACCR0_   /* Timer A Capture/Compare 0 */
#define TA0CCR1_            TACCR1_   /* Timer A Capture/Compare 1 */
#define TA0CCR2_            TACCR2_   /* Timer A Capture/Compare 2 */
#define TIMER0_A1_VECTOR    TIMERA1_VECTOR /* Int. Vector: Timer A CC1-2, TA */
#define TIMER0_A0_VECTOR    TIMERA0_VECTOR /* Int. Vector: Timer A CC0 */

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */
/* TA3IV Definitions */
#define TAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define TAIV_TACCR1         (0x0002u)    /* TACCR1_CCIFG */
#define TAIV_TACCR2         (0x0004u)    /* TACCR2_CCIFG */
#define TAIV_6              (0x0006u)    /* Reserved */
#define TAIV_8              (0x0008u)    /* Reserved */
#define TAIV_TAIFG          (0x000Au)    /* TAIFG */
/* Alternate register names - 5xx style */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TACCR1        (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2        (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_6             (0x0006u)    /* Reserved */
#define TA0IV_8             (0x0008u)    /* Reserved */
#define TA0IV_TAIFG         (0x000Au)    /* TA0IFG */

/*-------------------------------------------------------------------------
 *   Timer B7
 *-------------------------------------------------------------------------*/



  /* Timer B Interrupt Vector Word */
__no_init volatile unsigned __READ short TBIV @ 0x011E;



__no_init volatile union
{
  unsigned short TBCTL;   /* Timer B Control */

  struct
  {
    unsigned short TBIFG           : 1; /* Timer B interrupt flag */
    unsigned short TBIE            : 1; /* Timer B interrupt enable */
    unsigned short TBCLR           : 1; /* Timer B counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TBSSEL0         : 1; /* Clock source 0 */
    unsigned short TBSSEL1         : 1; /* Clock source 1 */
    unsigned short                : 1;
    unsigned short CNTL0           : 1; /* Counter lenght 0 */
    unsigned short CNTL1           : 1; /* Counter lenght 1 */
    unsigned short TBCLGRP0        : 1; /* Timer B Compare latch load group 0 */
    unsigned short TBCLGRP1        : 1; /* Timer B Compare latch load group 1 */
  }TBCTL_bit;
} @0x0180;


enum {
  TBIFG           = 0x0001,
  TBIE            = 0x0002,
  TBCLR           = 0x0004,
/*  MC0             = 0x0010, */
/*  MC1             = 0x0020, */
/*  ID0             = 0x0040, */
/*  ID1             = 0x0080, */
  TBSSEL0         = 0x0100,
  TBSSEL1         = 0x0200,
  CNTL0           = 0x0800,
  CNTL1           = 0x1000,
  TBCLGRP0        = 0x2000,
  TBCLGRP1        = 0x4000
};


__no_init volatile union
{
  unsigned short TBCCTL0;   /* Timer B Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL0_bit;
} @0x0182;


enum {
/*  CCIFG           = 0x0001, */
/*  COV             = 0x0002, */
/*  OUT             = 0x0004, */
/*  CCI             = 0x0008, */
/*  CCIE            = 0x0010, */
/*  OUTMOD0         = 0x0020, */
/*  OUTMOD1         = 0x0040, */
/*  OUTMOD2         = 0x0080, */
/*  CAP             = 0x0100, */
  CLLD0           = 0x0200,
  CLLD1           = 0x0400
/*  SCS             = 0x0800, */
/*  CCIS0           = 0x1000, */
/*  CCIS1           = 0x2000, */
/*  CM0             = 0x4000, */
/*  CM1             = 0x8000, */
};


__no_init volatile union
{
  unsigned short TBCCTL1;   /* Timer B Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL1_bit;
} @0x0184;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TBCCTL2;   /* Timer B Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL2_bit;
} @0x0186;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TBCCTL3;   /* Timer B Capture/Compare Control 3 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL3_bit;
} @0x0188;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TBCCTL4;   /* Timer B Capture/Compare Control 4 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL4_bit;
} @0x018A;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TBCCTL5;   /* Timer B Capture/Compare Control 5 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL5_bit;
} @0x018C;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TBCCTL6;   /* Timer B Capture/Compare Control 6 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TBCCTL6_bit;
} @0x018E;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer B Counter Register */
__no_init volatile unsigned short TBR @ 0x0190;



  /* Timer B Capture/Compare 0 */
__no_init volatile unsigned short TBCCR0 @ 0x0192;



  /* Timer B Capture/Compare 1 */
__no_init volatile unsigned short TBCCR1 @ 0x0194;



  /* Timer B Capture/Compare 2 */
__no_init volatile unsigned short TBCCR2 @ 0x0196;



  /* Timer B Capture/Compare 3 */
__no_init volatile unsigned short TBCCR3 @ 0x0198;



  /* Timer B Capture/Compare 4 */
__no_init volatile unsigned short TBCCR4 @ 0x019A;



  /* Timer B Capture/Compare 5 */
__no_init volatile unsigned short TBCCR5 @ 0x019C;



  /* Timer B Capture/Compare 6 */
__no_init volatile unsigned short TBCCR6 @ 0x019E;


#define __MSP430_HAS_TB7__            /* Definition to show that Module is available */
/* Alternate register names - 5xx style */
#define TB0IV               TBIV      /* Timer B Interrupt Vector Word */
#define TB0CTL              TBCTL     /* Timer B Control */
#define TB0CCTL0            TBCCTL0   /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1            TBCCTL1   /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2            TBCCTL2   /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3            TBCCTL3   /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4            TBCCTL4   /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5            TBCCTL5   /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6            TBCCTL6   /* Timer B Capture/Compare Control 6 */
#define TB0R                TBR       /* Timer B Counter Register */
#define TB0CCR0             TBCCR0    /* Timer B Capture/Compare 0 */
#define TB0CCR1             TBCCR1    /* Timer B Capture/Compare 1 */
#define TB0CCR2             TBCCR2    /* Timer B Capture/Compare 2 */
#define TB0CCR3             TBCCR3    /* Timer B Capture/Compare 3 */
#define TB0CCR4             TBCCR4    /* Timer B Capture/Compare 4 */
#define TB0CCR5             TBCCR5    /* Timer B Capture/Compare 5 */
#define TB0CCR6             TBCCR6    /* Timer B Capture/Compare 6 */
#define TB0IV_              TBIV_     /* Timer B Interrupt Vector Word */
#define TB0CTL_             TBCTL_    /* Timer B Control */
#define TB0CCTL0_           TBCCTL0_  /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1_           TBCCTL1_  /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2_           TBCCTL2_  /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3_           TBCCTL3_  /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4_           TBCCTL4_  /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5_           TBCCTL5_  /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6_           TBCCTL6_  /* Timer B Capture/Compare Control 6 */
#define TB0R_               TBR_      /* Timer B Counter Register */
#define TB0CCR0_            TBCCR0_   /* Timer B Capture/Compare 0 */
#define TB0CCR1_            TBCCR1_   /* Timer B Capture/Compare 1 */
#define TB0CCR2_            TBCCR2_   /* Timer B Capture/Compare 2 */
#define TB0CCR3_            TBCCR3_   /* Timer B Capture/Compare 3 */
#define TB0CCR4_            TBCCR4_   /* Timer B Capture/Compare 4 */
#define TB0CCR5_            TBCCR5_   /* Timer B Capture/Compare 5 */
#define TB0CCR6_            TBCCR6_   /* Timer B Capture/Compare 6 */
#define TIMER0_B1_VECTOR    TIMERB1_VECTOR /* Int. Vector: Timer B CC1-6, TB */
#define TIMER0_B0_VECTOR    TIMERB0_VECTOR /* Int. Vector: Timer B CC0 */

#define SHR1                (0x4000u)  /* Timer B Compare latch load group 1 */
#define SHR0                (0x2000u)  /* Timer B Compare latch load group 0 */

#define TBSSEL_0            (0*0x0100u)  /* Clock Source: TBCLK */
#define TBSSEL_1            (1*0x0100u)  /* Clock Source: ACLK  */
#define TBSSEL_2            (2*0x0100u)  /* Clock Source: SMCLK */
#define TBSSEL_3            (3*0x0100u)  /* Clock Source: INCLK */
#define CNTL_0              (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL_1              (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL_2              (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL_3              (3*0x0800u)  /* Counter lenght:  8 bit */
#define SHR_0               (0*0x2000u)  /* Timer B Group: 0 - individually */
#define SHR_1               (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0*0x2000u)  /* Timer B Group: 0 - individually */
#define TBCLGRP_1           (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */

#define SLSHR1              (0x0400u)  /* Compare latch load source 1 */
#define SLSHR0              (0x0200u)  /* Compare latch load source 0 */

#define SLSHR_0             (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1             (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2             (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3             (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define CLLD_1              (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2              (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define CLLD_3              (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */
/* TB7IV Definitions */
#define TBIV_NONE           (0x0000u)    /* No Interrupt pending */
#define TBIV_TBCCR1         (0x0002u)    /* TBCCR1_CCIFG */
#define TBIV_TBCCR2         (0x0004u)    /* TBCCR2_CCIFG */
#define TBIV_TBCCR3         (0x0006u)    /* TBCCR3_CCIFG */
#define TBIV_TBCCR4         (0x0008u)    /* TBCCR4_CCIFG */
#define TBIV_TBCCR5         (0x000Au)    /* TBCCR3_CCIFG */
#define TBIV_TBCCR6         (0x000Cu)    /* TBCCR4_CCIFG */
#define TBIV_TBIFG          (0x000Eu)    /* TBIFG */
/* Alternate register names - 5xx style */
#define TB0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TB0IV_TBCCR1        (0x0002u)    /* TB0CCR1_CCIFG */
#define TB0IV_TBCCR2        (0x0004u)    /* TB0CCR2_CCIFG */
#define TB0IV_TBCCR3        (0x0006u)    /* TB0CCR3_CCIFG */
#define TB0IV_TBCCR4        (0x0008u)    /* TB0CCR4_CCIFG */
#define TB0IV_TBCCR5        (0x000Au)    /* TB0CCR3_CCIFG */
#define TB0IV_TBCCR6        (0x000Cu)    /* TB0CCR4_CCIFG */
#define TB0IV_TBIFG         (0x000Eu)    /* TB0IFG */

/*-------------------------------------------------------------------------
 *   System Clock
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char DCOCTL;   /* DCO Clock Frequency Control */

  struct
  {
    unsigned char MOD0            : 1; /* Modulation Bit 0 */
    unsigned char MOD1            : 1; /* Modulation Bit 1 */
    unsigned char MOD2            : 1; /* Modulation Bit 2 */
    unsigned char MOD3            : 1; /* Modulation Bit 3 */
    unsigned char MOD4            : 1; /* Modulation Bit 4 */
    unsigned char DCO0            : 1; /* DCO Select Bit 0 */
    unsigned char DCO1            : 1; /* DCO Select Bit 1 */
    unsigned char DCO2            : 1; /* DCO Select Bit 2 */
  }DCOCTL_bit;
} @0x0056;


enum {
  MOD0            = 0x0001,
  MOD1            = 0x0002,
  MOD2            = 0x0004,
  MOD3            = 0x0008,
  MOD4            = 0x0010,
  DCO0            = 0x0020,
  DCO1            = 0x0040,
  DCO2            = 0x0080
};


__no_init volatile union
{
  unsigned char BCSCTL1;   /* Basic Clock System Control 1 */

  struct
  {
    unsigned char RSEL0           : 1; /* Range Select Bit 0 */
    unsigned char RSEL1           : 1; /* Range Select Bit 1 */
    unsigned char RSEL2           : 1; /* Range Select Bit 2 */
    unsigned char XT5V            : 1; /* XT5V should always be reset */
    unsigned char DIVA0           : 1; /* ACLK Divider 0 */
    unsigned char DIVA1           : 1; /* ACLK Divider 1 */
    unsigned char XTS             : 1; /* LFXTCLK 0:Low Freq. / 1: High Freq. */
    unsigned char XT2OFF          : 1; /* Enable XT2CLK */
  }BCSCTL1_bit;
} @0x0057;


enum {
  RSEL0           = 0x0001,
  RSEL1           = 0x0002,
  RSEL2           = 0x0004,
  XT5V            = 0x0008,
  DIVA0           = 0x0010,
  DIVA1           = 0x0020,
  XTS             = 0x0040,
  XT2OFF          = 0x0080
};


__no_init volatile union
{
  unsigned char BCSCTL2;   /* Basic Clock System Control 2 */

  struct
  {
    unsigned char DCOR            : 1; /* Enable External Resistor : 1 */
    unsigned char DIVS0           : 1; /* SMCLK Divider 0 */
    unsigned char DIVS1           : 1; /* SMCLK Divider 1 */
    unsigned char SELS            : 1; /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
    unsigned char DIVM0           : 1; /* MCLK Divider 0 */
    unsigned char DIVM1           : 1; /* MCLK Divider 1 */
    unsigned char SELM0           : 1; /* MCLK Source Select 0 */
    unsigned char SELM1           : 1; /* MCLK Source Select 1 */
  }BCSCTL2_bit;
} @ 0x0058;


enum {
  DCOR            = 0x0001,
  DIVS0           = 0x0002,
  DIVS1           = 0x0004,
  SELS            = 0x0008,
  DIVM0           = 0x0010,
  DIVM1           = 0x0020,
  SELM0           = 0x0040,
  SELM1           = 0x0080
};



#define __MSP430_HAS_BASIC_CLOCK__    /* Definition to show that Module is available */

#define DIVA_0              (0x00)   /* ACLK Divider 0: /1 */
#define DIVA_1              (0x10)   /* ACLK Divider 1: /2 */
#define DIVA_2              (0x20)   /* ACLK Divider 2: /4 */
#define DIVA_3              (0x30)   /* ACLK Divider 3: /8 */

#define DIVS_0              (0x00)   /* SMCLK Divider 0: /1 */
#define DIVS_1              (0x02)   /* SMCLK Divider 1: /2 */
#define DIVS_2              (0x04)   /* SMCLK Divider 2: /4 */
#define DIVS_3              (0x06)   /* SMCLK Divider 3: /8 */

#define DIVM_0              (0x00)   /* MCLK Divider 0: /1 */
#define DIVM_1              (0x10)   /* MCLK Divider 1: /2 */
#define DIVM_2              (0x20)   /* MCLK Divider 2: /4 */
#define DIVM_3              (0x30)   /* MCLK Divider 3: /8 */

#define SELM_0              (0x00)   /* MCLK Source Select 0: DCOCLK */
#define SELM_1              (0x40)   /* MCLK Source Select 1: DCOCLK */
#define SELM_2              (0x80)   /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3              (0xC0)   /* MCLK Source Select 3: LFXTCLK */

/*-------------------------------------------------------------------------
 *   Flash
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short FCTL1;   /* FLASH Control 1 */

  struct
  {
    unsigned short                : 1;
    unsigned short ERASE           : 1; /* Enable bit for Flash segment erase */
    unsigned short MERAS           : 1; /* Enable bit for Flash mass erase */
    unsigned short                : 3;
    unsigned short WRT             : 1; /* Enable bit for Flash write */
    unsigned short BLKWRT          : 1; /* Enable bit for Flash segment write */
  }FCTL1_bit;
} @0x0128;


enum {
  ERASE           = 0x0002,
  MERAS           = 0x0004,
  WRT             = 0x0040,
  BLKWRT          = 0x0080
};


__no_init volatile union
{
  unsigned short FCTL2;   /* FLASH Control 2 */

  struct
  {
    unsigned short FN0             : 1; /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to: */
    unsigned short FN1             : 1; /* 32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1 */
    unsigned short FN2             : 1; /*  */
    unsigned short FN3             : 1; /*  */
    unsigned short FN4             : 1; /*  */
    unsigned short FN5             : 1; /*  */
    unsigned short FSSEL0          : 1; /* Flash clock select 0 */        /* to distinguish from USART SSELx */
    unsigned short FSSEL1          : 1; /* Flash clock select 1 */
  }FCTL2_bit;
} @0x012A;


enum {
  FN0             = 0x0001,
  FN1             = 0x0002,
  FN2             = 0x0004,
  FN3             = 0x0008,
  FN4             = 0x0010,
  FN5             = 0x0020,
  FSSEL0          = 0x0040,
  FSSEL1          = 0x0080
};


__no_init volatile union
{
  unsigned short FCTL3;   /* FLASH Control 3 */

  struct
  {
    unsigned short BUSY            : 1; /* Flash busy: 1 */
    unsigned short KEYV            : 1; /* Flash Key violation flag */
    unsigned short ACCVIFG         : 1; /* Flash Access violation flag */
    unsigned short WAIT            : 1; /* Wait flag for segment write */
    unsigned short LOCK            : 1; /* Lock bit: 1 - Flash is locked (read only) */
    unsigned short EMEX            : 1; /* Flash Emergency Exit */
  }FCTL3_bit;
} @ 0x012C;


enum {
  BUSY            = 0x0001,
  KEYV            = 0x0002,
  ACCVIFG         = 0x0004,
  WAIT            = 0x0008,
  LOCK            = 0x0010,
  EMEX            = 0x0020
};



#define __MSP430_HAS_FLASH__          /* Definition to show that Module is available */

#define FRKEY               (0x9600u)  /* Flash key returned by read */
#define FWKEY               (0xA500u)  /* Flash key for write */
#define FXKEY               (0x3300u)  /* for use with XOR instruction */
#define SEGWRT              (0x0080u)  /* old definition */ /* Enable bit for Flash segment write */

#define FSSEL_0             (0x0000u)  /* Flash clock select: 0 - ACLK */
#define FSSEL_1             (0x0040u)  /* Flash clock select: 1 - MCLK */
#define FSSEL_2             (0x0080u)  /* Flash clock select: 2 - SMCLK */
#define FSSEL_3             (0x00C0u)  /* Flash clock select: 3 - SMCLK */

/*-------------------------------------------------------------------------
 *   Comparator A
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned char CACTL1;   /* Comparator A Control 1 */

  struct
  {
    unsigned char CAIFG           : 1; /* Comp. A Interrupt Flag */
    unsigned char CAIE            : 1; /* Comp. A Interrupt Enable */
    unsigned char CAIES           : 1; /* Comp. A Int. Edge Select: 0:rising / 1:falling */
    unsigned char CAON            : 1; /* Comp. A enable */
    unsigned char CAREF0          : 1; /* Comp. A Internal Reference Select 0 */
    unsigned char CAREF1          : 1; /* Comp. A Internal Reference Select 1 */
    unsigned char CARSEL          : 1; /* Comp. A Internal Reference Enable */
    unsigned char CAEX            : 1; /* Comp. A Exchange Inputs */
  }CACTL1_bit;
} @0x0059;


enum {
  CAIFG           = 0x0001,
  CAIE            = 0x0002,
  CAIES           = 0x0004,
  CAON            = 0x0008,
  CAREF0          = 0x0010,
  CAREF1          = 0x0020,
  CARSEL          = 0x0040,
  CAEX            = 0x0080
};


__no_init volatile union
{
  unsigned char CACTL2;   /* Comparator A Control 2 */

  struct
  {
    unsigned char CAOUT           : 1; /* Comp. A Output */
    unsigned char CAF             : 1; /* Comp. A Enable Output Filter */
    unsigned char P2CA0           : 1; /* Comp. A Connect External Signal to CA0 : 1 */
    unsigned char P2CA1           : 1; /* Comp. A Connect External Signal to CA1 : 1 */
    unsigned char CACTL24         : 1; /*  */
    unsigned char CACTL25         : 1; /*  */
    unsigned char CACTL26         : 1; /*  */
    unsigned char CACTL27         : 1; /*  */
  }CACTL2_bit;
} @0x005A;


enum {
  CAOUT           = 0x0001,
  CAF             = 0x0002,
  P2CA0           = 0x0004,
  P2CA1           = 0x0008,
  CACTL24         = 0x0010,
  CACTL25         = 0x0020,
  CACTL26         = 0x0040,
  CACTL27         = 0x0080
};


__no_init volatile union
{
  unsigned char CAPD;   /* Comparator A Port Disable */

  struct
  {
    unsigned char CAPD0           : 1; /* Comp. A Disable Input Buffer of Port Register .0 */
    unsigned char CAPD1           : 1; /* Comp. A Disable Input Buffer of Port Register .1 */
    unsigned char CAPD2           : 1; /* Comp. A Disable Input Buffer of Port Register .2 */
    unsigned char CAPD3           : 1; /* Comp. A Disable Input Buffer of Port Register .3 */
    unsigned char CAPD4           : 1; /* Comp. A Disable Input Buffer of Port Register .4 */
    unsigned char CAPD5           : 1; /* Comp. A Disable Input Buffer of Port Register .5 */
    unsigned char CAPD6           : 1; /* Comp. A Disable Input Buffer of Port Register .6 */
    unsigned char CAPD7           : 1; /* Comp. A Disable Input Buffer of Port Register .7 */
  }CAPD_bit;
} @ 0x005B;


enum {
  CAPD0           = 0x0001,
  CAPD1           = 0x0002,
  CAPD2           = 0x0004,
  CAPD3           = 0x0008,
  CAPD4           = 0x0010,
  CAPD5           = 0x0020,
  CAPD6           = 0x0040,
  CAPD7           = 0x0080
};



#define __MSP430_HAS_COMPA__          /* Definition to show that Module is available */

#define CAREF_0             (0x00)    /* Comp. A Int. Ref. Select 0 : Off */
#define CAREF_1             (0x10)    /* Comp. A Int. Ref. Select 1 : 0.25*Vcc */
#define CAREF_2             (0x20)    /* Comp. A Int. Ref. Select 2 : 0.5*Vcc */
#define CAREF_3             (0x30)    /* Comp. A Int. Ref. Select 3 : Vt*/

/*-------------------------------------------------------------------------
 *   ADC12
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short ADC12CTL0;   /* ADC12 Control 0 */

  struct
  {
    unsigned short ADC12SC         : 1; /* ADC12 Start Conversion */
    unsigned short ENC             : 1; /* ADC12 Enable Conversion */
    unsigned short ADC12TOVIE      : 1; /* ADC12 Timer Overflow interrupt enable */
    unsigned short ADC12OVIE       : 1; /* ADC12 Overflow interrupt enable */
    unsigned short ADC12ON         : 1; /* ADC12 On/enable */
    unsigned short REFON           : 1; /* ADC12 Reference on */
    unsigned short REF2_5V         : 1; /*  */
    unsigned short MSC             : 1; /* ADC12 Multiple SampleConversion */
    unsigned short SHT00           : 1; /* ADC12 Sample Hold 0 Select 0 */
    unsigned short SHT01           : 1; /* ADC12 Sample Hold 0 Select 1 */
    unsigned short SHT02           : 1; /* ADC12 Sample Hold 0 Select 2 */
    unsigned short SHT03           : 1; /* ADC12 Sample Hold 0 Select 3 */
    unsigned short SHT10           : 1; /* ADC12 Sample Hold 0 Select 0 */
    unsigned short SHT11           : 1; /* ADC12 Sample Hold 1 Select 1 */
    unsigned short SHT12           : 1; /* ADC12 Sample Hold 2 Select 2 */
    unsigned short SHT13           : 1; /* ADC12 Sample Hold 3 Select 3 */
  }ADC12CTL0_bit;
} @0x01A0;


enum {
  ADC12SC         = 0x0001,
  ENC             = 0x0002,
  ADC12TOVIE      = 0x0004,
  ADC12OVIE       = 0x0008,
  ADC12ON         = 0x0010,
  REFON           = 0x0020,
  REF2_5V         = 0x0040,
  MSC             = 0x0080,
  SHT00           = 0x0100,
  SHT01           = 0x0200,
  SHT02           = 0x0400,
  SHT03           = 0x0800,
  SHT10           = 0x1000,
  SHT11           = 0x2000,
  SHT12           = 0x4000,
  SHT13           = 0x8000
};


__no_init volatile union
{
  unsigned short ADC12CTL1;   /* ADC12 Control 1 */

  struct
  {
    unsigned short ADC12BUSY       : 1; /* ADC12 Busy */
    unsigned short CONSEQ0         : 1; /* ADC12 Conversion Sequence Select 0 */
    unsigned short CONSEQ1         : 1; /* ADC12 Conversion Sequence Select 1 */
    unsigned short ADC12SSEL0      : 1; /* ADC12 Clock Source Select 0 */
    unsigned short ADC12SSEL1      : 1; /* ADC12 Clock Source Select 1 */
    unsigned short ADC12DIV0       : 1; /* ADC12 Clock Divider Select 0 */
    unsigned short ADC12DIV1       : 1; /* ADC12 Clock Divider Select 1 */
    unsigned short ADC12DIV2       : 1; /* ADC12 Clock Divider Select 2 */
    unsigned short ISSH            : 1; /* ADC12 Invert Sample Hold Signal */
    unsigned short SHP             : 1; /* ADC12 Sample/Hold Pulse Mode */
    unsigned short SHS0            : 1; /* ADC12 Sample/Hold Source 0 */
    unsigned short SHS1            : 1; /* ADC12 Sample/Hold Source 1 */
    unsigned short CSTARTADD0      : 1; /* ADC12 Conversion Start Address 0 */
    unsigned short CSTARTADD1      : 1; /* ADC12 Conversion Start Address 1 */
    unsigned short CSTARTADD2      : 1; /* ADC12 Conversion Start Address 2 */
    unsigned short CSTARTADD3      : 1; /* ADC12 Conversion Start Address 3 */
  }ADC12CTL1_bit;
} @0x01A2;


enum {
  ADC12BUSY       = 0x0001,
  CONSEQ0         = 0x0002,
  CONSEQ1         = 0x0004,
  ADC12SSEL0      = 0x0008,
  ADC12SSEL1      = 0x0010,
  ADC12DIV0       = 0x0020,
  ADC12DIV1       = 0x0040,
  ADC12DIV2       = 0x0080,
  ISSH            = 0x0100,
  SHP             = 0x0200,
  SHS0            = 0x0400,
  SHS1            = 0x0800,
  CSTARTADD0      = 0x1000,
  CSTARTADD1      = 0x2000,
  CSTARTADD2      = 0x4000,
  CSTARTADD3      = 0x8000
};


  /* ADC12 Interrupt Flag */
__no_init volatile unsigned short ADC12IFG @ 0x01A4;



  /* ADC12 Interrupt Enable */
__no_init volatile unsigned short ADC12IE @ 0x01A6;



  /* ADC12 Interrupt Vector Word */
__no_init volatile unsigned short ADC12IV @ 0x01A8;



  /* ADC12 Conversion Memory 0 */
__no_init volatile unsigned short ADC12MEM0 @ 0x0140;



  /* ADC12 Conversion Memory 1 */
__no_init volatile unsigned short ADC12MEM1 @ 0x0142;



  /* ADC12 Conversion Memory 2 */
__no_init volatile unsigned short ADC12MEM2 @ 0x0144;



  /* ADC12 Conversion Memory 3 */
__no_init volatile unsigned short ADC12MEM3 @ 0x0146;



  /* ADC12 Conversion Memory 4 */
__no_init volatile unsigned short ADC12MEM4 @ 0x0148;



  /* ADC12 Conversion Memory 5 */
__no_init volatile unsigned short ADC12MEM5 @ 0x014A;



  /* ADC12 Conversion Memory 6 */
__no_init volatile unsigned short ADC12MEM6 @ 0x014C;



  /* ADC12 Conversion Memory 7 */
__no_init volatile unsigned short ADC12MEM7 @ 0x014E;



  /* ADC12 Conversion Memory 8 */
__no_init volatile unsigned short ADC12MEM8 @ 0x0150;



  /* ADC12 Conversion Memory 9 */
__no_init volatile unsigned short ADC12MEM9 @ 0x0152;



  /* ADC12 Conversion Memory 10 */
__no_init volatile unsigned short ADC12MEM10 @ 0x0154;



  /* ADC12 Conversion Memory 11 */
__no_init volatile unsigned short ADC12MEM11 @ 0x0156;



  /* ADC12 Conversion Memory 12 */
__no_init volatile unsigned short ADC12MEM12 @ 0x0158;



  /* ADC12 Conversion Memory 13 */
__no_init volatile unsigned short ADC12MEM13 @ 0x015A;



  /* ADC12 Conversion Memory 14 */
__no_init volatile unsigned short ADC12MEM14 @ 0x015C;



  /* ADC12 Conversion Memory 15 */
__no_init volatile unsigned short ADC12MEM15 @ 0x015E;



__no_init volatile union
{
  unsigned char ADC12MCTL0;   /* ADC12 Memory Control 0 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL0_bit;
} @0x0080;


enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080
};


__no_init volatile union
{
  unsigned char ADC12MCTL1;   /* ADC12 Memory Control 1 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL1_bit;
} @0x0081;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL2;   /* ADC12 Memory Control 2 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL2_bit;
} @0x0082;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL3;   /* ADC12 Memory Control 3 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL3_bit;
} @0x0083;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL4;   /* ADC12 Memory Control 4 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL4_bit;
} @0x0084;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL5;   /* ADC12 Memory Control 5 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL5_bit;
} @0x0085;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL6;   /* ADC12 Memory Control 6 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL6_bit;
} @0x0086;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL7;   /* ADC12 Memory Control 7 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL7_bit;
} @0x0087;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL8;   /* ADC12 Memory Control 8 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL8_bit;
} @0x0088;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL9;   /* ADC12 Memory Control 9 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL9_bit;
} @0x0089;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL10;   /* ADC12 Memory Control 10 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL10_bit;
} @0x008A;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL11;   /* ADC12 Memory Control 11 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL11_bit;
} @0x008B;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL12;   /* ADC12 Memory Control 12 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL12_bit;
} @0x008C;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL13;   /* ADC12 Memory Control 13 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL13_bit;
} @0x008D;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL14;   /* ADC12 Memory Control 14 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL14_bit;
} @0x008E;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL15;   /* ADC12 Memory Control 15 */

  struct
  {
    unsigned char INCH0           : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char INCH1           : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char INCH2           : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char INCH3           : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char SREF0           : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char SREF1           : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char SREF2           : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char EOS             : 1; /* ADC12 End of Sequence */
  }ADC12MCTL15_bit;
} @ 0x008F;


/*
enum {
  INCH0           = 0x0001,
  INCH1           = 0x0002,
  INCH2           = 0x0004,
  INCH3           = 0x0008,
  SREF0           = 0x0010,
  SREF1           = 0x0020,
  SREF2           = 0x0040,
  EOS             = 0x0080
};
*/



#define __MSP430_HAS_ADC12__          /* Definition to show that Module is available */

#define ADC12MEM_           (0x0140u)  /* ADC12 Conversion Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MEM            (ADC12MEM_) /* ADC12 Conversion Memory (for assembler) */
#else
#define ADC12MEM            ((int*) ADC12MEM_) /* ADC12 Conversion Memory (for C) */
#endif

#define ADC12MCTL_          (0x0080u)  /* ADC12 Memory Control */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MCTL           (ADC12MCTL_) /* ADC12 Memory Control (for assembler) */
#else
#define ADC12MCTL           ((char*) ADC12MCTL_) /* ADC12 Memory Control (for C) */
#endif
#define MSH                 (0x080)

#define SHT0_0               (0*0x100u) /* ADC12 Sample Hold 0 Select Bit: 0 */
#define SHT0_1               (1*0x100u) /* ADC12 Sample Hold 0 Select Bit: 1 */
#define SHT0_2               (2*0x100u) /* ADC12 Sample Hold 0 Select Bit: 2 */
#define SHT0_3               (3*0x100u) /* ADC12 Sample Hold 0 Select Bit: 3 */
#define SHT0_4               (4*0x100u) /* ADC12 Sample Hold 0 Select Bit: 4 */
#define SHT0_5               (5*0x100u) /* ADC12 Sample Hold 0 Select Bit: 5 */
#define SHT0_6               (6*0x100u) /* ADC12 Sample Hold 0 Select Bit: 6 */
#define SHT0_7               (7*0x100u) /* ADC12 Sample Hold 0 Select Bit: 7 */
#define SHT0_8               (8*0x100u) /* ADC12 Sample Hold 0 Select Bit: 8 */
#define SHT0_9               (9*0x100u) /* ADC12 Sample Hold 0 Select Bit: 9 */
#define SHT0_10             (10*0x100u) /* ADC12 Sample Hold 0 Select Bit: 10 */
#define SHT0_11             (11*0x100u) /* ADC12 Sample Hold 0 Select Bit: 11 */
#define SHT0_12             (12*0x100u) /* ADC12 Sample Hold 0 Select Bit: 12 */
#define SHT0_13             (13*0x100u) /* ADC12 Sample Hold 0 Select Bit: 13 */
#define SHT0_14             (14*0x100u) /* ADC12 Sample Hold 0 Select Bit: 14 */
#define SHT0_15             (15*0x100u) /* ADC12 Sample Hold 0 Select Bit: 15 */

#define SHT1_0               (0*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 0 */
#define SHT1_1               (1*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 1 */
#define SHT1_2               (2*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 2 */
#define SHT1_3               (3*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 3 */
#define SHT1_4               (4*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 4 */
#define SHT1_5               (5*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 5 */
#define SHT1_6               (6*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 6 */
#define SHT1_7               (7*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 7 */
#define SHT1_8               (8*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 8 */
#define SHT1_9               (9*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 9 */
#define SHT1_10             (10*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 10 */
#define SHT1_11             (11*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 11 */
#define SHT1_12             (12*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 12 */
#define SHT1_13             (13*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 13 */
#define SHT1_14             (14*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 14 */
#define SHT1_15             (15*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 15 */

#define CONSEQ_0             (0*2u)      /* ADC12 Conversion Sequence Select: 0 */
#define CONSEQ_1             (1*2u)      /* ADC12 Conversion Sequence Select: 1 */
#define CONSEQ_2             (2*2u)      /* ADC12 Conversion Sequence Select: 2 */
#define CONSEQ_3             (3*2u)      /* ADC12 Conversion Sequence Select: 3 */
#define ADC12SSEL_0          (0*8u)      /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1          (1*8u)      /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2          (2*8u)      /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3          (3*8u)      /* ADC12 Clock Source Select: 3 */
#define ADC12DIV_0           (0*0x20u)   /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1           (1*0x20u)   /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2           (2*0x20u)   /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3           (3*0x20u)   /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4           (4*0x20u)   /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5           (5*0x20u)   /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6           (6*0x20u)   /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7           (7*0x20u)   /* ADC12 Clock Divider Select: 7 */
#define SHS_0                (0*0x400u)  /* ADC12 Sample/Hold Source: 0 */
#define SHS_1                (1*0x400u)  /* ADC12 Sample/Hold Source: 1 */
#define SHS_2                (2*0x400u)  /* ADC12 Sample/Hold Source: 2 */
#define SHS_3                (3*0x400u)  /* ADC12 Sample/Hold Source: 3 */
#define CSTARTADD_0          (0*0x1000u) /* ADC12 Conversion Start Address: 0 */
#define CSTARTADD_1          (1*0x1000u) /* ADC12 Conversion Start Address: 1 */
#define CSTARTADD_2          (2*0x1000u) /* ADC12 Conversion Start Address: 2 */
#define CSTARTADD_3          (3*0x1000u) /* ADC12 Conversion Start Address: 3 */
#define CSTARTADD_4          (4*0x1000u) /* ADC12 Conversion Start Address: 4 */
#define CSTARTADD_5          (5*0x1000u) /* ADC12 Conversion Start Address: 5 */
#define CSTARTADD_6          (6*0x1000u) /* ADC12 Conversion Start Address: 6 */
#define CSTARTADD_7          (7*0x1000u) /* ADC12 Conversion Start Address: 7 */
#define CSTARTADD_8          (8*0x1000u) /* ADC12 Conversion Start Address: 8 */
#define CSTARTADD_9          (9*0x1000u) /* ADC12 Conversion Start Address: 9 */
#define CSTARTADD_10        (10*0x1000u) /* ADC12 Conversion Start Address: 10 */
#define CSTARTADD_11        (11*0x1000u) /* ADC12 Conversion Start Address: 11 */
#define CSTARTADD_12        (12*0x1000u) /* ADC12 Conversion Start Address: 12 */
#define CSTARTADD_13        (13*0x1000u) /* ADC12 Conversion Start Address: 13 */
#define CSTARTADD_14        (14*0x1000u) /* ADC12 Conversion Start Address: 14 */
#define CSTARTADD_15        (15*0x1000u) /* ADC12 Conversion Start Address: 15 */

#define INCH_0               (0)        /* ADC12 Input Channel 0 */
#define INCH_1               (1)        /* ADC12 Input Channel 1 */
#define INCH_2               (2)        /* ADC12 Input Channel 2 */
#define INCH_3               (3)        /* ADC12 Input Channel 3 */
#define INCH_4               (4)        /* ADC12 Input Channel 4 */
#define INCH_5               (5)        /* ADC12 Input Channel 5 */
#define INCH_6               (6)        /* ADC12 Input Channel 6 */
#define INCH_7               (7)        /* ADC12 Input Channel 7 */
#define INCH_8               (8)        /* ADC12 Input Channel 8 */
#define INCH_9               (9)        /* ADC12 Input Channel 9 */
#define INCH_10             (10)        /* ADC12 Input Channel 10 */
#define INCH_11             (11)        /* ADC12 Input Channel 11 */
#define INCH_12             (12)        /* ADC12 Input Channel 12 */
#define INCH_13             (13)        /* ADC12 Input Channel 13 */
#define INCH_14             (14)        /* ADC12 Input Channel 14 */
#define INCH_15             (15)        /* ADC12 Input Channel 15 */

#define SREF_0               (0*0x10u)   /* ADC12 Select Reference 0 */
#define SREF_1               (1*0x10u)   /* ADC12 Select Reference 1 */
#define SREF_2               (2*0x10u)   /* ADC12 Select Reference 2 */
#define SREF_3               (3*0x10u)   /* ADC12 Select Reference 3 */
#define SREF_4               (4*0x10u)   /* ADC12 Select Reference 4 */
#define SREF_5               (5*0x10u)   /* ADC12 Select Reference 5 */
#define SREF_6               (6*0x10u)   /* ADC12 Select Reference 6 */
#define SREF_7               (7*0x10u)   /* ADC12 Select Reference 7 */
/* ADC12IV Definitions */
#define ADC12IV_NONE        (0x0000u)    /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG  (0x0002u)    /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG (0x0004u)    /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0   (0x0006u)    /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1   (0x0008u)    /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2   (0x000Au)    /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3   (0x000Cu)    /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4   (0x000Eu)    /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5   (0x0010u)    /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6   (0x0012u)    /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7   (0x0014u)    /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8   (0x0016u)    /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9   (0x0018u)    /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10  (0x001Au)    /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11  (0x001Cu)    /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12  (0x001Eu)    /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13  (0x0020u)    /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14  (0x0022u)    /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15  (0x0024u)    /* ADC12IFG15 */




#pragma language=restore
#endif  /* __IAR_SYSTEMS_ICC__  */


/************************************************************
* Timer A interrupt vector value
************************************************************/

/* Compability definitions */

#define TAIV_CCIFG1         TAIV_TACCR1       /* Capture/compare 1 */
#define TAIV_CCIFG2         TAIV_TACCR2       /* Capture/compare 2 */
#define TAIV_CCIFG3         TAIV_6            /* Capture/compare 3 */
#define TAIV_CCIFG4         TAIV_8            /* Capture/compare 4 */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define USART1TX_VECTOR     (2 * 2u)  /* 0xFFE4 USART 1 Transmit */
#define USART1RX_VECTOR     (3 * 2u)  /* 0xFFE6 USART 1 Receive */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      (5 * 2u)  /* 0xFFEA Timer A CC1-2, TA */
#define TIMERA0_VECTOR      (6 * 2u)  /* 0xFFEC Timer A CC0 */
#define ADC12_VECTOR          (7 * 2u)  /* 0xFFEE ADC */
#define USART0TX_VECTOR     (8 * 2u)  /* 0xFFF0 USART 0 Transmit */
#define USART0RX_VECTOR     (9 * 2u)  /* 0xFFF2 USART 0 Receive */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (11 * 2u) /* 0xFFF6 Comparator A */
#define TIMERB1_VECTOR      (12 * 2u) /* 0xFFF8 Timer B CC1-6, TB */
#define TIMERB0_VECTOR      (13 * 2u) /* 0xFFFA Timer B CC0 */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */
#define UART1TX_VECTOR      USART1TX_VECTOR
#define UART1RX_VECTOR      USART1RX_VECTOR
#define UART0TX_VECTOR      USART0TX_VECTOR
#define UART0RX_VECTOR      USART0RX_VECTOR
#define ADC_VECTOR          ADC12_VECTOR


#endif /* __IO430xxxx */
