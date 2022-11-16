#ifndef PARTS_H
#define PARTS_H

/*
 * macro definition
 */

/*
 * type definition
 */
typedef enum {WHITE, BLACK} COLOR;
typedef enum {CTRL_OFF, CTRL_ON} CTRL;
typedef enum {PALLET_DISPLAY_OFF, PALLET_DISPLAY_ON} PALLET_DISPLAY;
typedef enum {SHORT_SHARP_SELECTION_OFF, SHORT_SHARP_SELECTION_ON} SHORT_SHARP_SELECTION;

typedef struct {
    int map_x;
    int map_y;
    int offset_x;
    int offset_y;
} CURSOR;

typedef struct {
    int mapchip_id;
    char mapchip_name[256];
    int movable;
    int change_locate;
    SDL_Texture *map_image;
} MAPCHIP;


/*
 * prototype declaration
 */

/*
 * global variable external reference declaration
 */
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int IMAGE_WIDTH;
extern const int IMAGE_HEIGHT;
extern const int MAGNIFICATION;
extern const int GRID_SIZE;
extern const int PALLET_ROW;
extern const int PALLET_COL;
extern const int FONT_SIZE;

extern int ROW;
extern int COL;
extern int OUT_OF_MAP;
extern int OUTER_PERIPHERY;
extern char FILE_NAME[20];
extern int frame;
extern int SELECT_X;
extern int SELECT_Y;

extern int *map_array;
extern int *pallet_array;
extern int number_of_map_image;
extern int select_mapchip;

extern MAPCHIP mapchip[256];
extern CURSOR cursor;
extern CURSOR pallet_cursor;

extern CTRL ctrl;
extern PALLET_DISPLAY pallet_display;
extern SHORT_SHARP_SELECTION short_sharp_selection;

#endif
