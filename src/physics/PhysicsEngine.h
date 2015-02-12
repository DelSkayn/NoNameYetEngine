#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

class PhysicsEngine{
    public:
    PhysicsEngine();
    ~PhysicsEngine();

    void update() const;
    private:
    bool initalized;
    
};

#endif /* PHYSICSENGINE_H */
