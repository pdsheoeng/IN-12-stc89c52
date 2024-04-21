#include "reg52.h"
#include "ds3231.h"
#include "smg.h"

void main()
{
	u8 time_buf[6];
	while(1)
	{
		RTC_Read();
		time_buf[0]=gsmg_code[rtc[13]];
		time_buf[1]=gsmg_code[rtc[12]];
		time_buf[2]=gsmg_code[rtc[11]];
		time_buf[3]=gsmg_code[rtc[10]];
		time_buf[4]=gsmg_code[rtc[9]];
		time_buf[5]=gsmg_code[rtc[8]];
		smg_display(time_buf,1);
	}
}


