#include "pebble.h"
#include "schedule.h"
  
#define NUM_MENU_SECTIONS 2
#define NUM_MENU_ICONS 3
#define NUM_FIRST_MENU_ITEMS 5
#define NUM_SECOND_MENU_ITEMS 1

static const int num_results=6;
static int here_loc;
static char * places[6];  
static int flasher_change=0;
static int flasher_on[6];
static char * place_title;
static Window * map_window;
static TextLayer * stoplist_text_layer;
  
static Window *window;

// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;

// A callback is used to specify the amount of sections of menu items
// With this, you can dynamically add and remove sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

// Each section has a number of items;  we use a callback to specify this
// You can also dynamically add and remove items using this
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return num_results;

    case 1:
      return NUM_SECOND_MENU_ITEMS;

    default:
      return 0;
  }
}

// A callback is used to specify the height of the section header
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (here_loc) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer, "You're at U. Plaza");
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "You're at UDC");
      break;
  }  
    
}

// This is the menu item draw callback where you specify what each item should look like
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  int* flasher_change_data = (int*) data;
  // Determine which section we're going to draw in
  //tick_timer_service_unsubscribe();	
  char * times[num_results];
  int urgent[num_results];
  catbus_get_times(here_loc, num_results, times, places, urgent);
  if (cell_index->section == 0) {
      // Use the row to specify which item we'll draw
    if(cell_index->row < num_results) {
      menu_cell_basic_draw(ctx, cell_layer, places[cell_index->row], times[cell_index->row], NULL);
      if(urgent[cell_index->row] && *flasher_change_data){
        if(!flasher_on[cell_index->row]) {
          menu_cell_basic_draw(ctx, cell_layer, "         !!!",times[cell_index->row],NULL);
          flasher_on[cell_index->row] = 1;
        } else flasher_on[cell_index->row] = 0;
        *flasher_change_data=0;
      } else {
        if(flasher_on[cell_index->row])
          menu_cell_basic_draw(ctx, cell_layer, "         !!!",times[cell_index->row],NULL);
      }
    } 
  } else {
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          menu_cell_title_draw(ctx, cell_layer, "Settings");
          break;
      }
  }
  for(int i =0;i<num_results;i++) {
      if(places[i] != NULL) free(places[i]);
      if(times[i] != NULL) free(times[i]);
  }
}

static void map_window_load(Window *window) {
  Layer *map_window_layer = window_get_root_layer(map_window);
  GRect bounds = layer_get_bounds(map_window_layer);
  //render_layer = layer_create(bounds);
  stoplist_text_layer = text_layer_create(bounds);
  if(strcmp(place_title, "DE") == 0) {
    text_layer_set_text(stoplist_text_layer,"DE STOPS:\nHayes\nMeadows\nUniversity Plaza\nCourt St & Washington");
  } else if(strcmp(place_title, "UP") == 0) {
    text_layer_set_text(stoplist_text_layer,"UP STOPS:\nNewing\nCouper Building\nEast Gym\nUniversity Plaza\nMeadows\nHayes\nWashington Drive");
  } else
    text_layer_set_text(stoplist_text_layer,"UR STOPZ");
  layer_add_child(map_window_layer, text_layer_get_layer(stoplist_text_layer));
  
  //InverterLayer *inverter_layer;
  //inverter_layer = inverter_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  //layer_add_child(map_window_layer, inverter_layer_get_layer(inverter_layer));
}

static void map_window_unload(Window *window) {
  text_layer_destroy(stoplist_text_layer);
}

// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Use the row to specify which item will receive the select action
    place_title = places[cell_index->row];
    map_window = window_create();
    window_set_fullscreen(map_window, true);
    window_set_window_handlers(map_window, (WindowHandlers) {
      .load = map_window_load,
      .unload = map_window_unload,
    });
    window_stack_push(map_window, true);
}

//static int flasher_inverted = 0;
void menu_update(struct tm *tick_time, TimeUnits units_changed) {
  flasher_change=1;
  menu_layer_reload_data	(menu_layer);
  //flasher_change=0;
}

// This initializes the menu upon window load
void window_load(Window *window) {
  here_loc = 1;
  //for(int i=0;i<num_results;i++) flasher_layers[i]=NULL;
  for(int i=0;i<num_results;i++) flasher_on[i]=0;
  flasher_change = 0;
  // And also load the background
  //menu_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_BRAINS);

  // Now we prepare to initialize the menu layer
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, &flasher_change, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
  tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) menu_update);
}

void window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(menu_layer);
}

int main(void) {
  window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

  app_event_loop();

  window_destroy(window);
}
