#include "Engine.h"

#include <GLFW/glfw3.h>
#include <assimp/cimport.h>

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
    aiLogStream * Engine::assimp_log;
    bool Engine::initialized = false;

    void Engine::start(){
        //Init Sdl and test if init was succesful
        if(!glfwInit()){ 
            M_LOG("[Error] Could not init glfw")
                //TODO expant sdl error logging
        }


        current_window = new Core::Window(WINDOW_SIZE);
        current_window->resize();

        Core::Input::init();

        render_engine = new Render::RenderEngine(WINDOW_SIZE);
        physics_engine = new Physics::PhysicsEngine();
        console = new Core::Console();

        assimp_log = new aiLogStream();
        *assimp_log = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);

        aiAttachLogStream(assimp_log);

        initialized = true;
    }

    /*
     * Start Egine loop 
     */
    void Engine::run(){
        if(initialized){
            if(render_engine->ready()){
                Core::Kernel::run();
            }else{
                M_LOG("Engine could not init")
            }
        }else{
            M_LOGLVL("[Error] Please call Engine::init before start",Log::Level::ALL)
        }
    }

    void Engine::clean(){
        if(initialized){
            delete(console);
            delete(physics_engine);
            delete(render_engine);
            delete(current_window);
            delete(game);
            glfwTerminate();
            initialized = false;
        }
    }

    void Engine::setGame(AbstractGame * game){
        Engine::game = game;
    }

    Core::Window * Engine::getWindow(){
        return current_window;
    }

}
