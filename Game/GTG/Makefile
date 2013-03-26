CC = g++
CFLAGS = -Wall -g
SDLFLAGS = -lSDL -lSDL_image

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

main.o :  main.cpp
	${CC} ${CFLAGS} -c main.cpp

game : main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o GTG.o
	${CC} ${CFLAGS} ${SDLFLAGS} main.o SDL_gfxPrimitives.o SDLHelper.o GTGTile.o GTGPlayer.o GTGMap.o GTG.o -o game
