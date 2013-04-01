CC = g++
CFLAGS = -Wall -g
SDLFLAGS = `sdl-config --libs` -lSDL_image

all : main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o GTG.o
	${CC} ${CFLAGS} main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o GTG.o ${SDLFLAGS} -o game

GTG.o : GTG.cpp GTG.h
	${CC} ${CFLAGS} -c GTG.cpp

GTGMap.o : GTGMap.cpp GTGMap.h
	${CC} ${CFLAGS} -c GTGMap.cpp

GTGPlayer.o :  GTGPlayer.cpp GTGPlayer.h
	${CC} ${CFLAGS} -c GTGPlayer.cpp

GTGTile.o :  GTGTile.cpp GTGTile.h
	${CC} ${CFLAGS} -c GTGTile.cpp

SDLHelper.o :  SDLHelper.cpp SDLHelper.h
	${CC} ${CFLAGS} -c SDLHelper.cpp

SDL_gfxPrimitives.o :  SDL_gfxPrimitives.c SDL_gfxPrimitives.h
	${CC} ${CFLAGS} -c SDL_gfxPrimitives.c

main.o :	main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o GTG.o game

.PHONY: clean
