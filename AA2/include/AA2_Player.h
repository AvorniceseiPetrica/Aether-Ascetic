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
        int current_state;
        float gravity_strength = 1;
        float jump_strength = 30;
        float velocity_y = 0;
        bool on_ground;
        bool in_air;
        bool moving_right;

    public:

        AA2_Player(float x, float y);
        ~AA2_Player() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        SDL_FRect* GetRect();
        void ChangePosition(float x, float y);
        bool CheckCollision(float x, float y);
        void IdleStateUpdate();
        void IdleStateRender();
        void RunningStateUpdate();
        void RunningStateRender();
        void JumpingStateUpdate();
        void JumpingStateRender();
        bool IsMovingRight();

};