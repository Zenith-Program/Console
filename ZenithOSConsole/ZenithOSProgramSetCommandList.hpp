#include "ZenithOSProgramList.cfg.h"

#define ZenithOS_Concat(a,b) a##b
#define ZenithOS_ExpandAndConcat(a,b) ZenithOS_Concat(a,b)

#ifndef ZenithOS_UseProgramSlot
static_assert(false, "ZenithOS_UseProgramSlot must be defined before including this file");
#else 
#if ZenithOS_UseProgramSlot < 0 || ZenithOS_UseProgramSlot >= ZenithOS_ProgramListSize
static_assert(false, "ZenithOS_UseProgramSlot must be defined as a program slot less than ZenithOS_ProgramListSize");
#else

#ifndef ZenithOS_CommandListSize
static_assert(false, "Command list size must be defined with ZenithOS_CommandListSize before including this file");
#else
static_assert(ZenithOS_CommandListSize > 0, "Command list size must be positive");
namespace ZenithOS {
	namespace ProgramList {
		extern ZenithOS::ProgramList::StaticCommandList<ZenithOS_CommandListSize> ZenithOS_ExpandAndConcat(ProgramCommandList_, ZenithOS_UseProgramSlot);
	}
}
#define ZenithOS_RegisterProgramCommandList template<> ZenithOS::ProgramList::CommandList* ZenithOS::ProgramList::ProgramCommandList<ZenithOS_UseProgramSlot> = (ZenithOS::ProgramList::CommandList*)&ZenithOS::ProgramList::ZenithOS_ExpandAndConcat(ProgramCommandList_, ZenithOS_UseProgramSlot);
#define ZenithOS_ProgramCommandList ZenithOS::ProgramList::StaticCommandList<ZenithOS_CommandListSize> ZenithOS::ProgramList::ZenithOS_ExpandAndConcat(ProgramCommandList_, ZenithOS_UseProgramSlot)
#define NextCommand ZenithOS::ProgramList::Command
#endif
#endif
#endif



