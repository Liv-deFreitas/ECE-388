/*
* LCD.h
*
* Created: 11/17/2018 4:15:40 PM
*  Author: rjfur
*/

#include <avr/io.h>
#ifndef LCD_H_
#define LCD_H_

#define LCD1_ADDR (0x03F<<1) //0x03F
#define LCD2_ADDR (0x027<<1) //0x027
#define BACKLIGHT 8

#define En 4  // Enable bit
#define Rw 2  // Read/Write bit
#define Rs 1  // Register select bit

#define LCD_LINES           2     // number of visible lines of the display
#define LineOne 0x80
#define LineTwo 0xc0
#define LCD_DISP_LENGTH    16     // visible characters per line of the display
#define LCD_LINE_LENGTH  0x40     // internal line length of the display
#define LCD_START_LINE1  0x00     // DDRAM address of first char of line 1
#define LCD_START_LINE2  0x40     // DDRAM address of first char of line 2

#define LCD_DisplayOff 0x08//0b00001000 // turn display off #define lcd_DisplayOn 0b00001100 // display on, cursor off, don't blink character
#define LCD_DisplayOn 0xC//0b00001100 // display on, cursor off, don't blink character

void LCD_Init(void);

void LCD_Print( char * str);

void LCD_Posit(unsigned char x, unsigned char y);

void LCD_Send(unsigned char DATA);

void LCD_Pulse(unsigned char data);

void bitdata(unsigned char data);

void LCD_DWrite(unsigned char data, uint8_t rsmode);

void LCD_Clear(void);

void LCD_DISPOFF();

#endif /* LCD_H_ */