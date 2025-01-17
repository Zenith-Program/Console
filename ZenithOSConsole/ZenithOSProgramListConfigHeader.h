#pragma once
#include "Types.h"

namespace ZenithOS {
	namespace ProgramList {
		template<int> int_z ProgramStartup();
		template<int> int_z ProgramLoop();
		template<int> int_z ProgramShutdown();
		template<int> const char* ProgramName;
	}
}

#ifndef ZenithOS_ProgramListSize
static_assert(false, "ZenithOS_ProgramListSize must be defined before including this file");
#endif


#define ZenithOS_DeclareProgramSlot(n, name) \
static_assert(n<ZenithOS_ProgramListSize, "Cannot declare program for a slot outside the size of the program list. use ZenithOS_PROGRAM_SIZE_LIST to change the size");\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramStartup<n>();\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramLoop<n>();\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramShutdown<n>();\
template<> const char* ZenithOS::ProgramList::ProgramName<n> = name;

/*ZenithOS_ProgramListConfigHeader.h-----------
* This file defines the macro that the user uses in the ZenithOSProgramConfig.h configuration file to define each program's data
* Programs using the ZenithOS framework must implement 3 functions: Startup, Loop, and Shutdown
* Each program has it's own copies of these functions, meaning that 3*ProgramListSize of them need to be declared at compile time
* Template functions are used for this with an int template argument that represents which program the function assosiates with
* 
* The ZenithOS_DeclareProgramSlot macro instantiates the template functions for the given slot
* A program which includes the configuration file can then define ProgramStartup<n>, ProgramLoop<n>, ... without forward declaration
* ZenithOS has acess to the configuration file and therefore has acess to these fuctions' declarations without having to include any program files
* 
* 
* 
*/
