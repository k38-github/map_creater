#include <stdio.h>
#include "../headers/draw_filename.h"
#include "../../parts.h"

int draw_filename(SDL_Window *window) {
    char title_name[256] = {0};

    sprintf(title_name, "MAP CREATER(%s)", FILE_NAME);
    SDL_SetWindowTitle(window, title_name);

    return 0;

}

