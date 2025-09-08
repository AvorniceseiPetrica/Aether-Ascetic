#include "AA2_Player.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"
#include "AA2_Config.h"

enum PLAYER_STATE {
    PLAYER_IDLE,
    PLAYER_RUNNING,
    PLAYER_JUMPING
};

AA2_Player::AA2_Player(float x, float y) : AA2_Creature(x, y, 0, 0)
{
    
}

void AA2_Player::Init()
{
    texture = AA2_TextureLoader::LoadTexture("assets/tiles/red.png");
    data.w = width;
    data.h = height;

    current_state = PLAYER_JUMPING;

    SDL_Log("Player initialized...\n");
}

void AA2_Player::Update()
{
    switch (current_state)
    {
        case PLAYER_IDLE: IdleStateUpdate();
        break;

        case PLAYER_RUNNING: RunningStateUpdate();
        break;

        case PLAYER_JUMPING: JumpingStateUpdate();
    }
}

void AA2_Player::Render()
{
    switch(current_state)
    {
        case PLAYER_IDLE: IdleStateRender();
        break;

        case PLAYER_RUNNING: RunningStateRender();
        break;

        case PLAYER_JUMPING: JumpingStateRender();
        break;
    }
}

SDL_FRect* AA2_Player::GetRect()
{
    return &data;
}

void AA2_Player::ChangePosition(float x, float y)
{
    data.x = x;
    data.y = y;
}

bool AA2_Player::CheckCollision(float x, float y)
{
    int tile_x = (int)(x / TILE_WIDTH);
    int tile_y = (int)(y / TILE_HEIGHT);

    int tile_id = AA2_RefLinks::GetMap()->GetTileId(tile_y, tile_x);

    return AA2_RefLinks::GetMap()->IsTileSolid(tile_id);
}

void AA2_Player::IdleStateUpdate()
{
    current_state = PLAYER_RUNNING;
}

void AA2_Player::IdleStateRender()
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

void AA2_Player::RunningStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    int new_x = data.x;
    int new_y = data.y;
    bool collision_top_left;
    bool collision_top_right;
    bool collision_bottom_left;
    bool collision_bottom_right;

    if(keys[SDL_SCANCODE_A])
        new_x -= speed;
    if(keys[SDL_SCANCODE_D])
        new_x += speed;

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
    }

    collision_bottom_left = CheckCollision(data.x, data.y + height);
    collision_bottom_right + CheckCollision(data.x + width, data.y + height);

    if(!collision_bottom_left && !collision_bottom_right)
    {
        current_state = PLAYER_JUMPING;
        on_ground = false;
    }
}

void AA2_Player::RunningStateRender()
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

void AA2_Player::JumpingStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    float new_x = data.x;
    bool collision_top_left;
    bool collision_top_right;
    bool collision_bottom_left;
    bool collision_bottom_right;

    velocity_y += gravity_strength;

    float new_y = data.y + velocity_y;

    collision_bottom_left = CheckCollision(data.x, new_y + height);
    collision_bottom_right = CheckCollision(data.x + width, new_y + height);

    if(collision_bottom_left || collision_bottom_right)
    {
        on_ground = true;
        velocity_y = 0;
        current_state = PLAYER_RUNNING;
    }
    else
        data.y = new_y;

    if(keys[SDL_SCANCODE_A])
        new_x -= speed;
    if(keys[SDL_SCANCODE_D])
        new_x += speed;

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

void AA2_Player::JumpingStateRender()
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
