#include <stdio.h>
#include <limits.h>
#include "../headers/display_character_string.h"
#include "../../utils/headers/accept_character_input.h"
#include "../../utils/headers/make_box.h"
#include "../../parts.h"

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
