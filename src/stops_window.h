#ifndef _STOPS_WINDOW_H_
#define _STOPS_WINDOW_H_
  
#include "pebble.h"
extern Window * stops_window;
extern TextLayer * stoplist_text_layer;

extern char * place_title;
extern void stops_window_load(Window *window);
extern void stops_window_unload(Window *window);
  
#endif