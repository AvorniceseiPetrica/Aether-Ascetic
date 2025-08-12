#include "AA2_TileManager.h"

enum TILES {
    NOTHING,
    BLACK,
    CEILING1,
    CEILING2,
    GROUND1,
    GROUND2
};

#define SOLID true
#define NOT_SOLID false

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
    tiles[NOTHING] = new AA2_Tile(NOTHING, "assets/textures/tiles/empty.png", NOT_SOLID);
    tiles[BLACK] = new AA2_Tile(BLACK, "assets/textures/tiles/black.png", SOLID);
    tiles[CEILING1] = new AA2_Tile(CEILING1, "assets/textures/tiles/ceiling1.png", SOLID);
    tiles[CEILING2] = new AA2_Tile(CEILING2, "assets/textures/tiles/ceiling2.png", SOLID);
    tiles[GROUND1] = new AA2_Tile(GROUND1, "assets/textures/tiles/ground1.png", SOLID);
    tiles[GROUND2] = new AA2_Tile(GROUND2, "assets/textures/tiles/ground2.png", SOLID);
}

AA2_Tile* AA2_TileManager::GetTile(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA2_TileManager::GetTile()\t << Invalid tile id >>\n\n");
    else
        return tiles[id];
    
    return nullptr;
}