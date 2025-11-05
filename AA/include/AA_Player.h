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
        float velocity_x = 0;
        bool on_ground = false;
        bool in_air = true;
        bool moving_right = true;

        SDL_Texture* walking[6];
        int walking_frame_counter;

        SDL_Texture* jumping[2];
        int jumping_frame_counter;

        SDL_Texture* falling[2];
        int falling_frame_counter;

        SDL_Texture* idle[4];
        int idle_frame_counter;

        SDL_Texture* punching[6];
        int punching_frame_counter;

        SDL_Texture* kicking[5];
        int kicking_frame_counter;

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
        void WalkStateUpdate();
        void WalkStateRender();
        void JumpStateUpdate();
        void JumpStateRender();
        void FallStateUpdate();
        void FallStateRender();
        void PunchStateUpdate();
        void PunchStateRender();
        void KickStateUpdate();
        void KickStateRender();
        bool IsMovingRight();

};