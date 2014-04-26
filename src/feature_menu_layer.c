#include "pebble.h"
#include "schedule.h"
#include "stops_window.h"
#include "settings_window.h"
  
#define NUM_MENU_SECTIONS 2
#define NUM_MENU_ICONS 3
#define NUM_FIRST_MENU_ITEMS 5
#define NUM_SECOND_MENU_ITEMS 2

//static int num_results;
static int here_loc;
static char ** places;  
static int flasher_change=0;
static int * flasher_changes;
static int * flasher_on = NULL;

static void setup_containers(int n) {
  if(places) free(places);
  if(flasher_on) free(flasher_on);
  if(flasher_changes) free(flasher_changes);
  num_results = n;
  flasher_on = (int *) malloc(n*sizeof(int));
  places = (char **) malloc(n*sizeof(char*));
  flasher_changes = (int *) malloc(n*sizeof(int));
}
  
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
  switch (section_index) {
    case 0:
      switch (here_loc) {
        case 0:
          menu_cell_basic_header_draw(ctx, cell_layer, "You're at U. Plaza");
          break;
        case 1:
          menu_cell_basic_header_draw(ctx, cell_layer, "You're at UDC");
          break;
        case 2:
          menu_cell_basic_header_draw(ctx, cell_layer, "You're on campus");
          break;
      }  
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "Settings");
      break;
  }
}

// This is the menu item draw callback where you specify what each item should look like
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  //int* flasher_change_data = (int*) data;
  int ** pt = (int **) data;
  int * flasher_changes_data = *pt;
  // Determine which section we're going to draw in
  //tick_timer_service_unsubscribe();	
  char * times[num_results];
  int urgent[num_results];
  char b[13];
  catbus_get_times(here_loc, num_results, times, places, urgent);
  if (cell_index->section == 0) {
      // Use the row to specify which item we'll draw
    if(cell_index->row < num_results) {
      menu_cell_basic_draw(ctx, cell_layer, places[cell_index->row], times[cell_index->row], NULL);
      if(urgent[cell_index->row] && flasher_changes_data[cell_index->row]){
        if(!flasher_on[cell_index->row]) {
          menu_cell_basic_draw(ctx, cell_layer, "         !!!",times[cell_index->row],NULL);
          flasher_on[cell_index->row] = 1;
        } else flasher_on[cell_index->row] = 0;
        //*flasher_change_data=0;
        flasher_changes_data[cell_index->row] = 0;
      } else {
        if(flasher_on[cell_index->row])
          menu_cell_basic_draw(ctx, cell_layer, "         !!!",times[cell_index->row],NULL);
      }
    } 
  } else {
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          switch (here_loc) {
            case 0:
              menu_cell_title_draw(ctx, cell_layer, "Loc: UP");
              break;
            case 1:
              menu_cell_title_draw(ctx, cell_layer, "Loc: UDC");
              break;
            default:
              menu_cell_title_draw(ctx, cell_layer, "Loc: Union");
              break;
          }
          
          break;
        case 1:
          snprintf(b, 12, "Results: %d", num_results);
          menu_cell_title_draw(ctx, cell_layer, b);
      }
  }
  for(int i =0;i<num_results;i++) {
      if(places[i] != NULL) free(places[i]);
      if(times[i] != NULL) free(times[i]);
  }
}

// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Use the row to specify which item will receive the select action
  if (cell_index->section == 0) {
    place_title = places[cell_index->row];
    stops_window = window_create();
    window_set_fullscreen(stops_window, true);
    window_set_window_handlers(stops_window, (WindowHandlers) {
      .load = stops_window_load,
      .unload = stops_window_unload,
    });
    window_stack_push(stops_window, true);
  } else {
    if(cell_index->row == 0) {
      here_loc++; if(here_loc==3) here_loc=0;
      for(int i=0;i<num_results;i++) flasher_on[i]=0;
    } else {
      if(num_results == 15) setup_containers(6);
      else setup_containers(num_results+1);;
    }
  }
}

//static int flasher_inverted = 0;
void menu_update(struct tm *tick_time, TimeUnits units_changed) {
  //flasher_change=1;
  for(int i =0;i<num_results;i++)flasher_changes[i]=1;
  menu_layer_reload_data	(menu_layer);
  //flasher_change=0;
}

// This initializes the menu upon window load
void window_load(Window *window) {
  here_loc = 2;
  //for(int i=0;i<num_results;i++) flasher_layers[i]=NULL;
  for(int i=0;i<num_results;i++) flasher_on[i]=0;
  //flasher_change = 0;
  for(int i =0;i<num_results;i++)flasher_changes[i]=0;
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
  menu_layer_set_callbacks(menu_layer, &flasher_changes, (MenuLayerCallbacks){
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
  setup_containers(6);
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
