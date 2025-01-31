#include "ZenithOSProgramList.cfg.h"


#ifndef ZenithOS_ProgramID
static_assert(false, "Define ZenithOS_UseProgramSlot before including this file");
#define Startup static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#define Loop static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#define Shutdown static_assert(false, "Define ZenithOS_UseProgramSlot before including this file")
#else
#if ZenithOS_ProgramID >= ZenithOS_ProgramListSize || ZenithOS_ProgramID<0
static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize");
#define Startup static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#define Loop static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#define Shutdown static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize")
#else
#define Startup template<> ZenithOS::int_z ZenithOS::ProgramList::ProgramStartup<ZenithOS_ProgramID>
#define Loop template<> void ZenithOS::ProgramList::ProgramLoop<ZenithOS_ProgramID>
#define Shutdown template<> ZenithOS::int_z ZenithOS::ProgramList::ProgramShutdown<ZenithOS_ProgramID>
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