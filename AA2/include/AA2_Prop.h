#pragma once

#include "AA2_DrawableEntity.h"
#include <iostream>

class AA2_Prop : public AA2_DrawableEntity
{
    private:

        std::string texture_path;

    public:

        AA2_Prop(float x, float y, float width, float height, std::string p_texture_path);
        ~AA2_Prop();
        void Init() override;
        void Update() override;
        void Render() override;

};