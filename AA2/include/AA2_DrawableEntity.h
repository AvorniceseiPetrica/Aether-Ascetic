#pragma once

#include "AA2_Entity.h"

class AA2_DrawableEntity : public AA2_Entity
{
    protected:

        SDL_Texture *texture = nullptr;

    public:

        AA2_DrawableEntity(float x, float y, float width, float height);
        virtual ~AA2_DrawableEntity() = default;
        virtual void Init() = 0;
};