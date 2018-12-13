/*
 * TWI.c
 *
 * 
 *  Author: rjfur
 */ 
 #define F_CPU 16000000UL
 #define F_SCL 100000UL // SCL frequency
 #define Prescaler 1
 #define TWBR_VAL ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

 #include"TWI.h"

 void TWI_Init()
 {
	TWBR = (uint8_t)TWBR_VAL;
	TWSR &= ~(0b11<<TWPS0); //set prescaler bits to 0
	DDRC &=~((1<<4)|(1<<5));// Set input lines
	PORTC |= (1<<5)|(1<<4);// Internal pull ups used with external
 }
 void TWI_WAIT()
 {
	 while(!(TWCR & (1 << TWINT)));// waiting until int flag =1
 }
 uint8_t TWI_START()
 	 //start condition 
 {
	 TWCR=0x00;
	 TWCR = (1 << TWINT) | (1 << TWSTA) | (1<<TWEN);
	 TWI_WAIT();
	 return (TWSR & 0xF8);
 }
 void TWI_STOP()
 //STOP.
 {
	 TWCR = (1 << TWEN) | (1 << TWSTO) | (1<<TWINT);
 }
 //Send slave address + R or W bit r=1 w=0
 void TWI_SLA(uint8_t ADDR, uint8_t RWbar)
 {
	 TWDR = ADDR | (RWbar&1);// data reg = addr RW makeing sure 1 bit
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 TWI_WAIT();
 }
 //Transmitter
 uint8_t TWI_Transmit(uint8_t DATA)
{
	 TWDR = DATA;//
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 TWI_WAIT();
	 return (TWSR & 0xF8);
 }
 //Receiver
 uint8_t TWI_Receive(uint8_t Ack, uint8_t *DATA)
 {
	 if (Ack)
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); //enable Acknowledge
	 else
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 TWI_WAIT();
	 return TWDR;
	 //*DATA = TWDR;
	
 }
 //communication(repeated start condition)
 //# define keypad_ADDR (0xB4)
 //TWI_START();
 //TWI_SLA(keypad_ADDR,TWI_WRITE);
 //TWI_Transmit(data);
 
 //TWI_START();
 //TWI_SLA(keypad_ADDR,TWI_READ);
 //TWI_Receive(bbd,TWI_ACK); need to ACK all reads except last one
 //TWI_Receive(bcd,TWI_NACK);
 //TWI_STOP();

