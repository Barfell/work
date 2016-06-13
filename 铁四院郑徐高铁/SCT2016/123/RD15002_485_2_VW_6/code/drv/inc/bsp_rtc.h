#ifndef _BSP_RTC_H
#define _BSP_RTC_H

typedef enum {
	inner,
	extrnal
} rtc_clk;

char* get_time(void);

unsigned char RTC_Config(rtc_clk rtcclk);

void set_time(	unsigned char year,
				unsigned char mounth,
				unsigned char day,
				unsigned char hour,
				unsigned char min,
				unsigned char sec,
				unsigned char week,
				unsigned char ampm);

void set_alarm(	unsigned char hour,
				unsigned char min,
				unsigned char sec
				);




#endif



