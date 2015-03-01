#include "util/Log.h"
#include "core/Console.h"

#include <SDL2/SDL.h>
#include "Engine.h"
#include "example/TestGame.h" 

int main(){
    NNY::Engine::setGame(new TestGame());
    NNY::Engine::start();
    NNY::Engine::run();
    NNY::Engine::clean();
}
