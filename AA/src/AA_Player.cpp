#include "AA_Player.h"
#include "AA_RefLinks.h"

AA_Player::AA_Player(float x, float y) : AA_Creature(x, y, 150, 150)
{
    
}

void AA_Player::SetState(PLAYER_STATES new_state)
{
    if(current_state == new_state)
        return;

    current_state = new_state;
    current_animation = animations[current_state];
}

void AA_Player::HandleHorizontalMovement()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    float new_x = data.x;

    if(keys[SDL_SCANCODE_D])
    {
        new_x += speed;
        moving_right = true;
    }

    if(keys[SDL_SCANCODE_A])
    {
        new_x -= speed;
        moving_right = false;
    }

    if(!HandleCollisions(new_x, data.y))
        data.x = new_x;
}

void AA_Player::ApplyGravity()
{
    float new_y = data.y;

    velocity_y += gravity;
    new_y += velocity_y;

    if(!HandleCollisions(data.x, new_y))
        data.y = new_y;
    else
    {
        current_state = PLAYER_IDLE;   
        velocity_y = 0;
    }
}

bool AA_Player::CheckCollision(float x, float y)
{
    int tile_x = (int)(x / TILE_WIDTH);
    int tile_y = (int)(y / TILE_HEIGHT);

    int tile_id = AA_RefLinks::GetMap()->GetTileId(tile_x, tile_y);

    return AA_RefLinks::GetMap()->IsTileSolid(tile_id);
}

bool AA_Player::HandleCollisions(float new_x, float new_y)
{
    return (CheckCollision(new_x + 30, new_y) || 
            CheckCollision(new_x + data.w - 30, new_y) || 
            CheckCollision(new_x + 30, new_y + data.h) || 
            CheckCollision(new_x + data.w - 30, new_y + data.h)
        );
}

void AA_Player::CalculateHitbox(float offset_x, float offset_y)
{
    body_hitbox.x = data.x;
    body_hitbox.y = data.y;
}

void AA_Player::Init()
{
    moving_right = true;
    velocity_y = 0;
    time_since_last_hit = 0;

    animations[PLAYER_IDLE] = new AA_Animation
    (
        {
            "assets/sprites/player/idle/idle1.png",
            "assets/sprites/player/idle/idle2.png",
            "assets/sprites/player/idle/idle3.png",
            "assets/sprites/player/idle/idle4.png"
        },
        8
    );
    animations[PLAYER_WALK] = new AA_Animation
    (
        {
            "assets/sprites/player/walk/walk1.png",
            "assets/sprites/player/walk/walk2.png",
            "assets/sprites/player/walk/walk3.png",
            "assets/sprites/player/walk/walk4.png",
            "assets/sprites/player/walk/walk5.png",
            "assets/sprites/player/walk/walk6.png"
        },
        8
    );
    animations[PLAYER_FALL] = new AA_Animation
    (
        {
            "assets/sprites/player/fall/fall1.png",
            "assets/sprites/player/fall/fall2.png"
        },
        8
    );

    body_hitbox.w = 150;
    body_hitbox.h = 150;
    CalculateHitbox(0, 0);

    SetState(PLAYER_FALL);
}

void AA_Player::Update()
{
    CalculateHitbox(0, 0);

    const bool *keys = SDL_GetKeyboardState(nullptr);

    time_since_last_hit++;

    if(current_state == PLAYER_IDLE || current_state == PLAYER_WALK)
    {
        if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_D])
            SetState(PLAYER_WALK);
        else
            SetState(PLAYER_IDLE);
    }

    HandleHorizontalMovement();
    ApplyGravity();

    current_animation->Update();
}

void AA_Player::Render()
{
    SDL_FRect dst = {
        .x = data.x - AA_RefLinks::GetCamera()->GetViewPort().x,
        .y = data.y - AA_RefLinks::GetCamera()->GetViewPort().y,
        .w = width,
        .h = height
    };

    SDL_RenderTexture(AA_RefLinks::GetRenderer(), current_animation->GetFrame(), nullptr, &dst);
}

SDL_FRect* AA_Player::GetBodyHitbox()
{
    return &body_hitbox;
}

SDL_FRect AA_Player::GetActionHitbox()
{
    return body_hitbox;
}

PLAYER_STATES AA_Player::GetCurrentState()
{
    return current_state;
}

void AA_Player::TakeDamage()
{
    
}

bool AA_Player::IsMovingRight()
{
    return moving_right;
}

void AA_Player::ChangePosition(float x, float y)
{
    data.x = x;
    data.y = y;
}