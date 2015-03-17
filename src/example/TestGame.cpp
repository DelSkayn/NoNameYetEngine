#include "TestGame.h" 
#include "../rendering/Mesh.h" 
#include "../rendering/RenderEngine.h" 
#include "../rendering/Shader.h" 
#include "../rendering/RenderObject.h" 

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
    MeshManager::loadMesh("teapot.obj","t");
    ShaderManager::LoadShader("pv.glsl","p.glsl","s");
    for(unsigned int i = 0;i < NUMBER_TEAPOT*3;i++){
        this->place[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 40;
    }
}

void TestGame::render(RenderEngine * re){
    Camera & cam = re->getRenderQueue()->getCamera();
       for(unsigned int i = 0;i < NUMBER_TEAPOT;i++){
           RenderObject obj;
           obj.m = MeshManager::getMesh("t");
           obj.ModelMat = Matrix4d().toTranslation(Vector3d(
               place[i*3],
               place[i*3+1],
               place[i*3+2]
           ));
           re->getRenderQueue()->addRenderObj(obj);
       }
    RenderObject obj;
    obj.m = MeshManager::getMesh("t");
    re->getRenderQueue()->addRenderObj(obj);


    Quaterniond quat1(Vector3d(0,1,0),Mouse::x /300);
    Quaterniond quat2(quat1.right(),Mouse::y /300);
    cam.rotation = quat2 * quat1;
    cam.rotation.conjugate();

    if(Keyboard::isKeyPressed(GLFW_KEY_W)){
        cam.position -= cam.rotation.forward() *0.5;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_S)){
        cam.position -= cam.rotation.back() * 0.5;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_A)){
        cam.position += cam.rotation.left() * 0.5;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_D)){
        cam.position += cam.rotation.right() * 0.5;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_Q)){
        cam.position += cam.rotation.up() * 0.5;
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_E)){
        cam.position += cam.rotation.down() * 0.5;
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
    re->getRenderQueue()->setShader(ShaderManager::getShader("s"));
}

void TestGame::update(NNY::Physics::PhysicsEngine * pe){
}

void TestGame::clean(){
}
