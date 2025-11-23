#pragma once

#include "AA_Enemy.h"

class AA_Ghoul : public AA_Enemy
{
    private:

        SDL_Texture *frames[8];

        int frame_counter;
        int current_state;
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

    public:

        AA_Ghoul(float x, float y, float width, float height, int health);
        virtual ~AA_Ghoul() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void FallStateUpdate();
        void FallStateRender();
        void RunStateUpdate();
        void RunStateRender();
        void HurtStateUpdate();
        void HurtStateRender();
        void TakeDamage(bool to_right) override;
};