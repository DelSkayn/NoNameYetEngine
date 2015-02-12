#include "util/Log.h"
#include "core/Console.h"

#include <SDL2/SDL.h>
#include "Engine.h"
#include "example/TestGame.h" 

int main(){
    ImpactEngine::start();
    ImpactEngine::setGame(new TestGame());
    ImpactEngine::run();
    ImpactEngine::clean();
}
