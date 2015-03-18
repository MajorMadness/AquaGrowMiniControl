void printSpace(int val){
    if(val<1000)lcd.print(F(" "));
    if(val<100)lcd.print(F(" "));
    if(val<10)lcd.print(F(" "));
}

void printLightVal(byte channel, int val){
}

void printTemp(float val){
    lcd.setCursor(9,0);
    lcd.print(val);
    lcd.print((char)223);
    lcd.print(F("C"));
}

void printTime(){
  lcd.setCursor(0,0);  
  lcd.print(retTime());
}

void printDose(int pos, int val){
    int EEPval;
    EEPROM_readAnything(100+(pos*2),EEPval);  
    EEPval=EEPval-val; 
    EEPROM_writeAnything(100+(pos*2), EEPval);
    
    lcd.setCursor(0+(pos*4),1); 
          EEPval=EEPval*100/dose_val;
          lcd.print(EEPval);
    printSpace(EEPval);
  
}
