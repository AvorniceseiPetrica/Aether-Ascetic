#pragma once

#include "AA_Creature.h"

enum ENEMY_TYPE {
    ENEMY_GHOUL
};

class AA_Enemy : public AA_Creature
{
    protected:

        int damage;
        int type;

    public:

        AA_Enemy(float x, float y, float width, float height);
        virtual ~AA_Enemy() = default;
        virtual bool CheckCollision(float x, float y);
        SDL_FRect GetData();
};