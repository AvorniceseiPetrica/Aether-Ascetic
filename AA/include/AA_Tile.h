#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class AA_Tile
{
    private:

        int id;
        SDL_Texture *texture;
        bool is_solid;

    public:

        AA_Tile(int p_id, std::string texture_path, bool p_is_solid);
        ~AA_Tile() = default;
        void Render(float x, float y);
        bool IsSolid();
};