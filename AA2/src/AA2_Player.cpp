#include "AA2_Player.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"

AA2_Player::AA2_Player(float x, float y)
{
    data.x = x;
    data.y = y;
    data.w = width;
    data.h = height;
}

void AA2_Player::Init()
{
    texture = AA2_TextureLoader::LoadTexture("assets/textures/tiles/red.png");
}

void AA2_Player::Update()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_A])
        data.x -= speed;
    if(keys[SDL_SCANCODE_D])
        data.x += speed;
    if(keys[SDL_SCANCODE_W])
        data.y -= speed;
    if(keys[SDL_SCANCODE_S])
        data.y += speed;
}

void AA2_Player::Render()
{
    SDL_FRect camera = AA2_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    SDL_RenderTexture(AA2_RefLinks::GetRenderer(), texture, nullptr, &dst);
}

SDL_FRect* AA2_Player::GetRect()
{
    return &data;
}
