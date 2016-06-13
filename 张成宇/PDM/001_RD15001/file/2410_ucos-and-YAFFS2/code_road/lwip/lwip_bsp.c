#include "TypeCpu.h"
#include "ucos_ii.h"
#include <stdio.h>
#include <stdlib.h>
#include "Uart.h"
#include "tcpip.h"
#include "cs8900.h"
#include "PBuf.h"
#include "EthArp.h"

static OS_EVENT *recv_sem = 0;
static char sem_err = 0;
static struct netif cs8900_if = {0}; 

static void cs8900_skip(INT16U len)
{
	INT16U counter = 0;
	volatile INT16U content = 0;
	len = (len / 2) + (len % 2);

	for (; counter < len; ++counter)
		content = *(volatile INT16U *)0x19000300;
}

static err_t cs8900_init(struct netif *cs8900_if)
{
	/*config CS8900*/
	WriteCS8900Reg(0x0022, 0x0000); //use IRQ0
	WriteCS8900Reg(0x0158, 0x1412); //set mac addr
	WriteCS8900Reg(0x015a, 0x1816);
	WriteCS8900Reg(0x015c, 0x1c1a);
	WriteCS8900Reg(0x0112, 0x00d3); //enable RX and TX
	WriteCS8900Reg(0x0104, 0x7d05); //recieve Individual and Broadcast Addr
	WriteCS8900Reg(0x0102, 0x7903); //enable RX Done Interupt
	WriteCS8900Reg(0x0106, 0x0107); //enable TX Done Interupt
	WriteCS8900Reg(0x010a, 0x010b); //enable TX Ready Interupt
	WriteCS8900Reg(0x0116, 0x8017); //enable IRQ
	return ERR_OK;
}

static struct pbuf *cs8900_input(struct netif *cs8900_if)
{
	struct pbuf *p = NULL, *q = NULL;
	INT16U status = 0;
	INT16U len = 0;
	INT16U rx_ok = 0;

	if (rx_ok = (ReadCS8900Reg(0x0124) & 0x0100))
	{
		status = (*(volatile INT16U *)0x19000300);
		len = (*(volatile INT16U *)0x19000300);

		if (len > 0)
		{
			p = pbuf_alloc(PBUF_RAW, len + ETH_PAD_SIZE, PBUF_POOL);
			if (p != NULL)
			{
				for (q = p; q != 0; q = q->next)
				{
					/* read 8 bytes per iteration */
					INT16U *ptr = q->payload;
					INT16U i = q->len / 8;
					while(i > 0)
					{
						*ptr = *(volatile INT16U *)0x19000300; ptr++;
						*ptr = *(volatile INT16U *)0x19000300; ptr++;
						*ptr = *(volatile INT16U *)0x19000300; ptr++;
						*ptr = *(volatile INT16U *)0x19000300; ptr++;
						i--;
				  	}
					  /* read remainder */
					  i = ((q->len % 8) + 1) / 2;
					  while(i > 0)
					  {
						*ptr = *(volatile INT16U *)0x19000300;
						ptr++;
						i--;
					  }
				}
			}
			else
			{
				printf("fatal error! must make cs8900 skip the frame!\n");
				cs8900_skip(len);
			}
		}
	}

	return p;
}

void cs8900if_input(struct netif *cs8900_if)
{
	struct eth_hdr *ethhdr = NULL;
	struct pbuf *p = NULL;

	/* move received packet into a new pbuf */
	p = cs8900_input(cs8900_if);
	/* no packet could be read */
	if (p == NULL) {
		return;
	}
	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
	/* IP packet? */
	case ETHTYPE_IP:
		/* skip Ethernet header */
		pbuf_header(p, -(s16_t)sizeof(struct eth_hdr));
		/* pass to network layer */
		cs8900_if->input(p, cs8900_if);
		break;
	/* ARP packet? */
	case ETHTYPE_ARP:
		/* pass p to ARP module */
		etharp_arp_input(cs8900_if, (struct eth_addr *)&cs8900_if->hwaddr, p);
		break;
	/* unsupported Ethernet packet type */
	default:
		/* free pbuf */
		pbuf_free(p);
		p = NULL;
		break;
	}
}

#define ETH_MIN_FRAME_LEN 60

static err_t cs8900_output(struct netif *cs8900_if, struct pbuf *p)
{
	INT8U tries = 0;
	err_t result = ERR_OK;
	INT16U tx_ready = 0;
	INT16U tx_len = (p->tot_len < ETH_MIN_FRAME_LEN) ? ETH_MIN_FRAME_LEN : p->tot_len;

	/*if no eth link return ERR_CONN*/

	(*(volatile INT16U *)0x19000304) = 0x00c9; //Tx Cmd
	(*(volatile INT16U *)0x19000306) = tx_len; //Tx Len

	do
	{
		tx_ready = ReadCS8900Reg(0x0138) & 0x0100;
	}while (!tx_ready && (tries++ < 100));

	if (tx_ready)
	{
		INT16U sent_bytes = 0;
		struct pbuf *q = p;
		INT16U index_in_pbuf = 0;
		INT16U index_in_word = 0;
		INT8U word_to_send[2] = {0};

		while (q)
		{
			if (index_in_pbuf < q->len)
			{
				word_to_send[index_in_word++] = ((INT8U*)q->payload)[index_in_pbuf++];

				if (index_in_word == 2)
				{
					  (*(volatile INT16U*)0x19000300) = (word_to_send[1] << 8) | word_to_send[0];
					  index_in_word = 0;
					  sent_bytes += 2;
				}
			}
			else
			{
				q = q->next;
				index_in_pbuf = 0;
			}
		}

		if (index_in_word == 1)
		{
			 (*(volatile INT16U*)0x19000300) = word_to_send[0];
			sent_bytes += 2;
		}

		while (sent_bytes < ETH_MIN_FRAME_LEN)
		{
			(*(volatile INT16U*)0x19000300) = 0x0000;
			sent_bytes += 2;
		}
	}
	else
	{
		result = ERR_IF;
	}

	return result;
}
static void RecvTask(void *parameter)
{
	printf("eth recv task is running......\n");

	while (1)
	{
		OSSemPend(recv_sem, 0, &sem_err);
		cs8900if_input(&cs8900_if);
	}
}

static void InitEthRecv()
{
	INT8U *stack = (INT8U *)malloc(0x1000) + 0x1000;
	recv_sem = OSSemCreate(16);
	OSTaskCreate(RecvTask, (void *)0, (OS_STK *)stack, 5);
}

void RecvEthPkt()
{
	OSSemPost(recv_sem);
}


static err_t cs8900if_init(struct netif *cs8900_if)
{
	printf("cs8900if_init\n");
	/* administrative details */
	cs8900_if->name[0] = 'w';
	cs8900_if->name[1] = 't';
	/* downward functions */
	cs8900_if->output = etharp_output;
	cs8900_if->linkoutput = cs8900_output;
	/* initialize cs8900 specific interface state data pointer */
	cs8900_if->state = 0;
	/* maximum transfer unit */
	cs8900_if->mtu = 1500;
	/* broadcast capability */
	cs8900_if->flags = NETIF_FLAG_BROADCAST;
	/* hardware address length */
	cs8900_if->hwaddr_len = 6;
	cs8900_if->hwaddr[0] = 0x12;
	cs8900_if->hwaddr[1] = 0x14;
	cs8900_if->hwaddr[2] = 0x16;
	cs8900_if->hwaddr[3] = 0x18;
	cs8900_if->hwaddr[4] = 0x1a;
	cs8900_if->hwaddr[5] = 0x1c;
	/* intialize the cs8900a chip */
	return cs8900_init(cs8900_if);
}

void sys_init()
{
}

void netif_init()
{
	struct ip_addr ipaddr, netmask, gw;
	IP4_ADDR(&gw, 166,16,6,1);
	IP4_ADDR(&ipaddr, 166,16,6,6);
	IP4_ADDR(&netmask, 255,255,255,0);
	netif_add(&cs8900_if, &ipaddr, &netmask, &gw, NULL, cs8900if_init, tcpip_input);
	netif_set_default(&cs8900_if);
	netif_set_up(&cs8900_if);
	printf("netif_init\n");
}

void InitLwip()
{
	InitEthRecv();
	tcpip_init(0, 0);
}

