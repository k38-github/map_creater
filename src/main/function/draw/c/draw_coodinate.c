#include <stdio.h>
#include "../headers/draw_coodinate.h"
#include "../../display/headers/display_character_string.h"
#include "../../parts.h"


int draw_coordinate(SDL_Renderer *renderer, TTF_Font *font) {

    char coordinate[10];
    int coordinate_x = cursor.map_x;
    int coordinate_y = cursor.map_y;

    if (coordinate_x < 0) {
        coordinate_x--;
    }

    if (coordinate_y < 0) {
        coordinate_y--;
    }

    sprintf(coordinate, "%03d %03d", coordinate_x / GRID_SIZE, coordinate_y / GRID_SIZE);
    display_character_string(renderer, font, coordinate, 695, 100);

    return 0;

}
