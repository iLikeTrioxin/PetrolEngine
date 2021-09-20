/*
#include "PCH.h"
#include "Console.h"

namespace PetrolEngine::Console {
	Console Console::console;
	Vector<IConsoleVariable*> Console::variables;
	
	void Console::setVariable   (String tag, void* value   ) {
		for (unsigned int i = 0; i < variables.size(); i++)
			if (variables[i]->tag == tag)
				variables[i]->set(value);
	}
	
	Console& Console::Get() { return console; }
	
}
*/