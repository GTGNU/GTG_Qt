#include "GTGMap.h"
#include "GTGTile.h"

GTGMap::GTGMap(){ Construct(); }
GTGMap::~GTGMap(){ Destruct(); }

void GTGMap::Construct(){
  memset(error,0,128); sprintf(error,"No error");
  tiles.clear();
  spaceX = 16; spaceY = 16; width = 0; height = 0;
  backgroundColor = 0xFFFFFFFF;
  player.Construct();
  cameraX = 0; cameraY = 0; camTargetX = 0; camTargetY = 0; camTime = 0;
}

void GTGMap::Destruct(){
  Clear();
  Construct();
}

void GTGMap::Clear(){
  for(size_t n = 0; n<tiles.size(); n++)tiles.at(n).clear();
  tiles.clear();
  spaceX = 16; spaceY = 16; width = 0; height = 0;
  player.Destruct();
}

const char* GTGMap::GetLastError(){
  return error;
}

bool GTGMap::Load(const char *root, GTGTileSet *tileSet){
  char path[128], line[512];
  size_t lineCount = 0;

  Clear();

  if(!player.Load(root,tileSet)){
    sprintf(error,"%s",player.GetLastError());
    Clear();
    return false;
  }

  sprintf(path,"%s/map.txt",root);
  FILE *file = fopen(path,"rt");
  if(file == NULL){
    sprintf(error,"Could not open %s for reading",path);
    Clear();
    return false;
  }
  lineCount = 0;
  while(!feof(file)){
    size_t pos = 0;
    while(true){
      int c = fgetc(file);
      if((c == EOF)||(c == '\n'))break;
      line[pos] = (char)c;
      pos++;
    }
    line[pos] = 0;
    lineCount++;
    if(pos == 0)continue;
    if(lineCount == 1){
      int w, h, sx, sy;
      if(sscanf(line,"%d %d %d %d",&w,&h,&sx,&sy) != 4){
        Clear();
        sprintf(error,"First line in map.txt must have 4 numbers");
        fclose(file);
        return false;
      }
      if((w < 2)||(h < 2)||(sx < 2)||(sy < 2)){
        Clear();
        sprintf(error,"All 4 numbers on first line in map.txt must be positive");
        fclose(file);
        return false;
      }
      tiles.resize(w);
      for(size_t n = 0; n<tiles.size(); n++){
        tiles.at(n).resize(h);
        for(size_t m = 0; m<tiles.at(n).size(); m++)tiles.at(n).at(m) = NULL;
      }
      width = w;
      height = h;
      spaceX = sx;
      spaceY = sy;
    }else{
      size_t size = pos, n = 0, last = 0; pos = 0;
      while(true){
        while((pos < size)&&(line[pos] != ' '))pos++;
        line[pos] = 0;
        int id;
        if(sscanf(line + last,"%d",&id) != 1){
          Clear();
          sprintf(error,"Line %d in map.txt: Invalid line [%s]",lineCount,line+last);
          fclose(file);
          return false;
        }else if((id < 0)||(id >= (int)tileSet->tiles.size())){
          Clear();
          sprintf(error,"Line %d in map.txt: Tile %d is invalid",lineCount,id);
          fclose(file);
          return false;
        }
        tiles.at(n).at(lineCount - 2) = &tileSet->tiles.at(id);
        n++;
        if(pos < size)pos++;
        while((pos < size)&&(line[pos] == ' '))pos++;
        if(pos >= size)break;
        last = pos;
        if(n >= width){
          Clear();
          sprintf(error,"Line %d in map.txt: Too many tiles",lineCount);
          fclose(file);
          return false;
        }
      }
      if(n != width){
        Clear();
        sprintf(error,"Line %d in map.txt: Not enough tiles",lineCount);
        fclose(file);
        return false;
      }
    }
  }
  fclose(file);
  if(tiles.size() == 0){
    Clear();
    sprintf(error,"No loaded map");
    return false;
  }
  for(size_t x = 0; x<tiles.size(); x++){
    for(size_t y = 0; y<tiles.at(x).size(); y++){
      if(tiles.at(x).at(y) == NULL){
        Clear();
        sprintf(error,"Map not fully loaded");
        return false;
      }
    }
  }
  return true;
}

void GTGMap::Draw(SDL_Surface *dst, Uint16 posX1, Uint16 posY1, Uint16 posX2, Uint16 posY2){
  int startX = posX1 + ((posX2 - posX1)/2) - (width *spaceX/2) + cameraX;
  int startY = posY1 + ((posY2 - posY1)/2) - (height*spaceY/2) + cameraY;
  boxColor(dst,posX1,posY1,posX2,posY2,backgroundColor);
  for(size_t x = 0; x<tiles.size(); x++){
    for(size_t y = 0; y<tiles.at(x).size(); y++){
      SDL_Surface *src = tiles.at(x).at(y)->GetSurface();
      int px = startX + x*spaceX;
      int py = startY + y*spaceY;
      int pw = spaceX;
      int ph = spaceY;
      int srcX = 0;
      int srcY = 0;
      if(px < posX1)srcX = posX1 - px; if(srcX > spaceX)continue;
      if(px >= posX2)continue; if(px + pw > posX2)pw = posX2 - px;
      if(py < posY1)srcY = posY1 - py; if(srcY > spaceY)continue;
      if(py >= posY2)continue; if(py + ph > posY2)ph = posY2 - py;
      SDLBlit(src,dst,px + srcX,py + srcY,pw,ph,srcX,srcY);
    }
  }

  int px = startX + player.x*spaceX;
  int py = startY + player.y*spaceY;
  int pw = spaceX;
  int ph = spaceY;
  int srcX = 0;
  int srcY = 0;
  bool error = false;
  if(px < posX1)srcX = posX1 - px; if(srcX > spaceX)error = true;
  if(px >= posX2)error = true; if(px + pw > posX2)pw = posX2 - px;
  if(py < posY1)srcY = posY1 - py; if(srcY > spaceY)error = true;
  if(py >= posY2)error = true; if(py + ph > posY2)ph = posY2 - py;
  if(!error)SDLBlit(player.GetSurface(),dst,px + srcX,py + srcY,pw,ph,srcX,srcY);

  rectangleColor(dst,posX1,posY1,posX2,posY2,0x000000FF);
}

void GTGMap::Frame(SDLTimer *timer, Uint16 posX1, Uint16 posY1, Uint16 posX2, Uint16 posY2){
  player.Frame(timer);

  int px = posX1 + ((posX2 - posX1)/2) - (width *spaceX/2) + player.x*spaceX + cameraX;
  int py = posY1 + ((posY2 - posY1)/2) - (height*spaceY/2) + player.y*spaceY + cameraY;
  int sx = spaceX*((posX2 - posX1)/spaceX)/4;
  int sy = spaceY*((posY2 - posY1)/spaceY)/4;

  float d = ((timer->now - camTime)/200.);

  if(d > 1.){
    cameraX = camTargetX; camFromX = cameraX;
    cameraY = camTargetY; camFromY = cameraY;

    if(px < posX1 + sx){
      camTargetX = camTargetX+sx; camFromX = cameraX;
      camTime = timer->now;
    }else if(px + spaceX > posX2 - sx){
      camTargetX = camTargetX-sx; camFromX = cameraX;
      camTime = timer->now;
    }

    if(py < posY1 + sy){
      camTargetY = camTargetY+sy; camFromY = cameraY;
      camTime = timer->now;
    }else if(py + spaceY > posY2 - sy){
      camTargetY = camTargetY-sy; camFromY = cameraY;
      camTime = timer->now;
    }

  }else{
    cameraX = camFromX + (camTargetX - camFromX)*sin(d);
    cameraY = camFromY + (camTargetY - camFromY)*sin(d);
  }

}
