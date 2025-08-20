#pragma once

#include <SDL3/SDL.h>
#include "AA2_Creature.h"

class AA2_Player : public AA2_Creature
{
    private:

        float speed = 10;
        float width = 150;
        float height = 150;
        SDL_Texture *texture = nullptr;

    public:

        AA2_Player(float x, float y);
        ~AA2_Player() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        SDL_FRect* GetRect();
};