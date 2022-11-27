#include <stdio.h>
#include "../headers/load_file.h"
#include "../../parts.h"

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
