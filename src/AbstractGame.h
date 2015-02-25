#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

namespace NNY{
    namespace Render{
        class RenderEngine;
    }
    namespace Physics{
        class PhysicsEngine;
    }
}

class AbstractGame{
    public:
        virtual void init() = 0;
        virtual void render(NNY::Render::RenderEngine * re) = 0;
        virtual void update(NNY::Physics::PhysicsEngine * pe) = 0;
        virtual void clean() = 0;
        virtual ~AbstractGame();
};

#endif /* ABSTRACTGAME_H */
