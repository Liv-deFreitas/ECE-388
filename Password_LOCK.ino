/*This code was taken from Arduino website
    || @file Keypad Password
    || @version 1.0
    || @author Andrew Mascolo
    || @date May 7, 2013
    ||
    || @description
    || Simple use of keypad, password and LCD
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Lenght 5 // Give enough room for 4 chars + NULL char

//Define LCD pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

//Define I2C Address
const int i2c_addr = 0x3F;

//creat LCD obj
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

char Data[Password_Lenght]; // 4 is the number of chars it can hold + the null char = 5
char Master[Password_Lenght] = "1234"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char Keys[ROWS][COLS] = {
                             {'1','2','3','A'},
                             {'4','5','6','B'},
                             {'7','8','9','C'},
                             {'*','0','#','D'}
                                              };
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

//initialize an instance of class Keypad
Keypad myKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void setup() {
lcd.begin(16, 2);
}

void loop() {
    lcd.setCursor(0,0);
    lcd.print("Enter Password");
  customKey = myKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count,1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    //lcd.print("Password is ");

    if(!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
      lcd.print("CORRECT CODE");
    else
      lcd.print("INCORRECT CODE");

    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    lcd.clear();
    clearData();   
  }
}

void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
