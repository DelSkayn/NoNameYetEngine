#ifndef TESTGAME_H
#define TESTGAME_H

#include "../AbstractGame.h"
#include "../rendering/Scene.h" 

/*
 * A Very basic example to test the Engine
 */
class TestGame : public AbstractGame{
    public:
        ~TestGame();
        void init() override;
        void render(NNY::Render::RenderEngine * re) override;
        void update(NNY::Physics::PhysicsEngine * pe) override;
        void clean() override;
    private:
        bool forward;
        bool backward;
        bool left;
        bool right;
        bool up;
        bool down;
        NNY::Render::Scene * scene;
};

#endif /* TESTGAME_H */
