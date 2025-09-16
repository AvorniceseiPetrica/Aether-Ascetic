#include "AA2_Camera.h"

#include "AA2_Config.h"
#include "AA2_RefLinks.h"

AA2_Camera::AA2_Camera()
{
    viewport.w = WINDOW_WIDTH;
    viewport.h = WINDOW_HEIGHT;
}

void AA2_Camera::SetTarget(SDL_FRect *p_target)
{
    if(p_target != nullptr)
        target = p_target;
}

void AA2_Camera::Update()
{
    float desired_offset_x;

    if(AA2_RefLinks::GetPlayer()->IsMovingRight())
        desired_offset_x = target_offset_x;
    else
        desired_offset_x = -target_offset_x;

    current_offset_x += (desired_offset_x - current_offset_x) * 0.05;

    viewport.x = target->x - viewport.w / 2 + current_offset_x;
    viewport.y = target->y - viewport.h / 2;

    if(viewport.x < 0)
        viewport.x = 0;

    if(viewport.y < 0)
        viewport.y = 0;

    if(viewport.x + viewport.w > MAP_WIDTH)
        viewport.x = MAP_WIDTH - viewport.w;

    if(viewport.y + viewport.h > MAP_HEIGHT)
        viewport.y = MAP_HEIGHT - viewport.h;
}

SDL_FRect AA2_Camera::GetViewPort()
{
    return viewport;
}