#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <map>
#include <vector>
#include "../util/HName.h"

template<typename T>
class ValueEvent;

class Event{
    public:
        void subscribe(std::function<void(Event *)> func);

        virtual void call();
        /*
         * returns event with name
         * If event does not exist it is created
         */
        static Event * getEvent(HName name);

        template<typename T>
        static ValueEvent<T> * getValueEvent(HName name);
    private:
        std::vector<std::function<void(Event *)>> subscribers;
        static std::map<HName,Event *> event_map;
};

template<typename T>
class ValueEvent :public Event{
    public:
        void setValue(T value);
    private:
        T value;
};

#include "EventDefine.h"

#endif /* EVENT_H */
