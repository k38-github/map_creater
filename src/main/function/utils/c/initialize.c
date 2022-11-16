#include <stdio.h>
#include "../../load/headers/load_mapchip.h"
#include "../../parts.h"

/*
 * private macro definition
 */

/*
 * global variable definition
 */

int initialize(SDL_Renderer *renderer) {


    map_array = malloc(sizeof(int) * COL * ROW);
    pallet_array = malloc(sizeof(int) * PALLET_COL * PALLET_ROW);

    load_mapchip(renderer);

    int i;
    for (i=0;i <= COL*ROW;i++) {
        map_array[i] = 1;
    }

    return 0;
}
