#include "ZenithOSProgramList.cfg.h"


#ifndef ZenithOS_UseProgramSlot
static_assert(false, "ZenithOS_UseProgramSlot must be defined before including this file");
#else 
#if ZenithOS_UseProgramSlot < 0 || ZenithOS_UseProgramSlot >= ZenithOS_ProgramListSize
static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize");
#else
#define ProgramCommandList ZenithOS::ProgramList::StaticCommandList<1> ProgramCommandList##ZenithOS_UseProgramSlot
#endif
#endif



