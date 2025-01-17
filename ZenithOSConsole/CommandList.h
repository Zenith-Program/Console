#pragma once
#include "ConsoleToken.h"

namespace ZenithOS {
	namespace Interpreter {
		struct Command {
			const char* identifier;
			const TokenTypes* expectation;
			void (*execution)(const Token*);
		};
		class CommandList {
			uint32_t size;
			const Command* commands;
		public:
			CommandList(const Command* commands, uint32_t size);
			const Command* getCommandWithName(char*) const;
			uint32_t size() const;
		};
	}
}
