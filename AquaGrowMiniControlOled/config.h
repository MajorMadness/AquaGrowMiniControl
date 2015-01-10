#define PUMPCOUNTS 4      // Number Pumps
#define LIGHT_CHANEL 8    // Anzahl LED Kanäle
#define LIGHT_VALUES 8    // Zeiten Pro Kanal
#define KEYPADI2C 0x20    // Adresse Keypad
#define LED_DRV 0x40      // Adresse LED Driver, bei mehreren 0x70 eingeben für Broadcast adresse



// PIN MAPPING NICHT ÄNDERN!!!
// Pin Mapping für Nano
  #define PIN_TEMP 4   // Temperatur
  #define DOSE1 6      // Dosierpumpe1 (Nahe an LED)
  #define DOSE2 7      // Dosierpumpe 
  #define DOSE3 8      // Dosierpumpe 
  #define DOSE4 9      // Dosierpumpe 
  #define DOSE5 10     // Dosierpumpe 
  #define DOSE6 12     // Dosierpumpe6 (Nahe an + Pol / Keypad) 
  #define PIN_PWM 11   // PWM PIN    // Lüfter

// Temperatur ab Wann Lüfter an gehen (Ganzzahl)
const byte coolingTemp = 40;
const byte cTemp = 60;
// Geschwindigkeit der Lüfter -> 0 Aus, 255 Maximale Geschwindigkeit
const byte pwmValue = 255;
// Größe Vorratsflaschen Dünger in ml
const int dose_val = 1000;

// Neu zuordnung der Pins für Dosierung
const byte dosingPins[PUMPCOUNTS]={DOSE1,DOSE2,DOSE3,DOSE4};
// Milliliter per minute in Reihenfolge wie Pumpen oben
const byte dosingMlMin[PUMPCOUNTS]={60,60,60,60};

// Pumpen Einstellungen
// Uhrzeit, Aktive, Name, Pin Adresse (von array oben 0 ist erste Pumpe "Dose1"), Status (ignorieren, nur wichtig für Programm), Milliliter pro Dosierungconst 
PUMP dosing[] = {  
{get_ts(10,0,0),1,"D1",0,5},
{get_ts(11,0,0),1,"D2",1,6},
{get_ts(11,25,0),0,"D3",2,3},
{get_ts(11,26,0),0,"D4",3,3},
//{get_ts(11,23,0),0,"D3",2,3},
//{get_ts(11,28,0),0,"D1",0,5},
};

// Licht Einstellungen immer paar aus Uhrzeit und % angabe. Je reihe Zahl von LIGHT_VALUES, so viele Reihen wie in LIGHT_CHANEL
LIGHT light_channels[LIGHT_CHANEL][LIGHT_VALUES] ={
        {{get_ts(0,1,0),0},{get_ts(10,0,0),0},{get_ts(11,30,0),100},{get_ts(19,0,0),100},{get_ts(20,0,0),0},{get_ts(21,30,0),0},{get_ts(23,30,0),0},{get_ts(23,32,0),0}},
        {{get_ts(0,1,0),0},{get_ts(9,0,0),0},{get_ts(11,0,0),100},{get_ts(19,0,0),100},{get_ts(21,0,0),0},{get_ts(21,30,0),0},{get_ts(23,30,0),0},{get_ts(23,32,0),0}},
        {{get_ts(0,1,0),0},{get_ts(10,0,0),0},{get_ts(11,30,0),100},{get_ts(19,0,0),100},{get_ts(20,0,0),0},{get_ts(21,30,0),0},{get_ts(23,30,0),0},{get_ts(23,32,0),0}},
        {{get_ts(0,1,0),0},{get_ts(9,0,0),0},{get_ts(11,0,0),100},{get_ts(19,0,0),100},{get_ts(21,0,0),0},{get_ts(21,30,0),0},{get_ts(23,30,0),0},{get_ts(23,32,0),0}},
        {{get_ts(10,30,0),0},{get_ts(11,30,0),0},{get_ts(12,30,0),0},{get_ts(13,30,0),0},{get_ts(14,30,0),0},{get_ts(15,30,0),0},{get_ts(16,30,0),0},{get_ts(17,30,0),0}},
        {{get_ts(10,30,0),0},{get_ts(11,30,0),0},{get_ts(12,30,0),0},{get_ts(13,30,0),0},{get_ts(14,30,0),0},{get_ts(15,30,0),0},{get_ts(16,30,0),0},{get_ts(17,30,0),0}},
        {{get_ts(0,1,0),0},{get_ts(8,30,0),0},{get_ts(9,0,0),20},{get_ts(9,30,0),0},{get_ts(20,0,0),0},{get_ts(20,30,0),70},{get_ts(21,0,0),0},{get_ts(23,30,0),0}}, //Rot
        {{get_ts(8,30,0),5},{get_ts(9,30,0),0},{get_ts(20,30,0),0},{get_ts(21,0,0),40},{get_ts(21,30,0),20},{get_ts(21,50,0),10},{get_ts(21,55,20),10},{get_ts(23,55,20),5}}  // Blau
      };
// byte ManLightState[]={70,70,70,70,70,70,0,0};

// Dies nicht ändern!!! Nur zum erfassen wie das Keypad schaltet oder dimmt
LIGHT_STATE dimming[LIGHT_CHANEL] ={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

// Wird verwendet um zu sehen ob schon dosiert wurde. Nicht Ändern!!!
boolean dosingState[sizeof dosing / sizeof dosing[0]];
