#pragma once

#include <vector>
#include <string>

namespace Engine::Console {
	class IConsoleVariable
	{
	public:
		std::string tag;
		   void*    var;

		virtual void set(void* value) = 0;
	};

	template<typename T>
	class ConsoleVariable : public IConsoleVariable
	{
	public:
		ConsoleVariable(std::string tag, T& variable)
			: tag(tag), var(variable) {}
		
		void set(void* value) { *((T*)var) = *((T*)value); }
	};

	class Console
	{
	public:
		Console(const Console&) = delete;
		static std::vector<IConsoleVariable*> variables;

		template<typename T>
		static void addVariable( std::string tag,   T&  variable ) {
			variables.emplace_back((IConsoleVariable*) new ConsoleVariable<T>(tag, variable));
		}
		static void setVariable( std::string tag, void* value    );

	private:
		static Console  console;
		
		static Console& Get();

		Console() = default;
	};
}