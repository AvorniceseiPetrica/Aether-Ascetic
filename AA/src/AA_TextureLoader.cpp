#include "AA_TextureLoader.h"

#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include "AA_RefLinks.h"

SDL_Texture* AA_TextureLoader::LoadTexture(std::string texture_path)
{   
    SDL_Surface *surface = IMG_Load(texture_path.c_str());

    if(surface == nullptr)
    {
        SDL_Log("\n\tAA_TextureLoader::LoadTexture()\t<< Failed to load surface from file: %s >>\n", texture_path.c_str());
        SDL_Log("\tSDL_GetError():\t%s\n\n", SDL_GetError());
    }
    else
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(AA_RefLinks::GetRenderer(), surface);

        if(texture == nullptr)
        {
            SDL_Log("\n\tAA_TextureLoader::LoadTexture()\t<< Failed to create texture from surface: %s >>\n", texture_path.c_str());
            SDL_Log("\tSDL_GetError():\t%s\n\n", SDL_GetError());
        }
         
        else
            return texture;
    }

    return nullptr;
}