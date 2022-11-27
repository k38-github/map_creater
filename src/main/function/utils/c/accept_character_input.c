#include <stdio.h>
#include "../../display/headers/display_character_string.h"
#include "../../utils/headers/make_box.h"
#include "../../parts.h"

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
