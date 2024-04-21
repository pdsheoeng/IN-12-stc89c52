#include "smg.h"

//�������������ʾ0~F�Ķ�������
u8 gsmg_code[10]={0x80,0x81,0x82,0x83
,0x84,0x85,0x08,0x10,0x20,0x40};

u8 light_code[6]={0x10,0x02,0x04,0x08,0x40,0x20};
				   //0,1,2,3,4,5,6,7,8,9
/*******************************************************************************
* �� �� ��       : smg_display
* ��������		 : ��̬�������ʾ
* ��    ��       : dat��Ҫ��ʾ������
				   pos������ʼ�ڼ���λ�ÿ�ʼ��ʾ����Χ1-8
* ��    ��    	 : ��
*******************************************************************************/



void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<6;i++)
	{
	   	switch(5-i)//λѡ
		{
			case 0: P1=light_code[5];break;
			case 1: P1=light_code[4];break;
			case 2: P1=light_code[3];break;
			case 3: P1=light_code[2];break;
			case 4: P1=light_code[1];break;
			case 5: P1=light_code[0];break;
		}
		SMG_A_DP_PORT=dat[i-pos_temp];//���Ͷ�ѡ����
		delay_10us(300);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
		SMG_A_DP_PORT=0x00;//����
	}
}

