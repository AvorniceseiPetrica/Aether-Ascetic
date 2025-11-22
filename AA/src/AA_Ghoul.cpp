#include "AA_Ghoul.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

enum GHOUL_STATES {
    GHOUL_FALL,
    GHOUL_RUN,
    GHOUL_ATTACK,
    GHOUL_HURT
};

AA_Ghoul::AA_Ghoul(float x, float y, float width, float height, int health) : AA_Enemy(x, y, width, height)
{
    this->health = health;
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

    current_state = GHOUL_FALL;
    velocity_y = 0;

    hitbox.w = 128;
    hitbox.h = 128;
    hitbot_offset_y = 64;
    
    time_since_last_hit = 0;
}

void AA_Ghoul::Update()
{
    if(moving_right)
        hitbox_offset_x = 48;
    else
        hitbox_offset_x = 15;

    hitbox.x = data.x - AA_RefLinks::GetCamera()->GetViewPort().x + hitbox_offset_x;
    hitbox.y = data.y - AA_RefLinks::GetCamera()->GetViewPort().y + hitbot_offset_y;

    switch(current_state)
    {
        case GHOUL_FALL: FallStateUpdate();
        break;

        case GHOUL_RUN: RunStateUpdate();
        break;

        case GHOUL_ATTACK:
        break;

        case GHOUL_HURT: HurtStateUpdate();
        break;
    }
}

void AA_Ghoul::Render()
{
    switch(current_state)
    {
        case GHOUL_FALL: FallStateRender();
        break;

        case GHOUL_RUN:  RunStateRender();
        break;

        case GHOUL_ATTACK: 
        break;

        case GHOUL_HURT: HurtStateRender();
        break;
    }
}

void AA_Ghoul::FallStateUpdate()
{
    bool collision_bottom_left;
    bool collision_bottom_right;
    int tile_y;

    velocity_y += gravity;

    if(velocity_y > 30)
        velocity_y = 30;

    float new_y = data.y + velocity_y;

    
    collision_bottom_left = CheckCollision(data.x, new_y + data.h - 1);
    collision_bottom_right = CheckCollision(data.x + data.w, new_y + data.h - 1);

    if(collision_bottom_left || collision_bottom_right)
    {
        tile_y = (int)(new_y + data.h) / TILE_HEIGHT;
        data.y = (tile_y) * TILE_HEIGHT - data.h - 1;
        velocity_y = 0;
        current_state = GHOUL_RUN;
    }
    else
        data.y = new_y;
}

void AA_Ghoul::FallStateRender()
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

void AA_Ghoul::RunStateUpdate()
{
    float new_x = data.x;
    bool collision_bottom_left;
    bool collision_bottom_right;
    bool collision_middle_left;
    bool collision_middle_right;

    if(AA_RefLinks::GetPlayer()->GetCurrentState() == PLAYER_PUNCH)
    {
        SDL_FRect punch_hitbox = AA_RefLinks::GetPlayer()->GetPunchHitbox();

        if(SDL_HasRectIntersectionFloat(&punch_hitbox, &data))
        {
            current_state = GHOUL_HURT;
            health--;

            if(AA_RefLinks::GetPlayer()->IsMovingRight())
                knockback_direction = 1.0;
            else
                knockback_direction = -1.0;

            knockback_velocity = 50;

            return;
        }
    }

    if(moving_right)
        new_x += speed;
    else
        new_x -= speed;

    collision_bottom_left = CheckCollision(new_x, data.y + data.h + 1);
    collision_bottom_right = CheckCollision(new_x + data.w, data.y + data.h + 1);
    collision_middle_left = CheckCollision(new_x, data.y + data.h / 2);
    collision_middle_right = CheckCollision(new_x + data.w, data.y + data.h / 2);

    if(!collision_bottom_left || !collision_bottom_right || collision_middle_left || collision_middle_right)
        moving_right = !moving_right;
    else
        data.x = new_x;

    frame_counter++;

    if(frame_counter > 63)
        frame_counter = 0;
}

void AA_Ghoul::RunStateRender()
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

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &hitbox);
}

void AA_Ghoul::HurtStateUpdate()
{
    float new_x;
    bool collision_left;
    bool collision_right;

    printf("Health: %d\n", health);

    if(health == 0)
        exit(0);
    
    data.x += knockback_velocity * knockback_direction;
    knockback_velocity *= 0.9;

    collision_left = CheckCollision(new_x, data.y + data.h / 2);
    collision_right = CheckCollision(new_x + data.w, data.y + data.h / 2);

    if(!collision_left && !collision_right)
        data.x = new_x;

    if(knockback_velocity < 1)
        current_state = GHOUL_RUN;
}

void AA_Ghoul::HurtStateRender()
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

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &hitbox);
}