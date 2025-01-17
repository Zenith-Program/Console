#pragma once
#include "ConsoleToken.h"
#include "CommandList.h"
#include "BasicBuffer.h"
#include <cstdio>

namespace ZenithOS{
	namespace Interpreter {
#define TokenBufferSize 8
		class ConsoleInterpreter {
			BasicBuffer* workingBuffer;
			const CommandList* workingList;
			Token tokenBuffer[TokenBufferSize];
		public:
			void handleLine();
			void setWorkingBuffer(BasicBuffer*);
			void setWorkingCommandList(const CommandList&);
			//singleton implementation-------------------------
		public:
			static ConsoleInterpreter& get();
			ConsoleInterpreter(const ConsoleInterpreter&) = delete;
			void operator=(const ConsoleInterpreter&) = delete;
		private:
			ConsoleInterpreter();
			ConsoleInterpreter(const ConsoleInterpreter&);
			void operator=(const ConsoleInterpreter&);
		private:
			//helper functions---------------------------------
			bool prepLine(const char*, uint32_t, char = '\n');
			void initTokenBuffer();
		};
	}
}
