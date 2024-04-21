//iic.c

#include "reg52.h"
#include "I2C.h"
#include "intrins.h"
#include "delay.h"

//#define I2CDelay() {_nop_();_nop_();}

void I2C_Start(void) //????
{
	SDA_H;
	//I2CDelay();
	SCL_H;
	//I2CDelay();
	SDA_L;
	//I2CDelay();
}
void I2C_Stop(void) //??
{
	SDA_L;
	//I2CDelay();
	SCL_H;
	//I2CDelay();
	SDA_H;
	//I2CDelay();
}


void send_ACK(bit b_ACK)     //????ACK,????
{
	SCL_L;
	//I2CDelay();
	if(b_ACK)                    //ACK
	{
		SDA_L;        
	}
	else                          //NOACK
	{
		SDA_H;
	}
	//I2CDelay();
	SCL_H;
	//I2CDelay();
	SCL_L;
	//I2CDelay();
}

void read_ACK(void)    //?? 24C02 ?? ACK
{
	uint8_t t=0;
	SCL_H;
	//I2CDelay();
	while((I2C_SDA==1)&&(t<200))t++;    //??ACK,????
	SCL_L;
	//I2CDelay();
}

void I2C_init()  //I2C?????,?? I2C_SDA ? I2C_SCL ????
{
	SDA_H;
	SCL_H;
}

void write_byte(uint8_t date)       //?24C02?????????
{
	uint8_t mask;
	SCL_L;
	for(mask=0x80;mask!=0;mask>>=1)    //??????????
	{
		
		if((mask&date)==0)
		{
			SDA_L;
		}
		else
		{
			SDA_H;
		}
		//I2CDelay();
		SCL_H;
		//I2CDelay();
		SCL_L;
	}

}

uint8_t read_byte()   //?????,? 24C02 ???????
{
	uint8_t i=0,read_data=0;
	SCL_L;
	//I2CDelay();
	SDA_H;
	//I2CDelay();
	for(i=0;i<8;i++)
	{
		SCL_H;        //I2C_SCL ???????
		//I2CDelay();
		read_data=(read_data<<1)|I2C_SDA; //? I2C_SDA ??????
		SCL_L;        //I2C_SCL ???????
		//I2CDelay();
	}
	return read_data;
}

void write_add(uint8_t address,uint8_t date)    //? 24C02 ????????
{
	I2C_Start();        //????
	write_byte(0XA0);    //?????
	read_ACK();        //????
	write_byte(address);   //????????
	read_ACK();            //????
	write_byte(date);    //????
	read_ACK();           //????
	I2C_Stop();          //????
}


/*void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date)    //????,???????
{ 
	while(length--)
	{
		write_add(address++,*date++);
	}
	
}*/

void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date)    //?????
{ 
	I2C_Start();           
	write_byte(0XA0);      
	read_ACK();
	write_byte(address);    
	read_ACK();
	while(length--)
	{
		write_byte(*date++);
		read_ACK();
		//I2CDelay();
	}
	I2C_Stop();
}


uint8_t read_add(uint8_t address,bit ACK)  //? 24C02 ?????
{
	uint8_t date;
	I2C_Start();          //???????
	write_byte(0XA0);      //?????
	read_ACK();              //????
	write_byte(address);     //????????
	read_ACK();              //????
	I2C_Start();            //???????
	write_byte(0XA1);       //?????
	read_ACK();              //????
	date=read_byte();      //???
	
	send_ACK(ACK);     //????ACK????
	
	I2C_Stop();          //????
	
	return date;
}

void read_MultipleByte(uint8_t *temp,uint8_t address,uint8_t data_size)    //??????
{
	I2C_Start();
	write_byte(0XA0);
	read_ACK();
	write_byte(address);
	read_ACK();
	
	I2C_Start();
	write_byte(0XA1);
	read_ACK();
	
	while(data_size--)
	{
		*temp++=read_byte();
		//I2CDelay();
		send_ACK(data_size);     //????ACK,?data_size = 0?,?????    ????,???????;???,???????
	}
	
	I2C_Stop();
	
	//return temp;
}



