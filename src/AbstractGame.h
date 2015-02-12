#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

class RenderingEngine;
class PhysicsEngine;

class AbstractGame{
    public:
        virtual void init() = 0;
        virtual void render(RenderingEngine * re) = 0;
        virtual void update(PhysicsEngine * pe) = 0;
        virtual void clean() = 0;
        virtual ~AbstractGame();
};

#endif /* ABSTRACTGAME_H */
