#include "TestGame.h" 

#include "../rendering/Mesh.h" 
#include "../rendering/RenderinEngine.h" 
#include "../rendering/Shader.h" 
#include "../rendering/RenderObject.h" 

#include "../core/Event.h"
#include "../core/Input.h"

#include "../core/Kernel.h"

#include "../physics/PhysicsEngine.h" 

#include "../util/Log.h" 

#include <cstdlib>
#include <cmath>

TestGame::~TestGame(){
}

void TestGame::init(){
    MeshManager::loadMesh("teapot.obj","t");
    ShaderManager::LoadShader("pv.glsl","p.glsl","s");
    for(unsigned int i = 0;i < 150;i++){
        this->place[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 10;
    }
}

void TestGame::render(RenderingEngine * re){
    Camera & cam = re->getRenderQueue().getCamera();
    /*
       for(unsigned int i = 0;i < 50;i++){
           RenderObject obj;
           obj.m = MeshManager::getMesh("t");
           obj.ModelMat = Matrix4d().toTranslation(Vector3d(
               place[i*3],
               place[i*3+1],
               place[i*3+2]
           ));
           re->getRenderQueue().addRenderObj(obj);
       }
       */
    RenderObject obj;
    obj.m = MeshManager::getMesh("t");
    re->getRenderQueue().addRenderObj(obj);

    RenderObject obj2;
    obj2.m = MeshManager::getMesh("t");
    re->getRenderQueue().addRenderObj(obj);


    Quaterniond quat1(Vector3d(0,1,0),Mouse::x /100);
    Quaterniond quat2(quat1.right(),Mouse::y /100);
    cam.rotation = quat2 * quat1;


    if(Keyboard::isKeyPressed(GLFW_KEY_W)){
        cam.position += cam.rotation.forward();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_S)){
        cam.position += cam.rotation.back();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_A)){
        cam.position += cam.rotation.left();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_D)){
        cam.position += cam.rotation.right();
    }
    if(Keyboard::isKeyPressed(GLFW_KEY_ESCAPE)){
        Kernel::quit();
    }
    re->getRenderQueue().setShader(ShaderManager::getShader("s"));
}

void TestGame::update(PhysicsEngine * pe){
}

void TestGame::clean(){
}
