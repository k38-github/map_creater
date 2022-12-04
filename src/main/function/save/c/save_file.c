#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/save_file.h"
#include "../../parts.h"

int save_file(char *file_name) {
    FILE *fp;
    char file[256] = {0};
    int i = 0;

    sprintf(FILE_NAME, "%s", file_name);
    while (FILE_NAME[i] != '\0') {
        FILE_NAME[i] = toupper((unsigned char)FILE_NAME[i]);
        i++;
    }

    char path_name[512];
    getcwd(path_name, 512);
    printf("current dir : %s\n", path_name);

    sprintf(file, "./%s.map", file_name);

    i = 0;
    while (file[i] != '\0') {
        file[i] = tolower((unsigned char)file[i]);
        i++;
    }

    if ((fp = fopen(file, "wb")) == NULL) {
        return 1;
    }

    fwrite(&COL, sizeof(int), 1, fp);
    fwrite(&ROW, sizeof(int), 1, fp);
    fwrite(&OUTER_PERIPHERY, sizeof(int), 1, fp);
    fwrite(map_array, sizeof(int) * COL * ROW, 1, fp);

    fclose(fp);

    return 0;
}
