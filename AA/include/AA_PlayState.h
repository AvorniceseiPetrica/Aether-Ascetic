#pragma once

#include "AA_State.h"
#include "AA_World.h"

class AA_PlayState : public AA_State
{
    private:

        AA_World world;

    public:

        AA_PlayState() = default;
        ~AA_PlayState() = default;
        void Init() override;
        void HandleEvents();
        void Update() override;
        void Render() override;
};