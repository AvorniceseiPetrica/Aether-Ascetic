#pragma once

#include <vector>

#include "AA2_Tile.h"
#include "AA2_Config.h"

class AA2_TileManager
{
    private:

        AA2_Tile *tiles[TILE_COUNT];

    public:

        AA2_TileManager();
        ~AA2_TileManager();
        void Init();
        AA2_Tile* GetTile(int id);
        bool IsTileSolid(int id);
};