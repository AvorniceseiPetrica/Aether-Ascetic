#pragma once

#include <iostream>

#include "AA2_Config.h"
#include "AA2_TileManager.h"


class AA2_Map
{
    private:

        int tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH];
        AA2_TileManager tile_manager;

    public:

        AA2_Map();
        ~AA2_Map() = default;
        void Init();
        void LoadMap(std::string map_path);
        void Render();
        void PrintInfo();
};