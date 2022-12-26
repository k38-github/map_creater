#include <stdio.h>
#include "../headers/place_mapchip.h"

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
