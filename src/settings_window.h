#ifndef _SETTINGS_WINDOW_H_
#define _SETTINGS_WINDOW_H_
  
#include "pebble.h"
extern Window * settings_window;
extern TextLayer * settings_text_layer;

extern int num_results;
extern void settings_window_load(Window *window);
extern void settings_window_unload(Window *window);
  
#endif