#line 1 "..\\fs\\yaffs_guts.c"











 

const char *yaffs_guts_c_version =
    "$Id: yaffs_guts.c,v 1.78 2009/01/27 02:52:45 charles Exp $";

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


















#line 18 "..\\fs\\yaffs_guts.c"

#line 1 "..\\fs\\yaffsfs.h"













 




 





#line 26 "..\\fs\\yaffsfs.h"
#line 27 "..\\fs\\yaffsfs.h"









































































































































#line 170 "..\\fs\\yaffsfs.h"








struct yaffs_dirent{
    long d_ino;                  
    off_t d_off;                 
    unsigned short d_reclen;     
    unsigned char  d_type;	 
    char d_name [256+1];    
    unsigned d_dont_use;	 
};

typedef struct yaffs_dirent yaffs_dirent;


typedef struct __opaque yaffs_DIR;



struct yaffs_stat{
    int		      st_dev;       
    int           st_ino;       
    unsigned      st_mode;      
    int           st_nlink;     
    int           st_uid;       
    int           st_gid;       
    unsigned      st_rdev;      
    off_t         st_size;      
    unsigned long st_blksize;   
    unsigned long st_blocks;    
#line 211 "..\\fs\\yaffsfs.h"
	unsigned long yst_atime;     
    unsigned long yst_mtime;     
    unsigned long yst_ctime;     

};

int yaffs_open(const char *path, int oflag, int mode) ;
int yaffs_close(int fd) ;
int yaffs_flush(int fd) ;

int yaffs_access(const char *path, int amode);

int yaffs_dup(int fd);

int yaffs_read(int fd, void *buf, unsigned int nbyte) ;
int yaffs_write(int fd, const void *buf, unsigned int nbyte) ;

int yaffs_pread(int fd, void *buf, unsigned int nbyte, unsigned int offset);
int yaffs_pwrite(int fd, const void *buf, unsigned int nbyte, unsigned int offset);

off_t yaffs_lseek(int fd, off_t offset, int whence) ;

int yaffs_truncate(const char *path, off_t newSize);
int yaffs_ftruncate(int fd, off_t newSize);

int yaffs_unlink(const char *path) ;
int yaffs_rename(const char *oldPath, const char *newPath) ;

int yaffs_stat(const char *path, struct yaffs_stat *buf) ;
int yaffs_lstat(const char *path, struct yaffs_stat *buf) ;
int yaffs_fstat(int fd, struct yaffs_stat *buf) ;

#line 249 "..\\fs\\yaffsfs.h"

int yaffs_chmod(const char *path, mode_t mode); 
int yaffs_fchmod(int fd, mode_t mode); 

int yaffs_mkdir(const char *path, mode_t mode) ;
int yaffs_rmdir(const char *path) ;

yaffs_DIR *yaffs_opendir(const char *dirname) ;
struct yaffs_dirent *yaffs_readdir(yaffs_DIR *dirp) ;
void yaffs_rewinddir(yaffs_DIR *dirp) ;
int yaffs_closedir(yaffs_DIR *dirp) ;

int yaffs_mount(const char *path) ;
int yaffs_unmount(const char *path) ;

int yaffs_sync(const char *path) ;

int yaffs_symlink(const char *oldpath, const char *newpath); 
int yaffs_readlink(const char *path, char *buf, int bufsiz); 

int yaffs_link(const char *oldpath, const char *newpath); 
int yaffs_mknod(const char *pathname, mode_t mode, dev_t dev);

loff_t yaffs_freespace(const char *path);
loff_t yaffs_totalspace(const char *path);

int yaffs_inodecount(const char *path);


void yaffs_initialise(yaffsfs_DeviceConfiguration *configList);

int yaffs_StartUp(void);




#line 20 "..\\fs\\yaffs_guts.c"
#line 1 "..\\fs\\yaffs_guts.h"













 




#line 20 "..\\fs\\yaffs_guts.h"
#line 21 "..\\fs\\yaffs_guts.h"









 











#line 49 "..\\fs\\yaffs_guts.h"



















#line 75 "..\\fs\\yaffs_guts.h"



 





 




 








 








 



 


 
typedef struct {
	struct yaffs_ObjectStruct *object;
	int chunkId;
	int lastUse;
	int dirty;
	int nBytes;		 
	int locked;		 

	__u8 *data;



} yaffs_ChunkCache;






 


typedef struct {
        unsigned chunkId:20;
        unsigned serialNumber:2;
        unsigned byteCountLSB:10;
        unsigned objectId:18;
        unsigned ecc:12;
        unsigned byteCountMSB:2;

} yaffs_Tags;

typedef union {
	yaffs_Tags asTags;
	__u8 asBytes[8];
} yaffs_TagsUnion;



 

typedef enum {
	YAFFS_ECC_RESULT_UNKNOWN,
	YAFFS_ECC_RESULT_NO_ERROR,
	YAFFS_ECC_RESULT_FIXED,
	YAFFS_ECC_RESULT_UNFIXED
} yaffs_ECCResult;

typedef enum {
	YAFFS_OBJECT_TYPE_UNKNOWN,
	YAFFS_OBJECT_TYPE_FILE,
	YAFFS_OBJECT_TYPE_SYMLINK,
	YAFFS_OBJECT_TYPE_DIRECTORY,
	YAFFS_OBJECT_TYPE_HARDLINK,
	YAFFS_OBJECT_TYPE_SPECIAL
} yaffs_ObjectType;



typedef struct {

	unsigned validMarker0;
	unsigned chunkUsed;	 
	unsigned objectId;	 
	unsigned chunkId;	 
	unsigned byteCount;	 

	 
	yaffs_ECCResult eccResult;
	unsigned blockBad;	

	 
	unsigned chunkDeleted;	 
	unsigned serialNumber;	 

	 
	unsigned sequenceNumber;	 

	 

	unsigned extraHeaderInfoAvailable;	 
	unsigned extraParentObjectId;	 
	unsigned extraIsShrinkHeader;	 
	unsigned extraShadows;		 

	yaffs_ObjectType extraObjectType;	 

	unsigned extraFileLength;		 
	unsigned extraEquivalentObjectId;	 

	unsigned validMarker1;

} yaffs_ExtendedTags;

 
typedef struct {
	__u8 tagByte0;
	__u8 tagByte1;
	__u8 tagByte2;
	__u8 tagByte3;
	__u8 pageStatus;	 
	__u8 blockStatus;
	__u8 tagByte4;
	__u8 tagByte5;
	__u8 ecc1[3];
	__u8 tagByte6;
	__u8 tagByte7;
	__u8 ecc2[3];
} yaffs_Spare;

 
struct yaffs_NANDSpare {
	yaffs_Spare spare;
	int eccres1;
	int eccres2;
};

 

typedef enum {
	YAFFS_BLOCK_STATE_UNKNOWN = 0,

	YAFFS_BLOCK_STATE_SCANNING,
	YAFFS_BLOCK_STATE_NEEDS_SCANNING,
	




 

	YAFFS_BLOCK_STATE_EMPTY,
	 

	YAFFS_BLOCK_STATE_ALLOCATING,
	



 

	YAFFS_BLOCK_STATE_FULL,	
	
 

	YAFFS_BLOCK_STATE_DIRTY,
	

 

	YAFFS_BLOCK_STATE_CHECKPOINT,	
	
 

	YAFFS_BLOCK_STATE_COLLECTING,	
	 

	YAFFS_BLOCK_STATE_DEAD	
	 
} yaffs_BlockState;




typedef struct {

	int softDeletions:10;	 
	int pagesInUse:10;	 
	unsigned blockState:4;	 
	__u32 needsRetiring:1;	 
                        	 
	__u32 skipErasedCheck: 1;  
	__u32 gcPrioritise: 1; 	
 
        __u32 chunkErrorStrikes:3;  


	__u32 hasShrinkHeader:1;  
	__u32 sequenceNumber;	  


} yaffs_BlockInfo;

 
 

typedef struct {
	yaffs_ObjectType type;

	 
	int parentObjectId;
        __u16 sum__NoLongerUsed;         
        char name[255 + 1];

         
        __u32 yst_mode;          




	__u32 yst_uid;
	__u32 yst_gid;
	__u32 yst_atime;
	__u32 yst_mtime;
	__u32 yst_ctime;


	 
	int fileSize;

	 
	int equivalentObjectId;

	 
	char alias[159 + 1];

	__u32 yst_rdev;		 






	__u32 roomToGrow[6];


	__u32 inbandShadowsObject;
	__u32 inbandIsShrink;

	__u32 reservedSpace[2];
	int shadowsObject;	 

	 
	__u32 isShrink;

} yaffs_ObjectHeader;

 

union yaffs_Tnode_union {



	union yaffs_Tnode_union *internal[(16 / 2)];

 

};

typedef union yaffs_Tnode_union yaffs_Tnode;

struct yaffs_TnodeList_struct {
	struct yaffs_TnodeList_struct *next;
	yaffs_Tnode *tnodes;
};

typedef struct yaffs_TnodeList_struct yaffs_TnodeList;

 





 

typedef struct {
	__u32 fileSize;
	__u32 scannedFileSize;
	__u32 shrinkSize;
	int topLevel;
	yaffs_Tnode *top;
} yaffs_FileStructure;

typedef struct {
        struct ylist_head children;      
} yaffs_DirectoryStructure;

typedef struct {
	char *alias;
} yaffs_SymLinkStructure;

typedef struct {
	struct yaffs_ObjectStruct *equivalentObject;
	__u32 equivalentObjectId;
} yaffs_HardLinkStructure;

typedef union {
	yaffs_FileStructure fileVariant;
	yaffs_DirectoryStructure directoryVariant;
	yaffs_SymLinkStructure symLinkVariant;
	yaffs_HardLinkStructure hardLinkVariant;
} yaffs_ObjectVariant;

struct yaffs_ObjectStruct {
	__u8 deleted:1;		 
	__u8 softDeleted:1;	 
	__u8 unlinked:1;	 
	__u8 fake:1;		 
	__u8 renameAllowed:1;	 
	__u8 unlinkAllowed:1;
	__u8 dirty:1;		 
	__u8 valid:1;		


 
	__u8 lazyLoaded:1;	 

	__u8 deferedFree:1;	


 
        __u8 beingCreated:1;	 

	__u8 serial;		 
	__u16 sum;		 

        struct yaffs_DeviceStruct *myDev;        

        struct ylist_head hashLink;      

        struct ylist_head hardLinks;     

         
         
        struct yaffs_ObjectStruct *parent; 
        struct ylist_head siblings;

	 
	int hdrChunk;

	int nDataChunks;	 

	__u32 objectId;		 

	__u32 yst_mode;






	__u32 inUse;







	__u32 yst_uid;
	__u32 yst_gid;
	__u32 yst_atime;
	__u32 yst_mtime;
	__u32 yst_ctime;


	__u32 yst_rdev;






	yaffs_ObjectType variantType;

	yaffs_ObjectVariant variant;

};

typedef struct yaffs_ObjectStruct yaffs_Object;

struct yaffs_ObjectList_struct {
	yaffs_Object *objects;
	struct yaffs_ObjectList_struct *next;
};

typedef struct yaffs_ObjectList_struct yaffs_ObjectList;

typedef struct {
        struct ylist_head list;
        int count;
} yaffs_ObjectBucket;




 

typedef struct {
        int structType;
	__u32 objectId;		
	__u32 parentId;
	int hdrChunk;
	yaffs_ObjectType variantType:3;
	__u8 deleted:1;		
	__u8 softDeleted:1;	
	__u8 unlinked:1;	
	__u8 fake:1;		
	__u8 renameAllowed:1;
	__u8 unlinkAllowed:1;
	__u8 serial;		
	
	int nDataChunks;	
	__u32 fileSizeOrEquivalentObjectId;

}yaffs_CheckpointObject;




 

typedef struct {
	__u8 *buffer;
	int line;	 
	int maxLine;
} yaffs_TempBuffer;

 

struct yaffs_DeviceStruct {
        struct ylist_head devList;
        const char *name;

         
        int nDataBytesPerChunk;  
        int nChunksPerBlock;     
        int spareBytesPerChunk; 
        int startBlock;          
        int endBlock;            
        int nReservedBlocks;     
				 
	
	
	 
	 
	


	


	int nShortOpCaches;	

 

	int useHeaderFileSize;	 

	int useNANDECC;		 

	void *genericDevice;	

 
        void *superBlock;
        
	 

	int (*writeChunkToNAND) (struct yaffs_DeviceStruct * dev,int chunkInNAND, const __u8 * data,const yaffs_Spare * spare);
 	int (*readChunkFromNAND) (struct yaffs_DeviceStruct * dev,int chunkInNAND, __u8 * data,yaffs_Spare * spare);
        int (*eraseBlockInNAND) (struct yaffs_DeviceStruct * dev, int blockInNAND);                               
        int (*initialiseNAND) (struct yaffs_DeviceStruct * dev);
        int (*deinitialiseNAND) (struct yaffs_DeviceStruct * dev);
        int (*writeChunkWithTagsToNAND) (struct yaffs_DeviceStruct * dev, int chunkInNAND, const __u8 * data,const yaffs_ExtendedTags * tags);					 
        int (*readChunkWithTagsFromNAND) (struct yaffs_DeviceStruct * dev,int chunkInNAND, __u8 * data,yaffs_ExtendedTags * tags);
        int (*markNANDBlockBad) (struct yaffs_DeviceStruct * dev, int blockNo);
        int (*queryNANDBlock) (struct yaffs_DeviceStruct * dev, int blockNo,yaffs_BlockState * state, __u32 *sequenceNumber);
        
        int isYaffs2;
	
	


 
	void (*removeObjectCallback)(struct yaffs_ObjectStruct *obj);
	
	 
	void (*markSuperBlockDirty)(void * superblock);
	
	int wideTnodesDisabled;  
	
	char *pathDividers;	 
	

	 
	
	 
	__u8 skipCheckpointRead;
	__u8 skipCheckpointWrite;

	 

	__u16 chunkGroupBits;	 
	__u16 chunkGroupSize;	 
	
	 
	__u32 tnodeWidth;
	__u32 tnodeMask;
	
	 
	__u32 chunkShift;  
	__u32 chunkDiv;    
	__u32 chunkMask;   

	 
	int inbandTags;
	__u32 totalBytesPerChunk;

#line 632 "..\\fs\\yaffs_guts.h"

	int isMounted;
	
	int isCheckpointed;


	 
	int internalStartBlock;
	int internalEndBlock;
	int blockOffset;
	int chunkOffset;
	

	 
	int checkpointPageSequence;    
	int checkpointByteCount;
	int checkpointByteOffset;
	__u8 *checkpointBuffer;
	int checkpointOpenForWrite;
	int blocksInCheckpoint;
	int checkpointCurrentChunk;
	int checkpointCurrentBlock;
	int checkpointNextBlock;
	int *checkpointBlockList;
	int checkpointMaxBlocks;
	__u32 checkpointSum;
	__u32 checkpointXor;
	
	int nCheckpointBlocksRequired;  
	
	 
	yaffs_BlockInfo *blockInfo;
	__u8 *chunkBits;	 
	unsigned blockInfoAlt:1;	 
	unsigned chunkBitsAlt:1;	 
	int chunkBitmapStride;	

 

	int nErasedBlocks;
	int allocationBlock;	 
	__u32 allocationPage;
	int allocationBlockFinder;	 

	 
	int nTnodesCreated;
	yaffs_Tnode *freeTnodes;
	int nFreeTnodes;
	yaffs_TnodeList *allocatedTnodeList;

	int isDoingGC;
	int gcBlock;
	int gcChunk;

	int nObjectsCreated;
	yaffs_Object *freeObjects;
	int nFreeObjects;
	
	int nHardLinks;

	yaffs_ObjectList *allocatedObjectList;

	yaffs_ObjectBucket objectBucket[256];

	int nFreeChunks;

	int currentDirtyChecker;	 

	__u32 *gcCleanupList;	 
	int nonAggressiveSkip;	 

	 
	int nPageWrites;
	int nPageReads;
	int nBlockErasures;
	int nErasureFailures;
	int nGCCopies;
	int garbageCollections;
	int passiveGarbageCollections;
	int nRetriedWrites;
	int nRetiredBlocks;
	int eccFixed;
	int eccUnfixed;
	int tagsEccFixed;
	int tagsEccUnfixed;
	int nDeletions;
	int nUnmarkedDeletions;
	
	int hasPendingPrioritisedGCs;  

	 
	yaffs_Object *rootDir;
	yaffs_Object *lostNFoundDir;

	


 
	
	int bufferedBlock;	 
	int doingBufferedBlockRewrite;

	yaffs_ChunkCache *srCache;
	int srLastUse;

	int cacheHits;

	 
	yaffs_Object *unlinkedDir;	 
	yaffs_Object *deletedDir;	 
	yaffs_Object *unlinkedDeletion;	 
	int nDeletedFiles;		 
	int nUnlinkedFiles;		 
	int nBackgroundDeletions;	 

	
	 
	yaffs_TempBuffer tempBuffer[6];
	int maxTemp;
	int tempInUse;
	int unmanagedTempAllocations;
	int unmanagedTempDeallocations;

	 
	unsigned sequenceNumber;	 
	unsigned oldestDirtySequence;

};

typedef struct yaffs_DeviceStruct yaffs_Device;

 
typedef struct {
        int StructType;
        int version;
	int checkpointStartBlock;
	int checkpointEndBlock;
	int startBlock;
	int endBlock;
	int rfu[100];
} yaffs_SuperBlockHeader;
	


 
typedef struct {
        int structType;
	int nErasedBlocks;
	int allocationBlock;	 
	__u32 allocationPage;
	int nFreeChunks;

	int nDeletedFiles;		 
	int nUnlinkedFiles;		 
	int nBackgroundDeletions;	 

	 
	unsigned sequenceNumber;	 
	unsigned oldestDirtySequence;

} yaffs_CheckpointDevice;


typedef struct {
    int structType;
    __u32 magic;
    __u32 version;
    __u32 head;
} yaffs_CheckpointValidity;


 

int yaffs_GutsInitialise(yaffs_Device * dev);
void yaffs_Deinitialise(yaffs_Device * dev);

int yaffs_GetNumberOfFreeChunks(yaffs_Device * dev);

int yaffs_RenameObject(yaffs_Object * oldDir, const char * oldName,
		       yaffs_Object * newDir, const char * newName);

int yaffs_Unlink(yaffs_Object * dir, const char * name);
int yaffs_DeleteFile(yaffs_Object * obj);

int yaffs_GetObjectName(yaffs_Object * obj, char * name, int buffSize);
int yaffs_GetObjectFileLength(yaffs_Object * obj);
int yaffs_GetObjectInode(yaffs_Object * obj);
unsigned yaffs_GetObjectType(yaffs_Object * obj);
int yaffs_GetObjectLinkCount(yaffs_Object * obj);

int yaffs_SetAttributes(yaffs_Object * obj, struct iattr *attr);
int yaffs_GetAttributes(yaffs_Object * obj, struct iattr *attr);

 
int yaffs_ReadDataFromFile(yaffs_Object * obj, __u8 * buffer, loff_t offset,
                           int nBytes);
int yaffs_WriteDataToFile(yaffs_Object * obj, const __u8 * buffer, loff_t offset,
                          int nBytes, int writeThrough);
int yaffs_ResizeFile(yaffs_Object * obj, loff_t newSize);

yaffs_Object *yaffs_MknodFile(yaffs_Object * parent, const char * name,
                              __u32 mode, __u32 uid, __u32 gid);
int yaffs_FlushFile(yaffs_Object * obj, int updateTime);

 
void yaffs_FlushEntireDeviceCache(yaffs_Device *dev);

int yaffs_CheckpointSave(yaffs_Device *dev);
int yaffs_CheckpointRestore(yaffs_Device *dev);

 
yaffs_Object *yaffs_MknodDirectory(yaffs_Object * parent, const char * name,
				   __u32 mode, __u32 uid, __u32 gid);
yaffs_Object *yaffs_FindObjectByName(yaffs_Object * theDir, const char * name);
int yaffs_ApplyToDirectoryChildren(yaffs_Object * theDir,
				   int (*fn) (yaffs_Object *));

yaffs_Object *yaffs_FindObjectByNumber(yaffs_Device * dev, __u32 number);

 
yaffs_Object *yaffs_Link(yaffs_Object * parent, const char * name,
			 yaffs_Object * equivalentObject);

yaffs_Object *yaffs_GetEquivalentObject(yaffs_Object * obj);

 
yaffs_Object *yaffs_MknodSymLink(yaffs_Object * parent, const char * name,
				 __u32 mode, __u32 uid, __u32 gid,
				 const char * alias);
char *yaffs_GetSymlinkAlias(yaffs_Object * obj);

 
yaffs_Object *yaffs_MknodSpecial(yaffs_Object * parent, const char * name,
				 __u32 mode, __u32 uid, __u32 gid, __u32 rdev);

 
yaffs_Object *yaffs_Root(yaffs_Device * dev);
yaffs_Object *yaffs_LostNFound(yaffs_Device * dev);











 
int yaffs_DumpObject(yaffs_Object * obj);

void yaffs_GutsTest(yaffs_Device * dev);

 
void yaffs_InitialiseTags(yaffs_ExtendedTags * tags);
void yaffs_DeleteChunk(yaffs_Device * dev, int chunkId, int markNAND, int lyn);
int yaffs_CheckFF(__u8 * buffer, int nBytes);
void yaffs_HandleChunkError(yaffs_Device *dev, yaffs_BlockInfo *bi);

__u8 *yaffs_GetTempBuffer(yaffs_Device * dev, int lineNo);
void yaffs_ReleaseTempBuffer(yaffs_Device * dev, __u8 * buffer, int lineNo);

#line 21 "..\\fs\\yaffs_guts.c"
#line 1 "..\\fs\\yaffs_tagsvalidity.h"













 





#line 21 "..\\fs\\yaffs_tagsvalidity.h"

void yaffs_InitialiseTags(yaffs_ExtendedTags * tags);
int yaffs_ValidateTags(yaffs_ExtendedTags * tags);
#line 22 "..\\fs\\yaffs_guts.c"
#line 1 "..\\fs\\yaffs_getblockinfo.h"













 




#line 20 "..\\fs\\yaffs_getblockinfo.h"

 
static __inline yaffs_BlockInfo *yaffs_GetBlockInfo(yaffs_Device * dev, int blk)
{
	if (blk < dev->internalStartBlock || blk > dev->internalEndBlock) {
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		;
	}
	return &dev->blockInfo[blk - dev->internalStartBlock];
}

#line 23 "..\\fs\\yaffs_guts.c"

#line 1 "..\\fs\\yaffs_tagscompat.h"













 




#line 20 "..\\fs\\yaffs_tagscompat.h"
int yaffs_TagsCompatabilityWriteChunkWithTagsToNAND(yaffs_Device * dev,
						    int chunkInNAND,
						    const __u8 * data,
						    const yaffs_ExtendedTags *
						    tags);
int yaffs_TagsCompatabilityReadChunkWithTagsFromNAND(yaffs_Device * dev,
						     int chunkInNAND,
						     __u8 * data,
						     yaffs_ExtendedTags *
						     tags);
int yaffs_TagsCompatabilityMarkNANDBlockBad(struct yaffs_DeviceStruct *dev,
					    int blockNo);
int yaffs_TagsCompatabilityQueryNANDBlock(struct yaffs_DeviceStruct *dev,
					  int blockNo, 
					  yaffs_BlockState *state,
					  __u32 *sequenceNumber);

void yaffs_CalcTagsECC(yaffs_Tags * tags);
int yaffs_CheckECCOnTags(yaffs_Tags * tags);
int yaffs_CountBits(__u8 byte);

#line 25 "..\\fs\\yaffs_guts.c"
#line 1 "..\\fs\\yaffs_qsort.h"













 





extern void yaffs_qsort (void *const base, size_t total_elems, size_t size,
                   int (*cmp)(const void *, const void *));

#line 27 "..\\fs\\yaffs_guts.c"



#line 1 "..\\fs\\yaffs_checkptrw.h"













 




#line 20 "..\\fs\\yaffs_checkptrw.h"

int yaffs_CheckpointOpen(yaffs_Device *dev, int forWriting);

int yaffs_CheckpointWrite(yaffs_Device *dev,const void *data, int nBytes);

int yaffs_CheckpointRead(yaffs_Device *dev,void *data, int nBytes);

int yaffs_GetCheckpointSum(yaffs_Device *dev, __u32 *sum);

int yaffs_CheckpointClose(yaffs_Device *dev);

int yaffs_CheckpointInvalidateStream(yaffs_Device *dev);




#line 31 "..\\fs\\yaffs_guts.c"


#line 1 "..\\fs\\yaffs_packedtags2.h"













 

 




#line 22 "..\\fs\\yaffs_packedtags2.h"
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
#line 23 "..\\fs\\yaffs_packedtags2.h"

typedef struct {
	unsigned sequenceNumber;
	unsigned objectId;
	unsigned chunkId;
	unsigned byteCount;
} yaffs_PackedTags2TagsPart;

typedef struct {
	yaffs_PackedTags2TagsPart t;
	yaffs_ECCOther ecc;
} yaffs_PackedTags2;

 
void yaffs_PackTags2(yaffs_PackedTags2 * pt, const yaffs_ExtendedTags * t);
void yaffs_UnpackTags2(yaffs_ExtendedTags * t, yaffs_PackedTags2 * pt);

 
void yaffs_PackTags2TagsPart(yaffs_PackedTags2TagsPart * pt, const yaffs_ExtendedTags * t);
void yaffs_UnpackTags2TagsPart(yaffs_ExtendedTags * t, yaffs_PackedTags2TagsPart * pt);
#line 34 "..\\fs\\yaffs_guts.c"




#line 39 "..\\fs\\yaffs_guts.c"
#line 1 "..\\Drivers\\debug_frmwrk.h"
 
















 




#line 1 "..\\Drivers\\lpc177x_8x_uart.h"
 

















 

 



 
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

#line 27 "..\\Drivers\\lpc177x_8x_uart.h"
#line 1 "..\\Drivers\\lpc_types.h"
 



















 

 



 
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

#line 40 "..\\fs\\yaffs_guts.c"

 
static void yaffs_RetireBlock(yaffs_Device * dev, int blockInNAND);
static void yaffs_HandleWriteChunkError(yaffs_Device * dev, int chunkInNAND, int erasedOk);
static void yaffs_HandleWriteChunkOk(yaffs_Device * dev, int chunkInNAND,
				     const __u8 * data,
				     const yaffs_ExtendedTags * tags);
static void yaffs_HandleUpdateChunk(yaffs_Device * dev, int chunkInNAND,
				    const yaffs_ExtendedTags * tags);

 
static int yaffs_UnlinkObject( yaffs_Object *obj);
static int yaffs_ObjectHasCachedWriteData(yaffs_Object *obj);

static void yaffs_HardlinkFixup(yaffs_Device *dev, yaffs_Object *hardList);

static int yaffs_WriteNewChunkWithTagsToNAND(yaffs_Device * dev,
					     const __u8 * buffer,
					     yaffs_ExtendedTags * tags,
					     int useReserve);
static int yaffs_PutChunkIntoFile(yaffs_Object * in, int chunkInInode,
				  int chunkInNAND, int inScan);

static yaffs_Object *yaffs_CreateNewObject(yaffs_Device * dev, int number,
					   yaffs_ObjectType type);
static void yaffs_AddObjectToDirectory(yaffs_Object * directory,
				       yaffs_Object * obj);
static int yaffs_UpdateObjectHeader(yaffs_Object * in, const char * name,
				    int force, int isShrink, int shadows);
static void yaffs_RemoveObjectFromDirectory(yaffs_Object * obj);
static int yaffs_CheckStructures(void);
static int yaffs_DeleteWorker(yaffs_Object * in, yaffs_Tnode * tn, __u32 level,
			      int chunkOffset, int *limit);
static int yaffs_DoGenericObjectDeletion(yaffs_Object * in);

static yaffs_BlockInfo *yaffs_GetBlockInfo(yaffs_Device * dev, int blockNo);


static int yaffs_CheckChunkErased(struct yaffs_DeviceStruct *dev,
				  int chunkInNAND);

static int yaffs_UnlinkWorker(yaffs_Object * obj);
static void yaffs_DestroyObject(yaffs_Object * obj);

static int yaffs_TagsMatch(const yaffs_ExtendedTags * tags, int objectId,
			   int chunkInObject);

loff_t yaffs_GetFileSize(yaffs_Object * obj);

static int yaffs_AllocateChunk(yaffs_Device * dev, int useReserve, yaffs_BlockInfo **blockUsedPtr);

static void yaffs_VerifyFreeChunks(yaffs_Device * dev);

static void yaffs_CheckObjectDetailsLoaded(yaffs_Object *in);

static void yaffs_VerifyDirectory(yaffs_Object *directory);






static void yaffs_InvalidateWholeChunkCache(yaffs_Object * in);
static void yaffs_InvalidateChunkCache(yaffs_Object * object, int chunkId);

static void yaffs_InvalidateCheckpoint(yaffs_Device *dev);

static int yaffs_FindChunkInFile(yaffs_Object * in, int chunkInInode,
				 yaffs_ExtendedTags * tags);

static __u32 yaffs_GetChunkGroupBase(yaffs_Device *dev, yaffs_Tnode *tn, unsigned pos);
static yaffs_Tnode *yaffs_FindLevel0Tnode(yaffs_Device * dev,
					  yaffs_FileStructure * fStruct,
					  __u32 chunkId);


 

static void yaffs_AddrToChunk(yaffs_Device *dev, loff_t addr, int *chunkOut, __u32 *offsetOut)
{
	int chunk;
	__u32 offset;
	
	chunk  = (__u32)(addr >> dev->chunkShift);
		
	if(dev->chunkDiv == 1)
	{
		 
		offset = (__u32)(addr & dev->chunkMask);
	}
	else
	{
		 
		
		loff_t chunkBase;
		
		chunk /= dev->chunkDiv;
		
		chunkBase = ((loff_t)chunk) * dev->nDataBytesPerChunk;
		offset = (__u32)(addr - chunkBase);
	}

	*chunkOut = chunk;
	*offsetOut = offset;
}





 
 
static __u32 ShiftsGE(__u32 x)
{
	int extraBits;
	int nShifts;
	
	nShifts = extraBits = 0;
	
	while(x>1){
		if(x & 1) extraBits++;
		x>>=1;
		nShifts++;
	}

	if(extraBits) 
		nShifts++;
		
	return nShifts;
}


 
 
static __u32 Shifts(__u32 x)
{
	int nShifts;
	
	nShifts =  0;
	
	if(!x) return 0;
	
	while( !(x&1)){
		x>>=1;
		nShifts++;
	}
		
	return nShifts;
}





 

static int yaffs_InitialiseTempBuffers(yaffs_Device *dev)	
{
	int i;
	__u8 *buf = (__u8 *)1;
		
	memset(dev->tempBuffer,0,sizeof(dev->tempBuffer));
	
	for (i = 0; buf && i < 6; i++) {
		dev->tempBuffer[i].line = 0;	 
		dev->tempBuffer[i].buffer = buf =
		    yaffs_malloc(dev->totalBytesPerChunk);
	}
    
    return buf ? 1 : 0;
	
}

__u8 *yaffs_GetTempBuffer(yaffs_Device * dev, int lineNo)
{
	int i, j;

	dev->tempInUse++;
	if(dev->tempInUse > dev->maxTemp)
		dev->maxTemp = dev->tempInUse;

	for (i = 0; i < 6; i++) {
		if (dev->tempBuffer[i].line == 0) {
			dev->tempBuffer[i].line = lineNo;
			if ((i + 1) > dev->maxTemp) {
				dev->maxTemp = i + 1;
				for (j = 0; j <= i; j++)
					dev->tempBuffer[j].maxLine =
					    dev->tempBuffer[j].line;
			}

			return dev->tempBuffer[i].buffer;
		}
	}

	do{ if((0x00000400) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	for (i = 0; i < 6; i++) {
		do{ if((0x00000400) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	}
	do{ if((0x00000400) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	


 

	dev->unmanagedTempAllocations++;
	return yaffs_malloc(dev->nDataBytesPerChunk);

}

void yaffs_ReleaseTempBuffer(yaffs_Device * dev, __u8 * buffer,
				    int lineNo)
{
	int i;
	
	dev->tempInUse--;
	 
	for (i = 0; i < 6; i++) 
	{
		if (dev->tempBuffer[i].buffer == buffer) 
		{
			dev->tempBuffer[i].line = 0;
			return;
		}
	}
 
	if (buffer) {
		 
		do{ if((0x00000400) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	  
		free(buffer);
		dev->unmanagedTempDeallocations++;
	}

}



 
int yaffs_IsManagedTempBuffer(yaffs_Device * dev, const __u8 * buffer)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (dev->tempBuffer[i].buffer == buffer)
			return 1;

	}

    for (i = 0; i < dev->nShortOpCaches; i++) {
        if( dev->srCache[i].data == buffer )
            return 1;

    }

    if (buffer == dev->checkpointBuffer)
      return 1;

    do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

    return 0;
}





 

static __inline __u8 *yaffs_BlockBits(yaffs_Device * dev, int blk)
{
	if (blk < dev->internalStartBlock || blk > dev->internalEndBlock) {
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		;
	}
	return dev->chunkBits +
	    (dev->chunkBitmapStride * (blk - dev->internalStartBlock));
}

static __inline void yaffs_VerifyChunkBitId(yaffs_Device *dev, int blk, int chunk)
{
	if(blk < dev->internalStartBlock || blk > dev->internalEndBlock ||
	   chunk < 0 || chunk >= dev->nChunksPerBlock) {
	   do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	    ;
	}
}

static __inline void yaffs_ClearChunkBits(yaffs_Device * dev, int blk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);

	memset(blkBits, 0, dev->chunkBitmapStride);
}

static __inline void yaffs_ClearChunkBit(yaffs_Device * dev, int blk, int chunk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);

	yaffs_VerifyChunkBitId(dev,blk,chunk);

	blkBits[chunk / 8] &= ~(1 << (chunk & 7));
}

static __inline void yaffs_SetChunkBit(yaffs_Device * dev, int blk, int chunk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);
	
	yaffs_VerifyChunkBitId(dev,blk,chunk);

	blkBits[chunk / 8] |= (1 << (chunk & 7));
}

static __inline int yaffs_CheckChunkBit(yaffs_Device * dev, int blk, int chunk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);
	yaffs_VerifyChunkBitId(dev,blk,chunk);

	return (blkBits[chunk / 8] & (1 << (chunk & 7))) ? 1 : 0;
}

static __inline int yaffs_StillSomeChunkBits(yaffs_Device * dev, int blk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);
	int i;
	for (i = 0; i < dev->chunkBitmapStride; i++) {
		if (*blkBits)
			return 1;
		blkBits++;
	}
	return 0;
}

static int yaffs_CountChunkBits(yaffs_Device * dev, int blk)
{
	__u8 *blkBits = yaffs_BlockBits(dev, blk);
	int i;
	int n = 0;
	for (i = 0; i < dev->chunkBitmapStride; i++) {
		__u8 x = *blkBits;
		while(x){
			if(x & 1)
				n++;
			x >>=1;
		}
			
		blkBits++;
	}
	return n;
}



 
 
static int yaffs_SkipVerification(yaffs_Device *dev)
{
	return !(yaffs_traceMask & (0x00010000 | 0x00040000));
}

static int yaffs_SkipFullVerification(yaffs_Device *dev)
{
	return !(yaffs_traceMask & (0x00040000));
}

static int yaffs_SkipNANDVerification(yaffs_Device *dev)
{
	return !(yaffs_traceMask & (0x00020000));
}

static const char * blockStateName[] = {
"Unknown",
"Needs scanning",
"Scanning",
"Empty",
"Allocating",
"Full",
"Dirty",
"Checkpoint",
"Collecting",
"Dead"
};

static void yaffs_VerifyBlock(yaffs_Device *dev,yaffs_BlockInfo *bi,int n)
{
	int actuallyUsed;
	int inUse;
	
	if(yaffs_SkipVerification(dev))
		return;
		
	 
	if(bi->blockState >= (YAFFS_BLOCK_STATE_DEAD + 1))
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		
	switch(bi->blockState){
	 case YAFFS_BLOCK_STATE_UNKNOWN:
	 case YAFFS_BLOCK_STATE_SCANNING:
	 case YAFFS_BLOCK_STATE_NEEDS_SCANNING:
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	}
	
	 
	
	actuallyUsed = bi->pagesInUse - bi->softDeletions;
	
	if(bi->pagesInUse < 0 || bi->pagesInUse > dev->nChunksPerBlock ||
	   bi->softDeletions < 0 || bi->softDeletions > dev->nChunksPerBlock ||
	   actuallyUsed < 0 || actuallyUsed > dev->nChunksPerBlock)
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	
		
	 
	inUse = yaffs_CountChunkBits(dev,n);
	if(inUse != bi->pagesInUse)
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	
	

 
	if(dev->isYaffs2 && 
	   (bi->blockState == YAFFS_BLOCK_STATE_ALLOCATING || bi->blockState == YAFFS_BLOCK_STATE_FULL) &&
	   (bi->sequenceNumber < 0x00001000 || bi->sequenceNumber > 10000000 ))
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		
}

static void yaffs_VerifyCollectedBlock(yaffs_Device *dev,yaffs_BlockInfo *bi,int n)
{
	yaffs_VerifyBlock(dev,bi,n);
	
	 
	 
	
	if(bi->blockState != YAFFS_BLOCK_STATE_COLLECTING &&
	   bi->blockState != YAFFS_BLOCK_STATE_EMPTY){
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	}
}

static void yaffs_VerifyBlocks(yaffs_Device *dev)
{
	int i;
	int nBlocksPerState[(YAFFS_BLOCK_STATE_DEAD + 1)];
	int nIllegalBlockStates = 0;
	

	if(yaffs_SkipVerification(dev))
		return;

	memset(nBlocksPerState,0,sizeof(nBlocksPerState));

		
	for(i = dev->internalStartBlock; i <= dev->internalEndBlock; i++){
		yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev,i);
		yaffs_VerifyBlock(dev,bi,i);

		if(bi->blockState < (YAFFS_BLOCK_STATE_DEAD + 1))
			nBlocksPerState[bi->blockState]++;
		else
			nIllegalBlockStates++;
					
	}
	
	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	
	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	if(nBlocksPerState[YAFFS_BLOCK_STATE_ALLOCATING] > 1)
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	for(i = 0; i < (YAFFS_BLOCK_STATE_DEAD + 1); i++)
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	
	if(dev->blocksInCheckpoint != nBlocksPerState[YAFFS_BLOCK_STATE_CHECKPOINT])
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		 
	if(dev->nErasedBlocks != nBlocksPerState[YAFFS_BLOCK_STATE_EMPTY])
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		 
	if(nBlocksPerState[YAFFS_BLOCK_STATE_COLLECTING] > 1)
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

}




 
static void yaffs_VerifyObjectHeader(yaffs_Object *obj, yaffs_ObjectHeader *oh, yaffs_ExtendedTags *tags, int parentCheck)
{
	if(obj && yaffs_SkipVerification(obj->myDev))
		return;
		
	if(!(tags && obj && oh)){
	 	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		return;
	}
	
	if(oh->type <= YAFFS_OBJECT_TYPE_UNKNOWN ||
	   oh->type > YAFFS_OBJECT_TYPE_SPECIAL)
	 	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	if(tags->objectId != obj->objectId)
	 	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




	



 
	
	if(parentCheck && tags->objectId > 1 && !obj->parent)
	 	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		
	
	if(parentCheck && obj->parent &&
	   oh->parentObjectId != obj->parent->objectId && 
	   (oh->parentObjectId != 3 ||
	    obj->parent->objectId != 4))
	 	do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		
	
	if(tags->objectId > 1 && oh->name[0] == 0)  
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	if(tags->objectId > 1 && ((__u8)(oh->name[0])) == 0xff)  
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


}



static int yaffs_VerifyTnodeWorker(yaffs_Object * obj, yaffs_Tnode * tn,
				  	__u32 level, int chunkOffset)
{
	int i;
	yaffs_Device *dev = obj->myDev;
	int ok = 1;

	if (tn) {
		if (level > 0) {

			for (i = 0; i < (16 / 2) && ok; i++){
				if (tn->internal[i]) {
					ok = yaffs_VerifyTnodeWorker(obj,
							tn->internal[i],
							level - 1,
							(chunkOffset<<(4 - 1)) + i);
				}
			}
		} else if (level == 0) {
			yaffs_ExtendedTags tags;
			__u32 objectId = obj->objectId;
			
			chunkOffset <<=  4;
			
			for(i = 0; i < 16; i++){
				__u32 theChunk = yaffs_GetChunkGroupBase(dev,tn,i);
				
				if(theChunk > 0){
					 
					yaffs_ReadChunkWithTagsFromNAND(dev,theChunk,0, &tags);
					if(tags.objectId != objectId || tags.chunkId != chunkOffset){
						do{ if((~0) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


					}
				}
				chunkOffset++;
			}
		}
	}

	return ok;

}


static void yaffs_VerifyFile(yaffs_Object *obj)
{
	int requiredTallness;
	int actualTallness;
	__u32 lastChunk;
	__u32 x;
	__u32 i;
	yaffs_Device *dev;
	yaffs_ExtendedTags tags;
	yaffs_Tnode *tn;
	__u32 objectId;
	
	if(!obj)
		return;

	if(yaffs_SkipVerification(obj->myDev))
		return;
	
	dev = obj->myDev;
	objectId = obj->objectId;
	
	 
	lastChunk =  obj->variant.fileVariant.fileSize / dev->nDataBytesPerChunk + 1;
	x = lastChunk >> 4;
	requiredTallness = 0;
	while (x> 0) {
		x >>= (4 - 1);
		requiredTallness++;
	}
	
	actualTallness = obj->variant.fileVariant.topLevel;
	
	if(requiredTallness > actualTallness )
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	
	
	


 

	if(yaffs_SkipNANDVerification(dev))
		return;
		
	for(i = 1; i <= lastChunk; i++){
		tn = yaffs_FindLevel0Tnode(dev, &obj->variant.fileVariant,i);

		if (tn) {
			__u32 theChunk = yaffs_GetChunkGroupBase(dev,tn,i);
			if(theChunk > 0){
				 
				yaffs_ReadChunkWithTagsFromNAND(dev,theChunk,0, &tags);
				if(tags.objectId != objectId || tags.chunkId != i){
					do{ if((~0) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


				}
			}
		}

	}

}


static void yaffs_VerifyHardLink(yaffs_Object *obj)
{
	if(obj && yaffs_SkipVerification(obj->myDev))
		return;
		
	 
}

static void yaffs_VerifySymlink(yaffs_Object *obj)
{
	if(obj && yaffs_SkipVerification(obj->myDev))
		return;
		
	 
}

static void yaffs_VerifySpecial(yaffs_Object *obj)
{
	if(obj && yaffs_SkipVerification(obj->myDev))
		return;
}

static void yaffs_VerifyObject(yaffs_Object *obj)
{
	yaffs_Device *dev;
	
	__u32 chunkMin;
	__u32 chunkMax;
	
	__u32 chunkIdOk;
	__u32 chunkInRange;
	__u32 chunkShouldNotBeDeleted;
	__u32 chunkValid; 
	
	if(!obj)
		return;
		
	if(obj->beingCreated)
		return;
	
	dev = obj->myDev;
	
	if(yaffs_SkipVerification(dev))
		return;
		
	 

	chunkMin = dev->internalStartBlock * dev->nChunksPerBlock;
	chunkMax = (dev->internalEndBlock+1) * dev->nChunksPerBlock - 1;

	chunkInRange = (((unsigned)(obj->hdrChunk)) >= chunkMin && ((unsigned)(obj->hdrChunk)) <= chunkMax);
	chunkIdOk = chunkInRange || obj->hdrChunk == 0;
	chunkValid  =  chunkInRange &&
			yaffs_CheckChunkBit(dev,
					    obj->hdrChunk / dev->nChunksPerBlock,
					    obj->hdrChunk % dev->nChunksPerBlock);
	chunkShouldNotBeDeleted = chunkInRange && !chunkValid;

	if(!obj->fake &&
	    (!chunkIdOk || chunkShouldNotBeDeleted)) {
	   do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




	}
	
	if(chunkValid &&!yaffs_SkipNANDVerification(dev)) {
		yaffs_ExtendedTags tags;
		yaffs_ObjectHeader *oh;
		__u8 *buffer = yaffs_GetTempBuffer(dev,792);
		
		oh = (yaffs_ObjectHeader *)buffer;

		yaffs_ReadChunkWithTagsFromNAND(dev, obj->hdrChunk,buffer, &tags);

		yaffs_VerifyObjectHeader(obj,oh,&tags,1);
		
		yaffs_ReleaseTempBuffer(dev,buffer,800);
	}
	
	 
	if(obj && !obj->fake &&
	   (!obj->parent || obj->parent->myDev != dev)){
	   do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);	   


	}
	
	 
	if(obj->parent && obj->parent->variantType != YAFFS_OBJECT_TYPE_DIRECTORY){
	   do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);	   


	}
	
	switch(obj->variantType){
	case YAFFS_OBJECT_TYPE_FILE:
		yaffs_VerifyFile(obj);
		break;
	case YAFFS_OBJECT_TYPE_SYMLINK:
		yaffs_VerifySymlink(obj);
		break;
	case YAFFS_OBJECT_TYPE_DIRECTORY:
		yaffs_VerifyDirectory(obj);
		break;
	case YAFFS_OBJECT_TYPE_HARDLINK:
		yaffs_VerifyHardLink(obj);
		break;
	case YAFFS_OBJECT_TYPE_SPECIAL:
		yaffs_VerifySpecial(obj);
		break;
	case YAFFS_OBJECT_TYPE_UNKNOWN:
	default:
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);	   


		break;
	}
	
	
}

static void yaffs_VerifyObjects(yaffs_Device *dev)
{
        yaffs_Object *obj;
        int i;
        struct ylist_head *lh;

        if(yaffs_SkipVerification(dev))
                return;
	
         
         
         for(i = 0; i <  256; i++){
                for (lh = (&dev->objectBucket[i]. list)->next; lh != (&dev->objectBucket[i]. list); lh = lh->next ) {
                        if (lh) {
                                obj = ((yaffs_Object *)((char *)(lh)-(unsigned long)(&((yaffs_Object *)0)->hashLink)));
                                yaffs_VerifyObject(obj);
                        }
                }
	 }

}




 
 
static __inline int yaffs_HashFunction(int n)
{
	n = abs(n);
	return (n % 256);
}




 
 
yaffs_Object *yaffs_Root(yaffs_Device * dev)
{
	return dev->rootDir;
}

yaffs_Object *yaffs_LostNFound(yaffs_Device * dev)
{
	return dev->lostNFoundDir;
}




 
 
int yaffs_CheckFF(__u8 * buffer, int nBytes)
{
	 
	while (nBytes--) {
		if (*buffer != 0xFF)
			return 0;
		buffer++;
	}
	return 1;
}

static int yaffs_CheckChunkErased(struct yaffs_DeviceStruct *dev,
				  int chunkInNAND)
{

	int retval = 1;
	__u8 *data = yaffs_GetTempBuffer(dev, 914);
	yaffs_ExtendedTags tags;
	int result;

	result = yaffs_ReadChunkWithTagsFromNAND(dev, chunkInNAND, data, &tags);
	 
	if(tags.eccResult > YAFFS_ECC_RESULT_NO_ERROR)
		retval = 0;
		

	if (!yaffs_CheckFF(data, dev->nDataBytesPerChunk) || tags.chunkUsed) {
		do{ if((0x00000800) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		retval = 0;
	}

	yaffs_ReleaseTempBuffer(dev, data, 930);

	return retval;

}

static int yaffs_WriteNewChunkWithTagsToNAND(struct yaffs_DeviceStruct *dev,
					     const __u8 * data,
					     yaffs_ExtendedTags * tags,
					     int useReserve)
{
	int attempts = 0;
	int writeOk = 0;
	int chunk;

	yaffs_InvalidateCheckpoint(dev);
 
	do {
		yaffs_BlockInfo *bi = 0;
		int erasedOk = 0;

		chunk = yaffs_AllocateChunk(dev, useReserve, &bi);
		if (chunk < 0) 
		{
			 
			break;
		}

		

















 
		 
		if (bi->gcPrioritise) {
			yaffs_DeleteChunk(dev, chunk, 1, 979);
			 
			 
			continue;
		}
                 
		 
		attempts++;




		if (!bi->skipErasedCheck) 
		{
		
			erasedOk = yaffs_CheckChunkErased(dev, chunk);
			if (erasedOk != 1) 
			{
				do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


                           
				 
				continue;
			}
			 
			bi->skipErasedCheck = 1;
		}
 
		writeOk = yaffs_WriteChunkWithTagsToNAND(dev, chunk,data, tags);
	 	
		if (writeOk != 1) {
			yaffs_HandleWriteChunkError(dev, chunk, erasedOk);
			 
			continue;
		}

		 
		yaffs_HandleWriteChunkOk(dev, chunk, data, tags);
 
	} while (writeOk != 1 && (yaffs_wr_attempts <= 0 || attempts <= yaffs_wr_attempts));
	        
 
	if(!writeOk)
		chunk = -1;

	if (attempts > 1) 
	{
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		dev->nRetriedWrites += (attempts - 1);
	}

	return chunk;
}



 
 
static void yaffs_RetireBlock(yaffs_Device * dev, int blockInNAND)
{
	yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, blockInNAND);

	yaffs_InvalidateCheckpoint(dev);
	
	if (yaffs_MarkBlockBad(dev, blockInNAND) != 1) {
		if (yaffs_EraseBlockInNAND(dev, blockInNAND) != 1) {
			do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		}
		else {
			yaffs_ExtendedTags tags;
			int chunkId = blockInNAND * dev->nChunksPerBlock;

			__u8 *buffer = yaffs_GetTempBuffer(dev, 1057);

			memset(buffer, 0xff, dev->nDataBytesPerChunk);
			yaffs_InitialiseTags(&tags);
			tags.sequenceNumber = 0xFFFF0000;
			if (dev->writeChunkWithTagsToNAND(dev, chunkId -
			    dev->chunkOffset, buffer, &tags) != 1)
				do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



			yaffs_ReleaseTempBuffer(dev, buffer, 1068);
		}
	}

	bi->blockState = YAFFS_BLOCK_STATE_DEAD;
	bi->gcPrioritise = 0;
	bi->needsRetiring = 0;

	dev->nRetiredBlocks++;
}




 
 
static void yaffs_HandleWriteChunkOk(yaffs_Device * dev, int chunkInNAND,
				     const __u8 * data,
				     const yaffs_ExtendedTags * tags)
{
}

static void yaffs_HandleUpdateChunk(yaffs_Device * dev, int chunkInNAND,
				    const yaffs_ExtendedTags * tags)
{
}

void yaffs_HandleChunkError(yaffs_Device *dev, yaffs_BlockInfo *bi)
{
	if(!bi->gcPrioritise){
		bi->gcPrioritise = 1;
		dev->hasPendingPrioritisedGCs = 1;
		bi->chunkErrorStrikes ++;
		
		if(bi->chunkErrorStrikes > 3){
			bi->needsRetiring = 1;  
			do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		}
		
	}
}

static void yaffs_HandleWriteChunkError(yaffs_Device * dev, int chunkInNAND, int erasedOk)
{

	int blockInNAND = chunkInNAND / dev->nChunksPerBlock;
	yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, blockInNAND);

	yaffs_HandleChunkError(dev,bi);
		
	
	if(erasedOk ) {
		 
		bi->needsRetiring = 1;
		do{ if((0x40000000 | 0x00000010) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		
	}
	
	 
	yaffs_DeleteChunk(dev, chunkInNAND, 1, 1130);
}


  

static __u16 yaffs_CalcNameSum(const char * name)
{
	__u16 sum = 0;
	__u16 i = 1;

	const unsigned char *bname = (const unsigned char *) name;
	if (bname) {
		while ((*bname) && (i < (255/2))) {




			sum += (*bname) * i;

			i++;
			bname++;
		}
	}
	return sum;
}

static void yaffs_SetObjectName(yaffs_Object * obj, const char * name)
{
#line 1167 "..\\fs\\yaffs_guts.c"
	obj->sum = yaffs_CalcNameSum(name);
}






 
 



 

static int yaffs_CreateTnodes(yaffs_Device * dev, int nTnodes)
{
	int i;
	int tnodeSize;
	yaffs_Tnode *newTnodes;
	__u8 *mem;
	yaffs_Tnode *curr;
	yaffs_Tnode *next;
	yaffs_TnodeList *tnl;

	if (nTnodes < 1)
		return 1;
		
	
 
	tnodeSize = (dev->tnodeWidth * 16)/8;

	if(tnodeSize < sizeof(yaffs_Tnode))
		tnodeSize = sizeof(yaffs_Tnode);
		

	 

	newTnodes = yaffs_malloc(nTnodes * tnodeSize);
	mem = (__u8 *)newTnodes;

	if (!newTnodes) {
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}

	 
#line 1229 "..\\fs\\yaffs_guts.c"
	 
	for(i = 0; i < nTnodes -1; i++) {
		curr = (yaffs_Tnode *) &mem[i * tnodeSize];
		next = (yaffs_Tnode *) &mem[(i+1) * tnodeSize];
		curr->internal[0] = next;
	}
	
	curr = (yaffs_Tnode *) &mem[(nTnodes - 1) * tnodeSize];
	curr->internal[0] = dev->freeTnodes;
	dev->freeTnodes = (yaffs_Tnode *)mem;




	dev->nFreeTnodes += nTnodes;
	dev->nTnodesCreated += nTnodes;

	


 
	 
	tnl = yaffs_malloc(sizeof(yaffs_TnodeList));
	if (!tnl) {
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		   return 0;

	} else {
		tnl->tnodes = newTnodes;
		tnl->next = dev->allocatedTnodeList;
		dev->allocatedTnodeList = tnl;
	}

	do{ if((0x00000004) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	return 1;
}

 

static yaffs_Tnode *yaffs_GetTnodeRaw(yaffs_Device * dev)
{
	yaffs_Tnode *tn = 0;

	 
	if (!dev->freeTnodes) {
		yaffs_CreateTnodes(dev, 100);
	}

	if (dev->freeTnodes) {
		tn = dev->freeTnodes;
#line 1289 "..\\fs\\yaffs_guts.c"
		dev->freeTnodes = dev->freeTnodes->internal[0];
		dev->nFreeTnodes--;
	}

	dev->nCheckpointBlocksRequired = 0;  

	return tn;
}

static yaffs_Tnode *yaffs_GetTnode(yaffs_Device * dev)
{
	yaffs_Tnode *tn = yaffs_GetTnodeRaw(dev);
	int tnodeSize = (dev->tnodeWidth * 16)/8;

	if(tnodeSize < sizeof(yaffs_Tnode))
		tnodeSize = sizeof(yaffs_Tnode);
	
	if(tn)
		memset(tn, 0, tnodeSize);

	return tn;	
}

 
static void yaffs_FreeTnode(yaffs_Device * dev, yaffs_Tnode * tn)
{
	if (tn) {
#line 1324 "..\\fs\\yaffs_guts.c"
		tn->internal[0] = dev->freeTnodes;
		dev->freeTnodes = tn;
		dev->nFreeTnodes++;
	}
	dev->nCheckpointBlocksRequired = 0;  
	
}

static void yaffs_DeinitialiseTnodes(yaffs_Device * dev)
{
	 
	yaffs_TnodeList *tmp;

	while (dev->allocatedTnodeList) {
		tmp = dev->allocatedTnodeList->next;

		free(dev->allocatedTnodeList->tnodes);
		free(dev->allocatedTnodeList);
		dev->allocatedTnodeList = tmp;

	}

	dev->freeTnodes = 0;
	dev->nFreeTnodes = 0;
}

static void yaffs_InitialiseTnodes(yaffs_Device * dev)
{
	dev->allocatedTnodeList = 0;
	dev->freeTnodes = 0;
	dev->nFreeTnodes = 0;
	dev->nTnodesCreated = 0;

}


void yaffs_PutLevel0Tnode(yaffs_Device *dev, yaffs_Tnode *tn, unsigned pos, unsigned val)
{
  __u32 *map = (__u32 *)tn;
  __u32 bitInMap;
  __u32 bitInWord;
  __u32 wordInMap;
  __u32 mask;
  
  pos &= 0xf;
  val >>= dev->chunkGroupBits;
  
  bitInMap = pos * dev->tnodeWidth;
  wordInMap = bitInMap /32;
  bitInWord = bitInMap & (32 -1);
  
  mask = dev->tnodeMask << bitInWord;
  
  map[wordInMap] &= ~mask;
  map[wordInMap] |= (mask & (val << bitInWord));
  
  if(dev->tnodeWidth > (32-bitInWord)) {
    bitInWord = (32 - bitInWord);
    wordInMap++;;
    mask = dev->tnodeMask >> (  bitInWord);
    map[wordInMap] &= ~mask;
    map[wordInMap] |= (mask & (val >> bitInWord));
  }
}

static __u32 yaffs_GetChunkGroupBase(yaffs_Device *dev, yaffs_Tnode *tn, unsigned pos)
{
  __u32 *map = (__u32 *)tn;
  __u32 bitInMap;
  __u32 bitInWord;
  __u32 wordInMap;
  __u32 val;
  
  pos &= 0xf;
  
  bitInMap = pos * dev->tnodeWidth;
  wordInMap = bitInMap /32;
  bitInWord = bitInMap & (32 -1);
  
  val = map[wordInMap] >> bitInWord;
  
  if(dev->tnodeWidth > (32-bitInWord)) {
    bitInWord = (32 - bitInWord);
    wordInMap++;;
    val |= (map[wordInMap] << bitInWord);
  }
  
  val &= dev->tnodeMask;
  val <<= dev->chunkGroupBits;
  
  return val;
}

 




 

 
static yaffs_Tnode *yaffs_FindLevel0Tnode(yaffs_Device * dev,
					  yaffs_FileStructure * fStruct,
					  __u32 chunkId)
{

	yaffs_Tnode *tn = fStruct->top;
	__u32 i;
	int requiredTallness;
	int level = fStruct->topLevel;

	 
	if (level < 0 || level > 6) {
		return 0;
	}

	if (chunkId > 0x000FFFFF) {
		return 0;
	}

	 

	i = chunkId >> 4;
	requiredTallness = 0;
	while (i) {
		i >>= (4 - 1);
		requiredTallness++;
	}

	if (requiredTallness > fStruct->topLevel) {
		 
		return 0;
	}

	 
	while (level > 0 && tn) {
		tn = tn->
		    internal[(chunkId >>
			       ( 4 + 
			         (level - 1) *
			         (4 - 1))
			      ) &
			     0x7];
		level--;

	}

	return tn;
}










 
 
static yaffs_Tnode *yaffs_AddOrFindLevel0Tnode(yaffs_Device * dev,
					       yaffs_FileStructure * fStruct,
					       __u32 chunkId,
					       yaffs_Tnode *passedTn)
{

	int requiredTallness;
	int i;
	int l;
	yaffs_Tnode *tn;

	__u32 x;


	 
	if (fStruct->topLevel < 0 || fStruct->topLevel > 6) {
		return 0;
	}

	if (chunkId > 0x000FFFFF) {
		return 0;
	}

	 

	x = chunkId >> 4;
	requiredTallness = 0;
	while (x) {
		x >>= (4 - 1);
		requiredTallness++;
	}


	if (requiredTallness > fStruct->topLevel) {
		 
		for (i = fStruct->topLevel; i < requiredTallness; i++) {
		
			tn = yaffs_GetTnode(dev);

			if (tn) {
				tn->internal[0] = fStruct->top;
				fStruct->top = tn;
			} else {
				do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			}
		}

		fStruct->topLevel = requiredTallness;
	}

	 

	l = fStruct->topLevel;
	tn = fStruct->top;
	
	if(l > 0) {
		while (l > 0 && tn) {
			x = (chunkId >>
			     ( 4 +
			      (l - 1) * (4 - 1))) &
			    0x7;


			if((l>1) && !tn->internal[x]){
				 
				tn->internal[x] = yaffs_GetTnode(dev);

			} else if(l == 1) {
				 
			 	if (passedTn) {
					 
					if(tn->internal[x])
						yaffs_FreeTnode(dev,tn->internal[x]);
					tn->internal[x] = passedTn;
			
				} else if(!tn->internal[x]) {
					 
					tn->internal[x] = yaffs_GetTnode(dev);
				}
			}
		
			tn = tn->internal[x];
			l--;
		}
	} else {
		 
		if(passedTn) {
			memcpy(tn,passedTn,(dev->tnodeWidth * 16)/8);
			yaffs_FreeTnode(dev,passedTn);
		}
	}

	return tn;
}

static int yaffs_FindChunkInGroup(yaffs_Device * dev, int theChunk,
				  yaffs_ExtendedTags * tags, int objectId,
				  int chunkInInode)
{
	int j;

	for (j = 0; theChunk && j < dev->chunkGroupSize; j++) {
		if (yaffs_CheckChunkBit
		    (dev, theChunk / dev->nChunksPerBlock,
		     theChunk % dev->nChunksPerBlock)) {
			yaffs_ReadChunkWithTagsFromNAND(dev, theChunk, 0,
							tags);
			if (yaffs_TagsMatch(tags, objectId, chunkInInode)) {
				 
				return theChunk;

			}
		}
		theChunk++;
	}
	return -1;
}






 

static int yaffs_DeleteWorker(yaffs_Object * in, yaffs_Tnode * tn, __u32 level,
			      int chunkOffset, int *limit)
{
	int i;
	int chunkInInode;
	int theChunk;
	yaffs_ExtendedTags tags;
	int foundChunk;
	yaffs_Device *dev = in->myDev;

	int allDone = 1;

	if (tn) {
		if (level > 0) {

			for (i = (16 / 2) - 1; allDone && i >= 0;
			     i--) {
				if (tn->internal[i]) {
					if (limit && (*limit) < 0) {
						allDone = 0;
					} else {
						allDone =
						    yaffs_DeleteWorker(in,
								       tn->
								       internal
								       [i],
								       level -
								       1,
								       (chunkOffset
									<<
									(4 - 1))
								       + i,
								       limit);
					}
					if (allDone) {
						yaffs_FreeTnode(dev,
								tn->
								internal[i]);
						tn->internal[i] = 0;
					}
				}

			}
			return (allDone) ? 1 : 0;
		} else if (level == 0) {
			int hitLimit = 0;

			for (i = 16 - 1; i >= 0 && !hitLimit;
			     i--) {
			        theChunk = yaffs_GetChunkGroupBase(dev,tn,i);
				if (theChunk) {

					chunkInInode =
					    (chunkOffset <<
					     4) + i;

					foundChunk =
					    yaffs_FindChunkInGroup(dev,
								   theChunk,
								   &tags,
								   in->objectId,
								   chunkInInode);

					if (foundChunk > 0) {
						yaffs_DeleteChunk(dev,
								  foundChunk, 1,
								  1677);
						in->nDataChunks--;
						if (limit) {
							*limit = *limit - 1;
							if (*limit <= 0) {
								hitLimit = 1;
							}
						}

					}

					yaffs_PutLevel0Tnode(dev,tn,i,0);
				}

			}
			return (i < 0) ? 1 : 0;

		}

	}

	return 1;

}

static void yaffs_SoftDeleteChunk(yaffs_Device * dev, int chunk)
{

	yaffs_BlockInfo *theBlock;

	do{ if((0x00000200) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	theBlock = yaffs_GetBlockInfo(dev, chunk / dev->nChunksPerBlock);
	if (theBlock) {
		theBlock->softDeletions++;
		dev->nFreeChunks++;
	}
}





 
 
static int yaffs_SoftDeleteWorker(yaffs_Object * in, yaffs_Tnode * tn,
				  __u32 level, int chunkOffset)
{
	int i;
	int theChunk;
	int allDone = 1;
	yaffs_Device *dev = in->myDev;

	if (tn) {
		if (level > 0) {

			for (i = (16 / 2) - 1; allDone && i >= 0;
			     i--) {
				if (tn->internal[i]) {
					allDone =
					    yaffs_SoftDeleteWorker(in,
								   tn->
								   internal[i],
								   level - 1,
								   (chunkOffset
								    <<
								    (4 - 1))
								   + i);
					if (allDone) {
						yaffs_FreeTnode(dev,
								tn->
								internal[i]);
						tn->internal[i] = 0;
					} else {
						 
					}
				}
			}
			return (allDone) ? 1 : 0;
		} else if (level == 0) {

			for (i = 16 - 1; i >= 0; i--) {
				theChunk = yaffs_GetChunkGroupBase(dev,tn,i);
				if (theChunk) {
					


 
					yaffs_SoftDeleteChunk(dev, theChunk);
					yaffs_PutLevel0Tnode(dev,tn,i,0);
				}

			}
			return 1;

		}

	}

	return 1;

}

static void yaffs_SoftDeleteFile(yaffs_Object * obj)
{
	if (obj->deleted &&
	    obj->variantType == YAFFS_OBJECT_TYPE_FILE && !obj->softDeleted) {
		if (obj->nDataChunks <= 0) {
			 
			yaffs_FreeTnode(obj->myDev,
					obj->variant.fileVariant.top);
			obj->variant.fileVariant.top = 0;
			do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


			yaffs_DoGenericObjectDeletion(obj);
		} else {
			yaffs_SoftDeleteWorker(obj,
					       obj->variant.fileVariant.top,
					       obj->variant.fileVariant.
					       topLevel, 0);
			obj->softDeleted = 1;
		}
	}
}










 

static yaffs_Tnode *yaffs_PruneWorker(yaffs_Device * dev, yaffs_Tnode * tn,
				      __u32 level, int del0)
{
	int i;
	int hasData;

	if (tn) {
		hasData = 0;

		for (i = 0; i < (16 / 2); i++) {
			if (tn->internal[i] && level > 0) {
				tn->internal[i] =
				    yaffs_PruneWorker(dev, tn->internal[i],
						      level - 1,
						      (i == 0) ? del0 : 1);
			}

			if (tn->internal[i]) {
				hasData++;
			}
		}

		if (hasData == 0 && del0) {
			 

			yaffs_FreeTnode(dev, tn);
			tn = 0;
		}

	}

	return tn;

}

static int yaffs_PruneFileStructure(yaffs_Device * dev,
				    yaffs_FileStructure * fStruct)
{
	int i;
	int hasData;
	int done = 0;
	yaffs_Tnode *tn;

	if (fStruct->topLevel > 0) {
		fStruct->top =
		    yaffs_PruneWorker(dev, fStruct->top, fStruct->topLevel, 0);

		




 

		while (fStruct->topLevel && !done) {
			tn = fStruct->top;

			hasData = 0;
			for (i = 1; i < (16 / 2); i++) {
				if (tn->internal[i]) {
					hasData++;
				}
			}

			if (!hasData) {
				fStruct->top = tn->internal[0];
				fStruct->topLevel--;
				yaffs_FreeTnode(dev, tn);
			} else {
				done = 1;
			}
		}
	}

	return 1;
}

 



 
static int yaffs_CreateFreeObjects(yaffs_Device * dev, int nObjects)
{
	int i;
	yaffs_Object *newObjects;
	yaffs_ObjectList *list;

	if (nObjects < 1)
		return 1;

	 
	newObjects = yaffs_malloc(nObjects * sizeof(yaffs_Object));
	list = yaffs_malloc(sizeof(yaffs_ObjectList));

	if (!newObjects || !list) {
		if(newObjects)
			free(newObjects);
		if(list)
			free(list);
		do{ if((0x00000004) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}
	
         
        for (i = 0; i < nObjects - 1; i++) {
                newObjects[i].siblings.next =
                    (struct ylist_head *)(&newObjects[i + 1]);
        }

        newObjects[nObjects - 1].siblings.next = (void *)dev->freeObjects;
	dev->freeObjects = newObjects;
	dev->nFreeObjects += nObjects;
	dev->nObjectsCreated += nObjects;

	 

	list->objects = newObjects;
	list->next = dev->allocatedObjectList;
	dev->allocatedObjectList = list;

	return 1;
}


 
static yaffs_Object *yaffs_AllocateEmptyObject(yaffs_Device * dev)
{
	yaffs_Object *tn = 0;




	 
	if (!dev->freeObjects) {
		yaffs_CreateFreeObjects(dev, 100);
	}

	if (dev->freeObjects) {
		tn = dev->freeObjects;
		dev->freeObjects =
		    (yaffs_Object *) (dev->freeObjects->siblings.next);
		dev->nFreeObjects--;
	}

	if(tn){
		 

		memset(tn, 0, sizeof(yaffs_Object));
		tn->beingCreated = 1;
		
		tn->myDev = dev;
		tn->hdrChunk = 0;
		tn->variantType = YAFFS_OBJECT_TYPE_UNKNOWN;
		do { (&(tn->hardLinks))->next = (&(tn->hardLinks)); (&(tn->hardLinks))->prev = (&(tn->hardLinks)); } while(0);
		do { (&(tn->hashLink))->next = (&(tn->hashLink)); (&(tn->hashLink))->prev = (&(tn->hashLink)); } while(0);
		do { (&tn->siblings)->next = (&tn->siblings); (&tn->siblings)->prev = (&tn->siblings); } while(0);
		

		 
		if(dev->rootDir){
			tn->parent = dev->rootDir;
			ylist_add(&(tn->siblings),&dev->rootDir->variant.directoryVariant.children);
		}

                


 
		if (dev->lostNFoundDir) {
			yaffs_AddObjectToDirectory(dev->lostNFoundDir, tn);
		}
		
		tn->beingCreated = 0;
	}
	
	dev->nCheckpointBlocksRequired = 0;  

	return tn;
}

static yaffs_Object *yaffs_CreateFakeDirectory(yaffs_Device * dev, int number,
					       __u32 mode)
{

	yaffs_Object *obj =
	    yaffs_CreateNewObject(dev, number, YAFFS_OBJECT_TYPE_DIRECTORY);
	if (obj) {
		obj->fake = 1;		 
		obj->renameAllowed = 0;	 
		obj->unlinkAllowed = 0;	 
		obj->deleted = 0;
		obj->unlinked = 0;
		obj->yst_mode = mode;
		obj->myDev = dev;
		obj->hdrChunk = 0;	 
	}

	return obj;

}

static void yaffs_UnhashObject(yaffs_Object * tn)
{
	int bucket;
        yaffs_Device *dev = tn->myDev;

         
        if (!ylist_empty(&tn->hashLink)) {
                ylist_del_init(&tn->hashLink);
                bucket = yaffs_HashFunction(tn->objectId);
                dev->objectBucket[bucket].count--;
        }

}

 
static void yaffs_FreeObject(yaffs_Object * tn)
{

	yaffs_Device *dev = tn->myDev;

	
	if(tn->parent)
		;
	if(!ylist_empty(&tn->siblings))
		;


#line 2053 "..\\fs\\yaffs_guts.c"

        yaffs_UnhashObject(tn);




         
        tn->siblings.next = (struct ylist_head *)(dev->freeObjects);
        dev->freeObjects = tn;
        dev->nFreeObjects++;

	dev->nCheckpointBlocksRequired = 0;  

}

#line 2078 "..\\fs\\yaffs_guts.c"

static void yaffs_DeinitialiseObjects(yaffs_Device * dev)
{
	 

	yaffs_ObjectList *tmp;

	while (dev->allocatedObjectList) {
		tmp = dev->allocatedObjectList->next;
		free(dev->allocatedObjectList->objects);
		free(dev->allocatedObjectList);

		dev->allocatedObjectList = tmp;
	}

	dev->freeObjects = 0;
	dev->nFreeObjects = 0;
}

static void yaffs_InitialiseObjects(yaffs_Device * dev)
{
	int i;

	dev->allocatedObjectList = 0;
	dev->freeObjects = 0;
        dev->nFreeObjects = 0;

        for (i = 0; i < 256; i++) {
                do { (&dev->objectBucket[i]. list)->next = (&dev->objectBucket[i]. list); (&dev->objectBucket[i]. list)->prev = (&dev->objectBucket[i]. list); } while(0);
                dev->objectBucket[i].count = 0;
        }

}

static int yaffs_FindNiceObjectBucket(yaffs_Device * dev)
{
	static int x = 0;
	int i;
	int l = 999;
	int lowest = 999999;

	 

	for (i = 0; i < 10 && lowest > 0; i++) {
		x++;
		x %= 256;
		if (dev->objectBucket[x].count < lowest) {
			lowest = dev->objectBucket[x].count;
			l = x;
		}

	}

	

 

	for (i = 0; i < 10 && lowest > 3; i++) {
		x++;
		x %= 256;
		if (dev->objectBucket[x].count < lowest) {
			lowest = dev->objectBucket[x].count;
			l = x;
		}

	}

	return l;
}

static int yaffs_CreateNewObjectNumber(yaffs_Device * dev)
{
	int bucket = yaffs_FindNiceObjectBucket(dev);

	

 

        int found = 0;
        struct ylist_head *i;

        __u32 n = (__u32) bucket;

	 

	while (!found) {
                found = 1;
                n += 256;
                if (1 || dev->objectBucket[bucket].count > 0) {
                        for (i = (&dev->objectBucket[bucket]. list)->next; i != (&dev->objectBucket[bucket]. list); i = i->next ) {
                                 
                                if (i
                                    && ((yaffs_Object *)((char *)(i)-(unsigned long)(&((yaffs_Object *)0)->hashLink)))->objectId == n) {

                                        found = 0;
                                }
			}
		}
	}


	return n;
}

static void yaffs_HashObject(yaffs_Object * in)
{
        int bucket = yaffs_HashFunction(in->objectId);
        yaffs_Device *dev = in->myDev;

        ylist_add(&in->hashLink, &dev->objectBucket[bucket].list);
        dev->objectBucket[bucket].count++;

}

yaffs_Object *yaffs_FindObjectByNumber(yaffs_Device * dev, __u32 number)
{
        int bucket = yaffs_HashFunction(number);
        struct ylist_head *i;
        yaffs_Object *in;

        for (i = (&dev->objectBucket[bucket]. list)->next; i != (&dev->objectBucket[bucket]. list); i = i->next ) {
                 
                if (i) {
                        in = ((yaffs_Object *)((char *)(i)-(unsigned long)(&((yaffs_Object *)0)->hashLink)));
                        if (in->objectId == number) {






				return in;
			}
		}
	}

	return 0;
}

yaffs_Object *yaffs_CreateNewObject(yaffs_Device * dev, int number,
				    yaffs_ObjectType type)
{

	yaffs_Object *theObject;
	yaffs_Tnode *tn = 0;

	if (number < 0) {
		number = yaffs_CreateNewObjectNumber(dev);
	}

	theObject = yaffs_AllocateEmptyObject(dev);
	if(!theObject)
		return 0;
		
	if(type == YAFFS_OBJECT_TYPE_FILE){
		tn = yaffs_GetTnode(dev);
		if(!tn){
			yaffs_FreeObject(theObject);
			return 0;
		}
	}
		
	

	if (theObject) {
		theObject->fake = 0;
		theObject->renameAllowed = 1;
		theObject->unlinkAllowed = 1;
		theObject->objectId = number;
		yaffs_HashObject(theObject);
		theObject->variantType = type;
#line 2257 "..\\fs\\yaffs_guts.c"

		theObject->yst_atime = theObject->yst_mtime =
		    theObject->yst_ctime = yaffsfs_CurrentTime();

		switch (type) {
		case YAFFS_OBJECT_TYPE_FILE:
			theObject->variant.fileVariant.fileSize = 0;
			theObject->variant.fileVariant.scannedFileSize = 0;
			theObject->variant.fileVariant.shrinkSize = 0xFFFFFFFF;	 
			theObject->variant.fileVariant.topLevel = 0;
                        theObject->variant.fileVariant.top = tn;
                        break;
                case YAFFS_OBJECT_TYPE_DIRECTORY:
                        do { (&theObject->variant . directoryVariant . children)->next = (&theObject->variant . directoryVariant . children); (&theObject->variant . directoryVariant . children)->prev = (&theObject->variant . directoryVariant . children); } while(0);

                        break;
                case YAFFS_OBJECT_TYPE_SYMLINK:
		case YAFFS_OBJECT_TYPE_HARDLINK:
		case YAFFS_OBJECT_TYPE_SPECIAL:
			 
			break;
		case YAFFS_OBJECT_TYPE_UNKNOWN:
			 
			break;
		}
	}

	return theObject;
}

static yaffs_Object *yaffs_FindOrCreateObjectByNumber(yaffs_Device * dev,
						      int number,
						      yaffs_ObjectType type)
{
	yaffs_Object *theObject = 0;

	if (number > 0) {
		theObject = yaffs_FindObjectByNumber(dev, number);
	}

	if (!theObject) {
		theObject = yaffs_CreateNewObject(dev, number, type);
	}

	return theObject;

}
			

static char *yaffs_CloneString(const char * str)
{
	char *newStr = 0;

	if (str && *str) {
		newStr = yaffs_malloc((strlen(str) + 1) * sizeof(char));
		if(newStr)
			strcpy(newStr,str);
	}

	return newStr;

}






 
 
static yaffs_Object *yaffs_MknodObject(yaffs_ObjectType type,
				       yaffs_Object * parent,
				       const char * name,
				       __u32 mode,
				       __u32 uid,
				       __u32 gid,
				       yaffs_Object * equivalentObject,
				       const char * aliasString, __u32 rdev)
{
	yaffs_Object *in;
	char *str = 0;

	yaffs_Device *dev = parent->myDev;
 
	 
	if (yaffs_FindObjectByName(parent, name)) {
		return 0;
	}

	in = yaffs_CreateNewObject(dev, -1, type);

	if(!in)
		return 0;
	 
	if(type == YAFFS_OBJECT_TYPE_SYMLINK)
	{
		str = yaffs_CloneString(aliasString);
	 
		if(!str)
		{
			yaffs_FreeObject(in);
			return 0;
		}
	}
 
	

	if (in) {
		in->hdrChunk = 0;
		in->valid = 1;
		in->variantType = type;

		in->yst_mode = mode;

#line 2377 "..\\fs\\yaffs_guts.c"
		in->yst_atime = in->yst_mtime = in->yst_ctime = yaffsfs_CurrentTime();

		in->yst_rdev = rdev;
		in->yst_uid = uid;
		in->yst_gid = gid;

		in->nDataChunks = 0;

		yaffs_SetObjectName(in, name);
		in->dirty = 1;

		yaffs_AddObjectToDirectory(parent, in);

		in->myDev = parent->myDev;
 
		switch (type) {
		case YAFFS_OBJECT_TYPE_SYMLINK:
			in->variant.symLinkVariant.alias = str;
			break;
		case YAFFS_OBJECT_TYPE_HARDLINK:
			in->variant.hardLinkVariant.equivalentObject =
                            equivalentObject;
                        in->variant.hardLinkVariant.equivalentObjectId =
                            equivalentObject->objectId;
                        ylist_add(&in->hardLinks, &equivalentObject->hardLinks);
                        break;
                case YAFFS_OBJECT_TYPE_FILE:    
                case YAFFS_OBJECT_TYPE_DIRECTORY:
		case YAFFS_OBJECT_TYPE_SPECIAL:
		case YAFFS_OBJECT_TYPE_UNKNOWN:
			 
			break;
		}
 
		if (yaffs_UpdateObjectHeader(in, name, 0, 0, 0) < 0) {
			 
 
			yaffs_DestroyObject(in);
			in = 0;
		}

	}

	return in;
}

yaffs_Object *yaffs_MknodFile(yaffs_Object * parent, const char * name,
			      __u32 mode, __u32 uid, __u32 gid)
{
	return yaffs_MknodObject(YAFFS_OBJECT_TYPE_FILE, parent, name, mode,
				 uid, gid, 0, 0, 0);
}

yaffs_Object *yaffs_MknodDirectory(yaffs_Object * parent, const char * name,
				   __u32 mode, __u32 uid, __u32 gid)
{
	return yaffs_MknodObject(YAFFS_OBJECT_TYPE_DIRECTORY, parent, name,
				 mode, uid, gid, 0, 0, 0);
}

yaffs_Object *yaffs_MknodSpecial(yaffs_Object * parent, const char * name,
				 __u32 mode, __u32 uid, __u32 gid, __u32 rdev)
{
	return yaffs_MknodObject(YAFFS_OBJECT_TYPE_SPECIAL, parent, name, mode,
				 uid, gid, 0, 0, rdev);
}

yaffs_Object *yaffs_MknodSymLink(yaffs_Object * parent, const char * name,
				 __u32 mode, __u32 uid, __u32 gid,
				 const char * alias)
{
	return yaffs_MknodObject(YAFFS_OBJECT_TYPE_SYMLINK, parent, name, mode,
				 uid, gid, 0, alias, 0);
}

 
yaffs_Object *yaffs_Link(yaffs_Object * parent, const char * name,
			 yaffs_Object * equivalentObject)
{
	 
	equivalentObject = yaffs_GetEquivalentObject(equivalentObject);

	if (yaffs_MknodObject
	    (YAFFS_OBJECT_TYPE_HARDLINK, parent, name, 0, 0, 0,
	     equivalentObject, 0, 0)) {
		return equivalentObject;
	} else {
		return 0;
	}

}

static int yaffs_ChangeObjectName(yaffs_Object * obj, yaffs_Object * newDir,
				  const char * newName, int force, int shadows)
{
	int unlinkOp;
	int deleteOp;

	yaffs_Object *existingTarget;

	if (newDir == 0) {
		newDir = obj->parent;	 
	}

	if (newDir->variantType != YAFFS_OBJECT_TYPE_DIRECTORY) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		;
	}
	
	 
	if (obj->myDev->isYaffs2) {
		unlinkOp = (newDir == obj->myDev->unlinkedDir);
	} else {
		unlinkOp = (newDir == obj->myDev->unlinkedDir
			    && obj->variantType == YAFFS_OBJECT_TYPE_FILE);
	}

	deleteOp = (newDir == obj->myDev->deletedDir);

	existingTarget = yaffs_FindObjectByName(newDir, newName);

	



 
	if ((unlinkOp ||
	     deleteOp ||
	     force ||
	     (shadows > 0) ||
	     !existingTarget) &&
	    newDir->variantType == YAFFS_OBJECT_TYPE_DIRECTORY) {
		yaffs_SetObjectName(obj, newName);
		obj->dirty = 1;

		yaffs_AddObjectToDirectory(newDir, obj);

		if (unlinkOp)
			obj->unlinked = 1;

		 
		if (yaffs_UpdateObjectHeader(obj, newName, 0, deleteOp, shadows)>= 0)
			return 1;
	}

	return 0;
}

int yaffs_RenameObject(yaffs_Object * oldDir, const char * oldName,
		       yaffs_Object * newDir, const char * newName)
{
	yaffs_Object *obj=0;
	yaffs_Object *existingTarget=0;
	int force = 0;
	
	
	if(!oldDir || oldDir->variantType != YAFFS_OBJECT_TYPE_DIRECTORY)
		;
	if(!newDir || newDir->variantType != YAFFS_OBJECT_TYPE_DIRECTORY)
		;

#line 2550 "..\\fs\\yaffs_guts.c"

	else if (strlen(newName) > 255)
	   
	  return 0;

	obj = yaffs_FindObjectByName(oldDir, oldName);

	if (obj && obj->renameAllowed) {

		 

                existingTarget = yaffs_FindObjectByName(newDir, newName);
                if (existingTarget &&
                    existingTarget->variantType == YAFFS_OBJECT_TYPE_DIRECTORY &&
                    !ylist_empty(&existingTarget->variant.directoryVariant.children)) {
                         
                        return 0;       
                } else if (existingTarget && existingTarget != obj) {
			

 
			yaffs_ChangeObjectName(obj, newDir, newName, force,
					       existingTarget->objectId);
			yaffs_UnlinkObject(existingTarget);
		}

		return yaffs_ChangeObjectName(obj, newDir, newName, 1, 0);
	}
	return 0;
}

 

static int yaffs_InitialiseBlocks(yaffs_Device * dev)
{
	int nBlocks = dev->internalEndBlock - dev->internalStartBlock + 1;

    
	dev->blockInfo = 0;
	dev->chunkBits = 0;
	
	dev->allocationBlock = -1;	 

	 
	dev->blockInfo = yaffs_malloc(nBlocks * sizeof(yaffs_BlockInfo));
    
	if(!dev->blockInfo){
		dev->blockInfo = yaffs_malloc(nBlocks * sizeof(yaffs_BlockInfo));
		dev->blockInfoAlt = 1;
	}
	else
		dev->blockInfoAlt = 0;
    
	if(dev->blockInfo){
	    
		 
		dev->chunkBitmapStride = (dev->nChunksPerBlock + 7) / 8;  
		dev->chunkBits = yaffs_malloc(dev->chunkBitmapStride * nBlocks);
		if(!dev->chunkBits){
			dev->chunkBits = yaffs_malloc(dev->chunkBitmapStride * nBlocks);
			dev->chunkBitsAlt = 1;
		}
		else
			dev->chunkBitsAlt = 0;
	}
	
	if (dev->blockInfo && dev->chunkBits) {
		memset(dev->blockInfo, 0, nBlocks * sizeof(yaffs_BlockInfo));
		memset(dev->chunkBits, 0, dev->chunkBitmapStride * nBlocks);
		return 1;
	}

    
    
	return 0;

}

static void yaffs_DeinitialiseBlocks(yaffs_Device * dev)
{
	if(dev->blockInfoAlt && dev->blockInfo)
		free(dev->blockInfo);
	else if(dev->blockInfo)
		free(dev->blockInfo);

	dev->blockInfoAlt = 0;

	dev->blockInfo = 0;
	
	if(dev->chunkBitsAlt && dev->chunkBits)
		free(dev->chunkBits);
	else if(dev->chunkBits)
		free(dev->chunkBits);
	dev->chunkBitsAlt = 0;
	dev->chunkBits = 0;
}

static int yaffs_BlockNotDisqualifiedFromGC(yaffs_Device * dev,
					    yaffs_BlockInfo * bi)
{
	int i;
	__u32 seq;
	yaffs_BlockInfo *b;

	if (!dev->isYaffs2)
		return 1;	 

	if (!bi->hasShrinkHeader)
		return 1;	 

	

 
	if (!dev->oldestDirtySequence) {
		seq = dev->sequenceNumber;

		for (i = dev->internalStartBlock; i <= dev->internalEndBlock;
		     i++) {
			b = yaffs_GetBlockInfo(dev, i);
			if (b->blockState == YAFFS_BLOCK_STATE_FULL &&
			    (b->pagesInUse - b->softDeletions) <
			    dev->nChunksPerBlock && b->sequenceNumber < seq) {
				seq = b->sequenceNumber;
			}
		}
		dev->oldestDirtySequence = seq;
	}

	

 
	return (bi->sequenceNumber <= dev->oldestDirtySequence);

}



 

static int yaffs_FindBlockForGarbageCollection(yaffs_Device * dev,
					       int aggressive)
{

	int b = dev->currentDirtyChecker;

	int i;
	int iterations;
	int dirtiest = -1;
	int pagesInUse = 0;
	int prioritised=0;
	yaffs_BlockInfo *bi;
	int pendingPrioritisedExist = 0;
	
	 
	if(dev->hasPendingPrioritisedGCs){
		for(i = dev->internalStartBlock; i < dev->internalEndBlock && !prioritised; i++){

			bi = yaffs_GetBlockInfo(dev, i);
			
			
			if(bi->gcPrioritise) {
				pendingPrioritisedExist = 1;
				if(bi->blockState == YAFFS_BLOCK_STATE_FULL &&
				   yaffs_BlockNotDisqualifiedFromGC(dev, bi)){
					pagesInUse = (bi->pagesInUse - bi->softDeletions);
					dirtiest = i;
					prioritised = 1;
					aggressive = 1;  
				}
			}
		}
		
		if(!pendingPrioritisedExist)  
			dev->hasPendingPrioritisedGCs = 0;
	}

	



 

	dev->nonAggressiveSkip--;

	if (!aggressive && (dev->nonAggressiveSkip > 0)) {
		return -1;
	}

	if(!prioritised)
		pagesInUse =
	    		(aggressive) ? dev->nChunksPerBlock : 2 + 1;

	if (aggressive) {
		iterations =
		    dev->internalEndBlock - dev->internalStartBlock + 1;
	} else {
		iterations =
		    dev->internalEndBlock - dev->internalStartBlock + 1;
		iterations = iterations / 16;
		if (iterations > 200) {
			iterations = 200;
		}
	}

	for (i = 0; i <= iterations && pagesInUse > 0 && !prioritised; i++) {
		b++;
		if (b < dev->internalStartBlock || b > dev->internalEndBlock) {
			b = dev->internalStartBlock;
		}

		if (b < dev->internalStartBlock || b > dev->internalEndBlock) {
			do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			;
		}

		bi = yaffs_GetBlockInfo(dev, b);

#line 2775 "..\\fs\\yaffs_guts.c"

		if (bi->blockState == YAFFS_BLOCK_STATE_FULL &&
		       (bi->pagesInUse - bi->softDeletions) < pagesInUse &&
		        yaffs_BlockNotDisqualifiedFromGC(dev, bi)) {
			dirtiest = b;
			pagesInUse = (bi->pagesInUse - bi->softDeletions);
		}
	}

	dev->currentDirtyChecker = b;

	if (dirtiest > 0) {
		do{ if((0x00000040) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	}

	dev->oldestDirtySequence = 0;

	if (dirtiest > 0) {
		dev->nonAggressiveSkip = 4;
	}

	return dirtiest;
}

static void yaffs_BlockBecameDirty(yaffs_Device * dev, int blockNo)
{
	yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, blockNo);

	int erasedOk = 0;

	

 
	 
	do{ if((0x00000040 | 0x00000020) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		
	bi->blockState = YAFFS_BLOCK_STATE_DIRTY;

	if (!bi->needsRetiring) {
		yaffs_InvalidateCheckpoint(dev);
		erasedOk = yaffs_EraseBlockInNAND(dev, blockNo);
		if (!erasedOk) {
			dev->nErasureFailures++;
			do{ if((0x40000000 | 0x00000010) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		}
	}

	if (erasedOk && 
	    ((yaffs_traceMask & 0x00000020) || !yaffs_SkipVerification(dev))) {
		int i;
		for (i = 0; i < dev->nChunksPerBlock; i++) {
			if (!yaffs_CheckChunkErased
			    (dev, blockNo * dev->nChunksPerBlock + i)) {
				do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



			}
		}
	}

	if (erasedOk) {
		 
		bi->blockState = YAFFS_BLOCK_STATE_EMPTY;
		dev->nErasedBlocks++;
		bi->pagesInUse = 0;
		bi->softDeletions = 0;
		bi->hasShrinkHeader = 0;
		bi->skipErasedCheck = 1;   
		bi->gcPrioritise = 0;
		yaffs_ClearChunkBits(dev, blockNo);

		do{ if((0x00000020) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	} else {
		dev->nFreeChunks -= dev->nChunksPerBlock;	 

		yaffs_RetireBlock(dev, blockNo);
		do{ if((0x40000000 | 0x00000010) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	}
}

static int yaffs_FindBlockForAllocation(yaffs_Device * dev)
{
	int i;

	yaffs_BlockInfo *bi;

	if (dev->nErasedBlocks < 1) {
		

 
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		return -1;
	}
	
	 

	for (i = dev->internalStartBlock; i <= dev->internalEndBlock; i++) {
		dev->allocationBlockFinder++;
		if (dev->allocationBlockFinder < dev->internalStartBlock
		    || dev->allocationBlockFinder > dev->internalEndBlock) {
			dev->allocationBlockFinder = dev->internalStartBlock;
		}

		bi = yaffs_GetBlockInfo(dev, dev->allocationBlockFinder);

		if (bi->blockState == YAFFS_BLOCK_STATE_EMPTY) {
			bi->blockState = YAFFS_BLOCK_STATE_ALLOCATING;
			dev->sequenceNumber++;
			bi->sequenceNumber = dev->sequenceNumber;
			dev->nErasedBlocks--;
			do{ if((0x00000004) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



			return dev->allocationBlockFinder;
		}
	}

	do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




	return -1;
}



static int yaffs_CalcCheckpointBlocksRequired(yaffs_Device *dev)
{
	if(!dev->nCheckpointBlocksRequired &&
	   dev->isYaffs2){
		 
		int nBytes = 0;
		int nBlocks;
		int devBlocks = (dev->endBlock - dev->startBlock + 1);
		int tnodeSize;

		tnodeSize = (dev->tnodeWidth * 16)/8;

		if(tnodeSize < sizeof(yaffs_Tnode))
			tnodeSize = sizeof(yaffs_Tnode);
		
		nBytes += sizeof(yaffs_CheckpointValidity);
		nBytes += sizeof(yaffs_CheckpointDevice);
		nBytes += devBlocks * sizeof(yaffs_BlockInfo);
		nBytes += devBlocks * dev->chunkBitmapStride;
		nBytes += (sizeof(yaffs_CheckpointObject) + sizeof(__u32)) * (dev->nObjectsCreated - dev->nFreeObjects);
		nBytes += (tnodeSize + sizeof(__u32)) * (dev->nTnodesCreated - dev->nFreeTnodes);
		nBytes += sizeof(yaffs_CheckpointValidity);
		nBytes += sizeof(__u32);  
	
		 
	
		nBlocks = (nBytes/(dev->nDataBytesPerChunk * dev->nChunksPerBlock)) + 3;
	
		dev->nCheckpointBlocksRequired = nBlocks;
	}

	return dev->nCheckpointBlocksRequired;
}



static int yaffs_CheckSpaceForAllocation(yaffs_Device * dev)
{
	int reservedChunks;
	int reservedBlocks = dev->nReservedBlocks;
	int checkpointBlocks;
	
	if(dev->isYaffs2){
		checkpointBlocks =  yaffs_CalcCheckpointBlocksRequired(dev) - 
				    dev->blocksInCheckpoint;
		if(checkpointBlocks < 0)
			checkpointBlocks = 0;
	} else {
		checkpointBlocks =0;
	}
	
	reservedChunks = ((reservedBlocks + checkpointBlocks) * dev->nChunksPerBlock);
	
	return (dev->nFreeChunks > reservedChunks);
}

static int yaffs_AllocateChunk(yaffs_Device * dev, int useReserve, yaffs_BlockInfo **blockUsedPtr)
{
	int retVal;
	yaffs_BlockInfo *bi;

	if (dev->allocationBlock < 0) {
		 
		dev->allocationBlock = yaffs_FindBlockForAllocation(dev);
		dev->allocationPage = 0;
	}

	if (!useReserve && !yaffs_CheckSpaceForAllocation(dev)) {
		 
		return -1;
	}

	if (dev->nErasedBlocks < dev->nReservedBlocks
	    && dev->allocationPage == 0) {
		do{ if((0x00000004) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	}

	 
	if (dev->allocationBlock >= 0) {
		bi = yaffs_GetBlockInfo(dev, dev->allocationBlock);

		retVal = (dev->allocationBlock * dev->nChunksPerBlock) +
		    dev->allocationPage;
		bi->pagesInUse++;
		yaffs_SetChunkBit(dev, dev->allocationBlock,
				  dev->allocationPage);

		dev->allocationPage++;

		dev->nFreeChunks--;

		 
		if (dev->allocationPage >= dev->nChunksPerBlock) {
			bi->blockState = YAFFS_BLOCK_STATE_FULL;
			dev->allocationBlock = -1;
		}

		if(blockUsedPtr)
			*blockUsedPtr = bi;
			
		return retVal;
	}
	
	do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	return -1;
}

static int yaffs_GetErasedChunks(yaffs_Device * dev)
{
	int n;

	n = dev->nErasedBlocks * dev->nChunksPerBlock;

	if (dev->allocationBlock > 0) {
		n += (dev->nChunksPerBlock - dev->allocationPage);
	}

	return n;

}

static int yaffs_GarbageCollectBlock(yaffs_Device * dev, int block, int wholeBlock)
{
	int oldChunk;
	int newChunk;
	int markNAND;
	int retVal = 1;
	int cleanups = 0;
	int i;
	int isCheckpointBlock;
	int matchingChunk;
	int maxCopies;

	int chunksBefore = yaffs_GetErasedChunks(dev);
	int chunksAfter;

	yaffs_ExtendedTags tags;

	yaffs_BlockInfo *bi = yaffs_GetBlockInfo(dev, block);

	yaffs_Object *object;

	isCheckpointBlock = (bi->blockState == YAFFS_BLOCK_STATE_CHECKPOINT);
	
	bi->blockState = YAFFS_BLOCK_STATE_COLLECTING;

	do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);






	 

	bi->hasShrinkHeader = 0;	 

	

 
	dev->nFreeChunks -= bi->softDeletions;

	dev->isDoingGC = 1;

	if (isCheckpointBlock ||
	    !yaffs_StillSomeChunkBits(dev, block)) {
		do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		yaffs_BlockBecameDirty(dev, block);
	} else {

		__u8 *buffer = yaffs_GetTempBuffer(dev, 3088);
		
		yaffs_VerifyBlock(dev,bi,block);

		maxCopies = (wholeBlock) ? dev->nChunksPerBlock : 10;
		oldChunk = block * dev->nChunksPerBlock + dev->gcChunk;
		
		for (  ;
		     retVal == 1 &&
		     dev->gcChunk < dev->nChunksPerBlock &&
		     (bi->blockState == YAFFS_BLOCK_STATE_COLLECTING)&&
		     maxCopies > 0;
		     dev->gcChunk++, oldChunk++) {
			if (yaffs_CheckChunkBit(dev, block, dev->gcChunk)) {

				 
				
				maxCopies--;

				markNAND = 1;

				yaffs_InitialiseTags(&tags);

				yaffs_ReadChunkWithTagsFromNAND(dev, oldChunk,
								buffer, &tags);

				object =
				    yaffs_FindObjectByNumber(dev,
							     tags.objectId);

				do{ if((0x00001000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




				   
				if(object && !yaffs_SkipVerification(dev)){
					if(tags.chunkId == 0)
						matchingChunk = object->hdrChunk;
					else if(object->softDeleted)
						matchingChunk = oldChunk;  
					else
						matchingChunk = yaffs_FindChunkInFile(object,tags.chunkId,0);
					
					if(oldChunk != matchingChunk)
						do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


						
				}

				if (!object) {
					do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




				}

				if (object && 
				    object->deleted &&
				    object->softDeleted &&
				    tags.chunkId != 0) {
					



 

					object->nDataChunks--;

					if (object->nDataChunks <= 0) {
						 
						dev->gcCleanupList[cleanups] =
						    tags.objectId;
						cleanups++;
					}
					markNAND = 0;
				} else if (0
					    
					   ) {
					

 
					object->hdrChunk = 0;
					yaffs_FreeTnode(object->myDev,
							object->variant.
							fileVariant.top);
					object->variant.fileVariant.top = 0;
					yaffs_DoGenericObjectDeletion(object);

				} else if (object) {
					



 
					tags.serialNumber++;

					dev->nGCCopies++;

					if (tags.chunkId == 0) {
						



 

						yaffs_ObjectHeader *oh;
						oh = (yaffs_ObjectHeader *)buffer;
						oh->isShrink = 0;
						tags.extraIsShrinkHeader = 0;
						
						yaffs_VerifyObjectHeader(object,oh,&tags,1);
					}

					newChunk =
					    yaffs_WriteNewChunkWithTagsToNAND(dev, buffer, &tags, 1);

					if (newChunk < 0) {
						retVal = 0;
					} else {

						 

						if (tags.chunkId == 0) {
							 
							object->hdrChunk =  newChunk;
							object->serial =   tags.serialNumber;
						} else {
							 
							yaffs_PutChunkIntoFile
							    (object,
							     tags.chunkId,
							     newChunk, 0);
						}
					}
				}

				if(retVal == 1)
					yaffs_DeleteChunk(dev, oldChunk, markNAND, 3228);

			}
		}

		yaffs_ReleaseTempBuffer(dev, buffer, 3233);


		 
		for (i = 0; i < cleanups; i++) {
			 
			object =
			    yaffs_FindObjectByNumber(dev,
						     dev->gcCleanupList[i]);
			if (object) {
				yaffs_FreeTnode(dev,
						object->variant.fileVariant.
						top);
				object->variant.fileVariant.top = 0;
				do{ if((0x00000040) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



				yaffs_DoGenericObjectDeletion(object);
				object->myDev->nDeletedFiles--;
			}

		}

	}

	yaffs_VerifyCollectedBlock(dev,bi,block);
	  
	if (chunksBefore >= (chunksAfter = yaffs_GetErasedChunks(dev))) {
		do{ if((0x00000040) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	}

	 
	if(bi->blockState != YAFFS_BLOCK_STATE_COLLECTING){
		dev->gcBlock = -1;
		dev->gcChunk = 0;
	}
	
	dev->isDoingGC = 0;

	return retVal;
}









 
static int yaffs_CheckGarbageCollection(yaffs_Device * dev)
{
	int block;
	int aggressive;
	int gcOk = 1;
	int maxTries = 0;
	
	int checkpointBlockAdjust;

	if (dev->isDoingGC) {
		 
		return 1;
	}
	
	

 

	do {
		maxTries++;
		
		checkpointBlockAdjust = yaffs_CalcCheckpointBlocksRequired(dev) - dev->blocksInCheckpoint;
		if(checkpointBlockAdjust < 0)
			checkpointBlockAdjust = 0;

		if (dev->nErasedBlocks < (dev->nReservedBlocks + checkpointBlockAdjust + 2)) {
			 
			aggressive = 1;
		} else {
			 
			aggressive = 0;
		}

		if(dev->gcBlock <= 0){
			dev->gcBlock = yaffs_FindBlockForGarbageCollection(dev, aggressive);
			dev->gcChunk = 0;
		}
		
		block = dev->gcBlock;

		if (block > 0) {
			dev->garbageCollections++;
			if (!aggressive) {
				dev->passiveGarbageCollections++;
			}

			do{ if((0x00000040) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




			gcOk = yaffs_GarbageCollectBlock(dev,block,aggressive);
		}

		if (dev->nErasedBlocks < (dev->nReservedBlocks) && block > 0) {
			do{ if((0x00000040) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		}
	} while ((dev->nErasedBlocks < dev->nReservedBlocks) && 
		 (block > 0) &&
		 (maxTries < 2));

	return aggressive ? gcOk : 1;
}

 

static int yaffs_TagsMatch(const yaffs_ExtendedTags * tags, int objectId,
			   int chunkInObject)
{
	return (tags->chunkId == chunkInObject &&
		tags->objectId == objectId && !tags->chunkDeleted) ? 1 : 0;

}


 

static int yaffs_FindChunkInFile(yaffs_Object * in, int chunkInInode,
				 yaffs_ExtendedTags * tags)
{
	 
	yaffs_Tnode *tn;
	int theChunk = -1;
	yaffs_ExtendedTags localTags;
	int retVal = -1;

	yaffs_Device *dev = in->myDev;

	if (!tags) {
		 
		tags = &localTags;
	}

	tn = yaffs_FindLevel0Tnode(dev, &in->variant.fileVariant, chunkInInode);

	if (tn) {
		theChunk = yaffs_GetChunkGroupBase(dev,tn,chunkInInode);

		retVal =
		    yaffs_FindChunkInGroup(dev, theChunk, tags, in->objectId,
					   chunkInInode);
	}
	return retVal;
}

static int yaffs_FindAndDeleteChunkInFile(yaffs_Object * in, int chunkInInode,
					  yaffs_ExtendedTags * tags)
{
	 
	yaffs_Tnode *tn;
	int theChunk = -1;
	yaffs_ExtendedTags localTags;

	yaffs_Device *dev = in->myDev;
	int retVal = -1;

	if (!tags) {
		 
		tags = &localTags;
	}

	tn = yaffs_FindLevel0Tnode(dev, &in->variant.fileVariant, chunkInInode);

	if (tn) {

		theChunk = yaffs_GetChunkGroupBase(dev,tn,chunkInInode);

		retVal =
		    yaffs_FindChunkInGroup(dev, theChunk, tags, in->objectId,
					   chunkInInode);

		 
		if (retVal != -1) {
			yaffs_PutLevel0Tnode(dev,tn,chunkInInode,0);
		}
	} else {
		 
	}

	if (retVal == -1) {
		 
	}
	return retVal;
}

#line 3495 "..\\fs\\yaffs_guts.c"

static int yaffs_PutChunkIntoFile(yaffs_Object * in, int chunkInInode,
				  int chunkInNAND, int inScan)
{
	


 
	 
	yaffs_Tnode *tn;
	yaffs_Device *dev = in->myDev;
	int existingChunk;
	yaffs_ExtendedTags existingTags;
	yaffs_ExtendedTags newTags;
	unsigned existingSerial, newSerial;

	if (in->variantType != YAFFS_OBJECT_TYPE_FILE) {
		

 
		if (!inScan) {
			do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



			;
		}

		yaffs_DeleteChunk(dev, chunkInNAND, 1, 3523);
		return 1;
	}

	tn = yaffs_AddOrFindLevel0Tnode(dev, 
					&in->variant.fileVariant,
					chunkInInode,
					0);
	if (!tn) {
		return 0;
	}

	existingChunk = yaffs_GetChunkGroupBase(dev,tn,chunkInInode);

	if (inScan != 0) {
		






 

		if (existingChunk > 0) {
			







 

			if (inScan > 0) {
				 
				yaffs_ReadChunkWithTagsFromNAND(dev,
								chunkInNAND,
								0, &newTags);

				 
				existingChunk =
				    yaffs_FindChunkInFile(in, chunkInInode,
							  &existingTags);
			}

			if (existingChunk <= 0) {
				 

				do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




			}

			

 

			if(inScan > 0) {
				newSerial = newTags.serialNumber;
				existingSerial = existingTags.serialNumber;
			}

			if ((inScan > 0) &&
			    (in->myDev->isYaffs2 ||
			     existingChunk <= 0 ||
			     ((existingSerial + 1) & 3) == newSerial)) {
				


 
				yaffs_DeleteChunk(dev, existingChunk, 1,
						  3598);
			} else {
				


 
				yaffs_DeleteChunk(dev, chunkInNAND, 1,
						  3605);
				return 1;
			}
		}

	}

	if (existingChunk == 0) {
		in->nDataChunks++;
	}

	yaffs_PutLevel0Tnode(dev,tn,chunkInInode,chunkInNAND);

	return 1;
}

static int yaffs_ReadChunkDataFromObject(yaffs_Object * in, int chunkInInode,
					 __u8 * buffer)
{
	int chunkInNAND = yaffs_FindChunkInFile(in, chunkInInode, 0);
        
	if (chunkInNAND >= 0) {
		return yaffs_ReadChunkWithTagsFromNAND(in->myDev, chunkInNAND, buffer,0);
						      
	} else {
		do{ if((0x00000800) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		 
		memset(buffer, 0, in->myDev->nDataBytesPerChunk);	
		return 0;
	}

}

void yaffs_DeleteChunk(yaffs_Device * dev, int chunkId, int markNAND, int lyn)
{
	int block;
	int page;
	yaffs_ExtendedTags tags;
	yaffs_BlockInfo *bi;

	if (chunkId <= 0)
		return;
		

	dev->nDeletions++;
	block = chunkId / dev->nChunksPerBlock;
	page = chunkId % dev->nChunksPerBlock;


	if(!yaffs_CheckChunkBit(dev,block,page))
		do{ if((0x00010000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	bi = yaffs_GetBlockInfo(dev, block);

	do{ if((0x00000200) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	if (markNAND &&
	    bi->blockState != YAFFS_BLOCK_STATE_COLLECTING && !dev->isYaffs2) {

		yaffs_InitialiseTags(&tags);

		tags.chunkDeleted = 1;

		yaffs_WriteChunkWithTagsToNAND(dev, chunkId, 0, &tags);
		yaffs_HandleUpdateChunk(dev, chunkId, &tags);
	} else {
		dev->nUnmarkedDeletions++;
	}

	

 
	if (bi->blockState == YAFFS_BLOCK_STATE_ALLOCATING ||
	    bi->blockState == YAFFS_BLOCK_STATE_FULL ||
	    bi->blockState == YAFFS_BLOCK_STATE_NEEDS_SCANNING ||
	    bi->blockState == YAFFS_BLOCK_STATE_COLLECTING) {
		dev->nFreeChunks++;

		yaffs_ClearChunkBit(dev, block, page);

		bi->pagesInUse--;

		if (bi->pagesInUse == 0 &&
		    !bi->hasShrinkHeader &&
		    bi->blockState != YAFFS_BLOCK_STATE_ALLOCATING &&
		    bi->blockState != YAFFS_BLOCK_STATE_NEEDS_SCANNING) {
			yaffs_BlockBecameDirty(dev, block);
		}

	} else {
		 
	}

}

static int yaffs_WriteChunkDataToObject(yaffs_Object * in, int chunkInInode,
					const __u8 * buffer, int nBytes,
					int useReserve)
{
	


 

	int prevChunkId;
	yaffs_ExtendedTags prevTags;

	int newChunkId;
	yaffs_ExtendedTags newTags;

	yaffs_Device *dev = in->myDev;

	yaffs_CheckGarbageCollection(dev);

	 
	prevChunkId = yaffs_FindChunkInFile(in, chunkInInode, &prevTags);

	 
	yaffs_InitialiseTags(&newTags);

	newTags.chunkId = chunkInInode;
	newTags.objectId = in->objectId;
	newTags.serialNumber =
	    (prevChunkId >= 0) ? prevTags.serialNumber + 1 : 1;
	newTags.byteCount = nBytes;
	
	if(nBytes < 1 || nBytes > dev->totalBytesPerChunk){
	  do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	  ;
     }
	
	

	newChunkId =
	    yaffs_WriteNewChunkWithTagsToNAND(dev, buffer, &newTags,
					      useReserve);

	if (newChunkId >= 0) {
		yaffs_PutChunkIntoFile(in, chunkInInode, newChunkId, 0);

		if (prevChunkId >= 0) {
			yaffs_DeleteChunk(dev, prevChunkId, 1, 3752);

		}

		;
	}
	return newChunkId;

}



 
int yaffs_UpdateObjectHeader(yaffs_Object * in, const char * name, int force,
			     int isShrink, int shadows)
{

	yaffs_BlockInfo *bi;

	yaffs_Device *dev = in->myDev;

	int prevChunkId;
	int retVal = 0;
	int result = 0;

	int newChunkId;
	yaffs_ExtendedTags newTags;
	yaffs_ExtendedTags oldTags;

	__u8 *buffer = 0;
	char oldName[255 + 1];

        yaffs_ObjectHeader *oh = 0;
        
        strcpy(oldName,"silly old name");
 

	if (!in->fake || 
	    in == dev->rootDir ||  
	    force) {

		yaffs_CheckGarbageCollection(dev);
		yaffs_CheckObjectDetailsLoaded(in);
 
		buffer = yaffs_GetTempBuffer(in->myDev, 3796);
		oh = (yaffs_ObjectHeader *) buffer;
 
		prevChunkId = in->hdrChunk;

		if (prevChunkId > 0) {
			result = yaffs_ReadChunkWithTagsFromNAND(dev, prevChunkId,
							buffer, &oldTags);
			 
			yaffs_VerifyObjectHeader(in,oh,&oldTags,0);
			 					
			memcpy(oldName, oh->name, sizeof(oh->name));
		}
 
		memset(buffer, 0xFF, dev->nDataBytesPerChunk);

		oh->type = in->variantType;
		oh->yst_mode = in->yst_mode;
		oh->shadowsObject = oh->inbandShadowsObject = shadows;

#line 3824 "..\\fs\\yaffs_guts.c"
		oh->yst_uid = in->yst_uid;
		oh->yst_gid = in->yst_gid;
		oh->yst_atime = in->yst_atime;
		oh->yst_mtime = in->yst_mtime;
		oh->yst_ctime = in->yst_ctime;
		oh->yst_rdev = in->yst_rdev;

		if (in->parent) {
			oh->parentObjectId = in->parent->objectId;
		} else {
			oh->parentObjectId = 0;
		}

		if (name && *name) {
			memset(oh->name, 0, sizeof(oh->name));
			strncpy(oh->name,name,255);
		} else if (prevChunkId>=0) {
			memcpy(oh->name, oldName, sizeof(oh->name));
		} else {
			memset(oh->name, 0, sizeof(oh->name));
		}

		oh->isShrink = isShrink;
 
		switch (in->variantType) {
		case YAFFS_OBJECT_TYPE_UNKNOWN:
			 
			break;
		case YAFFS_OBJECT_TYPE_FILE:
			oh->fileSize =
			    (oh->parentObjectId == 4
			     || oh->parentObjectId ==
			     3) ? 0 : in->variant.
			    fileVariant.fileSize;
			break;
		case YAFFS_OBJECT_TYPE_HARDLINK:
			oh->equivalentObjectId =
			    in->variant.hardLinkVariant.equivalentObjectId;
			break;
		case YAFFS_OBJECT_TYPE_SPECIAL:
			 
			break;
		case YAFFS_OBJECT_TYPE_DIRECTORY:
			 
			break;
		case YAFFS_OBJECT_TYPE_SYMLINK:
			strncpy(oh->alias,in->variant . symLinkVariant . alias,159);


			oh->alias[159] = 0;
			break;
		}
 
		 
		yaffs_InitialiseTags(&newTags);
		in->serial++;
		newTags.chunkId = 0;
		newTags.objectId = in->objectId;
		newTags.serialNumber = in->serial;

		 

		newTags.extraHeaderInfoAvailable = 1;
		newTags.extraParentObjectId = oh->parentObjectId;
		newTags.extraFileLength = oh->fileSize;
		newTags.extraIsShrinkHeader = oh->isShrink;
		newTags.extraEquivalentObjectId = oh->equivalentObjectId;
		newTags.extraShadows = (oh->shadowsObject > 0) ? 1 : 0;
		newTags.extraObjectType = in->variantType;

		yaffs_VerifyObjectHeader(in,oh,&newTags,1);
 
		 
		newChunkId =
		    yaffs_WriteNewChunkWithTagsToNAND(dev, buffer, &newTags,
						      (prevChunkId >= 0) ? 1 : 0);
 
		if (newChunkId >= 0) {

			in->hdrChunk = newChunkId;

			if (prevChunkId >= 0) {
				yaffs_DeleteChunk(dev, prevChunkId, 1,
						  3907);
			}

			if(!yaffs_ObjectHasCachedWriteData(in))
				in->dirty = 0;

			 
			if (isShrink) {
				bi = yaffs_GetBlockInfo(in->myDev,
							newChunkId /in->myDev->	nChunksPerBlock);
				bi->hasShrinkHeader = 1;
			}

		}

		retVal = newChunkId;

	}
 
	if (buffer)
		yaffs_ReleaseTempBuffer(dev, buffer, 3927);
 
	return retVal;
}












 

static int yaffs_ObjectHasCachedWriteData(yaffs_Object *obj)
{
	yaffs_Device *dev = obj->myDev;
	int i;
	yaffs_ChunkCache *cache;
	int nCaches = obj->myDev->nShortOpCaches;
	
	for(i = 0; i < nCaches; i++){
		cache = &dev->srCache[i];
		if (cache->object == obj &&
		    cache->dirty)
			return 1;
	}
	
	return 0;
}


static void yaffs_FlushFilesChunkCache(yaffs_Object * obj)
{
	yaffs_Device *dev = obj->myDev;
	int lowest = -99;	 
	int i;
	yaffs_ChunkCache *cache;
	int chunkWritten = 0;
	int nCaches = obj->myDev->nShortOpCaches;

	if (nCaches > 0) {
		do {
			cache = 0;

			 
			for (i = 0; i < nCaches; i++) {
				if (dev->srCache[i].object == obj &&
				    dev->srCache[i].dirty) {
					if (!cache
					    || dev->srCache[i].chunkId <
					    lowest) {
						cache = &dev->srCache[i];
						lowest = cache->chunkId;
					}
				}
			}

			if (cache && !cache->locked) {
				 

				chunkWritten =
				    yaffs_WriteChunkDataToObject(cache->object,
								 cache->chunkId,
								 cache->data,
								 cache->nBytes,
								 1);
				cache->dirty = 0;
				cache->object = 0;
			}

		} while (cache && chunkWritten > 0);

		if (cache) {
			 
			do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		}
	}

}




 

void yaffs_FlushEntireDeviceCache(yaffs_Device *dev)
{
	yaffs_Object *obj;
	int nCaches = dev->nShortOpCaches;
	int i;
	
	

 
	do {
		obj = 0;
		for( i = 0; i < nCaches && !obj; i++) {
			if (dev->srCache[i].object &&
			    dev->srCache[i].dirty)
				obj = dev->srCache[i].object;
			    
		}
		if(obj)
			yaffs_FlushFilesChunkCache(obj);
			
	} while(obj);
	
}






 
static yaffs_ChunkCache *yaffs_GrabChunkCacheWorker(yaffs_Device * dev)
{
	int i;

	if (dev->nShortOpCaches > 0) {
		for (i = 0; i < dev->nShortOpCaches; i++) {
			if (!dev->srCache[i].object) 
				return &dev->srCache[i];
		}
	}

	return 0;
}

static yaffs_ChunkCache *yaffs_GrabChunkCache(yaffs_Device * dev)
{
	yaffs_ChunkCache *cache;
	yaffs_Object *theObj;
	int usage;
	int i;
	int pushout;

	if (dev->nShortOpCaches > 0) {
		 

		cache = yaffs_GrabChunkCacheWorker(dev);

		if (!cache) {
			



 

			 

			theObj = 0;
			usage = -1;
			cache = 0;
			pushout = -1;

			for (i = 0; i < dev->nShortOpCaches; i++) {
				if (dev->srCache[i].object &&
				    !dev->srCache[i].locked &&
				    (dev->srCache[i].lastUse < usage || !cache))
				{
					usage = dev->srCache[i].lastUse;
					theObj = dev->srCache[i].object;
					cache = &dev->srCache[i];
					pushout = i;
				}
			}

			if (!cache || cache->dirty) {
				 
				yaffs_FlushFilesChunkCache(theObj);
				cache = yaffs_GrabChunkCacheWorker(dev);
			}

		}
		return cache;
	} else
		return 0;

}

 
static yaffs_ChunkCache *yaffs_FindChunkCache(const yaffs_Object * obj,
					      int chunkId)
{
	yaffs_Device *dev = obj->myDev;
	int i;
	if (dev->nShortOpCaches > 0) {
		for (i = 0; i < dev->nShortOpCaches; i++) {
			if (dev->srCache[i].object == obj &&
			    dev->srCache[i].chunkId == chunkId) {
				dev->cacheHits++;

				return &dev->srCache[i];
			}
		}
	}
	return 0;
}

 
static void yaffs_UseChunkCache(yaffs_Device * dev, yaffs_ChunkCache * cache,
				int isAWrite)
{

	if (dev->nShortOpCaches > 0) {
		if (dev->srLastUse < 0 || dev->srLastUse > 100000000) {
			 
			int i;
			for (i = 1; i < dev->nShortOpCaches; i++) {
				dev->srCache[i].lastUse = 0;
			}
			dev->srLastUse = 0;
		}

		dev->srLastUse++;

		cache->lastUse = dev->srLastUse;

		if (isAWrite) {
			cache->dirty = 1;
		}
	}
}




 
static void yaffs_InvalidateChunkCache(yaffs_Object * object, int chunkId)
{
	if (object->myDev->nShortOpCaches > 0) {
		yaffs_ChunkCache *cache = yaffs_FindChunkCache(object, chunkId);

		if (cache) {
			cache->object = 0;
		}
	}
}



 
static void yaffs_InvalidateWholeChunkCache(yaffs_Object * in)
{
	int i;
	yaffs_Device *dev = in->myDev;

	if (dev->nShortOpCaches > 0) {
		 
		for (i = 0; i < dev->nShortOpCaches; i++) {
			if (dev->srCache[i].object == in) {
				dev->srCache[i].object = 0;
			}
		}
	}
}

 


static int yaffs_WriteCheckpointValidityMarker(yaffs_Device *dev,int head)
{
	yaffs_CheckpointValidity cp;
	
	memset(&cp,0,sizeof(cp));
	
	cp.structType = sizeof(cp);
	cp.magic = 0x5941FF53;
	cp.version = 3;
	cp.head = (head) ? 1 : 0;
	
	return (yaffs_CheckpointWrite(dev,&cp,sizeof(cp)) == sizeof(cp))?
		1 : 0;
}

static int yaffs_ReadCheckpointValidityMarker(yaffs_Device *dev, int head)
{
	yaffs_CheckpointValidity cp;
	int ok;

    
	ok = (yaffs_CheckpointRead(dev,&cp,sizeof(cp)) == sizeof(cp));
    
	if(ok)
		ok = (cp.structType == sizeof(cp)) &&
		     (cp.magic == 0x5941FF53) &&
		     (cp.version == 3) &&
		     (cp.head == ((head) ? 1 : 0));
	return ok ? 1 : 0;
}

static void yaffs_DeviceToCheckpointDevice(yaffs_CheckpointDevice *cp, 
					   yaffs_Device *dev)
{
	cp->nErasedBlocks = dev->nErasedBlocks;
	cp->allocationBlock = dev->allocationBlock;
	cp->allocationPage = dev->allocationPage;
	cp->nFreeChunks = dev->nFreeChunks;
	
	cp->nDeletedFiles = dev->nDeletedFiles;
	cp->nUnlinkedFiles = dev->nUnlinkedFiles;
	cp->nBackgroundDeletions = dev->nBackgroundDeletions;
	cp->sequenceNumber = dev->sequenceNumber;
	cp->oldestDirtySequence = dev->oldestDirtySequence;
	
}

static void yaffs_CheckpointDeviceToDevice(yaffs_Device *dev,
					   yaffs_CheckpointDevice *cp)
{
	dev->nErasedBlocks = cp->nErasedBlocks;
	dev->allocationBlock = cp->allocationBlock;
	dev->allocationPage = cp->allocationPage;
	dev->nFreeChunks = cp->nFreeChunks;
	
	dev->nDeletedFiles = cp->nDeletedFiles;
	dev->nUnlinkedFiles = cp->nUnlinkedFiles;
	dev->nBackgroundDeletions = cp->nBackgroundDeletions;
	dev->sequenceNumber = cp->sequenceNumber;
	dev->oldestDirtySequence = cp->oldestDirtySequence;
}


static int yaffs_WriteCheckpointDevice(yaffs_Device *dev)
{
	yaffs_CheckpointDevice cp;
	__u32 nBytes;
	__u32 nBlocks = (dev->internalEndBlock - dev->internalStartBlock + 1);

	int ok;
		
	 
	yaffs_DeviceToCheckpointDevice(&cp,dev);
	cp.structType = sizeof(cp);
	
	ok = (yaffs_CheckpointWrite(dev,&cp,sizeof(cp)) == sizeof(cp));
	
	 
	if(ok) {
		nBytes = nBlocks * sizeof(yaffs_BlockInfo);
		ok = (yaffs_CheckpointWrite(dev,dev->blockInfo,nBytes) == nBytes);
	}
		
	 		
	if(ok) {
		nBytes = nBlocks * dev->chunkBitmapStride;
		ok = (yaffs_CheckpointWrite(dev,dev->chunkBits,nBytes) == nBytes);
	}
	return	 ok ? 1 : 0;

}

static int yaffs_ReadCheckpointDevice(yaffs_Device *dev)
{
	yaffs_CheckpointDevice cp;
	__u32 nBytes;
	__u32 nBlocks = (dev->internalEndBlock - dev->internalStartBlock + 1);

	int ok;	
	
	ok = (yaffs_CheckpointRead(dev,&cp,sizeof(cp)) == sizeof(cp));
	if(!ok)
		return 0;
		
	if(cp.structType != sizeof(cp))
		return 0;
		
	
	yaffs_CheckpointDeviceToDevice(dev,&cp);
	
	nBytes = nBlocks * sizeof(yaffs_BlockInfo);
	
	ok = (yaffs_CheckpointRead(dev,dev->blockInfo,nBytes) == nBytes);
	
	if(!ok)
		return 0;
	nBytes = nBlocks * dev->chunkBitmapStride;
	
	ok = (yaffs_CheckpointRead(dev,dev->chunkBits,nBytes) == nBytes);
	
	return ok ? 1 : 0;
}

static void yaffs_ObjectToCheckpointObject(yaffs_CheckpointObject *cp,
					   yaffs_Object *obj)
{

	cp->objectId = obj->objectId;
	cp->parentId = (obj->parent) ? obj->parent->objectId : 0;
	cp->hdrChunk = obj->hdrChunk;
	cp->variantType = obj->variantType;
	cp->deleted = obj->deleted;
	cp->softDeleted = obj->softDeleted;
	cp->unlinked = obj->unlinked;
	cp->fake = obj->fake;
	cp->renameAllowed = obj->renameAllowed;
	cp->unlinkAllowed = obj->unlinkAllowed;
	cp->serial = obj->serial;
	cp->nDataChunks = obj->nDataChunks;
	
	if(obj->variantType == YAFFS_OBJECT_TYPE_FILE)
		cp->fileSizeOrEquivalentObjectId = obj->variant.fileVariant.fileSize;
	else if(obj->variantType == YAFFS_OBJECT_TYPE_HARDLINK)
		cp->fileSizeOrEquivalentObjectId = obj->variant.hardLinkVariant.equivalentObjectId;
}

static int yaffs_CheckpointObjectToObject( yaffs_Object *obj,yaffs_CheckpointObject *cp)
{

	yaffs_Object *parent;

	if (obj->variantType != cp->variantType) {
		do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		return 0;
	}
	
	obj->objectId = cp->objectId;
	
	if(cp->parentId)
		parent = yaffs_FindOrCreateObjectByNumber(
					obj->myDev,
					cp->parentId,
					YAFFS_OBJECT_TYPE_DIRECTORY);
	else
		parent = 0;
		
	if(parent) {
		if (parent->variantType != YAFFS_OBJECT_TYPE_DIRECTORY) {
			do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



			return 0;
		}
		yaffs_AddObjectToDirectory(parent, obj);
	}

	obj->hdrChunk = cp->hdrChunk;
	obj->variantType = cp->variantType;
	obj->deleted = cp->deleted;
	obj->softDeleted = cp->softDeleted;
	obj->unlinked = cp->unlinked;
	obj->fake = cp->fake;
	obj->renameAllowed = cp->renameAllowed;
	obj->unlinkAllowed = cp->unlinkAllowed;
	obj->serial = cp->serial;
	obj->nDataChunks = cp->nDataChunks;
	
	if(obj->variantType == YAFFS_OBJECT_TYPE_FILE)
		obj->variant.fileVariant.fileSize = cp->fileSizeOrEquivalentObjectId;
	else if(obj->variantType == YAFFS_OBJECT_TYPE_HARDLINK)
		obj->variant.hardLinkVariant.equivalentObjectId = cp->fileSizeOrEquivalentObjectId;

	if(obj->hdrChunk > 0)
		obj->lazyLoaded = 1;
	return 1;
}



static int yaffs_CheckpointTnodeWorker(yaffs_Object * in, yaffs_Tnode * tn,
				  	__u32 level, int chunkOffset)
{
	int i;
	yaffs_Device *dev = in->myDev;
	int ok = 1;
	int tnodeSize = (dev->tnodeWidth * 16)/8;

	if(tnodeSize < sizeof(yaffs_Tnode))
		tnodeSize = sizeof(yaffs_Tnode);
	

	if (tn) {
		if (level > 0) {

			for (i = 0; i < (16 / 2) && ok; i++){
				if (tn->internal[i]) {
					ok = yaffs_CheckpointTnodeWorker(in,
							tn->internal[i],
							level - 1,
							(chunkOffset<<(4 - 1)) + i);
				}
			}
		} else if (level == 0) {
			__u32 baseOffset = chunkOffset <<  4;
			ok = (yaffs_CheckpointWrite(dev,&baseOffset,sizeof(baseOffset)) == sizeof(baseOffset));
			if(ok)
				ok = (yaffs_CheckpointWrite(dev,tn,tnodeSize) == tnodeSize);
		}
	}

	return ok;

}

static int yaffs_WriteCheckpointTnodes(yaffs_Object *obj)
{
	__u32 endMarker = ~0;
	int ok = 1;
	
	if(obj->variantType == YAFFS_OBJECT_TYPE_FILE){
		ok = yaffs_CheckpointTnodeWorker(obj,
					    obj->variant.fileVariant.top,
					    obj->variant.fileVariant.topLevel,
					    0);
		if(ok)
			ok = (yaffs_CheckpointWrite(obj->myDev,&endMarker,sizeof(endMarker)) == 
				sizeof(endMarker));
	}
	
	return ok ? 1 : 0;
}

static int yaffs_ReadCheckpointTnodes(yaffs_Object *obj)
{
	__u32 baseChunk;
	int ok = 1;
	yaffs_Device *dev = obj->myDev;
	yaffs_FileStructure *fileStructPtr = &obj->variant.fileVariant;
	yaffs_Tnode *tn;
	int nread = 0;
	int tnodeSize = (dev->tnodeWidth * 16)/8;

	if(tnodeSize < sizeof(yaffs_Tnode))
		tnodeSize = sizeof(yaffs_Tnode);

	ok = (yaffs_CheckpointRead(dev,&baseChunk,sizeof(baseChunk)) == sizeof(baseChunk));
	
	while(ok && (~baseChunk)){
		nread++;
		 
		
		
		tn = yaffs_GetTnodeRaw(dev);
		if(tn)
			ok = (yaffs_CheckpointRead(dev,tn,tnodeSize) == tnodeSize);
		else
			ok = 0;
			
		if(tn && ok){
			ok = yaffs_AddOrFindLevel0Tnode(dev,
					       		fileStructPtr,
					       		baseChunk,
					       		tn) ? 1 : 0;
					       		
		}
			
		if(ok)
			ok = (yaffs_CheckpointRead(dev,&baseChunk,sizeof(baseChunk)) == sizeof(baseChunk));
		
	}

	do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	return ok ? 1 : 0;	
}
 

static int yaffs_WriteCheckpointObjects(yaffs_Device *dev)
{
	yaffs_Object *obj;
        yaffs_CheckpointObject cp;
        int i;
        int ok = 1;
        struct ylist_head *lh;

        
        

 
         
         for(i = 0; ok &&  i <  256; i++){
                for (lh = (&dev->objectBucket[i]. list)->next; lh != (&dev->objectBucket[i]. list); lh = lh->next ) {
                        if (lh) {
                                obj = ((yaffs_Object *)((char *)(lh)-(unsigned long)(&((yaffs_Object *)0)->hashLink)));
                                if (!obj->deferedFree) {
                                        yaffs_ObjectToCheckpointObject(&cp,obj);
                                        cp.structType = sizeof(cp);

					do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



					ok = (yaffs_CheckpointWrite(dev,&cp,sizeof(cp)) == sizeof(cp));
					
					if(ok && obj->variantType == YAFFS_OBJECT_TYPE_FILE){
						ok = yaffs_WriteCheckpointTnodes(obj);
					}
				}
			}
		}
	 }
	 
	  
	memset(&cp,0xFF,sizeof(yaffs_CheckpointObject));
	cp.structType = sizeof(cp);
	
	if(ok)
		ok = (yaffs_CheckpointWrite(dev,&cp,sizeof(cp)) == sizeof(cp));
		
	return ok ? 1 : 0;
}

static int yaffs_ReadCheckpointObjects(yaffs_Device *dev)
{
	yaffs_Object *obj;
	yaffs_CheckpointObject cp;
	int ok = 1;
	int done = 0;
	yaffs_Object *hardList = 0;
	
	while(ok && !done) {
		ok = (yaffs_CheckpointRead(dev,&cp,sizeof(cp)) == sizeof(cp));
		if(cp.structType != sizeof(cp)) {
			do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			ok = 0;
		}
			
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		if(ok && cp.objectId == ~0)
			done = 1;
		else if(ok){
			obj = yaffs_FindOrCreateObjectByNumber(dev,cp.objectId, cp.variantType);
			if(obj) {
				ok = yaffs_CheckpointObjectToObject(obj,&cp);
				if (!ok)
					break;
				if(obj->variantType == YAFFS_OBJECT_TYPE_FILE) {
                                        ok = yaffs_ReadCheckpointTnodes(obj);
                                } else if(obj->variantType == YAFFS_OBJECT_TYPE_HARDLINK) {
                                        obj->hardLinks.next =
                                                    (struct ylist_head *)
                                                    hardList;
                                        hardList = obj;
                                }
			   
			}
			else
				ok = 0;
		}
	}
	
	if(ok)
		yaffs_HardlinkFixup(dev,hardList);
	
	return ok ? 1 : 0;
}

static int yaffs_WriteCheckpointSum(yaffs_Device *dev)
{
	__u32 checkpointSum;
	int ok;
	
	yaffs_GetCheckpointSum(dev,&checkpointSum);
	
	ok = (yaffs_CheckpointWrite(dev,&checkpointSum,sizeof(checkpointSum)) == sizeof(checkpointSum));
	
	if(!ok)
		return 0;
	
	return 1;
}

static int yaffs_ReadCheckpointSum(yaffs_Device *dev)
{
	__u32 checkpointSum0;
	__u32 checkpointSum1;
	int ok;
	
	yaffs_GetCheckpointSum(dev,&checkpointSum0);
	
	ok = (yaffs_CheckpointRead(dev,&checkpointSum1,sizeof(checkpointSum1)) == sizeof(checkpointSum1));
	
	if(!ok)
		return 0;
		
	if(checkpointSum0 != checkpointSum1)
		return 0;
	
	return 1;
}


static int yaffs_WriteCheckpointData(yaffs_Device *dev)
{

	int ok = 1;
	
	if(dev->skipCheckpointWrite || !dev->isYaffs2){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = 0;
	}
		
	if(ok)
		ok = yaffs_CheckpointOpen(dev,1);
	
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_WriteCheckpointValidityMarker(dev,1);
	}
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_WriteCheckpointDevice(dev);
	}
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_WriteCheckpointObjects(dev);
	}
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_WriteCheckpointValidityMarker(dev,0);
	}
	
	if(ok){
		ok = yaffs_WriteCheckpointSum(dev);
	}
	
	
	if(!yaffs_CheckpointClose(dev))
		 ok = 0;
		 
	if(ok)
	    	dev->isCheckpointed = 1;
	 else 
	 	dev->isCheckpointed = 0;

	return dev->isCheckpointed;
}

static int yaffs_ReadCheckpointData(yaffs_Device *dev)
{
	int ok = 1;

	if(dev->skipCheckpointRead || !dev->isYaffs2){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = 0;
	}
    
	if(ok)
		ok = yaffs_CheckpointOpen(dev,0);  
    
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);	
		ok = yaffs_ReadCheckpointValidityMarker(dev,1);
	}
    
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_ReadCheckpointDevice(dev);
	}
    
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);	
		ok = yaffs_ReadCheckpointObjects(dev);
	}
    
	if(ok){
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		ok = yaffs_ReadCheckpointValidityMarker(dev,0);
	}
 
	if(ok){
		ok = yaffs_ReadCheckpointSum(dev);
		do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	}
 
	if(!yaffs_CheckpointClose(dev))
		ok = 0;
 
	if(ok)
	    	dev->isCheckpointed = 1;
	 else 
	 	dev->isCheckpointed = 0;

	return ok ? 1 : 0;

}

static void yaffs_InvalidateCheckpoint(yaffs_Device *dev)
{
	if(dev->isCheckpointed || 
	   dev->blocksInCheckpoint > 0){
		dev->isCheckpointed = 0;
		yaffs_CheckpointInvalidateStream(dev);
		if(dev->superBlock && dev->markSuperBlockDirty)
			dev->markSuperBlockDirty(dev->superBlock);
	}
}


int yaffs_CheckpointSave(yaffs_Device *dev)
{

	do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	yaffs_VerifyObjects(dev);
	yaffs_VerifyBlocks(dev);
	yaffs_VerifyFreeChunks(dev);

	if(!dev->isCheckpointed) {
		yaffs_InvalidateCheckpoint(dev);
		yaffs_WriteCheckpointData(dev);
	}
	
	do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	return dev->isCheckpointed;
}

int yaffs_CheckpointRestore(yaffs_Device *dev)
{
	int retval;
	do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
                
	retval = yaffs_ReadCheckpointData(dev);
    
	if(dev->isCheckpointed){
		yaffs_VerifyObjects(dev);
		yaffs_VerifyBlocks(dev);
		yaffs_VerifyFreeChunks(dev);
	}

	do{ if((0x00008000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	
	return retval;
}









 

int yaffs_ReadDataFromFile(yaffs_Object * in, __u8 * buffer, loff_t offset,
			   int nBytes)
{

	int chunk;
	__u32 start;
	int nToCopy;
	int n = nBytes;
	int nDone = 0;
	yaffs_ChunkCache *cache;

	yaffs_Device *dev;

	dev = in->myDev;

	while (n > 0) {
		
		
		yaffs_AddrToChunk(dev,offset,&chunk,&start);
		chunk++;

		

 
		if ((start + n) < dev->nDataBytesPerChunk) {
			nToCopy = n;
		} else {
			nToCopy = dev->nDataBytesPerChunk - start;
		}

		cache = yaffs_FindChunkCache(in, chunk);

		


 
		if (cache || nToCopy != dev->nDataBytesPerChunk || dev->inbandTags) {
			if (dev->nShortOpCaches > 0) {

				 

				if (!cache) {
					cache = yaffs_GrabChunkCache(in->myDev);
					cache->object = in;
					cache->chunkId = chunk;
					cache->dirty = 0;
					cache->locked = 0;
					yaffs_ReadChunkDataFromObject(in, chunk,
								      cache->
								      data);
					cache->nBytes = 0;
				}

				yaffs_UseChunkCache(dev, cache, 0);

				cache->locked = 1;


				memcpy(buffer, &cache->data[start], nToCopy);

				cache->locked = 0;
			} else {
				 

				__u8 *localBuffer =
				    yaffs_GetTempBuffer(dev, 4845);
				yaffs_ReadChunkDataFromObject(in, chunk,
							      localBuffer);

				memcpy(buffer, &localBuffer[start], nToCopy);


				yaffs_ReleaseTempBuffer(dev, localBuffer,
							4853);
			}

		} else {

			 
			yaffs_ReadChunkDataFromObject(in, chunk, buffer);

		}

		n -= nToCopy;
		offset += nToCopy;
		buffer += nToCopy;
		nDone += nToCopy;

	}

	return nDone;
}

int yaffs_WriteDataToFile(yaffs_Object * in, const __u8 * buffer, loff_t offset,
			  int nBytes, int writeThrough)
{

	int chunk;
	__u32 start;
	int nToCopy;
        int n = nBytes;
        int nDone = 0;
        int nToWriteBack;
        int startOfWrite = offset;
        int chunkWritten = 0;
        __u32 nBytesRead;
        __u32 chunkStart;

	yaffs_Device *dev;

	dev = in->myDev;

	while (n > 0 && chunkWritten >= 0) {
		
		
		yaffs_AddrToChunk(dev,offset,&chunk,&start);
		
		if(chunk * dev->nDataBytesPerChunk + start != offset ||
		   start >= dev->nDataBytesPerChunk){
		   do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		}
		chunk++;

		

 

		if ((start + n) < dev->nDataBytesPerChunk) {
			nToCopy = n;

			


 

			chunkStart = ((chunk - 1) * dev->nDataBytesPerChunk);

			if(chunkStart > in->variant.fileVariant.fileSize)
				nBytesRead = 0;  
			else
				nBytesRead = in->variant.fileVariant.fileSize - chunkStart;

			if (nBytesRead > dev->nDataBytesPerChunk) {
				nBytesRead = dev->nDataBytesPerChunk;
			}

			nToWriteBack =
			    (nBytesRead >
			     (start + n)) ? nBytesRead : (start + n);
			
			if(nToWriteBack < 0 || nToWriteBack > dev->nDataBytesPerChunk)
				;

		} else {
			nToCopy = dev->nDataBytesPerChunk - start;
			nToWriteBack = dev->nDataBytesPerChunk;
		}

		if (nToCopy != dev->nDataBytesPerChunk || dev->inbandTags) {
			

 
			if (dev->nShortOpCaches > 0) {
				yaffs_ChunkCache *cache;
				 
				cache = yaffs_FindChunkCache(in, chunk);
				
				if (!cache
				    && yaffs_CheckSpaceForAllocation(in->
								     myDev)) {
					cache = yaffs_GrabChunkCache(in->myDev);
					cache->object = in;
					cache->chunkId = chunk;
					cache->dirty = 0;
					cache->locked = 0;
					yaffs_ReadChunkDataFromObject(in, chunk,
								      cache->
								      data);
				}
				else if(cache && 
				        !cache->dirty &&
					!yaffs_CheckSpaceForAllocation(in->myDev)){
					

  
					 cache = 0;
				}

				if (cache) {
					yaffs_UseChunkCache(dev, cache, 1);
					cache->locked = 1;


					memcpy(&cache->data[start], buffer,
					       nToCopy);


					cache->locked = 0;
					cache->nBytes = nToWriteBack;

					if (writeThrough) {
						chunkWritten =
						    yaffs_WriteChunkDataToObject
						    (cache->object,
						     cache->chunkId,
						     cache->data, cache->nBytes,
						     1);
						cache->dirty = 0;
					}

				} else {
					chunkWritten = -1;	 
				}
			} else {
				

 

				__u8 *localBuffer =
				    yaffs_GetTempBuffer(dev, 5002);

				yaffs_ReadChunkDataFromObject(in, chunk,
							      localBuffer);



				memcpy(&localBuffer[start], buffer, nToCopy);

				chunkWritten =
				    yaffs_WriteChunkDataToObject(in, chunk,
								 localBuffer,
								 nToWriteBack,
								 0);

				yaffs_ReleaseTempBuffer(dev, localBuffer,
							5018);

			}

		} else {
			 
			


			chunkWritten =
			    yaffs_WriteChunkDataToObject(in, chunk, buffer,
							 dev->nDataBytesPerChunk,
							 0);

			 
			yaffs_InvalidateChunkCache(in, chunk);
		}

		if (chunkWritten >= 0) {
			n -= nToCopy;
			offset += nToCopy;
			buffer += nToCopy;
			nDone += nToCopy;
		}

	}

	 

	if ((startOfWrite + nDone) > in->variant.fileVariant.fileSize) {
		in->variant.fileVariant.fileSize = (startOfWrite + nDone);
	}

	in->dirty = 1;

	return nDone;
}


 

static void yaffs_PruneResizedChunks(yaffs_Object * in, int newSize)
{

	yaffs_Device *dev = in->myDev;
	int oldFileSize = in->variant.fileVariant.fileSize;

	int lastDel = 1 + (oldFileSize - 1) / dev->nDataBytesPerChunk;

	int startDel = 1 + (newSize + dev->nDataBytesPerChunk - 1) /
	    dev->nDataBytesPerChunk;
	int i;
	int chunkId;

	

 
	for (i = lastDel; i >= startDel; i--) {
		


 

		chunkId = yaffs_FindAndDeleteChunkInFile(in, i, 0);
		if (chunkId > 0) {
			if (chunkId <
			    (dev->internalStartBlock * dev->nChunksPerBlock)
			    || chunkId >=
			    ((dev->internalEndBlock +
			      1) * dev->nChunksPerBlock)) {
				do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


			} else {
				in->nDataChunks--;
				yaffs_DeleteChunk(dev, chunkId, 1, 5093);
			}
		}
	}

}

int yaffs_ResizeFile(yaffs_Object * in, loff_t newSize)
{

	int oldFileSize = in->variant.fileVariant.fileSize;
	__u32 newSizeOfPartialChunk;
	int newFullChunks;
	
	yaffs_Device *dev = in->myDev;

	yaffs_AddrToChunk(dev, newSize, &newFullChunks, &newSizeOfPartialChunk);

	yaffs_FlushFilesChunkCache(in);
	yaffs_InvalidateWholeChunkCache(in);

        yaffs_CheckGarbageCollection(dev);

        if (in->variantType != YAFFS_OBJECT_TYPE_FILE) {
                return 0;
        }

        if (newSize == oldFileSize) {
                return 1;
        }

        if (newSize < oldFileSize) {

		yaffs_PruneResizedChunks(in, newSize);

		if (newSizeOfPartialChunk != 0) {
			int lastChunk = 1 + newFullChunks;
			
			__u8 *localBuffer = yaffs_GetTempBuffer(dev, 5131);

			 
			yaffs_ReadChunkDataFromObject(in, lastChunk,
						      localBuffer);

			memset(localBuffer + newSizeOfPartialChunk, 0,
			       dev->nDataBytesPerChunk - newSizeOfPartialChunk);

			yaffs_WriteChunkDataToObject(in, lastChunk, localBuffer,
						     newSizeOfPartialChunk, 1);

			yaffs_ReleaseTempBuffer(dev, localBuffer, 5143);
		}

		in->variant.fileVariant.fileSize = newSize;

		yaffs_PruneFileStructure(dev, &in->variant.fileVariant);
	} else {
		 
		in->variant.fileVariant.fileSize = newSize;
	}

		
	
	


 
	if (in->parent &&
	    in->parent->objectId != 3 &&
	    in->parent->objectId != 4) {
		yaffs_UpdateObjectHeader(in, 0, 0,
					 (newSize < oldFileSize) ? 1 : 0, 0);
	}

	return 1;
}

loff_t yaffs_GetFileSize(yaffs_Object * obj)
{
	obj = yaffs_GetEquivalentObject(obj);

	switch (obj->variantType) {
	case YAFFS_OBJECT_TYPE_FILE:
		return obj->variant.fileVariant.fileSize;
	case YAFFS_OBJECT_TYPE_SYMLINK:
		return strlen(obj->variant . symLinkVariant . alias);
	default:
		return 0;
	}
}



int yaffs_FlushFile(yaffs_Object * in, int updateTime)
{
	int retVal;
	if (in->dirty) {
		yaffs_FlushFilesChunkCache(in);
		if (updateTime) {




			in->yst_mtime = yaffsfs_CurrentTime();


		}

		retVal =
		    (yaffs_UpdateObjectHeader(in, 0, 0, 0, 0) >=
		     0) ? 1 : 0;
	} else {
		retVal = 1;
	}

	return retVal;

}

static int yaffs_DoGenericObjectDeletion(yaffs_Object * in)
{

	 
	yaffs_InvalidateWholeChunkCache(in);

	if (in->myDev->isYaffs2 && (in->parent != in->myDev->deletedDir)) {
		 
		yaffs_ChangeObjectName(in, in->myDev->deletedDir,"deleted", 0, 0);

	}

	yaffs_RemoveObjectFromDirectory(in);
	yaffs_DeleteChunk(in->myDev, in->hdrChunk, 1, 5225);
	in->hdrChunk = 0;

	yaffs_FreeObject(in);
	return 1;

}




 
static int yaffs_UnlinkFile(yaffs_Object * in)
{

	int retVal;
	int immediateDeletion = 0;






	if (in->inUse <= 0) {
		immediateDeletion = 1;
	}


	if (immediateDeletion) {
		retVal =
		    yaffs_ChangeObjectName(in, in->myDev->deletedDir,
					   "deleted", 0, 0);
		do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		in->deleted = 1;
		in->myDev->nDeletedFiles++;
		if (1 || in->myDev->isYaffs2) {
			yaffs_ResizeFile(in, 0);
		}
		yaffs_SoftDeleteFile(in);
	} else {
		retVal =
		    yaffs_ChangeObjectName(in, in->myDev->unlinkedDir,
					   "unlinked", 0, 0);
	}


	return retVal;
}

int yaffs_DeleteFile(yaffs_Object * in)
{
	int retVal = 1;
	int deleted = in->deleted;
	
	yaffs_ResizeFile(in,0);

	if (in->nDataChunks > 0) {
		

 
		if (!in->unlinked) {
			retVal = yaffs_UnlinkFile(in);
		}
		if (retVal == 1 && in->unlinked && !in->deleted) {
			in->deleted = deleted = 1;
			in->myDev->nDeletedFiles++;
			yaffs_SoftDeleteFile(in);
		}
		return deleted ? 1 : 0;
	} else {
		 
		yaffs_FreeTnode(in->myDev, in->variant.fileVariant.top);
		in->variant.fileVariant.top = 0;
		yaffs_DoGenericObjectDeletion(in);

		return 1;
	}
}

static int yaffs_DeleteDirectory(yaffs_Object * in)
{
         
        if (ylist_empty(&in->variant.directoryVariant.children)) {
                return yaffs_DoGenericObjectDeletion(in);
        }

	return 0;

}

static int yaffs_DeleteSymLink(yaffs_Object * in)
{
	free(in->variant . symLinkVariant . alias);

	return yaffs_DoGenericObjectDeletion(in);
}

static int yaffs_DeleteHardLink(yaffs_Object * in)
{
        

 
        ylist_del_init(&in->hardLinks);
        return yaffs_DoGenericObjectDeletion(in);
}

static void yaffs_DestroyObject(yaffs_Object * obj)
{
	switch (obj->variantType) {
	case YAFFS_OBJECT_TYPE_FILE:
		yaffs_DeleteFile(obj);
		break;
	case YAFFS_OBJECT_TYPE_DIRECTORY:
		yaffs_DeleteDirectory(obj);
		break;
	case YAFFS_OBJECT_TYPE_SYMLINK:
		yaffs_DeleteSymLink(obj);
		break;
	case YAFFS_OBJECT_TYPE_HARDLINK:
		yaffs_DeleteHardLink(obj);
		break;
	case YAFFS_OBJECT_TYPE_SPECIAL:
		yaffs_DoGenericObjectDeletion(obj);
		break;
	case YAFFS_OBJECT_TYPE_UNKNOWN:
		break;		 
	}
}

static int yaffs_UnlinkWorker(yaffs_Object * obj)
{

        if (obj->variantType == YAFFS_OBJECT_TYPE_HARDLINK) {
                return yaffs_DeleteHardLink(obj);
        } else if (!ylist_empty(&obj->hardLinks)) {
                











 

		yaffs_Object *hl;
                int retVal;
                char name[255 + 1];

                hl = ((yaffs_Object *)((char *)(obj->hardLinks . next)-(unsigned long)(&((yaffs_Object *)0)->hardLinks)));

                ylist_del_init(&hl->hardLinks);
                ylist_del_init(&hl->siblings);

                yaffs_GetObjectName(hl, name, 255 + 1);

		retVal = yaffs_ChangeObjectName(obj, hl->parent, name, 0, 0);

		if (retVal == 1) {
			retVal = yaffs_DoGenericObjectDeletion(hl);
		}
		return retVal;

	} else {
		switch (obj->variantType) {
		case YAFFS_OBJECT_TYPE_FILE:
			return yaffs_UnlinkFile(obj);
			break;
		case YAFFS_OBJECT_TYPE_DIRECTORY:
			return yaffs_DeleteDirectory(obj);
			break;
		case YAFFS_OBJECT_TYPE_SYMLINK:
			return yaffs_DeleteSymLink(obj);
			break;
		case YAFFS_OBJECT_TYPE_SPECIAL:
			return yaffs_DoGenericObjectDeletion(obj);
			break;
		case YAFFS_OBJECT_TYPE_HARDLINK:
		case YAFFS_OBJECT_TYPE_UNKNOWN:
		default:
			return 0;
		}
	}
}


static int yaffs_UnlinkObject( yaffs_Object *obj)
{

	if (obj && obj->unlinkAllowed) {
		return yaffs_UnlinkWorker(obj);
	}

	return 0;

}
int yaffs_Unlink(yaffs_Object * dir, const char * name)
{
	yaffs_Object *obj;

	obj = yaffs_FindObjectByName(dir, name);
	return yaffs_UnlinkObject(obj);
}

 

static void yaffs_HandleShadowedObject(yaffs_Device * dev, int objId,
				       int backwardScanning)
{
	yaffs_Object *obj;

	if (!backwardScanning) {
		

 

	} else {
		

 
		if (yaffs_FindObjectByNumber(dev, objId)) {
			return;
		}
	}

	

 
	obj =
	    yaffs_FindOrCreateObjectByNumber(dev, objId,
					     YAFFS_OBJECT_TYPE_FILE);
	if (!obj)
		return;
	yaffs_AddObjectToDirectory(dev->unlinkedDir, obj);
	obj->variant.fileVariant.shrinkSize = 0;
	obj->valid = 1;		 

}

typedef struct {
	int seq;
	int block;
} yaffs_BlockIndex;


static void yaffs_HardlinkFixup(yaffs_Device *dev, yaffs_Object *hardList)
{
	yaffs_Object *hl;
	yaffs_Object *in;
	
	while (hardList) {
		hl = hardList;
		hardList = (yaffs_Object *) (hardList->hardLinks.next);

		in = yaffs_FindObjectByNumber(dev,
					      hl->variant.hardLinkVariant.
					      equivalentObjectId);

                if (in) {
                         
                        hl->variant.hardLinkVariant.equivalentObject = in;
                        ylist_add(&hl->hardLinks, &in->hardLinks);
                } else {
                        

 
                        hl->variant.hardLinkVariant.equivalentObject = 0;
                        do { (&hl->hardLinks)->next = (&hl->hardLinks); (&hl->hardLinks)->prev = (&hl->hardLinks); } while(0);

                }

	}

}





static int ybicmp(const void *a, const void *b){
    register int aseq = ((yaffs_BlockIndex *)a)->seq;
    register int bseq = ((yaffs_BlockIndex *)b)->seq;
    register int ablock = ((yaffs_BlockIndex *)a)->block;
    register int bblock = ((yaffs_BlockIndex *)b)->block;
    if( aseq == bseq )
        return ablock - bblock;
    else
        return aseq - bseq;

}


struct yaffs_ShadowFixerStruct {
	int objectId;
	int shadowedId;
	struct yaffs_ShadowFixerStruct *next;
};


static void yaffs_StripDeletedObjects(yaffs_Device *dev)
{
	

 
	struct ylist_head *i;
	struct ylist_head *n;
	yaffs_Object *l;

	 
	for (i = (&dev->unlinkedDir->variant . directoryVariant . children)->next, n = (&dev->unlinkedDir->variant . directoryVariant . children)->next->next; i != (&dev->unlinkedDir->variant . directoryVariant . children); i = n, n = n->next) {

		if (i) {
			l = ((yaffs_Object *)((char *)(i)-(unsigned long)(&((yaffs_Object *)0)->siblings)));
			yaffs_DestroyObject(l);
		}
	}
	
	for (i = (&dev->deletedDir->variant . directoryVariant . children)->next, n = (&dev->deletedDir->variant . directoryVariant . children)->next->next; i != (&dev->deletedDir->variant . directoryVariant . children); i = n, n = n->next) {

		if (i) {
			l = ((yaffs_Object *)((char *)(i)-(unsigned long)(&((yaffs_Object *)0)->siblings)));
			yaffs_DestroyObject(l);
		}
	}

}

static int yaffs_Scan(yaffs_Device * dev)
{
	yaffs_ExtendedTags tags;
	int blk;
	int blockIterator;
	int startIterator;
	int endIterator;
	int result;

	int chunk;
	int c;
	int deleted;
	yaffs_BlockState state;
	yaffs_Object *hardList = 0;
	yaffs_BlockInfo *bi;
	__u32 sequenceNumber;
	yaffs_ObjectHeader *oh;
	yaffs_Object *in;
	yaffs_Object *parent;
	
	int alloc_failed = 0;
	
	struct yaffs_ShadowFixerStruct *shadowFixerList = 0;
	

	__u8 *chunkData;

	
	
	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



	chunkData = yaffs_GetTempBuffer(dev, 5591);

	dev->sequenceNumber = 0x00001000;

	 
	for (blk = dev->internalStartBlock; blk <= dev->internalEndBlock; blk++) {
		bi = yaffs_GetBlockInfo(dev, blk);
		yaffs_ClearChunkBits(dev, blk);
		bi->pagesInUse = 0;
		bi->softDeletions = 0;

		yaffs_QueryInitialBlockState(dev, blk, &state, &sequenceNumber);

		bi->blockState = state;
		bi->sequenceNumber = sequenceNumber;

		if(bi->sequenceNumber == 0xFFFF0000)
			bi->blockState = state = YAFFS_BLOCK_STATE_DEAD;

		do{ if((0x00002000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		if (state == YAFFS_BLOCK_STATE_DEAD) {
			do{ if((0x00000010) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		} else if (state == YAFFS_BLOCK_STATE_EMPTY) {
			do{ if((0x00002000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			dev->nErasedBlocks++;
			dev->nFreeChunks += dev->nChunksPerBlock;
		} 
	}

	startIterator = dev->internalStartBlock;
	endIterator = dev->internalEndBlock;

	 
	for (blockIterator = startIterator; !alloc_failed && blockIterator <= endIterator;
	     blockIterator++) {
		
		do {} while(0);

	     	do {} while(0);
	     	
		blk = blockIterator;

		bi = yaffs_GetBlockInfo(dev, blk);
		state = bi->blockState;

		deleted = 0;

		 
		for (c = 0; !alloc_failed && c < dev->nChunksPerBlock &&
		     state == YAFFS_BLOCK_STATE_NEEDS_SCANNING; c++) {
			 
			chunk = blk * dev->nChunksPerBlock + c;

			result = yaffs_ReadChunkWithTagsFromNAND(dev, chunk, 0,
							&tags);

			 

			if (tags.eccResult == YAFFS_ECC_RESULT_UNFIXED || tags.chunkDeleted) {
				

 
				deleted++;
				dev->nFreeChunks++;
				 
			} else if (!tags.chunkUsed) {
				


 

				if (c == 0) {
					 
					state = YAFFS_BLOCK_STATE_EMPTY;
					dev->nErasedBlocks++;
				} else {
					 
					do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



					state = YAFFS_BLOCK_STATE_ALLOCATING;
					dev->allocationBlock = blk;
					dev->allocationPage = c;
					dev->allocationBlockFinder = blk;	
					 
					
				}

				dev->nFreeChunks += (dev->nChunksPerBlock - c);
			} else if (tags.chunkId > 0) {
				 
				unsigned int endpos;

				yaffs_SetChunkBit(dev, blk, c);
				bi->pagesInUse++;

				in = yaffs_FindOrCreateObjectByNumber(dev,
								      tags.
								      objectId,
								      YAFFS_OBJECT_TYPE_FILE);
				

 
				 
				if(!in)
					alloc_failed = 1;

				if(in){
					if(!yaffs_PutChunkIntoFile(in, tags.chunkId, chunk,1))
						alloc_failed = 1;
				}
				
				endpos =
				    (tags.chunkId - 1) * dev->nDataBytesPerChunk +
				    tags.byteCount;
				if (in && 
				    in->variantType == YAFFS_OBJECT_TYPE_FILE
				    && in->variant.fileVariant.scannedFileSize <
				    endpos) {
					in->variant.fileVariant.
					    scannedFileSize = endpos;
					if (!dev->useHeaderFileSize) {
						in->variant.fileVariant.
						    fileSize =
						    in->variant.fileVariant.
						    scannedFileSize;
					}

				}
				 
			} else {
				

 
				yaffs_SetChunkBit(dev, blk, c);
				bi->pagesInUse++;

				result = yaffs_ReadChunkWithTagsFromNAND(dev, chunk,
								chunkData,
								0);

				oh = (yaffs_ObjectHeader *) chunkData;

				in = yaffs_FindObjectByNumber(dev,
							      tags.objectId);
				if (in && in->variantType != oh->type) {
					


 

					yaffs_DestroyObject(in);

					in = 0;
				}

				in = yaffs_FindOrCreateObjectByNumber(dev,
								      tags.
								      objectId,
								      oh->type);

				if(!in)
					alloc_failed = 1;
					
				if (in && oh->shadowsObject > 0) {
				
					struct yaffs_ShadowFixerStruct *fixer;
					fixer = yaffs_malloc(sizeof(struct yaffs_ShadowFixerStruct));
					if(fixer){
						fixer-> next = shadowFixerList;
						shadowFixerList = fixer;
						fixer->objectId = tags.objectId;
						fixer->shadowedId = oh->shadowsObject;
					}
					
				}

				if (in && in->valid) {
					 

					unsigned existingSerial = in->serial;
					unsigned newSerial = tags.serialNumber;

					if (((existingSerial + 1) & 3) == newSerial) {
						 
						yaffs_DeleteChunk(dev,
								  in->hdrChunk,
								  1, 5784);
						in->valid = 0;
					} else {
						 
						yaffs_DeleteChunk(dev, chunk, 1,
								  5789);
					}
				}

				if (in && !in->valid &&
				    (tags.objectId == 1 ||
				     tags.objectId == 2)) {
					 
					in->valid = 1;
					in->variantType = oh->type;

					in->yst_mode = oh->yst_mode;
#line 5809 "..\\fs\\yaffs_guts.c"
					in->yst_uid = oh->yst_uid;
					in->yst_gid = oh->yst_gid;
					in->yst_atime = oh->yst_atime;
					in->yst_mtime = oh->yst_mtime;
					in->yst_ctime = oh->yst_ctime;
					in->yst_rdev = oh->yst_rdev;

					in->hdrChunk = chunk;
					in->serial = tags.serialNumber;

				} else if (in && !in->valid) {
					 

					in->valid = 1;
					in->variantType = oh->type;

					in->yst_mode = oh->yst_mode;
#line 5834 "..\\fs\\yaffs_guts.c"
					in->yst_uid = oh->yst_uid;
					in->yst_gid = oh->yst_gid;
					in->yst_atime = oh->yst_atime;
					in->yst_mtime = oh->yst_mtime;
					in->yst_ctime = oh->yst_ctime;
					in->yst_rdev = oh->yst_rdev;

					in->hdrChunk = chunk;
					in->serial = tags.serialNumber;

					yaffs_SetObjectName(in, oh->name);
					in->dirty = 0;

					

 

					parent =
					    yaffs_FindOrCreateObjectByNumber
					    (dev, oh->parentObjectId,
					     YAFFS_OBJECT_TYPE_DIRECTORY);
					if(!parent)
						alloc_failed = 1;
					if (parent && parent->variantType ==
					    YAFFS_OBJECT_TYPE_UNKNOWN) {
                                                 
                                                parent->variantType =
                                                    YAFFS_OBJECT_TYPE_DIRECTORY;
                                                do { (&parent->variant . directoryVariant . children)->next = (&parent->variant . directoryVariant . children); (&parent->variant . directoryVariant . children)->prev = (&parent->variant . directoryVariant . children); } while(0);


                                        } else if (!parent || parent->variantType !=
						   YAFFS_OBJECT_TYPE_DIRECTORY)
					{
						

 

						do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



						parent = dev->lostNFoundDir;
					}

					yaffs_AddObjectToDirectory(parent, in);

					if (0 && (parent == dev->deletedDir ||
						  parent == dev->unlinkedDir)) {
						in->deleted = 1;	 
						dev->nDeletedFiles++;
					}
					




 

					switch (in->variantType) {
					case YAFFS_OBJECT_TYPE_UNKNOWN:	
						 
						break;
					case YAFFS_OBJECT_TYPE_FILE:
						if (dev->useHeaderFileSize)

							in->variant.fileVariant.
							    fileSize =
							    oh->fileSize;

						break;
					case YAFFS_OBJECT_TYPE_HARDLINK:
						in->variant.hardLinkVariant.
                                                    equivalentObjectId =
                                                    oh->equivalentObjectId;
                                                in->hardLinks.next =
                                                    (struct ylist_head *)
                                                    hardList;
                                                hardList = in;
                                                break;
					case YAFFS_OBJECT_TYPE_DIRECTORY:
						 
						break;
					case YAFFS_OBJECT_TYPE_SPECIAL:
						 
						break;
					case YAFFS_OBJECT_TYPE_SYMLINK:	
						in->variant.symLinkVariant.alias =
						    yaffs_CloneString(oh->alias);
						if(!in->variant.symLinkVariant.alias)
							alloc_failed = 1;
						break;
					}






 
				}
			}
		}

		if (state == YAFFS_BLOCK_STATE_NEEDS_SCANNING) {
			 
			state = YAFFS_BLOCK_STATE_FULL;
		}

		bi->blockState = state;

		 
		if (bi->pagesInUse == 0 &&
		    !bi->hasShrinkHeader &&
		    bi->blockState == YAFFS_BLOCK_STATE_FULL) {
			yaffs_BlockBecameDirty(dev, blk);
		}

	}

	
	



 

	yaffs_HardlinkFixup(dev,hardList);
	
	 
	{
		struct yaffs_ShadowFixerStruct *fixer;
		yaffs_Object *obj;
		
		while(shadowFixerList){
			fixer = shadowFixerList;
			shadowFixerList = fixer->next;
			

 
			obj = yaffs_FindObjectByNumber(dev,fixer->shadowedId);
			if(obj)
				yaffs_DestroyObject(obj);
	
			obj = yaffs_FindObjectByNumber(dev,fixer->objectId);
			if(obj){
				yaffs_UpdateObjectHeader(obj,0,1,0,0);
			}
			
			free(fixer);
		}
	}

	yaffs_ReleaseTempBuffer(dev, chunkData, 5987);

	if(alloc_failed){
		return 0;
	}
	
	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
	

	return 1;
}

static void yaffs_CheckObjectDetailsLoaded(yaffs_Object *in)
{
	__u8 *chunkData;
	yaffs_ObjectHeader *oh;
	yaffs_Device *dev;
	yaffs_ExtendedTags tags;
	int result;
	int alloc_failed = 0;

	if(!in)
		return;
		
	dev = in->myDev;
		






	if(in->lazyLoaded && in->hdrChunk > 0){
		in->lazyLoaded = 0;
		chunkData = yaffs_GetTempBuffer(dev, 6021);

		result = yaffs_ReadChunkWithTagsFromNAND(dev,in->hdrChunk,chunkData,&tags);
		oh = (yaffs_ObjectHeader *) chunkData;

		in->yst_mode = oh->yst_mode;
#line 6035 "..\\fs\\yaffs_guts.c"
		in->yst_uid = oh->yst_uid;
		in->yst_gid = oh->yst_gid;
		in->yst_atime = oh->yst_atime;
		in->yst_mtime = oh->yst_mtime;
		in->yst_ctime = oh->yst_ctime;
		in->yst_rdev = oh->yst_rdev;
		

		yaffs_SetObjectName(in, oh->name);
		
		if(in->variantType == YAFFS_OBJECT_TYPE_SYMLINK){
			 in->variant.symLinkVariant.alias =
						    yaffs_CloneString(oh->alias);
			if(!in->variant.symLinkVariant.alias)
				alloc_failed = 1;  
		}
						    
		yaffs_ReleaseTempBuffer(dev,chunkData, 6052);
	}
}

static int yaffs_ScanBackwards(yaffs_Device * dev)
{
	yaffs_ExtendedTags tags;
	int blk;
	int blockIterator;
	int startIterator;
	int endIterator;
	int nBlocksToScan = 0;

	int chunk;
	int result;
	int c;
	int deleted;
	yaffs_BlockState state;
	yaffs_Object *hardList = 0;
	yaffs_BlockInfo *bi;
	__u32 sequenceNumber;
	yaffs_ObjectHeader *oh;
	yaffs_Object *in;
	yaffs_Object *parent;
	int nBlocks = dev->internalEndBlock - dev->internalStartBlock + 1;
	int itsUnlinked;
	__u8 *chunkData;
	
	int fileSize;
	int isShrink;
	int foundChunksInBlock;
	int equivalentObjectId;
	int alloc_failed = 0;
	

	yaffs_BlockIndex *blockIndex = 0;
	int altBlockIndex = 0;

	if (!dev->isYaffs2) {
		do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}

	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);





	dev->sequenceNumber = 0x00001000;

	blockIndex = yaffs_malloc(nBlocks * sizeof(yaffs_BlockIndex));
	
	if(!blockIndex) {
		blockIndex = yaffs_malloc(nBlocks * sizeof(yaffs_BlockIndex));
		altBlockIndex = 1;
	}
	
	if(!blockIndex) {
		do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}
	
	dev->blocksInCheckpoint = 0;
	
	chunkData = yaffs_GetTempBuffer(dev, 6119);

	 
	for (blk = dev->internalStartBlock; blk <= dev->internalEndBlock; blk++) {
		bi = yaffs_GetBlockInfo(dev, blk);
		yaffs_ClearChunkBits(dev, blk);
		bi->pagesInUse = 0;
		bi->softDeletions = 0;

		yaffs_QueryInitialBlockState(dev, blk, &state, &sequenceNumber);

		bi->blockState = state;
		bi->sequenceNumber = sequenceNumber;

		if(bi->sequenceNumber == 0x21)
			bi->blockState = state = YAFFS_BLOCK_STATE_CHECKPOINT;
		if(bi->sequenceNumber == 0xFFFF0000)
			bi->blockState = state = YAFFS_BLOCK_STATE_DEAD;
			
		do{ if((0x00002000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		
		if(state == YAFFS_BLOCK_STATE_CHECKPOINT){
			dev->blocksInCheckpoint++;
			
		} else if (state == YAFFS_BLOCK_STATE_DEAD) {
			do{ if((0x00000010) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		} else if (state == YAFFS_BLOCK_STATE_EMPTY) {
			do{ if((0x00002000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			dev->nErasedBlocks++;
			dev->nFreeChunks += dev->nChunksPerBlock;
		} else if (state == YAFFS_BLOCK_STATE_NEEDS_SCANNING) {

			 
			if (sequenceNumber >= 0x00001000 &&
			    sequenceNumber < 0xEFFFFF00) {

				blockIndex[nBlocksToScan].seq = sequenceNumber;
				blockIndex[nBlocksToScan].block = blk;

				nBlocksToScan++;

				if (sequenceNumber >= dev->sequenceNumber) {
					dev->sequenceNumber = sequenceNumber;
				}
			} else {
				 
				do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




			}
		}
	}

	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




	do {} while(0);

	 

	{
		 
		yaffs_qsort(blockIndex, nBlocksToScan, sizeof(yaffs_BlockIndex), ybicmp);
	}
#line 6209 "..\\fs\\yaffs_guts.c"

	do {} while(0);

    	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	 
	startIterator = 0;
	endIterator = nBlocksToScan - 1;
	do{ if((0x00002000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


	 
	for (blockIterator = endIterator; !alloc_failed && blockIterator >= startIterator;
	     blockIterator--) {
	        
 
	        do {} while(0);

		 
		blk = blockIndex[blockIterator].block;

		bi = yaffs_GetBlockInfo(dev, blk);
		
		
		state = bi->blockState;

		deleted = 0;

		 
		foundChunksInBlock = 0;
		for (c = dev->nChunksPerBlock - 1; 
		     !alloc_failed && c >= 0 &&
		     (state == YAFFS_BLOCK_STATE_NEEDS_SCANNING ||
		      state == YAFFS_BLOCK_STATE_ALLOCATING); c--) {
			

 
			
			chunk = blk * dev->nChunksPerBlock + c;

			result = yaffs_ReadChunkWithTagsFromNAND(dev, chunk, 0,
							&tags);

			 

			if (!tags.chunkUsed) {
				






 

				if(foundChunksInBlock)
				{
					 
					
				} else if (c == 0) {
					 
					state = YAFFS_BLOCK_STATE_EMPTY;
					dev->nErasedBlocks++;
				} else {
					if (state == YAFFS_BLOCK_STATE_NEEDS_SCANNING ||
					    state == YAFFS_BLOCK_STATE_ALLOCATING) {
					    	if(dev->sequenceNumber == bi->sequenceNumber) {
							 
					    	
							do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);




							state = YAFFS_BLOCK_STATE_ALLOCATING;
							dev->allocationBlock = blk;
							dev->allocationPage = c;
							dev->allocationBlockFinder = blk;	
						}
						else {
							


 
						  
							  
							 bi->gcPrioritise = 1;
							 						 
							 do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


						}

					}
					 
				}

				dev->nFreeChunks++;
				
			} else if (tags.eccResult == YAFFS_ECC_RESULT_UNFIXED){
				do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



				  dev->nFreeChunks++;

			}else if (tags.chunkId > 0) {
				 
				unsigned int endpos;
				__u32 chunkBase =
				    (tags.chunkId - 1) * dev->nDataBytesPerChunk;
								
				foundChunksInBlock = 1;


				yaffs_SetChunkBit(dev, blk, c);
				bi->pagesInUse++;

				in = yaffs_FindOrCreateObjectByNumber(dev,
								      tags.
								      objectId,
								      YAFFS_OBJECT_TYPE_FILE);
				if(!in){
					 
					alloc_failed = 1;
				}
				
				if (in &&
				    in->variantType == YAFFS_OBJECT_TYPE_FILE
				    && chunkBase <
				    in->variant.fileVariant.shrinkSize) {
					 
					if(!yaffs_PutChunkIntoFile(in, tags.chunkId,
							       chunk, -1)){
						alloc_failed = 1;
					}

					

 
					endpos =
					    (tags.chunkId -
					     1) * dev->nDataBytesPerChunk +
					    tags.byteCount;
					    
					if (!in->valid &&	 
					    in->variant.fileVariant.
					    scannedFileSize < endpos) {
						in->variant.fileVariant.
						    scannedFileSize = endpos;
						in->variant.fileVariant.
						    fileSize =
						    in->variant.fileVariant.
						    scannedFileSize;
					}

				} else if(in) {
					 
					yaffs_DeleteChunk(dev, chunk, 1, 6367);

				}
			} else {
				

 
				foundChunksInBlock = 1;

				yaffs_SetChunkBit(dev, blk, c);
				bi->pagesInUse++;

				oh = 0;
				in = 0;

				if (tags.extraHeaderInfoAvailable) {
					in = yaffs_FindOrCreateObjectByNumber
					    (dev, tags.objectId,
					     tags.extraObjectType);
					if (!in)
						alloc_failed = 1;
				}

				if (!in ||



				    tags.extraShadows ||
				    (!in->valid &&
				    (tags.objectId == 1 ||
				     tags.objectId == 2))
				    ) {

					


 

					result = yaffs_ReadChunkWithTagsFromNAND(dev,
									chunk,
									chunkData,
									0);

					oh = (yaffs_ObjectHeader *) chunkData;
					
					if(dev->inbandTags){
						 
						oh->shadowsObject = oh->inbandShadowsObject;
						oh->isShrink = oh->inbandIsShrink;
					}

					if (!in) {
						in = yaffs_FindOrCreateObjectByNumber(dev, tags.objectId, oh->type);
						if (!in)
							alloc_failed = 1;
					}

				}

				if (!in) {
					 
					do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



					continue;
				}

				if (in->valid) {
					


 

					if ((in->variantType == YAFFS_OBJECT_TYPE_FILE) && 
					     ((oh && 
					       oh-> type == YAFFS_OBJECT_TYPE_FILE)||
					      (tags.extraHeaderInfoAvailable  &&
					       tags.extraObjectType == YAFFS_OBJECT_TYPE_FILE))
					    ) {
						__u32 thisSize =
						    (oh) ? oh->fileSize : tags.
						    extraFileLength;
						__u32 parentObjectId =
						    (oh) ? oh->
						    parentObjectId : tags.
						    extraParentObjectId;
						
						
						isShrink =
						    (oh) ? oh->isShrink : tags.
						    extraIsShrinkHeader;

						

 
						if (parentObjectId ==
						    4
						    || parentObjectId ==
						    3) {
							thisSize = 0;
							isShrink = 1;
						}

						if (isShrink &&
						    in->variant.fileVariant.
						    shrinkSize > thisSize) {
							in->variant.fileVariant.
							    shrinkSize =
							    thisSize;
						}

						if (isShrink) {
							bi->hasShrinkHeader = 1;
						}

					}
					 
					yaffs_DeleteChunk(dev, chunk, 1, 6485);

				}

				if (!in->valid && in->variantType !=
				    (oh ? oh->type : tags.extraObjectType))
					do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
#line 6499 "..\\fs\\yaffs_guts.c"

				if (!in->valid &&
				    (tags.objectId == 1 ||
				     tags.objectId ==
				     2)) {
					 
					in->valid = 1;
					
					if(oh) {
						in->variantType = oh->type;

						in->yst_mode = oh->yst_mode;
#line 6519 "..\\fs\\yaffs_guts.c"
						in->yst_uid = oh->yst_uid;
						in->yst_gid = oh->yst_gid;
						in->yst_atime = oh->yst_atime;
						in->yst_mtime = oh->yst_mtime;
						in->yst_ctime = oh->yst_ctime;
						in->yst_rdev = oh->yst_rdev;
		

					} else {
						in->variantType = tags.extraObjectType;
						in->lazyLoaded = 1;
					}

					in->hdrChunk = chunk;

				} else if (!in->valid) {
					 

					in->valid = 1;
					in->hdrChunk = chunk;

					if(oh) {
						in->variantType = oh->type;

						in->yst_mode = oh->yst_mode;
#line 6552 "..\\fs\\yaffs_guts.c"
						in->yst_uid = oh->yst_uid;
						in->yst_gid = oh->yst_gid;
						in->yst_atime = oh->yst_atime;
						in->yst_mtime = oh->yst_mtime;
						in->yst_ctime = oh->yst_ctime;
						in->yst_rdev = oh->yst_rdev;


						if (oh->shadowsObject > 0) 
							yaffs_HandleShadowedObject(dev,
									   oh->
									   shadowsObject,
									   1);
					

						yaffs_SetObjectName(in, oh->name);
						parent =
						    yaffs_FindOrCreateObjectByNumber
					    		(dev, oh->parentObjectId,
					     		 YAFFS_OBJECT_TYPE_DIRECTORY);

						 fileSize = oh->fileSize;
 						 isShrink = oh->isShrink;
						 equivalentObjectId = oh->equivalentObjectId;

					}
					else {
						in->variantType = tags.extraObjectType;
						parent =
						    yaffs_FindOrCreateObjectByNumber
					    		(dev, tags.extraParentObjectId,
					     		 YAFFS_OBJECT_TYPE_DIRECTORY);
						 fileSize = tags.extraFileLength;
						 isShrink = tags.extraIsShrinkHeader;
						 equivalentObjectId = tags.extraEquivalentObjectId;
						in->lazyLoaded = 1;

					}
					in->dirty = 0;

					if (!parent)
						alloc_failed = 1;

					

 

					if (parent && parent->variantType ==
					    YAFFS_OBJECT_TYPE_UNKNOWN) {
                                                 
                                                parent->variantType =
                                                    YAFFS_OBJECT_TYPE_DIRECTORY;
                                                do { (&parent->variant . directoryVariant . children)->next = (&parent->variant . directoryVariant . children); (&parent->variant . directoryVariant . children)->prev = (&parent->variant . directoryVariant . children); } while(0);


                                        } else if (!parent || parent->variantType !=
						   YAFFS_OBJECT_TYPE_DIRECTORY)
					{
						

 

						do{ if((0x40000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



						parent = dev->lostNFoundDir;
					}

					yaffs_AddObjectToDirectory(parent, in);

					itsUnlinked = (parent == dev->deletedDir) ||
						      (parent == dev->unlinkedDir);

					if (isShrink) {
						 
						bi->hasShrinkHeader = 1;
					}

					




 

					switch (in->variantType) {
					case YAFFS_OBJECT_TYPE_UNKNOWN:	
						 
						break;
					case YAFFS_OBJECT_TYPE_FILE:

						if (in->variant.fileVariant.
						    scannedFileSize < fileSize) {
							



 
							in->variant.fileVariant.fileSize = fileSize;
							in->variant.fileVariant.scannedFileSize =
							    in->variant.fileVariant.fileSize;
						}

						if (isShrink &&
						    in->variant.fileVariant.shrinkSize > fileSize) {
							in->variant.fileVariant.shrinkSize = fileSize;
						}

						break;
					case YAFFS_OBJECT_TYPE_HARDLINK:
						if(!itsUnlinked) {
                                                  in->variant.hardLinkVariant.equivalentObjectId =
                                                    equivalentObjectId;
                                                  in->hardLinks.next =
                                                    (struct ylist_head *) hardList;
                                                  hardList = in;
                                                }
                                                break;
					case YAFFS_OBJECT_TYPE_DIRECTORY:
						 
						break;
					case YAFFS_OBJECT_TYPE_SPECIAL:
						 
						break;
					case YAFFS_OBJECT_TYPE_SYMLINK:
						if(oh){
						   in->variant.symLinkVariant.alias =
						    yaffs_CloneString(oh->
								      alias);
						   if(!in->variant.symLinkVariant.alias)
						   	alloc_failed = 1;
						}
						break;
					}

				}
				
			}

		}  

		if (state == YAFFS_BLOCK_STATE_NEEDS_SCANNING) {
			 
			state = YAFFS_BLOCK_STATE_FULL;
		}

		bi->blockState = state;

		 
		if (bi->pagesInUse == 0 &&
		    !bi->hasShrinkHeader &&
		    bi->blockState == YAFFS_BLOCK_STATE_FULL) {
			yaffs_BlockBecameDirty(dev, blk);
		}

	}

	if (altBlockIndex) 
		free(blockIndex);
	else
		free(blockIndex);
	
	



 
	yaffs_HardlinkFixup(dev,hardList);
	

	yaffs_ReleaseTempBuffer(dev, chunkData, 6723);
	
	if(alloc_failed){
		return 0;
	}

	do{ if((0x00000008) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	return 1;
}

 

static void yaffs_VerifyObjectInDirectory(yaffs_Object *obj)
{
        struct ylist_head *lh;
        yaffs_Object *listObj;
        
        int count = 0;

	if(!obj){
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		;
	}

        if(yaffs_SkipVerification(obj->myDev))
                return;

	if(!obj->parent){
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		;
	}
		
	if(obj->parent->variantType != YAFFS_OBJECT_TYPE_DIRECTORY){
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		;
	}
	
         
         
        for (lh = (&obj->parent->variant . directoryVariant . children)->next; lh != (&obj->parent->variant . directoryVariant . children); lh = lh->next ) {
		if (lh) {
                        listObj = ((yaffs_Object *)((char *)(lh)-(unsigned long)(&((yaffs_Object *)0)->siblings)));
			yaffs_VerifyObject(listObj);
			if(obj == listObj)
				count ++;
                }
	 }
	 
	 if(count != 1){
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		;
	}

}

static void yaffs_VerifyDirectory(yaffs_Object *directory)
{

        struct ylist_head *lh;
        yaffs_Object *listObj;
        
	if(!directory)
		;

        if(yaffs_SkipFullVerification(directory->myDev))
                return;

		
	if(directory->variantType != YAFFS_OBJECT_TYPE_DIRECTORY){
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		;
	}
	
         
         
        for (lh = (&directory->variant . directoryVariant . children)->next; lh != (&directory->variant . directoryVariant . children); lh = lh->next ) {
		if (lh) {
                        listObj = ((yaffs_Object *)((char *)(lh)-(unsigned long)(&((yaffs_Object *)0)->siblings)));
			if(listObj->parent != directory){
				do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
				;
			}
			yaffs_VerifyObjectInDirectory(listObj);
                }
	 }
	 
}


static void yaffs_RemoveObjectFromDirectory(yaffs_Object * obj)
{
	yaffs_Device *dev = obj->myDev;
	yaffs_Object *parent;
	
        yaffs_VerifyObjectInDirectory(obj);
	parent = obj->parent;
	
	yaffs_VerifyDirectory(parent);

        if(dev && dev->removeObjectCallback)
                dev->removeObjectCallback(obj);

           
        ylist_del_init(&obj->siblings);
        obj->parent = 0;

	yaffs_VerifyDirectory(parent);

}


static void yaffs_AddObjectToDirectory(yaffs_Object * directory,
				       yaffs_Object * obj)
{

	if (!directory) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		;
	}
	if (directory->variantType != YAFFS_OBJECT_TYPE_DIRECTORY) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		;
	}

        if (obj->siblings.prev == 0) {
                 
                ;

        } else if (ylist_empty(&obj->siblings)) {
        	;
        } 


	yaffs_VerifyDirectory(directory);

	yaffs_RemoveObjectFromDirectory(obj);
        
        
         
        ylist_add(&obj->siblings, &directory->variant.directoryVariant.children);
        obj->parent = directory;

        if (directory == obj->myDev->unlinkedDir
	    || directory == obj->myDev->deletedDir) {
		obj->unlinked = 1;
		obj->myDev->nUnlinkedFiles++;
		obj->renameAllowed = 0;
	}

	yaffs_VerifyDirectory(directory);
        yaffs_VerifyObjectInDirectory(obj);


}

yaffs_Object *yaffs_FindObjectByName(yaffs_Object * directory,
				     const char * name)
{
        int sum;

        struct ylist_head *i;
        char buffer[255 + 1];

        yaffs_Object *l;

	if (!name) {
		return 0;
	}

	if (!directory) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		;
	}
	if (directory->variantType != YAFFS_OBJECT_TYPE_DIRECTORY) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		;
	}

        sum = yaffs_CalcNameSum(name);

        for (i = (&directory->variant . directoryVariant . children)->next; i != (&directory->variant . directoryVariant . children); i = i->next ) {
                if (i) {
                        l = ((yaffs_Object *)((char *)(i)-(unsigned long)(&((yaffs_Object *)0)->siblings)));
                        
                        if(l->parent != directory)
                        	;
                        
                        yaffs_CheckObjectDetailsLoaded(l);

			 
			if (l->objectId == 2) {
				if (strcmp(name,"lost+found") == 0) {
					return l;
				}
			} else if (((l->sum) == (sum)) || l->hdrChunk <= 0){
				

 
				yaffs_GetObjectName(l, buffer,
						    255);
				if (strncmp(name,buffer,255) == 0) {
					return l;
				}

			}
		}
	}

	return 0;
}


#line 6981 "..\\fs\\yaffs_guts.c"



 

yaffs_Object *yaffs_GetEquivalentObject(yaffs_Object * obj)
{
	if (obj && obj->variantType == YAFFS_OBJECT_TYPE_HARDLINK) {
		 
		obj = obj->variant.hardLinkVariant.equivalentObject;
		yaffs_CheckObjectDetailsLoaded(obj);
	}
	return obj;

}

int yaffs_GetObjectName(yaffs_Object * obj, char * name, int buffSize)
{
	memset(name, 0, buffSize * sizeof(char));
	
	yaffs_CheckObjectDetailsLoaded(obj);

	if (obj->objectId == 2) {
		strncpy(name,"lost+found",buffSize - 1);
	} else if (obj->hdrChunk <= 0) {
		char locName[20];
		char numString[20];
		char *x = &numString[19];
		unsigned v = obj->objectId;
		numString[19] = 0;
		while(v>0){
			x--;
			*x = '0' + (v % 10);
			v /= 10;
		}
		 
		strcpy(locName,"obj");
		strcat(locName,x);
		strncpy(name,locName,buffSize - 1);

	}





	else {
		int result;
		__u8 *buffer = yaffs_GetTempBuffer(obj->myDev, 7029);

		yaffs_ObjectHeader *oh = (yaffs_ObjectHeader *) buffer;

		memset(buffer, 0, obj->myDev->nDataBytesPerChunk);

		if (obj->hdrChunk > 0) {
			result = yaffs_ReadChunkWithTagsFromNAND(obj->myDev,
							obj->hdrChunk, buffer,
							0);
		}
		strncpy(name,oh->name,buffSize - 1);

		yaffs_ReleaseTempBuffer(obj->myDev, buffer, 7042);
	}

	return strlen(name);
}

int yaffs_GetObjectFileLength(yaffs_Object * obj)
{

	 
	obj = yaffs_GetEquivalentObject(obj);

	if (obj->variantType == YAFFS_OBJECT_TYPE_FILE) 
	{
		 
		return obj->variant.fileVariant.fileSize;
	}
	if (obj->variantType == YAFFS_OBJECT_TYPE_SYMLINK) {
		return strlen(obj->variant . symLinkVariant . alias);
	} else {
		 
		return obj->myDev->nDataBytesPerChunk;
	}
}

int yaffs_GetObjectLinkCount(yaffs_Object * obj)
{
        int count = 0;
        struct ylist_head *i;

        if (!obj->unlinked) {
                count++;         
        }
        for (i = (&obj->hardLinks)->next; i != (&obj->hardLinks); i = i->next ) {
                count++;         
        }
        return count;

}

int yaffs_GetObjectInode(yaffs_Object * obj)
{
	obj = yaffs_GetEquivalentObject(obj);

	return obj->objectId;
}

unsigned yaffs_GetObjectType(yaffs_Object * obj)
{
	obj = yaffs_GetEquivalentObject(obj);

	switch (obj->variantType) {
	case YAFFS_OBJECT_TYPE_FILE:
		return 8;
		break;
	case YAFFS_OBJECT_TYPE_DIRECTORY:
		return 4;
		break;
	case YAFFS_OBJECT_TYPE_SYMLINK:
		return 10;
		break;
	case YAFFS_OBJECT_TYPE_HARDLINK:
		return 8;
		break;
	case YAFFS_OBJECT_TYPE_SPECIAL:
		 
		








 
			
	default:
		return 8;
		break;
	}
}

char *yaffs_GetSymlinkAlias(yaffs_Object * obj)
{
	obj = yaffs_GetEquivalentObject(obj);
	if (obj->variantType == YAFFS_OBJECT_TYPE_SYMLINK) {
		return yaffs_CloneString(obj->variant.symLinkVariant.alias);
	} else {
		return yaffs_CloneString("");
	}
}



int yaffs_SetAttributes(yaffs_Object * obj, struct iattr *attr)
{
	unsigned int valid = attr->ia_valid;

	if (valid & 1)
		obj->yst_mode = attr->ia_mode;
	if (valid & 2)
		obj->yst_uid = attr->ia_uid;
	if (valid & 4)
		obj->yst_gid = attr->ia_gid;

	if (valid & 16)
		obj->yst_atime = attr->ia_atime;
	if (valid & 64)
		obj->yst_ctime = attr->ia_ctime;
	if (valid & 32)
		obj->yst_mtime = attr->ia_mtime;

	if (valid & 8)
		yaffs_ResizeFile(obj, attr->ia_size);

	yaffs_UpdateObjectHeader(obj, 0, 1, 0, 0);

	return 1;

}
int yaffs_GetAttributes(yaffs_Object * obj, struct iattr *attr)
{
	unsigned int valid = 0;

	attr->ia_mode = obj->yst_mode;
	valid |= 1;
	attr->ia_uid = obj->yst_uid;
	valid |= 2;
	attr->ia_gid = obj->yst_gid;
	valid |= 4;

	attr->ia_atime = obj->yst_atime;
	valid |= 16;
	attr->ia_ctime = obj->yst_ctime;
	valid |= 64;
	attr->ia_mtime = obj->yst_mtime;
	valid |= 32;

	attr->ia_size = yaffs_GetFileSize(obj);
	valid |= 8;

	attr->ia_valid = valid;

	return 1;

}



#line 7210 "..\\fs\\yaffs_guts.c"

 

static int yaffs_CheckDevFunctions(const yaffs_Device * dev)
{

	 
	if (!dev->eraseBlockInNAND || !dev->initialiseNAND)
		return 0;



	 
	if (dev->writeChunkWithTagsToNAND &&
	    dev->readChunkWithTagsFromNAND &&
	    !dev->writeChunkToNAND &&
	    !dev->readChunkFromNAND &&
	    dev->markNANDBlockBad && dev->queryNANDBlock)
		return 1;


	 
	if (!dev->isYaffs2 &&
	    !dev->writeChunkWithTagsToNAND &&
	    !dev->readChunkWithTagsFromNAND &&
	    dev->writeChunkToNAND &&
	    dev->readChunkFromNAND &&
	    !dev->markNANDBlockBad && !dev->queryNANDBlock)
		return 1;

	return 0;		 
}


static int yaffs_CreateInitialDirectories(yaffs_Device *dev)
{
	 
	
	dev->lostNFoundDir = dev->rootDir =  0;
	dev->unlinkedDir = dev->deletedDir = 0;

	dev->unlinkedDir =
	    yaffs_CreateFakeDirectory(dev, 3, 0040000);
	
	dev->deletedDir =
	    yaffs_CreateFakeDirectory(dev, 4, 0040000);

	dev->rootDir =
	    yaffs_CreateFakeDirectory(dev, 1,
				      0666 | 0040000);
	dev->lostNFoundDir =
	    yaffs_CreateFakeDirectory(dev, 2,
				      0666 | 0040000);
	
	if(dev->lostNFoundDir && dev->rootDir && dev->unlinkedDir && dev->deletedDir){
		yaffs_AddObjectToDirectory(dev->rootDir, dev->lostNFoundDir);
		return 1;
	}
	
	return 0;
}

int yaffs_GutsInitialise(yaffs_Device * dev)
{
	int init_failed = 0;
	unsigned x;
	int bits;

	do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	 

	if (!dev) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);
		return 0;
	}

	dev->internalStartBlock = dev->startBlock;
	dev->internalEndBlock = dev->endBlock;
	dev->blockOffset = 0;
	dev->chunkOffset = 0;
	dev->nFreeChunks = 0;
	
	dev->gcBlock = -1;

	if (dev->startBlock == 0) {
		dev->internalStartBlock = dev->startBlock + 1;
		dev->internalEndBlock = dev->endBlock + 1;
		dev->blockOffset = 1;
		dev->chunkOffset = dev->nChunksPerBlock;
	}

	 

	if ((!dev->inbandTags && dev->isYaffs2 && dev->totalBytesPerChunk < 1024) || 
	    (!dev->isYaffs2 && dev->totalBytesPerChunk < 512) || 
	    (dev->inbandTags && !dev->isYaffs2 ) ||
	     dev->nChunksPerBlock < 2 || 
	     dev->nReservedBlocks < 2 || 
	     dev->internalStartBlock <= 0 || 
	     dev->internalEndBlock <= 0 || 
	     dev->internalEndBlock <= (dev->internalStartBlock + dev->nReservedBlocks + 2)	
	    ) {
 		 
 
		return 0;
	}
    
	if (yaffs_InitialiseNAND(dev) != 1) {
		 
		 
		return 0;
	}
	
	 
	if(dev->inbandTags)
		dev->nDataBytesPerChunk = dev->totalBytesPerChunk - sizeof(yaffs_PackedTags2TagsPart);
	else 
		dev->nDataBytesPerChunk = dev->totalBytesPerChunk;

	 
	if (!yaffs_CheckDevFunctions(dev)) {
		 
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);



		return 0;
	}
    
	 
	if (!yaffs_CheckStructures()) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}
    
	if (dev->isMounted) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

		return 0;
	}
    
	 

	dev->isMounted = 1;

	 
	
	

 
	x = dev->nDataBytesPerChunk;
	 
	dev->chunkShift = Shifts(x);
	x >>= dev->chunkShift;
	dev->chunkDiv = x;
	 
	dev->chunkMask = (1<<dev->chunkShift) - 1;
	 	
	


 

	x = dev->nChunksPerBlock * (dev->internalEndBlock + 1);
	
	bits = ShiftsGE(x);
	
	 
	if(!dev->wideTnodesDisabled){
		 
		if(bits & 1)
			bits++;
		if(bits < 16)
			dev->tnodeWidth = 16;
		else
			dev->tnodeWidth = bits;
	}
	else
		dev->tnodeWidth = 16;
 
	dev->tnodeMask = (1<<dev->tnodeWidth)-1;
		
	



 
		 
	if (bits <= dev->tnodeWidth)
		dev->chunkGroupBits = 0;
	else
		dev->chunkGroupBits = bits - dev->tnodeWidth;
		

	dev->chunkGroupSize = 1 << dev->chunkGroupBits;

	if (dev->nChunksPerBlock < dev->chunkGroupSize) {
		


 
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		return 0;
	}
    
	 

	 
	dev->garbageCollections = 0;
	dev->passiveGarbageCollections = 0;
	dev->currentDirtyChecker = 0;
	dev->bufferedBlock = -1;
	dev->doingBufferedBlockRewrite = 0;
	dev->nDeletedFiles = 0;
	dev->nBackgroundDeletions = 0;
	dev->nUnlinkedFiles = 0;
	dev->eccFixed = 0;
	dev->eccUnfixed = 0;
	dev->tagsEccFixed = 0;
	dev->tagsEccUnfixed = 0;
	dev->nErasureFailures = 0;
	dev->nErasedBlocks = 0;
	dev->isDoingGC = 0;
	dev->hasPendingPrioritisedGCs = 1;  
  
	 
	if(!yaffs_InitialiseTempBuffers(dev))
		init_failed = 1;
    
	dev->srCache = 0;
	dev->gcCleanupList = 0;
	
	if (!init_failed &&
	    dev->nShortOpCaches > 0) {
		int i;
		void *buf;
		int srCacheBytes = dev->nShortOpCaches * sizeof(yaffs_ChunkCache);

		if (dev->nShortOpCaches > 20) {
			dev->nShortOpCaches = 20;
		}

		dev->srCache =  yaffs_malloc(srCacheBytes);
		
		buf = (__u8 *) dev->srCache;
		    
		if(dev->srCache)
			memset(dev->srCache,0,srCacheBytes);
		   
		for (i = 0; i < dev->nShortOpCaches && buf; i++) {
			dev->srCache[i].object = 0;
			dev->srCache[i].lastUse = 0;
			dev->srCache[i].dirty = 0;
			dev->srCache[i].data = buf = yaffs_malloc(dev->totalBytesPerChunk);
		}
		if(!buf)
			init_failed = 1;
			
		dev->srLastUse = 0;
	}

	dev->cacheHits = 0;
	
	if(!init_failed){
		dev->gcCleanupList = yaffs_malloc(dev->nChunksPerBlock * sizeof(__u32));
		if(!dev->gcCleanupList)
			init_failed = 1;
	}
   
	if (dev->isYaffs2) {
		dev->useHeaderFileSize = 1;
	}
    
    
	if(!init_failed && !yaffs_InitialiseBlocks(dev))
		init_failed = 1;
	
	yaffs_InitialiseTnodes(dev);
	yaffs_InitialiseObjects(dev);
    
	if(!init_failed && !yaffs_CreateInitialDirectories(dev))
		init_failed = 1;
    
	if(!init_failed){
		 
		if (dev->isYaffs2) {
		    
			if(yaffs_CheckpointRestore(dev)) {
			    
				yaffs_CheckObjectDetailsLoaded(dev->rootDir);
				do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

			} else {
                
				

 
				yaffs_DeinitialiseBlocks(dev);
				yaffs_DeinitialiseTnodes(dev);
				yaffs_DeinitialiseObjects(dev);
				
			
				dev->nErasedBlocks = 0;
				dev->nFreeChunks = 0;
				dev->allocationBlock = -1;
				dev->allocationPage = -1;
				dev->nDeletedFiles = 0;
				dev->nUnlinkedFiles = 0;
				dev->nBackgroundDeletions = 0;
				dev->oldestDirtySequence = 0;

				if(!init_failed && !yaffs_InitialiseBlocks(dev))
					init_failed = 1;
					
				yaffs_InitialiseTnodes(dev);
				yaffs_InitialiseObjects(dev);

				if(!init_failed && !yaffs_CreateInitialDirectories(dev))
					init_failed = 1;

				if(!init_failed && !yaffs_ScanBackwards(dev))
					init_failed = 1;
			}
		}else
			if(!yaffs_Scan(dev))
				init_failed = 1;

		yaffs_StripDeletedObjects(dev);
	}
	
	if(init_failed){
        
		 
		do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		yaffs_Deinitialise(dev);
        
		return 0;
	}
    
	 
	dev->nPageReads = 0;
	dev->nPageWrites = 0;
	dev->nBlockErasures = 0;
	dev->nGCCopies = 0;
	dev->nRetriedWrites = 0;

	dev->nRetiredBlocks = 0;

	yaffs_VerifyFreeChunks(dev);
	yaffs_VerifyBlocks(dev);
	

	do{ if((0x00000100) & (yaffs_traceMask | 0xF0000000)) ;} while(0);

	return 1;

}

void yaffs_Deinitialise(yaffs_Device * dev)
{
	if (dev->isMounted) {
		int i;

		yaffs_DeinitialiseBlocks(dev);
		yaffs_DeinitialiseTnodes(dev);
		yaffs_DeinitialiseObjects(dev);
		if (dev->nShortOpCaches > 0 &&
		    dev->srCache) {

			for (i = 0; i < dev->nShortOpCaches; i++) {
				if(dev->srCache[i].data)
					free(dev->srCache[i]. data);
				dev->srCache[i].data = 0;
			}

			free(dev->srCache);
			dev->srCache = 0;
		}

		free(dev->gcCleanupList);

		for (i = 0; i < 6; i++) {
			free(dev->tempBuffer[i]. buffer);
		}


		dev->isMounted = 0;
		
		if(dev->deinitialiseNAND)
			dev->deinitialiseNAND(dev);
	}

}

static int yaffs_CountFreeChunks(yaffs_Device * dev)
{
	int nFree;
	int b;

	yaffs_BlockInfo *blk;

	for (nFree = 0, b = dev->internalStartBlock; b <= dev->internalEndBlock;
	     b++) {
		blk = yaffs_GetBlockInfo(dev, b);

		switch (blk->blockState) {
		case YAFFS_BLOCK_STATE_EMPTY:
		case YAFFS_BLOCK_STATE_ALLOCATING:
		case YAFFS_BLOCK_STATE_COLLECTING:
		case YAFFS_BLOCK_STATE_FULL:
			nFree +=
			    (dev->nChunksPerBlock - blk->pagesInUse +
			     blk->softDeletions);
			break;
		default:
			break;
		}

	}

	return nFree;
}

int yaffs_GetNumberOfFreeChunks(yaffs_Device * dev)
{
	 

	int nFree;
	int nDirtyCacheChunks;
	int blocksForCheckpoint;


	nFree = dev->nFreeChunks;




	nFree += dev->nDeletedFiles;
	
	 

	{
		int i;
		for (nDirtyCacheChunks = 0, i = 0; i < dev->nShortOpCaches; i++) {
			if (dev->srCache[i].dirty)
				nDirtyCacheChunks++;
		}
	}

	nFree -= nDirtyCacheChunks;

	nFree -= ((dev->nReservedBlocks + 1) * dev->nChunksPerBlock);
	
	 
	blocksForCheckpoint = yaffs_CalcCheckpointBlocksRequired(dev) - dev->blocksInCheckpoint;
	if(blocksForCheckpoint < 0)
		blocksForCheckpoint = 0;
		
	nFree -= (blocksForCheckpoint * dev->nChunksPerBlock);

	if (nFree < 0)
		nFree = 0;

	return nFree;

}

static int yaffs_freeVerificationFailures;

static void yaffs_VerifyFreeChunks(yaffs_Device * dev)
{
	int counted;
	int difference;
	
	if(yaffs_SkipVerification(dev))
		return;
	
	counted = yaffs_CountFreeChunks(dev);

	difference = dev->nFreeChunks - counted;

	if (difference) {
		do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0);


		yaffs_freeVerificationFailures++;
	}
}

 

#line 7716 "..\\fs\\yaffs_guts.c"

static int yaffs_CheckStructures(void)
{
 
 
 

        do { if(sizeof(yaffs_Tnode) != 2 * 16) { do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0); return 0; } } while(0);


		do { if(sizeof(yaffs_ObjectHeader) != 512) { do{ if((0xF0000000) & (yaffs_traceMask | 0xF0000000)) ;} while(0); return 0; } } while(0);

	    return 1;
}
