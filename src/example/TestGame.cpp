#include "TestGame.h" 
#include "../rendering/Mesh.h" 
#include "../rendering/RenderEngine.h" 
#include "../rendering/Shader.h" 
#include "../rendering/RenderObject.h" 
#include "../rendering/Scene.h" 

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
}

void TestGame::render(RenderEngine * re){
    Camera & cam = re->camera;

    Quaterniond quat1(Vector3d(0,1,0),Mouse::x /300);
    Quaterniond quat2(quat1.right(),Mouse::y /300);
    cam.rotation = quat2 * quat1;
    cam.rotation.conjugate();

    if(Keyboard::isKeyPressed(GLFW_KEY_W)){
        cam.position -= cam.rotation.forward();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_S)){
        cam.position -= cam.rotation.back();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_A)){
        cam.position += cam.rotation.left();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_D)){
        cam.position += cam.rotation.right();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_Q)){
        cam.position += cam.rotation.up();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_E)){
        cam.position += cam.rotation.down();
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
    re->render(this->scene);
}

void TestGame::update(NNY::Physics::PhysicsEngine * pe){
}

void TestGame::clean(){
    delete this->scene;
}
