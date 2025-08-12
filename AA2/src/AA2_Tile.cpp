#include "AA2_Tile.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"

AA2_Tile::AA2_Tile(int p_id, std::string texture_path)
{
    if(p_id < 0)
        SDL_Log("\n\tAA2_Tile::AA2_Tile\t<< Invalid tile id >>\n\n");
    else
        id = p_id;

    texture = AA2_TextureLoader::LoadTexture(texture_path);
}

void AA2_Tile::Render(float x, float y)
{
    SDL_FRect dst = {
        .x = x,
        .y = y,
        .w = 192,
        .h = 192
    };

    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), texture, nullptr, &dst);
}