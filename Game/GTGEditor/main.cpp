#include "GTGMap.h"
#include "GTGTile.h"

#include "SDLHelper.h"
#include "SDLGui.h"
#include "SDL_gfxPrimitives.h"

void Popup(const char *text, Uint32 txtColor, Uint32 backColor, Uint32 time = 0);

bool FileExists(const char *filename){
  FILE *f = fopen(filename,"rt");
  if(f == NULL)return false;
  fclose(f);
  return true;
}

struct Map{
  int width, height, spaceX, spaceY, backgroundColor;
  std::vector< std::vector< int > > mapID;
  std::vector< std::vector< bool > > mapSolid;
  int spawnX, spawnY;
  int wl,wr,wu,wd,il,ir,iu,id;
  void Resize(int w, int h, int defaultID, bool defaultSolid){
    int ow = mapID.size(), oh = 0; if(ow > 0)oh = mapID.at(0).size();
    mapID.resize(w);
    mapSolid.resize(w);
    for(int n = 0; n<w; n++){
      mapID.at(n).resize(h);
      mapSolid.at(n).resize(h);
      for(int k = 0; k<h; k++){
        if((n >= ow)||(k >= oh)){
          mapID.at(n).at(k) = defaultID;
          mapSolid.at(n).at(k) = defaultSolid;
        }
      }
    }
    width = w; height = h;
  }
  void Save(const char *filename){
    FILE *f = fopen(filename,"wt");
    if(f == NULL)return;
    fprintf(f,"%d %d %d %d %d\n",width,height,spaceX,spaceY,backgroundColor);
    for(int y = 0; y<height; y++){
      for(int x = 0; x<width; x++){
        if(x != 0)fprintf(f," ");
        fprintf(f,"%d:%d",mapID[x][y],(mapSolid[x][y])?1:0);
      }
      fprintf(f,"\n");
    }
    fprintf(f,"%d %d\n",spawnX,spawnY);
    fprintf(f,"%d %d %d %d %d %d %d %d\n",wl,wr,wu,wd,il,ir,iu,id);
    fclose(f);
  }
};

int main(int argc, char* args[]){
  SDLInit();
  SDL_WM_SetCaption("GTG - map editor","GTG");
  GUILoadFont("font.ttf");

  GTGTileSet tileset;

  int res = tileset.Load("res","tiles.txt");
  if(res < 0){
    Popup(tileset.GetLastError(),0xFF0000FF,0x000000FF);
    return 0;
  }else if(res == 0){
    Popup("res/tiles.txt: No tiles",0xFF0000FF,0x000000FF);
    return 0;
  }

  Map map;

  if(FileExists("res/map.txt")){
    GTGMap loadedMap;
    if(!loadedMap.Load("res","map.txt",&tileset)){
      Popup(loadedMap.GetLastError(),0xFF0000FF,0x000000FF);
      return 0;
    }

    map.width = loadedMap.width;
    map.height = loadedMap.height;
    map.spaceX = loadedMap.spaceX;
    map.spaceY = loadedMap.spaceY;
    map.Resize(map.width,map.height,-1,false);
    for(size_t x = 0; x<loadedMap.backTiles.size(); x++){
      for(size_t y = 0; y<loadedMap.backTiles.at(x).size(); y++){
        map.mapSolid.at(x).at(y) = loadedMap.backTiles.at(x).at(y).solid;
        map.mapID.at(x).at(y) = -1;
        for(size_t n = 0; n<tileset.tiles.size(); n++){
          if(loadedMap.backTiles.at(x).at(y).tile == &tileset.tiles.at(n)){
             map.mapID.at(x).at(y) = n;
             break;
          }
        }
        if(map.mapID.at(x).at(y) == -1){
          Popup("Strange error",0xFF0000FF,0x000000FF);
          return 0;
        }
      }
    }
    map.spawnX = loadedMap.spawnX;
    map.spawnY = loadedMap.spawnY;
    for(size_t n = 0; n<tileset.tiles.size(); n++){
      if(loadedMap.player.tileIdleLeft  == &tileset.tiles.at(n))map.il = n;
      if(loadedMap.player.tileIdleRight == &tileset.tiles.at(n))map.ir = n;
      if(loadedMap.player.tileIdleUp    == &tileset.tiles.at(n))map.iu = n;
      if(loadedMap.player.tileIdleDown  == &tileset.tiles.at(n))map.id = n;
      if(loadedMap.player.tileWalkLeft  == &tileset.tiles.at(n))map.wl = n;
      if(loadedMap.player.tileWalkRight == &tileset.tiles.at(n))map.wr = n;
      if(loadedMap.player.tileWalkUp    == &tileset.tiles.at(n))map.wu = n;
      if(loadedMap.player.tileWalkDown  == &tileset.tiles.at(n))map.wd = n;
    }
    loadedMap.Clear();
    loadedMap.Destruct();
  }else{
    map.width = 3; map.height = 3; map.spaceX = 64; map.spaceY = 64; map.backgroundColor = (int)0xFFFFFFFF;
    map.Resize(3,3,0,false);
    map.spawnX = 0; map.spawnY = 0;
    map.wl = 0; map.wr = 0; map.wu = 0; map.wd = 0;
    map.il = 0; map.ir = 0; map.iu = 0; map.id = 0;
  }

  bool run = true; SDLTimer timer; SDL_Event SDLEvent;

  GUIButton increaseX, decreaseX, increaseY, decreaseY; increaseX.Register(); decreaseX.Register(); increaseY.Register(); decreaseY.Register();
  GUIButton increaseSX, decreaseSX, increaseSY, decreaseSY; increaseSX.Register(); decreaseSX.Register(); increaseSY.Register(); decreaseSY.Register();
  GUIButton increaseSPX, decreaseSPX, increaseSPY, decreaseSPY; increaseSPX.Register(); decreaseSPX.Register(); increaseSPY.Register(); decreaseSPY.Register();
  GUIButton saveMap; saveMap.Register();
  GUIButton nextTile, prevTile; nextTile.Register(); prevTile.Register();

  GUIButton setWL, setWR, setWU, setWD, setIL, setIR, setIU, setID;
  setWL.Register(); setWR.Register(); setWU.Register(); setWD.Register();
  setIL.Register(); setIR.Register(); setIU.Register(); setID.Register();

  GUIScrollBar scrollX, scrollY;
  scrollX.SetHorizontal(true); scrollX.Register();
  scrollY.SetHorizontal(false); scrollY.Register();

  int selectedTile = 0; bool isPressingLeft = false;
  int drawOffX = 0, drawOffY = 0, drawPosX1 = 0, drawPosY1 = 0, drawPosX2 = 0, drawPosY2 = 0;

  SDLPushResizeEvent(800,600);
  while(run){
    while(SDL_PollEvent(&SDLEvent)){
      switch(SDLEvent.type){
      case SDL_QUIT: run=false; break;
      case SDL_VIDEORESIZE:
        SDLSetVideo(SDLEvent.resize.w,SDLEvent.resize.h,true);
        drawPosX1 = map.spaceX + 20; drawPosY1 = 110;
        drawPosX2 = screen->w-30; drawPosY2 = screen->h-130;

        scrollY.SetPos(drawPosX2,drawPosY1,drawPosX2+20,drawPosY2);
        scrollX.SetPos(drawPosX1,drawPosY2,drawPosX2,drawPosY2+20);

        saveMap.SetPos(370,50,480,70); saveMap.SetText(" SAVE MAP ");

        increaseX.SetPos(10 ,20,90 ,40); increaseX.SetText(" Width++ "); increaseX.Register();
        decreaseX.SetPos(100,20,180,40); decreaseX.SetText(" Width-- "); decreaseX.Register();
        increaseY.SetPos(190,20,270,40); increaseY.SetText(" Height++ "); increaseY.Register();
        decreaseY.SetPos(280,20,360,40); decreaseY.SetText(" Height-- "); decreaseY.Register();

        increaseSX.SetPos(10 ,50,90 ,70); increaseSX.SetText(" SpaceX++ "); increaseSX.Register();
        decreaseSX.SetPos(100,50,180,70); decreaseSX.SetText(" SpaceX-- "); decreaseSX.Register();
        increaseSY.SetPos(190,50,270,70); increaseSY.SetText(" SpaceY++ "); increaseSY.Register();
        decreaseSY.SetPos(280,50,360,70); decreaseSY.SetText(" SpaceY-- "); decreaseSY.Register();

        increaseSPX.SetPos(10 ,80,90 ,100); increaseSPX.SetText(" SpawnX++ "); increaseSPX.Register();
        decreaseSPX.SetPos(100,80,180,100); decreaseSPX.SetText(" SpawnX-- "); decreaseSPX.Register();
        increaseSPY.SetPos(190,80,270,100); increaseSPY.SetText(" SpawnY++ "); increaseSPY.Register();
        decreaseSPY.SetPos(280,80,360,100); decreaseSPY.SetText(" SpawnY-- "); decreaseSPY.Register();

        nextTile.SetPos(10,120+map.spaceY,10+map.spaceX,140+map.spaceY); nextTile.SetText("Next");
        prevTile.SetPos(10,150+map.spaceY,10+map.spaceX,170+map.spaceY); prevTile.SetText("Prev");

        res = 10;
        setWL.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setWL.SetText("Walk left"); res += 80;
        setWR.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setWR.SetText("Walk right"); res += 80;
        setWU.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setWU.SetText("Walk up"); res += 80;
        setWD.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setWD.SetText("Walk down"); res += 80;

        setIL.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setIL.SetText("Idle left"); res += 80;
        setIR.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setIR.SetText("Idle right"); res += 80;
        setIU.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setIU.SetText("Idle up"); res += 80;
        setID.SetPos(res,drawPosY2+30,res+70,drawPosY2+50); setID.SetText("Idle down"); res += 80;

        break;
      case SDL_KEYDOWN:
        if(SDLEvent.key.keysym.sym==SDLK_ESCAPE)run=false;
        if(SDLEvent.key.keysym.sym==SDLK_LEFT){ selectedTile--; if(selectedTile<0)selectedTile = tileset.tiles.size()-1; }
        if(SDLEvent.key.keysym.sym==SDLK_RIGHT){ selectedTile++; if(selectedTile>=(int)tileset.tiles.size())selectedTile = 0; }
        break;
      case SDL_MOUSEBUTTONUP:
        if(SDLEvent.button.button == SDL_BUTTON_LEFT){
          isPressingLeft = false;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if((SDLEvent.button.x > drawPosX1)&&(SDLEvent.button.x < drawPosX2)&&(SDLEvent.button.y > drawPosY1)&&(SDLEvent.button.y < drawPosY2)){
          int tileX = (SDLEvent.button.x - (drawOffX + drawPosX1))/map.spaceX;
          int tileY = (SDLEvent.button.y - (drawOffY + drawPosY1))/map.spaceY;
          if((tileX >= 0)&&(tileX < map.width)&&(tileY >= 0)&&(tileY < map.height)){
            if(SDLEvent.button.button == SDL_BUTTON_LEFT){
              map.mapID[tileX][tileY] = selectedTile;
              isPressingLeft = true;
            }else if(SDLEvent.button.button == SDL_BUTTON_RIGHT){
              map.mapSolid[tileX][tileY] = !map.mapSolid[tileX][tileY];
            }
          }
        }
      case SDL_MOUSEMOTION:
        if(isPressingLeft){
          int tileX = (SDLEvent.motion.x - (drawOffX + drawPosX1))/map.spaceX;
          int tileY = (SDLEvent.motion.y - (drawOffY + drawPosY1))/map.spaceY;
          if((tileX >= 0)&&(tileX < map.width)&&(tileY >= 0)&&(tileY < map.height)){
            map.mapID[tileX][tileY] = selectedTile;
          }
        }
        break;
      case SDL_USEREVENT:
        if(SDLEvent.user.code==GUIBUTTON_RELEASE){
          if(SDLEvent.user.data1 == &setWL)map.wl = selectedTile;
          else if(SDLEvent.user.data1 == &setWR)map.wr = selectedTile;
          else if(SDLEvent.user.data1 == &setWU)map.wu = selectedTile;
          else if(SDLEvent.user.data1 == &setWD)map.wd = selectedTile;
          else if(SDLEvent.user.data1 == &setIL)map.il = selectedTile;
          else if(SDLEvent.user.data1 == &setIR)map.ir = selectedTile;
          else if(SDLEvent.user.data1 == &setIU)map.iu = selectedTile;
          else if(SDLEvent.user.data1 == &setID)map.id = selectedTile;
          else if(SDLEvent.user.data1 == &increaseX){
            map.Resize(map.width+1,map.height,selectedTile,false);
          }else if(SDLEvent.user.data1 == &decreaseX){
            map.Resize(map.width-1,map.height,selectedTile,false);
          }else if(SDLEvent.user.data1 == &increaseY){
            map.Resize(map.width,map.height+1,selectedTile,false);
          }else if(SDLEvent.user.data1 == &decreaseY){
            map.Resize(map.width,map.height-1,selectedTile,false);
          }else if(SDLEvent.user.data1 == &increaseSX){
            map.spaceX++; SDLPushResizeEvent(screen->w,screen->h);
          }else if(SDLEvent.user.data1 == &decreaseSX){
            if(map.spaceX>1)map.spaceX--; SDLPushResizeEvent(screen->w,screen->h);
          }else if(SDLEvent.user.data1 == &increaseSY){
            map.spaceY++; SDLPushResizeEvent(screen->w,screen->h);
          }else if(SDLEvent.user.data1 == &decreaseSY){
            if(map.spaceY>1)map.spaceY--; SDLPushResizeEvent(screen->w,screen->h);
          }else if(SDLEvent.user.data1 == &increaseSPX){
            map.spawnX++; if(map.spawnX >= map.width)map.spawnX = map.width - 1;
          }else if(SDLEvent.user.data1 == &decreaseSPX){
            map.spawnX--; if(map.spawnX < 0)map.spawnX = 0;
          }else if(SDLEvent.user.data1 == &increaseSPY){
            map.spawnY++; if(map.spawnY >= map.height)map.spawnY = map.height - 1;
          }else if(SDLEvent.user.data1 == &decreaseSPY){
            map.spawnY--; if(map.spawnY < 0)map.spawnY = 0;
          }else if(SDLEvent.user.data1 == &saveMap){
            map.Save("res/map.txt");
          }else if(SDLEvent.user.data1 == &nextTile){
            selectedTile++; if(selectedTile>=(int)tileset.tiles.size())selectedTile = 0;
          }else if(SDLEvent.user.data1 == &prevTile){
            selectedTile--; if(selectedTile<0)selectedTile = tileset.tiles.size()-1;
          }
        }
        break;
      }
      GUIEvent(&SDLEvent);
    }
    timer.Frame(1);

    tileset.Frame();
    boxColor(screen,0,0,screen->w,screen->h,0xF0F0F0FF);

    drawOffX = ((drawPosX2-drawPosX1)-(map.width *map.spaceX))*scrollX.GetScrollPos();
    drawOffY = ((drawPosY2-drawPosY1)-(map.height*map.spaceY))*scrollY.GetScrollPos();

    SDLBlit(tileset.tiles.at(selectedTile).GetSurface(),screen,10,110);
    int px,py,pw,ph,srcX,srcY;
    for(int x = 0; x<map.width; x++){
      for(int y = 0; y<map.height; y++){
        px = drawOffX + drawPosX1 + x*map.spaceX;
        py = drawOffY + drawPosY1 + y*map.spaceY;
        pw = map.spaceX;
        ph = map.spaceY;
        srcX = 0; srcY = 0;
        if(px + pw <= drawPosX1)continue; if(px >= drawPosX2)continue;
        if(px < drawPosX1){ srcX = drawPosX1 - px; px = drawPosX1; }else if(px + map.spaceX > drawPosX2){ pw = drawPosX2 - px; }
        if(py + ph <= drawPosY1)continue; if(py >= drawPosY2)continue;
        if(py < drawPosY1){ srcY = drawPosY1 - py; py = drawPosY1; }else if(py + map.spaceY > drawPosY2){ ph = drawPosY2 - py; }
        SDLBlit(tileset.tiles.at(map.mapID[x][y]).GetSurface(),screen,px,py,pw,ph,srcX,srcY);
        if(map.mapSolid[x][y]){
          lineColor(screen,px,py,px+pw-srcX,py+ph-srcY,0xFF0000FF);
          lineColor(screen,px+pw-srcX,py,px,py+ph-srcY,0xFF0000FF);
          boxColor(screen,px,py,px+pw-srcX,py+ph-srcY,0x00000099);
        }
      }
    }
    rectangleColor(screen,drawPosX1,drawPosY1,drawPosX2,drawPosY2,0x000000FF);

    int pos = 0;
    SDLBlit(tileset.tiles.at(map.wl).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.wr).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.wu).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.wd).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.il).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.ir).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.iu).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;
    SDLBlit(tileset.tiles.at(map.id).GetSurface(),screen,10 + pos,drawPosY2+60); pos += map.spaceX+10;

    GUIDraw(screen);
    char txt[255];
    sprintf(txt,"Width: %d Height: %d SpaceX: %d SpaceY: %d SpawnX: %d SpawnY: %d",map.width,map.height,map.spaceX,map.spaceY,map.spawnX,map.spawnY); stringColor(screen,10,5,txt,0xFF0000FF);
    //sprintf(txt,"FPS %.2f",timer.fps); stringColor(screen,2,screen->h-10,txt,0xFF0000FF);
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
