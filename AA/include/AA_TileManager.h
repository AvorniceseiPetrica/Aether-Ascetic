#pragma once

#include <vector>

#include "AA_Tile.h"
#include "AA_Config.h"

class AA_TileManager
{
    private:

        AA_Tile *tiles[TILE_COUNT];

    public:

        AA_TileManager();
        ~AA_TileManager();
        void Init();
        AA_Tile* GetTile(int id);
        bool IsTileSolid(int id);
};