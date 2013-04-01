CC = g++
CFLAGS = -Wall -g
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf

all : main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o SDLGuiStyle.o SDLGui.o
	${CC} ${CFLAGS} ${SDLFLAGS} main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o SDLGuiStyle.o SDLGui.o -o editor

GTGMap.o : GTGMap.cpp GTGMap.h
	${CC} ${CFLAGS} -c GTGMap.cpp

GTGPlayer.o :  GTGPlayer.cpp GTGPlayer.h
	${CC} ${CFLAGS} -c GTGPlayer.cpp

GTGTile.o :  GTGTile.cpp GTGTile.h
	${CC} ${CFLAGS} -c GTGTile.cpp

SDLHelper.o :  SDLHelper.cpp SDLHelper.h
	${CC} ${CFLAGS} -c SDLHelper.cpp

SDL_gfxPrimitives.o :  SDL_gfxPrimitives.c SDL_gfxPrimitives.h SDL_gfxPrimitives_font.h
	${CC} ${CFLAGS} -c SDL_gfxPrimitives.c

SDLGuiStyle.o : SDLGuiStyle.cpp
	${CC} ${CFLAGS} -c SDLGuiStyle.cpp

SDLGui.o : SDLGui.cpp SDLGui.h
	${CC} ${CFLAGS} -c SDLGui.cpp

main.o :	main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o SDLGuiStyle.o SDLGui.o editor

.PHONY: clean
