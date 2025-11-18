#include "AA_Player.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include "AA_Config.h"

AA_Player::AA_Player(float x, float y) : AA_Creature(x, y, 0, 0)
{
    
}

void AA_Player::Init()
{
    texture = AA_TextureLoader::LoadTexture("assets/sprites/player.png");
    data.w = width;
    data.h = height;

    current_state = PLAYER_FALL;
    kicked_mid_air = false;

    walk[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk1.png");
    walk[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk2.png");
    walk[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk3.png");
    walk[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk4.png");
    walk[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk5.png");
    walk[5] = AA_TextureLoader::LoadTexture("assets/sprites/player/walk/walk6.png");
    
    walk_frame_counter = -1;

    jump[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/jump/jump1.png");
    jump[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/jump/jump2.png");

    jump_frame_counter = -1;

    fall[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/fall/fall1.png");
    fall[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/fall/fall2.png");

    fall_frame_counter = -1;

    idle[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle1.png");
    idle[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle2.png");
    idle[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle3.png");
    idle[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/idle/idle4.png");

    idle_frame_counter = -1;

    punch[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch1.png");
    punch[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch2.png");
    punch[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch3.png");
    punch[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch4.png");
    punch[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch5.png");
    punch[5] = AA_TextureLoader::LoadTexture("assets/sprites/player/punch/punch6.png");

    punch_frame_counter = -1;

    kick[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick1.png");
    kick[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick2.png");
    kick[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick3.png");
    kick[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick4.png");
    kick[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/kick/kick5.png");

    kick_frame_counter = -1;

    crouch[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch/crouch1.png");
    crouch[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch/crouch2.png");

    crouch_frame_counter = -1;

    crouch_kick[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch_kick/crouch_kick1.png");
    crouch_kick[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch_kick/crouch_kick2.png");
    crouch_kick[2] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch_kick/crouch_kick3.png");
    crouch_kick[3] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch_kick/crouch_kick4.png");
    crouch_kick[4] = AA_TextureLoader::LoadTexture("assets/sprites/player/crouch_kick/crouch_kick5.png");

    crouch_kick_frame_counter = -1;

    flying_kick[0] = AA_TextureLoader::LoadTexture("assets/sprites/player/flying_kick/flying_kick1.png");
    flying_kick[1] = AA_TextureLoader::LoadTexture("assets/sprites/player/flying_kick/flying_kick2.png");

    flying_kick_frame_counter = -1;

    red = AA_TextureLoader::LoadTexture("assets/sprites/red.png");
    green = AA_TextureLoader::LoadTexture("assets/sprites/green.png");
    blue = AA_TextureLoader::LoadTexture("assets/sprites/blue.png");

    punch_hitbox.w = 80. / 192 * 150;
    punch_hitbox.h = height;

    kick_hitbox.w = 96. / 192 * 150;
    kick_hitbox.h = height;

    crouch_kick_hitbox.w = 96. / 192 * 150;
    kick_hitbox.h = height;

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

        case PLAYER_CROUCH: CrouchStateUpdate();
        break;

        case PLAYER_PUNCH: PunchStateUpdate();
        break;

        case PLAYER_KICK: KickStateUpdate();
        break;

        case PLAYER_CROUCH_KICK: CrouchKickStateUpdate();
        break;

        case PLAYER_FLYING_KICK: FlyingKickStateUpdate();
        break;
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

        case PLAYER_CROUCH: CrouchStateRender();
        break;

        case PLAYER_PUNCH: PunchStateRender();
        break;

        case PLAYER_KICK: KickStateRender();
        break;

        case PLAYER_CROUCH_KICK: CrouchKickStateRender();
        break;

        case PLAYER_FLYING_KICK: FlyingKickStateRender();
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

    if(keys[SDL_SCANCODE_LCTRL])
    {
        current_state = PLAYER_CROUCH;
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

    walk_frame_counter++;
    
    if(walk_frame_counter> 47)
        walk_frame_counter = 0;
    
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
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), walk[walk_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), walk[walk_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
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

    // if(keys[SDL_SCANCODE_LSHIFT] && kicked_mid_air == false)
    // {
    //     current_state = PLAYER_FLYING_KICK;
    //     kicked_mid_air = true;
    //     return;
    // }

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

    jump_frame_counter++;

    if(jump_frame_counter > 15)
        jump_frame_counter = 0;
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
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), jump[jump_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), jump[jump_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
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
        kicked_mid_air = false;
        velocity_y = 0;
        current_state = PLAYER_IDLE;
    }
    else
        data.y = new_y;

    // if(keys[SDL_SCANCODE_LSHIFT] && kicked_mid_air == false)
    // {
    //     current_state = PLAYER_FLYING_KICK;
    //     kicked_mid_air = true;
    //     return;
    // }

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

    fall_frame_counter++;

    if(fall_frame_counter > 15)
        fall_frame_counter = 0;
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
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), fall[fall_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), fall[fall_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::CrouchStateUpdate()
{
    const bool *keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_LALT])
    {
        current_state = PLAYER_CROUCH_KICK;
        return;
    }

    if(!keys[SDL_SCANCODE_LCTRL])
    {
        current_state = PLAYER_IDLE;
        return;
    }

    crouch_frame_counter++;

    if(crouch_frame_counter > 15)
        crouch_frame_counter = 0;
}

void AA_Player::CrouchStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), crouch[crouch_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), crouch[crouch_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void AA_Player::PunchStateUpdate()
{
    if(moving_right)
        punch_hitbox_offset_x = 112. / 192 * 150;
    else
        punch_hitbox_offset_x = 16. / 192 * 150;

    punch_hitbox.x = data.x + punch_hitbox_offset_x;
    punch_hitbox.y = data.y;

    punch_frame_counter++;

    if(punch_frame_counter > 47)
    {
        punch_frame_counter = -1;
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
    SDL_FRect punch_dst = {
        .x = punch_hitbox.x - camera.x,
        .y = punch_hitbox.y - camera.y,
        .w = punch_hitbox.w,
        .h = punch_hitbox.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), punch[punch_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), punch[punch_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &punch_dst);
}

void AA_Player::KickStateUpdate()
{
    if(moving_right)
        kick_hitbox_offset_x = 96. / 192 * 150;
    else
        kick_hitbox_offset_x = 0;

    kick_hitbox.x = data.x - AA_RefLinks::GetCamera()->GetViewPort().x + kick_hitbox_offset_x;
    kick_hitbox.y = data.y - AA_RefLinks::GetCamera()->GetViewPort().y;

    kick_frame_counter++;

    if(kick_frame_counter > 39)
    {
        kick_frame_counter = -1;
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
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), kick[kick_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), kick[kick_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &kick_hitbox);
}

void AA_Player::CrouchKickStateUpdate()
{
    if(moving_right)
        crouch_kick_hitbox_offset_x = 96. / 192 * 150;
    else
        crouch_kick_hitbox_offset_x = 0;

    crouch_kick_hitbox.x = data.x - AA_RefLinks::GetCamera()->GetViewPort().x + crouch_kick_hitbox_offset_x;
    crouch_kick_hitbox.y = data.y - AA_RefLinks::GetCamera()->GetViewPort().y;


    crouch_kick_frame_counter++;

    if(crouch_kick_frame_counter > 39)
    {
        current_state = PLAYER_CROUCH;
        crouch_kick_frame_counter = -1;
    }
}

void AA_Player::CrouchKickStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), crouch_kick[crouch_kick_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), crouch_kick[crouch_kick_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &crouch_kick_hitbox);
}

void AA_Player::FlyingKickStateUpdate()
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

    flying_kick_frame_counter++;
    
    if(flying_kick_frame_counter > 15)
    {
        current_state = PLAYER_FALL;
        flying_kick_frame_counter = -1;
    }
}

void AA_Player::FlyingKickStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    if(moving_right)
        SDL_RenderTexture(AA_RefLinks::GetRenderer(), flying_kick[flying_kick_frame_counter / 8], nullptr, &dst);
    else
        SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), flying_kick[flying_kick_frame_counter / 8], nullptr, &dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

bool AA_Player::IsMovingRight()
{
    return moving_right;
}

int AA_Player::GetCurrentState()
{
    return current_state;
}

SDL_FRect AA_Player::GetPunchHitbox()
{
    return punch_hitbox;
}