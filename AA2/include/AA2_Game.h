#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include "AA2_World.h"

class AA2_Game
{
    private:

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        AA2_World world;

        bool is_running;

    public:

        AA2_Game() = default;
        ~AA2_Game() = default;
        void InitSDL(std::string window_name, int window_width, int window_height);
        void DestroySDL();
        void Init(std::string window_name, int window_width, int window_height);
        void HandleEvents();
        void Update();
        void Render();
        void Run();
};