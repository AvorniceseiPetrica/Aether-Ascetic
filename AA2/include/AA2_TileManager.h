#pragma once

#include <vector>

#include "AA2_Tile.h"

class AA2_TileManager
{
    private:

        AA2_Tile *tiles[3];

    public:

        AA2_TileManager();
        ~AA2_TileManager();
        void Init();
        AA2_Tile* GetTile(int id);
};