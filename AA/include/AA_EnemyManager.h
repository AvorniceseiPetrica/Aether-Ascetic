#include "AA_Enemy.h"

#include <vector>
#include <string>

class AA_EnemyManager
{
    private:

        std::vector<AA_Enemy*> enemies;

    public:

        AA_EnemyManager();
        ~AA_EnemyManager();
        void LoadEnemies(std::string enmies_config_path);
        void InitEnemies();
        void UpdateEnemies();
        void RenderEnemies();
};