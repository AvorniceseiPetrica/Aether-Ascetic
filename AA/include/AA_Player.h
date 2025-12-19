#pragma once

#include <SDL3/SDL.h>
#include "AA_Creature.h"
#include "AA_Animation.h"

enum PLAYER_STATES {
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_JUMP,
    PLAYER_FALL,
    PLAYER_CROUCH,
    PLAYER_PUNCH,
    PLAYER_KICK,
    PLAYER_CROUCH_KICK,
    PLAYER_FLYING_KICK
};

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

        int time_since_last_hit;

        SDL_FRect body_hitbox;
        int body_hitbox_offset_x;
        int body_hitbox_offset_y;

        AA_Animation *idle_animation;
        AA_Animation *walk_animation;
        AA_Animation *jump_animation;
        AA_Animation *fall_animation;
        AA_Animation *punch_animation;
        AA_Animation *kick_animation;
        AA_Animation *crouch_animation;

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
        int GetCurrentState();
        SDL_FRect GetPunchHitbox();
        void TakeDamage();
        SDL_FRect GetBodyHitbox();
};