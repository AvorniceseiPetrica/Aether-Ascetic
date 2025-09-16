#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class AA_TextureLoader
{
    public:

        static SDL_Texture* LoadTexture(std::string texture_path);
};