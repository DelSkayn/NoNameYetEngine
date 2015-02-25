#include "Profile.h" 
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>

std::map<std::string,ProfileTime> Profile::profileList;
unsigned int Profile::currentProfile = 0;

ProfileSample::ProfileSample(std::string name){
    startTime = glfwGetTime();
    if(Profile::profileList.find(name) == Profile::profileList.end()){
        Profile::profileList.insert(std::pair<std::string,ProfileTime>(name,ProfileTime()));
    }
    this->name = name;
}

ProfileSample::~ProfileSample(){
    ProfileTime & p = Profile::profileList[name];
    p.timesProfiled++;
    p.totalTime += glfwGetTime() - startTime;
    p.name = name;
}

void Profile::reset(){
    profileList.clear();
}

std::string Profile::getProfileAsString(){
    std::stringstream ss;
    ss.precision(3);
    ss << std::fixed;
    for(auto & prof : profileList){
        double avgTime = prof.second.totalTime / prof.second.timesProfiled;
        ss << prof.second.name << " : " << prof.second.timesProfiled << " | " << avgTime*1000 << " | "
           << 1.0f/prof.second.timesProfiled << " | " << prof.second.totalTime << std::endl;
    }
    return ss.str();
}
