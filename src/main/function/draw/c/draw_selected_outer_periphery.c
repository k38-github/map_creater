#include <stdio.h>
#include "../headers/draw_selected_outer_periphery.h"
#include "../../utils/headers/make_box.h"
#include "../../parts.h"

int draw_selected_outer_periphery(SDL_Renderer *renderer) {
    make_box(renderer, 700, 170, 62, 62, 255, WHITE);
    make_box(renderer, 702, 172, 58, 58, 255, BLACK);

    SDL_Rect imageRect=(SDL_Rect){0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};
    SDL_Rect drawRect=(SDL_Rect){715,
                                 185,
                                 IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

    SDL_RenderCopy(renderer, mapchip[OUTER_PERIPHERY].map_image, &imageRect, &drawRect);


    return 0;
}
