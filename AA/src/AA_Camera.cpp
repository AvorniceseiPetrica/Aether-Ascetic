#include "AA_Camera.h"

#include "AA_Config.h"
#include "AA_RefLinks.h"

AA_Camera::AA_Camera()
{
    viewport.w = WINDOW_WIDTH;
    viewport.h = WINDOW_HEIGHT;
}

void AA_Camera::SetTarget(SDL_FRect *p_target)
{
    if(p_target != nullptr)
        target = p_target;
}

void AA_Camera::Update()
{
    float desired_offset_x;

    if(AA_RefLinks::GetPlayer()->IsMovingRight())
        desired_offset_x = target_offset_x;
    else
        desired_offset_x = -target_offset_x;

    current_offset_x += (desired_offset_x - current_offset_x) * switch_direction_strength;

    viewport.x = target->x - viewport.w / 2 + current_offset_x;
    viewport.y = target->y - viewport.h / 2;

    if(viewport.x < 192)
        viewport.x = 192;

    if(viewport.y < 0)
        viewport.y = 0;

    if(viewport.x + viewport.w > MAP_WIDTH - TILE_WIDTH * 2 - TILE_WIDTH * 0.80)
        viewport.x = MAP_WIDTH - viewport.w - TILE_WIDTH * 2 - TILE_WIDTH * 0.80;

    if(viewport.y + viewport.h > MAP_HEIGHT - TILEMAP_HEIGHT)
        viewport.y = MAP_HEIGHT - viewport.h - TILE_HEIGHT;
}

SDL_FRect AA_Camera::GetViewPort()
{
    return viewport;
}