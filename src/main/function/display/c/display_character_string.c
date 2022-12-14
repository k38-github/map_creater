#include <stdio.h>
#include "../headers/display_character_string.h"
#include "../../parts.h"

int display_character_string(SDL_Renderer *renderer, TTF_Font *font, char *string, int x, int y) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderUTF8_Blended(font, string, (SDL_Color){255,255,255,255});

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int iw,ih;
    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);

    SDL_Rect txtRect=(SDL_Rect){0,0,iw,ih};
    SDL_Rect pasteRect=(SDL_Rect){x,y,iw,ih};

    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);

    SDL_FreeSurface(surface);

    return 0;
}
