#pragma once

#include "Event.h"

#include <Aliases.h>

#include <list>
#include <typeindex>

namespace PetrolEngine {

    // Event manager
    class EventStack {
    public:
        template<class T>
        static bool checkEvents() {
            return events.find(typeid(T)) != events.end();
        }

        template<class T>
        static Vector<T*>& getEvents() {
            // I believe that typeid is resolved here on compile time, but I'm not sure,
            // TODO: so it is something to check.
            auto eventList = events.find(typeid(T));

            if (eventList == events.end())
                return *reinterpret_cast<Vector<T*>*>(const_cast<Vector<Event*>*>(&emptyEventList));

            return *reinterpret_cast<Vector<T*>*>(&eventList->second);
        }

        template<class T>
        static void popFront() {
            auto eventList = events.find(typeid(T));

            if (eventList == events.end()) return;

            eventList->second.erase(eventList->second.begin());
        }

        static void clear() {
            for (auto& event : events) event.second.clear();
        }

        template<class T>
        static T* addEvent(T* _event) {
            auto eventClassEvents = events.find(typeid(T));

            // If there wasn't Vector of this event class create new
            // Else reinterpret any Event-inherited class into Event and push
            if (eventClassEvents == events.end())
                events.emplace<TypeIndex, Vector<Event*>>(typeid(T), { _event });
            else
                eventClassEvents->second.push_back(reinterpret_cast<Event*>(_event));
            
            return _event;
        }
    private:
        static UnorderedMap<TypeIndex, Vector<Event*>> events;
        static const Vector<Event*> emptyEventList;
    };
}