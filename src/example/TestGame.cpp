#include "TestGame.h" 

#include "../rendering/Mesh.h" 
#include "../rendering/RenderinEngine.h" 
#include "../rendering/Shader.h" 
#include "../rendering/RenderObject.h" 

#include "../physics/PhysicsEngine.h" 

#include "../util/Log.h" 

TestGame::~TestGame(){
}

void TestGame::init(){
    MeshManager::loadMesh("teapot.obj","t");
    ShaderManager::LoadShader("pv.glsl","p.glsl","s");
}

void TestGame::render(RenderingEngine * re){
    RenderObject obj;
    obj.m = MeshManager::getMesh("t");
    obj.ModelMat = Matrix4d().toIdentity();
    re->getRenderQueue().addRenderObj(obj);
    re->getRenderQueue().setShader(ShaderManager::getShader("s"));
}

void TestGame::update(PhysicsEngine * pe){
}

void TestGame::clean(){
}
