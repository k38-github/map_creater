#include <stdio.h>
#include "../headers/get_mapchip.h"

int get_mapchip(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    select_mapchip =
       pallet_array[((pallet_cursor.offset_y + mouse_position.y) / GRID_SIZE) * PALLET_COL +
                    ((pallet_cursor.offset_x + mouse_position.x) / GRID_SIZE)];

    return 0;

}
