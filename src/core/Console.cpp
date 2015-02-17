#include "Console.h"
#include <iostream>
#include <vector>

#include "../Engine.h"
#include "../memory/Memory.h"
#include "../util/Log.h"
#include "../util/Misc.h"
#include "../rendering/RenderinEngine.h"
#include "../rendering/RenderQueue.h" 
#include "../rendering/Camera.h" 
#include "../core/Window.h"
#include "../rendering/Mesh.h"
#include "../rendering/Shader.h"
#include "../rendering/Texture.h"
#include "../core/Input.h"
#include "Kernel.h"


Console::Console(){
    console_manager = new ConsoleManager();
    initMap();
}

Console::~Console(){
    delete(console_manager);
}


void Console::execute(){
    //for each input the console_manager has
    while(console_manager->hasInput()){
        //get the input
        std::string command = console_manager->getNextInput();
        //check if the input is the hard coded command "commands
        if(command == "commands"){
            //list commands
            for(auto it = Commands.begin();it != Commands.end();it++){
                std::cout << it->first << std::endl;
            }
        }else if(Commands.find(command) == Commands.end()){
            std::cout << "Command not found"  << std::endl;
        }else{
            CommandStruct commandFunction = Commands.at(command);
            std::vector<std::string> arguments;
            //get arguments required by the command
            for(unsigned int i = 0;i < commandFunction.amount_arguments;i++){
                if(console_manager->hasInput()){
                    arguments.push_back(console_manager->getNextInput());
                }else{
                    break;
                }
            }
            if(arguments.size() == commandFunction.amount_arguments){
                commandFunction.command(arguments);
            }else{
                std::cout << "Missing arguments"  << std::endl;
            }
        }
    }
}

std::string Console::get_input(){
    std::string s;
    std::cin >> s;
    return s;
}

/*
 * This functions sole purpose is the initiliasation of 
 * the command map.
 * Each command is defined inside a std::map<std::string,ConsoleCommand>.
 * MAP_FUNCTION is a macro which makes the defining and reading of the function
 * definitions easier, its use is encuraged but not nessary (TODO Spelling)
 * the first argument is the name of the argument which will need to be typed into 
 * the console in order to excute the command
 * the second arg is the amount of args the command takes which will be provided
 * in a std::vector<std::string> arguments.
 * The function will not execute if not enough args are suplied.
 * the third arg is the definition of the function
 *
 * "," are nessery between to MAP_FUNCTION macros.
 * TODO move function defition to own file ??
 */
void Console::initMap(){
    Commands = {
        MAP_FUNCTION(l,0,
                Log::getInstance().toggleCout();
                ),
        MAP_FUNCTION(echo,1,
                std::cout << arguments[0] << std::endl;
                ),
        MAP_FUNCTION(memory,0,
                std::cout << "Memory used: " << Memory::getAllocatedMemory()
                << " bytes"<< std::endl;
                ),
        MAP_FUNCTION(q,0,
                Kernel::quit();
                ),
        MAP_FUNCTION(windowSize,2,
                ImpactEngine::current_window->setDimensions(Misc::int_value_of(arguments[0]),Misc::int_value_of(arguments[1]));
                ImpactEngine::current_window->resize();
                ),
        MAP_FUNCTION(loadMesh,2,
                MeshManager::loadMesh(arguments[0],arguments[1]);
                ),
        MAP_FUNCTION(loadShader,3,
                ShaderManager::LoadShader(arguments[0],arguments[1],arguments[2]);
                ),
        MAP_FUNCTION(loadTexture,2,
                TextureManager::loadTexture(arguments[0],arguments[1]);
                ),
        MAP_FUNCTION(move,3,
                Camera & camera= ImpactEngine::render_engine->getRenderQueue().getCamera();
                camera.setPosition(Misc::float_value_of(arguments[0]),Misc::float_value_of(arguments[1]),Misc::float_value_of(arguments[2]));
                ),
        MAP_FUNCTION(look,3,
                Camera & camera= ImpactEngine::render_engine->getRenderQueue().getCamera();
                camera.lookAt(Misc::float_value_of(arguments[0]),Misc::float_value_of(arguments[1]),Misc::float_value_of(arguments[2]));
                ),
        MAP_FUNCTION(grab,0,
                Mouse::grabMouse(!Mouse::isGrabed());
                ),
    };
}

ConsoleManager::ConsoleManager(){
    this->console_thread = std::thread(&ConsoleManager::run,this);
    this->input_list.clear();
}

ConsoleManager::~ConsoleManager(){
    //free the thread handle
    console_thread.detach();
}

bool ConsoleManager::hasInput(){
    bool res;
    input_list_mutex.lock();
    res = input_list.size() != 0;
    input_list_mutex.unlock();
    return res;
}

void ConsoleManager::run(){
    for(;;){
        std::string input;
        std::cin >> input;
        if(input[0] == '"'){
            //argument is in the format arg "word"
            std::string append;
            std::cin >> append;
            input.erase(0,1);//remove the "
            while(append[append.size() - 1] != '"'){
                input.append(append);
                std::cin >> append;
            }
            input.append(append.substr(0,append.size()-1));//remove "
        }
        addInput(input);
    }
}

void ConsoleManager::addInput(std::string input){
    input_list_mutex.lock();
    this->input_list.push_back(input);
    input_list_mutex.unlock();
}

std::string ConsoleManager::getNextInput(){
    std::string res;
    input_list_mutex.lock();
    res = this->input_list.front();
    this->input_list.pop_front();
    input_list_mutex.unlock();
    return res;
}
