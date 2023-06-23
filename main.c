/*
 * coding.c
 *
 * Created: 6/23/2023 4:53:46 AM
 * Author : kamar
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "I2C_driver.h"
#include "LCD driver.h"

int main(void)
{
    LCD_vinit ();
	unsigned char x;
	
	/*write to specific location >> frist location 0b00000000 */
	I2C_Master_Init (5000);
	_delay_ms(500);
	I2C_start ();                                                                            // transmit start condition
	I2C_Write_adress (0b10100000);                                                          // transmit device adress and write
	I2C_Write_data (0b00000000);                                                            // transmit word adress
	I2C_Write_data (0x32);                                                                  // transmit data which write in location 0b00000000
	I2C_stop ();
	
	
	/*read from location 0b000000000*/
	_delay_ms(500);
	I2C_start ();                                                                            // transmit start condition
	I2C_Write_adress (0b10100000);                                                          // transmit device adress and write
	I2C_Write_data (0b00000000);                                                            // transmit word adress
	I2C_repeted_start();                                                                    // transmit repeted start condition
	I2C_Write_adress_and_read(0b10100000);                                                  // transmit device adress with read
	x=I2C_red_with_NACK ();
	I2C_stop ();
	LCD_vsend_char (x);                                                                     // print data wich read on lcd
	
	
    
}

