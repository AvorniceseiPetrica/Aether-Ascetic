#pragma once

#include "AA2_DrawableEntity.h"

class AA2_Creature : public AA2_DrawableEntity
{
    protected:

        int health;

    public:

        AA2_Creature(float x, float y, float width, float height);
        virtual ~AA2_Creature() = default;
};