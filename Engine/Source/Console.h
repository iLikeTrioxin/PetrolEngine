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
		ConsoleVariable(T& variable, std::string tag);
		
		void set(void* value);
	};

	class Console
	{
	public:
		Console(const Console&) = delete;
		static std::vector<IConsoleVariable*> variables;

		template<typename T>
		static void addVariable( std::string tag,   T&  variable );
		static void setVariable( std::string tag, void* value    );

	private:
		static Console  console;
		
		static Console& Get();

		Console() = default;
	};
}