#include "AA_Enemy.h"

class AA_Wizard : public AA_Enemy
{
    private:

        int current_state;
        int idle_frame_counter;
        SDL_Texture* idle_frames[5];

    public:

        AA_Wizard(float x, float y, float width, float height);
        ~AA_Wizard() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void IdleStateUpdate();
        void IdleStateRender();
};