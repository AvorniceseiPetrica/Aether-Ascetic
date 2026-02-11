#pragma once

#include <SDL3/SDL.h>
#include "AA_DrawableEntity.h"
#include "AA_Animation.h"

class AA_Fireball : public AA_DrawableEntity
{
    private:

        int speed;
        int damage;
        bool moving_right;
        bool collided = false;

        AA_Animation *animation;

    public:

        AA_Fireball(float x, float y, float width, float height, bool moving_right);
        ~AA_Fireball() = default;
        void Init() override;   
        void Update() override;
        void Render() override;
        bool CheckCollision(float new_x, float new_y);
        bool HasCollided();
        SDL_FRect GetData();
};