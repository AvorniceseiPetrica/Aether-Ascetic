#pragma once

#include "AA_Creature.h"

enum ENEMY_TYPE {
    ENEMY_GHOUL,
    ENEMY_WIZARD
};

class AA_Enemy : public AA_Creature
{
    protected:

        int damage;
        int type;
        bool is_dead;

    public:

        AA_Enemy(float x, float y, float width, float height);
        virtual ~AA_Enemy() = default;
        virtual bool CheckCollision(float x, float y);
        SDL_FRect GetData();
        void SetHealth(int health);
        int GetHealth();
        bool IsDead();
        virtual void TakeDamage(bool to_right) = 0;
};