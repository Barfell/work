/**
 * @file  i430type.h
 * @author  wf
 * @version V1.0
 * @date  2015-11-18
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-18
 * +  file create
 */
#ifndef I430TYPE_H
#define I430TYPE_H

#include "io430.h"
#include "in430.h"

/* 错误代码 */
enum
{
	ERR_RCC_NO1 = 1,

};

#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

/* MSP430 	自定义数据类型, 16位单片机适用 */
typedef signed long			s32;
typedef signed int			s16;
typedef signed char			s8;

typedef const signed long		sc32;  /*!< Read Only */
typedef const signed int		sc16;  /*!< Read Only */
typedef const signed char		sc8;   /*!< Read Only */

typedef unsigned long			u32;
typedef unsigned int			u16;
typedef unsigned char			u8;

typedef const unsigned long		uc32;  /*!< Read Only */
typedef const unsigned int		uc16;  /*!< Read Only */
typedef const unsigned char		uc8;   /*!< Read Only */
#endif










