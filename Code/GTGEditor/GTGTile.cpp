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

void GTGTile::SetTime(Uint32 time){
	lastFrame = 0; lastTex = 0; lastTexFrame = time;
}

void GTGTile::Frame(){
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

void GTGTileSet::Frame(){
	for(size_t n = 0; n<tiles.size(); n++)tiles.at(n).Frame();
}

int GTGTileSet::Load(const char *root, const char *filename){
	char path[128], path2[128], line[512];

	Free();

	sprintf(path,"%s/%s",root,filename);
	FILE *file = fopen(path,"rt");
	if(file == NULL){
		sprintf(error,"Could not open %s for reading",path);
		return -1;
	}
	size_t lineCount = 0, handle = 0;
	while(!feof(file)){
		size_t lineSize = 0;
		while(true){
			int c = fgetc(file);
			if(c == '\r')continue;
			if(c == '#')while(true){ c = fgetc(file); if((c == EOF)||(c == '\n'))break; }
			if((c == EOF)||(c == '\n'))break;
			if(isspace(c))c = ' ';
			line[lineSize] = (char)c;
			lineSize++;
		}
		line[lineSize] = 0;
		lineCount++;
		if(lineSize == 0)continue;
		if(handle == 0){
			int num = 0;
			if(sscanf(line,"%d",&num) != 1){
				fclose(file);
				sprintf(error,"%s line %d: Should be a number of tiles",path,lineCount);
				return -1;
			}else if(num <= 0){
				fclose(file);
				sprintf(error,"%s line %d: Number of tiles cannot be %d",path,lineCount,num);
				return -1;
			}
			tiles.resize(num);
			for(size_t n = 0; n<tiles.size(); n++)tiles.at(n).Construct();
			handle++;
		}else{
			if(handle - 1 >= tiles.size()){
				fclose(file);
				sprintf(error,"%s: Number of tiles %d on first line is incorrect",path,tiles.size());
				Free();
				return -1;
			}
			size_t pos = 0, last = 0, count = 0; SDL_Surface *surf = NULL;
			while(true){
				while((pos < lineSize)&&(line[pos] != ' '))pos++;
				line[pos] = 0;
				if(surf == NULL){
					sprintf(path2,"%s/%s",root,line + last);
					surf = SDLLoad(path2);
					if(surf == NULL){
						sprintf(error,"%s: Could not load %s",path,path2);
						fclose(file);
						Free();
						return -1;
					}
				}else{
					int num;
					if(sscanf(line + last,"%d",&num) != 1){
						sprintf(error,"%s line %d: Duration expected, got [%s]",path,lineCount,line + last);
						fclose(file);
						Free();
						return -1;
					}else if(num < 0){
						sprintf(error,"%s line %d: Duration %d invalid",path,lineCount,num);
						fclose(file);
						Free();
						return -1;
					}
					tiles.at(handle - 1).AddFrame(surf,num);
					surf = NULL;
					count++;
				}
				if(pos < lineSize)pos++;
				while((pos < lineSize)&&(line[pos] == ' '))pos++;
				if(pos >= lineSize)break;
				last = pos;
			}
			if(surf != NULL){
				tiles.at(handle - 1).AddFrame(surf,0);
				count++;
			}
			if(count == 0){
				sprintf(error,"%s line %d: Invalid tile",path,lineCount);
				fclose(file);
				Free();
				return -1;
			}
			handle++;
		}
	}
	fclose(file);
	if(handle == 0){
		sprintf(error,"%s: Empty file. First line should be number of tiles",path);
		return -1;
	}else if(handle == 1){
		sprintf(error,"%s: Second line should be an image filename",path);
		return -1;
	}else if(handle - 1 != tiles.size()){
		sprintf(error,"%s: Number of loaded tiles (%d) don't match the first line (%d)",path,handle-1,tiles.size());
		Free();
		return -1;
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

bool GTGTileSet::IsValidID(int id){
	return !((id<0)||(id>=(int)tiles.size()));
}
