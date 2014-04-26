#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_
  
#include "pebble.h"
  
typedef struct bus_time {
  int h;
  int m;
  char * n;
} bus_time;
  

  
extern void catbus_get_times(int loc, char ** times, char ** places);

#endif