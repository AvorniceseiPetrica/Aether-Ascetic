#pragma once

#include "AA_DrawableEntity.h"

class AA_Creature : public AA_DrawableEntity
{
    protected:

        int health;

    public:

        AA_Creature(float x, float y, float width, float height);
        virtual ~AA_Creature() = default;
};