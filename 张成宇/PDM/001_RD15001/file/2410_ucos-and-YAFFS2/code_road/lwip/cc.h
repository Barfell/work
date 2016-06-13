#ifndef CC_H
#define CC_H
#include <stdio.h>

typedef unsigned char u8_t;
typedef signed char s8_t;
typedef unsigned short u16_t;
typedef signed short s16_t;
typedef unsigned int u32_t;
typedef signed int s32_t;
typedef u32_t mem_ptr_t;
typedef unsigned int sys_prot_t;

#define PACK_STRUCT_FIELD(x) x __attribute__((packed))
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do { printf("Assertion %s failed at line %d in %s\n", x, __LINE__, __FILE__); } while(0)
#endif

#ifndef LWIP_MIN
#define LWIP_MIN(x , y) (x) < (y) ? (x) : (y)
#endif

#endif

