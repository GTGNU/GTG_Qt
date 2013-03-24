#include "GTGTile.h"

GTGTile::GTGTile(){ Construct(); }
GTGTile::~GTGTile(){ Destruct(); }

void GTGTile::Construct(){
  tex.clear();
  lastFrame = 0;
  lastTex = 0;
  lastTexFrame = 0;
}

void GTGTile::Destruct(){
  Free();
  Construct();
}

void GTGTile::Free(){
  for(size_t n = 0; n<tex.size(); n++){
    if(tex.at(n).surface != NULL){ SDL_FreeSurface(tex.at(n).surface); tex.at(n).surface = NULL; }
  }
  tex.clear();
}

void GTGTile::AddFrame(SDL_Surface *s, Uint32 duration){
  GTGTileTex t; t.surface = s; t.duration = duration;
  tex.push_back(t);
}

void GTGTile::Frame(SDLTimer *timer){
  if(tex.at(lastTex).duration == 0)return;
  Uint32 now = SDL_GetTicks();
  if(lastFrame == 0)lastFrame = now;
  Uint32 diff = now - lastFrame + lastTexFrame;
  lastTexFrame = 0;
  while(diff > 0){
    if(tex.at(lastTex).duration > diff){
      lastTexFrame = diff;
      diff = 0;
    }else{
      diff -= tex.at(lastTex).duration;
      lastTex++;
      if(lastTex >= tex.size())lastTex = 0;
    }
  }
  lastFrame = now;
}

SDL_Surface* GTGTile::GetSurface(){
  return tex.at(lastTex).surface;
}

GTGTileSet::GTGTileSet(){ Construct(); }
GTGTileSet::~GTGTileSet(){ Destruct(); }

void GTGTileSet::Construct(){
  memset(error,0,128); sprintf(error,"No error");
  tiles.clear();
}

void GTGTileSet::Destruct(){
  Free();
  Construct();
}

const char* GTGTileSet::GetLastError(){
  return error;
}

void GTGTileSet::Frame(SDLTimer *timer){
  for(size_t n = 0; n<tiles.size(); n++)tiles.at(n).Frame(timer);
}

int GTGTileSet::Load(const char *root){
  char path[128], line[512];
  size_t lineCount = 0;

  Free();

  sprintf(path,"%s/tiles.txt",root);
  FILE *file = fopen(path,"rt");
  if(file == NULL){
    sprintf(error,"Could not open %s for reading",path);
    return -1;
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
    if(pos==0)continue;
    if(lineCount == 0){
      int num = 0;
      if((sscanf(line,"%d",&num) != 1)||(num <= 0)){
        sprintf(error,"First line in tiles.txt to be a positive number");
        fclose(file);
        return -1;
      }
      tiles.resize(num);
      for(size_t n = 0; n<tiles.size(); n++)tiles.at(n).Construct();
      lineCount++;
    }else{
      if(lineCount - 1 >= tiles.size()){
        Free();
        sprintf(error,"Too much tiles in tiles.txt. Edit the first line.");
        fclose(file);
        return -1;
      }
      size_t size = pos, last = 0; pos = 0;
      SDL_Surface *surf = NULL;
      while(true){
        while((pos < size)&&(line[pos] != ' '))pos++;
        line[pos] = 0;
        if(surf != NULL){
          int num;
          if((sscanf(line + last,"%d",&num) != 1)||(num < 0)){
            Free();
            sprintf(error,"Invalid line %d in tiles.txt",lineCount);
            fclose(file);
            return -1;
          }
          tiles.at(lineCount - 1).AddFrame(surf,num);
          surf = NULL;
        }else{
          sprintf(path,"%s/%s",root,line + last);
          surf = SDLLoad(path);
          if(surf == NULL){
            Free();
            sprintf(error,"Could not load %s",path);
            fclose(file);
            return -1;
          }
        }
        if(pos < size)pos++;
        while((pos < size)&&(line[pos] == ' '))pos++;
        if(pos >= size)break;
        last = pos;
      }
      if(surf != NULL)tiles.at(lineCount - 1).AddFrame(surf,0);
      lineCount++;
    }
  }
  fclose(file);
  if(lineCount - 1 != tiles.size()){
    Free();
    sprintf(error,"Number of loaded tiles don't match the first line");
    return false;
  }
  return tiles.size();
}

void GTGTileSet::Free(){
  for(size_t n = 0; n<tiles.size(); n++){
    tiles.at(n).Free();
    tiles.at(n).Destruct();
  }
  tiles.clear();
}
