#include "GTGTile.h"
#include "GTGMap.h"

#include "SDLHelper.h"
#include "SDL_gfxPrimitives.h"

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time = 0);

int main(int argc, char* args[]){
  SDLInit();
  SDLSetVideo(800,600,true,false);
  SDL_WM_SetCaption("GTG - player","GTG");

  bool run = true; SDLTimer timer; SDLEvents events; SDL_Event SDLEvent;
  int ret = 0;

  GTGTileSet tileSet;
  ret = tileSet.Load("map");
  if(ret < 0){
    Popup(tileSet.GetLastError(),0xFF0000FF,0x000000FF);
    return 0;
  }else if(ret == 0){
    Popup("0 tiles loaded",0xFF0000FF,0x000000FF);
    return 0;
  }

  GTGMap map;
  if(!map.Load("map",&tileSet)){
    Popup(map.GetLastError(),0xFF0000FF,0x000000FF);
    return 0;
  }

  boxColor(screen,0,0,screen->w,screen->h,0xF0F0F0FF);
  while(run){
    timer.Frame();
    while(SDL_PollEvent(&SDLEvent)){
      switch(SDLEvent.type){
      case SDL_QUIT: run = false; break;
      case SDL_VIDEORESIZE:
        SDLSetVideo(SDLEvent.resize.w,SDLEvent.resize.h,true,false);
        boxColor(screen,0,0,screen->w,screen->h,0xF0F0F0FF);
        break;
      case SDL_KEYDOWN:
        if(SDLEvent.key.keysym.sym == SDLK_ESCAPE)run = false;
        break;
      }
      events.HandleEvent(&SDLEvent);
    }

    if(events.keys[SDLK_w])map.player.GoUp(&timer);
    if(events.keys[SDLK_a])map.player.GoLeft(&timer);
    if(events.keys[SDLK_s])map.player.GoDown(&timer);
    if(events.keys[SDLK_d])map.player.GoRight(&timer);

    tileSet.Frame(&timer);
    map.Frame(&timer,50,50,screen->w-50,screen->h-50);

    //boxColor(screen,0,0,screen->w,screen->h,0xF0F0F0FF);
    boxColor(screen,0,screen->h-50,screen->w,screen->h,0xF0F0F0FF);
    map.Draw(screen,50,50,screen->w-50,screen->h-50);
    char txt[255]; sprintf(txt,"FPS %.2f TIME %d",timer.fps,timer.time); stringColor(screen,2,screen->h-10,txt,0xFF0000FF);
    SDL_Flip(screen);
  }

  SDLExit(); return 0;
}

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time){
  SDLTimer timer; SDL_Event SDLEvent;
  bool run = true; Uint16 textLen = strlen(text);
  SDLSetVideo(800,200,false);
  SDL_ShowCursor(SDL_ENABLE);
  timer.Reset();
  while(run){
    while(SDL_PollEvent(&SDLEvent)){
      switch(SDLEvent.type){
      case SDL_QUIT: run = false; break;
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
