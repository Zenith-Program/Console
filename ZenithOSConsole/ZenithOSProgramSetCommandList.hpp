#include "ZenithOSProgramList.cfg.h"

#define ZenithOS_Concat(a,b) a##b
#define ZenithOS_ExpandAndConcat(a,b) ZenithOS_Concat(a,b)

#ifndef ZenithOS_ProgramID
static_assert(false, "ZenithOS_UseProgramSlot must be defined before including this file");
#else 
#if ZenithOS_ProgramID < 0 || ZenithOS_ProgramID >= ZenithOS_ProgramListSize
static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize");
#else
#define ZenithOS_ProgramCommandList template<> constexpr ZenithOS::ProgramList::CommandList ZenithOS::ProgramList::ProgramCommandList<ZenithOS_ProgramID>
#define NextCommand ZenithOS::ProgramList::Command
#endif
#endif




