#include "AA_Wizard.h"
#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

AA_Wizard::AA_Wizard(float x, float y, float width, float height, int health) : AA_Enemy(x, y, width, height)
{
    this->health = health;
}

void AA_Wizard::UpdateVision()
{
    if(current_state == WIZARD_IDLE_STATE)
    {
        vision.x = data.x - 4 * TILE_WIDTH;
        vision.y = data.y;
    }

    if(current_state == WIZARD_ATTACK_STATE)
    {
        vision.x = data.x - 5 * TILE_WIDTH;
        vision.y = data.y - 1.5 * TILE_HEIGHT;
    }
}

void AA_Wizard::HandleHurt()
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

void AA_Wizard::UpdateHitbox()
{
    hitbox.x = data.x + 30;
    hitbox.y = data.y;

    if(current_state == WIZARD_HURT_STATE)
    {
        hitbox.x = 0;
        hitbox.y = 0;
    }
}

void AA_Wizard::Init()
{
    animations[WIZARD_IDLE_STATE] = new AA_Animation(
        {
            "assets/sprites/enemies/wizard/wizard_idle1.png",
            "assets/sprites/enemies/wizard/wizard_idle2.png",
            "assets/sprites/enemies/wizard/wizard_idle3.png",
            "assets/sprites/enemies/wizard/wizard_idle4.png",
            "assets/sprites/enemies/wizard/wizard_idle5.png",
        },
        8
    );
    animations[WIZARD_ATTACK_STATE] = new AA_Animation(
        {
            "assets/sprites/enemies/wizard/wizard_attack1.png",
            "assets/sprites/enemies/wizard/wizard_attack2.png",
            "assets/sprites/enemies/wizard/wizard_attack3.png",
            "assets/sprites/enemies/wizard/wizard_attack4.png",
            "assets/sprites/enemies/wizard/wizard_attack5.png",
            "assets/sprites/enemies/wizard/wizard_attack6.png",
            "assets/sprites/enemies/wizard/wizard_attack7.png",
            "assets/sprites/enemies/wizard/wizard_attack8.png",
            "assets/sprites/enemies/wizard/wizard_attack9.png",
            "assets/sprites/enemies/wizard/wizard_attack10.png",
        },
        10
    );
    animations[WIZARD_HURT_STATE] = new AA_Animation(
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

    SetState(WIZARD_IDLE_STATE);
    
    hitbox.w = 120;
    hitbox.h = 192;
}

void AA_Wizard::Update()
{
    UpdateHitbox();

    for(auto fireball : fireballs)
    {
        SDL_FRect fireball_data = fireball->GetData();
        SDL_FRect *player_body_hitbox = AA_RefLinks::GetPlayer()->GetBodyHitbox();
        
        if(SDL_HasRectIntersectionFloat(&fireball_data, player_body_hitbox) && !AA_RefLinks::GetPlayer()->IsInvincible())
            AA_RefLinks::GetPlayer()->TakeDamage();
    }

    if(data.x > MAP_WIDTH || data.y > MAP_HEIGHT)
    {
        is_dead = true;
        return;
    }

    UpdateVision();

    for(auto it = fireballs.begin(); it != fireballs.end(); ) 
    {
        if ((*it)->HasCollided()) 
        {
            delete *it;
            it = fireballs.erase(it);
        }
        else
        {
            ++it;
        }
    }

    SDL_FRect *player_rect = AA_RefLinks::GetPlayer()->GetBodyHitbox();

    switch(current_state)
    {
        case WIZARD_IDLE_STATE :
        {
            if(SDL_HasRectIntersectionFloat(player_rect, &vision))
                SetState(WIZARD_ATTACK_STATE);
        }
        break;
        
        case WIZARD_ATTACK_STATE :
        {
            if(data.x - player_rect->x > 0)
                moving_right = false;
            else
                moving_right = true;

            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() == 9 && ready_to_shoot == true)
            {   
                float fireball_x;

                if(moving_right)
                    fireball_x = data.x + data.w;
                else
                    fireball_x = data.x;

                AA_Fireball *fb = new AA_Fireball(fireball_x, data.y + data.h / 2.7, 70, 70, moving_right);
                fb->Init(); 
                fireballs.push_back(fb);
                ready_to_shoot = false;
            }

            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() < 9)
                ready_to_shoot = true;
                

            SDL_FRect *player_rect = AA_RefLinks::GetPlayer()->GetBodyHitbox();

            if(!SDL_HasRectIntersectionFloat(player_rect, &vision))
                SetState(WIZARD_IDLE_STATE);

            SDL_FRect player_attack_hitbox = AA_RefLinks::GetPlayer()->GetAttackHitbox();

            if(SDL_HasRectIntersectionFloat(&player_attack_hitbox, &data))
                TakeDamage(!moving_right);
        }
        break;

        case WIZARD_HURT_STATE :
        {
            if(current_animation->GetFrameCounterValue() / current_animation->GetFrameSpeed() == 6)
                is_dead = true;
        }
        
        default: break;
    }

    for(auto fireball : fireballs)
        fireball->Update();

    current_animation->Update();
}

void AA_Wizard::Render()
{
    for(auto fireball : fireballs)
        fireball->Render();

    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderTextureRotated(AA_RefLinks::GetRenderer(), current_animation->GetFrame(), nullptr, &dst, 0, nullptr, moving_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void AA_Wizard::SetState(WIZARD_STATES new_state)
{
    if(new_state != current_state)
        current_state = new_state;

    if(current_animation)
        current_animation->Reset();

    current_animation = animations[current_state];

    if(current_state == WIZARD_IDLE_STATE)
    {
        vision.w = 9 * TILE_WIDTH;
        vision.h = TILE_HEIGHT;  
    }

    if(current_state == WIZARD_ATTACK_STATE)
    {
        vision.w = 11 * TILE_WIDTH;
        vision.h = 2.5 * TILE_HEIGHT;
    }
}

void AA_Wizard::TakeDamage(bool to_right)
{
    if(to_right)
        knockback_direction = 1.0;
    else
        knockback_direction = -1.0;

    knockback_velocity = 40;
    knocked_out_timer = 0;
    time_since_last_hit = 0;

    SetState(WIZARD_HURT_STATE);
}

SDL_FRect AA_Wizard::GetBodyHitbox()
{
    return hitbox;
}