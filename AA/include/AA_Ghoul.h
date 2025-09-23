#pragma once

#include "AA_Enemy.h"

class AA_Ghoul : public AA_Enemy
{
    private:

        SDL_Texture *frames[8];

        int frame_counter;
        int current_state;
        float velocity_y;
        int speed = 7;
        bool moving_right;

    public:

        AA_Ghoul(float x, float y, float width, float height);
        virtual ~AA_Ghoul() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void FallingStateUpdate();
        void FallingStateRender();
        void RunningStateUpdate();
        void RunningStateRender();
};