#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class AA2_Game
{
    private:

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

        bool is_running;

    public:

        void InitSDL(std::string window_name, int window_width, int window_height);
        void Init(std::string window_name, int window_width, int window_height);
        void Update();
        void Render();
        void Run();
};