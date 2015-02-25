#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

namespace NNY{
    namespace Physics{
        class PhysicsEngine{
            public:
                PhysicsEngine();
                ~PhysicsEngine();

                void update() const;
            private:
                bool initalized;

        };
    }
}
#endif /* PHYSICSENGINE_H */
