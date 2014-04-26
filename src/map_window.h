#ifndef _MAP_WINDOW_H_
#define _MAP_WINDOW_H_
  
#include "pebble.h"
extern Window * map_window;
extern GBitmap *image;
extern BitmapLayer *image_layer;

extern char * place_title;
extern void map_window_load(Window *window);
extern void map_window_unload(Window *window);
  
#endif