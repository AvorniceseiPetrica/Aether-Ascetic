#pragma once

#include <SDL3/SDL.h>
#include "AA_Config.h"
#include "AA_State.h"

#define BUTTON_WIDTH 400

class AA_MenuState : public AA_State
{
    private:

        SDL_Texture *background;

        SDL_FRect background_rect = {
            .x = 0,
            .y = 0,
            .w = WINDOW_WIDTH,
            .h = WINDOW_HEIGHT
        };

        SDL_FRect start_game_rect = {
            .x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
            .y = WINDOW_HEIGHT / 2 - 300,
            .w = BUTTON_WIDTH,
            .h = 200
        };
        
        SDL_Texture *start_game_button_unpressed;
        SDL_Texture *start_game_button_pressed;

        SDL_FRect quit_game_rect = {
            .x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2,
            .y = WINDOW_HEIGHT / 2 + 100,
            .w = 400,
            .h = 200
        };
        
        SDL_Texture *quit_game_button_unpressed;
        SDL_Texture *quit_game_button_pressed;

        bool start_game_pressed;
        bool quit_game_pressed;

    public:

        AA_MenuState() = default;
        ~AA_MenuState() = default;
        void Init() override;
        void Update() override;
        void Render() override;
};