#include "Input.h"
#include "../Engine.h"
#include "Window.h"

#include "../util/Log.h"

std::map<int,Keyboard::KeyState> Keyboard::key_map;
std::list<Event *> Keyboard::keys_in_proper_state;

void Input::init(){
    Keyboard::init();
    Mouse::init();
}

void Keyboard::init(){  
    glfwSetKeyCallback(ImpactEngine::getWindow()->getNativeWindow(),Keyboard::keyCallback);

}

void Mouse::init(){

}

void Keyboard::keyCallback(GLFWwindow * window,int key,int scancode,int action,int mods){
    auto it = key_map.find(key);
    if(it != key_map.end()){
        KeyState & ks = &it->second;
        if(ks.motion == action){
            ks.event->call();
        }else if(ks.motion == Input::Motion::Pressed){
            if(action = GLFW_PRESS){

            }
        }
    }
}

