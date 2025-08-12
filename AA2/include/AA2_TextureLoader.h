#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class AA2_TextureLoader
{
    public:

        static SDL_Texture* LoadTexture(std::string texture_path);
};