#include "AA_Prop.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

AA_Prop::AA_Prop(float x, float y, float width, float height, std::string p_texture_path) : AA_DrawableEntity(x, y, width, height)
{
    texture_path = p_texture_path;
}

AA_Prop::~AA_Prop()
{

}

void AA_Prop::Init()
{
    texture = AA_TextureLoader::LoadTexture(texture_path);
}

void AA_Prop::Update()
{

}

void AA_Prop::Render()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderTexture(AA_RefLinks::GetRenderer(), texture, nullptr, &dst);
}