CXX = g++

CXXSRC = *.cpp
OFILE = gtg.bin
SDLGFXDIR = SDL_gfx

build:
	make -C $(SDLGFXDIR)
	$(CXX) -I$(SDLGFXDIR) -L$(SDLGFXDIR) \
		-lSDL -lSDL_image -lSDL_gfx \
		$(CXXSRC) \
		-o $(OFILE)

clean:
	make -C $(SDLGFXDIR) clean
	rm $(OFILE)

run:
	LD_LIBRARY_PATH=$(SDLGFXDIR) ./$(OFILE)
