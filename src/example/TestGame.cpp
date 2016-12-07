#include "TestGame.h" 
#include "../rendering/Mesh.h" 
#include "../rendering/RenderEngine.h" 
#include "../rendering/Shader.h" 
#include "../rendering/RenderObject.h" 
#include "../rendering/Scene.h" 
#include "../rendering/Light.h" 

#include "../core/Input.h"

#include "../core/Kernel.h"

#include "../physics/PhysicsEngine.h" 

#include "../util/Log.h" 

#include <cstdlib>
#include <cmath>


using namespace NNY::Render;
using namespace NNY::Core;

TestGame::~TestGame(){
}

void TestGame::init(){
    this->scene = new NNY::Render::Scene();
    this->scene->load_from_file("res/mesh/sponza.obj");
    this->scene->load();
    this->scene->p_lights.push_back(NNY::Render::PointLight{ 1000, Vector3f(1.0,1.0,1.0), Vector3f(0.0,10.0,0.0)});
    this->was_added = false;
}

void TestGame::render(RenderEngine * re){
    Camera & cam = re->camera;

    Quaterniond quat1(Vector3d(0,1,0),Mouse::x /300);
    Quaterniond quat2(quat1.right(),Mouse::y /300);
    cam.rotation = quat2 * quat1;
    cam.rotation.conjugate();

    if(Keyboard::isKeyPressed(GLFW_KEY_W)){
        cam.position -= cam.rotation.forward() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_S)){
        cam.position -= cam.rotation.back() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_A)){
        cam.position += cam.rotation.left() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_D)){
        cam.position += cam.rotation.right() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_Q)){
        cam.position += cam.rotation.up() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_E)){
        cam.position += cam.rotation.down() * 2;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_ESCAPE)){
        Kernel::quit();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_G)){
        Mouse::grabMouse(true);
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_T)){
        Mouse::grabMouse(false);
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_O)){
        re->exposure += 0.01;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_P)){
        re->exposure -= 0.01;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_M)){
        re->which = RenderEngine::RenderOut::ALBEDO;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_N)){
        re->which = RenderEngine::RenderOut::POSITIONS;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_B)){
        re->which = RenderEngine::RenderOut::NORMALS;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_V)){
        re->which = RenderEngine::RenderOut::FULL;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_C)){
        this->scene->d_light.direction 
            = Quaternionf(Vector3f(1.0,0.0,0.0),0.01).rotateVec(
                    this->scene->d_light.direction
                    );
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_Z) && !this->was_added){
        this->was_added = true;
        this->scene->p_lights.push_back(
                NNY::Render::PointLight
                    { 5000
                    , Vector3f::random()
                    , Vector3f(cam.position) });
    }else if(!Keyboard::isKeyPressed(GLFW_KEY_Z)){
        this->was_added = false;
    }
    re->render(this->scene);
}

void TestGame::update(NNY::Physics::PhysicsEngine * pe){
}

void TestGame::clean(){
    delete this->scene;
}
