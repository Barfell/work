#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>

void abort() {}

extern char __heap_start__;

void *_sbrk_r(struct _reent *reent, ptrdiff_t incr)
{
	static unsigned long level = 0;
	char *expected = &__heap_start__ + level;
	level += incr;
	return expected;
}

void _exit(int code)
{
}

_ssize_t _read_r(
    struct _reent *r, 
    int file, 
    void *ptr, 
    size_t len)
{
	char c;
	int  i;
	unsigned char *p;
	
	p = (unsigned char*)ptr;
	
	for (i = 0; i < len; i++) {
		// c = uart0Getch();
		c = ReadChar();
		if (c == 0x0D) {
			*p='\0';
			break;
		}
		*p++ = c;
		WriteChar(c);
	}
	return len - i;
}

_ssize_t _write_r (
    struct _reent *r, 
    int file, 
    const void *ptr, 
    size_t len)
{
	int i;
	const unsigned char *p;
	
	p = (const unsigned char*) ptr;
	
	for (i = 0; i < len; i++) {
		if (*p == '\n' ) WriteChar('\r');
		WriteChar(*p++);
	}
	
	return len;
}

int _close_r(
    struct _reent *r, 
    int file)
{
	return 0;
}

_off_t _lseek_r(
    struct _reent *r, 
    int file, 
    _off_t ptr, 
    int dir)
{
	return (_off_t)0;	/*  Always indicate we are at file beginning.	*/
}


int _fstat_r(
    struct _reent *r, 
    int file, 
    struct stat *st)
{
	/*  Always set as character device.				*/
	st->st_mode = S_IFCHR;	
		/* assigned to strong type with implicit 	*/
		/* signed/unsigned conversion.  Required by 	*/
		/* newlib.					*/

	return 0;
}

int isatty(int file); /* avoid warning */

int isatty(int file)
{
	return 1;
}

