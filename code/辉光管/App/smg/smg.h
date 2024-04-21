#ifndef _smg_H
#define _smg_H

#include "public.h"


#define SMG_A_DP_PORT	P2	//使用宏定义数码管段码口



extern u8 gsmg_code[10];

void smg_display(u8 dat[],u8 pos);

#endif