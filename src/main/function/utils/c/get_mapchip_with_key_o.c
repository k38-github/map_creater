#include <stdio.h>
#include "../headers/get_mapchip_with_key_o.h"

int get_mapchip_with_key_o(SDL_Renderer *renderer) {

    if (pallet_display == PALLET_DISPLAY_ON) {
        OUTER_PERIPHERY =
           pallet_array[(pallet_cursor.map_y / GRID_SIZE) * PALLET_COL +
                        (pallet_cursor.map_x / GRID_SIZE)];
    } else {
        OUTER_PERIPHERY =
           map_array[(cursor.map_y / GRID_SIZE) * COL +
                        (cursor.map_x / GRID_SIZE)];
    }

    return 0;

}
