#include "AA_Wizard.h"
#include "AA_TextureLoader.h"
#include "AA_RefLinks.h"

AA_Wizard::AA_Wizard(float x, float y, float width, float height, int health) : AA_Enemy(x, y, width, height)
{
    this->health = health;
}

void AA_Wizard::Init()
{
    idle_frames[0] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/wizard/wizard_idle1.png");
    idle_frames[1] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/wizard/wizard_idle2.png");
    idle_frames[2] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/wizard/wizard_idle3.png");
    idle_frames[3] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/wizard/wizard_idle4.png");
    idle_frames[4] = AA_TextureLoader::LoadTexture("assets/sprites/enemies/wizard/wizard_idle5.png");
   
    idle_frame_counter = -1;

    current_state = WIZARD_IDLE_STATE;
}

void AA_Wizard::Update()
{
    switch(current_state)
    {
        case WIZARD_IDLE_STATE : IdleStateUpdate();
        break;
    }
}

void AA_Wizard::Render()
{
    switch(current_state)
    {
        case WIZARD_IDLE_STATE : IdleStateRender();
        break;
    }
}

void AA_Wizard::IdleStateUpdate()
{
    idle_frame_counter++;

    if(idle_frame_counter > 39)
        idle_frame_counter = 0;
}

void AA_Wizard::IdleStateRender()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();
    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderRect(AA_RefLinks::GetRenderer(), &dst);
    SDL_RenderTexture(AA_RefLinks::GetRenderer(), idle_frames[idle_frame_counter / 8], nullptr, &dst);
}

void AA_Wizard::TakeDamage(bool to_right)
{
    
}

void AA_Wizard::SetState(WIZARD_STATES new_state)
{
    if(new_state != current_state)
        current_state = new_state;
}