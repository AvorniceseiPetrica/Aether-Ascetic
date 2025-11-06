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

        SDL_Texture* walk[6];
        int walk_frame_counter;

        SDL_Texture* jump[2];
        int jump_frame_counter;

        SDL_Texture* fall[2];
        int fall_frame_counter;

        SDL_Texture* idle[4];
        int idle_frame_counter;

        SDL_Texture* punch[6];
        int punch_frame_counter;

        SDL_Texture* kick[5];
        int kick_frame_counter;

        SDL_Texture* crouch[2];
        int crouch_frame_counter;

        SDL_Texture* crouch_kick[5];
        int crouch_kick_frame_counter;

        SDL_Texture* flying_kick[2];
        int flying_kick_frame_counter;

        SDL_Texture *red, *green, *blue;

        bool kicked_mid_air;

        SDL_FRect punch_hitbox;
        int punch_hitbox_offset_x;
        int punch_hitbox_offset_y;
        
        SDL_FRect kick_hitbox;
        int kick_hitbox_offset_x;
        int kick_hitbox_offset_y;

        SDL_FRect crouch_kick_hitbox;
        int crouch_kick_hitbox_offset_x;
        int crouch_kick_hitbox_offset_y;

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
        void CrouchStateUpdate();
        void CrouchStateRender();
        void PunchStateUpdate();
        void PunchStateRender();
        void KickStateUpdate();
        void KickStateRender();
        void CrouchKickStateUpdate();
        void CrouchKickStateRender();
        void FlyingKickStateUpdate();
        void FlyingKickStateRender();
        bool IsMovingRight();

};