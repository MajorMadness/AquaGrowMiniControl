void setRelay(){
  for( byte i=0;i <  RELAYCHANNELS; i++){
    boolean rState = findState(i);
    
    if(digitalRead(relayPIN[i])!=rState){
      digitalWrite(relayPIN[i],rState);
      printRelay(i,rState);
    }
  }
}

boolean findState(byte cNum){
  int curIndex=0;
  
  for(byte n=0;n<RELAYTIMES;n++){
    if(relays[cNum][n].time < rtc.daystamp){
      curIndex=n;
    }
  }
  
  return relays[cNum][curIndex].state;
}
