#pragma once

#include "AA_Camera.h"
#include "AA_LevelManager.h"

class AA_World
{
    private:

        AA_Camera camera;
        AA_LevelManager *level_manager = nullptr;
        SDL_Texture *hearts[3];

    public:

        AA_World() = default;
        ~AA_World();
        void Init();
        void Update();
        void Render();
};