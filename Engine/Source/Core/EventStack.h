#pragma once

#include "Event.h"

#include <list>
#include <unordered_map>
#include <typeindex>

namespace Engine {
    // Event manager
    class EventStack {
    public:
        template<class T>
        std::list<T*>* getEvents() {
            auto eventList = events.find(typeid(T));

            if (eventList == events.end())
                return nullptr;

            return reinterpret_cast<std::list<T*>*>(&eventList->second);
        }

        template<class T>
        T* addEvent(T* event) {
            auto eventClassEvents = events.find(typeid(T));

            // If there wasn't list of this event class create new
            // Else reinterpret any Event-inherited class into Event and push
            if (eventClassEvents == events.end())
                events.emplace<std::type_index, std::list<Event*>>(typeid(T), { event });
            else
                eventClassEvents->second.push_back(reinterpret_cast<Event*>(event));
            
            // return event
            return event;
        }
    private:
        std::unordered_map<std::type_index, std::list<Event*>> events;
    };
}