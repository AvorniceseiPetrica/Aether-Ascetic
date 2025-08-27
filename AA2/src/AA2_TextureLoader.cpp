#include "AA2_TextureLoader.h"

#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include "AA2_RefLinks.h"

SDL_Texture* AA2_TextureLoader::LoadTexture(std::string texture_path)
{   
    SDL_Surface *surface = IMG_Load(texture_path.c_str());

    if(surface == nullptr)
        SDL_Log("\n\t<< Failed to load surface from file: %s >>", texture_path.c_str());
    else
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(AA2_RefLinks::GetRenderer(), surface);

        if(texture == nullptr)
        {
            SDL_Log("\n\t<< Failed to create texture from surface: %s >>\n\n", texture_path.c_str());
            SDL_Log("Error: %s", SDL_GetError());
        }
         
        else
            return texture;
    }

    return nullptr;
}