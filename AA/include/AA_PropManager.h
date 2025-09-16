#pragma once

#include "AA_Prop.h"
#include <vector>

class AA_PropManager
{
    private:

        std::vector<AA_Prop> props;

    public:

        AA_PropManager() = default;
        ~AA_PropManager() = default;
        void Init();
        void LoadProps(std::string props_config_path);
        void Update();
        void Render();

};