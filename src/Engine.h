#ifndef ENGINE_H
#define ENGINE_H 
#include <GL/glew.h>
#include <assimp/cimport.h>
#include "core/Kernel.h"

#define OGL_VERSION_MAJOR_REQUIRED 4
#define OGL_VERSION_MINOR_REQUIRED 3

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
        friend class Core::Kernel;
        friend class Core::Console;
        friend class Core::Input;
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
        static aiLogStream * assimp_log;
        static bool initialized;
        //pointers to the different modules of the engine
    };
}
#endif
