#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include "AA_State.h"

class AA_Game
{
    private:

        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

        bool is_running;
        
        AA_State *current_state = nullptr;

    public:

        AA_Game() = default;
        ~AA_Game() = default;
        void InitSDL(std::string window_name, int window_width, int window_height);
        void DestroySDL();
        void Init(std::string window_name, int window_width, int window_height);
        void HandleEvents();
        void Update();
        void Render();
        void Run();
        void ChangeState(AA_State *new_state);
};