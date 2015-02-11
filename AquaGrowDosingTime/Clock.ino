String retTime(){
  uint32_t t = rtc.daystamp;
 int ss = t % 60;
    t /= 60;
 int   mm = t % 60;
    t /= 60;
 int   hh = t % 24;

  String sReturn;
  
    sReturn = "";
  if (hh < 10) {      // correct hour if necessary
    sReturn += "0";
    sReturn += hh;
  }else{
    sReturn += hh;
  }
    sReturn += ":";
  if (mm < 10) {      // correct minute if necessary
    sReturn += "0";
    sReturn += mm;
  }else{
    sReturn += mm;
  }
    sReturn += ":";
  if (ss < 10) {      // correct second if necessary
    sReturn += "0";
    sReturn += ss;
  }else{
    sReturn += ss;
  }
  return sReturn;
}
