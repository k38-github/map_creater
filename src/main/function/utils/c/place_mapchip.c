#include <stdio.h>
#include "../headers/place_mapchip.h"

int place_mapchip(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    map_array[((cursor.offset_y + mouse_position.y) / GRID_SIZE)*COL +
              ((cursor.offset_x + mouse_position.x) / GRID_SIZE)] = select_mapchip;

    return 0;

}


