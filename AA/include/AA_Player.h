#pragma once

#include <SDL3/SDL.h>
#include "AA_Creature.h"

class AA_Player : public AA_Creature
{
    private:

        float speed = 10;
        float width = 150;
        float height = 150;
        SDL_Texture *texture = nullptr;
        int current_state;
        float gravity_strength = 1;
        float jump_strength = 28.5;
        float velocity_y = 0;
        bool on_ground;
        bool in_air;
        bool moving_right;

        SDL_Texture* walking[6];
        int walk_txt_count;

        SDL_Texture *red, *green, *blue;

    public:

        AA_Player(float x, float y);
        ~AA_Player() = default;
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
        void FallingStateUpdate();
        void FallingStateRender();
        bool IsMovingRight();

};