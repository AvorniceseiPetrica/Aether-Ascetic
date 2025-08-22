#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include "AA2_Camera.h"
#include "AA2_LevelManager.h"

class AA2_Game
{
    private:

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        AA2_Camera C;
        AA2_LevelManager *LM;

        bool is_running;

    public:

        AA2_Game() = default;
        ~AA2_Game();
        void InitSDL(std::string window_name, int window_width, int window_height);
        void DestroySDL();
        void Init(std::string window_name, int window_width, int window_height);
        void HandleEvents();
        void Update();
        void Render();
        void Run();
};