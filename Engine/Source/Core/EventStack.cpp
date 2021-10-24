#include "../PCH.h"
#include "EventStack.h"

namespace PetrolEngine {
    const Vector<Event*> EventStack::emptyEventList = {};

    std::unordered_map<std::type_index, Vector<Event*>> EventStack::events;
}