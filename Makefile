PROGNAME := MAPCreater
MAINSRC := src/main/main/c/main.c
FUNCSRCDIR := src/main/function
OUTDIR := build/exec
OUTOBJSDIR := build/objects

TARGET := map
SRCS := $(wildcard $(FUNCSRCDIR)/*/c/*.c)
OBJFILE := $(notdir $(patsubst %.c,%.o,$(SRCS)))
OBJS := $(addprefix $(OUTOBJSDIR)/,$(OBJFILE))

CC = gcc
SDLLFGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

.PHONY: all build run clean
all: $(TARGET)

$(TARGET): $(OBJFILE)
	$(CC) -g -o $(OUTDIR)/$(PROGNAME) $(MAINSRC) $(OBJS) $(SDLLFGS)

$(OBJFILE): $(SRCS)

$(SRCS): build
	$(CC) -c $@ -o $(OUTOBJSDIR)/$(notdir $*).o

build:
	mkdir -p ./build/exec
	mkdir -p ./build/objects

run:
	./build/exec/MAPCreater

clean:
	rm -f ./build/exec/MAPCreater
	rm -rf ./build
