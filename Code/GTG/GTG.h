#pragma once
#ifndef _GTG_H_
#define _GTG_H_

#include "SDLHelper.h"
#include <vector>
#include "GTGTile.h"
#include "GTGMap.h"
#include "GTGPlayer.h"

class GTG
{
    GTGTileSet tileset;
    GTGMap map;

    char error[128];

public:
    GTG();
    ~GTG();
    void Construct();
    void Destruct();
    bool Load(const char *root);
    void Free();
    int Run(); //-1 = error, 0 = no error, 1 = force quit
    const char *GetLastError();
};

#endif
