#pragma once

#include <iostream>

#include "AA_Config.h"
#include "AA_TileManager.h"


class AA_Map
{
    private:

        int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH];
        AA_TileManager tile_manager;

    public:

        AA_Map();
        ~AA_Map() = default;
        void Init();
        void LoadMap(std::string map_path);
        void Render();
        void PrintInfo();
        int GetTileId(int x, int y);
        bool IsTileSolid(int id);
};