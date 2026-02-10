#pragma once

#include "AA_Enemy.h"
#include "AA_Animation.h"
#include <map>

enum GHOUL_STATES {
    GHOUL_FALL,
    GHOUL_RUN,
    GHOUL_ATTACK,
    GHOUL_HURT
};

class AA_Ghoul : public AA_Enemy
{
    private:

        GHOUL_STATES current_state;
        float velocity_y;
        int speed = 5;
        float gravity = 0.5;
        bool moving_right;

        SDL_FRect hitbox;
        float hitbox_offset_x;
        float hitbot_offset_y;
        int hitpoints = 3;
        int time_since_last_hit;
        float knockback_direction = 1.0;
        float knockback_velocity;
        int knocked_out_timer = 0;

        std::map<GHOUL_STATES, AA_Animation*> animations;
        AA_Animation *current_animation = nullptr;

        void SetState(GHOUL_STATES new_state);
        void UpdateHitbox();
        void ApplyGravity();
        void HandleRunning();
        void HandleHurt();

    public:

        AA_Ghoul(float x, float y, float width, float height, int health);
        virtual ~AA_Ghoul() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void TakeDamage(bool to_right) override;
};