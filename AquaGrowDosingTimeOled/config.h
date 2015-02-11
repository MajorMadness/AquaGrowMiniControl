#define PUMPCOUNTS 7      // Number Pumps
#define RELAYCHANNELS 4
#define RELAYTIMES 6
#define KEYPADI2C 0x20
#define LCD_ADR 0x27


  // PIN MAPPING NICHT ÄNDERN!!!
  #define PIN_TEMP A1   // Temperatur
  #define RELAY1 2
  #define RELAY2 3
  #define RELAY3 4
  #define RELAY4 5
  #define DOSE7 6      // Dosierpumpe 
  #define DOSE6 7       // Dosierpumpe 
  #define DOSE5 8      // Dosierpumpe 
  #define DOSE4 9     // Dosierpumpe 
  #define DOSE3 10      // Dosierpumpe 
  #define DOSE2 11     // Dosierpumpe 
  #define DOSE1 12     // Dosierpumpe 

// Größe Vorratsflaschen Dünger in ml
const int dose_val = 1000;

// Neu zuordnung der Pins für Dosierung
const byte dosingPins[PUMPCOUNTS]={DOSE1,DOSE2,DOSE3,DOSE4,DOSE5,DOSE6,DOSE7};
// Milliliter per minute in Reihenfolge wie Pumpen oben Achtung Maximum 255ml/Minute
const byte dosingMlMin[PUMPCOUNTS]={60,60,60,60,60,60,60};

// Pumpen Einstellungen
// Uhrzeit, Aktive, Name, Pin Adresse (von array oben 0 ist erste Pumpe "Dose1") Milliliter pro Dosierung
const PUMP dosing[] = {  
{get_ts(10,0,0),1,"D1",0,5},
{get_ts(11,0,0),1,"D2",1,6},
{get_ts(11,25,0),1,"D3",2,3},
{get_ts(11,26,0),1,"D4",3,3},
{get_ts(11,23,0),1,"D3",4,3},
{get_ts(11,28,0),1,"D1",5,5},
{get_ts(11,28,0),1,"D1",6,5},
};

// Wird verwendet um zu sehen ob schon dosiert wurde. Nicht Ändern!!!
boolean dosingState[sizeof dosing / sizeof dosing[0]];

const byte relayPIN[]= {RELAY1,RELAY2,RELAY3,RELAY4};
RELAY relays[RELAYCHANNELS][RELAYTIMES] = { 
  {{get_ts(0,0,0),1},{get_ts(17,10,0),0},{get_ts(17,15,0),1},{get_ts(17,20,0),0},{get_ts(17,25,0),1},{get_ts(17,30,0),0}},
  {{get_ts(0,0,0),0},{get_ts(10,0,0),1},{get_ts(11,30,0),0},{get_ts(19,0,0),1},{get_ts(20,0,0),0},{get_ts(21,30,0),0}},
  {{get_ts(0,0,0),0},{get_ts(10,0,0),1},{get_ts(11,30,0),0},{get_ts(19,0,0),1},{get_ts(20,0,0),0},{get_ts(21,30,0),0}},
  {{get_ts(0,0,0),0},{get_ts(10,0,0),1},{get_ts(11,30,0),0},{get_ts(19,0,0),1},{get_ts(20,0,0),0},{get_ts(21,30,0),0}}
};

