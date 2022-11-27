#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../function/parts.h"
#include "../../function/utils/headers/accept_character_input.h"
#include "../../function/utils/headers/calc_offset.h"
#include "../../function/utils/headers/initialize.h"
#include "../../function/utils/headers/make_box.h"
#include "../../function/utils/headers/pallet_move.h"
#include "../../function/draw/headers/draw_coodinate.h"
#include "../../function/draw/headers/draw_filename.h"
#include "../../function/draw/headers/draw_map.h"
#include "../../function/draw/headers/draw_outer_periphery.h"
#include "../../function/draw/headers/draw_pallet.h"
#include "../../function/draw/headers/draw_selected_mapchip.h"
#include "../../function/draw/headers/draw_selected_outer_periphery.h"
#include "../../function/display/headers/display_character_string.h"
#include "../../function/display/headers/display_load_window.h"
#include "../../function/display/headers/display_new_window.h"
#include "../../function/display/headers/display_save_window.h"

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
int cursor_move(SDL_Event, SDL_Renderer *);
int place_mapchip(SDL_Point, SDL_Renderer *);
int place_mapchip_with_key(SDL_Renderer *);
int get_mapchip(SDL_Point, SDL_Renderer *);
int get_mapchip_right_click(SDL_Point, SDL_Renderer *);
int get_mapchip_with_key(SDL_Renderer *);
int get_mapchip_with_key_a(SDL_Renderer *);
int get_mapchip_with_key_o(SDL_Renderer *);

/*
 * global variable external reference declaration
 */

#endif
