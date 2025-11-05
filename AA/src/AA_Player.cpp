#include "AA_Player.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_Config.h"

enum PLAYER_STATES {
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_JUMP,
    PLAYER_FALL,
    PLAYER_CROUCH,
    PLAYER_PUNCH,
    PLAYER_KICK,
    PLAYER_CROUCH_KICK,
    PLAYER_FLYING_KICK
};

AA_Player::AA_Player(float x, float y) : AA_Creature(x, y, 0, 0)
{
    
}

void AA_Player::Init()
{
    texture = AA_TextureLoader::LoadTexture("assets/sprites/player.png");
    data.w = width;
    data.h = height;

    current_state = PLAYER_FALL;

    walking[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk1.png");
    walking[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk2.png");
    walking[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk3.png");
    walking[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk4.png");
    walking[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk5.png");
    walking[5] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk6.png");
    
    walking_frame_counter = -1;

    jumping[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/jump/jump1.png");
    jumping[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/jump/jump2.png");

    jumping_frame_counter = -1;

    falling[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/fall/fall1.png");
    falling[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/fall/fall2.png");

    falling_frame_counter = -1;

    idle[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle1.png");
    idle[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle2.png");
    idle[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle3.png");
    idle[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle4.png");

    idle_frame_counter = -1;

    punching[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch1.png");
    punching[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch2.png");
    punching[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch3.png");
    punching[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch4.png");
    punching[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch5.png");
    punching[5] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch6.png");

    punching_frame_counter = -1;

    kicking[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick1.png");
    kicking[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick2.png");
    kicking[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick3.png");
    kicking[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick4.png");
    kicking[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick5.png");

    kicking_frame_counter = -1;

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

        case PLAYER_WALK: WalkStateUpdate();
        break;

        case PLAYER_JUMP: JumpStateUpdate();
        break;

        case PLAYER_FALL: FallStateUpdate();
        break;

        case PLAYER_CROUCH: break;

        case PLAYER_PUNCH: PunchStateUpdate();
        break;

        case PLAYER_KICK: KickStateUpdate();
        break;

        case PLAYER_CROUCH_KICK: break;

        case PLAYER_FLYING_KICK: break;
    }
}

void AA_Player::Render()
{
    switch(current_state)
    {
        case PLAYER_IDLE: IdleStateRender();
        break;

        case PLAYER_WALK: WalkStateRender();
        break;

        case PLAYER_JUMP: JumpStateRender();
        break;

        case PLAYER_FALL: FallStateRender();
        break;

        case PLAYER_PUNCH: PunchStateRender();
        break;

        case PLAYER_KICK: KickStateRender();
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
        
    int tile_id = AA_RefLinks::GetMap()->GetTileId(tile_x, tile_y);

    return AA_RefLinks::GetMap()->IsTileSolid(tile_id);
}

void AA_Player::IdleStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_W])
    {
        current_state = PLAYER_JUMP;
        on_ground = false;
        velocity_y -= jump_strength;
        return;
    }

    if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_D])
    {
        current_state = PLAYER_WALK;
        return;
    }

    if(keys[SDL_SCANCODE_F])
    {
        current_state = PLAYER_PUNCH;
        return;
    }

    if(keys[SDL_SCANCODE_LSHIFT])
    {
        current_state = PLAYER_KICK;
        return;
    }

    idle_frame_counter++;

    if(idle_frame_counter > 31)
        idle_frame_counter = 0;
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

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), idle[idle_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), idle[idle_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::WalkStateUpdate()
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

    if(new_x == data.x)
        current_state = PLAYER_IDLE;

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
        current_state = PLAYER_JUMP;
        on_ground = false;
        velocity_y -= jump_strength;
        return;
    }

    collision_bottom_left = CheckCollision(data.x, data.y + height + 1);
    collision_bottom_right = CheckCollision(data.x + width, data.y + height + 1);

    if(!collision_bottom_left && !collision_bottom_right)
    {
        current_state = PLAYER_FALL;
        on_ground = false;
        return;
    }

    walking_frame_counter++;
    
    if(walking_frame_counter> 47)
        walking_frame_counter = 0;
    
}

void AA_Player::WalkStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), walking[walking_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), walking[walking_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::JumpStateUpdate()
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
        current_state = PLAYER_FALL;
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

    jumping_frame_counter++;

    if(jumping_frame_counter > 15)
        jumping_frame_counter = 0;
}

void AA_Player::JumpStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), jumping[jumping_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), jumping[jumping_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::FallStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    float new_x = data.x;
    float new_y;
    int tile_y;
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
        tile_y = (int)(new_y + height) / TILE_HEIGHT;
        data.y = (tile_y) * TILE_HEIGHT - height - 1;
        on_ground = true;
        velocity_y = 0;
        current_state = PLAYER_IDLE;
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

    falling_frame_counter++;

    if(falling_frame_counter > 15)
        falling_frame_counter = 0;
}

void AA_Player::FallStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), falling[falling_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), falling[falling_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::PunchStateUpdate()
{
    punching_frame_counter++;

    if(punching_frame_counter > 47)
    {
        punching_frame_counter = -1;
        current_state = PLAYER_IDLE;
        return;
    }
}

void AA_Player::PunchStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), punching[punching_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), punching[punching_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::KickStateUpdate()
{
    kicking_frame_counter++;

    if(kicking_frame_counter > 39)
    {
        kicking_frame_counter = -1;
        current_state = PLAYER_IDLE;
        return;
    }
}

void AA_Player::KickStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), kicking[kicking_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), kicking[kicking_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

bool AA_Player::IsMovingRight()
{
    return moving_right;
}