
// Taking care of some special events.
void keypadEvent(KeypadEvent key){
  byte chanel;
    switch (keypad.getState()){
    case PRESSED:
//      Serial.print(F("keypressed"));
//      Serial.println(key);
        if (key == 'A') {
          t.pulse(dosingPins[0],60000 / dosingMlMin[0], LOW);
//      Serial.print(F("DOSINGA"));
//      Serial.println(key);
          printDose(0,1);
        }else if (key == 'B') {
          t.pulse(dosingPins[1],60000 / dosingMlMin[1], LOW);
          printDose(1,1);
        }else if (key == 'C') {
          t.pulse(dosingPins[2],60000 / dosingMlMin[2], LOW);
          printDose(2,1);
        }else if (key == 'D') {
          t.pulse(dosingPins[3],60000 / dosingMlMin[3], LOW);
          printDose(3,1);
        }else if (key == '*' && PUMPCOUNTS>4) {
          t.pulse(dosingPins[4],60000 / dosingMlMin[4], LOW);
          printDose(4,1);
        }else if (key == '#' && PUMPCOUNTS>5) {
          t.pulse(dosingPins[5],60000 / dosingMlMin[5], LOW);
          printDose(5,1);
        }else if (key == '9') {
            manualLight=false;
   /*     }else if (key == '0') {
          manualLight=true;
          for(int i=0;i<LIGHT_CHANEL;i++){
            setLED(i,4095-int(ManLightState[i]*40.95));
          } */
        }else{
          char keyB = keypad.getKey();
          chanel = key-'1';
//      Serial.print(F("chanel"));
//      Serial.println(chanel);
          if(dimming[chanel].state==1){
            dimming[chanel].state=0;
            ledDriver.setLEDOff(chanel*2);
            ledDriver.setLEDOff(chanel*2+1);
            manualLight=true;
          }else if(dimming[chanel].state==0){
            dimming[chanel].state=1;
            ledDriver.setLEDOn(chanel*2);
            ledDriver.setLEDOn(chanel*2+1);
            manualLight=true;
          } 
        }
        break;
        
        
    case HOLD:
//      Serial.print(F("keyHOLD"));
//      Serial.println(key);
      if (key == 'A') {
          EEPROM_writeAnything(100, dose_val);
        }else if (key == 'B') {
          EEPROM_writeAnything(102, dose_val);
        }else if (key == 'C') {
          EEPROM_writeAnything(104, dose_val);
        }else if (key == 'D') {
          EEPROM_writeAnything(106, dose_val);
 /*       }else if (key == '*') {
          EEPROM_writeAnything(108, dose_val);
        }else if (key == '#') {
          EEPROM_writeAnything(110, dose_val);
 */       }
        break;
    }

}

void switch_holdKey(char k1){
//      Serial.print("-");
//      Serial.print(key);
//      Serial.println("-");
//      char k1 = keypad.getKey();
//      Serial.println(k1);
//      if(k1==65||k1==66||k1==67||k1==68||k1=='#'||k1=='*')return;
//  if(strcmp(key,"A")==0 || strcmp(key,"B")==0 || strcmp(key,"C")==0 || strcmp(key,"D")==0 || strcmp(key,"#")==0 || strcmp(key,"*")==0)return;
  
//      Serial.print(F("keySWITCH2"));
//      Serial.println(k1);
  int k = k1-'1';
  //k=k-1;
  if(dimming[k].state==1){
    dimming[k].level=dimming[k].level + 1;
  }else if(dimming[k].state==0){
    dimming[k].level=dimming[k].level - 1;
  }
  if(dimming[k].level>=100){
    dimming[k].state=0;
  }else if(dimming[k].level<=1){
    dimming[k].state=1;
  }
  
//    Serial.print(int(100-float(level/40.95)));
//    Serial.println(F("%"));
      setLED(k,4095-int(dimming[k].level*40.95));
}
