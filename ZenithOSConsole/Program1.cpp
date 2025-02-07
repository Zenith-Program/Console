#define ZenithOS_UseProgramSlot 0
#include "ZenithOSProgramEntryPoint.hpp"
#include "ZenithOSProgramSetCommandList.hpp"

#include <iostream>

ZenithOS::ProgramList::StaticCommandList<1> ProgramCommandList0 = { ZenithOS::ProgramList::Command({"Command1", "f", nullptr}) };

Startup() {
	std::cout << "Start of program 0" << std::endl;
	return 0;
}

Loop() {
	std::cout << "This is the loop of program 0" << std::endl;
}
//test comment
Shutdown() {
	std::cout << "End of program 0" << std::endl;
	return 0;
}