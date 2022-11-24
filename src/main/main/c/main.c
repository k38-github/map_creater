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
CURSOR cursor = {1, 1, 0, 0};
CURSOR pallet_cursor = {1, 1, 0, 0};

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

        clac_offset(cursor.map_x, cursor.map_y, &cursor.offset_x, &cursor.offset_y);
        clac_offset(pallet_cursor.map_x, pallet_cursor.map_y, &pallet_cursor.offset_x, &pallet_cursor.offset_y);

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

int place_mapchip(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    map_array[((cursor.offset_y + mouse_position.y) / GRID_SIZE)*COL +
              ((cursor.offset_x + mouse_position.x) / GRID_SIZE)] = select_mapchip;

    return 0;

}

int place_mapchip_with_key(SDL_Renderer *renderer) {

    int x, y;

    if (short_sharp_selection == SHORT_SHARP_SELECTION_OFF) {
        map_array[(cursor.map_y / GRID_SIZE) * COL +
                  (cursor.map_x / GRID_SIZE)] = select_mapchip;
    } else {
        if ((cursor.map_x/GRID_SIZE) - (SELECT_X/GRID_SIZE) < 0 &&
            (cursor.map_y/GRID_SIZE) - (SELECT_Y/GRID_SIZE) < 0 ) {
            for (x = cursor.map_x/GRID_SIZE;x <= SELECT_X/GRID_SIZE;x++) {
                for (y = cursor.map_y/GRID_SIZE;y <= SELECT_Y/GRID_SIZE;y++) {
                    map_array[y * COL + x] = select_mapchip;
                }
            }
        } else if ((cursor.map_x/GRID_SIZE) - (SELECT_X/GRID_SIZE) < 0 &&
                   (cursor.map_y/GRID_SIZE) - (SELECT_Y/GRID_SIZE) >= 0 ) {
            for (x = cursor.map_x/GRID_SIZE;x <= SELECT_X/GRID_SIZE;x++) {
                for (y = SELECT_Y/GRID_SIZE;y <= cursor.map_y/GRID_SIZE;y++) {
                    map_array[y * COL + x] = select_mapchip;
                }
            }
        } else if ((cursor.map_x/GRID_SIZE) - (SELECT_X/GRID_SIZE) >= 0 &&
                   (cursor.map_y/GRID_SIZE) - (SELECT_Y/GRID_SIZE) < 0 ) {
            for (x = SELECT_X/GRID_SIZE;x <= cursor.map_x/GRID_SIZE;x++) {
                for (y = cursor.map_y/GRID_SIZE;y <= SELECT_Y/GRID_SIZE;y++) {
                    map_array[y * COL + x] = select_mapchip;
                }
            }
        } else {
            for (x = SELECT_X/GRID_SIZE;x <= cursor.map_x/GRID_SIZE;x++) {
                for (y = SELECT_Y/GRID_SIZE;y <= cursor.map_y/GRID_SIZE;y++) {
                    map_array[y * COL + x] = select_mapchip;
                }
            }
        }

        short_sharp_selection = SHORT_SHARP_SELECTION_OFF;
    }

    return 0;

}

int get_mapchip(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    select_mapchip =
       pallet_array[((pallet_cursor.offset_y + mouse_position.y) / GRID_SIZE) * PALLET_COL +
                    ((pallet_cursor.offset_x + mouse_position.x) / GRID_SIZE)];

    return 0;

}

int get_mapchip_right_click(SDL_Point mouse_position, SDL_Renderer *renderer) {

    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    select_mapchip =
       map_array[((cursor.offset_y + mouse_position.y) / GRID_SIZE) * COL +
                    ((cursor.offset_x + mouse_position.x) / GRID_SIZE)];

    return 0;

}

int get_mapchip_with_key(SDL_Renderer *renderer) {

    select_mapchip =
       pallet_array[(pallet_cursor.map_y / GRID_SIZE) * PALLET_COL +
                    (pallet_cursor.map_x / GRID_SIZE)];

    return 0;

}

int get_mapchip_with_key_a(SDL_Renderer *renderer) {

    select_mapchip =
       map_array[(cursor.map_y / GRID_SIZE) * COL +
                    (cursor.map_x / GRID_SIZE)];

    return 0;

}

int get_mapchip_with_key_o(SDL_Renderer *renderer) {

    if (pallet_display == PALLET_DISPLAY_ON) {
        OUTER_PERIPHERY =
           pallet_array[(pallet_cursor.map_y / GRID_SIZE) * PALLET_COL +
                        (pallet_cursor.map_x / GRID_SIZE)];
    } else {
        OUTER_PERIPHERY =
           map_array[(cursor.map_y / GRID_SIZE) * COL +
                        (cursor.map_x / GRID_SIZE)];
    }

    return 0;

}

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

int clac_offset(int x, int y, int *offset_x, int *offset_y) {
    *offset_x = x - (SCREEN_WIDTH / 2);
    *offset_y = y - (SCREEN_HEIGHT / 2);

    return 0;
}

int save_file(char *file_name) {
    FILE *fp;
    char file[256] = {0};
    int i = 0;

    sprintf(FILE_NAME, "%s", file_name);
    while (FILE_NAME[i] != '\0') {
        FILE_NAME[i] = toupper((unsigned char)FILE_NAME[i]);
        i++;
    }

    sprintf(file, "data/%s.map", file_name);

    i = 0;
    while (file[i] != '\0') {
        file[i] = tolower((unsigned char)file[i]);
        i++;
    }

    if ((fp = fopen(file, "wb")) == NULL) {
        return 1;
    }

    fwrite(&COL, sizeof(int), 1, fp);
    fwrite(&ROW, sizeof(int), 1, fp);
    fwrite(&OUTER_PERIPHERY, sizeof(int), 1, fp);
    fwrite(map_array, sizeof(int) * COL * ROW, 1, fp);

    fclose(fp);

    return 0;
}

int load_file(char *file_name) {
    FILE *fp;
    char file[256] = {0};
    int i = 0;

    sprintf(file, "data/%s.map", file_name);

    while (file_name[i] != '\0') {
        file_name[i] = tolower((unsigned char)file_name[i]);
        i++;
    }

    if ((fp = fopen(file, "rb")) == NULL) {
        return 1;
    }

    sprintf(FILE_NAME, "%s", file_name);

    i = 0;
    while (FILE_NAME[i] != '\0') {
        FILE_NAME[i] = toupper((unsigned char)FILE_NAME[i]);
        i++;
    }

    fread(&COL, sizeof(int), 1, fp);
    fread(&ROW, sizeof(int), 1, fp);
    fread(&OUTER_PERIPHERY, sizeof(int), 1, fp);

    OUT_OF_MAP = 10;

    map_array = realloc(map_array, sizeof(int) * COL * ROW);

    i = 0;
    while(!feof(fp)) {
        fread(&map_array[i++], sizeof(int), 1, fp);
    }

    fclose(fp);

    return 0;
}

int display_new_window(SDL_Event e, SDL_Renderer *renderer, TTF_Font *font) {

    int i = 0;
    char file_name[21] = {0};
    char *status;
    long col;
    long row;
    char *endptr;

    make_box(renderer, 244, 296, 304, 32, 255, WHITE);
    make_box(renderer, 246, 298, 300, 28, 255, BLACK);

    display_character_string(renderer, font, "NEW? :", 250, 300);
    SDL_RenderPresent(renderer);

    if (accept_character_input(e, renderer, font, file_name, 316, 525) == 0) {

        sprintf(FILE_NAME, "%s", file_name);
        while (FILE_NAME[i] != '\0') {
            FILE_NAME[i] = toupper((unsigned char)FILE_NAME[i]);
            i++;
        }

        memset(file_name, '\0', 21);

        make_box(renderer, 244, 296, 304, 32, 255, WHITE);
        make_box(renderer, 246, 298, 300, 28, 255, BLACK);

        display_character_string(renderer, font, "COL? :", 250, 300);
        SDL_RenderPresent(renderer);

        accept_character_input(e, renderer, font, file_name, 316, 525);

        col = strtol(file_name, &endptr, 10);
        if (file_name == endptr) {
           puts("could not convert to number");
        }

        if (col > INT_MAX || col < INT_MIN) {
           puts("can not convert to int type");
        }
        COL = (int)col;

        memset(file_name, '\0', 21);

        make_box(renderer, 244, 296, 304, 32, 255, WHITE);
        make_box(renderer, 246, 298, 300, 28, 255, BLACK);

        display_character_string(renderer, font, "ROW? :", 250, 300);
        SDL_RenderPresent(renderer);

        accept_character_input(e, renderer, font, file_name, 316, 525);

        row = strtol(file_name, &endptr, 10);
        if (file_name == endptr) {
           puts("could not convert to number");
        }

        if (row > INT_MAX || row < INT_MIN) {
           puts("can not convert to int type");
        }
        ROW = (int)row;


        map_array = realloc(map_array, sizeof(int) * COL * ROW);

        int i;
        for (i=0;i <= COL*ROW;i++) {
            map_array[i] = 1;
        }

    }


    return 0;
}

int display_save_window(SDL_Event e, SDL_Renderer *renderer, TTF_Font *font) {

    char file_name[21] = {0};
    char *status;
    char *endptr;

    make_box(renderer, 244, 296, 304, 32, 255, WHITE);
    make_box(renderer, 246, 298, 300, 28, 255, BLACK);

    display_character_string(renderer, font, "SAVE?:", 250, 300);

    // FONT_SIZE 22 ,11pt

    SDL_RenderPresent(renderer);

    sprintf(file_name, "%s", FILE_NAME);
    if (accept_character_input(e, renderer, font, file_name, 316, 525) == 0) {

        make_box(renderer, 244, 296, 304, 32, 255, WHITE);
        make_box(renderer, 246, 298, 300, 28, 255, BLACK);

        if(save_file(file_name) == 0) {
            status = "SAVED!";
        } else {
            status = "SAVING FAILD";
        }

        while(1) {
            make_box(renderer, 244, 296, 304, 32, 255, WHITE);
            make_box(renderer, 246, 298, 300, 28, 255, BLACK);
            display_character_string(renderer, font, status, 250, 300);
            SDL_RenderPresent(renderer);

            if ( SDL_PollEvent(&e) ) {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                    break;
                }
            }
        }
    }

    return 0;
}

int display_load_window(SDL_Event e, SDL_Renderer *renderer, TTF_Font *font) {

    char file_name[21] = {0};
    char *status;

    make_box(renderer, 244, 296, 304, 32, 255, WHITE);
    make_box(renderer, 246, 298, 300, 28, 255, BLACK);

    display_character_string(renderer, font, "LOAD?:", 250, 300);

    // FONT_SIZE 22 ,11pt

    SDL_RenderPresent(renderer);

    if (accept_character_input(e, renderer, font, file_name, 316, 525) == 0) {

        if(load_file(file_name) == 0) {
            status = "LOADED!";
        } else {
            status = "LOADING FAILD";
        }

        while(1) {
            make_box(renderer, 244, 296, 304, 32, 255, WHITE);
            make_box(renderer, 246, 298, 300, 28, 255, BLACK);
            display_character_string(renderer, font, status, 250, 300);
            SDL_RenderPresent(renderer);

            if ( SDL_PollEvent(&e) ) {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                    break;
                }
            }
        }
    }

    return 0;
}

int accept_character_input(SDL_Event e, SDL_Renderer *renderer, TTF_Font *font,
                           char *file_name, int start_pt, int end_pt) {
    char buf[21] = {0};
    int pt = start_pt;
    int file_name_element = 0;
    int i;

    for(i=0;(int)strlen(file_name)>i;i++) {
        display_character_string(renderer, font, &file_name[i], pt, 300);
        pt = pt + 11;
        file_name_element++;
    }

    while(1) {

        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                return 1;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                break;
            }

            if (pt <= end_pt) {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a) {
                    display_character_string(renderer, font, "A", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "a");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b) {
                    display_character_string(renderer, font, "B", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "b");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c) {
                    display_character_string(renderer, font, "C", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "c");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d) {
                    display_character_string(renderer, font, "D", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "d");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e) {
                    display_character_string(renderer, font, "E", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "e");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f) {
                    display_character_string(renderer, font, "F", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "f");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_g) {
                    display_character_string(renderer, font, "G", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "g");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h) {
                    display_character_string(renderer, font, "H", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "h");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_i) {
                    display_character_string(renderer, font, "I", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "i");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_j) {
                    display_character_string(renderer, font, "J", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "j");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_k) {
                    display_character_string(renderer, font, "K", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "k");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l) {
                    display_character_string(renderer, font, "L", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "l");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m) {
                    display_character_string(renderer, font, "M", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "m");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) {
                    display_character_string(renderer, font, "N", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "n");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o) {
                    display_character_string(renderer, font, "O", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "o");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {
                    display_character_string(renderer, font, "P", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "p");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q) {
                    display_character_string(renderer, font, "Q", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "q");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                    display_character_string(renderer, font, "R", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "r");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s) {
                    display_character_string(renderer, font, "S", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "s");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t) {
                    display_character_string(renderer, font, "T", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "t");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_u) {
                    display_character_string(renderer, font, "U", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "u");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_v) {
                    display_character_string(renderer, font, "V", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "v");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w) {
                    display_character_string(renderer, font, "W", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "w");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x) {
                    display_character_string(renderer, font, "X", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "x");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_y) {
                    display_character_string(renderer, font, "Y", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "y");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_z) {
                    display_character_string(renderer, font, "Z", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "z");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_0) {
                    display_character_string(renderer, font, "0", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "0");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1) {
                    display_character_string(renderer, font, "1", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "1");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2) {
                    display_character_string(renderer, font, "2", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "2");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3) {
                    display_character_string(renderer, font, "3", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "3");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4) {
                    display_character_string(renderer, font, "4", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "4");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5) {
                    display_character_string(renderer, font, "5", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "5");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6) {
                    display_character_string(renderer, font, "6", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "6");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7) {
                    display_character_string(renderer, font, "7", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "7");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8) {
                    display_character_string(renderer, font, "8", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "8");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_9) {
                    display_character_string(renderer, font, "9", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "9");
                    file_name_element++;
                } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SLASH) {
                    display_character_string(renderer, font, "_", pt, 300);
                    pt = pt + 11;
                    strcat(file_name, "_");
                    file_name_element++;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE) {
                if (start_pt < pt) {
                    make_box(renderer, pt - 11, 301, 11, 22, 255, BLACK);
                    pt = pt - 11;

                    file_name_element--;
                    strncpy(buf, file_name, file_name_element);
                    memset(file_name, '\0', 20);
                    sprintf(file_name, "%s", buf);
                    memset(buf, '\0', 20);
                }
            }
        }

        SDL_RenderPresent(renderer);

    }

    return 0;
}
