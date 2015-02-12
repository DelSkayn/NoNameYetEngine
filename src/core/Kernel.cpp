#include "Kernel.h"
#include "../Engine.h"
#include "Console.h"
#include "../rendering/RenderinEngine.h"
#include "../physics/PhysicsEngine.h"
#include "../AbstractGame.h" 
#include "Window.h"

#include "../util/Log.h"

bool Kernel::running;

void Kernel::run(){
    running = true;
    ImpactEngine::game->init();
    while(running){
        //TODO temp loop
        ImpactEngine::console->execute();
        ImpactEngine::game->update(ImpactEngine::physics_engine);
        ImpactEngine::physics_engine->update();
        ImpactEngine::game->render(ImpactEngine::render_engine);
        ImpactEngine::render_engine->render();
        ImpactEngine::current_window->update();
    }
    ImpactEngine::game->clean();
}

void Kernel::quit(){
    running = false;
}

