#include "AA_Enemy.h"

enum WIZARD_STATES {
    WIZARD_IDLE_STATE
};

class AA_Wizard : public AA_Enemy
{
    private:

        int current_state;
        int idle_frame_counter;
        SDL_Texture* idle_frames[5];

        void SetState(WIZARD_STATES new_state);

    public:

        AA_Wizard(float x, float y, float width, float height, int health);
        ~AA_Wizard() = default;
        void Init() override;
        void Update() override;
        void Render() override;
        void IdleStateUpdate();
        void IdleStateRender();
        void TakeDamage(bool to_right) override;
};