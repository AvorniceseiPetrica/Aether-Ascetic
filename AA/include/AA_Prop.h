#pragma once

#include "AA_DrawableEntity.h"
#include <iostream>

class AA_Prop : public AA_DrawableEntity
{
    private:

        std::string texture_path;

    public:

        AA_Prop(float x, float y, float width, float height, std::string p_texture_path);
        ~AA_Prop();
        void Init() override;
        void Update() override;
        void Render() override;

};