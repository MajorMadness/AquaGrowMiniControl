void resetPumps(){
  if(rtc.daystamp>get_ts(23,59,30)){
    pumpReset=true;
  }
  if(rtc.daystamp<60 && pumpReset==true){
    pumpReset=false;
    for( int i=0;i < sizeof(dosingState)/sizeof(dosingState[0]); i++){
        dosingState[i]=false;
    }
  }
}
void setDosing(){
  resetPumps();
    for( int i=0;i < sizeof(dosing) / sizeof(dosing[0]); i++){
      if(dosing[i].active!=0){
        if(rtc.daystamp>=dosing[i].time && rtc.daystamp<=dosing[i].time+10 && digitalRead(dosingPins[dosing[i].pinAddr])==LOW && dosingState[i]==false){
	  unsigned long time = long(60000L * dosing[i].mldosing / dosingMlMin[dosing[i].pinAddr]);
          t.pulseImmediate(dosingPins[dosing[i].pinAddr],time, HIGH);
          dosingState[i]=true;
          printDose(dosing[i].pinAddr,dosing[i].mldosing);
        }
      }
    }
}