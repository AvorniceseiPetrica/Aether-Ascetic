#pragma once

#include <SDL3/SDL.h>

class AA_Camera
{
    private:

        SDL_FRect viewport;
        SDL_FRect *target;

        float target_offset_x = 600;
        float current_offset_x;

    public:

        AA_Camera();
        ~AA_Camera() = default;
        void SetTarget(SDL_FRect *p_target);
        void Update();
        SDL_FRect GetViewPort();
};