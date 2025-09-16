#include "AA_Tile.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_Config.h"

AA_Tile::AA_Tile(int p_id, std::string texture_path, bool p_is_solid)
{
    if(p_id < 0)
        SDL_Log("\n\tAA_Tile::AA_Tile\t<< Invalid tile id >>\n\n");
    else
        id = p_id;

    texture = AA_TextureLoader::LoadTexture(texture_path);
    is_solid = p_is_solid;
}

void AA_Tile::Render(float x, float y)
{
    SDL_FRect dst = {
        .x = x,
        .y = y,
        .w = TILE_WIDTH,
        .h = TILE_HEIGHT
    };

    SDL_RenderTexture(AA_RefLinks::GetRenderer(), texture, nullptr, &dst);
}

bool AA_Tile::IsSolid()
{
    return is_solid;
}