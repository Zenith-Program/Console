#define ZenithOS_UseProgramSlot 1
#include "ZenithOSProgramEntryPoint.hpp"

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