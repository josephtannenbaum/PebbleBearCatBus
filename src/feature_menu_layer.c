#include "pebble.h"
#include "schedule.h"
  
#define NUM_MENU_SECTIONS 2
#define NUM_MENU_ICONS 3
#define NUM_FIRST_MENU_ITEMS 5
#define NUM_SECOND_MENU_ITEMS 1

static int here_loc=1;
static char * places[5];  
static char * place_title;
static Window * map_window;
static TextLayer * stoplist_text_layer;
  
static Window *window;

// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;

// Menu items can optionally have an icon drawn with them
//static GBitmap *menu_icons[NUM_MENU_ICONS];

static int current_icon = 0;

// You can draw arbitrary things in a menu item such as a background
static GBitmap *menu_background;

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
      return NUM_FIRST_MENU_ITEMS;

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
  // Determine which section we're going to draw in
  char * times[5];
  catbus_get_times(here_loc, times, places);
  if (cell_index->section == 0) {
    //char * places[3];
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          //menu_cell_basic_draw(ctx, cell_layer, places[0], times[0], NULL);
        menu_cell_basic_draw(ctx, cell_layer, places[0], times[0], NULL);
          break;
        case 1:
         // menu_cell_basic_draw(ctx, cell_layer, places[1], times[1], NULL);
        menu_cell_basic_draw(ctx, cell_layer, places[1], times[1], NULL);
          break;
        case 2:
          //menu_cell_basic_draw(ctx, cell_layer, places[2], times[2], NULL);
        menu_cell_basic_draw(ctx, cell_layer, places[2], times[2], NULL);
          break;
        case 3:
          //menu_cell_basic_draw(ctx, cell_layer, places[2], times[2], NULL);
        menu_cell_basic_draw(ctx, cell_layer, places[3], times[3], NULL);
          break;
        case 4:
          //menu_cell_basic_draw(ctx, cell_layer, places[2], times[2], NULL);
        menu_cell_basic_draw(ctx, cell_layer, places[4], times[4], NULL);
          break;
      }
  } else {
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          menu_cell_title_draw(ctx, cell_layer, "Settings");
          break;
      }
  }
  for(int i =0;i<5;i++) {
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
    text_layer_set_text(stoplist_text_layer,"UR STOPS");
  layer_add_child(map_window_layer, text_layer_get_layer(stoplist_text_layer));
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

// This initializes the menu upon window load
void window_load(Window *window) {
  here_loc = 1;
  // Here we load the bitmap assets
  // resource_init_current_app must be called before all asset loading
  int num_menu_icons = 0;
  //menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BIG_WATCH);
  //menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_SECTOR_WATCH);
  //menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BINARY_WATCH);

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
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
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
}

void window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(menu_layer);

  // Cleanup the menu icons
  for (int i = 0; i < NUM_MENU_ICONS; i++) {
    //gbitmap_destroy(menu_icons[i]);
  }

  // And cleanup the background
  //gbitmap_destroy(menu_background);
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
