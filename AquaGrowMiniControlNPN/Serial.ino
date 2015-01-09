// Handle Serial input
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void serialHandler(String input){
      int year;
      uint8_t month,day,hour,minute;
      int val,pin;
//      Serial.print(input);
  switch (input.substring(0,1).toInt()){
    //1=2014/03/05/18:28
    case 1:
       year=input.substring(2,6).toInt();
       month=input.substring(7,9).toInt();
       day=input.substring(10,12).toInt();
       hour=input.substring(13,15).toInt();
       minute=input.substring(16,18).toInt();
      rtc.adjust(year,month,day,hour,minute,0);
    break;
    //2=2:90
    case 2:
      pin= input.substring(2,3).toInt();
      val= input.substring(4,7).toInt();
      setLED(pin,4095-int(val*40.95));
      manualLight=true;
      Serial.print(pin);
      Serial.print(F(" -> "));
      Serial.println(4095-int(val*40.95));
      break;
    //3=2:60
    case 3:
      pin= input.substring(2,3).toInt();
      val= input.substring(4,7).toInt();
      if(pin<PUMPCOUNTS){
        unsigned long time = long(val*1000L);
        t.pulseImmediate(dosingPins[pin],time, HIGH);
        Serial.print(F("P "));
        Serial.print(pin);
        Serial.print(F(" kalibriert"));
      }else{
        Serial.print(F("P "));
        Serial.print(pin);
        Serial.print(F(" nicht definiert"));
      }
      break;
  }
      
}
