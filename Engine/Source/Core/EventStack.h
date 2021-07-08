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
        static bool checkEvents() {
            return events.find(typeid(T)) == events.end() ? false : true;
        }

        template<class T>
        static std::list<T*>* getEvents() {
            // I belive that typeid is resolved here on compile time but i'm not sure
            // so it is something to check later.
            auto eventList = events.find(typeid(T));

            if (eventList == events.end())
                return nullptr;

            return reinterpret_cast<std::list<T*>*>(&eventList->second);
        }

        template<class T>
        static T* addEvent(T* _event) {
            auto eventClassEvents = events.find(typeid(T));

            // If there wasn't list of this event class create new
            // Else reinterpret any Event-inherited class into Event and push
            if (eventClassEvents == events.end())
                events.emplace<std::type_index, std::list<Event*>>(typeid(T), { _event });
            else
                eventClassEvents->second.push_back(reinterpret_cast<Event*>(_event));
            
            return _event;
        }
    private:
        static std::unordered_map<std::type_index, std::list<Event*>> events;
    };
}