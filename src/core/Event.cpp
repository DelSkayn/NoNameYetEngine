#include "Event.h" 

std::map<HName,Event *> Event::event_map;

void Event::subscribe(std::function<void(Event *)> func){
    this->subscribers.push_back(func);
}

void Event::call(){
    for(auto func : subscribers){
        func(this);
    }
}

Event * Event::getEvent(HName name){
    auto it = event_map.find(name);
    if(it == event_map.end()){
        event_map.insert(std::pair<HName,Event *>(name,new Event()));
    }
    return event_map.at(name);
}
