#include "Input.h"
#include "../Engine.h"
#include "Window.h"

#include "../util/Log.h"

namespace NNY{
    namespace Core{

        bool Mouse::grabed = false;

        double Mouse::x;
        double Mouse::y;

        std::map<int,bool> Keyboard::key_map;

        void Input::init(){
            Keyboard::init();
            Mouse::init();
        }

        void Keyboard::init(){  
            glfwSetKeyCallback(Engine::getWindow()->getNativeWindow(),Keyboard::keyCallback);
        }

        void Mouse::init(){
            glfwSetCursorPosCallback(Engine::getWindow()->getNativeWindow(),Mouse::posCallback);
        }

        void Mouse::grabMouse(bool grab){
            if(grab){
                glfwSetInputMode(Engine::getWindow()->getNativeWindow(),GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                grabed = true;
            }else{
                glfwSetInputMode(Engine::getWindow()->getNativeWindow(),GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                grabed = false;
            }
        }

        void Mouse::posCallback(GLFWwindow * window, double x, double y){
            Mouse::x = x;
            Mouse::y = y;
        }

        bool Mouse::isGrabed(){
            return grabed;
        }

        void Keyboard::keyCallback(GLFWwindow * window,int key,int scancode,int action,int mods){
            auto it = key_map.find(key);
            if(it == key_map.end()){
                key_map.insert(std::pair<int,bool>(key,false));
                it = key_map.find(key);
            }
            if(action == GLFW_PRESS){
                it->second = true;
            }else if(action == GLFW_RELEASE){
                it->second = false;
            }
        }

        bool Keyboard::isKeyPressed(int key){
            auto it = key_map.find(key);
            if(it == key_map.end()){
                return false;
            }
            return it->second;
        }
    }
}
