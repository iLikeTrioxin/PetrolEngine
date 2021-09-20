#include "../PCH.h"
#include "EventStack.h"

namespace PetrolEngine {
	std::unordered_map<std::type_index, std::list<Event*>> EventStack::events;
}