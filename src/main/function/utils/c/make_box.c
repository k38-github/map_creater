#include <stdio.h>
#include "../headers/make_box.h"

int make_box(SDL_Renderer *renderer, int x, int y, int w, int h, int blend, COLOR color) {

    SDL_Rect rectangle;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    if (color == WHITE) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, blend);
    } else if (color == BLACK) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, blend);
    }

    SDL_RenderFillRect(renderer, &rectangle);

    return 0;
}
