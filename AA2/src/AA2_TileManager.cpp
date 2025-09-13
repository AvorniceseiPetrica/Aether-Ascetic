#include "AA2_TileManager.h"

enum TILES {
    NOTHING,
    GROUND1,
    GROUND2,
    BRICK1,
    BRICK2,
    BRICK3,
    BRICK4,
    BRICK_BELOW1,
    BRICK_BELOW2,
    BRICK_BELOW3,
    BRICK_DARK1,
    BRICK_DARK2,
    BRICK_DARK3,
    BRICK_GRASSY1,
    BRICK_GRASSY2,
    PILLAR,
    PILLAR_GRASSY
};

#define SOLID true
#define NOT_SOLID false

AA2_TileManager::AA2_TileManager()
{
    for(int i = 0; i < TILE_COUNT; ++i)
        tiles[i] = nullptr;
}

AA2_TileManager::~AA2_TileManager()
{
    for(auto tile : tiles)
        if(tile != nullptr)
            delete tile;
}

void AA2_TileManager::Init()
{
    tiles[NOTHING] = new AA2_Tile(NOTHING, "assets/tiles/empty.png", NOT_SOLID);
    tiles[GROUND1] = new AA2_Tile(GROUND1, "assets/new/ground1.png", SOLID);
    tiles[GROUND2] = new AA2_Tile(GROUND2, "assets/new/ground2.png", SOLID);
    tiles[BRICK1] = new AA2_Tile(BRICK1, "assets/new/brick1.png", SOLID);
    tiles[BRICK2] = new AA2_Tile(BRICK2, "assets/new/brick2.png", SOLID);
    tiles[BRICK3] = new AA2_Tile(BRICK3, "assets/new/brick3.png", SOLID);
    tiles[BRICK4] = new AA2_Tile(BRICK4, "assets/new/brick4.png", SOLID);
    tiles[BRICK_BELOW1] = new AA2_Tile(BRICK_BELOW1, "assets/new/brick_below1.png", SOLID);
    tiles[BRICK_BELOW2] = new AA2_Tile(BRICK_BELOW2, "assets/new/brick_below2.png", SOLID);
    tiles[BRICK_BELOW3] = new AA2_Tile(BRICK_BELOW3, "assets/new/brick_below3.png", SOLID);
    tiles[BRICK_DARK1] = new AA2_Tile(BRICK_DARK1, "assets/new/brick_dark1.png", SOLID);
    tiles[BRICK_DARK2] = new AA2_Tile(BRICK_DARK2, "assets/new/brick_dark2.png", SOLID);
    tiles[BRICK_DARK3] = new AA2_Tile(BRICK_DARK3, "assets/new/brick_dark3.png", SOLID);
    tiles[BRICK_GRASSY1] = new AA2_Tile(BRICK_GRASSY1, "assets/new/brick_grassy1.png", SOLID);
    tiles[BRICK_GRASSY2] = new AA2_Tile(BRICK_GRASSY2, "assets/new/brick_grassy2.png", SOLID);
    tiles[PILLAR] = new AA2_Tile(PILLAR, "assets/new/pillar.png", SOLID);
    tiles[PILLAR_GRASSY] = new AA2_Tile(PILLAR_GRASSY, "assets/new/pillar_grassy.png", SOLID);

    SDL_Log("Initialized tile manager...\n");
}

AA2_Tile* AA2_TileManager::GetTile(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA2_TileManager::GetTile()\t<< Invalid tile id >>\n\n");
    else
        return tiles[id];
    
    return nullptr;
}

bool AA2_TileManager::IsTileSolid(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA2_TileManager::IsTileSolid()\t<< Invalid tile id >>\n\n");

    return tiles[id]->IsSolid();
}