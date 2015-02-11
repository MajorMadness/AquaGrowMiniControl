// Taking care of some special events.
void keypadEvent(KeypadEvent key){
  int chanel;
  boolean s_Light=false;
    switch (keypad.getState()){
    case PRESSED:
        if (key == 'A') {
          manualRelay=true;
          lcd.setCursor(12,0); 
          if(digitalRead(relayPIN[0])==HIGH){
            digitalWrite(relayPIN[0],LOW);
      printRelay(0,0);
          }else{
            digitalWrite(relayPIN[0],HIGH);
      printRelay(0,1);
          }
          Serial.println(digitalRead(relayPIN[0]));
          manualRelay=true;
        }else if (key == 'B') {
          manualRelay=true;
          lcd.setCursor(13,0); 
          if(digitalRead(relayPIN[1])==HIGH){
            digitalWrite(relayPIN[1],LOW);
      printRelay(1,0);
          }else{
            digitalWrite(relayPIN[1],HIGH);
      printRelay(1,1);
          }
          Serial.println(digitalRead(relayPIN[1]));
          manualRelay=true;
        }else if (key == 'C') {
          manualRelay=true;
          lcd.setCursor(14,0); 
          if(digitalRead(relayPIN[2])==HIGH){
            digitalWrite(relayPIN[2],LOW);
      printRelay(2,0);
          }else{
            digitalWrite(relayPIN[2],HIGH);
      printRelay(2,1);
          }
          Serial.println(digitalRead(relayPIN[2]));
          manualRelay=true;
        }else if (key == 'D') {
          manualRelay=true;
          lcd.setCursor(15,0); 
          if(digitalRead(relayPIN[3])==HIGH){
            digitalWrite(relayPIN[3],LOW);
      printRelay(3,0);
          }else{
            digitalWrite(relayPIN[3],HIGH);
      printRelay(3,1);
          }
          Serial.println(digitalRead(relayPIN[3]));
        }else if (key == '1') {
          t.pulse(dosingPins[0],60000 / dosingMlMin[0], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(0,1);
        }else if (key == '2') {
          t.pulse(dosingPins[1],60000 / dosingMlMin[1], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(1,1);
        }else if (key == '3') {
          t.pulse(dosingPins[2],60000 / dosingMlMin[2], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(2,1);
        }else if (key == '4') {
          t.pulse(dosingPins[3],60000 / dosingMlMin[3], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(3,1);
        }else if (key == '5') {
          t.pulse(dosingPins[4],60000 / dosingMlMin[4], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(4,1);
        }else if (key == '6') {
          t.pulse(dosingPins[5],60000 / dosingMlMin[5], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(5,1);
        }else if (key == '7') {
          t.pulse(dosingPins[6],60000 / dosingMlMin[6], LOW);
      Serial.print(F("DOSINGA"));
      Serial.println(key);
          printDose(6,1);
        }else if (key == '8') {
        }else if (key == '9') {
          manualRelay=false;
          lcd.setCursor(15,1); 
          lcd.print(F("A"));
        }else if (key == '*') {
        }else if (key == '#') {
        }else if (key == '0') {
        }
        break;
        
        
    case HOLD:
      if (key == '1') {
          EEPROM_writeAnything(100, dose_val);
        }else if (key == '2') {
          EEPROM_writeAnything(102, dose_val);
        }else if (key == '3') {
          EEPROM_writeAnything(104, dose_val);
        }else if (key == '4') {
          EEPROM_writeAnything(106, dose_val);
        }else if (key == '5') {
          EEPROM_writeAnything(108, dose_val);
        }else if (key == '6') {
          EEPROM_writeAnything(110, dose_val);
        }else if (key == '7') {
          EEPROM_writeAnything(112, dose_val);
        }
        break;
    } 
}

void switch_holdKey(char* key){
  if(strcmp(key,"A")==0 || strcmp(key,"B")==0 || strcmp(key,"C")==0 || strcmp(key,"D")==0 || strcmp(key,"#")==0 || strcmp(key,"*")==0)return;
  
}
