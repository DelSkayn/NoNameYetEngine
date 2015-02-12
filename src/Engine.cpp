#include "Engine.h"

#include <GLFW/glfw3.h>

#include "util/Log.h"
#include "rendering/RenderinEngine.h"
#include "physics/PhysicsEngine.h"
#include "core/Console.h"
#include "core/Window.h"
#include "core/Input.h"

Window * ImpactEngine::current_window;
RenderingEngine * ImpactEngine::render_engine;
PhysicsEngine * ImpactEngine::physics_engine;
Console * ImpactEngine::console;
AbstractGame * ImpactEngine::game;

void ImpactEngine::start(){
    //Init Sdl and test if init was succesful
    if(!glfwInit()){ 
        LOG("[Error] Could not init glfw");
        //TODO expant sdl error logging
    }

    current_window = new Window();
    current_window->resize();

    Input::init();

    render_engine = new RenderingEngine();

    physics_engine = new PhysicsEngine();

    console = new Console();

}

void ImpactEngine::run(){
    if(render_engine->ready()){
        Kernel::run();
    }else{
        LOG("Engine could not init")
    }
}

void ImpactEngine::clean(){
    delete(console);
    delete(physics_engine);
    delete(render_engine);
    delete(current_window);
    delete(game);
    glfwTerminate();
}

void ImpactEngine::setGame(AbstractGame * game){
    ImpactEngine::game = game;
}

Window * ImpactEngine::getWindow(){
    return current_window;
}
