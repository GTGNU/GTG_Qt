#include "GTG.h"

GTG::GTG(){ Construct(); }
GTG::~GTG(){ Destruct(); }

void GTG::Construct(){
  tileset.Construct();
  map.Construct();

  memset(error,0,128); sprintf(error,"No error");
}

void GTG::Destruct(){
  Free();
  Construct();
}

void GTG::Free(){
  tileset.Free();
  map.Clear();
}

int GTG::Run(){

  Uint32 cameraMoveSpeed = 200;

  if((map.width <= 0)||(map.height <= 0)){ sprintf(error,"No loaded map"); return -1; }
  SDLSetVideo(800,600,true,false);
  //SDL_ShowCursor(SDL_DISABLE);
  int run = 0; SDLTimer timer; SDLEvents events; SDL_Event SDLEvent;

  int offX = screen->w/2 - (map.width *map.spaceX*0.5);
  int offY = screen->h/2 - (map.height*map.spaceY*0.5);

  float cameraX, cameraY, cameraTargetX, cameraTargetY, cameraFromX, cameraFromY; Uint32 cameraTime = 0;
  cameraX = 0; cameraTargetX = 0; cameraFromX = 0;
  cameraY = 0; cameraTargetY = 0; cameraFromY = 0;

  while(run == 0){
    timer.Frame();
    while(SDL_PollEvent(&SDLEvent)){
      switch(SDLEvent.type){
      case SDL_QUIT: run = 1; break;
      case SDL_VIDEORESIZE:
        SDLSetVideo(SDLEvent.resize.w,SDLEvent.resize.h,true,false);
        offX = screen->w/2 - (map.width *map.spaceX*0.5);
        offY = screen->h/2 - (map.height*map.spaceY*0.5);
        break;
      case SDL_KEYDOWN:
        if(SDLEvent.key.keysym.sym == SDLK_ESCAPE)run = 1;
        break;
      }
      events.HandleEvent(&SDLEvent);
    }

    tileset.Frame();
    map.Frame(&timer);
    map.player.Frame(&timer,events.keys[SDLK_a],events.keys[SDLK_d],events.keys[SDLK_w],events.keys[SDLK_s],&map);

    int px, py;
    boxColor(screen,0,0,screen->w,screen->h,map.backgroundColor);
    for(size_t x = 0; x<map.backTiles.size(); x++){
      for(size_t y = 0; y<map.backTiles.size(); y++){
        px = ((int)x*map.spaceX) + offX + (int)cameraX;
        py = ((int)y*map.spaceY) + offY + (int)cameraY;
        if((px + map.spaceX <= 0)||(px >= screen->w))continue;
        if((py + map.spaceY <= 0)||(py >= screen->h))continue;
        SDLBlit(map.backTiles.at(x).at(y).tile->GetSurface(),screen,px,py,map.spaceX,map.spaceY);
      }
    }
    px = map.player.drawX*map.spaceX + offX + cameraTargetX;
    py = map.player.drawY*map.spaceX + offY + cameraTargetY;
    if(px<(int)map.spaceX){ cameraTargetX += map.spaceX*2; cameraTime = timer.now; cameraFromX = cameraX; cameraFromY = cameraY; } if(px>screen->w-(int)map.spaceX){ cameraTargetX -= map.spaceX*2; cameraTime = timer.now; cameraFromX = cameraX; cameraFromY = cameraY; }
    if(py<(int)map.spaceY){ cameraTargetY += map.spaceY*2; cameraTime = timer.now; cameraFromX = cameraX; cameraFromY = cameraY; } if(py>screen->h-(int)map.spaceY){ cameraTargetY -= map.spaceY*2; cameraTime = timer.now; cameraFromX = cameraX; cameraFromY = cameraY; }
    SDLBlit(map.player.currentTile->GetSurface(),screen,px-cameraTargetX+cameraX,py-cameraTargetY+cameraY);

    if(timer.now - cameraTime > cameraMoveSpeed){
      cameraX = cameraTargetX; cameraY = cameraTargetY;
    }else{
      float d = (float)(timer.now - cameraTime)/cameraMoveSpeed;
      if(d > 1.)d = 1.;
      cameraX = cameraFromX + (cameraTargetX - cameraFromX)*d;
      cameraY = cameraFromY + (cameraTargetY - cameraFromY)*d;
    }

    char txt[255]; sprintf(txt,"FPS %.2f",timer.fps); stringColor(screen,2,screen->h-10,txt,0xFF0000FF);
    SDL_Flip(screen);
  }

  return run;
}

bool GTG::Load(const char *root){

  Free();

  int res = tileset.Load(root,"tiles.txt");
  if(res < 0){
    sprintf(error,"%s",tileset.GetLastError());
    return false;
  }else if(res == 0){
    sprintf(error,"%s/tiles.txt: No tiles",root);
    return false;
  }

  if(!map.Load(root,"map.txt",&tileset)){
    sprintf(error,"%s",map.GetLastError());
    Free();
    return false;
  }

  return true;
}



const char* GTG::GetLastError(){
  return error;
}