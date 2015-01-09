#ifndef structs_h
#define structs_h

#include <WString.h>


typedef struct {
  uint32_t time;
  byte level;  
}LIGHT;

typedef struct {
  byte level;  
  boolean state;
}LIGHT_STATE;

typedef struct {
    uint32_t time;
    boolean active;
    char name[3];
    byte pinAddr;
    byte mldosing;
}PUMP;

uint32_t get_ts(uint8_t h, uint8_t m, uint8_t s){
  uint32_t t;
  t = h;
  t *= 60;
  t += m;
  t *= 60;
  t += s;
  return t;
}
#endif
