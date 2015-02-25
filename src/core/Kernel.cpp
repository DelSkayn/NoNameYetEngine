#include "Kernel.h"
#include "../Engine.h"
#include "Console.h"
#include "../rendering/RenderEngine.h"
#include "../physics/PhysicsEngine.h"
#include "../AbstractGame.h" 
#include "Window.h"
#include "../util/Profile.h" 

#include "../util/Log.h"

namespace NNY{
    namespace Core{

        bool Kernel::running;

        void Kernel::run(){
            running = true;
            Engine::game->init();
            while(running){
                //TODO temp loop
                {
                    PROFILE(physics)
                        Engine::console->execute();
                    Engine::game->update(Engine::physics_engine);
                    Engine::physics_engine->update();
                }
                {
                    PROFILE(render)
                        Engine::game->render(Engine::render_engine);
                    Engine::render_engine->render();
                }
                Engine::current_window->update();
            }
            Engine::game->clean();
        }

        void Kernel::quit(){
            running = false;
        }
    }
}
