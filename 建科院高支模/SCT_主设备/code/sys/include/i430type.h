/*****************************************************************
*Modules: i430type.c
*Dedcription: 宏定义一些数据类型，方便代码统一
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       添加文件
******************************************************************/
#ifndef I430TYPE_H
#define I430TYPE_H

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










