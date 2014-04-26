#include "pebble.h"
  
Window * map_window;
GBitmap *image;
BitmapLayer *image_layer;


char * place_title;
void map_window_load(Window *window) {
  
  Layer *map_window_layer = window_get_root_layer(map_window);
  GRect bounds = layer_get_bounds(map_window_layer);
  
  if(strcmp(place_title, "DE") == 0) {
    image = gbitmap_create_with_resource(RESOURCE_ID_DCR_MAP);
  } else if(strcmp(place_title, "UP") == 0) {
    image = gbitmap_create_with_resource(RESOURCE_ID_DCR_MAP);
  } else if(strcmp(place_title, "DCR") == 0) {
    image = gbitmap_create_with_resource(RESOURCE_ID_DCR_MAP);
  } else if(strcmp(place_title, "WS") == 0) {
    image = gbitmap_create_with_resource(RESOURCE_ID_DCR_MAP);
  } else
    image = gbitmap_create_with_resource(RESOURCE_ID_DCR_MAP);
  
  
  image_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(image_layer, image);
  layer_add_child(map_window_layer, bitmap_layer_get_layer(image_layer));
}

void map_window_unload(Window *window) {
  bitmap_layer_destroy(image_layer);
}