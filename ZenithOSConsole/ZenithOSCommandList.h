#pragma once
#include "ConsoleToken.h"
#include <initializer_list>

namespace ZenithOS {
	namespace ProgramList {
		struct Command {
			const char* name;
			const char* args;
			const char* (*function)(ZenithOS::Interpreter::Token*);
		};

		class CommandList {
		public:
			virtual int_z getCommandIndex(const char*) const = 0;
			virtual const char* getArgumentsList(int_z) const = 0;
			virtual const char* (*getFunction(int_z) const)(ZenithOS::Interpreter::Token*) = 0;
		};

		template <int_z size> class StaticCommandList : public CommandList {
			Command commands[size];
		public:
		
			//template<typename... T, typename = std::enable_if_t<sizeof...(T) == size>> constexpr StaticCommandList(T... values) : commands{ values... } {}
			template<typename... T, typename = std::enable_if_t<sizeof...(T) == size>> constexpr StaticCommandList(T... values);
			int_z getCommandIndex(const char*) const override;
			const char* getArgumentsList(int_z) const override;
			const char* (*getFunction(int_z) const)(ZenithOS::Interpreter::Token*) override;
		};
	}
}

#include "ZenithOSCommandList.hpp"
