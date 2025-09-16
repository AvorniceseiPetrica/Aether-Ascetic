#pragma once

#include "AA_Entity.h"

class AA_DrawableEntity : public AA_Entity
{
    protected:

        SDL_Texture *texture = nullptr;

    public:

        AA_DrawableEntity(float x, float y, float width, float height);
        virtual ~AA_DrawableEntity() = default;
        virtual void Init() = 0;
};