#include <stdio.h>
#include "../headers/draw_outer_periphery.h"
#include "../../display/headers/display_character_string.h"
#include "../../parts.h"


int draw_outer_periphery(SDL_Renderer *renderer, TTF_Font *font) {

    display_character_string(renderer, font, "OUT_OF_MAP", 680, 250);

    return 0;

}
