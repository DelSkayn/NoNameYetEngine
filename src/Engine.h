#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include "core/Kernel.h"

#define OGL_VERSION_MAJOR_REQUIRED 3
#define OGL_VERSION_MINOR_REQUIRED 2 

#include "AbstractGame.h" 

//some forward declarations
class Window;
class RenderingEngine;
class PhysicsEngine;
class Console;
class Input;

class ImpactEngine{
    friend Kernel;
    friend Console;
    friend Input;
public:
    static void setGame(AbstractGame * game);
    static void start();
    static void clean();
    static void run();

    static Window * getWindow();

private:
    static Window * current_window;
    static RenderingEngine * render_engine;
    static PhysicsEngine * physics_engine;
    static Console * console;
    static AbstractGame * game;
    //pointers to the different modules of the engine
};


#endif
