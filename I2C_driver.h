/*
 * I2C_driver.h
 *
 * Created: 6/22/2023 1:40:25 AM
 *  Author: kamar
 */ 


#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

/* intialize the master*/
void I2C_Master_Init (unsigned long scl_clock);

/* transmit start condition from master*/
void I2C_start (void);

/* transmit adress of slave  over data line */
void I2C_Write_adress (unsigned char adress);

/* tranmit data wich write in the slave */
void I2C_Write_data (unsigned char data);

/* transmit stop condition from master*/
void I2C_stop (void);

/* set Adress of microcontroller (master or  slave) not send Adress*/
void I2C_set_adress (unsigned char adress);

/* read from the slave */
unsigned char I2C_read_slave();



/*send rebeted start if you want another or specific adress*/
void I2C_repeted_start(void);

/* master reciver >> tranmit specfic adress and read from this adress */
void I2C_Write_adress_and_read(unsigned char adress);

/* read single messege only */
unsigned char I2C_red_with_NACK (void);


#endif /* I2C_DRIVER_H_ */