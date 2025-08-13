#include "AA2_Camera.h"

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
    viewport.x = target->x - 1920/2;
    viewport.y = target->y - 1080/2;

    if(viewport.x < 0)
        viewport.x = 0;

    if(viewport.y < 0)
        viewport.y = 0;
}

SDL_FRect AA2_Camera::GetViewPort()
{
    return viewport;
}