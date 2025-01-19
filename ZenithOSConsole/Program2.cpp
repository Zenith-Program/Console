#define ZenithOS_UseProgramSlot 1
#define ZenithOS_CommandListSize 2
#include "ZenithOSProgramEntryPoint.hpp"
#include "ZenithOSProgramSetCommandList.hpp"

ZenithOS_ProgramCommandList = { NextCommand{"t", "", nullptr}, NextCommand{"f", "", nullptr} };
ZenithOS_RegisterProgramCommandList



#include <iostream>

Startup() {
	std::cout << "Program 1 is starting" << std::endl;
	return 0;
}

Loop() {
	std::cout << "loopdy loop" << std::endl;
}

Shutdown() {
	std::cout << "Program 1 is ending" << std::endl;
	return 0;
}