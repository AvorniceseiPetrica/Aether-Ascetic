#include "AA_Enemy.h"

#include "AA_Config.h"
#include "AA_RefLinks.h"

AA_Enemy::AA_Enemy(float x, float y, float width, float height) : AA_Creature(x, y, width, height)
{

}

bool AA_Enemy::CheckCollision(float x, float y)
{
    int tile_x = (int)(x / TILE_WIDTH);
    int tile_y = (int)(y / TILE_HEIGHT);

    int tile_id = AA_RefLinks::GetMap()->GetTileId(tile_x, tile_y);

    return AA_RefLinks::GetMap()->IsTileSolid(tile_id);
}