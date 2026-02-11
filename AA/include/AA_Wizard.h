#pragma once

#include "AA_Enemy.h"
#include "AA_Animation.h"
#include <map>
#include "AA_Fireball.h"

enum WIZARD_STATES {
    WIZARD_IDLE_STATE,
    WIZARD_ATTACK_STATE,
    WIZARD_HURT_STATE
};

class AA_Wizard : public AA_Enemy
{
    private:

        WIZARD_STATES current_state;
        std::map<WIZARD_STATES, AA_Animation*> animations;
        AA_Animation *current_animation = nullptr;
        SDL_FRect vision;
        bool moving_right = false;
        std::vector<AA_Fireball*> fireballs;
        bool ready_to_shoot = false;
        float knockback_direction = 1.0;
        float knockback_velocity;
        int knocked_out_timer;
        int time_since_last_hit;
        float velocity_y = 0;
        float gravity = 1;
        SDL_FRect hitbox;

        void SetState(WIZARD_STATES new_state);
        void UpdateVision();
        void HandleHurt();

    public:

        AA_Wizard(float x, float y, float width, float height, int health);
        ~AA_Wizard() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void TakeDamage(bool to_right) override;
        SDL_FRect GetBodyHitbox() override;
};