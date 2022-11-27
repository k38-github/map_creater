#include <stdio.h>
#include "../headers/make_box.h"
#include "../headers/pallet_move.h"

int pallet_move(SDL_Event e, SDL_Renderer *renderer) {

    int cursor_x = pallet_cursor.map_x - pallet_cursor.offset_x;
    int cursor_y = pallet_cursor.map_y - pallet_cursor.offset_y;

    make_box(renderer, cursor_x, cursor_y, GRID_SIZE, GRID_SIZE, 100, BLACK);

    if (frame % 5 == 0) {

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){
            pallet_cursor.map_y = pallet_cursor.map_y - GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN){
            pallet_cursor.map_y = pallet_cursor.map_y + GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
            pallet_cursor.map_x = pallet_cursor.map_x + GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){
            pallet_cursor.map_x = pallet_cursor.map_x - GRID_SIZE;
        }

     }

    if (frame <= 10000) {
        frame++;
    } else {
        frame = 0;
    }

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_k){
        pallet_cursor.map_y = pallet_cursor.map_y - GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_j){
        pallet_cursor.map_y = pallet_cursor.map_y + GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l){
        pallet_cursor.map_x = pallet_cursor.map_x + GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h){
        pallet_cursor.map_x = pallet_cursor.map_x - GRID_SIZE;
    }

    return 0;

}
