#include "ZenithOSProgramList.cfg.h"


#ifndef ZenithOS_UseProgramSlot
static_assert(false, "Define ZenithOS_UseProgramSlot before including this file");
#define Startup static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#define Loop static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#define Shutdown static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#else
#if ZenithOS_UseProgramSlot >= ZenithOS_ProgramListSize || ZenithOS_UseProgramSlot<0
static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize");
#define Startup static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#define Loop static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#define Shutdown static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#else
#define Startup template<> ZenithOS::int_z ZenithOS::ProgramList::ProgramStartup<ZenithOS_UseProgramSlot>
#define Loop template<> void ZenithOS::ProgramList::ProgramLoop<ZenithOS_UseProgramSlot>
#define Shutdown template<> ZenithOS::int_z ZenithOS::ProgramList::ProgramShutdown<ZenithOS_UseProgramSlot>
#endif
#endif


/*ZenithOSProgramListConfig.h------------------
* This file is included at the start of a user defined program to set up the entry point
* 
* ZenithOS_UseProgramSlot needs to be defined as the program slot for the program (program slots are configured in ZenithOSProgramListConfig.h)
* Then this file should be included
* Startup, Loop, and Shutdown are defined here to be the specific ProgramStartup<n>, ... for the program
* 
* Example Usage:
* #define ZenithOS_UseProgramSlot 0
* #include "ZenithOSProgramEntryPoint.hpp"
* 
* Startup(){
*	//your code
*	return 0;
* }
* 
* Loop(){
*	//your code
*	return 0;
* }
* 
* Shutdown(){
*	//your code
*	return 0;
* }
* 
* 
*/