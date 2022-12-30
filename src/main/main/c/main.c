#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../headers/main.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_WIDTH = 16;
const int IMAGE_HEIGHT = 16;
const int MAGNIFICATION = 2;
const int GRID_SIZE = 32;
const int PALLET_ROW = 15;
const int PALLET_COL = 20;
const int FONT_SIZE = 22;

int ROW = 15;
int COL = 20;
int OUT_OF_MAP = 10;
int OUTER_PERIPHERY = 1;
char FILE_NAME[20] = "NEW";
int frame = 0;
int SELECT_X = 0;
int SELECT_Y = 0;

int *map_array;
int *pallet_array;
int number_of_map_image = 0;
int select_mapchip = 0;

MAPCHIP mapchip[256] = {0};
CURSOR cursor = {0, 0, 0, 0};
CURSOR pallet_cursor = {0, 0, 0, 0};

CTRL ctrl = CTRL_OFF;
PALLET_DISPLAY pallet_display = PALLET_DISPLAY_OFF;
SHORT_SHARP_SELECTION short_sharp_selection = SHORT_SHARP_SELECTION_OFF;


int main (int argc, char *argv[]) {

    int IMAGE_WIDTH_SENTER = IMAGE_WIDTH * MAGNIFICATION / 2;
    int IMAGE_HEIGHT_SENTER = IMAGE_HEIGHT * MAGNIFICATION / 2;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    // ウィンドウの位置
    SDL_Point window_position = {
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    };

    // ウィンドウのサイズ
    SDL_Point window_size = {SCREEN_WIDTH, SCREEN_HEIGHT};

    // マウスの座標
    SDL_Point mouse_position = {IMAGE_WIDTH_SENTER, IMAGE_WIDTH_SENTER};

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    window = SDL_CreateWindow( "MAP CREATER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    //Initialize TTF
    if ( TTF_Init() < 0 ) {
        printf("TTFcould not initialize! TTF_Error: %s\n", TTF_GetError());
    }

    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if ( font == NULL ) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    initialize(renderer);

    // main loop
    while (1) {

        SDL_Delay(10);

        SDL_Event e;

        calc_offset(cursor.map_x, cursor.map_y, &cursor.offset_x, &cursor.offset_y);
        calc_offset(pallet_cursor.map_x, pallet_cursor.map_y, &pallet_cursor.offset_x, &pallet_cursor.offset_y);

        SDL_RenderClear(renderer);
        if (pallet_display == PALLET_DISPLAY_ON) {
            draw_pallet(renderer);
            pallet_move(e, renderer);
        } else {
            draw_map(renderer);
            cursor_move(e, renderer);
        }

        draw_selected_mapchip(renderer);
        draw_selected_outer_periphery(renderer);

        draw_coordinate(renderer, font);
        draw_filename(window);
        draw_outer_periphery(renderer, font);

        SDL_RenderPresent(renderer);

        // event handling
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT) {
                break;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (short_sharp_selection == SHORT_SHARP_SELECTION_ON) {
                    short_sharp_selection = SHORT_SHARP_SELECTION_OFF;
                } else {
                    break;
                }
            } else if (e.type == SDL_KEYDOWN &&
                      (e.key.keysym.sym == SDLK_RCTRL || e.key.keysym.sym == SDLK_LCTRL)) {
                ctrl = CTRL_ON;
            } else if (e.type == SDL_KEYUP &&
                      (e.key.keysym.sym == SDLK_RCTRL || e.key.keysym.sym == SDLK_LCTRL)) {
                ctrl = CTRL_OFF;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s) {
                if (ctrl == CTRL_ON) {
                    ctrl = CTRL_OFF;
                    display_save_window(e, renderer, font);
                }
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l) {
                if (ctrl == CTRL_ON) {
                    ctrl = CTRL_OFF;
                    display_load_window(e, renderer, font);
                }
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) {
                if (ctrl == CTRL_ON) {
                    ctrl = CTRL_OFF;
                    display_new_window(e, renderer, font);
                }
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_v) {
                if (ctrl == CTRL_ON) {
                    ctrl = CTRL_OFF;
                    short_sharp_selection = SHORT_SHARP_SELECTION_ON;
                    SELECT_X = cursor.map_x;
                    SELECT_Y = cursor.map_y;
                }
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_i) {
                if (pallet_display == PALLET_DISPLAY_OFF) {
                    pallet_display = PALLET_DISPLAY_ON;
                } else {
                    pallet_display = PALLET_DISPLAY_OFF;
                }
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a &&
                       pallet_display == PALLET_DISPLAY_OFF) {
                get_mapchip_with_key_a(renderer);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o) {
                get_mapchip_with_key_o(renderer);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE &&
                       pallet_display == PALLET_DISPLAY_ON) {
                get_mapchip_with_key(renderer);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE &&
                       pallet_display == PALLET_DISPLAY_OFF) {
                place_mapchip_with_key(renderer);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT &&
                       pallet_display == PALLET_DISPLAY_ON) {
                get_mapchip(mouse_position, renderer);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT &&
                       pallet_display == PALLET_DISPLAY_OFF) {
                place_mapchip(mouse_position, renderer);
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT &&
                       pallet_display == PALLET_DISPLAY_OFF) {
                get_mapchip_right_click(mouse_position, renderer);
            }
        }

    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    int i;
    for (i = 0;i < number_of_map_image;i++) {
        SDL_DestroyTexture(mapchip[i].map_image);
    }

    SDL_Quit();

    return 0;

}
