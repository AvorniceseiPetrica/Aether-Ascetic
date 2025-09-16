#include "AA_TileManager.h"

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

AA_TileManager::AA_TileManager()
{
    for(int i = 0; i < TILE_COUNT; ++i)
        tiles[i] = nullptr;
}

AA_TileManager::~AA_TileManager()
{
    for(auto tile : tiles)
        if(tile != nullptr)
            delete tile;
}

void AA_TileManager::Init()
{
    tiles[NOTHING] = new AA_Tile(NOTHING, "assets/tiles/empty.png", NOT_SOLID);
    tiles[GROUND1] = new AA_Tile(GROUND1, "assets/tiles/ground1.png", SOLID);
    tiles[GROUND2] = new AA_Tile(GROUND2, "assets/tiles/ground2.png", SOLID);
    tiles[BRICK1] = new AA_Tile(BRICK1, "assets/tiles/brick1.png", SOLID);
    tiles[BRICK2] = new AA_Tile(BRICK2, "assets/tiles/brick2.png", SOLID);
    tiles[BRICK3] = new AA_Tile(BRICK3, "assets/tiles/brick3.png", SOLID);
    tiles[BRICK4] = new AA_Tile(BRICK4, "assets/tiles/brick4.png", SOLID);
    tiles[BRICK_BELOW1] = new AA_Tile(BRICK_BELOW1, "assets/tiles/brick_below1.png", SOLID);
    tiles[BRICK_BELOW2] = new AA_Tile(BRICK_BELOW2, "assets/tiles/brick_below2.png", SOLID);
    tiles[BRICK_BELOW3] = new AA_Tile(BRICK_BELOW3, "assets/tiles/brick_below3.png", SOLID);
    tiles[BRICK_DARK1] = new AA_Tile(BRICK_DARK1, "assets/tiles/brick_dark1.png", SOLID);
    tiles[BRICK_DARK2] = new AA_Tile(BRICK_DARK2, "assets/tiles/brick_dark2.png", SOLID);
    tiles[BRICK_DARK3] = new AA_Tile(BRICK_DARK3, "assets/tiles/brick_dark3.png", SOLID);
    tiles[BRICK_GRASSY1] = new AA_Tile(BRICK_GRASSY1, "assets/tiles/brick_grassy1.png", SOLID);
    tiles[BRICK_GRASSY2] = new AA_Tile(BRICK_GRASSY2, "assets/tiles/brick_grassy2.png", SOLID);
    tiles[PILLAR] = new AA_Tile(PILLAR, "assets/tiles/pillar.png", SOLID);
    tiles[PILLAR_GRASSY] = new AA_Tile(PILLAR_GRASSY, "assets/tiles/pillar_grassy.png", SOLID);

    SDL_Log("Initialized tile manager...\n");
}

AA_Tile* AA_TileManager::GetTile(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA_TileManager::GetTile()\t<< Invalid tile id >>\n\n");
    else
        return tiles[id];
    
    return nullptr;
}

bool AA_TileManager::IsTileSolid(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA_TileManager::IsTileSolid()\t<< Invalid tile id >>\n\n");

    return tiles[id]->IsSolid();
}