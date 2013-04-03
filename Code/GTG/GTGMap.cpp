#include "GTGMap.h"
#include "GTGTile.h"

GTGMap::GTGMap()
{
    Construct();
}

GTGMap::~GTGMap()
{
    Destruct();
}

void GTGMap::Construct()
{
    memset(error,0,128);
    sprintf(error,"No error");
    width = 0;
    height = 0;
    spaceX = 16;
    spaceY = 16;
    backgroundColor = 0xFFFFFFFF;
    backTiles.clear();
    spawnX = 0;
    spawnY = 0;
}

void GTGMap::Destruct()
{
    Clear();
    Construct();
}

void GTGMap::Clear()
{
    for(size_t n = 0; n<backTiles.size(); n++)backTiles.at(n).clear();
    backTiles.clear();
    width = 0;
    height = 0;
    spaceX = 16;
    spaceY = 16;
    backgroundColor = 0xFFFFFFFF;
    spawnX = 0;
    spawnY = 0;
    player.Destruct();
}

const char* GTGMap::GetLastError()
{
    return error;
}

bool GTGMap::IsSolid(int x, int y)
{
    if((x<0)||(y<0))return true;
    if((x>=(int)width)||(y>=(int)height))return true;
    return backTiles.at(x).at(y).solid;
}

void GTGMap::Frame(SDLTimer *timer)
{

}

bool GTGMap::Load(const char *root, const char *filename, GTGTileSet *tileSet)
{
    char path[128], line[512];

    Clear();

    sprintf(path,"%s/%s",root,filename);
    FILE *file = fopen(path,"rt");
    if(file == NULL) {
        sprintf(error,"Could not open map %s for reading",path);
        return false;
    }
    size_t lineCount = 0, handle = 0, handleCount = 0;
    while(!feof(file)) {
        size_t lineSize = 0;
        while(true) {
            int c = fgetc(file);
            if(c == '\r')continue;
            if(c == '#')while(true) {
                    c = fgetc(file);
                    if((c == EOF)||(c == '\n'))break;
                }
            if((c == EOF)||(c == '\n'))break;
            if(isspace(c))c = ' ';
            line[lineSize] = (char)c;
            lineSize++;
        }
        line[lineSize] = 0;
        lineCount++;
        if(lineSize == 0)continue;
        if(handle == 0) {
            int w, h, sx, sy, bcolor, ret = sscanf(line,"%d %d %d %d %d",&w,&h,&sx,&sy,&bcolor);
            if(ret == 4) {
                ret = 5;
                bcolor = (int)0xFFFFFFFF;
            }
            if(ret != 5) {
                sprintf(error,"First line in map %s must have 5 numbers",path);
                fclose(file);
                Clear();
                return false;
            }
            if((w < 2)||(h < 2)||(sx < 2)||(sy < 2)) {
                Clear();
                sprintf(error,"Invalid first line in map %s",path);
                fclose(file);
                return false;
            }
            backTiles.resize(w);
            for(size_t n = 0; n<backTiles.size(); n++) {
                backTiles.at(n).resize(h);
                for(size_t m = 0; m<backTiles.at(n).size(); m++) {
                    backTiles.at(n).at(m).tile = NULL;
                    backTiles.at(n).at(m).solid = false;
                }
            }
            width = w;
            height = h;
            spaceX = sx;
            spaceY = sy;
            backgroundColor = ((Uint32)bcolor)|0x000000FF;
            handle++;
            handleCount = 0;
        } else if(handle == 1) {
            size_t pos = 0, last = 0, count = 0;
            while(true) {
                while((pos < lineSize)&&(line[pos] != ' '))pos++;
                line[pos] = 0;
                int tileID, tileSolid, ret = sscanf(line+last,"%d:%d",&tileID,&tileSolid);
                if(ret == 1) {
                    ret = 2;
                    tileSolid = 0;
                }
                if(ret != 2) {
                    sprintf(error,"map %s line %lu: Invalid line segment [%s]",path,lineCount,line+last);
                    fclose(file);
                    Clear();
                    return false;
                } else if((tileID < 0)||(tileID >= (int)tileSet->tiles.size())||(tileSolid < 0)||(tileSolid > 1)) {
                    sprintf(error,"map %s line %lu: Tile %d:%d is invalid",path,lineCount,tileID,tileSolid);
                    fclose(file);
                    Clear();
                    return false;
                }
                backTiles.at(count).at(handleCount).tile = &tileSet->tiles.at(tileID);
                backTiles.at(count).at(handleCount).solid = tileSolid;
                count++;
                if(pos < lineSize)pos++;
                while((pos < lineSize)&&(line[pos] == ' '))pos++;
                if(pos >= lineSize)break;
                last = pos;
                if(count >= width) {
                    sprintf(error,"map %s line %lu: Too many line segments. Width is %d",path,lineCount,width);
                    fclose(file);
                    Clear();
                    return false;
                }
            }
            handleCount++;
            if(handleCount >= height) {
                handle++;
                handleCount = 0;
            }
        } else if(handle == 2) {
            int sx,sy;
            if(sscanf(line,"%d %d",&sx,&sy) != 2) {
                sprintf(error,"map %s line %lu: Expected 2 numbers - spawn location",path,lineCount);
                fclose(file);
                Clear();
                return false;
            } else if((sx<0)||(sx>=(int)width)||(sy<0)||(sx>=(int)height)) {
                sprintf(error,"map %s line %lu: Spawn location %d %d is off the map",path,lineCount,sx,sy);
                fclose(file);
                Clear();
                return false;
            }
            spawnX = sx;
            spawnY = sy;
            handle++;
            handleCount = 0;
        } else if(handle == 3) {
            int wl,wr,wu,wd,il,ir,iu,id;
            if(sscanf(line,"%d %d %d %d %d %d %d %d",&wl,&wr,&wu,&wd,&il,&ir,&iu,&id) != 8) {
                sprintf(error,"map %s line %lu: Expected 8 numbers - player sprites",path,lineCount);
                fclose(file);
                Clear();
                return false;
            } else if((!tileSet->IsValidID(wl))||(!tileSet->IsValidID(wr))
                      ||(!tileSet->IsValidID(wu))||(!tileSet->IsValidID(wd))
                      ||(!tileSet->IsValidID(il))||(!tileSet->IsValidID(ir))
                      ||(!tileSet->IsValidID(iu))||(!tileSet->IsValidID(id))) {
                sprintf(error,"map %s line %lu: Some player sprite id's are invalid",path,lineCount);
                fclose(file);
                Clear();
                return false;
            }

            player.Construct();
            player.tileWalkLeft  = &tileSet->tiles.at(wl);
            player.tileWalkRight = &tileSet->tiles.at(wr);
            player.tileWalkUp		 = &tileSet->tiles.at(wu);
            player.tileWalkDown  = &tileSet->tiles.at(wd);
            player.tileIdleLeft  = &tileSet->tiles.at(il);
            player.tileIdleRight = &tileSet->tiles.at(ir);
            player.tileIdleUp		 = &tileSet->tiles.at(iu);
            player.tileIdleDown  = &tileSet->tiles.at(id);
            player.Spawn(spawnX,spawnY);
            handle++;
            handleCount = 0;
        }
    }
    fclose(file);
    if(handle == 0) {
        sprintf(error,"map %s: First line should have 4 numbers",path);
        Clear();
        return false;
    } else if(handle == 1) {
        sprintf(error,"map %s: Map tiles unexpectedly ended",path);
        Clear();
        return false;
    } else if(handle == 2) {
        sprintf(error,"map %s: No spawn location",path);
        Clear();
        return false;
    } else if(handle == 3) {
        sprintf(error,"map %s: Missing player sprite id's",path);
        Clear();
        return false;
    }
    if(backTiles.size() == 0) {
        sprintf(error,"map %s: No map tiles",path);
        Clear();
        return false;
    }
    for(size_t x = 0; x<backTiles.size(); x++) {
        for(size_t y = 0; y<backTiles.at(x).size(); y++) {
            if(backTiles.at(x).at(y).tile == NULL) {
                sprintf(error,"map %s: Tile [%lu][%lu] unknown",path,x,y);
                Clear();
                return false;
            }
        }
    }
    return true;
}
