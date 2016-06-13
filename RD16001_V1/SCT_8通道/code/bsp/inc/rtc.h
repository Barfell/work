#ifndef _RTC_H_
#define _RTC_H_

void rtc_init(void);
void read_rtc(void);

void GetRtc(char *rtcdata);

void SetRtc(
            unsigned int year,
            unsigned char mounth,
            unsigned char day,
            unsigned char dow,
            unsigned char hour,
            unsigned char min,
            unsigned char sec
             );

#endif