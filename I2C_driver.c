/*
 * I2C_driver.c
 *   
 * Created: 6/22/2023 1:40:02 AM
 *  Author: kamar
 */ 

#include <avr/io.h>
#include "macros.h"
#define F_CPU 8000000UL

#define prescaler 1


/* Master send and slave recive*/


void I2C_Master_Init (unsigned long scl_clock)
{
	/*reset the clock that the master generat it */
	TWBR= (unsigned char) (((F_CPU /scl_clock)-16)/(2* prescaler));
	
	if (prescaler==1)
	{
		TWSR=0;
	}
	else if (prescaler==4)
	{
		TWSR=1;
	}
	else if (prescaler==16)
	{
		TWSR=2;
	}
	else if (prescaler==64)
	{
		TWSR=3;
	}
}

 I2C_start ()
 {
	 TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTA) ;                                                       // set interrurt &enable I2C & start bit
	 while (READ_BIT(TWCR,TWINT)==0);                                                             // wait to finish action 
	 while ((TWSR &0XF8)!=0x08);                                                                 // stop to start condition has been transmit 
 }

I2C_Write_adress (unsigned char adress)
{
	TWDR=adress;                                                                                  // MSB=0>>write , MSB=1>>read
	TWCR= (1<<TWINT)|(1<<TWEN);                                                                  // set interrupt flag& enable I2C &
	while (READ_BIT(TWCR,TWINT)==0);                                                            // wait to finish action 
	while ((TWSR &0XF8)!=0x18);                                                                 //SLA+wr transmitted and ACK recived
}

I2C_Write_data (unsigned char data)
{
	TWDR=data;
	TWCR= (1<<TWINT)|(1<<TWEN);                                                                 //set interrupt flag &enable I2C 
	while (READ_BIT(TWCR,TWINT)==0);                                                             // wait to finish action 
	while ((TWSR &0XF8)!=0x28);                                                                 // data transimitted and ACK recived
}


I2C_stop (void)
{
	TWCR= (1<<TWINT) |(1<<TWEN)|(1<<TWSTO) ;                                               // set interrupt flag& stop bit
}


I2C_set_adress (unsigned char adress)
{
	TWAR= adress;                                                                                     //load adress of micro in TWAR register
}


I2C_read_slave()
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWEA);                                                         //set interrupt flag &enable I2C&  ACK bit 
	while (READ_BIT(TWCR,TWINT)==0);                                                              // wait to finish action 
	while ((TWSR &0XF8)!=0x60);                                                                   //slave recived SLA+WR and ACK has been returned                                                               
	TWCR |= (1<<TWINT);  
	while (READ_BIT(TWCR,TWINT)==0);                                                             // wait to read data
	while ((TWSR &0XF8)!=0x80);                                                                  //slave recived SLA+WR & data recived and ACK has been returned  
	return TWDR;
}




/* master is reciver >> this part of code specific to interface with external EEPROM */
	
I2C_repeted_start()
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTA) ;                                                       // set interrurt &enable I2C & start bit
	 while (READ_BIT(TWCR,TWINT)==0);                                                             // wait to finish action 
	 while ((TWSR &0XF8)!=0x10);                                                                 // stop to repeted start condition has been transmit 
}	

I2C_Write_adress_and_read(unsigned char adress)
{
	TWDR=adress;                                                                                  
	TWCR= (1<<TWINT)|(1<<TWEN);                                                                  // set interrupt flag& enable I2C &
	while (READ_BIT(TWCR,TWINT)==0);                                                            // wait to finish action 
	while ((TWSR &0XF8)!=0x40);                                                                 //SLA+R transmitted and ACK recived
}

I2C_red_with_NACK (void)
{
	TWCR= (1<<TWINT)|(1<<TWEN);                                                                //set interrupt flag &enable I2C 
	while (READ_BIT(TWCR,TWINT)==0);                                                           // wait to finish action 
	while ((TWSR &0XF8)!=0x58);                                                                //one data byte recived and not return ACK  
	return TWDR;
}