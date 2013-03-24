#include "GTGPlayer.h"
#include "GTGTile.h"

GTGPlayer::GTGPlayer(){ Construct(); }
GTGPlayer::~GTGPlayer(){ Destruct(); }

void GTGPlayer::Construct(){
  memset(error,0,128); sprintf(error,"No error");
  x = 0; y = 0;
  tileLeft = NULL; tileRight = NULL; tileUp = NULL; tileDown = NULL;
  tileIdleLeft = NULL; tileIdleRight = NULL; tileIdleUp = NULL; tileIdleDown = NULL;
  action = 0;
  targetX = 0; targetY = 0; fromX = 0; fromY = 0; moveTime = 0;
}

void GTGPlayer::Destruct(){
  Construct();
}

const char* GTGPlayer::GetLastError(){
  return error;
}

SDL_Surface* GTGPlayer::GetSurface(){
  switch(action){
  default: case 0: return tileIdleLeft->GetSurface();
  case 1: return tileIdleRight->GetSurface();
  case 2: return tileIdleUp->GetSurface();
  case 3: return tileIdleDown->GetSurface();
  case 4: return tileLeft->GetSurface();
  case 5: return tileRight->GetSurface();
  case 6: return tileUp->GetSurface();
  case 7: return tileDown->GetSurface();
  }
  return tileRight->GetSurface();
}

void GTGPlayer::GoLeft(SDLTimer *timer){
  if((action == 6)||(action == 7)||(action == 4))return;
  targetX--; fromX = x; fromY = y;
  action = 4;
  moveTime = timer->now;
}

void GTGPlayer::GoRight(SDLTimer *timer){
  if((action == 6)||(action == 7)||(action == 5))return;
  targetX++; fromX = x; fromY = y;
  action = 5;
  moveTime = timer->now;
}

void GTGPlayer::GoUp(SDLTimer *timer){
  if((action == 4)||(action == 5)||(action == 6))return;
  targetY--; fromX = x; fromY = y;
  action = 6;
  moveTime = timer->now;
}

void GTGPlayer::GoDown(SDLTimer *timer){
  if((action == 4)||(action == 5)||(action == 7))return;
  targetY++; fromX = x; fromY = y;
  action = 7;
  moveTime = timer->now;
}

void GTGPlayer::Frame(SDLTimer *timer){

  if(action > 3){
    float d = (timer->now - moveTime)/400.;
    if(d > 1.){
      switch(action){
      case 4: action = 0; break;
      case 5: action = 1; break;
      case 6: action = 2; break;
      case 7: action = 3; break;
      }
      x = targetX; y = targetY;
    }else{
      x = fromX + (targetX - fromX)*sin(d);
      y = fromY + (targetY - fromY)*sin(d);
    }
  }

}

bool GTGPlayer::Load(const char *root, GTGTileSet *tileSet){
  char path[128], line[512];
  size_t lineCount = 0;

  sprintf(path,"%s/player.txt",root);
  FILE *file = fopen(path,"rt");
  if(file == NULL){
    sprintf(error,"Could not open %s for reading",path);
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
    if(lineCount == 1){
      int px, py;
      if((sscanf(line,"%d %d",&px,&py) != 2)||(px < 0)||(py < 0)){
        sprintf(error,"Line %d in player.txt: Must be 2 positive numbers - spawn location",lineCount);
        return false;
      }
      x = px; y = py; targetX = px; targetY = py; fromX = px; fromY = py;
    }else{
      int id;
      if(sscanf(line,"%d",&id) != 1){
        sprintf(error,"Line %d in player.txt: Not a number",lineCount);
        return false;
      }else if((id < 0)||(id >= (int)tileSet->tiles.size())){
        sprintf(error,"Line %d in player.txt: %d is not a valid tile",lineCount,id);
        return false;
      }
      switch(lineCount){
      case 2: tileLeft = &tileSet->tiles.at(id); break;
      case 3: tileRight = &tileSet->tiles.at(id); break;
      case 4: tileUp = &tileSet->tiles.at(id); break;
      case 5: tileDown = &tileSet->tiles.at(id); break;
      case 6: tileIdleLeft = &tileSet->tiles.at(id); break;
      case 7: tileIdleRight = &tileSet->tiles.at(id); break;
      case 8: tileIdleUp = &tileSet->tiles.at(id); break;
      case 9: tileIdleDown = &tileSet->tiles.at(id); break;
      default: break;
      }
      if(lineCount == 9)break;
    }
  }
  if(lineCount != 9){
    sprintf(error,"Not enough tiles in player.txt");
    return false;
  }

  fclose(file);
  return true;
}
