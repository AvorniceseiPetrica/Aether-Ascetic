#include "AA2_Camera.h"

#include "AA2_Config.h"

AA2_Camera::AA2_Camera()
{
    viewport.w = 1920;
    viewport.h = 1080;
}

void AA2_Camera::SetTarget(SDL_FRect *p_target)
{
    if(p_target != nullptr)
        target = p_target;
}

void AA2_Camera::Update()
{
    viewport.x = target->x - viewport.w / 2;
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