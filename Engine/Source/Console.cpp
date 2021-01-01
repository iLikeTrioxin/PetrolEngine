#include "PrecompiledHeader.h"
#include "Console.h"

namespace Engine::Console {
	Console Console::console;
	std::vector<IConsoleVariable*> Console::variables;
	

	template<typename T>
	void Console::addVariable<T>(std::string tag,   T&  variable) {
		variables.emplace_back((IConsoleVariable*) new ConsoleVariable<T>(variable, tag));
	}
	void Console::setVariable   (std::string tag, void* value   ) {
		for (unsigned int i = 0; i < variables.size(); i++)
			if (variables[i]->tag == tag)
				variables[i]->set(value);
	}
	
	Console& Console::Get() { return console; }

	template<typename T> void ConsoleVariable<T>::set             (void* value) {*((T*)var) = *((T*)value);}
	template<typename T>      ConsoleVariable<T>::ConsoleVariable (T& variable, std::string tag) {
		this->var = &variable;
		this->tag = tag;
	}
}