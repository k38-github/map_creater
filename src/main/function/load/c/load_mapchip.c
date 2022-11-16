#include <stdio.h>
#include "../headers/load_image.h"
#include "../../parts.h"

int load_mapchip(SDL_Renderer *renderer) {

    FILE *fp;
    int x, y, z;
    char n[256];
    char path[320];
    char buf[256];
    int i = 0;

    fp = fopen("src/resources/dat/mapchip.dat", "r");
    if (fp == NULL) {
        printf("file open error. %d\n", __LINE__);
        return 1;
    }

    for(i = 0;fgets(buf, sizeof(buf), fp) != NULL;i++){
        if (strncmp(buf, "#", 1) != 0){
            sscanf(buf, "%d,%[^,],%d,%d", &x, n, &y, &z);
            mapchip[i].mapchip_id = x;
            strcpy(mapchip[i].mapchip_name, n);
            mapchip[i].movable = y;
            mapchip[i].change_locate = z;

            sprintf(path, "src/resources/image/mapchip/%s.bmp", mapchip[i].mapchip_name);
            load_image(renderer, &mapchip[i].map_image, path);

            pallet_array[i] = x;
        } else {
            i--;
        }
    }

    number_of_map_image = i - 1;

    fclose(fp);

    return 0;

}
