#pragma once

#include <SDL3/SDL.h>

class AA2_Player
{
    private:

        SDL_FRect data;
        float speed = 10;
        float width = 100;
        float height = 100;
        SDL_Texture *texture = nullptr;

    public:

        AA2_Player(float x, float y);
        ~AA2_Player() = default;
        void Init();
        void Update();
        void Render();
        SDL_FRect* GetRect();
};