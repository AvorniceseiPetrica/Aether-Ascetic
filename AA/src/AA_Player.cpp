#include "AA_Player.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_Config.h"

enum PLAYER_STATE {
    PLAYER_IDLE,
    PLAYER_RUNNING,
    PLAYER_JUMPING,
    PLAYER_FALLING
};

AA_Player::AA_Player(float x, float y) : AA_Creature(x, y, 0, 0)
{
    
}

void AA_Player::Init()
{
    texture = AA_TextureLoader::LoadTexture("assets/sprites/player.png");
    data.w = width;
    data.h = height;

    current_state = PLAYER_FALLING;

    walking[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk1.png");
    walking[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk2.png");
    walking[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk3.png");
    walking[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk4.png");
    walking[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk5.png");
    walking[5] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk6.png");

    red = AA_TextureLoader::LoadTexture("assets/sprites/red.png");
    green = AA_TextureLoader::LoadTexture("assets/sprites/green.png");
    blue = AA_TextureLoader::LoadTexture("assets/sprites/blue.png");

    SDL_Log("Player initialized...\n");
}

void AA_Player::Update()
{
    switch (current_state)
    {
        case PLAYER_IDLE: IdleStateUpdate();
        break;

        case PLAYER_RUNNING: {
            SDL_Log("RUNNING STATE | vy = %f\n", velocity_y);
            RunningStateUpdate();
        }
        break;

        case PLAYER_JUMPING: {
            SDL_Log("JUMPING STATE | vy = %f\n", velocity_y);
            JumpingStateUpdate();
        }
        break;

        case PLAYER_FALLING: {
            SDL_Log("FALLING STATE | vy = %f\n", velocity_y);
            FallingStateUpdate();
        }
        break;
    }
}

void AA_Player::Render()
{
    switch(current_state)
    {
        case PLAYER_IDLE: IdleStateRender();
        break;

        case PLAYER_RUNNING: RunningStateRender();
        break;

        case PLAYER_JUMPING: JumpingStateRender();
        break;

        case PLAYER_FALLING: FallingStateRender();
        break;
    }
}

SDL_FRect* AA_Player::GetRect()
{
    return &data;
}

void AA_Player::ChangePosition(float x, float y)
{
    data.x = x;
    data.y = y;
}

bool AA_Player::CheckCollision(float x, float y)
{
    int tile_x = (int)(x / TILE_WIDTH);
    int tile_y = (int)(y / TILE_HEIGHT);

    int tile_id = AA_RefLinks::GetMap()->GetTileId(tile_y, tile_x);

    return AA_RefLinks::GetMap()->IsTileSolid(tile_id);
}

void AA_Player::IdleStateUpdate()
{
    current_state = PLAYER_RUNNING;
}

void AA_Player::IdleStateRender()
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

void AA_Player::RunningStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    int new_x = data.x;
    bool collision_top_left;
    bool collision_top_right;
    bool collision_bottom_left;
    bool collision_bottom_right;

    if(keys[SDL_SCANCODE_A])
    {
        new_x -= speed;
        moving_right = false;
    }
    if(keys[SDL_SCANCODE_D])
    {
        new_x += speed;
        moving_right = true;
    }

    collision_top_left = CheckCollision(new_x, data.y);
    collision_top_right = CheckCollision(new_x + width, data.y);
    collision_bottom_left = CheckCollision(new_x, data.y + height);
    collision_bottom_right = CheckCollision(new_x + width, data.y + height);

    if(
        !collision_top_left &&
        !collision_top_right &&
        !collision_bottom_left &&
        !collision_bottom_right
    )
        data.x = new_x;

    if(keys[SDL_SCANCODE_W])
    {
        current_state = PLAYER_JUMPING;
        on_ground = false;
        velocity_y -= jump_strength;
        return;
    }

    collision_bottom_left = CheckCollision(data.x, data.y + height + 1);
    collision_bottom_right = CheckCollision(data.x + width, data.y + height + 1);

    if(!collision_bottom_left && !collision_bottom_right)
    {
        current_state = PLAYER_FALLING;
        on_ground = false;
        return;
    }

    walk_txt_count++;

    if(walk_txt_count > 36)
        walk_txt_count = 0;
}

void AA_Player::RunningStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), red, nullptr, &dst);
}

void AA_Player::JumpingStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    float new_x = data.x;
    float new_y;
    bool collision_top_left;
    bool collision_top_right;
    bool collision_bottom_left;
    bool collision_bottom_right;

    velocity_y += gravity_strength;
    new_y = data.y + velocity_y;

    collision_top_left = CheckCollision(data.x, new_y);
    collision_top_right = CheckCollision(data.x + width, new_y);

    if(collision_top_left || collision_top_right)
        velocity_y = 0;
    else
        data.y = new_y;

    if(velocity_y > 0)
    {
        current_state = PLAYER_FALLING;
        return;
    }

    if(keys[SDL_SCANCODE_A])
    {
        new_x -= speed;
        moving_right = false;
    }
    if(keys[SDL_SCANCODE_D])
    {
        new_x += speed;
        moving_right = true;
    }

    collision_top_left = CheckCollision(new_x, data.y);
    collision_top_right = CheckCollision(new_x + width, data.y);
    collision_bottom_left = CheckCollision(new_x, data.y + height);
    collision_bottom_right = CheckCollision(new_x + width, data.y + height);

    if(
        !collision_top_left &&
        !collision_top_right &&
        !collision_bottom_left &&
        !collision_bottom_right    
    )
        data.x = new_x;
}

void AA_Player::JumpingStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), green, nullptr, &dst);
}

void AA_Player::FallingStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    float new_x = data.x;
    float new_y;
    bool collision_top_left;
    bool collision_top_right;
    bool collision_bottom_left;
    bool collision_bottom_right;

    velocity_y += gravity_strength;
    new_y = data.y + velocity_y;

    collision_bottom_left = CheckCollision(data.x, new_y + height);
    collision_bottom_right = CheckCollision(data.x + width, new_y + height);

    if(collision_bottom_left || collision_bottom_right)
    {
        on_ground = true;
        velocity_y = 0;
        current_state = PLAYER_RUNNING;
        walk_txt_count = 0;
    }
    else
        data.y = new_y;

    if(keys[SDL_SCANCODE_A])
    {
        new_x -= speed;
        moving_right = false;
    }
    if(keys[SDL_SCANCODE_D])
    {
        new_x += speed;
        moving_right = true;
    }

    collision_top_left = CheckCollision(new_x, data.y);
    collision_top_right = CheckCollision(new_x + width, data.y);
    collision_bottom_left = CheckCollision(new_x, data.y + height);
    collision_bottom_right = CheckCollision(new_x + width, data.y + height);

    if(
        !collision_top_left &&
        !collision_top_right &&
        !collision_bottom_left &&
        !collision_bottom_right    
    )
        data.x = new_x;
}

void AA_Player::FallingStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), blue, nullptr, &dst);
}

bool AA_Player::IsMovingRight()
{
    return moving_right;
}
