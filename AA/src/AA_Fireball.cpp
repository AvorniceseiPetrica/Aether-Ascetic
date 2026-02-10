#include "AA_Fireball.h"
#include "AA_TextureLoader.h"
#include "AA_Config.h"
#include "AA_RefLinks.h"

AA_Fireball::AA_Fireball(float x, float y, float width, float height, bool moving_right) : AA_DrawableEntity(x, y, width, height)
{
    this->moving_right = moving_right;
}

void AA_Fireball::Init()
{
    speed = 10;
    damage = 1;
    texture = AA_TextureLoader::LoadTexture("assets/sprites/red.png");

    animation = new AA_Animation(
        {
            "assets/sprites/fx/fireball/fireball1.png",
            "assets/sprites/fx/fireball/fireball2.png",
            "assets/sprites/fx/fireball/fireball3.png"
        },
        8
    );
}

void AA_Fireball::Update()
{
    float new_x = data.x;
    bool collision_left, collision_right;

    if(moving_right)
        new_x += speed;
    else
        new_x -= speed;

    collision_left = CheckCollision(new_x, data.y + data.w / 2);
    collision_right = CheckCollision(new_x + data.w, data.y + data.w / 2);

    if(!collision_left && !collision_right)
        data.x = new_x;
    else
        collided = true;
    
    animation->Update();
}

void AA_Fireball::Render()
{
    SDL_FRect camera = AA_RefLinks::GetCamera()->GetViewPort();

    SDL_FRect dst = {
        .x = data.x - camera.x,
        .y = data.y - camera.y,
        .w = data.w,
        .h = data.h
    };

    SDL_RenderTexture(AA_RefLinks::GetRenderer(), animation->GetFrame(), nullptr, &dst);
}

bool AA_Fireball::CheckCollision(float x, float y)
{
    int tile_x = (int)(x / TILE_WIDTH);
    int tile_y = (int)(y / TILE_HEIGHT);

    int tile_id = AA_RefLinks::GetMap()->GetTileId(tile_x, tile_y);

    return AA_RefLinks::GetMap()->IsTileSolid(tile_id);
}

bool AA_Fireball::HasCollided()
{
    return collided;
}