#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "RenderObject.h" 

class Camera;

//NOT USED

/*
 * this should be the container for rendering objects
 * Might not became something else
 */
class Scene{
    public:
        void render();
    private:
        Camera * current_camera;
        std::vector<RenderObject> render_objects;
};

#endif /* SCENE_H */
