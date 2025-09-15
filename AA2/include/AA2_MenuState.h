#pragma once

#include <SDL3/SDL.h>
#include "AA2_State.h"

class AA2_MenuState : public AA2_State
{
    private:

        SDL_Texture *background;

        SDL_FRect background_rect = {
            .x = 0,
            .y = 0,
            .w = 1920,
            .h = 1080
        };

        SDL_FRect start_game_rect = {
            .x = 1000,
            .y = 400,
            .w = 400,
            .h = 200
        };
        
        SDL_Texture *start_game_button;

        SDL_FRect quit_game_rect = {
            .x = 1000,
            .y = 800,
            .w = 400,
            .h = 200
        };
        
        SDL_Texture *quit_game_button;

    public:

        AA2_MenuState() = default;
        ~AA2_MenuState() = default;
        void Init() override;
        void Update() override;
        void Render() override;
};