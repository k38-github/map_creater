#include <stdio.h>
#include "../headers/get_mapchip_right_click.h"

int get_mapchip_right_click(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    select_mapchip =
       map_array[((cursor.offset_y + mouse_position.y) / GRID_SIZE) * COL +
                    ((cursor.offset_x + mouse_position.x) / GRID_SIZE)];

    return 0;

}
