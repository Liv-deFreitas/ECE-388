/*
* TWI.h
*
* 
*  Author: rjfur
*/

#include <avr/io.h>
#ifndef TWI_H_
#define TWI_H_

#define TWI_WRITE 0
#define TWI_READ 1

#define TWI_ACK 1
#define TWI_NACK 0

//Start codes
#define TWI_SSTART 0x8 //start
#define TWI_RSTART 0x10 //repeated start

//Status codes for master Transmitter mode
#define TWI_WACK 0x18 //write ack
#define TWI_WNACK 0x20 //write nack
#define TWI_WDACK 0x28 // data transmitted return ack
#define TWI_WDNACK 0x30//data transmitted return nack
#define TWI_ARBLOST 0x38

//Status codes for master Receiver mode
#define TWI_RACK 0x40 //read ack
#define TWI_RNACK 0x48 //read nack
#define TWI_RDACK 0x50 //data byte received return ACK
#define TWI_RDNACK 0x58 //data byte received return NACK

void TWI_Init();
void TWI_WAIT();
uint8_t TWI_START();
void TWI_STOP();
void TWI_SLA(uint8_t ADDR, uint8_t RWbar);
uint8_t TWI_Transmit(uint8_t DATA);
uint8_t TWI_Receive(uint8_t Ack, uint8_t *DATA);

#endif /* TWI_H_ */