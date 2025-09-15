#pragma once

#include "AA2_Camera.h"
#include "AA2_LevelManager.h"

class AA2_World
{
    private:

        AA2_Camera camera;
        AA2_LevelManager *level_manager = nullptr;

    public:

        AA2_World() = default;
        ~AA2_World();
        void Init();
        void Update();
        void Render();
};