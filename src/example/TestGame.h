#ifndef TESTGAME_H
#define TESTGAME_H

#include "../AbstractGame.h"

class TestGame : public AbstractGame{
    public:
        ~TestGame();
        void init() override;
        void render(RenderingEngine * re) override;
        void update(PhysicsEngine * pe) override;
        void clean() override;
};

#endif /* TESTGAME_H */
