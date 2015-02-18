#ifndef TESTGAME_H
#define TESTGAME_H

#include "../AbstractGame.h"
#define NUMBER_TEAPOT 200

class TestGame : public AbstractGame{
    public:
        ~TestGame();
        void init() override;
        void render(RenderingEngine * re) override;
        void update(PhysicsEngine * pe) override;
        void clean() override;
    private:
        bool forward;
        bool backward;
        bool left;
        bool right;
        bool up;
        bool down;
        double place[NUMBER_TEAPOT*3];
};

#endif /* TESTGAME_H */
