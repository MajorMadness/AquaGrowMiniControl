void resetPumps(){
  if(rtc.daystamp>get_ts(23,59,30)){
    pumpReset=true;
  }
  if(rtc.daystamp<60 && pumpReset==true){
    pumpReset=false;
    for( int i=0;i < PUMPCOUNTS; i++){
        dosingState[i]=false;
    }
  }
}
void setDosing(){
  resetPumps();
    for( int i=0;i < PUMPCOUNTS; i++){
      if(dosing[i].active!=0){
        if(rtc.daystamp>=dosing[i].time && rtc.daystamp<=dosing[i].time+10 && digitalRead(dosingPins[dosing[i].pinAddr])==LOW && dosingState[i]==false){
 //     Serial.print(F("setDosing "));
 //     Serial.println(i);
	  unsigned long time = long(60000L * dosing[i].mldosing / dosingMlMin[i]);
          t.pulseImmediate(dosingPins[dosing[i].pinAddr],time, HIGH);
          dosingState[i]=true;
          printDose(i,dosing[i].mldosing);
        }
      }
    }
}

