#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "MacroUtil.h"
#include "Misc.h"

/*
 * Logging utility class
 * This class defines fuctions for Logging
 * Log is a singelton 
 */
class Log{
    public:
    static Log & getInstance(); 
    
    /*
     * Logs message to the log file and to cout if it is not disabbled
     */
    void log(std::string message, char verbosity);
    /*
     * Logs the string with the current time 
     */
    void log_timed(std::string message, char verbosity);
    /*
     * When called toggles whether log
     * uses cout or only file output.`
     * Used for making the commandline easier to read when
     * typing commands.
     */
    void toggleCout();

    void logOglError(std::string line);

    void logOglDebug();

    unsigned int verbosity;

    enum Level{
        NONE = 0,      //No Error Log messages displayed
        MINIMALE = 1,  //Only critical warnings displayed
        RENDERING = 2, //
        CORE = 4,      
        DEBUGGING = 8, //All debug messages displayed
        ALL = (8 << 1) -1, //All messages displayed DO NOT USE IN LOGLVL 
    };

    private:
    std::ofstream out;

    //whether to log to cout
    bool log_cout;

    Log();
    ~Log();

    //deleted copyconstructor and assigment
    Log(const Log &);
    void operator = (const Log &); 
};

#define LOG_FOLDER_DIR "res/"

//log any amount of types type
#define LOG_VALUES( ... ) Log::getInstance().log( Misc::string_of_rec(__VA_ARGS__) , Log::Level::ALL);

#define LOG( string ) Log::getInstance().log( string , Log::Level::ALL );

#define LOGLVL( string, level) Log::getInstance().log( string, level);

#define LOGLVL_VALUES( level ,...) Log::getInstance().log( Misc::string_of_rec(__VA_ARGS__) , level);

#ifdef DEBUG
//Prints appart form the value given also the file and line
//empty defined if DEBUG is not defined
#define LOG_DEBUG( value ) Log::getInstance().log( "[DEBUG] [" STR_MACRO_VALUE(__LINE__)  "] In file" __FILE__ "\n    " + Misc::string_of(value) , Log::Level::DEBUGGING );

#define LOG_DEBUG_VALUES( ... ) Log::getInstance().log( "[DEBUG][ " STR_MACRO_VALUE(__LINE__) "] In file" __FILE__ "\n    " + Misc::string_of_rec(__VA_ARGS__) , Log::Level::DEBUGGING );
#define LOG_OGLERR Log::getInstance().logOglError( "[DEBUG][OGL] " STR_MACRO_VALUE(__LINE__) "] in file " __FILE__ )
#else 
#define LOG_DEBUG(value )
#define LOG_DEBUG_VALUES (...)

#endif /* DEBUG */

#endif /* LOG_H */
