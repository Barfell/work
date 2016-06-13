#line 1 "..\\fs\\yaffs_ecc.c"











 









 






 

const char *yaffs_ecc_c_version =
    "$Id: yaffs_ecc.c,v 1.10 2007/12/13 15:35:17 wookey Exp $";

#line 1 "..\\fs\\yportenv.h"













 













 
typedef int off_t;
typedef int dev_t;
typedef unsigned int mode_t;
typedef unsigned long loff_t;



#line 113 "..\\fs\\yportenv.h"



 
#line 1 "..\\fs\\ydirectenv.h"













 



 






#line 1 "..\\fs\\devextras.h"













 






 











 
typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned __u32;






 

struct ylist_head {
	struct ylist_head *next;  
	struct ylist_head *prev;  
};


 





 







 
static __inline void ylist_add(struct ylist_head *newEntry, 
                                 struct ylist_head *list)
{
        struct ylist_head *listNext = list->next;
        
        list->next = newEntry;
        newEntry->prev = list;
	newEntry->next = listNext;
	listNext->prev = newEntry;
	
}

static __inline void ylist_add_tail(struct ylist_head *newEntry, 
				 struct ylist_head *list)
{
	struct ylist_head *listPrev = list->prev;
	
	list->prev = newEntry;
	newEntry->next = list;
	newEntry->prev = listPrev;
	listPrev->next = newEntry;
	
}



 
static __inline void ylist_del(struct ylist_head *entry)
{
        struct ylist_head *listNext = entry->next;
        struct ylist_head *listPrev = entry->prev;
        
        listNext->prev = listPrev;
        listPrev->next = listNext;
        
}

static __inline void ylist_del_init(struct ylist_head *entry)
{
        ylist_del(entry);
        entry->next = entry->prev = entry;
}


 
static __inline int ylist_empty(struct ylist_head *entry)
{
        return (entry->next == entry);
}




 
 
 






 


















 


#line 159 "..\\fs\\devextras.h"









 
#line 176 "..\\fs\\devextras.h"

struct iattr {
	unsigned int ia_valid;
	unsigned ia_mode;
	unsigned ia_uid;
	unsigned ia_gid;
	unsigned ia_size;
	unsigned ia_atime;
	unsigned ia_mtime;
	unsigned ia_ctime;
        unsigned int ia_attr_flags;
};






#line 201 "..\\fs\\devextras.h"


#line 26 "..\\fs\\ydirectenv.h"

#line 1 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
 
 
 




 
 



 







 




  
 










  


 








#line 57 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


  
  typedef unsigned int size_t;










    



    typedef unsigned short wchar_t;  
#line 86 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { __int64 quot, rem; } lldiv_t;
    


#line 107 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   



 

   




 
#line 126 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) __int64 atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) __int64 strtoll(const char * __restrict  ,
                               char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned __int64 strtoull(const char * __restrict  ,
                                         char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 429 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 517 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 546 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) __int64 llabs(__int64  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(__int64  , __int64  );
   











 
#line 627 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 885 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdlib.h"


 

#line 28 "..\\fs\\ydirectenv.h"
#line 1 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 138 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 957 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\stdio.h"



 

#line 29 "..\\fs\\ydirectenv.h"
#line 1 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 185 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 201 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 224 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 239 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 262 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 494 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\string.h"



 

#line 30 "..\\fs\\ydirectenv.h"
#line 1 "..\\fs\\yaffs_malloc.h"













 
 



#line 20 "..\\fs\\yaffs_malloc.h"
 
void *yaffs_malloc(size_t size); 
void yaffs_free(void *ptr);
 


#line 31 "..\\fs\\ydirectenv.h"

#line 1 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\assert.h"
 
 
 
 





 









 





 

#line 43 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\assert.h"
    extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
    extern __declspec(__nothrow) __declspec(__noreturn) void __aeabi_assert(const char *, const char *, int) __attribute__((__nonnull__(1,2)));
#line 53 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\assert.h"

#line 77 "D:\\Program Files\\mdk\\ARM\\ARMCC\\bin\\..\\include\\assert.h"





 

#line 33 "..\\fs\\ydirectenv.h"




#line 47 "..\\fs\\ydirectenv.h"


































#line 1 "..\\fs\\yaffscfg.h"













 




 






#line 1 "..\\fs\\yportenv.h"













 


#line 27 "..\\fs\\yaffscfg.h"




typedef struct {
	const char *prefix;
	struct yaffs_DeviceStruct *dev;
} yaffsfs_DeviceConfiguration;


void yaffsfs_Lock(void);
void yaffsfs_Unlock(void);
__u32 yaffsfs_CurrentTime(void);
void yaffsfs_SetError(int err);



#line 82 "..\\fs\\ydirectenv.h"













#line 118 "..\\fs\\yportenv.h"

#line 168 "..\\fs\\yportenv.h"

 
extern unsigned int yaffs_traceMask;
extern unsigned int yaffs_wr_attempts;




 

#line 193 "..\\fs\\yportenv.h"


















#line 35 "..\\fs\\yaffs_ecc.c"

#line 1 "..\\fs\\yaffs_ecc.h"













 

 







 




typedef struct {
	unsigned char colParity;
	unsigned lineParity;
	unsigned lineParityPrime;
} yaffs_ECCOther;

void yaffs_ECCCalculate(const unsigned char *data, unsigned char *ecc);
int yaffs_ECCCorrect(unsigned char *data, unsigned char *read_ecc,
		     const unsigned char *test_ecc);

void yaffs_ECCCalculateOther(const unsigned char *data, unsigned nBytes,
			     yaffs_ECCOther * ecc);
int yaffs_ECCCorrectOther(unsigned char *data, unsigned nBytes,
			  yaffs_ECCOther * read_ecc,
			  const yaffs_ECCOther * test_ecc);
#line 37 "..\\fs\\yaffs_ecc.c"

static const unsigned char column_parity_table[] = {
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00,
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95,
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99,
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c,
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5,
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30,
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c,
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9,
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9,
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c,
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30,
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5,
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c,
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99,
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95,
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00,
};

 

static int yaffs_CountBits(unsigned char x)
{
	int r = 0;
	while (x) {
		if (x & 1)
			r++;
		x >>= 1;
	}
	return r;
}

static int yaffs_CountBits32(unsigned x)
{
	int r = 0;
	while (x) {
		if (x & 1)
			r++;
		x >>= 1;
	}
	return r;
}

 
void yaffs_ECCCalculate(const unsigned char *data, unsigned char *ecc)
{
	unsigned int i;

	unsigned char col_parity = 0;
	unsigned char line_parity = 0;
	unsigned char line_parity_prime = 0;
	unsigned char t;
	unsigned char b;

	for (i = 0; i < 256; i++) {
		b = column_parity_table[*data++];
		col_parity ^= b;

		if (b & 0x01)	
		{
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}

	}

	ecc[2] = (~col_parity) | 0x03;

	t = 0;
	if (line_parity & 0x80)
		t |= 0x80;
	if (line_parity_prime & 0x80)
		t |= 0x40;
	if (line_parity & 0x40)
		t |= 0x20;
	if (line_parity_prime & 0x40)
		t |= 0x10;
	if (line_parity & 0x20)
		t |= 0x08;
	if (line_parity_prime & 0x20)
		t |= 0x04;
	if (line_parity & 0x10)
		t |= 0x02;
	if (line_parity_prime & 0x10)
		t |= 0x01;
	ecc[1] = ~t;

	t = 0;
	if (line_parity & 0x08)
		t |= 0x80;
	if (line_parity_prime & 0x08)
		t |= 0x40;
	if (line_parity & 0x04)
		t |= 0x20;
	if (line_parity_prime & 0x04)
		t |= 0x10;
	if (line_parity & 0x02)
		t |= 0x08;
	if (line_parity_prime & 0x02)
		t |= 0x04;
	if (line_parity & 0x01)
		t |= 0x02;
	if (line_parity_prime & 0x01)
		t |= 0x01;
	ecc[0] = ~t;

#line 166 "..\\fs\\yaffs_ecc.c"
}


 

int yaffs_ECCCorrect(unsigned char *data, unsigned char *read_ecc,
		     const unsigned char *test_ecc)
{
	unsigned char d0, d1, d2;	 

	d0 = read_ecc[0] ^ test_ecc[0];
	d1 = read_ecc[1] ^ test_ecc[1];
	d2 = read_ecc[2] ^ test_ecc[2];

	if ((d0 | d1 | d2) == 0)
		return 0;  

	if (((d0 ^ (d0 >> 1)) & 0x55) == 0x55 &&
	    ((d1 ^ (d1 >> 1)) & 0x55) == 0x55 &&
	    ((d2 ^ (d2 >> 1)) & 0x54) == 0x54) {
		 

		unsigned byte;
		unsigned bit;

#line 199 "..\\fs\\yaffs_ecc.c"

		bit = byte = 0;

		if (d1 & 0x80)
			byte |= 0x80;
		if (d1 & 0x20)
			byte |= 0x40;
		if (d1 & 0x08)
			byte |= 0x20;
		if (d1 & 0x02)
			byte |= 0x10;
		if (d0 & 0x80)
			byte |= 0x08;
		if (d0 & 0x20)
			byte |= 0x04;
		if (d0 & 0x08)
			byte |= 0x02;
		if (d0 & 0x02)
			byte |= 0x01;

		if (d2 & 0x80)
			bit |= 0x04;
		if (d2 & 0x20)
			bit |= 0x02;
		if (d2 & 0x08)
			bit |= 0x01;

		data[byte] ^= (1 << bit);

		return 1;  
	}

	if ((yaffs_CountBits(d0) +
	     yaffs_CountBits(d1) +
	     yaffs_CountBits(d2)) ==  1) {
		 

		read_ecc[0] = test_ecc[0];
		read_ecc[1] = test_ecc[1];
		read_ecc[2] = test_ecc[2];

		return 1;  
	}

	 

	return -1;

}




 
void yaffs_ECCCalculateOther(const unsigned char *data, unsigned nBytes,
			     yaffs_ECCOther * eccOther)
{
	unsigned int i;

	unsigned char col_parity = 0;
	unsigned line_parity = 0;
	unsigned line_parity_prime = 0;
	unsigned char b;

	for (i = 0; i < nBytes; i++) {
		b = column_parity_table[*data++];
		col_parity ^= b;

		if (b & 0x01)	 {
			 
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}

	}

	eccOther->colParity = (col_parity >> 2) & 0x3f;
	eccOther->lineParity = line_parity;
	eccOther->lineParityPrime = line_parity_prime;
}

int yaffs_ECCCorrectOther(unsigned char *data, unsigned nBytes,
			  yaffs_ECCOther * read_ecc,
			  const yaffs_ECCOther * test_ecc)
{
	unsigned char cDelta;	 
	unsigned lDelta;	 
	unsigned lDeltaPrime;	 
	unsigned bit;

	cDelta = read_ecc->colParity ^ test_ecc->colParity;
	lDelta = read_ecc->lineParity ^ test_ecc->lineParity;
	lDeltaPrime = read_ecc->lineParityPrime ^ test_ecc->lineParityPrime;

	if ((cDelta | lDelta | lDeltaPrime) == 0)
		return 0;  

	if (lDelta == ~lDeltaPrime &&
	    (((cDelta ^ (cDelta >> 1)) & 0x15) == 0x15))
	{
		 

		bit = 0;

		if (cDelta & 0x20)
			bit |= 0x04;
		if (cDelta & 0x08)
			bit |= 0x02;
		if (cDelta & 0x02)
			bit |= 0x01;

		if(lDelta >= nBytes)
			return -1;

		data[lDelta] ^= (1 << bit);

		return 1;  
	}

	if ((yaffs_CountBits32(lDelta) + yaffs_CountBits32(lDeltaPrime) +
	     yaffs_CountBits(cDelta)) == 1) {
		 

		*read_ecc = *test_ecc;
		return 1;  
	}

	 

	return -1;

}

