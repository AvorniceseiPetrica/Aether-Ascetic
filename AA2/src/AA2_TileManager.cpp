#include "AA2_TileManager.h"

enum TILES {
    NOTHING,
    BLACK,
    CEILING1,
    CEILING2,
    GROUND1,
    GROUND2,
    WALL_LEFT,
    WALL_RIGHT,
    CORNER_LOWER_LEFT,
    CORNER_LOWER_RIGHT,
    CORNER_UPPER_LEFT,
    CORNER_UPPER_RIGHT,
    CONNECT_LOWER_LEFT,
    CONNECT_LOWER_RIGHT,
    CONNECT_UPPER_LEFT,
    CONNECT_UPPER_RIGHT
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
    tiles[WALL_LEFT] = new AA2_Tile(WALL_LEFT, "assets/textures/tiles/wall_left.png", SOLID);
    tiles[WALL_RIGHT] = new AA2_Tile(WALL_RIGHT, "assets/textures/tiles/wall_right.png", SOLID);
    tiles[CORNER_LOWER_LEFT] = new AA2_Tile(CONNECT_LOWER_LEFT, "assets/textures/tiles/corner_lower_left.png", SOLID);
    tiles[CORNER_LOWER_RIGHT] = new AA2_Tile(CORNER_LOWER_RIGHT, "assets/textures/tiles/corner_lower_right.png", SOLID);
    tiles[CORNER_UPPER_LEFT] = new AA2_Tile(CORNER_UPPER_LEFT, "assets/textures/tiles/corner_upper_left.png", SOLID);
    tiles[CORNER_UPPER_RIGHT] = new AA2_Tile(CORNER_UPPER_RIGHT, "assets/textures/tiles/corner_upper_right.png", SOLID);
    tiles[CONNECT_LOWER_LEFT] = new AA2_Tile(CONNECT_LOWER_LEFT, "assets/textures/tiles/connect_lower_left.png", SOLID);
    tiles[CONNECT_LOWER_RIGHT] = new AA2_Tile(CONNECT_LOWER_RIGHT, "assets/textures/tiles/connect_lower_right.png", SOLID);
    tiles[CONNECT_UPPER_LEFT] = new AA2_Tile(CONNECT_UPPER_LEFT, "assets/textures/tiles/connect_upper_left.png", SOLID);
    tiles[CONNECT_UPPER_RIGHT] = new AA2_Tile(CONNECT_UPPER_RIGHT, "assets/textures/tiles/connect_upper_right.png", SOLID);
}

AA2_Tile* AA2_TileManager::GetTile(int id)
{
    if(id < 0 || id >= TILE_COUNT)
        SDL_Log("\n\tAA2_TileManager::GetTile()\t << Invalid tile id >>\n\n");
    else
        return tiles[id];
    
    return nullptr;
}