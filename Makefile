all: map

map: initialize.o load_mapchip.o load_image.o
	gcc -g -o build/exec/MAPCreater src/main/main/c/main.c src/main/main/headers/main.h build/objects/*.o `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

initialize.o:
	gcc -g -c src/main/function/utils/c/initialize.c -o build/objects/initialize.o

load_mapchip.o:
	gcc -g -c src/main/function/load/c/load_mapchip.c -o build/objects/load_mapchip.o

load_image.o:
	gcc -g -c src/main/function/load/c/load_image.c -o build/objects/load_image.o

run:
	./build/exec/MAPCreater

clean:
	rm -f ./build/exec/MAPCreater
	rm -f ./build/objects/*.o
