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

    if(new_state == PLAYER_JUMP)
        velocity_y -= jump_strength;

    if(current_animation)
        current_animation->Reset();
    
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

    if(!HandleCollisions(new_x, data.y + data.h + 1) && current_state != PLAYER_JUMP)
        SetState(PLAYER_FALL);
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
        int tile_y = data.y / TILE_HEIGHT;

        this->ChangePosition(data.x, tile_y * TILE_HEIGHT + (TILE_HEIGHT - height - 1));
        SetState(PLAYER_IDLE);   
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

void AA_Player::UpdateBodyHitbox()
{
    switch(current_state)
    {
        case PLAYER_IDLE:
        {
            body_hitbox.x = data.x + 40;
            body_hitbox.y = data.y + 30;
            body_hitbox.w = 70;
            body_hitbox.h = 120;
        }
        break;

        case PLAYER_WALK:
        {
            if(moving_right)
                body_hitbox.x = data.x + 40;
            else
                body_hitbox.x = data.x + 25;

            body_hitbox.y = data.y + 25;
            body_hitbox.w = 80;
            body_hitbox.h = 125;
        }
        break;

        case PLAYER_JUMP:
        {
            if(moving_right)
                body_hitbox.x = data.x + 40;
            else
                body_hitbox.x = data.x + 25;

            body_hitbox.y = data.y + 25;
            body_hitbox.w = 80;
            body_hitbox.h = 100;
        }
        break;

        case PLAYER_FALL:
        {
            if(moving_right)
                body_hitbox.x = data.x + 40;
            else
                body_hitbox.x = data.x + 25;

            body_hitbox.y = data.y + 40;
            body_hitbox.w = 80;
            body_hitbox.h = 100;
        }
        break;

        case PLAYER_PUNCH:
        {
            if(moving_right)
                body_hitbox.x = data.x;
            else
                body_hitbox.x = data.x + 70;

            body_hitbox.y = data.y + 40;
            body_hitbox.w = 80;
            body_hitbox.h = 110;
        };
        break;

        case PLAYER_KICK:
        {
            if(moving_right)
                body_hitbox.x = data.x;
            else
                body_hitbox.x = data.x + 80;

            body_hitbox.y = data.y + 20;
            body_hitbox.w = 70;
            body_hitbox.h = 130;
        }
        break;

        default: body_hitbox = data;
    }
}

void AA_Player::UpdateAttackHitbox()
{
    switch(current_state)
    {
        case PLAYER_PUNCH:
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() > 0)
            {
                if(moving_right)
                    attack_hitbox.x = data.x + 80;
                else
                    attack_hitbox.x = data.x + 10;

                attack_hitbox.y = data.y;
                attack_hitbox.w = 30;
                attack_hitbox.h = 150;
            }
            else
            {
                attack_hitbox.w = 0;
                attack_hitbox.h = 0;
            }
        }
        break;

        case PLAYER_KICK:
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() > 1)
            {
                if(moving_right)
                    attack_hitbox.x = data.x + 70;
                else
                    attack_hitbox.x = data.x + 50;

                attack_hitbox.y = data.y;
                attack_hitbox.w = 30;
                attack_hitbox.h = 150;
            }
            else
            {
                attack_hitbox.w = 0;
                attack_hitbox.h = 0;
            }
        }
        break;

        default: 
        {
            attack_hitbox.w = 0;
            attack_hitbox.h = 0;
        }
    }
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
    animations[PLAYER_JUMP] = new AA_Animation
    (
        {
            "assets/sprites/player/jump/jump1.png",
            "assets/sprites/player/jump/jump2.png"
        },
        8
    );
    animations[PLAYER_PUNCH] = new AA_Animation
    (
        {
            "assets/sprites/player/punch/punch1.png",
            "assets/sprites/player/punch/punch2.png",
            "assets/sprites/player/punch/punch3.png",
            "assets/sprites/player/punch/punch4.png",
            "assets/sprites/player/punch/punch5.png",
            "assets/sprites/player/punch/punch6.png"
        },
        8
    );
    animations[PLAYER_KICK] = new AA_Animation
    (
        {
            "assets/sprites/player/kick/kick1.png",
            "assets/sprites/player/kick/kick2.png",
            "assets/sprites/player/kick/kick3.png",
            "assets/sprites/player/kick/kick4.png",
            "assets/sprites/player/kick/kick5.png",
        },
        8
    );

    UpdateBodyHitbox();
    SetState(PLAYER_FALL);
}

void AA_Player::Update()
{
    UpdateBodyHitbox();
    UpdateAttackHitbox();

    const bool *keys = SDL_GetKeyboardState(nullptr);

    time_since_last_hit++;

    switch(current_state)
    {
        case PLAYER_FALL:
        {
            ApplyGravity();
            HandleHorizontalMovement();
        }
        break;

        case PLAYER_IDLE:
        {
            if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_D])
            {
                SetState(PLAYER_WALK);
                return;
            }

            if(keys[SDL_SCANCODE_SPACE])
            {
                SetState(PLAYER_JUMP);
                return;
            }

            if(keys[SDL_SCANCODE_E])
            {
                SetState(PLAYER_PUNCH);
                return;
            }

            if(keys[SDL_SCANCODE_F])
            {
                SetState(PLAYER_KICK);
                return;
            }

            HandleHorizontalMovement();
        }
        break;

        case PLAYER_WALK:
        {
            if(!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_SPACE])
            {
                SetState(PLAYER_IDLE);
                return;
            }

            if(keys[SDL_SCANCODE_SPACE])
            {
                SetState(PLAYER_JUMP);
                return;
            }

            HandleHorizontalMovement();
        }
        break;

        case PLAYER_JUMP:
        {
            velocity_y += gravity;
            
            if(velocity_y > 0)
            {
                SetState(PLAYER_FALL);
                velocity_y = 0;
                return;
            }

            data.y += velocity_y;
            HandleHorizontalMovement();
        }
        break;

        case PLAYER_PUNCH:
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() == 5)
            {
                SetState(PLAYER_IDLE);
                return;
            }
        }
        break;

        case PLAYER_KICK:
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() == 4)
            {
                SetState(PLAYER_IDLE);
                return;
            }
        }
        break;
    }

    current_animation->Update();
}

void AA_Player::Render()
{
    SDL_FRect dst = {
        .x = data.x - AA_RefLinks::GetCamera()->GetViewPort().x,
        .y = data.y - AA_RefLinks::GetCamera()->GetViewPort().y,
        .w = (float)width,
        .h = (float)height
    };

    SDL_FRect body_hitbox = *GetBodyHitbox();
    SDL_FRect attack_hitbox = GetAttackHitbox();

    body_hitbox.x -= AA_RefLinks::GetCamera()->GetViewPort().x;
    body_hitbox.y -= AA_RefLinks::GetCamera()->GetViewPort().y;

    attack_hitbox.x -= AA_RefLinks::GetCamera()->GetViewPort().x;
    attack_hitbox.y -= AA_RefLinks::GetCamera()->GetViewPort().y;

    SDL_FlipMode flip_mode = moving_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), current_animation->GetFrame(), nullptr, &dst, 0, nullptr, flip_mode);
    
    SDL_SetRenderDrawColor(AA_RefLinks::GetRenderer(), 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderRect(AA_RefLinks::GetRenderer(), &body_hitbox);

    SDL_SetRenderDrawColor(AA_RefLinks::GetRenderer(), 0x55, 0xFF, 0x55, 0x00);
    SDL_RenderRect(AA_RefLinks::GetRenderer(), &attack_hitbox);
}

SDL_FRect* AA_Player::GetData()
{
    return &data;
}

SDL_FRect* AA_Player::GetBodyHitbox()
{
    return &body_hitbox;
}

SDL_FRect AA_Player::GetAttackHitbox()
{
    return attack_hitbox;
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