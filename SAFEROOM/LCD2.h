/*
 * LCD2.h
 *
 * 
 *  Author: rjfur
 */ 


#ifndef LCD2_H_
#define LCD2_H_

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

void LCD2_Init(void);

void LCD2_Print( char * str);

void LCD2_Posit(unsigned char x, unsigned char y);

void LCD2_Send(unsigned char DATA);

void LCD2_Pulse(unsigned char data);

void bitdata2(unsigned char data);

void LCD2_DWrite(unsigned char data, uint8_t rsmode);

void LCD2_Clear(void);


#endif /* LCD2_H_ */