/*
  AquaGrow Programmcode zur Steuerung von Aquarien
  Copyright (C)2013-2015 AquaGrow - Moritz Stapelfeldt. All right reserved
  
  Der Code wurde entwickelt um Aquarien zu automatisieren und zu steuern. Er ist frei zugänglich und unterliegt dem Gedanken des OpenSource. Jeder kann ihn kostenfrei verwenden, kopieren, ganz oder teilweise solange die verwendeten Codezeilen als Fremdcode Kenntlich gemacht wurden und ein Link zum Orginal und/oder zur Webseite http://www.Aqua-Grow.de erhalten bleibt.
  
  Ich, als Urheber des Quellcodes übernehme keine Garantie auf die funktion des Quellcodes im ganzen oder teilen. Für evt Bugfixes und Updates besuche bitte http://www.Aqua-Grow.de und/oder https://github.com/majormadness
  
  Wenn veränderungen, modifikationen und/oder verbesserungen am Code vorgenommen werden bitte Ich um mitteilung unter info@aqua-grow.de

  This Software is free software; you can redistribute it and/or modify it under the terms of the CC BY-NC-SA 3.0 license.

  Commercial use of this Software requires you to buy a license that will allow commercial use. This includes using the Software, modified or not, as a tool to sell products.

  The license applies to all part of the Software including the examples and tools supplied with the Software.
*/

#include <Wire.h>
#include <RTClib.h>
#include <Timer.h>
#include <OneWire.h>
#include <MemoryFree.h>
#include <Keypad.h>  
#include <Keypad_I2C.h>  
#include <EEPROM.h>
#include "writeAnything.h" 
#include "structs.h"
#include "config.h"

#include <LiquidCrystal_I2C.h>

Timer t;
RTC_DS1307 rtc;
OneWire  ds(PIN_TEMP);
LiquidCrystal_I2C lcd(LCD_ADR,2,1,0,4,5,6,7,3,POSITIVE);   // Set the LCD I2C address

boolean pumpReset=false;


boolean manualRelay=false;
unsigned long last_print = 0;
String inputString = "";
boolean stringComplete = false;
float temperatur;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

char holdKey;
unsigned long t_hold;

//initialize an instance of class NewKeypad
Keypad_I2C keypad = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPADI2C );


void setup() {

  Wire.begin();
  rtc.begin();
  keypad.begin( );  
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  
  
  Serial.begin(9600);

  lcd.begin(16,2);

  for (int n=6;n<=12;n++){
    pinMode(n, OUTPUT);
  }
  for (int i=0;i<4;i++){
    pinMode(relayPIN[i], OUTPUT);
  }
  inputString.reserve(20);
  
    lcd.setCursor(4,0); 
    lcd.print(F("AquaGrow"));
    lcd.setCursor(2,1); 
    lcd.print(F("DosingTime"));
    delay(2000);
}

void loop() {
  rtc.now();
  t.update();
  char key = keypad.getKey();
  
  
    if(!manualRelay){
      setRelay();
    }
  // print the string when a newline arrives:
  if (stringComplete) {
    serialHandler(inputString);
    inputString = "";
    stringComplete = false;
  }

  if (millis() - last_print > 1000) {
    last_print = millis();
    
    temperatur = getTemp();
    Serial.println(retTime());
//    Serial.println(freeMemory());
    
    setDosing();
    
    printTime();
    printTemp(temperatur);

  }            
}

float getTemp(){
  byte present = 0;
  byte data[12];
  byte addr[8];
  ds.search(addr);
      
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); 
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  
  return (float)raw / 16.0; //celsius;
}
