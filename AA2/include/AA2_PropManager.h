#pragma once

#include "AA2_Prop.h"
#include <vector>

class AA2_PropManager
{
    private:

        std::vector<AA2_Prop> props;

    public:

        AA2_PropManager() = default;
        ~AA2_PropManager() = default;
        void Init();
        void LoadProps(std::string props_config_path);
        void Update();
        void Render();

};