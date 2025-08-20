#pragma once

#include <SDL3/SDL.h>

class AA2_Entity
{
    protected:

        SDL_FRect data;

    public:

        AA2_Entity(float x, float y, float width, float height);
        virtual ~AA2_Entity() = default;
        virtual void Update() = 0;
        virtual void Render() = 0;
};