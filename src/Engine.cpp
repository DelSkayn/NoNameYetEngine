#include "Engine.h"

#include <GLFW/glfw3.h>

#include "util/Log.h"
#include "rendering/RenderEngine.h"
#include "physics/PhysicsEngine.h"
#include "core/Console.h"
#include "core/Window.h"
#include "core/Input.h"

namespace NNY{

    Core::Window * Engine::current_window;
    Render::RenderEngine * Engine::render_engine;
    Physics::PhysicsEngine * Engine::physics_engine;
    Core::Console * Engine::console;
    AbstractGame * Engine::game;

    void Engine::start(){
        //Init Sdl and test if init was succesful
        if(!glfwInit()){ 
            LOG("[Error] Could not init glfw");
            //TODO expant sdl error logging
        }

        current_window = new Core::Window();
        current_window->resize();

        Core::Input::init();

        render_engine = new Render::RenderEngine();

        physics_engine = new Physics::PhysicsEngine();

        console = new Core::Console();

    }

    void Engine::run(){
        if(render_engine->ready()){
            Core::Kernel::run();
        }else{
            LOG("Engine could not init")
        }
    }

    void Engine::clean(){
        delete(console);
        delete(physics_engine);
        delete(render_engine);
        delete(current_window);
        delete(game);
        glfwTerminate();
    }

    void Engine::setGame(AbstractGame * game){
        Engine::game = game;
    }

    Core::Window * Engine::getWindow(){
        return current_window;
    }

}
