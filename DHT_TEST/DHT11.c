/*
* DHT11.c
*
* Created: 11/11/2018 10:22:22 PM
*  Author: rjfur
http://www.electronicwings.com
copyright (c) Davide Gironi, 2012

First- Send request to sensor
Second-Sensor will send response, then will send out 40-bit data packet.

StartPULSE- pull down data pin 18ms min then pull up.

ResponsePULSE- LOW for 54us and goes HIGH 80us.
After response pulse the sensor will send the 40-bit data(5 8-bit segments).
1st- INT HUM
2nd- DEC HUM
3rd- INT TEMP IN C
4th- DEC TEMP IN C
5th- CHECKSUM VALUE (TEMP + HUM values)

EndPUSLE- After sending the data 54us LOW then goes HIGH, then enters Sleep Mode.

*/

#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "DHT11.h"

//Get data from sensor
int8_t DHT11_Getdata( int8_t *temp, int8_t *humid)
{
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	DDRD |= (1<<DHT11_PIN); //output
	PORTD |= (1<<DHT11_PIN); //high
	_delay_ms(100);

	//send start pulse to DHT11

	DDRD |= (1<<DHT11_PIN); //set pin as output
	PORTD &= ~(1<<DHT11_PIN); //clear to LOW pull down
	_delay_ms(20); //wait 20ms to let DHT detect the signal
	PORTD |= (1<<DHT11_PIN); //set to HIGH pull up
	

	//get response pulse from DHT11

	DDRD &= ~(1<<DHT11_PIN);//set pin as input
	_delay_us(40); //wait for DHTs response
	if ((PIND & (1<<DHT11_PIN))) //check for LOW response
	{
		return -1;
	}
	_delay_us(80); //response lasts 80us
	if (!(PIND & (1<<DHT11_PIN))) //check if DHT sets from LOW to HIGH
	{
		return -1;
	}
	_delay_us(80); //This will keep for 80us (prep for data trans)


	// receive data

	uint16_t timeoutcounter = 0;
	for (j=0; j<5; j++) //read 5 byte
	{
		uint8_t result=0;
		for(i=0; i<8; i++) //read every bit
		{
			timeoutcounter = 0;
			while(!(PIND & (1<<DHT11_PIN))) //wait for an high input (non blocking)
			{
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT)
				{
					return -1; //timeout
				}
			}
			_delay_us(30);
			if(PIND & (1<<DHT11_PIN)) //if input is high after 30 us, get result
			result |= (1<<(7-i));
			timeoutcounter = 0;
			while(PIND & (1<<DHT11_PIN)) { //wait until input get low (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1; //timeout
				}
			}
		}
		bits[j] = result;
	}
	//reset port
	DDRD |= (1<<DHT11_PIN); //output
	PORTD |= (1<<DHT11_PIN); //high
	_delay_ms(100);
	
	//checksum
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
		*temp = bits[2];
		*humid = bits[0];
		return 0;
	}
	else
	return -1;
}
int8_t DHT_GetTH(int8_t *temp, int8_t *humid)
{
	
	return DHT11_Getdata(temp, humid);
	
}
