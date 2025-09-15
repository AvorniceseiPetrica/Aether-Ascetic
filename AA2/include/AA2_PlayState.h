#pragma once

#include "AA2_State.h"
#include "AA2_World.h"

class AA2_PlayState : public AA2_State
{
    private:

        AA2_World world;

    public:

        AA2_PlayState() = default;
        ~AA2_PlayState() = default;
        void Init() override;
        void Update() override;
        void Render() override;
};