/*
 * DHT11_SENSOR.h
 *
 * Created: 11/20/2018 1:34:48 AM
 *  Author: rjfur
 */ 


#ifndef DHT11_SENSOR_H_
#define DHT11_SENSOR_H_

#define DHT11_PIN 5//Define DHT11 PIN

uint8_t humid;
uint8_t temp;

#define DHT11_DATA_TEMP 0
#define DHT11_DATA_HUM 1
#define DHT11_ERROR 150

uint8_t DHT11_Getdata(uint8_t select);


#endif /* DHT11_SENSOR_H_ */