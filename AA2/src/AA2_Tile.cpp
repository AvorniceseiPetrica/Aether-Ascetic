#include "AA2_Tile.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"
#include "AA2_Config.h"

AA2_Tile::AA2_Tile(int p_id, std::string texture_path, bool p_is_solid)
{
    if(p_id < 0)
        SDL_Log("\n\tAA2_Tile::AA2_Tile\t<< Invalid tile id >>\n\n");
    else
        id = p_id;

    texture = AA2_TextureLoader::LoadTexture(texture_path);
    is_solid = p_is_solid;
}

void AA2_Tile::Render(float x, float y)
{
    SDL_FRect dst = {
        .x = x,
        .y = y,
        .w = TILE_WIDTH,
        .h = TILE_HEIGHT
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), texture, nullptr, &dst);
}