#include <stdio.h>
#include "../headers/get_mapchip_with_key_a.h"

int get_mapchip_with_key_a(SDL_Renderer *renderer) {

    select_mapchip =
       map_array[(cursor.map_y / GRID_SIZE) * COL +
                    (cursor.map_x / GRID_SIZE)];

    return 0;

}


