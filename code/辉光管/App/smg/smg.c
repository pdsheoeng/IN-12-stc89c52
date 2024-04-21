#include "smg.h"

//共阴极数码管显示0~F的段码数据
u8 gsmg_code[10]={0x80,0x81,0x82,0x83
,0x84,0x85,0x08,0x10,0x20,0x40};

u8 light_code[6]={0x10,0x02,0x04,0x08,0x40,0x20};
				   //0,1,2,3,4,5,6,7,8,9
/*******************************************************************************
* 函 数 名       : smg_display
* 函数功能		 : 动态数码管显示
* 输    入       : dat：要显示的数据
				   pos：从左开始第几个位置开始显示，范围1-8
* 输    出    	 : 无
*******************************************************************************/



void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<6;i++)
	{
	   	switch(5-i)//位选
		{
			case 0: P1=light_code[5];break;
			case 1: P1=light_code[4];break;
			case 2: P1=light_code[3];break;
			case 3: P1=light_code[2];break;
			case 4: P1=light_code[1];break;
			case 5: P1=light_code[0];break;
		}
		SMG_A_DP_PORT=dat[i-pos_temp];//传送段选数据
		delay_10us(300);//延时一段时间，等待显示稳定
		SMG_A_DP_PORT=0x00;//消音
	}
}

