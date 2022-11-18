#include <stdio.h>
#include "../headers/draw_selected_mapchip.h"
#include "../../utils/headers/make_box.h"
#include "../../parts.h"

int draw_selected_mapchip(SDL_Renderer *renderer) {
    make_box(renderer, 700, 30, 62, 62, 255, WHITE);
    make_box(renderer, 702, 32, 58, 58, 255, BLACK);

    SDL_Rect imageRect=(SDL_Rect){0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};
    SDL_Rect drawRect=(SDL_Rect){715,
                                 45,
                                 IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

    SDL_RenderCopy(renderer, mapchip[select_mapchip].map_image, &imageRect, &drawRect);

    return 0;
}
