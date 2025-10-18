#include "AA_Ghoul.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

enum GHOUL_STATE {
    GHOUL_FALLING,
    GHOUL_RUNNING,
    GHOUL_ATTACKING,
    GHOUL_HURT
};

AA_Ghoul::AA_Ghoul(float x, float y, float width, float height) : AA_Enemy(x, y, width, height)
{
    
}

void AA_Ghoul::Init()
{
    frames[0] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul1.png");
    frames[1] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul2.png");
    frames[2] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul3.png");
    frames[3] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul4.png");
    frames[4] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul5.png");
    frames[5] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul6.png");
    frames[6] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul7.png");
    frames[7] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/ghoul/ghoul8.png");

    frame_counter = -1;

    moving_right = true;

    current_state = GHOUL_FALLING;
}

void AA_Ghoul::Update()
{
    switch(current_state)
    {
        case GHOUL_FALLING : {
            FallingStateUpdate();
        };
        break;

        case GHOUL_RUNNING : {
            RunningStateUpdate();
        };
        break;

        case GHOUL_ATTACKING : {

        };
        break;

        case GHOUL_HURT : {

        };
        break;
    }
}

void AA_Ghoul::Render()
{
    switch(current_state)
    {
        case GHOUL_FALLING : {
            FallingStateRender();
        };
        break;

        case GHOUL_RUNNING : {
            RunningStateRender();
        };
        break;

        case GHOUL_ATTACKING : {

        };
        break;

        case GHOUL_HURT : {

        };
        break;
    }
}

void AA_Ghoul::FallingStateUpdate()
{
    bool collision_bottom_left;
    bool collision_bottom_right;

    velocity_y += gravity;

    float new_y = data.y + velocity_y;

    
    collision_bottom_left = CheckCollision(data.x, new_y + data.h);
    collision_bottom_right = CheckCollision(data.x + data.w, new_y + data.h);

    if(collision_bottom_left || collision_bottom_right)
    {
        velocity_y = 0;
        current_state = GHOUL_RUNNING;
    }
    else
        data.y = new_y;
}

void AA_Ghoul::FallingStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderTexture(AA_RefLinks::GetRenderer(), frames[0], nullptr, &dst);
}

void AA_Ghoul::RunningStateUpdate()
{
    float new_x = data.x;
    bool collision_bottom_left;
    bool collision_bottom_right;

    if(moving_right)
        new_x += speed;
    else
        new_x -= speed;

    collision_bottom_left = CheckCollision(new_x, data.y + data.h + 1);
    collision_bottom_right = CheckCollision(new_x + data.w, data.y + data.h + 1);

    if(!collision_bottom_left || !collision_bottom_right)
        moving_right = !moving_right;
    else
        data.x = new_x;

    frame_counter++;

    if(frame_counter > 63)
        frame_counter = 0;
}

void AA_Ghoul::RunningStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(!moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), frames[frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), frames[frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}