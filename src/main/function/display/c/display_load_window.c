#include <stdio.h>
#include "../headers/display_load_window.h"
#include "../headers/display_character_string.h"
#include "../../load/headers/load_file.h"
#include "../../utils/headers/accept_character_input.h"
#include "../../utils/headers/make_box.h"
#include "../../parts.h"

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

