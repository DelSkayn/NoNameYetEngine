#ifndef CONSOLE_H
#define CONSOLE_H

#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <list>
#include <functional>

#include "../util/MacroUtil.h"

struct CommandStruct{
    unsigned int amount_arguments;
    std::function<void(std::vector<std::string> & arguments)> command;
};

class ConsoleManager;


class Console{
    public:
        Console();
        ~Console();

        /*
         * Execute all pending commandline arguments
         */
        void execute(); 
    private:
        /*
         * Loads commands defined in the cpp file
         * Called inside teh constructor
         */
        void initMap();
        std::string get_input();
        typedef std::map<std::string,CommandStruct> CommandMap;
        typedef std::pair<std::string,CommandStruct> CommandPair;
        CommandMap Commands;
        ConsoleManager * console_manager;
};

//ConsoleManager manages a different thread on which will read input
class ConsoleManager{
public:
    ConsoleManager();
    ~ConsoleManager();
    bool hasInput();
    std::string getNextInput();
private: 
    void run();
    void addInput(std::string input);
    
    std::mutex input_list_mutex;
    std::thread console_thread;
    std::list<std::string> input_list;
};

#define MAP_FUNCTION(name,amount_arguments,definition) { STR(name),CommandStruct{amount_arguments,[](std::vector<std::string> & arguments) { definition} } }

#endif /* CONSOLE_H */
