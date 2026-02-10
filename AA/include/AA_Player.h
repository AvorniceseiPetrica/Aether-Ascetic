#pragma once

#include <SDL3/SDL.h>
#include "AA_Creature.h"
#include "AA_Animation.h"
#include <map>

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

        int width = 150;
        int height = 150;
        const float speed = 10;
        const float gravity = 1;
        const float jump_strength = 30;

        PLAYER_STATES current_state;
        bool moving_right;
        float velocity_y;
        int time_since_last_hit;
        
        std::map<PLAYER_STATES, AA_Animation*> animations;
        AA_Animation *current_animation = nullptr;

        SDL_FRect body_hitbox;
        SDL_FRect attack_hitbox;

        void SetState(PLAYER_STATES new_state);
        void HandleHorizontalMovement();
        void ApplyGravity();
        bool CheckCollision(float x, float y);
        bool HandleCollisions(float new_x, float new_y);
        void UpdateBodyHitbox();
        void UpdateAttackHitbox();

    public:

        AA_Player(float x, float y);
        ~AA_Player() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        SDL_FRect* GetData();
        SDL_FRect* GetBodyHitbox();
        SDL_FRect GetAttackHitbox();
        PLAYER_STATES GetCurrentState();
        void TakeDamage();
        bool IsMovingRight();
        void ChangePosition(float x, float y);
        void ChangeState(PLAYER_STATES new_state);
        int GetHealth();
};