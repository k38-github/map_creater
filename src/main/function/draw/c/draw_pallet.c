#include <stdio.h>
#include "../headers/draw_pallet.h"
#include "../../parts.h"

int draw_pallet(SDL_Renderer *renderer){

    int x, y;
    int start_x = pallet_cursor.offset_x / GRID_SIZE - 1;
    int end_x = start_x + SCREEN_WIDTH / GRID_SIZE + 2;
    int start_y = pallet_cursor.offset_y / GRID_SIZE - 1;
    int end_y = start_y + SCREEN_HEIGHT/ GRID_SIZE + 2;


    for(y = start_y;y < end_y;y++){
        for(x = start_x; x < end_x;x++){

            SDL_Rect imageRect=(SDL_Rect){0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};
            SDL_Rect drawRect=(SDL_Rect){(x * GRID_SIZE) - pallet_cursor.offset_x,
                                         (y * GRID_SIZE) - pallet_cursor.offset_y,
                                         IMAGE_WIDTH*MAGNIFICATION, IMAGE_HEIGHT*MAGNIFICATION};

            if ((x < 0) || (x > PALLET_COL - 1) || (y < 0) || (y > PALLET_ROW - 1)){
                SDL_RenderCopy(renderer, mapchip[OUT_OF_MAP].map_image, &imageRect, &drawRect);
            } else {
                if(number_of_map_image >= y*PALLET_COL+x) {
                    SDL_RenderCopy(renderer, mapchip[pallet_array[y*PALLET_COL+x]].map_image, &imageRect, &drawRect);
                } else {
                    SDL_RenderCopy(renderer, mapchip[OUT_OF_MAP].map_image, &imageRect, &drawRect);
                }
            }

        }
    }

    return 0;
}
