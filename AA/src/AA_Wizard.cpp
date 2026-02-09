#include "AA_Wizard.h"
#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

AA_Wizard::AA_Wizard(float x, float y, float width, float height, int health) : AA_Enemy(x, y, width, height)
{
    this->health = health;
}

void AA_Wizard::UpdateVision()
{
    vision.x = data.x - vision.w / 2;
    vision.y = data.y - vision.h / 2;   
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
        8
    );

    SetState(WIZARD_IDLE_STATE);
}

void AA_Wizard::Update()
{
    current_animation->Update();
    UpdateVision();

    switch(current_state)
    {
        case WIZARD_IDLE_STATE :
        {
            SDL_FRect *player_rect = AA_RefLinks::GetPlayer()->GetBodyHitbox();

            if(SDL_HasRectIntersectionFloat(player_rect, &vision))
                SetState(WIZARD_ATTACK_STATE);
        }
        break;
        
        case WIZARD_ATTACK_STATE :
        {
            SDL_FRect *player_rect = AA_RefLinks::GetPlayer()->GetBodyHitbox();

            if(!SDL_HasRectIntersectionFloat(player_rect, &vision))
                SetState(WIZARD_IDLE_STATE);
        }
        break;
        
        default: break;
    }
}

void AA_Wizard::Render()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };
    SDL_FRect vis = {
        .x = vision.x - camera.x,
        .y = vision.y - camera.y,
        .w = vision.w,
        .h = vision.h
    };

    SDL_SetRenderDrawColor(AA_RefLinks::GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderRect(AA_RefLinks::GetRenderer(), &vis);
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), current_animation->GetFrame(), nullptr, &dst);
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

}