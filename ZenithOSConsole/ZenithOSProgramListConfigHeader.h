#pragma once
#include "ZenithOSTypes.h"
#include "ZenithOSCommandList.h"

namespace ZenithOS {
	namespace ProgramList {
		template<int_z> int_z ProgramStartup();
		template<int_z> void ProgramLoop();
		template<int_z> int_z ProgramShutdown();
		template<int_z> const char* ProgramName;
		template<int_z> uint_z ProgramPriority;
		template<int_z> CommandList* ProgramCommandList;
	}
}

#ifndef ZenithOS_ProgramListSize
static_assert(false, "ZenithOS_ProgramListSize must be defined before including this file");
#else
static_assert(ZenithOS_ProgramListSize > 0, "ZenithOS_ProgramListSize must be greater than 0");
#endif

#ifndef ZenithOS_DefaultProgramPriority
#define ZenithOS_DefaultProgramPriority 1
#else
#if ZenithOS_DefaultProgramPriority <1
static_assert(false, "Program priority 0 is reserved for ZenithOS. ZenithOS_DefualtProgramPriority cannot be <1");
#endif
#endif


#define ZenithOS_DeclareProgramSlot(n, name, listSize) \
static_assert(ZenithOS_ProgramListSize > 0, "ZenithOS_ProgramListSize must be greater than 0");\
static_assert(n<ZenithOS_ProgramListSize, "Cannot declare program for a slot outside the size of the program list. use ZenithOS_PROGRAM_SIZE_LIST to change the size");\
static_assert(ZenithOS_DefaultProgramPriority>0, "Program priority 0 is reserved for ZenithOS. ZenithOS_DefualtProgramPriority cannot be <1");\
static_assert(listSize>0, "Command list size must be positive");\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramStartup<n>();\
extern template void ZenithOS::ProgramList::ProgramLoop<n>();\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramShutdown<n>();\
template<> const char* ZenithOS::ProgramList::ProgramName<n> = name;\
template<> const ZenithOS::uint_z ZenithOS::ProgramList::ProgramPriority<n> = ZenithOS_DefaultProgramPriority;\
extern ZenithOS::ProgramList::StaticCommandList<listSize> ProgramCommandList##n;\
template<> ZenithOS::ProgramList::CommandList* ZenithOS::ProgramList::ProgramCommandList<n> = &ProgramCommandList##n;

#define ZenithOS_DeclareProgramSlotWithPriority(n, name, listSize, priority)\
static_assert(ZenithOS_ProgramListSize > 0, "ZenithOS_ProgramListSize must be greater than 0");\
static_assert(n<ZenithOS_ProgramListSize, "Cannot declare program for a slot outside the size of the program list. use ZenithOS_PROGRAM_SIZE_LIST to change the size");\
static_assert(priority>0, "Program priority 0 is reserved for ZenithOS");\
static_assert(listSize>0, "Command list size must be positive");\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramStartup<n>();\
extern template void ZenithOS::ProgramList::ProgramLoop<n>();\
extern template ZenithOS::int_z ZenithOS::ProgramList::ProgramShutdown<n>();\
template<> const char* ZenithOS::ProgramList::ProgramName<n> = name;\
template<> ZenithOS::uint_z ZenithOS::ProgramList::ProgramPriority<n> = priority;\
extern ZenithOS::ProgramList::StaticCommandList<listSize> ProgramCommandList##n;\
template<> ZenithOS::ProgramList::CommandList* ZenithOS::ProgramList::ProgramCommandList<n> = &ProgramCommandList##n;

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
