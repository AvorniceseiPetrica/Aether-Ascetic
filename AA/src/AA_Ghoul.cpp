#include "AA_Ghoul.h"

#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"
#include <vector>

AA_Ghoul::AA_Ghoul(float x, float y, float width, float height, int health) : AA_Enemy(x, y, width, height)
{
    this->health = health;
}

void AA_Ghoul::SetState(GHOUL_STATES new_state)
{
    if(new_state != current_state)
        current_state = new_state;

    if(current_animation)
        current_animation->Reset();

    current_animation = animations[current_state];
}

void AA_Ghoul::UpdateHitbox()
{
    if(moving_right)
        hitbox_offset_x = 48;
    else
        hitbox_offset_x = 15;

    hitbox.x = data.x + hitbox_offset_x;
    hitbox.y = data.y + hitbot_offset_y;

    if(current_state == GHOUL_HURT)
    {
        hitbox.w = 0;
        hitbox.h = 0;
        hitbox.x = 0;
        hitbox.y = 0;
    }
}

void AA_Ghoul::ApplyGravity()
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
        SetState(GHOUL_RUN);
    }
    else
        data.y = new_y;
}

void AA_Ghoul::HandleRunning()
{
    float new_x = data.x;
    bool collision_bottom_left;
    bool collision_bottom_right;
    bool collision_middle_left;
    bool collision_middle_right;
    SDL_FRect player_attack_hitbox = AA_RefLinks::GetPlayer()->GetAttackHitbox();

    if(SDL_HasRectIntersectionFloat(&player_attack_hitbox, &data))
        TakeDamage(true);   

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
}

void AA_Ghoul::HandleHurt()
{
    float new_x = data.x;
    bool collision_middle_left,
        collision_middle_right;
    
    new_x += knockback_direction * knockback_velocity;

    collision_middle_left = CheckCollision(new_x, data.y + data.h / 2);
    collision_middle_right = CheckCollision(new_x + data.w, data.y + data.h / 2);

    if(collision_middle_left || collision_middle_right)
    {
        knockback_velocity = 0;
        return;
    }
    else
        data.x = new_x;
    
    knockback_velocity *= 0.9;
}

void AA_Ghoul::Init()
{
    std::vector<std::string> running_frames_paths = {
            "assets/sprites/enemies/ghoul/ghoul1.png",
            "assets/sprites/enemies/ghoul/ghoul2.png",
            "assets/sprites/enemies/ghoul/ghoul3.png",
            "assets/sprites/enemies/ghoul/ghoul4.png",
            "assets/sprites/enemies/ghoul/ghoul5.png",
            "assets/sprites/enemies/ghoul/ghoul6.png",
            "assets/sprites/enemies/ghoul/ghoul7.png",
            "assets/sprites/enemies/ghoul/ghoul8.png"
    };

    animations[GHOUL_FALL] = new AA_Animation(
        running_frames_paths,
        8
    );
    animations[GHOUL_RUN] = new AA_Animation(
        running_frames_paths,
        8
    );
    animations[GHOUL_ATTACK] = new AA_Animation(
        running_frames_paths,
        8
    );
    animations[GHOUL_HURT] = new AA_Animation(
        {
            "assets/sprites/enemies/enemy_death/enemy_death1.png",
            "assets/sprites/enemies/enemy_death/enemy_death2.png",
            "assets/sprites/enemies/enemy_death/enemy_death3.png",
            "assets/sprites/enemies/enemy_death/enemy_death4.png",
            "assets/sprites/enemies/enemy_death/enemy_death5.png",
            "assets/sprites/enemies/enemy_death/enemy_death6.png",
            "assets/sprites/enemies/enemy_death/enemy_death7.png",
        },
        8
    );

    moving_right = true;

    current_state = GHOUL_FALL;
    velocity_y = 0;

    hitbox.w = 128;
    hitbox.h = 128;
    hitbot_offset_y = 64;
    
    time_since_last_hit = 0;
    knockback_velocity = 0;

    SetState(GHOUL_FALL);

}

void AA_Ghoul::Update()
{
    if(health <= 0)
        is_dead = true;

    UpdateHitbox();

    time_since_last_hit++;

    current_animation->Update();

    switch(current_state)
    {
        case GHOUL_FALL: 
        {
            ApplyGravity();
        }
        break;

        case GHOUL_RUN: 
        {
            HandleRunning();
        }
        break;

        case GHOUL_HURT:
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() == 6)
                is_dead = true;
        }

        default: break;
    }
}

void AA_Ghoul::Render()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), current_animation->GetFrame(), nullptr, &dst, 0, nullptr, moving_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void AA_Ghoul::TakeDamage(bool to_right)
{
    if(to_right)
        knockback_direction = 1.0;
    else
        knockback_direction = -1.0;

    knockback_velocity = 40;
    knocked_out_timer = 0;
    time_since_last_hit = 0;

    SetState(GHOUL_HURT);
}

SDL_FRect AA_Ghoul::GetBodyHitbox()
{
    return hitbox;
}