#include "pebble.h"
#include "map_window.h"
  
Window * stops_window;
static ScrollLayer * scroll_layer;
TextLayer * stoplist_text_layer;
char * place_title;

void stops_select_callback(ClickRecognizerRef recognizer, void *context) {
    map_window = window_create();
    window_set_fullscreen(map_window, true);
    window_set_window_handlers(map_window, (WindowHandlers) {
      .load = map_window_load,
      .unload = map_window_unload,
    });
    window_stack_push(map_window, true);
}

void stops_select_callback_setup (void * data) {
  window_single_click_subscribe(BUTTON_ID_SELECT , stops_select_callback);
}

void stops_window_load(Window *window) {
  Layer *stops_window_layer = window_get_root_layer(stops_window);
  GRect bounds = layer_get_bounds(stops_window_layer);
  GRect max_text_bounds = GRect(0, 0, bounds.size.w, 2000);

  scroll_layer = scroll_layer_create(bounds);
  scroll_layer_set_click_config_onto_window(scroll_layer, stops_window);

  stoplist_text_layer = text_layer_create(GRect(0, 0, bounds.size.w, 2000));
  
  if(strcmp(place_title, "DE") == 0) {
    text_layer_set_text(stoplist_text_layer,"DE STOPS:\nHayes\nMeadows\nUniversity Plaza\nCourt St & Washington");
  } else if(strcmp(place_title, "UP") == 0) {
    text_layer_set_text(stoplist_text_layer,"UP STOPS:\nNewing\nCouper Building\nEast Gym\nUniversity Plaza\nMeadows\nHayes\nWashington Drive");
  } else if(strcmp(place_title, "DCR") == 0) {
    text_layer_set_text(stoplist_text_layer,"DCR STOPS:\nUniversity Downtown Center\nFront St & Riverside Dr\nMurray St & Riverside Dr\nChestnut St & Riverside Dr\nLaurel Ave & Riverside Dr\nBeethoven St & Riverside Dr\nMargaret St & Riverside Dr\nColumbus Pl & Riverside Dr\nElfred St & Riverside Dr\nEthel St & Riverside Dr\nAcademic A");
  } else if(strcmp(place_title, "WS") == 0) {
    text_layer_set_text(stoplist_text_layer,"WS STOPS:\nPhysical Facilities\nDenny's\nNew York Ave & Floral Ave\nAckely Ave & Floral Ave\nHarrison St & Floral Ave\nRoberts St & Floral Ave\nWillow St & Floral Ave\nBurbank Ave & Floral Ave\nCleveland Ave & Floral Ave\nFloral Ave & Main St\nMatthews St & Main St\nCrestmont Rd & Main St\nHelen St & Main St\nSchiller St & Main St\nClarke St & Main St\nCedar St & Main St\nMather St & Main St\nMurray St & Main St\nFront St & Main St\nHawley St & Court St\nUniversity Downtown Center");
  } else
    text_layer_set_text(stoplist_text_layer,"UR STOPZ");
  
  GSize max_size = text_layer_get_content_size(stoplist_text_layer);
  text_layer_set_size(stoplist_text_layer, max_size);
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, max_size.h + 4));
  
  scroll_layer_add_child(scroll_layer, text_layer_get_layer(stoplist_text_layer));
  
  layer_add_child(stops_window_layer, scroll_layer_get_layer(scroll_layer));
  
  scroll_layer_set_callbacks(scroll_layer, (ScrollLayerCallbacks) {
   .click_config_provider = stops_select_callback_setup
  });
}

void stops_window_unload(Window *window) {
  text_layer_destroy(stoplist_text_layer);
  scroll_layer_destroy(scroll_layer);
}