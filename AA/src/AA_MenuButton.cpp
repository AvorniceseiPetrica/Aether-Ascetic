#include "AA_MenuButton.h"
#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

AA_MenuButton::AA_MenuButton(float x, float y, float width, float height, std::string unpressed_texture_path, std::string pressed_texture_path)
{
    rect = {x, y, width, height};
    unpressed_texture = AA_TextureLoader::LoadTexture(unpressed_texture_path);
    pressed_texture = AA_TextureLoader::LoadTexture(pressed_texture_path);
}

AA_MenuButton::~AA_MenuButton()
{
    // if(unpressed_texture)
    //     delete unpressed_texture;

    // if(pressed_texture)
    //     delete pressed_texture;
}

void AA_MenuButton::Update()
{

}

void AA_MenuButton::Render()
{
    if(is_pressed)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), pressed_texture, nullptr, &rect);
    else
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), unpressed_texture, nullptr, &rect);
}

void AA_MenuButton::SetIfPressed(bool pressed_value)
{
    is_pressed = pressed_value;
}