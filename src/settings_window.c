#include "pebble.h"
#include "settings_window.h"
  
Window * settings_window;
TextLayer * settings_text_layer;
int num_results;
static char buf[8];

void settings_select_callback(ClickRecognizerRef recognizer, void *context) {
  
}
void settings_up_callback(ClickRecognizerRef recognizer, void *context) {
  if(num_results == 14) return;
  num_results++;  
  snprintf(buf, 8, "%d", num_results);
  text_layer_set_text(settings_text_layer, buf);
}
void settings_down_callback(ClickRecognizerRef recognizer, void *context) {
  if(num_results == 0) return;
  num_results--;  
  snprintf(buf, 8, "%d", num_results);
  text_layer_set_text(settings_text_layer, buf);
}
void settings_window_load(Window *window) {
  Layer *settings_window_layer = window_get_root_layer(settings_window);
  GRect bounds = layer_get_bounds(settings_window_layer);
  settings_text_layer = text_layer_create(bounds);
  //num_results = 4;
  text_layer_set_font(settings_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  snprintf(buf, 7, "%d", num_results);
  
  text_layer_set_text(settings_text_layer, buf);
  layer_add_child(settings_window_layer, text_layer_get_layer(settings_text_layer));
  
  /*window_single_click_subscribe	(	BUTTON_ID_SELECT,(ClickHandler)settings_select_callback );
  window_single_click_subscribe	(	BUTTON_ID_UP,(ClickHandler)settings_up_callback )	;
  window_single_click_subscribe	(	BUTTON_ID_DOWN,(ClickHandler)settings_down_callback )	  ;*/
}

void settings_window_unload(Window *window) {
  text_layer_destroy(settings_text_layer);
}