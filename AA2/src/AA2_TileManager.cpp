#include "AA2_TileManager.h"

enum TILES {
    RED,
    GREEN,
    BLUE
};

AA2_TileManager::AA2_TileManager()
{
    
}

AA2_TileManager::~AA2_TileManager()
{
    for(auto tile : tiles)
        if(tile != nullptr)
            delete tile;
}

void AA2_TileManager::Init()
{
    tiles[RED] = new AA2_Tile(RED, "assets/textures/tiles/red.png");
    tiles[GREEN] = new AA2_Tile(GREEN, "assets/textures/tiles/green.png");
    tiles[BLUE] = new AA2_Tile(BLUE, "assets/textures/tiles/blue.png");
}

AA2_Tile* AA2_TileManager::GetTile(int id)
{
    if(id < 0)
        SDL_Log("\n\tAA2_TileManager::GetTile()\t << Invalid tile id >>\n\n");
    else
        return tiles[id];
    
    return nullptr;
}