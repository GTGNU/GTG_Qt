#include "GTG.h"
#include "SDLHelper.h"
#include "SDL_gfxPrimitives.h"

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time = 0);

int main(int argc, char* args[])
{
    SDLInit();
    GTG gtg;
    gtg.Construct();

    // Set window title
    SDL_WM_SetCaption("GTG - maps", "GTG");

    // Run the game
    if( !gtg.Load("res") )
        Popup(gtg.GetLastError(),0xFF0000FF,0x000000FF);
     else
         if( !gtg.Run() )
            Popup(gtg.GetLastError(),0xFF0000FF,0x000000FF);
         else
            Popup("Game finished",0x0000FFFF,0xFFFFFFFF);

    // Exit game
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

        if(time > 0)
            if(timer.total > time)
                run = false;
        
        boxColor(screen,0,0,screen->w,screen->h,backColor);
        stringColor(screen,(screen->w/2)-(textLen*4),screen->h/2 - 4,text,txtColor);
        SDL_Flip(screen);
    }
}
