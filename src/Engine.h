#ifndef ENGINE_H
#define ENGINE_H 
#include <GL/glew.h>
#include "core/Kernel.h"

#define OGL_VERSION_MAJOR_REQUIRED 3
#define OGL_VERSION_MINOR_REQUIRED 2 

#include "AbstractGame.h" 


namespace NNY{
    //some forward declarations
    namespace Render{
        class RenderEngine;
    }
    namespace Physics{
        class PhysicsEngine;
    }
    namespace Core{
        class Console;
        class Input;
        class Window;
        class Kernel;
    }

    class Engine{
        friend Core::Kernel;
        friend Core::Console;
        friend Core::Input;
        public:
        static void setGame(AbstractGame * game);
        static void start();
        static void clean();
        static void run();

        static Core::Window * getWindow();

        private:
        static Core::Window * current_window;
        static Render::RenderEngine * render_engine;
        static Physics::PhysicsEngine * physics_engine;
        static Core::Console * console;
        static AbstractGame * game;
        //pointers to the different modules of the engine
    };

}
#endif
