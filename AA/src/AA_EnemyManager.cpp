#include "AA_EnemyManager.h"

#include <fstream>
#include "AA_Ghoul.h"

AA_EnemyManager::AA_EnemyManager()
{
    
}

AA_EnemyManager::~AA_EnemyManager()
{
    for(auto enemy : enemies)
        if(enemy != nullptr)
            delete enemy;
}

void AA_EnemyManager::LoadEnemies(std::string enemies_config_path)
{
    std::fstream f;

    f.open(enemies_config_path);

    if(!f.is_open())
        SDL_Log("\n\tAA_EnemyManager::LoadEnemies()\t<< Could not open config file %s >>\n\n", enemies_config_path);
    else
    {
        int enemy_type;
        float x, y, width, height;

        while(!f.eof())
        {
            f>>enemy_type>>x>>y>>width>>height;

            switch(enemy_type)
            {
                case ENEMY_GHOUL: enemies.push_back(new AA_Ghoul(x, y, width, height));
                break;

            }
        }
    }

    SDL_Log("Enemies loaded...\n");
}

void AA_EnemyManager::InitEnemies()
{
    for(auto &enemy : enemies)
        enemy->Init();

    SDL_Log("Enemies initialized...\n");
}

void AA_EnemyManager::UpdateEnemies()
{
    for(auto &enemy : enemies)
        enemy->Update();
}

void AA_EnemyManager::RenderEnemies()
{
    for(auto &enemy : enemies)
        enemy->Render();
}