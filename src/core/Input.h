#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
//glew needs to be included before gl.h
//glfw includes gl.h so in we include glew.h
//to stop it from wining about gl.h
#include <GLFW/glfw3.h>

#include <map>
#include <list>

#include "Event.h"

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
    private:

};

class Mouse{
    friend Input;
    public:
    private:
        static void init();

        static void CallPosCallback(GLFWwindow * window,double x,double y);
        static void ButtonCallback(GLFWwindow * window, int key, int action,int mod);
};

class Keyboard{
    friend Input;
    public:
        static Event * registerKeyEvent(int key,Motion motion,HName eventname);
    private:
        struct KeyState{
            Motion motion;
            Event * event;
        };
        static void init();

        static void update();

        static void keyCallback(GLFWwindow * window,int key,int scancode,int action,int mods);
    
        static std::map<int,KeyState> key_map;
        static std::map<int,Event *> keys_in_proper_state;
};

#endif /* INPUT_H */
