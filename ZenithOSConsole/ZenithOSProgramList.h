#pragma once
#include "ZenithOSTypes.h"
#include "ZenithOSCommandList.h"
#include "ZenithOSProgramList.cfg.h"
#include <array>

namespace ZenithOS {
	namespace ProgramList {
		struct ProgramData {
			const char* name;
			int_z (*Startup)();
			void (*Loop)();
			int_z (*Shutdown)();
			const CommandList* commandList;
			uint_z priority;
			uint8_t status;
		};

		template<int_z size> class ProgramList {
			std::array<ProgramData, size> programs;
			int_z currentThread;
		public:
			//initialization
			constexpr ProgramList();

			//program execution
			int_z startProgram(int_z);
			int_z stopProgram(int_z);
			void runActiveLoops();
			bool isRunning(int_z) const;

			//program information
			const CommandList* getProgramCommandList(int_z) const;
			uint_z getProgramPriority(int_z) const;
			const char* getProgramName(int_z) const;
			int_z getProgramIndex(const char*) const;

			//thread information
			int_z getCurrentThread() const;
			int_z setCurrentThread(int_z);
			uint_z getCurrentThreadPriority() const;

		private:
			template<std::size_t... I> static constexpr std::array<ProgramData, size> initProgramData(std::index_sequence<I...>);
		};
		using ProgramLedger = ProgramList<ZenithOS_ProgramListSize>;
		ProgramLedger& getProgramList();
	}
}

#include "ZenithOSProgramList.hpp"

