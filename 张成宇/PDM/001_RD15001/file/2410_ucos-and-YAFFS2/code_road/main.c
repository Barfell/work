#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>
#include "TypeCpu.h"
#include "yaffsfs.h"
#include "Uart.h"
#include "os_cpu.h"
#include "Shell.h"
#include "tcpip.h"
#include "Init.h"
#include "lwip_bsp.h"

void make_a_file(char *yaffsName)
{
	int outh;
	const unsigned char content[] = "hello yaffs2, this is a test!\n";
	outh = yaffs_open(yaffsName, O_CREAT | O_RDWR | O_TRUNC, S_IREAD | S_IWRITE);
	yaffs_write(outh,content,strlen(content));
	yaffs_close(outh);
}

int dump_file_data(char *fn)
{
	int h;
	int marker;
	int i = 0;
	int size;
	int ok = 1;
	unsigned char b;
	
	h = yaffs_open(fn, O_RDWR,0);

				
	printf("%s\n",fn);
	while(yaffs_read(h,&b,1)> 0)
	{
		printf("%c",b);
		i++;
		if(i > 32) 
		{
		   printf("\n");
		   i = 0;;
		 }
	}
	printf("\n");
	yaffs_close(h);
	return ok;
}

void EthSend(void *data, size_t len)
{
	unsigned short tx_ready = 0;
	unsigned short *addr = (unsigned short *)data;

	(*(volatile unsigned short*)0x19000304) = 0x00c9; //Tx Cmd
	(*(volatile unsigned short*)0x19000306) = (unsigned short)len; //Tx Len

	do
	{
		tx_ready = ReadCS8900Reg(0x0138) & 0x0100;
	}while (!tx_ready);

	for (; len > 0; len -= 2)
		(*(volatile unsigned short*)0x19000300) = *addr++;
}

static void WriteS3C2410Reg(unsigned long addr, unsigned long val)
{
	(*(volatile unsigned long *)addr) = val;
}


#include "opt.h"
#include "arch.h"
#include "api.h"

const static char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_html[] = "<html><head><title>Congrats!</title></head><body><h1>Welcome to our lwIP HTTP server!</h1><p>This is a small test page.</body></html>";

void http_server_serve(struct netconn *conn) {
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  
  /* Read the data from the port, blocking if nothing yet there. 
   We assume the request (the part we care about) is in one netbuf */
  inbuf = netconn_recv(conn);

  if (netconn_err(conn) == ERR_OK) {
    netbuf_data(inbuf, &buf, &buflen);
    
    /* Is this an HTTP GET command? (only check the first 5 chars, since
    there are other formats for GET, and we're keeping it very simple )*/
    if (buflen>=5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' &&
        buf[4]=='/' ) {
      
      /* Send the HTML header 
             * subtract 1 from the size, since we dont send the \0 in the string
             * NETCONN_NOCOPY: our data is const static, so no need to copy it
       */
      netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
      /* Send our HTML page */
      netconn_write(conn, http_index_html, sizeof(http_index_html)-1, NETCONN_NOCOPY);
    }
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);
  
  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}

int http_server() {
  struct netconn *conn, *newconn;
  
  /* Create a new TCP connection handle */
  conn = netconn_new(NETCONN_TCP);
  LWIP_ERROR("http_server: invalid conn", (conn != NULL), return -1;);
  
  /* Bind to port 80 (HTTP) with default IP address */
  netconn_bind(conn, NULL, 80);
  
  /* Put the connection into LISTEN state */
  netconn_listen(conn);
  
  while(1) {
    newconn = netconn_accept(conn);
    http_server_serve(newconn);
    netconn_delete(newconn);
  }
  return 0;
}



void ComTask(void *parameter)
{
	printf("Com task is running......\n");

	while (1)
	{
		http_server();
	}
}

void InitTask(void *parameter)
{
	printf("Initializing......\r\n");

	InitShell();
	InitLwip();

	/*redirect the IRQ entry to 0x30000000*/
	WriteS3C2410Reg(0x00000018, 0xe3a0f5c0);
	/*confgi GPH as UART*/	
	WriteS3C2410Reg(0x56000070, 0x000000aa);
	WriteS3C2410Reg(0x50000008, 0x00000000);
	WriteS3C2410Reg(0x5000000c, 0x00000000);
	WriteS3C2410Reg(0x50000000, 0x00000003);
	WriteS3C2410Reg(0x50000004, 0x00000045);
	/*config the GPG pin as EINT9*/
	WriteS3C2410Reg(0x56000060, 0x00000008);
	/*config EINT9 through high level*/
	WriteS3C2410Reg(0x5600008c, 0x00000010);
	/*config timer4*/
	WriteS3C2410Reg(0x51000000, 0x00ffff);/*set Prescaler as 0xff*/
	WriteS3C2410Reg(0x51000004, 0x633333);/*set MUX4 as 1/16*/
	WriteS3C2410Reg(0x5100003c, 0x3333);/*set TCNTB4 as 0x3333*/
	WriteS3C2410Reg(0x51000008, 0x200000);/*stop timer4 and update TCNT4 from TCNB4*/
	WriteS3C2410Reg(0x51000008, 0x500000);/*run timer4*/
	/*clear interrupt*/
	WriteS3C2410Reg(0x560000a8, 0xffffffff); 
	WriteS3C2410Reg(0x4a000018, 0x000007ff);
	WriteS3C2410Reg(0x4a000000, 0xffffffff);
	WriteS3C2410Reg(0x4a000010, 0xffffffff);
	/*open mask for EINT9*/
	WriteS3C2410Reg(0x560000a4, 0x00fffdf0);
	/*open mask for uart0 rx int*/
	WriteS3C2410Reg(0x4a00001c, 0x000007fe);
	/*open mask for uart0, ext int and timer 4*/
	WriteS3C2410Reg(0x4a000008, 0xEFFFBFCF);

	/*switch to the SVC mode and open IRQ*/
	__asm	("mrs	r0,cpsr");
	__asm	("bic	r0,r0,#0xff");
	__asm	("orr	r0,r0,#0x53");
	__asm	("msr	cpsr_c,r0");

	yaffs_StartUp();
	yaffs_mount("/");
	//make_a_file("/hello");
	dump_file_data("/hello");
	yaffs_unmount("/");
	printf("testing nand end\n");

	OSTaskDel(2);
}

void SpawnInitTask(void)
{
	char *stack = (char *)malloc(0x1000) + 0x1000;
	OSTaskCreate(InitTask, (void *)0, (OS_STK *)stack, 2);
}

void SpawnComTask(void)
{
	char *stack = (char *)malloc(0x1000) + 0x1000;
	OSTaskCreate(ComTask, (void *)0, (OS_STK *)stack, 10);
}

int main()
{
	printf("Hello, I'm wt133664\n");
	OSInit();
	SpawnInitTask();
	SpawnComTask();
	OSStart();
}

