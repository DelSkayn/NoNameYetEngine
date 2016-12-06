#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
//glew needs to be included before gl.h
//glfw includes gl.h so in we include glew.h
//to stop it from wining about gl.h
#include <GLFW/glfw3.h>

#include <map>
#include <list>


namespace NNY{
    namespace Core{

        class Input{
            public:
                static void init();

                enum Motion{
                    Press = GLFW_PRESS,
                    Release = GLFW_RELEASE,
                    Pressed,
                    Released,
                    Click,
                    DClick
                };

                static void update();
                static void posCallback(GLFWwindow * window,double xpos, double ypos);

                static void grabMouse(bool grab);

            private:

        };

        class Mouse{
            friend class Input;
            public:
                static double x;
                static double y;
                static void grabMouse(bool grab);
                static bool isGrabed();//TODO spell?
            private:
                static bool grabed;
                static void init();


                static void posCallback(GLFWwindow * window,double x,double y);
                static void ButtonCallback(GLFWwindow * window, int key, int action,int mod);
        };
        /*
         * Very temporary input selution
         */
        class Keyboard{
            friend class Input;
            public:
                static bool isKeyPressed(int key);
            private:
                static void init();
                static void keyCallback(GLFWwindow * window,int key,int scancode,int action,int mods);

                static std::map<int,bool> key_map;
        };
    }
}

#endif /* INPUT_H */
