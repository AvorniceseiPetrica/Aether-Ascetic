#pragma once

#include <SDL3/SDL.h>
#include <string>

class AA_MenuButton
{
    private:

        SDL_FRect rect;
        SDL_Texture *unpressed_texture = nullptr;
        SDL_Texture *pressed_texture = nullptr;
        bool is_pressed = false;

    public:

        AA_MenuButton(float x, float y, float width, float height, std::string unpressed_texture_path, std::string pressed_texture_path);
        ~AA_MenuButton();
        void Update();
        void Render();
        void SetIfPressed(bool pressed_value);
};