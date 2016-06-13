#line 1 "..\\fs\\yaffs_tagsvalidity.c"











 

#line 1 "..\\fs\\yaffs_tagsvalidity.h"













 





#line 1 "..\\fs\\yaffs_guts.h"













 




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


#line 20 "..\\fs\\yaffs_guts.h"
#line 1 "..\\fs\\yportenv.h"













 













 
typedef int off_t;
typedef int dev_t;
typedef unsigned int mode_t;
typedef unsigned long loff_t;



#line 113 "..\\fs\\yportenv.h"



 
#line 1 "..\\fs\\ydirectenv.h"













 



 






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

#line 21 "..\\fs\\yaffs_tagsvalidity.h"

void yaffs_InitialiseTags(yaffs_ExtendedTags * tags);
int yaffs_ValidateTags(yaffs_ExtendedTags * tags);
#line 15 "..\\fs\\yaffs_tagsvalidity.c"

void yaffs_InitialiseTags(yaffs_ExtendedTags * tags)
{
	memset(tags, 0, sizeof(yaffs_ExtendedTags));
	tags->validMarker0 = 0xAAAAAAAA;
	tags->validMarker1 = 0x55555555;
}

int yaffs_ValidateTags(yaffs_ExtendedTags * tags)
{
	return (tags->validMarker0 == 0xAAAAAAAA &&
		tags->validMarker1 == 0x55555555);

}
