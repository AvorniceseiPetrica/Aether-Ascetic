#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class AA2_Tile
{
    private:

        int id;
        SDL_Texture *texture;

    public:

        AA2_Tile(int p_id, std::string texture_path);
        ~AA2_Tile() = default;
        void Render(float x, float y);
};