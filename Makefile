all: map

map: initialize.o load_mapchip.o load_image.o draw_map.o draw_pallet.o draw_coodinate.o display_character_string.o
	gcc -g -o build/exec/MAPCreater src/main/main/c/main.c src/main/main/headers/main.h build/objects/*.o `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

initialize.o: build
	gcc -g -c src/main/function/utils/c/initialize.c -o build/objects/initialize.o

load_mapchip.o: build
	gcc -g -c src/main/function/load/c/load_mapchip.c -o build/objects/load_mapchip.o

load_image.o: build
	gcc -g -c src/main/function/load/c/load_image.c -o build/objects/load_image.o

draw_map.o: build
	gcc -g -c src/main/function/draw/c/draw_map.c -o build/objects/draw_map.o

draw_pallet.o: build
	gcc -g -c src/main/function/draw/c/draw_pallet.c -o build/objects/draw_pallet.o

draw_coodinate.o: build
	gcc -g -c src/main/function/draw/c/draw_coodinate.c -o build/objects/draw_coodinate.o

display_character_string.o: build
	gcc -g -c src/main/function/display/c/display_character_string.c -o build/objects/display_character_string.o

build:
	mkdir -p ./build/exec
	mkdir -p ./build/objects

run:
	./build/exec/MAPCreater

clean:
	rm -f ./build/exec/MAPCreater
	rm -rf ./build
