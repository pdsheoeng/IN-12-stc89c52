#include "I2C.h"



#define rtc_sec  0x00
#define rtc_min  0x01
#define rtc_hour  0x02
#define rtc_date  0x04
#define rtc_mon  0x05
#define rtc_year  0x06
#define rtc_week  0x03


unsigned char rtc_current[8] = {0x20,0x24,0x04,0x21,0x21,0x18,0x10,0x07};

unsigned char rtc[15];

void DS3231_Write(unsigned char addr,unsigned char dat)
{
    I2C_Start();
    I2C_SendByte(0XD0);
    I2C_ReadACK();
    I2C_SendByte(addr);
    I2C_ReadACK();
    I2C_SendByte(dat);
    I2C_ReadACK();
    I2C_Stop();
}


unsigned char DS3231_Read(unsigned char addr)
{
	  unsigned char Data;
	  I2C_Start();
    I2C_SendByte(0XD0);
    I2C_ReadACK();
    I2C_SendByte(addr);
    I2C_ReadACK();
    I2C_Start();
	  I2C_SendByte(0XD1);
	  I2C_ReadACK();
	  Data=I2C_ReadByte();
	  I2C_SendNAK();
    I2C_Stop();

	  return Data;
}


void RTC_WriteConfig(void)
{
	DS3231_Write(rtc_year,rtc_current[1]);
	DS3231_Write(rtc_mon,rtc_current[2]);
	DS3231_Write(rtc_date,rtc_current[3]);
	DS3231_Write(rtc_hour,rtc_current[4]);
	DS3231_Write(rtc_min,rtc_current[5]);
	DS3231_Write(rtc_sec,rtc_current[6]);
	DS3231_Write(rtc_week,rtc_current[7]);
}


void RTC_Read(void)
{
	
  rtc_current[1]=DS3231_Read(rtc_year);
  rtc_current[2]=DS3231_Read(rtc_mon);
  rtc_current[3]=DS3231_Read(rtc_date);
  rtc_current[4]=(DS3231_Read(rtc_hour)&0x3f);
  rtc_current[5]=(DS3231_Read(rtc_min)&0x7f);
  rtc_current[6]=(DS3231_Read(rtc_sec)&0x7f);
  rtc_current[7]=DS3231_Read(rtc_week);
	
	//-------?-------//
	rtc[0] = ((rtc_current[0]&0xf0)>>4);
	rtc[1] = (rtc_current[0]&0x0f);
	rtc[2] = ((rtc_current[1]&0xf0)>>4);
	rtc[3] = (rtc_current[1]&0x0f);
	//-------?-------//
		
	rtc[4] = ((rtc_current[2]&0xf0)>>4);
	rtc[5] = (rtc_current[2]&0x0f);
 
	//-------?-------//
	rtc[6] = ((rtc_current[3]&0xf0)>>4);
	rtc[7] = (rtc_current[3]&0x0f);
 
	//-------?-------//
	rtc[8] = ((rtc_current[4]&0xf0)>>4);
	rtc[9] = (rtc_current[4]&0x0f);
 
	//-------?-------//
	rtc[10] = ((rtc_current[5]&0xf0)>>4);
	rtc[11] = (rtc_current[5]&0x0f);
 
	//-------?-------//
	rtc[12] = ((rtc_current[6]&0xf0)>>4);
	rtc[13] = (rtc_current[6]&0x0f);
 
	//--------------//
	rtc[14] = (rtc_current[7]&0x0f);
}
