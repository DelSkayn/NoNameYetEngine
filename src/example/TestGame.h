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
        void init();
        void render(NNY::Render::RenderEngine * re);
        void update(NNY::Physics::PhysicsEngine * pe);
        void clean();
    private:
        bool was_added;
        bool forward;
        bool backward;
        bool left;
        bool right;
        bool up;
        bool down;
        NNY::Render::Scene * scene;
};

#endif /* TESTGAME_H */
