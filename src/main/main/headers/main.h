#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../function/parts.h"
#include "../../function/utils/headers/initialize.h"

/*
 * macro definition
 */

#define FONT_PATH "src/resources/font/PixelMplus12-Bold.ttf"

/*
 * type definition
 */

/*
 * prototype declaration
 */
int initialize(SDL_Renderer *);
int accept_character_input(SDL_Event, SDL_Renderer *, TTF_Font *, char *, int, int);
int display_load_window(SDL_Event, SDL_Renderer *, TTF_Font *);
int display_save_window(SDL_Event, SDL_Renderer *, TTF_Font *);
int display_new_window(SDL_Event, SDL_Renderer *, TTF_Font *);
int display_character_string(SDL_Renderer *, TTF_Font *, char *, int, int);
int make_box(SDL_Renderer *, int, int, int, int, int, COLOR);
int load_file(char *);
int save_file(char *);
int pallet_move(SDL_Event, SDL_Renderer *);
int draw_coordinate(SDL_Renderer *, TTF_Font *);
int draw_filename(SDL_Window *);
int draw_outer_periphery(SDL_Renderer *, TTF_Font *);
int clac_offset(int, int, int *, int *);
int draw_map(SDL_Renderer *);
int draw_pallet(SDL_Renderer *);
int draw_selected_mapchip(SDL_Renderer *);
int draw_selected_outer_periphery(SDL_Renderer *);
int cursor_move(SDL_Event, SDL_Renderer *);
int place_mapchip(SDL_Point, SDL_Renderer *);
int place_mapchip_with_key(SDL_Renderer *);
int get_mapchip(SDL_Point, SDL_Renderer *);
int get_mapchip_right_click(SDL_Point, SDL_Renderer *);
int get_mapchip_with_key(SDL_Renderer *);
int get_mapchip_with_key_a(SDL_Renderer *);
int get_mapchip_with_key_o(SDL_Renderer *);
int initialize(SDL_Renderer *);

/*
 * global variable external reference declaration
 */

#endif
