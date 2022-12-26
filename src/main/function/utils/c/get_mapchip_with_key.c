#include <stdio.h>
#include "../headers/get_mapchip_with_key.h"

int get_mapchip_with_key(SDL_Renderer *renderer) {

    select_mapchip =
       pallet_array[(pallet_cursor.map_y / GRID_SIZE) * PALLET_COL +
                    (pallet_cursor.map_x / GRID_SIZE)];

    return 0;

}


