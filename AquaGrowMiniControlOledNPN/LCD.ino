void printSpace(int val){
    if(val<1000)lcd.print(F(" "));
    if(val<100)lcd.print(F(" "));
    if(val<10)lcd.print(F(" "));
}
void printLightVal(byte channel, int val){
  
    if(channel<4){
    lcd.setCursor(channel*32,6);
    }else{
    lcd.setCursor((channel-5)*32,7);
    }
    lcd.print(4095-val);
    printSpace(4095-val);
}
void printTemp(float val){
    lcd.setCursor(80,1); 
    lcd.print(val);
    lcd.print(F(" C"));
}

void printTime(){
  lcd.setCursor(0,1);  
  lcd.print(retTime());
}

void printDose(int pos, int val){
    int EEPval;
    EEPROM_readAnything(100+(pos*2),EEPval);  
    EEPval=EEPval-val; 
    EEPROM_writeAnything(100+(pos*2), EEPval);
    
    if(pos<4){
    lcd.setCursor(0+(pos*32),3); 
    }else{
    lcd.setCursor(0+(pos*32),4); 
    }
    lcd.print(EEPval);
    printSpace(EEPval);
  
}
