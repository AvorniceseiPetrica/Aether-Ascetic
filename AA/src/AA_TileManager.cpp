#include "AA_TileManager.h"

enum TILES {
    // all levels

    NOTHING,
    BARRIER,

    // level 0

    BRICK_DARK0,
    BRICK_DARK_1, // shoukd be BRICK_DARK-1 but oh well
    PILLAR_DARK0,
    PILLAR_DARK0_GRASSY,

    // level 1

    BRICK_DARK1,
    BRICK_DARK2,
    BRICK_DARK3,
    BRICK_DARK4,
    BRICK_DARK5,
    PILLAR_DARK1,
    PILLAR_DARK1_GRASSY,

    // level 2

    BRICK1,
    BRICK2,
    BRICK3,
    BRICK4,
    BRICK_BELOW1,
    BRICK_BELOW2,
    BRICK_BELOW3,
    BRICK_GRASSY1,
    BRICK_GRASSY2,
    
    // level 3
    
    GROUND1,
    GROUND2,
    GROUND3
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
    // all levels
                    
    tiles[NOTHING] = new AA_Tile(NOTHING, "assets/tiles/empty.png", NOT_SOLID);
    tiles[BARRIER] = new AA_Tile(BARRIER, "assets/tiles/empty.png", SOLID);
    
    // level 0
    
    tiles[BRICK_DARK0] = new AA_Tile(BRICK_DARK0, "assets/tiles/level0/brick_dark0.png", SOLID);
    tiles[BRICK_DARK_1] = new AA_Tile(BRICK_DARK_1, "assets/tiles/level0/brick_dark-1.png", SOLID);
    tiles[PILLAR_DARK0] = new AA_Tile(PILLAR_DARK0, "assets/tiles/level0/pillar_dark0.png", NOT_SOLID);
    tiles[PILLAR_DARK0_GRASSY] = new AA_Tile(PILLAR_DARK0_GRASSY, "assets/tiles/level0/pillar_dark0_grassy.png", NOT_SOLID);

    // level 1

    tiles[BRICK_DARK1] = new AA_Tile(BRICK_DARK1, "assets/tiles/level1/brick_dark1.png", SOLID);
    tiles[BRICK_DARK2] = new AA_Tile(BRICK_DARK2, "assets/tiles/level1/brick_dark2.png", SOLID);
    tiles[BRICK_DARK3] = new AA_Tile(BRICK_DARK3, "assets/tiles/level1/brick_dark3.png", SOLID);
    tiles[BRICK_DARK4] = new AA_Tile(BRICK_DARK4, "assets/tiles/level1/brick_dark4.png", SOLID);
    tiles[BRICK_DARK5] = new AA_Tile(BRICK_DARK5, "assets/tiles/level1/brick_dark5.png", SOLID);
    tiles[PILLAR_DARK1] = new AA_Tile(PILLAR_DARK1, "assets/tiles/level1/pillar_dark1.png", NOT_SOLID);
    tiles[PILLAR_DARK1_GRASSY] = new AA_Tile(PILLAR_DARK1_GRASSY, "assets/tiles/level1/pillar_dark1_grassy.png", NOT_SOLID);

    // level 2

    tiles[BRICK1] = new AA_Tile(BRICK1, "assets/tiles/level2/brick1.png", SOLID);
    tiles[BRICK2] = new AA_Tile(BRICK2, "assets/tiles/level2/brick2.png", SOLID);
    tiles[BRICK3] = new AA_Tile(BRICK3, "assets/tiles/level2/brick3.png", SOLID);
    tiles[BRICK4] = new AA_Tile(BRICK4, "assets/tiles/level2/brick4.png", SOLID);
    tiles[BRICK_BELOW1] = new AA_Tile(BRICK_BELOW1, "assets/tiles/level2/brick_below1.png", SOLID);
    tiles[BRICK_BELOW2] = new AA_Tile(BRICK_BELOW2, "assets/tiles/level2/brick_below2.png", SOLID);
    tiles[BRICK_BELOW3] = new AA_Tile(BRICK_BELOW3, "assets/tiles/level2/brick_below3.png", SOLID);
    tiles[BRICK_GRASSY1] = new AA_Tile(BRICK_GRASSY1, "assets/tiles/level2/brick_grassy1.png", SOLID);
    tiles[BRICK_GRASSY2] = new AA_Tile(BRICK_GRASSY2, "assets/tiles/level2/brick_grassy2.png", SOLID);
    
    // level 3

    tiles[GROUND1] = new AA_Tile(GROUND1, "assets/tiles/level3/ground1.png", SOLID);
    tiles[GROUND2] = new AA_Tile(GROUND2, "assets/tiles/level3/ground2.png", SOLID);
    tiles[GROUND3] = new AA_Tile(GROUND3, "assets/tiles/level3/ground3.png", SOLID);

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