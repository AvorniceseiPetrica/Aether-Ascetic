#include "AA2_Prop.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"

AA2_Prop::AA2_Prop(float x, float y, float width, float height, std::string p_texture_path) : AA2_DrawableEntity(x, y, width, height)
{
    texture_path = p_texture_path;
}

AA2_Prop::~AA2_Prop()
{

}

void AA2_Prop::Init()
{
    texture = AA2_TextureLoader::LoadTexture(texture_path);
}

void AA2_Prop::Update()
{

}

void AA2_Prop::Render()
{
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), texture, nullptr, &data);
}