#include <stdio.h>
#include "../headers/cursor_move.h"
#include "../headers/make_box.h"

int cursor_move(SDL_Event e, SDL_Renderer *renderer) {

    int cursor_x = cursor.map_x - cursor.offset_x;
    int cursor_y = cursor.map_y - cursor.offset_y;

    int short_sharp_x = SELECT_X - cursor.offset_x;
    int short_sharp_y = SELECT_Y - cursor.offset_y;

    int range_x = 0;
    int range_y = 0;

    if (short_sharp_selection == SHORT_SHARP_SELECTION_ON) {
        if (cursor_x - short_sharp_x < 0) {
            short_sharp_x = short_sharp_x + GRID_SIZE;
            range_x = cursor_x - short_sharp_x;
        } else {
            range_x = cursor_x - short_sharp_x + GRID_SIZE;
        }

        if (cursor_y - short_sharp_y < 0) {
            short_sharp_y = short_sharp_y + GRID_SIZE;
            range_y = cursor_y - short_sharp_y;
        } else {
            range_y = cursor_y - short_sharp_y + GRID_SIZE;
        }

        make_box(renderer, short_sharp_x, short_sharp_y,range_x, range_y, 100, BLACK);
    } else {
        make_box(renderer, cursor_x, cursor_y, GRID_SIZE, GRID_SIZE, 100, BLACK);
    }

    if (frame % 5 == 0) {

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP){
            cursor.map_y = cursor.map_y - GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN){
            cursor.map_y = cursor.map_y + GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){
            cursor.map_x = cursor.map_x + GRID_SIZE;
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){
            cursor.map_x = cursor.map_x - GRID_SIZE;
        }

     }

    if (frame <= 10000) {
        frame++;
    } else {
        frame = 0;
    }

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_k){
        cursor.map_y = cursor.map_y - GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_j){
        cursor.map_y = cursor.map_y + GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l){
        cursor.map_x = cursor.map_x + GRID_SIZE;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h){
        cursor.map_x = cursor.map_x - GRID_SIZE;
    }

    return 0;

}
