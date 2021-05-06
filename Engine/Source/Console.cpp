#include "PrecompiledHeader.h"
#include "Console.h"

namespace Engine::Console {
	Console Console::console;
	std::vector<IConsoleVariable*> Console::variables;
	
	void Console::setVariable   (std::string tag, void* value   ) {
		for (unsigned int i = 0; i < variables.size(); i++)
			if (variables[i]->tag == tag)
				variables[i]->set(value);
	}
	
	Console& Console::Get() { return console; }
	
}