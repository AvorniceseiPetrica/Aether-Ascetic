#pragma once

#include "AA2_Prop.h"
#include <vector>

class AA2_PropManager
{
    private:

        std::vector<AA2_Prop> props;
        std::string props_config_path;

    public:

        AA2_PropManager(std::string p_props_config_path);
        ~AA2_PropManager() = default;
        void Init();
        void LoadProps();
        void Update();
        void Render();

};