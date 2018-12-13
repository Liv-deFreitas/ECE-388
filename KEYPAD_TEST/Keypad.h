/*
* Keypad.h
*
*
*  Author: rjfur
*/


#ifndef KEYPAD_H_
#define KEYPAD_H_
char Press;
uint8_t Key_Val;

//#define COL1  3  // P3 of PCF8574
//#define COL2  2  // P2 of PCF8574
//#define COL3  1  // P1 of PCF8574
//#define COL4  0  // P0
//#define ROW1  7  // P7 of PCF8574
//#define ROW2  6  // P6 of PCF8574
//#define ROW3  5  // P5 of PCF8574
//#define ROW4  4  // P4 of PCF8574

#define P4 0b01111111 //0x7F
#define P5 0b10111111 //0xBF
#define P6 0b11011111 //0xDF
#define P7 0b11101111 //0xEF
#define MASK 0b11111111 //0xFF
#define Keypad_pin PC0

#define PCF_ADDR (0x020<<1)

#define KEY_LOW !(PINB & (1<<Keypad_pin))

void Keypad_Init();

uint8_t IOX_Read(uint8_t ADDR);

void IOX_Write(uint8_t DATA); // write to LCD

void Keypad_Read(void);

#endif /* KEYPAD_H_ */