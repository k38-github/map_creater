#include <stdio.h>
#include <SDL2/SDL.h>
#include "../headers/draw_map.h"
#include "../../parts.h"

int draw_map(SDL_Renderer *renderer){

    int x, y;
    int start_x = cursor.offset_x / GRID_SIZE;
    int end_x = start_x + SCREEN_WIDTH / GRID_SIZE;
    int start_y = cursor.offset_y / GRID_SIZE;
    int end_y = start_y + SCREEN_HEIGHT/ GRID_SIZE;


    for(y = start_y;y < end_y;y++){
        for(x = start_x; x < end_x;x++){

            SDL_Rect imageRect=(SDL_Rect){0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};
            SDL_Rect drawRect=(SDL_Rect){(x * GRID_SIZE) - cursor.offset_x,
                                         (y * GRID_SIZE) - cursor.offset_y,
                                         IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

            if ((x < 0) || (x > COL - 1) || (y < 0) || (y > ROW - 1)){
                SDL_RenderCopy(renderer, mapchip[OUT_OF_MAP].map_image, &imageRect, &drawRect);
            } else {
                SDL_RenderCopy(renderer, mapchip[map_array[y*COL+x]].map_image, &imageRect, &drawRect);
            }

        }
    }

    return 0;
}


