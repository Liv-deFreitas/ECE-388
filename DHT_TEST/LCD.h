/*
 * LCD.h
 *
 * Created: 11/17/2018 4:15:40 PM
 *  Author: rjfur
 */ 

#include <avr/io.h>
#ifndef LCD_H_
#define LCD_H_

#define LCD1_ADDR (0x03F<<1)
#define BACKLIGHT 8

#define En 4  // Enable bit
#define Rw 2  // Read/Write bit
#define Rs 1  // Register select bit

#define LCD_LINES           2     // number of visible lines of the display 
#define LCD_DISP_LENGTH    16     // visible characters per line of the display 
#define LCD_LINE_LENGTH  0x40     // internal line length of the display    
#define LCD_START_LINE1  0x00     // DDRAM address of first char of line 1 
#define LCD_START_LINE2  0x40     // DDRAM address of first char of line 2 

 void LCD_Init(void);
 void LCD_Print( char * str);
 void LCD_Posit(unsigned char x, unsigned char y);
 void LCD_Send(unsigned char DATA);
 void LCD_Pulse(unsigned char data);
 void bitdata(unsigned char data);
 void LCD_Write(unsigned char data, uint8_t rsmode);
 void LCD_Clear(void);
#endif /* LCD_H_ */