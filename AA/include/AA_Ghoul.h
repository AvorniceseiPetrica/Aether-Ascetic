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
        float gravity = .1;
        bool moving_right;

        SDL_FRect hitbox;
        float hitbox_offset_x;
        float hitbot_offset_y;
        int hitpoints = 3;

    public:

        AA_Ghoul(float x, float y, float width, float height);
        virtual ~AA_Ghoul() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void FallStateUpdate();
        void FallStateRender();
        void RunStateUpdate();
        void RunStateRender();
};