#pragma once

#include <SDL3/SDL.h>

class AA2_Camera
{
    private:

        SDL_FRect viewport;
        SDL_FRect *target;

        float camera_zoom_factor = 0.5;

    public:

        AA2_Camera();
        ~AA2_Camera() = default;
        void SetTarget(SDL_FRect *p_target);
        void Update();
        SDL_FRect GetViewPort();
};