#pragma once
#include "ConsoleToken.h"
#include "ZenithOSProgramList.cfg.h"
#include <initializer_list>

namespace ZenithOS {
	namespace ProgramList {
		struct Command {
			const char* name;
			const char* args;
			const char* (*function)(ZenithOS::Interpreter::Token*);
		};

		template <int_z size> class StaticCommandList {
			Command commands[size];
			int_z actualSize;
		public:
		
			//template<typename... T, typename = std::enable_if_t<sizeof...(T) == size>> constexpr StaticCommandList(T... values) : commands{ values... } {}
			//template<typename... T, typename = std::enable_if_t<sizeof...(T) == size>> constexpr StaticCommandList(T... values);
			//StaticCommandList() = default;
			constexpr StaticCommandList(std::initializer_list<Command>);
			int_z getCommandIndex(const char*) const;
			const char* getArgumentsList(int_z) const;
			const char* (*getFunction(int_z) const)(ZenithOS::Interpreter::Token*);
		};

		using CommandList = StaticCommandList<ZenithOS_CommandListSize>;
	}
}

#include "ZenithOSCommandList.hpp"
