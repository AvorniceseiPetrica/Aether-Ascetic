#include "AA2_Player.h"

#include "AA2_TextureLoader.h"
#include "AA2_RefLinks.h"
#include "AA2_Config.h"

enum PLAYER_STATE {
    PLAYER_MOVING_STATE
};

AA2_Player::AA2_Player(float x, float y) : AA2_Creature(x, y, 0, 0)
{
    
}

void AA2_Player::Init()
{
    texture = AA2_TextureLoader::LoadTexture("assets/tiles/red.png");
    data.w = width;
    data.h = height;

    current_state = PLAYER_MOVING_STATE;

    SDL_Log("Player initialized...\n");
}

void AA2_Player::Update()
{
    switch (current_state)
    {
        case PLAYER_MOVING_STATE: MovingStateUpdate();
        break;

    }
}

void AA2_Player::Render()
{
    switch(current_state)
    {
        case PLAYER_MOVING_STATE: MovingStateRender();
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

void AA2_Player::MovingStateUpdate()
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
        new_y -= speed;
    if(keys[SDL_SCANCODE_S])
        new_y += speed;

    collision_top_left = CheckCollision(data.x, new_y);
    collision_top_right = CheckCollision(data.x + width, new_y);
    collision_bottom_left = CheckCollision(data.x, new_y + height);
    collision_bottom_right = CheckCollision(data.x + width, new_y + height);

    if(
        !collision_top_left &&
        !collision_top_right &&
        !collision_bottom_left &&
        !collision_bottom_right    
    )
        data.y = new_y;
}

void AA2_Player::MovingStateRender()
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
