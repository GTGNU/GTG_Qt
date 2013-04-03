#include "GTG.h"

#include "SDLHelper.h"
#include "SDL_gfxPrimitives.h"

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time = 0);

int main(int argc, char* args[])
{
    SDLInit();
    SDL_WM_SetCaption("GTG - maps","GTG");

    GTG gtg;
    gtg.Construct();
    if(!gtg.Load("res")) {
        Popup(gtg.GetLastError(),0xFF0000FF,0x000000FF);
    } else {
        int res = gtg.Run();
        if(res < 0) {
            Popup(gtg.GetLastError(),0xFF0000FF,0x000000FF);
        } else if(res == 0) {
            Popup("Game finished",0x0000FFFF,0xFFFFFFFF);
        }
    }
    gtg.Destruct();

    SDLExit();
    return 0;
}

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time)
{
    SDLTimer timer;
    SDL_Event SDLEvent;
    bool run = true;
    Uint16 textLen = strlen(text);
    SDLSetVideo(800,200,false);
    SDL_ShowCursor(SDL_ENABLE);
    timer.Reset();
    while(run) {
        while(SDL_PollEvent(&SDLEvent)) {
            switch(SDLEvent.type) {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                if(SDLEvent.key.keysym.sym == SDLK_ESCAPE)run = false;
                break;
            }
        }
        timer.Frame(15);
        if(time > 0)if(timer.total > time)run = false;
        boxColor(screen,0,0,screen->w,screen->h,backColor);
        stringColor(screen,(screen->w/2)-(textLen*4),screen->h/2 - 4,text,txtColor);
        SDL_Flip(screen);
    }
}
