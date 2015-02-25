#include "Event.h"

namespace NNY{
    namespace Core{

        std::map<HName,Event *> Event::event_map;

        template<typename T>
            ValueEvent<T> * Event::getValueEvent(HName name){
                auto it = Event::event_map.find(name);
                if(it != Event::event_map.end()){
                    return static_cast<ValueEvent<T> *> (&it->second);
                }
                Event * event = new ValueEvent<T>();
                Event::event_map.insert(std::pair<HName,Event *>(name,event));
                return event;
            }

        template<typename T>
            void ValueEvent<T>::setValue(T value){
                this->value = value;
            }
    }
}
