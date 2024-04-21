
////////////////////////////////////////////////////////////////////////////////////

#ifndef _ds3231_h_
#define _ds3231_h_
#define uint unsigned int
#define uchar unsigned char
/**************************************/
extern void IIC_Init(void);
extern uchar l_tmpdate[];
extern uchar l_tmpdisplay[];
extern void delay_IIC(void);
extern void IIC_start(void);
extern void IIC_stop(void);
extern bit IIC_Tack(void);
extern void Read_RTC(void);
extern void Set_RTC(void);
extern void DS1302_Initial();
#endif
