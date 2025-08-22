#pragma once

#include "AA2_Level.h"
#include <vector>

class AA2_LevelManager
{
    private:
    
        std::vector<AA2_Level> levels;
        int current_level_id;
        AA2_Level *current_level = nullptr;

    public:

        AA2_LevelManager(std::string levels_config_path);
        ~AA2_LevelManager() = default;
        void Init();
        void Update();
        void Render();
        void ChangeLevel(int level_id);
};